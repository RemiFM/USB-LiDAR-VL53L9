/*******************************************************************************
 *
 * Copyright (c) 2026 STMicroelectronics - All Rights Reserved
 *
 * License terms: STMicroelectronics Proprietary in accordance with licensing
 * terms at SLA0106
 *
 * STMicroelectronics confidential
 * Reproduction and Communication of this document is strictly prohibited unless
 * specifically authorized in writing by STMicroelectronics.
 *
 *******************************************************************************
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
 * @brief dmax module constants and constants computed and/or extracted from OTP
 *
 * @note Based on Python algo R_1.2.3
 *
 * @param bool cover_glass module has cover glass or not
 * @param uint32_t ambient_scaling quantisation factor of the ambient map
 * @param float_t ambient_clip quantisation zero clip replacement value
 * @param float_t max_spads maximum effective spad count (OTP)
 * @param float_t signal_factor conversion from amplitude to photon count
 * @param float_t six_step_scaler scaling parameter to translate reference signal from 7 to 6 steps
 * @param float_t max_distance fallback invalid distance value
 * @param float_t dmax_reflectance minimum detectable reflectance in percent
 * @param float_t dmax_correction dmax correction coefficient
 */
typedef struct dmax_params_t {
    bool cover_glass;
    uint32_t ambient_scaling;
    float_t ambient_clip;
    float_t max_spads;
    float_t signal_factor;
    float_t six_step_scaler;
    float_t max_distance;
    float_t dmax_reflectance;
    float_t dmax_correction;
} dmax_params_t;

/**
 * @brief init params default values
 *
 * @note Based on Python algo R_1.2.3
 */
void vl53l9_algo_dmax_init_default_params(dmax_params_t *params);

/**
 * @brief compute dmax map
 *
 * @note Based on Python algo R_1.2.3
 *
 * @retval EXIT_SUCCESS algo ran successfuly
 * @retval EXIT_FAILURE algo ran into an issue, check errno
 *
 * @param ambient input ambient
 * @param amp_norm input reference amplitude
 * @param r2p_coefs input r2p coefs
 * @param effective_spads input effective spads
 * @param conf_xtalk_est input confidence xtalk estimation
 * @param reflectance input reflectance
 * @param conf_valid input confidence valid flags
 * @param sig_correction_factor input signal correction factor, can be applied to fine tune scaling of
 * reference amplitude
 *
 * @param dmax output dmax map
 *
 * @param params dmax params
 * @param size image size
 * @param step_number number of dtof stages
 * @param conf_threshold_main confidence threshold for main sequence
 * @param auto_expo flag for auto exposure being active or not
 */
int32_t vl53l9_algo_dmax(const float_t *ambient, const float_t *amp_norm, const float_t *r2p_coefs,
    const float_t *effective_spads, const float_t *conf_xtalk_est, const float_t *reflectance, const bool *conf_valid,
    const float_t *sig_correction_factor,

    float_t *dmax,

    const dmax_params_t *params, uint32_t size, uint32_t step_number, float_t conf_threshold_main, bool auto_expo);

#ifdef __cplusplus
}
#endif
