/**
 ******************************************************************************
 * @file    ratenorm.h
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

/**
 * @brief ratenorm module constants and constants computed and/or extracted from OTP
 *
 * @note Based on Python algo R_1.9.6
 *
 * @param bool fast_mode trigger ratenorm fast mode (no bicubic interpolation)
 * @param bool ambient_signal_correction enable ambient signal correction computation
 * @param uint32_t ref_mode Reference computation modes
 * @param uint32_t ref_scaler reference scaler
 * @param uint32_t ref_distance reference distance
 * @param uint32_t ref_reflectance reference reflectance
 * @param uint32_t ref_expo reference exposition
 * @param uint32_t ref_amp_const Constant Reference Amplitude
 * @param uint32_t nominal_width nominal reference image width
 * @param uint32_t nominal_height nominal reference image height
 * @param uint32_t nominal_binningnominal reference image binning
 * @param float_t ambient_window window size of ambient step in ns
 * @param float_t ambient_blanking Blank timing for windows in ns
 * @param float_t signal_factor conversion from amplitude to photon count
 * @param float_t ambient_correction_factor factor to determine signal correction due to ambient
 * @param float_t main_scaler Scaler to refine all reference values
 * @param float_t side_scaler Scaler to refine direct neighbours
 * @param float_t corner_scaler Scaler to diagonal corner neighbours
 * @param float_t left_side_l_scaler Correcting left side column of coefficients
 * @param float_t right_side_l_scaler Correcting right side column of coefficients
 * @param float_t middle_section_l_scaler Correcting middle region coefficients
 * @param float_t center_region_l_scaler Correcting central region coefficients
 * @param float_t peak_l_scaler Correcting centre peak pixel
 * @param float_t top_row_l_scaler Correcting top row (excluding corners))
 * @param float_t bottom_row_l_scaler Correcting bottom row (excluding corners))
 * @param float_t corner_post_l_scaler Relative corner correction factor
 * @param float_t exposure_width_0 exposure width for 7 step captures
 * @param float_t exposure_width_1 exposure width for 6 step captures
 * @param float_t max_spads Max. SPADs of current device config
 * @param float_t max_spads_ref Max. SPAD state at reference measurement
 * @param float_t bicubic_coef bicubic interpolation coefficient, -0.75 is standard
 */
typedef struct ratenorm_params_t {
    bool fast_mode;
    bool ambient_signal_correction;
    uint32_t ref_mode;
    uint32_t ref_scaler;
    uint32_t ref_distance;
    uint32_t ref_reflectance;
    uint32_t ref_expo;
    uint32_t ref_amp_const;
    uint32_t nominal_width;
    uint32_t nominal_height;
    uint32_t nominal_binning;
    float_t ambient_window;
    float_t ambient_blanking;
    float_t signal_factor;
    float_t ambient_correction_factor;
    float_t main_scaler;
    float_t side_scaler;
    float_t corner_scaler;
    float_t left_side_l_scaler;
    float_t right_side_l_scaler;
    float_t middle_section_l_scaler;
    float_t center_region_l_scaler;
    float_t peak_l_scaler;
    float_t top_row_l_scaler;
    float_t bottom_row_l_scaler;
    float_t corner_post_l_scaler;
    float_t exposure_width_0;
    float_t exposure_width_1;
    float_t max_spads;
    float_t max_spads_ref;
    float_t bicubic_coef;
} ratenorm_params_t;

/**
 * @brief bicubic interpolation from input to output
 *
 * @note Based on Python algo R_1.9.6
 *
 * @retval EXIT_SUCCESS algo ran successfuly
 * @retval EXIT_FAILURE algo ran into an issue, check errno
 *
 * @param input input array
 *
 * @param output output array
 *
 * @param width_in input width
 * @param height_in input height
 * @param width_out output width
 * @param height_out output height
 * @param a bicubic interpolation coefficient, -0.75 is standard
 */
int32_t vl53l9_algo_ratenorm_bicubic_resize(const float_t *input,

                                            float_t *output,

                                            uint32_t width_in, uint32_t height_in, uint32_t width_out,
                                            uint32_t height_out, float_t a);

/**
 * @brief init params default values
 *
 * @note Based on Python algo R_1.9.6
 */
void vl53l9_algo_ratenorm_init_default_params(ratenorm_params_t *params);

/**
 * @brief compute nomilized maps at calibration time, once per stream
 *
 * @note Based on Python algo R_1.9.6
 *
 * @retval EXIT_SUCCESS algo ran successfuly
 * @retval EXIT_FAILURE algo ran into an issue, check errno
 *
 * @param reference_coefs OTP stored amplitude coefficients
 * @param r2p_coefs Radial to Perpendicular coeeficients
 *
 * @param ref_amp_no_expo amplitude reference without expoSF
 * @param ref_amp_rad_no_expo spherical amplitude reference without expoSF
 * @param coeff_norm_no_expo spatial rate correction without expoSF
 *
 * @param params ratenorm params
 * @param width output width
 * @param height output height
 * @param binning output binning
 */
int32_t vl53l9_algo_ratenorm_compute_norm_maps(const float_t *reference_coefs, const float_t *r2p_coefs,

                                               float_t *ref_amp_no_expo, float_t *ref_amp_rad_no_expo,
                                               float_t *coeff_norm_no_expo,

                                               const ratenorm_params_t *params, uint32_t width, uint32_t height,
                                               uint32_t binning);

/**
 * @brief compute rates
 *
 * @note Based on Python algo R_1.9.6
 *
 * @retval EXIT_SUCCESS algo ran successfuly
 * @retval EXIT_FAILURE algo ran into an issue, check errno
 *
 * @param amplitude input amplitude
 * @param ambient input ambient
 * @param effective_spads input effective spads
 * @param main_flag input main flag
 * @param ref_amp_no_expo input amplitude reference without expoSF
 * @param ref_amp_rad_no_expo input spherical amplitude reference without expoSF
 * @param coeff_norm_no_expo input spatial rate correction without expoSF
 *
 * @param ref_amp output amplitude reference
 * @param ref_amp_rad output spherical amplitude reference
 * @param signal_photon_rate output signal photon_rate
 * @param ambient_photon_rate output ambient photon rate
 * @param rescaled_ambient output rescaled ambient
 * @param signal_ambient_factor output signal correction factor due to ambient
 *
 * @param params ratenorm params
 * @param size image size
 * @param step_number step number
 * @param expo_sf main exposure number
 * @param expo_sc close distance exposure number
 * @param expo_sa ambient exposure number
 * @param ambient_attenuation Ambient attenuation shift
 */
int32_t vl53l9_algo_ratenorm_compute_rates(
    const float_t *amplitude, const float_t *ambient, const float_t *effective_spads, const bool *main_flag,
    const float_t *ref_amp_no_expo, const float_t *ref_amp_rad_no_expo, const float_t *coeff_norm_no_expo,

    float_t *ref_amp, float_t *ref_amp_rad, float_t *signal_photon_rate, float_t *ambient_photon_rate,
    float_t *rescaled_ambient, float_t *signal_ambient_factor,

    const ratenorm_params_t *params, uint32_t size, uint32_t step_number, uint32_t expo_sf, uint32_t expo_sc,
    uint32_t expo_sa, uint32_t ambient_attenuation);

#ifdef __cplusplus
}
#endif
