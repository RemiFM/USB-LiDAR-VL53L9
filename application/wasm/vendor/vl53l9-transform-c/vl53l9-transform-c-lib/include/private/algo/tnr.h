/**
 ******************************************************************************
 * @file    tnr.h
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
#include <stddef.h>
#include <stdint.h>

#define TNR_MAX_IMAGE_SIZE (54u * 42u)

/**
 * @brief size of the image you can process using a static context
 *
 * @note Based on Python algo R_1.9.1
 *
 * @details define TNR_IMAGE_SIZE before including tnr.h if you want to adapt the static context for smaller or bigger
 * images, TNR_IMAGE_SIZE needs to be equal or higher than the image size you want to process
 */
#ifndef TNR_IMAGE_SIZE
#define TNR_IMAGE_SIZE TNR_MAX_IMAGE_SIZE
#endif

/**
 * @brief tnr module constants and constants computed and/or extracted from OTP
 *
 * @note Based on Python algo R_1.9.1
 *
 * @param float_t invalid_distance when data is not good enough it takes this value
 * @param uint32_t ref_amplitude_ch1_short reference amplitude for channel 1 short
 * @param uint32_t ref_amplitude_ch2_short reference amplitude for channel 2 short
 * @param uint32_t ref_amplitude_ch1_long reference amplitude for channel 1 long
 * @param uint32_t ref_amplitude_ch2_long reference amplitude for channel 2 long
 * @param uint32_t flicker_max_frame max value taken by scores
 * @param float_t th_stat % th above which score is significant
 * @param uint32_t min_diff_score minimum diff between counters
 * @param uint32_t min_diff_counter minimum sum of scores
 * @param uint32_t flag_mode indicates which flag to favor: short, long, none
 * @param float_t std_factor_dist std factor on distance for tnr
 * @param float_t std_factor_amp std factor on amplitude for tnr
 * @param uint32_t max_counter max value for tnr counter
 * @param uint32_t clip_counter max value for noise reduction estimation
 * @param bool amplitude_filter filter amplitude flag
 * @param bool disable_conf_short if true, do not update confidence of short data
 * @param bool disable_flag_condition if true, average together data from short and long steps when they have the same
 * exposure
 * @param bool nrf_approximation use linear approximation for noise reduction factor
 * @param int32_t convergence approximate number of frames needed for convergence
 * @param int32_t tolerance additional frames after maxCounter for which 1/n formula is used
 * @param float_t std_factor_dist std factor on distance for motion
 * @param float_t std_factor_amp std factor on amplitude for motion
 * @param bool spacial_filter flag to filter the motion map
 * @param uint32_t kernel_size kernel size for the spatial filter
 * @param uint32_t th_motion_min number of pixels in kernel necessary to confirm motion
 * @param uint32_t th_motion_max number of pixels in kernel necessary to extend motion
 * @param float_t max_gradient max gradient
 * @param float_t pulse_width pulse width at last step in ns
 * @param float_t window_last_step window size of last step in ns, should be equal for long and short
 * @param float_t window_ambient window size of ambient step in ns
 * @param float_t window_blanking blank timing for ambient window in ns
 */
typedef struct tnr_params_t {
    float_t invalid_distance;
    uint32_t ref_amplitude_ch1_short;
    uint32_t ref_amplitude_ch2_short;
    uint32_t ref_amplitude_ch1_long;
    uint32_t ref_amplitude_ch2_long;
    struct flicker_params_t {
        uint32_t flicker_max_frame;
        float_t th_stat;
        uint32_t min_diff_score;
        uint32_t min_diff_counter;
        uint32_t flag_mode;
    } flicker;
    struct internal_tnr_params_t {
        float_t std_factor_dist;
        float_t std_factor_amp;
        uint32_t max_counter;
        uint32_t clip_counter;
        bool amplitude_filter;
        bool disable_conf_short;
        bool disable_flag_condition;
        bool nrf_approximation;
        uint32_t convergence;
        uint32_t tolerance;
    } tnr;
    struct motion_params_t {
        float_t std_factor_dist;
        float_t std_factor_amp;
        bool spacial_filter;
        uint32_t kernel_size;
        uint32_t th_motion_min;
        uint32_t th_motion_max;
        uint32_t max_gradient;
    } motion;
    struct system_params_t {
        float_t pulse_width;
        float_t window_last_step;
        float_t window_ambient;
        float_t window_blanking;
    } system;
} tnr_params_t;

/**
 * @brief static context structure
 *
 * @note Based on Python algo R_1.9.1
 *
 * @details do not modify instances of this structure yourself
 *
 * @param depth_candidates depth candidates
 * @param amplitude_candidates amplitude candidates
 * @param ambient_candidates ambient candidates
 * @param short_long_candidates main flag candidates
 * @param spads_candidates spads aperture candidates
 * @param score_candidates scores of candidates
 * @param tnr_counters tnr counters of candidates
 * @param previous_candidates previous cadidate is from the current or previous capture
 * @param reset reset flag
 */
typedef struct tnr_context_static_t {
    float_t depth_candidates[2][TNR_IMAGE_SIZE];
    float_t amplitude_candidates[2][TNR_IMAGE_SIZE];
    float_t ambient_candidates[2][TNR_IMAGE_SIZE];
    bool short_long_candidates[2][TNR_IMAGE_SIZE];
    float_t spads_candidates[2][TNR_IMAGE_SIZE];
    signed char score_candidates[2][TNR_IMAGE_SIZE];
    signed char tnr_counters[2][TNR_IMAGE_SIZE];
    bool previous_candidates[TNR_IMAGE_SIZE];
    bool reset;
} tnr_context_static_t;

/**
 * @brief context structure
 *
 * @note Based on Python algo R_1.9.1
 *
 * @details do not modify instances of this structure yourself
 *
 * @param depth_candidates depth candidates
 * @param amplitude_candidates amplitude candidates
 * @param ambient_candidates ambient candidates
 * @param short_long_candidates main flag candidates
 * @param spads_candidates spads aperture candidates
 * @param score_candidates scores of candidates
 * @param tnr_counters tnr counters of candidates
 * @param previous_candidates previous cadidate is from the current or previous capture
 * @param reset reset flag
 */
typedef struct tnr_context_t {
    float_t *depth_candidates[2];
    float_t *amplitude_candidates[2];
    float_t *ambient_candidates[2];
    bool *short_long_candidates[2];
    float_t *spads_candidates[2];
    signed char *score_candidates[2];
    signed char *tnr_counters[2];
    bool *previous_candidates;
    bool reset;
} tnr_context_t;

/**
 * @brief generate context from static context
 *
 * @note Based on Python algo R_1.9.1
 *
 * @param static_context const pointer to a stack allocated context
 *
 * @return tnr_context_t stack allocated context ready to use, check errno for argument errors
 */
tnr_context_t vl53l9_algo_tnr_create_static_context(tnr_context_static_t *static_context);

/**
 * @brief allocate context on heap
 *
 * @note Based on Python algo R_1.9.1
 *
 * @details deallocator is needed when allocation fails midway through the stucture's pointers, then all successfully
 *  allocated memory is freed before returing and errno is set to ENOMEM
 *
 * @param image_size image size in pixels
 * @param allocator memory allocator (malloc for example)
 * @param deallocator memory deallocator (free for malloc allocated memory for example)
 *
 * @return tnr_context_t heap allocated context ready to use, check errno for allocation or arguments errors
 */
tnr_context_t vl53l9_algo_tnr_create_dynamic_context(uint32_t image_size, void *allocator(size_t),
                                                     void deallocator(void *));

/**
 * @brief deallocate memory of heap allocated context
 *
 * @param context context to free
 * @param deallocator deallocator (free for example if memory was allocated by malloc), check errno for argument errors
 */
void vl53l9_algo_tnr_destroy_dynamic_context(tnr_context_t context, void deallocator(void *));

/**
 * @brief init params default values
 *
 * @note Based on Python algo R_1.9.1
 */
void vl53l9_algo_tnr_init_default_params(tnr_params_t *params);

/**
 * @brief compute tnr
 *
 * @note Based on Python algo R_1.9.1
 *
 * @param depth_in input depth
 * @param amplitude_in input amplitude
 * @param ambient_in input ambient
 * @param short_long_in input short long flag
 * @param effective_spads_in input effective spads
 *
 * @param depth_out output depth
 * @param amplitude_out output amplitude
 * @param ambient_out output ambient
 * @param short_long_out output short long flag
 * @param effective_spads_out output effective_spads
 * @param noise_reduction output noise_reduction
 *
 * @param params tnr parameters
 * @param width image width
 * @param height image height
 * @param current_expo_0 current exposure shots 0
 * @param current_expo_1 current exposure shots 1
 * @param current_expo_2 current exposure shots 2
 * @param current_expo_3 current exposure shots 3
 * @param ambient_attenuation ambient attenuation coef
 * @param step_number number of dtof stages
 *
 * @return int32_t EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int32_t vl53l9_algo_tnr(const float_t *depth_in, const float_t *amplitude_in, const float_t *ambient_in,
                        const bool *short_long_in, const float_t *effective_spads_in,

                        float_t *depth_out, float_t *amplitude_out, float_t *ambient_out, bool *short_long_out,
                        float_t *effective_spads_out, float_t *noise_reduction,

                        const tnr_params_t *params, tnr_context_t *context, uint32_t width, uint32_t height,
                        uint32_t current_expo_0, uint32_t current_expo_1, uint32_t current_expo_2,
                        uint32_t current_expo_3, uint32_t ambient_attenuation, uint32_t step_number);

/**
 * @brief reset tnr
 *
 * @note Based on Python algo R_1.9.1
 */
void vl53l9_algo_tnr_reset(tnr_context_t *context);

#ifdef __cplusplus
}
#endif
