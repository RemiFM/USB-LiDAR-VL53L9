/**
 ******************************************************************************
 * @file    distance_check.c
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

#include "algo/distance_check.h"

#include <stddef.h>

/**
 * @note Based on version R_1.4.14
 */

int32_t vl53l9_algo_distance_check(const float_t *const distance_in, const float_t *const dmax_in,
                                   const bool *const r2p_valid_in, const bool *const confidence_valid_in,
                                   const bool *const reflectance_valid_in, const bool *const sharpener_valid_in,
                                   const bool *const fp_valid_in,

                                   float_t *const distance_out, uint8_t *const status_out,

                                   uint32_t size, bool r2p_filter, bool confidence_filter, bool reflectance_filter,
                                   bool sharpener_filter, bool fp_filter, bool dmax_select, bool replace_distance,
                                   float_t max_distance, float_t invalid_distance) {

    // check mandatory pointers
    if ((distance_in == NULL) || (distance_out == NULL) || (status_out == NULL)) {
        return -1;
    }

    for (uint32_t i = 0; i < size; i++) {

        bool is_r2p_invalid = (((r2p_valid_in != NULL) && r2p_filter) ? !r2p_valid_in[i] : false);
        bool is_confidence_invalid =
            (((confidence_valid_in != NULL) && confidence_filter) ? !confidence_valid_in[i] : false);
        bool is_reflectance_invalid =
            (((reflectance_valid_in != NULL) && reflectance_filter) ? !reflectance_valid_in[i] : false);
        bool is_sharpener_invalid =
            (((sharpener_valid_in != NULL) && sharpener_filter) ? !sharpener_valid_in[i] : false);
        bool is_fp_invalid = (((fp_valid_in != NULL) && fp_filter) ? !fp_valid_in[i] : false);

        // TODO: check dmax_in dmax_select is true

        distance_out[i] = distance_in[i];

        if (is_r2p_invalid) {
            distance_out[i] = max_distance;
        }

        if (is_confidence_invalid) {
            if (dmax_select) {
                distance_out[i] = dmax_in[i];
            } else if (replace_distance) {
                distance_out[i] = invalid_distance;
            }
        }

        if (replace_distance && (is_reflectance_invalid || is_sharpener_invalid || is_fp_invalid)) {
            distance_out[i] = invalid_distance;
        }

        // use inverse logic for constant valid status equal to zero
        status_out[i] = ((uint8_t)is_confidence_invalid) | ((uint8_t)is_reflectance_invalid << 1u) |
                        ((uint8_t)is_sharpener_invalid << 2u) | ((uint8_t)is_r2p_invalid << 3u) |
                        ((uint8_t)is_fp_invalid << 4u);
    }
    return 0;
}
