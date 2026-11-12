/**
 ******************************************************************************
 * @file    flying_pixel.h
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

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * @brief flying pixel constants and constants computed and/or extracted from OTP
 *
 * @param dmax maximum measurable distance to set flying pixel at dMax + 1
 * @param depth_th threshold to be applied on differencies in mm
 * @param min_depth_occurence min depth occurence to be consider as valid
 * @param snr_th_kernel all the pixel snr with the same modulo are integrated the result must be considered higher
 * than this threshold to be considered as valid
 */
typedef struct flying_pixel_params_t {
    float_t dmax;
    float_t depth_th;
    uint32_t min_depth_occurence;
    float_t snr_th_kernel;
} flying_pixel_params_t;

/**
 * @brief init params default values
 *
 * Based on Python algo R_1.3.4
 */
void vl53l9_algo_flying_pixel_init_default_params(flying_pixel_params_t* params);

/**
 * @brief compute flying pixel filter map
 *
 * Based on Python algo R_1.3.4
 *
 * @param depth input depth buffer
 * @param confidence input confidence buffer
 *
 * @param flying_valid output valid flag buffer
 *
 * @param params flying pixel constant parameters
 * @param width image width
 * @param height image height
 */
int32_t vl53l9_algo_flying_pixel(const float_t* depth, const float_t* confidence,

    bool* flying_valid,

    const flying_pixel_params_t* params, uint32_t width, uint32_t height);

#ifdef __cplusplus
}
#endif
