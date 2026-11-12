/**
 ******************************************************************************
 * @file    radial_to_perp.c
 * @author  IMD Software Team
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include "algo/radial_to_perp.h"

#include <errno.h>
#include <stddef.h>
#include <stdlib.h>

#ifndef EINVAL
#define EINVAL 22
#endif

typedef uint32_t u32;
typedef uint8_t u8;

typedef float_t f32;

static inline f32 minf(f32 a, f32 b) {
    return (a < b) ? a : b;
}

static inline f32 maxf(f32 a, f32 b) {
    return (a > b) ? a : b;
}

static inline f32 rsqrt(f32 number) {
    union {
        f32 f;
        u32 i;
    } conv = { .f = number };
    conv.i = (u32)0x5F375A86 - (conv.i >> 1);
    conv.f *= 1.5f - (number * 0.5f * conv.f * conv.f);
    conv.f *= 1.5f - (number * 0.5f * conv.f * conv.f);
    return conv.f;
}

static inline f32 compute_distortion(f32 rsq, f32 alpha, f32 beta, f32 gamma, f32 kappa, f32 binning) {
    const f32 distorsion = (alpha * rsq) + (beta * rsq * rsq) + (gamma * rsq * rsq * rsq) + kappa;
    const f32 binning_distortion = binning * binning / 4.0f;

    return 1.0f + (binning_distortion * distorsion);
}

void vl53l9_algo_radial_to_perp_init_default_params(radial_to_perp_params_t *params) {
    params->efl = 2428.16f;
    params->residual_offset_x = 0.0f;
    params->residual_offset_y = 0.0f;
    params->max_distance = 9600;
    params->parallax_correction = true;
    params->parallax_limit = 50;
    params->alpha = -0.00015f;
    params->beta = 0.0f;
    params->gamma = 0.0f;
    params->kappa = 0.0f;
    params->max_spads_x = 216;
    params->max_spads_y = 168;
    params->spad_size_um = 10.17f;
}

int32_t vl53l9_algo_radial_to_perp(const f32 *depth,

                                   f32 *output_z, f32 *center_x, f32 *distorsion, bool *r2p_valid,

                                   const radial_to_perp_params_t *params, u32 width, u32 height, u32 binning) {
    // if one of the input is missing, return
    // if all outputs are missing, return
    if ((depth == NULL) || !((output_z != NULL) || (center_x != NULL) || (distorsion != NULL) || (r2p_valid != NULL))) {
        errno = EINVAL;
        return EXIT_FAILURE;
    }

    const f32 mspads_x = (f32)params->max_spads_x / 2.0f;
    const f32 mspads_y = (f32)params->max_spads_y / 2.0f;
    const f32 mpix = (f32)binning * 2.0f;
    const f32 focal = params->efl / (params->spad_size_um * mpix);

    const f32 x_center =
        ((mspads_x + params->residual_offset_x - (mspads_x - ((f32)binning * (f32)width))) / mpix) - 0.5f;
    const f32 y_center =
        ((mspads_y + params->residual_offset_y - (mspads_y - ((f32)binning * (f32)height))) / mpix) - 0.5f;

    for (u32 y = 0; y < height; ++y) {
        for (u32 x = 0; x < width; ++x) {
            const u32 linear_id = (y * width) + x;
            f32 dist_from_center_x = (f32)x - x_center;
            const f32 dist_from_center_y = (f32)y - y_center;
            f32 dist_from_center_sq =
                (dist_from_center_x * dist_from_center_x) + (dist_from_center_y * dist_from_center_y);
            f32 dist_from_center_ud = compute_distortion(dist_from_center_sq, params->alpha, params->beta,
                                                         params->gamma, params->kappa, (f32)binning);

            f32 depth_perp =
                depth[linear_id] *
                rsqrt(1.0f + (dist_from_center_sq / (dist_from_center_ud * dist_from_center_ud * focal * focal)));

            f32 new_x_center = x_center;
            if (params->parallax_correction) {
                new_x_center =
                    x_center - (params->efl * 7.166f /
                                (maxf((f32)params->parallax_limit, depth_perp) * params->spad_size_um * mpix));
                if (center_x) {
                    center_x[linear_id] = new_x_center;
                }
                dist_from_center_x = (f32)x - new_x_center;
                dist_from_center_sq =
                    (dist_from_center_x * dist_from_center_x) + (dist_from_center_y * dist_from_center_y);
                dist_from_center_ud = compute_distortion(dist_from_center_sq, params->alpha, params->beta,
                                                         params->gamma, params->kappa, (f32)binning);
                if ((bool)errno) {
                    return EXIT_FAILURE;
                }
                if (distorsion) {
                    distorsion[linear_id] = dist_from_center_ud;
                }

                depth_perp =
                    depth[linear_id] *
                    rsqrt(1.0f + (dist_from_center_sq / (dist_from_center_ud * dist_from_center_ud * focal * focal)));
            }

            if (output_z) {
                output_z[linear_id] = depth_perp;
            }
            if (r2p_valid) {
                r2p_valid[linear_id] = depth_perp <= (f32)params->max_distance;
            }
        }
    }

    return EXIT_SUCCESS;
}

int32_t vl53l9_algo_pointcloud(const f32 *depth, const f32 *center_x, const f32 *distorsion, const f32 *confidence,
                               const f32 *conf_thr, const u8 *filter_status,

                               f32 *pointcloud,

                               const radial_to_perp_params_t *params, u32 width, u32 height, u32 binning) {
    // if parralax is enabled and center_x is missing, return
    if (params->parallax_correction && (center_x == NULL)) {
        errno = EINVAL;
        return EXIT_FAILURE;
    }
    // if one of the other input is missing, return
    // if all outputs are missing, return
    if ((depth == NULL) || (distorsion == NULL) || (confidence == NULL) || (conf_thr == NULL) ||
        (filter_status == NULL) || (pointcloud == NULL)) {
        errno = EINVAL;
        return EXIT_FAILURE;
    }

    const f32 mspads_x = (f32)params->max_spads_x / 2.0f;
    const f32 mspads_y = (f32)params->max_spads_y / 2.0f;
    const f32 mpix = (f32)binning * 2.0f;
    const f32 focal = params->efl / (params->spad_size_um * mpix);

    const f32 x_center =
        ((mspads_x + params->residual_offset_x - (mspads_x - ((f32)binning * (f32)width))) / mpix) - 0.5f;
    const f32 y_center =
        ((mspads_y + params->residual_offset_y - (mspads_y - ((f32)binning * (f32)height))) / mpix) - 0.5f;

    for (u32 y = 0; y < height; ++y) {
        for (u32 x = 0; x < width; ++x) {
            const u32 linear_id = (y * width) + x;
            const f32 dist_from_center_x = (f32)x - (params->parallax_correction ? center_x[linear_id] : x_center);
            const f32 dist_from_center_y = (f32)y - y_center;
            const f32 distorted_z = depth[linear_id] / (distorsion[linear_id] * focal);

            const f32 pcx = dist_from_center_x * distorted_z;
            const f32 pcy = dist_from_center_y * distorted_z;

            pointcloud[linear_id * 4u] = pcx;
            pointcloud[(linear_id * 4u) + 1u] = pcy;
            pointcloud[(linear_id * 4u) + 2u] = depth[linear_id];
            pointcloud[(linear_id * 4u) + 3u] =
                minf(confidence[linear_id] / (params->conf_scaling * conf_thr[linear_id]), 1.0f);

            errno = 0;
            pointcloud[(linear_id * 4u) + 3u] =
                (floorf((pointcloud[(linear_id * 4u) + 3u]) * 1e3f) * 1e-3f) + ((f32)filter_status[linear_id] * 1e-6f);
            if ((bool)errno) {
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}
