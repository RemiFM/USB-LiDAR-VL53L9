/**
 ******************************************************************************
 * @file    distance_calibration.c
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

#include "algo/distance_calibration.h"

#include <errno.h>
#include <stddef.h>

/**
 * @note Implementation based on reference v2.2.2
 */

void vl53l9_algo_distance_calibration_init_default_params(distance_calibration_params_t *params) {
    params->gain_correction = 0.0f;
    params->nlc_mode = 0;

    params->lut_prec[0] = -1.16f;
    params->lut_prec[1] = 0.31f;
    params->lut_prec[2] = 3.18f;
    params->lut_prec[3] = 6.67f;
    params->lut_prec[4] = 6.31f;
    params->lut_prec[5] = 3.72f;
    params->lut_prec[6] = -1.09f;
    params->lut_prec[7] = 0.0f;

    params->lut_range[0] = -6.16f;
    params->lut_range[1] = -4.69f;
    params->lut_range[2] = -1.82f;
    params->lut_range[3] = 5.05f;
    params->lut_range[4] = 4.64f;
    params->lut_range[5] = 0.63f;
    params->lut_range[6] = -7.65f;
    params->lut_range[7] = 0.0f;

    params->scaler_range = 1.0f;

    params->constant_prec = 0;
    params->constant_range = 0;
}

int32_t vl53l9_algo_distance_calibration(const float_t *const distance_in, const float_t *const calibration_in,
                                         const uint8_t *const dss_in,

                                         float_t *const distance_out,

                                         const distance_calibration_params_t *const params, uint32_t size,
                                         uint32_t step_number) {

    if ((distance_in == NULL) || (distance_out == NULL)) {
        return -1; // Missing mandatory input and output buffers
    }

    if ((params->nlc_mode == 0u) && (calibration_in == NULL)) {
        return -1; // Missing required inputs for non-NLC mode
    }

    if ((params->nlc_mode != 0u) && (dss_in == NULL)) {
        return -1; // Missing required inputs for NLC mode
    }

    for (uint32_t i = 0; i < size; i++) {

        if (calibration_in != NULL) {
            errno = 0; // MISRA-C 2012 Rule 22.8 requires to clear errno before errno-setting functions
            distance_out[i] = fmaxf(distance_in[i] + calibration_in[i], 0.0f);
        } else {
            distance_out[i] = distance_in[i];
        }

        if (params->gain_correction != 0.0f) {
            distance_out[i] *= 1.0f + params->gain_correction;
        }

        if (params->nlc_mode == 0u) {
            continue;
        } else if (params->nlc_mode == 1u) {
            const float_t lut_corr_scaler = (step_number == 7u) ? 1.0f : params->scaler_range;
            const float_t *lut_corr = (step_number == 7u) ? params->lut_prec : params->lut_range;
            float_t constant_offset =
                (step_number == 7u) ? (float_t)params->constant_prec : (float_t)params->constant_range;
            errno = 0; // MISRA-C 2012 Rule 22.8 requires to clear errno before errno-setting functions
            distance_out[i] = fmaxf(0.0f, distance_out[i] + (lut_corr_scaler * lut_corr[dss_in[i]]) + constant_offset);
        }
    }

    return 0;
}
