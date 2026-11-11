/**
 ******************************************************************************
 * @file    reflectance.c
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

#include "algo/reflectance.h"

#include <errno.h>
#include <stdlib.h>

#ifndef EINVAL
#define EINVAL 22
#endif

typedef int32_t i32;
typedef uint32_t u32;

typedef float float32_t;
typedef float32_t f32;

void vl53l9_algo_reflectance_init_default_params(reflectance_params_t *params) {
    params->max_spads = 10.0f;
    params->max_refl_thr = 200.0f;
    params->min_refl_thr = 1.0f;
    params->correction_factor = 1.0f;
    params->sq_law_exponent = 1.995f;
    params->six_step_scaler = 2.9f;
    params->cutoff_distance = 25.0f;
    params->cover_glass = false;
}

i32 vl53l9_algo_reflectance(const f32 *depth, const f32 *amplitude, const bool *main_flag, const f32 *effective_spads,
                            const f32 *amp_ref, const f32 *sig_corr_factor,

                            f32 *reflectance, bool *low_refl_valid, bool *high_refl_valid,

                            const reflectance_params_t *params, u32 size, u32 expo_sf, u32 expo_sc, u32 step_number) {
    // if one of the input is missing, return
    // if all outputs are missing, return
    if (!(bool)depth || !(bool)amplitude || !(bool)main_flag || !(bool)effective_spads || !(bool)amp_ref ||
        !((bool)reflectance || (bool)low_refl_valid || (bool)high_refl_valid)) {
        errno = EINVAL;
        return EXIT_FAILURE;
    }

    f32 xt_correction;
    if (params->cover_glass) {
        if (step_number == 7u) {
            if (params->min_refl_thr > 1.0f) {
                xt_correction = 1.1f - (params->min_refl_thr / 80.0f);
            } else {
                xt_correction = 2.25f - params->min_refl_thr;
            }
        } else {
            xt_correction = 0.9f;
        }
    } else {
        xt_correction = 1.0f;
    }

    for (u32 i = 0; i < size; ++i) {
        errno = 0;
        const f32 depth_val = fmaxf(params->cutoff_distance, depth[i]);
        if ((bool)errno) {
            return EXIT_FAILURE;
        }
        const f32 coef = (main_flag[i] ? 1.0f : ((f32)expo_sc / (f32)expo_sf)) *
                         ((step_number == 6u) ? params->six_step_scaler : 1.0f);
        f32 amp_1pc = coef * xt_correction * amp_ref[i] * 1e6f * effective_spads[i] * sig_corr_factor[i] *
                      params->correction_factor / (powf(depth_val, params->sq_law_exponent) * params->max_spads);
        errno = 0;
        amp_1pc = fmaxf(0.0f, fminf(amp_1pc, 65535.0f));
        if ((bool)errno) {
            return EXIT_FAILURE;
        }

        errno = 0;
        f32 reflectance_val = fmaxf(0.0f, amplitude[i] / amp_1pc);
        if ((bool)errno) {
            return EXIT_FAILURE;
        }

        if (reflectance) {
            reflectance[i] = reflectance_val;
        }
        if (low_refl_valid) {
            low_refl_valid[i] = reflectance_val >= params->min_refl_thr;
        }
        if (high_refl_valid) {
            high_refl_valid[i] = reflectance_val < params->max_refl_thr;
        }
    }

    return EXIT_SUCCESS;
}
