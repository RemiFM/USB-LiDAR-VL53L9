/**
 ******************************************************************************
 * @file    confidence.c
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

#include "algo/confidence.h"

#include <errno.h>
#include <stddef.h>

/**
 * @note Implementation based on reference v1.10.4
 */

static float_t _compute_confidence_with_cover_glass(float_t amplitude, float_t ambient, float_t xtalk_est);
static float_t _compute_confidence_without_cover_glass(float_t amplitude, float_t ambient);
static float_t _compute_integration_time(uint32_t nb_steps, const uint32_t nb_shots[4]);

void vl53l9_algo_confidence_init_default_params(confidence_params_t *params) {
    params->cover_glass = false;
    params->signal_factor = 1.4f;
    params->ambient_factor = 1.0f;
    params->ambient_window = 64.0f;
    params->ambient_blanking = 0.0f;
    params->threshold_six = 3.8f;
    params->threshold_six_c = 3.5185f;
    params->threshold_seven = 3.8707f;
    params->threshold_seven_c = 3.5185f;
    params->threshold_scaler = 1.0f;
    params->threshold_scaler_cover_glass = 1.0f;
    params->xtalk_coeff = 2.0f;
}

int32_t vl53l9_algo_confidence(const float_t *const ambient_in, const float_t *const amplitude_in,
                               const bool *const msb_in, const float_t *const effective_spads_in,
                               const float_t *const noise_reduction_in,

                               float_t *const confidence_out, float_t *const threshold_out, bool *const validity_out,
                               float_t *const xtalk_est_out,

                               const confidence_params_t *const params, uint32_t size, uint32_t nb_steps,
                               uint32_t ambient_attenuation, const uint32_t nb_shots[4]) {

    // return error if any of the mandatory pointers is NULL
    if ((ambient_in == NULL) || (amplitude_in == NULL) || (msb_in == NULL) || (effective_spads_in == NULL) ||
        (confidence_out == NULL) || (threshold_out == NULL) || (validity_out == NULL) || (xtalk_est_out == NULL) ||
        (params == NULL)) {
        return -1;
    }

    // compute internal parameters
    float_t scaling_factor_short, scaling_factor_main;
    float_t threshold_short, threshold_main;
    float_t integration_time = _compute_integration_time(nb_steps, nb_shots);
    uint32_t amb_attenuation_shifted = ((uint32_t)1u << ambient_attenuation);

    float_t ambient_scaling_factor = params->ambient_factor * (float_t)amb_attenuation_shifted /
                                     ((float_t)nb_shots[3] * (params->ambient_window + params->ambient_blanking));

    // compute scaling factor and thresholds depending on number of steps
    if (nb_steps == 7u) {
        scaling_factor_main = (float_t)nb_shots[1] * 4.0f * ambient_scaling_factor;
        scaling_factor_short = (float_t)nb_shots[2] * 4.0f * ambient_scaling_factor;
        threshold_main = params->threshold_seven * params->threshold_scaler;
        threshold_short = params->threshold_seven_c * params->threshold_scaler;
    } else {
        scaling_factor_main = (float_t)nb_shots[1] * 8.0f * ambient_scaling_factor;
        scaling_factor_short = (float_t)nb_shots[2] * 8.0f * ambient_scaling_factor;
        threshold_main = params->threshold_six * params->threshold_scaler;
        threshold_short = params->threshold_six_c * params->threshold_scaler;
    }

    // calculate confidence
    if (params->cover_glass) {
        for (uint32_t i = 0; i < size; i++) {
            float_t scaling_factor = (msb_in[i] == false) ? scaling_factor_short : scaling_factor_main;
            xtalk_est_out[i] =
                params->xtalk_coeff * integration_time * params->threshold_scaler_cover_glass * effective_spads_in[i];
            confidence_out[i] = _compute_confidence_with_cover_glass(amplitude_in[i] * params->signal_factor,
                                                                     ambient_in[i] * scaling_factor, xtalk_est_out[i]);
        }
    } else {
        for (uint32_t i = 0; i < size; i++) {
            float_t scaling_factor = (msb_in[i] == false) ? scaling_factor_short : scaling_factor_main;
            xtalk_est_out[i] = 0.0f;
            confidence_out[i] = _compute_confidence_without_cover_glass(amplitude_in[i] * params->signal_factor,
                                                                        ambient_in[i] * scaling_factor);
        }
    }

    if (noise_reduction_in != NULL) {
        for (uint32_t i = 0; i < size; i++) {
            confidence_out[i] /= noise_reduction_in[i];
        }
    }

    // calculate threshold
    for (uint32_t i = 0; i < size; i++) {
        threshold_out[i] = (msb_in[i] == false) ? threshold_short : threshold_main;
    }

    // calculate validity
    for (uint32_t i = 0; i < size; i++) {
        validity_out[i] =
            (msb_in[i] == false) ? (confidence_out[i] > threshold_short) : (confidence_out[i] > threshold_main);
    }

    return 0;
}

static float_t _compute_confidence_with_cover_glass(float_t amplitude, float_t ambient, float_t xtalk_est) {
    const float_t num = ((amplitude * amplitude) - (xtalk_est * xtalk_est));
    const float_t den = (amplitude + ambient + xtalk_est);

    if ((num > 0.0f) && (den > 0.0f)) {
        errno = 0; // MISRA-C 2012 Rule 22.8 requires to clear errno before errno-setting functions
        return sqrtf(num / den);
    } else {
        return 0.0f;
    }
}

static float_t _compute_confidence_without_cover_glass(float_t amplitude, float_t ambient) {

    const float_t sum_amp_amb = ambient + amplitude;
    if (sum_amp_amb < 0.0f) {
        return 0.0f;
    } else {
        errno = 0; // MISRA-C 2012 Rule 22.8 requires to clear errno before errno-setting functions
        return amplitude / sqrtf(sum_amp_amb);
    }
}

static float_t _compute_integration_time(uint32_t nb_steps, const uint32_t nb_shots[4]) {

    const uint32_t seven_step_periods[7] = { 360, 180, 90, 84, 82, 82, 80 };
    const uint32_t six_step_periods[7] = { 360, 180, 90, 84, 80, 84, 80 };

    float_t expos[7] = {
        1.0f * (float_t)nb_shots[0], 2.0f * (float_t)nb_shots[0], 4.0f * (float_t)nb_shots[0], 0.0f, 0.0f, 0.0f, 0.0f
    };

    if (nb_steps == 7u) {
        expos[3] = 8.0f * (float_t)nb_shots[0];
        expos[4] = (float_t)nb_shots[1];
        expos[5] = (float_t)nb_shots[2];
        expos[6] = (float_t)nb_shots[3];
    } else {
        expos[3] = (float_t)nb_shots[1];
        expos[4] = 0.0f;
        expos[5] = (float_t)nb_shots[2];
        expos[6] = (float_t)nb_shots[3];
    }

    // hadamard product of matrix and accumulation
    float_t integration_time = 0.0f;
    float_t weighted_expos[7] = { 0 };

    for (uint8_t i = 0; i < 7u; i++) {
        weighted_expos[i] =
            expos[i] * ((nb_steps == 7u) ? (float_t)seven_step_periods[i] : (float_t)six_step_periods[i]);
        integration_time += weighted_expos[i];
    }

    return integration_time * 2.0e-6f; // apply 2x factor and convert to us
}
