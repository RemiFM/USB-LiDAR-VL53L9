/**
 ******************************************************************************
 * @file    reflectance.h
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

#include <math.h>
#include <stdbool.h>
#include <stdint.h>

/**
 * @brief refletance module constants and constants computed and/or extracted from OTP
 *
 * @note Based on Python algo R_1.5.0
 *
 * @param float_t max_spads maximum number of SPADs per zone
 * @param float_t min_refl_thr lowest allowed reflectance value in percent
 * @param float_t max_refl_thr highest allowed reflectance value in percent
 * @param float_t correction_factor can be applied to fine tune threshold by scaling relative amplitude
 * @param float_t sq_law_exponent can be applied to modify square law exponent
 * @param float_t six_step_scaler coef applied to estimated reflectance for 6 steps capture
 * @param float_t cutoff_distance minimum distance to clip
 * @param bool cover_glass cover glass presence
 */
typedef struct reflectance_params_t {
    float_t max_spads;
    float_t min_refl_thr;
    float_t max_refl_thr;
    float_t correction_factor;
    float_t sq_law_exponent;
    float_t six_step_scaler;
    float_t cutoff_distance;
    bool cover_glass;
} reflectance_params_t;

/**
 * @brief init params default values
 *
 * @note Based on Python algo R_1.5.0
 */
void vl53l9_algo_reflectance_init_default_params(reflectance_params_t *params);

/**
 * @brief compute reflectance and validation map for low and high reflectance pixels
 *
 * @note Based on Python algo R_1.5.0
 *
 * @retval EXIT_SUCCESS algo ran successfuly
 * @retval EXIT_FAILURE algo ran into an issue, check errno
 *
 * @param depth input depth buffer
 * @param amplitude input amplitude buffer
 * @param main_flag input main flag buffer
 * @param effective_spads input effective spads buffer
 * @param amp_ref input amplitude reference buffer
 * @param sig_corr_factor input signal correction factor buffer
 *
 * @param reflectance output estimated reflectance
 * @param low_refl_valid output low reflectance validation buffer
 * @param high_refl_valid output high reflectance validation buffer
 *
 * @param params reflectance constant parameters
 * @param size image size in pixels
 * @param expo_sf main exposure number
 * @param expo_sc close distance exposure number
 * @param step_number number of dToF capture steps
 */
int32_t vl53l9_algo_reflectance(const float_t *depth, const float_t *amplitude, const bool *main_flag,
                                const float_t *effective_spads, const float_t *amp_ref, const float_t *sig_corr_factor,

                                float_t *reflectance, bool *low_refl_valid, bool *high_refl_valid,

                                const reflectance_params_t *params, uint32_t size, uint32_t expo_sf, uint32_t expo_sc,
                                uint32_t step_number);
