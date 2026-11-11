/**
 ******************************************************************************
 * @file    tnr.c
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

#include "algo/tnr.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#ifndef EINVAL
#define EINVAL 22
#endif

#ifndef ENOMEM
#define ENOMEM 12
#endif

#ifndef M_PI
#define M_PI (3.141592f)
#endif
#define SQRT2F (1.41421356237f)

#define LIGHT_SPEED (299792458.0f)

#define CHECK_SQRTF_DOM(val) \
    if ((val) < 0.0f) {      \
        errno = EDOM;        \
        return EXIT_FAILURE; \
    }

#define CHECK_ERRNO(expression) \
    errno = 0;                  \
    (expression);               \
    if ((bool)errno)            \
    return

#define CHECK_ERRNO_FAIL(expression) \
    errno = 0;                       \
    (expression);                    \
    if ((bool)errno)                 \
    return EXIT_FAILURE

#define CHECK_ALLOC(ptr)                                               \
    if (!(bool)ptr) {                                                  \
        errno = ENOMEM;                                                \
        vl53l9_algo_tnr_destroy_dynamic_context(context, deallocator); \
        return context;                                                \
    }

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef uint8_t u8;
typedef uint32_t u32;

typedef float_t f32;

typedef struct internal_params_t {
    f32 duty_cycle;
    f32 frequency;
    f32 scaling_long;
    f32 scaling_short;
    f32 amp_factor;
    f32 depth_factor;
    f32 nr_at_convergence;
    f32 slope;
    f32 intercept;
} internal_params_t;

typedef struct sigmas_t {
    f32 depth;
    f32 amp;
} sigmas_t;

static inline i8 clampi8(i8 val, i8 min, i8 max) {
    return (val < min) ? min : ((val > max) ? max : val);
}

static inline i32 maxi32(i32 a, i32 b) {
    return (a > b) ? a : b;
}
static inline i32 mini32(i32 a, i32 b) {
    return (a < b) ? a : b;
}

static void init_candidates(tnr_context_t *context, const tnr_params_t *eparams, const f32 *depth_in,
                            const f32 *amplitude_in, const f32 *ambient_in, const bool *short_long_in,
                            const f32 *effective_spads_in, u32 size);

static sigmas_t compute_sigma(const tnr_params_t *eparams, const internal_params_t *iparams, f32 amplitude, f32 ambient,
                              bool short_long, u32 pixel_index, u32 size);

static i32 sqrtf_sigma(sigmas_t *sigmas);

static f32 compute_noise_reduction(const tnr_params_t *eparams, const internal_params_t *iparams, i8 tnr_counter);

static void soft_reset(tnr_context_t *context, const tnr_params_t *eparams, f32 depth, f32 amplitude, f32 ambient,
                       bool short_long, f32 effective_spads, u32 i);

static void merge_candidate(tnr_context_t *context, const tnr_params_t *eparams, u32 i);

static void spatial_filter(const tnr_params_t *eparams, const bool *motion_map, const f32 *depth, u32 width, u32 height,
                           bool *filtered_motion_map);

static void hard_reset(tnr_context_t *context, const tnr_params_t *eparams, f32 depth, f32 amplitude, f32 ambient,
                       bool short_long, f32 effective_spads, u32 i);

static bool choose_candidate(tnr_context_t *context, const tnr_params_t *eparams, u32 i);

void vl53l9_algo_tnr_init_default_params(tnr_params_t *params) {
    params->invalid_distance = 12000.0f;
    params->ref_amplitude_ch1_short = 0;
    params->ref_amplitude_ch2_short = 0;
    params->ref_amplitude_ch1_long = 0;
    params->ref_amplitude_ch2_long = 0;
    params->flicker.flicker_max_frame = 8;
    params->flicker.th_stat = 0.6f;
    params->flicker.min_diff_score = 6;
    params->flicker.min_diff_counter = 6;
    params->flicker.flag_mode = 2;
    params->tnr.std_factor_dist = 3.5f;
    params->tnr.std_factor_amp = 3.5f;
    params->tnr.max_counter = 16;
    params->tnr.clip_counter = 60;
    params->tnr.amplitude_filter = true;
    params->tnr.disable_conf_short = true;
    params->tnr.disable_flag_condition = true;
    params->tnr.nrf_approximation = false;
    params->tnr.convergence = 42u;
    params->tnr.tolerance = 9u;
    params->motion.std_factor_dist = 3.5f;
    params->motion.std_factor_amp = 10.0f;
    params->motion.spacial_filter = true;
    params->motion.kernel_size = 3;
    params->motion.th_motion_min = 3;
    params->motion.th_motion_max = 6;
    params->motion.max_gradient = 100u;
    params->system.pulse_width = 1.3f;
    params->system.window_last_step = 4.0f;
    params->system.window_ambient = 64.0f;
    params->system.window_blanking = 0.0f;
}

tnr_context_t vl53l9_algo_tnr_create_static_context(tnr_context_static_t *static_context) {
    tnr_context_t context = { 0 };

    if (!(bool)static_context) {
        errno = EINVAL;
        return context;
    }

    context.depth_candidates[0] = static_context->depth_candidates[0];
    context.depth_candidates[1] = static_context->depth_candidates[1];
    context.amplitude_candidates[0] = static_context->amplitude_candidates[0];
    context.amplitude_candidates[1] = static_context->amplitude_candidates[1];
    context.ambient_candidates[0] = static_context->ambient_candidates[0];
    context.ambient_candidates[1] = static_context->ambient_candidates[1];
    context.short_long_candidates[0] = static_context->short_long_candidates[0];
    context.short_long_candidates[1] = static_context->short_long_candidates[1];
    context.spads_candidates[0] = static_context->spads_candidates[0];
    context.spads_candidates[1] = static_context->spads_candidates[1];
    context.score_candidates[0] = static_context->score_candidates[0];
    context.score_candidates[1] = static_context->score_candidates[1];
    context.tnr_counters[0] = static_context->tnr_counters[0];
    context.tnr_counters[1] = static_context->tnr_counters[1];
    context.previous_candidates = static_context->previous_candidates;

    context.reset = true;

    return context;
}

tnr_context_t vl53l9_algo_tnr_create_dynamic_context(u32 image_size, void *allocator(size_t),
                                                     void deallocator(void *)) {
    tnr_context_t context = { 0 };

    if ((allocator == NULL) || (deallocator == NULL) || !(bool)image_size) {
        errno = EINVAL;
        return context;
    }

    context.depth_candidates[0] = (f32 *)allocator(image_size * sizeof(f32));
    CHECK_ALLOC(context.depth_candidates[0]);
    context.depth_candidates[1] = (f32 *)allocator(image_size * sizeof(f32));
    CHECK_ALLOC(context.depth_candidates[1]);
    context.amplitude_candidates[0] = (f32 *)allocator(image_size * sizeof(f32));
    CHECK_ALLOC(context.amplitude_candidates[0]);
    context.amplitude_candidates[1] = (f32 *)allocator(image_size * sizeof(f32));
    CHECK_ALLOC(context.amplitude_candidates[1]);
    context.ambient_candidates[0] = (f32 *)allocator(image_size * sizeof(f32));
    CHECK_ALLOC(context.ambient_candidates[0]);
    context.ambient_candidates[1] = (f32 *)allocator(image_size * sizeof(f32));
    CHECK_ALLOC(context.ambient_candidates[1]);
    context.short_long_candidates[0] = (bool *)allocator(image_size * sizeof(bool));
    CHECK_ALLOC(context.short_long_candidates[0]);
    context.short_long_candidates[1] = (bool *)allocator(image_size * sizeof(bool));
    CHECK_ALLOC(context.short_long_candidates[1]);
    context.spads_candidates[0] = (f32 *)allocator(image_size * sizeof(f32));
    CHECK_ALLOC(context.spads_candidates[0]);
    context.spads_candidates[1] = (f32 *)allocator(image_size * sizeof(f32));
    CHECK_ALLOC(context.spads_candidates[1]);
    context.score_candidates[0] = (signed char *)allocator(image_size * sizeof(signed char));
    CHECK_ALLOC(context.score_candidates[0]);
    context.score_candidates[1] = (signed char *)allocator(image_size * sizeof(signed char));
    CHECK_ALLOC(context.score_candidates[1]);
    context.tnr_counters[0] = (signed char *)allocator(image_size * sizeof(signed char));
    CHECK_ALLOC(context.tnr_counters[0]);
    context.tnr_counters[1] = (signed char *)allocator(image_size * sizeof(signed char));
    CHECK_ALLOC(context.tnr_counters[1]);
    context.previous_candidates = (bool *)allocator(image_size * sizeof(bool));
    CHECK_ALLOC(context.previous_candidates);

    context.reset = true;

    return context;
}

void vl53l9_algo_tnr_destroy_dynamic_context(tnr_context_t context, void deallocator(void *)) {
    if (deallocator == NULL) {
        errno = EINVAL;
        return;
    }

    if ((bool)context.depth_candidates[0]) {
        deallocator(context.depth_candidates[0]);
    }
    if ((bool)context.depth_candidates[1]) {
        deallocator(context.depth_candidates[1]);
    }
    if ((bool)context.amplitude_candidates[0]) {
        deallocator(context.amplitude_candidates[0]);
    }
    if ((bool)context.amplitude_candidates[1]) {
        deallocator(context.amplitude_candidates[1]);
    }
    if ((bool)context.ambient_candidates[0]) {
        deallocator(context.ambient_candidates[0]);
    }
    if ((bool)context.ambient_candidates[1]) {
        deallocator(context.ambient_candidates[1]);
    }
    if ((bool)context.short_long_candidates[0]) {
        deallocator(context.short_long_candidates[0]);
    }
    if ((bool)context.short_long_candidates[1]) {
        deallocator(context.short_long_candidates[1]);
    }
    if ((bool)context.spads_candidates[0]) {
        deallocator(context.spads_candidates[0]);
    }
    if ((bool)context.spads_candidates[1]) {
        deallocator(context.spads_candidates[1]);
    }
    if ((bool)context.score_candidates[0]) {
        deallocator(context.score_candidates[0]);
    }
    if ((bool)context.score_candidates[1]) {
        deallocator(context.score_candidates[1]);
    }
    if ((bool)context.tnr_counters[0]) {
        deallocator(context.tnr_counters[0]);
    }
    if ((bool)context.tnr_counters[1]) {
        deallocator(context.tnr_counters[1]);
    }
    if ((bool)context.previous_candidates) {
        deallocator(context.previous_candidates);
    }
}

i32 vl53l9_algo_tnr(const f32 *depth_in, const f32 *amplitude_in, const f32 *ambient_in, const bool *short_long_in,
                    const f32 *effective_spads_in,

                    f32 *depth_out, f32 *amplitude_out, f32 *ambient_out, bool *short_long_out,
                    f32 *effective_spads_out, f32 *noise_reduction,

                    const tnr_params_t *params, tnr_context_t *context, u32 width, u32 height, u32 current_expo_0,
                    u32 current_expo_1, u32 current_expo_2, u32 current_expo_3, u32 ambient_attenuation,
                    u32 step_number) {
    // if one of the input is missing, return
    // if all outputs are missing, return
    if (!(bool)depth_in || !(bool)amplitude_in || !(bool)ambient_in || !(bool)short_long_in ||
        !(bool)effective_spads_in ||
        !((bool)depth_out || (bool)amplitude_out || (bool)ambient_out || (bool)short_long_out ||
          (bool)effective_spads_out || (bool)noise_reduction)) {
        errno = EINVAL;
        return EXIT_FAILURE;
    }

    const f32 window_last_step = (step_number == 6u) ? 8.0f : 4.0f;
    const f32 pulse_width = (step_number == 6u) ? 2.6f : 1.3f;
    const u32 ambient_attenuation_val = ((u32)1u << ambient_attenuation);

    // create alias for clarity
    const tnr_params_t *eparams = params;
    tnr_context_t *ictx = context;

    internal_params_t iparams;
    iparams.duty_cycle = pulse_width / window_last_step;
    iparams.frequency = 1.0e9f / window_last_step;
    iparams.scaling_long = (f32)ambient_attenuation_val * (f32)current_expo_1 * window_last_step /
                           ((f32)current_expo_3 * (eparams->system.window_ambient + eparams->system.window_blanking));
    iparams.scaling_short = (f32)ambient_attenuation_val * (f32)current_expo_2 * window_last_step /
                            ((f32)current_expo_3 * (eparams->system.window_ambient + eparams->system.window_blanking));
    CHECK_ERRNO_FAIL(iparams.amp_factor =
                         iparams.duty_cycle * M_PI * M_PI / (2.0f * SQRT2F * sinf(M_PI * iparams.duty_cycle)));
    iparams.depth_factor = (1e3f * LIGHT_SPEED / (4.0f * M_PI * iparams.frequency)) *
                           (1e3f * LIGHT_SPEED / (4.0f * M_PI * iparams.frequency));
    iparams.nr_at_convergence = 1.0f / ((2.0f * (f32)eparams->tnr.max_counter) - 1.0f);
    iparams.slope =
        (iparams.nr_at_convergence - (1.0f / ((f32)eparams->tnr.max_counter + (f32)eparams->tnr.tolerance))) /
        ((f32)eparams->tnr.convergence - (f32)eparams->tnr.max_counter + (f32)eparams->tnr.tolerance);
    iparams.intercept = (1.0f / ((f32)eparams->tnr.max_counter + (f32)eparams->tnr.tolerance)) -
                        (iparams.slope * ((f32)eparams->tnr.max_counter + (f32)eparams->tnr.tolerance));

    const u32 size = width * height;

    if (ictx->reset) {
        init_candidates(ictx, eparams, depth_in, amplitude_in, ambient_in, short_long_in, effective_spads_in, size);

        if (depth_out) {
            memcpy(depth_out, depth_in, size * sizeof(*depth_in));
        }
        if (amplitude_out) {
            memcpy(amplitude_out, amplitude_in, size * sizeof(*amplitude_in));
        }
        if (short_long_out) {
            memcpy(short_long_out, short_long_in, size * sizeof(*short_long_in));
        }
        if (ambient_out) {
            memcpy(ambient_out, ambient_in, size * sizeof(*ambient_in));
        }
        if (effective_spads_out) {
            memcpy(effective_spads_out, effective_spads_in, size * sizeof(*effective_spads_in));
        }
        if (noise_reduction) {
            for (u32 i = 0; i < size; ++i) {
                noise_reduction[i] = compute_noise_reduction(eparams, &iparams, 1);
            }
        }

        memset(ictx->previous_candidates, 0, size * sizeof(*ictx->previous_candidates));

        ictx->reset = false;

        return EXIT_SUCCESS;
    }

    bool motion_map[TNR_IMAGE_SIZE] = { false };
    for (u32 i = 0; i < size; ++i) {
        const f32 previous_amp_norm = ictx->amplitude_candidates[(u32)ictx->previous_candidates[i]][i] /
                                      ictx->spads_candidates[(u32)ictx->previous_candidates[i]][i];
        const f32 previous_depth = ictx->depth_candidates[(u32)ictx->previous_candidates[i]][i];

        const bool empty_candidates[] = { ictx->depth_candidates[0][i] == eparams->invalid_distance,
                                          ictx->depth_candidates[1][i] == eparams->invalid_distance };

        // compute sigmas for each candidate
        sigmas_t sigmas[2];
        sigmas[0] = compute_sigma(eparams, &iparams, ictx->amplitude_candidates[0][i], ictx->ambient_candidates[0][i],
                                  ictx->short_long_candidates[0][i], i, size);
        sigmas[1] = compute_sigma(eparams, &iparams, ictx->amplitude_candidates[1][i], ictx->ambient_candidates[1][i],
                                  ictx->short_long_candidates[1][i], i, size);

        const f32 depth_diffs[] = { fabsf(ictx->depth_candidates[0][i] - depth_in[i]),
                                    fabsf(ictx->depth_candidates[1][i] - depth_in[i]) };

        const f32 short_long_diffs[] = { (eparams->tnr.disable_flag_condition && (current_expo_1 == current_expo_2))
                                             ? 0.0f
                                             : ((f32)ictx->short_long_candidates[0][i] - (f32)short_long_in[i]),
                                         (eparams->tnr.disable_flag_condition && (current_expo_1 == current_expo_2))
                                             ? 0.0f
                                             : ((f32)ictx->short_long_candidates[1][i] - (f32)short_long_in[i]) };

        const f32 spads_diffs[] = { ictx->spads_candidates[0][i] - effective_spads_in[i],
                                    ictx->spads_candidates[1][i] - effective_spads_in[i] };

        const f32 amp_diffs[] = { fabsf(ictx->amplitude_candidates[0][i] - amplitude_in[i]),
                                  fabsf(ictx->amplitude_candidates[1][i] - amplitude_in[i]) };

        f32 noise_reduction_factors[2];
        CHECK_ERRNO_FAIL(noise_reduction_factors[0] =
                             compute_noise_reduction(eparams, &iparams, ictx->tnr_counters[0][i]) + 1.0f);
        CHECK_ERRNO_FAIL(noise_reduction_factors[1] =
                             compute_noise_reduction(eparams, &iparams, ictx->tnr_counters[1][i]) + 1.0f);

        sigmas_t sigmas_nr[2] = { { .depth = sigmas[0].depth * noise_reduction_factors[0],
                                    .amp = sigmas[0].amp * noise_reduction_factors[0] },
                                  { .depth = sigmas[1].depth * noise_reduction_factors[1],
                                    .amp = sigmas[1].amp * noise_reduction_factors[1] } };

        CHECK_ERRNO_FAIL(sqrtf_sigma(&sigmas_nr[0]));
        CHECK_ERRNO_FAIL(sqrtf_sigma(&sigmas_nr[1]));

        const bool conds_depth[] = {
            depth_diffs[0] <= (eparams->tnr.std_factor_dist * sigmas_nr[0].depth),
            depth_diffs[1] <= (eparams->tnr.std_factor_dist * sigmas_nr[1].depth),
        };

        const bool conds_short_long[] = { !(bool)short_long_diffs[0], !(bool)short_long_diffs[1] };

        const bool conds_spads[] = { !(bool)spads_diffs[0], !(bool)spads_diffs[1] };

        const bool conds_amplitude[] = { amp_diffs[0] < (eparams->tnr.std_factor_amp * sigmas_nr[0].amp),
                                         amp_diffs[1] < (eparams->tnr.std_factor_amp * sigmas_nr[1].amp) };

        const bool choosing_conds[] = { conds_depth[0] && conds_short_long[0] && conds_spads[0] && conds_amplitude[0],
                                        conds_depth[1] && conds_short_long[1] && conds_spads[1] && conds_amplitude[1] };

        bool chosen_candidate[] = { false, false };
        if (!empty_candidates[0]) {
            chosen_candidate[0] = choosing_conds[0];
        }
        if (!empty_candidates[1]) {
            chosen_candidate[1] = choosing_conds[1];
        }
        if (empty_candidates[0] && !chosen_candidate[0]) {
            chosen_candidate[0] = true;
        }
        if (empty_candidates[1] && !chosen_candidate[0]) {
            chosen_candidate[1] = true;
        }

        // tnr
        if (chosen_candidate[0] && !empty_candidates[0]) {
            ++ictx->tnr_counters[0][i];
        }
        if (chosen_candidate[1] && !empty_candidates[1]) {
            ++ictx->tnr_counters[1][i];
        }
        if (chosen_candidate[0] && empty_candidates[0]) {
            ictx->tnr_counters[0][i] = 1;
        }
        if (chosen_candidate[1] && empty_candidates[1]) {
            ictx->tnr_counters[1][i] = 1;
        }
        if (ictx->tnr_counters[0][i] > (i8)eparams->tnr.clip_counter) {
            ictx->tnr_counters[0][i] = (i8)eparams->tnr.clip_counter;
        }
        if (ictx->tnr_counters[1][i] > (i8)eparams->tnr.clip_counter) {
            ictx->tnr_counters[1][i] = (i8)eparams->tnr.clip_counter;
        }

        const f32 alpha[] = { 1.0f / (f32)clampi8(ictx->tnr_counters[0][i], (i8)1, (i8)eparams->tnr.max_counter),
                              1.0f / (f32)clampi8(ictx->tnr_counters[1][i], (i8)1, (i8)eparams->tnr.max_counter) };

        if (chosen_candidate[0] && !empty_candidates[0]) {
            ictx->depth_candidates[0][i] =
                (depth_in[i] * alpha[0]) + (ictx->depth_candidates[0][i] * (1.0f - alpha[0]));
        }
        if (chosen_candidate[1] && !empty_candidates[1]) {
            ictx->depth_candidates[1][i] =
                (depth_in[i] * alpha[1]) + (ictx->depth_candidates[1][i] * (1.0f - alpha[1]));
        }
        if (chosen_candidate[0] && empty_candidates[0]) {
            ictx->depth_candidates[0][i] = depth_in[i];
        }
        if (chosen_candidate[1] && empty_candidates[1]) {
            ictx->depth_candidates[1][i] = depth_in[i];
        }
        if (eparams->tnr.amplitude_filter) {
            if (chosen_candidate[0] && !empty_candidates[0]) {
                ictx->amplitude_candidates[0][i] =
                    (amplitude_in[i] * alpha[0]) + (ictx->amplitude_candidates[0][i] * (1.0f - alpha[0]));
            }
            if (chosen_candidate[1] && !empty_candidates[1]) {
                ictx->amplitude_candidates[1][i] =
                    (amplitude_in[i] * alpha[1]) + (ictx->amplitude_candidates[1][i] * (1.0f - alpha[1]));
            }
            if (chosen_candidate[0] && empty_candidates[0]) {
                ictx->amplitude_candidates[0][i] = amplitude_in[i];
            }
            if (chosen_candidate[1] && empty_candidates[1]) {
                ictx->amplitude_candidates[1][i] = amplitude_in[i];
            }
        } else {
            if (chosen_candidate[0]) {
                ictx->amplitude_candidates[0][i] = amplitude_in[i];
            }
            if (chosen_candidate[1]) {
                ictx->amplitude_candidates[1][i] = amplitude_in[i];
            }
        }
        if (chosen_candidate[0]) {
            ictx->ambient_candidates[0][i] = ambient_in[i];
            ictx->short_long_candidates[0][i] = short_long_in[i];
            ictx->spads_candidates[0][i] = effective_spads_in[i];
        }
        if (chosen_candidate[1]) {
            ictx->ambient_candidates[1][i] = ambient_in[i];
            ictx->short_long_candidates[1][i] = short_long_in[i];
            ictx->spads_candidates[1][i] = effective_spads_in[i];
        }

        // update flicker score
        const bool no_chosen_candidate = !(chosen_candidate[0] || chosen_candidate[1]);
        if (chosen_candidate[0]) {
            ++ictx->score_candidates[0][i];
        }
        if (chosen_candidate[1]) {
            ++ictx->score_candidates[1][i];
        }
        if (!chosen_candidate[0] && !no_chosen_candidate) {
            --ictx->score_candidates[0][i];
        }
        if (!chosen_candidate[1] && !no_chosen_candidate) {
            --ictx->score_candidates[1][i];
        }
        ictx->score_candidates[0][i] =
            clampi8(ictx->score_candidates[0][i], (i8)0, (i8)eparams->flicker.flicker_max_frame);
        ictx->score_candidates[1][i] =
            clampi8(ictx->score_candidates[1][i], (i8)0, (i8)eparams->flicker.flicker_max_frame);

        // reset if no chosen cancdidate
        if (no_chosen_candidate) {
            soft_reset(ictx, eparams, depth_in[i], amplitude_in[i], ambient_in[i], short_long_in[i],
                       effective_spads_in[i], i);
        }

        // merge if two chosen candidate
        if (chosen_candidate[0] && chosen_candidate[1]) {
            merge_candidate(ictx, eparams, i);
        }

        // reset if motion
        sigmas_t previous_sigmas = sigmas[(u32)ictx->previous_candidates[i]];
        CHECK_ERRNO_FAIL(sqrtf_sigma(&previous_sigmas));
        const f32 previous_spads = ictx->spads_candidates[(u32)ictx->previous_candidates[i]][i];
        const f32 diff_range = fabsf(previous_depth - depth_in[i]);
        const f32 diff_amp = fabsf(previous_amp_norm - (amplitude_in[i] / effective_spads_in[i]));
        previous_sigmas.amp /= previous_spads;

        motion_map[i] = ((diff_range > (eparams->motion.std_factor_dist * previous_sigmas.depth * SQRT2F)) ||
                         (diff_amp > (eparams->motion.std_factor_amp * previous_sigmas.amp * SQRT2F)));
    }

    bool filtered_motion_map[TNR_IMAGE_SIZE] = { false };
    if (eparams->motion.spacial_filter) {
        CHECK_ERRNO_FAIL(spatial_filter(eparams, motion_map, depth_in, width, height, filtered_motion_map));
    }

    const bool *motion_map_tmp = eparams->motion.spacial_filter ? filtered_motion_map : motion_map;
    for (u32 i = 0; i < size; ++i) {
        if (motion_map_tmp[i]) {
            hard_reset(ictx, eparams, depth_in[i], amplitude_in[i], ambient_in[i], short_long_in[i],
                       effective_spads_in[i], i);
        }
        const bool is_candidate_0 = choose_candidate(ictx, eparams, i);

        if (depth_out) {
            depth_out[i] = is_candidate_0 ? ictx->depth_candidates[0][i] : ictx->depth_candidates[1][i];
        }
        if (amplitude_out) {
            amplitude_out[i] = is_candidate_0 ? ictx->amplitude_candidates[0][i] : ictx->amplitude_candidates[1][i];
        }
        if (ambient_out) {
            ambient_out[i] = is_candidate_0 ? ictx->ambient_candidates[0][i] : ictx->ambient_candidates[1][i];
        }
        if (short_long_out) {
            short_long_out[i] = is_candidate_0 ? ictx->short_long_candidates[0][i] : ictx->short_long_candidates[1][i];
        }
        if (effective_spads_out) {
            effective_spads_out[i] = is_candidate_0 ? ictx->spads_candidates[0][i] : ictx->spads_candidates[1][i];
        }

        if (noise_reduction) {
            i8 counter = is_candidate_0 ? ictx->tnr_counters[0][i] : ictx->tnr_counters[1][i];
            f32 noise_red = compute_noise_reduction(eparams, &iparams, counter);
            CHECK_SQRTF_DOM(noise_red);
            CHECK_ERRNO_FAIL(noise_reduction[i] = sqrtf(noise_red));
            if (eparams->tnr.disable_conf_short && !short_long_out[i]) {
                noise_reduction[i] = 1.0f;
            }
        }

        // store current data for next image processing
        ictx->previous_candidates[i] = !is_candidate_0;
    }

    return EXIT_SUCCESS;
}

void vl53l9_algo_tnr_reset(tnr_context_t *context) {
    context->reset = true;
}

void init_candidates(tnr_context_t *context, const tnr_params_t *eparams, const f32 *depth_in, const f32 *amplitude_in,
                     const f32 *ambient_in, const bool *short_long_in, const f32 *effective_spads_in, u32 size) {
    for (u32 i = 0; i < size; ++i) {
        context->depth_candidates[0][i] = depth_in[i];
        context->amplitude_candidates[0][i] = amplitude_in[i];
        context->ambient_candidates[0][i] = ambient_in[i];
        context->short_long_candidates[0][i] = short_long_in[i];
        context->spads_candidates[0][i] = effective_spads_in[i];
        context->score_candidates[0][i] = 1;
        context->tnr_counters[0][i] = 1;

        context->depth_candidates[1][i] = eparams->invalid_distance;
        context->amplitude_candidates[1][i] = 0.0f;
        context->ambient_candidates[1][i] = 0.0f;
        context->short_long_candidates[1][i] = false;
        context->spads_candidates[1][i] = 0.0f;
        context->score_candidates[1][i] = 0;
        context->tnr_counters[1][i] = 0;
    }
}

sigmas_t compute_sigma(const tnr_params_t *eparams, const internal_params_t *iparams, f32 amplitude, f32 ambient,
                       bool short_long, u32 pixel_index, u32 size) {
    const bool is_short = !short_long;
    const bool is_ch1 = (2u * pixel_index / size) == 0u;

    const f32 amp_norm = amplitude * iparams->amp_factor;
    const f32 amb_norm = ambient * (is_short ? iparams->scaling_short : iparams->scaling_long);
    const f32 photon_count = amp_norm + amb_norm;
    const u32 amp_ref = is_short ? is_ch1 ? eparams->ref_amplitude_ch1_short : eparams->ref_amplitude_ch2_short
                        : is_ch1 ? eparams->ref_amplitude_ch1_long
                                 : eparams->ref_amplitude_ch2_long;
    const f32 photon_count_ref = (f32)amp_ref * iparams->amp_factor;

    const bool is_div0 = (amplitude + ambient) == 0.0f;

    const f32 two_amp_sq = 2.0f * amplitude * amplitude;
    const f32 two_amp_ref_sq = 2.0f * (f32)amp_ref * (f32)amp_ref;
    const f32 d_fac = iparams->depth_factor;
    const sigmas_t res = { .depth = is_div0
                                        ? 0.0f
                                        : (d_fac * ((photon_count / two_amp_sq) + (photon_count_ref / two_amp_ref_sq))),
                           .amp = is_div0 ? 0.0f : (0.5f * photon_count * (1.0f + (photon_count / two_amp_sq))) };

    return res;
}

static i32 sqrtf_sigma(sigmas_t *sigmas) {
    CHECK_SQRTF_DOM(sigmas->depth); // MISRAC2012-Dir-4.11_b
    CHECK_ERRNO_FAIL(sigmas->depth = sqrtf(sigmas->depth));
    CHECK_SQRTF_DOM(sigmas->amp); // MISRAC2012-Dir-4.11_b
    CHECK_ERRNO_FAIL(sigmas->amp = sqrtf(sigmas->amp));

    return EXIT_SUCCESS;
}

f32 compute_noise_reduction(const tnr_params_t *eparams, const internal_params_t *iparams, i8 tnr_counter) {
    const i8 max_counter = (i8)eparams->tnr.max_counter;

    f32 nrf = 1.0f;
    if (eparams->tnr.nrf_approximation) {
        const bool inv_regime =
            (tnr_counter <= ((i8)eparams->tnr.max_counter + (i8)eparams->tnr.tolerance)) && (tnr_counter > (i8)0);
        const bool linear_regime = (tnr_counter > ((i8)eparams->tnr.max_counter + (i8)eparams->tnr.tolerance)) &&
                                   (tnr_counter < (i8)eparams->tnr.convergence);
        const bool cst_regime = tnr_counter >= (i8)eparams->tnr.convergence;

        if (inv_regime) {
            nrf = 1.0f / (f32)tnr_counter;
        }
        if (linear_regime) {
            nrf = iparams->intercept + (iparams->slope * (f32)tnr_counter);
        }
        if (cst_regime) {
            nrf = iparams->nr_at_convergence;
        }
    } else {
        if ((tnr_counter <= max_counter) && (tnr_counter > (i8)0)) {
            nrf = 1.0f / (f32)tnr_counter;
        } else if (tnr_counter > max_counter) {
            errno = 0;
            nrf =
                (1.0f + powf(1.0f - (1.0f / (f32)max_counter), 1.0f + (2.0f * ((f32)tnr_counter - (f32)max_counter)))) /
                ((2.0f * (f32)max_counter) - 1.0f);
        }
    }

    return nrf;
}

void soft_reset(tnr_context_t *context, const tnr_params_t *eparams, f32 depth, f32 amplitude, f32 ambient,
                bool short_long, f32 effective_spads, u32 i) {
    // replace lower counter
    bool lowest_counter = context->tnr_counters[0][i] < context->tnr_counters[1][i];

    const i16 tnr_diff = (i16)context->tnr_counters[0][i] - (i16)context->tnr_counters[1][i]; // MISRAC2012-Dir-4.11_i

    // if counters are close and candidates have different SPADs, replace lowest SPAD
    const bool low_diff = (abs(tnr_diff) <= (i32)eparams->flicker.min_diff_counter) &&
                          (context->spads_candidates[0][i] != context->spads_candidates[1][i]);
    if (low_diff) {
        lowest_counter = context->spads_candidates[0][i] < context->spads_candidates[1][i];
    }

    // if counters are low and candidates have same SPADs, replace with long or short depending on which has the
    // highest exposure
    const bool low_diff_same_spad = (abs(tnr_diff) <= (i32)eparams->flicker.min_diff_counter) &&
                                    (context->spads_candidates[0][i] == context->spads_candidates[1][i]);
    if (eparams->flicker.flag_mode == 1u) {
        lowest_counter =
            (u8)context->short_long_candidates[0][i] < (u8)context->short_long_candidates[1][i]; // keep long
    }
    if (eparams->flicker.flag_mode == 0u) {
        lowest_counter =
            (u8)context->short_long_candidates[0][i] > (u8)context->short_long_candidates[1][i]; // keep short
    }

    // if short long are the same, fall back on lowest counter condition
    const bool low_diff_same_spad_same_flag =
        ((eparams->flicker.flag_mode == 2u) ? low_diff_same_spad : low_diff_same_spad) &&
        (context->short_long_candidates[0][i] == context->short_long_candidates[1][i]);
    if (low_diff_same_spad_same_flag) {
        lowest_counter = context->tnr_counters[0][i] < context->tnr_counters[1][i];
    }

    if (!lowest_counter) {
        context->score_candidates[0][i] =
            clampi8(--context->score_candidates[0][i], (i8)0, (i8)eparams->flicker.flicker_max_frame);
    }
    if (lowest_counter) {
        context->score_candidates[1][i] =
            clampi8(--context->score_candidates[1][i], (i8)0, (i8)eparams->flicker.flicker_max_frame);
    }

    if (lowest_counter) {
        context->depth_candidates[0][i] = depth;
        context->amplitude_candidates[0][i] = amplitude;
        context->ambient_candidates[0][i] = ambient;
        context->short_long_candidates[0][i] = short_long;
        context->spads_candidates[0][i] = effective_spads;
        context->score_candidates[0][i] = 1;
        context->tnr_counters[0][i] = 1;
    }
    if (!lowest_counter) {
        context->depth_candidates[1][i] = depth;
        context->amplitude_candidates[1][i] = amplitude;
        context->ambient_candidates[1][i] = ambient;
        context->short_long_candidates[1][i] = short_long;
        context->spads_candidates[1][i] = effective_spads;
        context->score_candidates[1][i] = 1;
        context->tnr_counters[1][i] = 1;
    }
}

void merge_candidate(tnr_context_t *context, const tnr_params_t *eparams, u32 i) {
    context->depth_candidates[0][i] = ((context->depth_candidates[0][i] * (f32)context->tnr_counters[0][i]) +
                                       (context->depth_candidates[1][i] * (f32)context->tnr_counters[1][i])) /
                                      ((f32)context->tnr_counters[0][i] + (f32)context->tnr_counters[1][i]);
    context->amplitude_candidates[0][i] = ((context->amplitude_candidates[0][i] * (f32)context->tnr_counters[0][i]) +
                                           (context->amplitude_candidates[1][i] * (f32)context->tnr_counters[1][i])) /
                                          ((f32)context->tnr_counters[0][i] + (f32)context->tnr_counters[1][i]);
    context->score_candidates[0][i] = clampi8(context->score_candidates[0][i] + context->score_candidates[1][i], (i8)0,
                                              (i8)eparams->flicker.flicker_max_frame);
    context->tnr_counters[0][i] = clampi8(context->tnr_counters[0][i] + context->tnr_counters[1][i] - (i8)2, (i8)1,
                                          (i8)eparams->tnr.clip_counter);

    context->depth_candidates[1][i] = eparams->invalid_distance;
    context->amplitude_candidates[1][i] = 0.0f;
    context->ambient_candidates[1][i] = 0.0f;
    context->short_long_candidates[1][i] = false;
    context->spads_candidates[1][i] = 0.0f;
    context->score_candidates[1][i] = 0;
    context->tnr_counters[1][i] = 1;
}

void spatial_filter(const tnr_params_t *eparams, const bool *motion_map, const f32 *depth, u32 width, u32 height,
                    bool *filtered_motion_map) {
    const f32 kernel_half_size = (f32)eparams->motion.kernel_size / 2.0f;
    const i32 kernel_half_size_i = (i32)kernel_half_size;
    for (i32 line = 0; line < (i32)height; ++line) {
        for (i32 col = 0; col < (i32)width; ++col) {
            const u32 id = ((u32)line * (u32)width) + (u32)col;
            const u32 k_line_start = (u32)maxi32(0, line - kernel_half_size_i);
            const u32 k_line_end = (u32)mini32((i32)height, line + kernel_half_size_i + 1);
            const u32 k_col_start = (u32)maxi32(0, col - kernel_half_size_i);
            const u32 k_col_end = (u32)mini32((i32)width, col + kernel_half_size_i + 1);

            u32 ksum = 0;
            u32 gradient_count = 0;
            for (u32 kline = k_line_start; kline < k_line_end; ++kline) {
                for (u32 kcol = k_col_start; kcol < k_col_end; ++kcol) {
                    const u32 kid = (kline * width) + kcol;
                    const bool motion = motion_map[kid];
                    bool diff_center_below_grad = false;
                    CHECK_ERRNO(diff_center_below_grad =
                                    fabsf(depth[kid] - depth[id]) < (f32)eparams->motion.max_gradient);

                    ksum += (u32)motion;
                    if (motion) {
                        gradient_count += (u32)diff_center_below_grad;
                    }
                }
            }

            filtered_motion_map[id] = true;
            if ((ksum > eparams->motion.th_motion_min) && motion_map[id]) {
                if (gradient_count <= eparams->motion.th_motion_min) {
                    filtered_motion_map[id] = false;
                }
            } else if ((ksum > eparams->motion.th_motion_max) && !motion_map[id]) {
                if (gradient_count <= eparams->motion.th_motion_max) {
                    filtered_motion_map[id] = false;
                }
            } else {
                filtered_motion_map[id] = false;
            }
        }
    }
}

void hard_reset(tnr_context_t *context, const tnr_params_t *eparams, f32 depth, f32 amplitude, f32 ambient,
                bool short_long, f32 effective_spads, u32 i) {
    context->depth_candidates[0][i] = depth;
    context->amplitude_candidates[0][i] = amplitude;
    context->ambient_candidates[0][i] = ambient;
    context->short_long_candidates[0][i] = short_long;
    context->spads_candidates[0][i] = effective_spads;
    context->score_candidates[0][i] = 1;
    context->tnr_counters[0][i] = 1;

    context->depth_candidates[1][i] = eparams->invalid_distance;
    context->amplitude_candidates[1][i] = 0.0f;
    context->ambient_candidates[1][i] = 0.0f;
    context->short_long_candidates[1][i] = false;
    context->spads_candidates[1][i] = 0.0f;
    context->score_candidates[1][i] = 0;
    context->tnr_counters[1][i] = 0;
}

bool choose_candidate(tnr_context_t *context, const tnr_params_t *eparams, u32 i) {
    const bool empty_candidate_1 = context->depth_candidates[1][i] == eparams->invalid_distance;

    // if 2nd candidate is empty choose first one
    bool is_candidate_0 = empty_candidate_1;

    const i16 sum_score = (i16)context->score_candidates[0][i] + (i16)context->score_candidates[1][i];
    const f32 stat[] = { (sum_score > 0) ? ((f32)context->score_candidates[0][i] / (f32)sum_score) : 0.5f,
                         (sum_score > 0) ? ((f32)context->score_candidates[1][i] / (f32)sum_score) : 0.5f };

    // check if stats give a clear majority candidate
    const i16 score_diff =
        (i16)context->score_candidates[0][i] - (i16)context->score_candidates[1][i];          // MISRAC2012-Dir-4.11_i
    const i16 tnr_diff = (i16)context->tnr_counters[0][i] - (i16)context->tnr_counters[1][i]; // MISRAC2012-Dir-4.11_i
    const bool low_stat = (stat[0] + stat[1]) <= eparams->flicker.th_stat;
    const bool low_diff = abs(score_diff) <= (i32)eparams->flicker.min_diff_score;
    const bool low_flicker = low_diff || low_stat;
    const bool low_tnr = abs(tnr_diff) <= (i32)eparams->flicker.min_diff_counter;

    // if scores give a clear majority candidate, take highest score
    if (!empty_candidate_1 && !low_flicker) {
        is_candidate_0 = stat[0] > stat[1];
    }

    // if scores are low but counters are high, take highest counter
    if (!empty_candidate_1 && low_flicker && !low_tnr) {
        is_candidate_0 = context->tnr_counters[0][i] > context->tnr_counters[1][i];
    }

    // if scores and counters are low, take highest SPAD if SPADs are different
    const bool same_spads = context->spads_candidates[0][i] == context->spads_candidates[1][i];
    if (!empty_candidate_1 && low_flicker && low_tnr && !same_spads) {
        is_candidate_0 = context->spads_candidates[0][i] > context->spads_candidates[1][i];
    }

    // if scores and counters are low, same SPADs and different short/long flag, take short or long depending on
    // highest exposure
    bool same_short_long;
    if (eparams->flicker.flag_mode < 2u) {
        same_short_long = context->short_long_candidates[0][i] == context->short_long_candidates[1][i];
        const bool **slc = (const bool **)context->short_long_candidates;
        if (!empty_candidate_1 && low_flicker && low_tnr && same_spads && !same_short_long) {
            is_candidate_0 =
                (bool)eparams->flicker.flag_mode ? ((i8)slc[0][i] > (i8)slc[1][i]) : ((i8)slc[0][i] < (i8)slc[1][i]);
        }
    } else {
        same_short_long = true;
    }

    // if everything is similar revert to taking the highest stat (or the first candidate if same stat)
    if (!empty_candidate_1 && low_flicker && low_tnr && same_spads && same_short_long) {
        is_candidate_0 = stat[0] >= stat[1];
    }

    return is_candidate_0;
}
