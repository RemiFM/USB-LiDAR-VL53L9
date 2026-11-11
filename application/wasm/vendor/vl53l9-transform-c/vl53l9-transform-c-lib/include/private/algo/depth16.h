/**
 ******************************************************************************
 * @file    depth16.h
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
 * @brief depth16 confidence format enum
 *
 * @note Based on Python algo R_1.2.2
 *
 * @param DEPTH16_FORMAT_DEFAULT linear scaling from float to 3 bit confidence
 * @param DEPTH16_FORMAT_3DMAX 3DMax standardised depth16 confidence, with a linear scaling from float to confidence and
 *  2 values reserved for filter status
 * @param DEPTH16_FORMAT_CUSTOM 3DMax custom depth16 confidence format, all values represent filter status combinations
 */
typedef enum depth16_format_e {
    DEPTH16_FORMAT_DEFAULT,
    DEPTH16_FORMAT_3DMAX,
    DEPTH16_FORMAT_CUSTOM
} depth16_format_e;

/**
 * @brief depth16 module constants and constants computed and/or extracted from OTP
 *
 * @note Based on Python algo R_1.2.2
 *
 * @param depth16_format_e format depth16 confidence format
 */
typedef struct depth16_params_t {
    depth16_format_e format;
} depth16_params_t;

/**
 * @brief init params default values
 *
 * @note Based on Python algo R_1.2.2
 */
void vl53l9_algo_depth16_init_default_params(depth16_params_t* params);

/**
 * @brief assemble depth16 from depth and confidence with configurable confidence
 *
 * @note Based on Python algo R_1.2.2
 *
 * @details reference : https://developer.android.com/reference/android/graphics/ImageFormat#DEPTH16
 *
 * @retval EXIT_SUCCESS algo ran successfuly
 * @retval EXIT_FAILURE algo ran into an issue, check errno
 *
 * @param depth input depth buffer
 * @param filter_status input filter status
 * @param confidence input confidence buffer
 * @param conf_thr input confidence threshold buffer
 *
 * @param depth16 output depth16
 *
 * @param params depth16 constant parameters
 * @param size image size in pixels
 */
int32_t vl53l9_algo_depth16(const float_t* depth, const uint8_t* filter_status, const float_t* confidence,
    const float_t* conf_thr,

    uint16_t* depth16,

    const depth16_params_t* params, uint32_t size);

#ifdef __cplusplus
}
#endif
