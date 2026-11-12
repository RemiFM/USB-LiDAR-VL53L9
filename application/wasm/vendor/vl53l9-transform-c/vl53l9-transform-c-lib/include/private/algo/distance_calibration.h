/**
 ******************************************************************************
 * @file    distance_calibration.h
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

#ifndef DISTANCE_CALIBRATION_H
#define DISTANCE_CALIBRATION_H

#include <math.h>
#include <stdint.h>

typedef struct distance_calibration_params_t {
    float_t gain_correction; // Gain correction factor (applies 1 + gain_correction, i.e. 0.1 means 10% gain)
    uint32_t nlc_mode;       // Non linear correction mode (0: off, 1, 2, 3)
    int32_t constant_prec;   // Constant offset value (for 7 steps)
    int32_t constant_range;  // Constant offset value (for 6 steps)
    float_t scaler_range;    // Scaler for range LUT
    float_t lut_prec[8];     // LUT X precision offsets (for 7 steps)
    float_t lut_range[8];    // LUT X range offsets (for 6 steps)
} distance_calibration_params_t;

void vl53l9_algo_distance_calibration_init_default_params(distance_calibration_params_t *params);

/**
 * @brief Apply calibration map to depth image
 *
 * @param[in] distance_in
 * @param[in] calibration_in
 * @param[in] dss_in
 *
 * @param[out] distance_out
 *
 * @param[in] size
 * @param[in] step_number
 * @param[in] params
 *
 * @note input and output buffers are assumed to be row-major
 * @note input and output buffers are assumed to have the same size
 */
int32_t vl53l9_algo_distance_calibration(const float_t *const distance_in, const float_t *const calibration_in,
                                         const uint8_t *const dss_in,

                                         float_t *const distance_out,

                                         const distance_calibration_params_t *const params, uint32_t size,
                                         uint32_t step_number);

#endif // DISTANCE_CALIBRATION_H
