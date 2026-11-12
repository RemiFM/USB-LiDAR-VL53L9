/**
 ******************************************************************************
 * @file    confidence.h
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

#ifndef CONFIDENCE_H
#define CONFIDENCE_H

#include <math.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct confidence_params_t {
    bool cover_glass; // true if cover glass is present
    float_t signal_factor;
    float_t ambient_factor;
    float_t ambient_window;
    float_t ambient_blanking;
    float_t threshold_six;
    float_t threshold_six_c;
    float_t threshold_seven;
    float_t threshold_seven_c;
    float_t threshold_scaler;
    float_t threshold_scaler_cover_glass;
    float_t xtalk_coeff;
} confidence_params_t;

void vl53l9_algo_confidence_init_default_params(confidence_params_t *params);

/**
 * @brief
 *
 * @note If noise_reduction_in is set to NULL it is not applied on confidence_out.
 *
 * @return 0 on success, -1 in case of error
 */
int32_t vl53l9_algo_confidence(const float_t *const ambient_in, const float_t *const amplitude_in,
                               const bool *const msb_in, const float_t *const effective_spads_in,
                               const float_t *const noise_reduction_in,

                               float_t *const confidence_out, float_t *const threshold_out, bool *const validity_out,
                               float_t *const xtalk_est_out,

                               const confidence_params_t *const params, uint32_t size, uint32_t nb_steps,
                               uint32_t ambient_attenuation, const uint32_t nb_shots[4]);

#endif // CONFIDENCE_H
