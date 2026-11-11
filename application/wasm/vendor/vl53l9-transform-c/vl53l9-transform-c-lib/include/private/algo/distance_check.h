/**
 ******************************************************************************
 * @file    distance_check.h
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

#ifndef DISTANCE_CHECK_H
#define DISTANCE_CHECK_H

#include <math.h>
#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Filter unrealible values from input image depending on validity flags
 */
int32_t vl53l9_algo_distance_check(const float_t *const distance_in, const float_t *const dmax_in,
                               const bool *const r2p_valid_in, const bool *const confidence_valid_in,
                               const bool *const reflectance_valid_in, const bool *const sharpener_valid_in,
                               const bool *const fp_valid_in,

                               float_t *const distance_out, uint8_t *const status_out,

                               uint32_t size, bool r2p_filter, bool confidence_filter, bool reflectance_filter,
                               bool sharpener_filter, bool fp_filter, bool dmax_select, bool replace_distance,
                               float_t max_distance, float_t invalid_distance);

#endif /* DISTANCE_CHECK_H */
