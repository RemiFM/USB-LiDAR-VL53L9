/**
 ******************************************************************************
 * @file    flying_pixel.c
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

#include "algo/flying_pixel.h"
#include <errno.h>

static void gen_reflect_kernel(uint32_t *kern, int32_t line, int32_t column, int32_t width, int32_t height);

void vl53l9_algo_flying_pixel_init_default_params(flying_pixel_params_t *params) {
    params->dmax = 8091.0f;
    params->depth_th = 375.0f;
    params->min_depth_occurence = 22u;
    params->snr_th_kernel = 17.0f;
}

int32_t vl53l9_algo_flying_pixel(const float_t *depth, const float_t *confidence,

                                 bool *flying_valid,

                                 const flying_pixel_params_t *params, uint32_t width, uint32_t height) {
    // if one of the input is missing, return
    // if all outputs are missing, return
    if ((depth == NULL) || (confidence == NULL) || (flying_valid == NULL) || (params == NULL)) {
        return EXIT_FAILURE;
    }

    uint32_t kern[9] = { 0 };
    for (uint32_t line = 0; line < height; ++line) {
        for (uint32_t column = 0; column < width; ++column) {
            gen_reflect_kernel(kern, (int32_t)line, (int32_t)column, (int32_t)width, (int32_t)height);

            float_t snr_sum = 0.0f;
            uint32_t depth_cpt = 0;
            for (uint32_t i = 0; i < 9u; ++i) {
                if (depth[kern[i]] >= params->dmax) {
                    continue;
                }

                errno = 0; // MISRA-C 2012 Rule 22.8 requires to clear errno before errno-setting functions
                if (fabsf(depth[kern[0]] - depth[kern[i]]) >= params->depth_th) {
                    continue;
                }
                ++depth_cpt;
                snr_sum += confidence[kern[i]];
            }

            flying_valid[(line * width) + column] =
                (depth_cpt > params->min_depth_occurence) || (snr_sum > params->snr_th_kernel);
        }
    }

    return EXIT_SUCCESS;
}

void gen_reflect_kernel(uint32_t *kern, int32_t line, int32_t column, int32_t width, int32_t height) {
    static const uint32_t id_order[] = { 6, 7, 8, 5, 0, 1, 4, 3, 2 }; // reversed from : {4, 5, 8, 7, 6, 3, 0, 1, 2} //

    uint32_t kern_id = 0;
    for (int32_t sub_line = -1; sub_line <= 1; ++sub_line) {
        for (int32_t sub_column = -1; sub_column <= 1; ++sub_column) {
            int32_t tmp_line = sub_line;
            int32_t tmp_column = sub_column;

            if ((column + sub_column) == -1) {
                tmp_column = 1;
            } else if ((column + sub_column) == width) {
                tmp_column = -1;
            }
            if ((line + sub_line) == -1) {
                tmp_line = 1;
            } else if ((line + sub_line) == height) {
                tmp_line = -1;
            }

            int32_t new_kernel = ((line + tmp_line) * width) + (column + tmp_column);
            kern[id_order[kern_id++]] = (uint32_t)new_kernel;
        }
    }
}
