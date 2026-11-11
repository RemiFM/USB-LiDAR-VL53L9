/**
 ******************************************************************************
 * @file    sharpener.h
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

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

/**
 * @brief sharpener mode enum
 *
 * @note Based on Python algo R_1.6.2
 *
 * @invariant SHARPENER_MODE_SORT sharpener sorting mode (not supported)
 * @invariant SHARPENER_MODE_OPTIM sharpener optimized mode (not supported)
 * @invariant SHARPENER_MODE_DOUBLE_SHARP sharpener optimized mode run twice for quality purposes (not supported)
 */
typedef enum sharpener_mode_e {
    SHARPENER_MODE_SORT,
    SHARPENER_MODE_OPTIM,
    SHARPENER_MODE_DOUBLE_SHARP
} sharpener_mode_e;

/**
 * @brief sharpener module constants and constants computed and/or extracted from OTP
 *
 * @note Based on Python algo R_1.6.2
 *
 * @param mode sharpener mode
 * @param exp_optim use exponential approximation (taylor series) instead of exp()
 * @param recover_mode sharpener recover mode switch (estimation of the upper bound of the glare and recovery of
 *  pixels under this upper bound)
 * @param invalid_distance distance where a pixel is considered invalid
 * @param min_range_threshold_mm the minimum range threshold, for grouping, to be used in the event of very close
 *  targets
 * @param scale_range_threshd_by_range when set, scale the range threshold according to the target range, so that
 *  targets with the same degree of tilt will be grouped together
 * @param range_threshold_factor proportion of the current range to use as a threshold for grouping
 * @param enable_max_range_threshold when set, the maximum range threshold, for grouping. Distance above this threshold
 *  regarding the first element of group is considering to be a new group
 * @param max_range_threshold_mm_6_step the maximum range threshold between first pixel and the current one, for
 *  grouping on 6 step capture
 * @param max_range_threshold_mm_7_step the maximum range threshold between first pixel and the current one, for
 *  grouping on 7 step capture
 * @param enable_distance distance between current pixel and barycenter of the group is taking into account
 * @param enable_gaussian gaussian
 * @param sigma_factor gaussian sigma factor
 * @param distance_power power
 * @param signal_threshold_factor the threshold relative to the maximum signal for  the group, below which signals are
 *  blurred
 * @param threshold_includes_glare when set, the signal threshold is modified by the predicted glare on the zone
 * @param glare_ratio lens glare ratio input based on the edge-spread-function with 50% of the field of
 *  view (FoV) covered
 * @param leak_shift_range_grouping leaky integrator control for the grouping by range
 * @param max_distance max distance
 * @param min_distance_grouping distance of the first group
 * @param th_score_double_sharp threshold used when 2 sharpeners in a row
 * @param refl_aggressor_threshold reflectance threshold used to classify a pixel as an aggressor
 * @param confidence_threshold confidence threshold to select upper bound of the glare for recovering
 * @param reflectance_threshold reflectance threshold to select upper bound of the glare for recovering
 * @param recovery_signal_threshold_factor multiplicative factor applied to the recovery threshold
 *  (e.g. min_signal * factor). Higher values make recovery more conservative (fewer pixels recovered)
 * @param th_peak_dominance_ratio Threshold applied to the ratio between the highest and second-highest signal
 * in a group. If the ratio exceeds this value, the highest signal is considered too dominant and the second-highest
 * signal is used instead for group threshold computation
 */
typedef struct sharpener_params_t {
    sharpener_mode_e mode;
    bool exp_optim;
    bool recover_mode;
    float_t invalid_distance;
    float_t min_range_threshold_mm;
    bool scale_range_threshd_by_range;
    float_t range_threshold_factor;
    bool enable_max_range_threshold;
    float_t max_range_threshold_mm_6_step;
    float_t max_range_threshold_mm_7_step;
    bool enable_distance;
    bool enable_gaussian;
    float_t channel_ratio;
    float_t sigma_factor;
    float_t distance_power;
    float_t signal_threshold_factor;
    bool threshold_includes_glare;
    float_t glare_ratio;
    int32_t leak_shift_range_grouping;
    int32_t nb_lines_overlap;
    float_t max_distance;
    float_t min_distance_grouping;
    float_t th_score_double_sharp;
    float_t refl_aggressor_threshold;
    float_t confidence_threshold;
    float_t reflectance_threshold;
    float_t recovery_signal_threshold_factor;
    float_t th_peak_dominance_ratio;
} sharpener_params_t;

/**
 * @brief init params default values
 *
 * @note Based on Python algo R_1.6.2
 */
void vl53l9_algo_sharpener_init_default_params(sharpener_params_t* params);

/**
 * @brief compute sharpener filter map
 *
 * @note Based on Python algo R_1.6.2
 *
 * @retval EXIT_SUCCESS algo ran successfuly
 * @retval EXIT_FAILURE algo ran into an issue, check errno
 *
 * @param depth input depth
 * @param signal input signal
 * @param reflectance input reflectance
 * @param confidence input confidence
 *
 * @param sharp_valid output sharpener valid flag buffer
 * @param sharp_score output sharpener score buffer
 *
 * @param params sharpener constant parameters
 * @param width image width
 * @param height image height
 * @param step_number number of dToF capture steps
 */
int32_t vl53l9_algo_sharpener(const float_t* depth, const float_t* signal, const float_t* reflectance,
    const float_t* confidence,

    bool* sharp_valid, float_t* sharp_score,

    const sharpener_params_t* params, uint32_t width, uint32_t height, uint32_t step_number);

#ifdef __cplusplus
}
#endif
