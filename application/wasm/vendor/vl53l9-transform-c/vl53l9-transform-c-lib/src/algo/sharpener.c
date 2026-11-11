/**
 ******************************************************************************
 * @file    sharpener.c
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

#include "algo/sharpener.h"

#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <errno.h>
#include <stddef.h>

#ifndef EINVAL
    #define EINVAL 22
#endif

#define MAX_IMAGE_SIZE (108*84)
#define MAX_GROUP_AMOUNT (42)

#define CHECK_ERRNO(expression) \
    errno = 0; \
    expression; \
    if ((bool)errno) return

typedef int32_t i32;
typedef uint32_t u32;

typedef float_t f32;

typedef struct foption_t {
    f32 value;
    bool valid;
} foption_t;

typedef struct info_t  {
    f32 max_signal_top;
    f32 sub_max_signal_top;
    f32 sum_signal_top;
    f32 x_bar_top;
    f32 y_bar_top;
    f32 sig_score_top;
    f32 max_signal_bot;
    f32 sub_max_signal_bot;
    f32 sum_signal_bot;
    f32 x_bar_bot;
    f32 y_bar_bot;
    f32 sig_score_bot;
    bool retro;
    u32 nb_pixels;
    u32 invalid_pixel_amount;
} info_t;

static inline f32 minf(f32 a, f32 b) {
    return (a < b) ? a : b;
}

static inline f32 maxf(f32 a, f32 b) {
    return (a > b) ? a : b;
}

static inline f32 clampf(f32 val, f32 min, f32 max) {
    return maxf(min, minf(max, val));
}

static inline f32 sqf(f32 val) {
    return val * val;
}

void vl53l9_algo_sharpener_init_default_params(sharpener_params_t* params) {
    params->mode = SHARPENER_MODE_SORT;
    params->exp_optim = false;
    params->recover_mode = false;
    params->invalid_distance = 12000.0f;
    params->min_range_threshold_mm = 300.0f;
    params->scale_range_threshd_by_range = true;
    params->range_threshold_factor = 0.3f;
    params->enable_max_range_threshold = true;
    params->max_range_threshold_mm_6_step = 1200.0f;
    params->max_range_threshold_mm_7_step = 600.0f;
    params->enable_distance = true;
    params->enable_gaussian = true;
    params->channel_ratio = 19.23f;
    params->sigma_factor = 0.8f;
    params->distance_power = 0.1f;
    params->signal_threshold_factor = 0.05f;
    params->threshold_includes_glare = false;
    params->glare_ratio = 0.0000138871530f;
    params->leak_shift_range_grouping = 3;
    params->nb_lines_overlap = 1;
    params->max_distance = 15.0f;
    params->min_distance_grouping = 50.0f;
    params->th_score_double_sharp = 4.0f;
    params->refl_aggressor_threshold = 300.0f;
    params->confidence_threshold = 10.0f;
    params->reflectance_threshold = 3.0f;
    params->recovery_signal_threshold_factor = 4.0f;
    params->th_peak_dominance_ratio = 10.0f;
}

static void sharpener_optim(const f32* depth, const f32* signal, const float_t* reflectance, const float_t* confidence,

    bool* sharp_valid, f32* sharp_score,

    const sharpener_params_t* params, u32 width, u32 height, u32 step_number, f32 min_distance_grouping);

static void sharpener_double(const f32* depth, const f32* signal, const float_t* reflectance, const float_t* confidence,

    bool* sharp_valid, f32* sharp_score,

    const sharpener_params_t* params, u32 width, u32 height, u32 step_number);

static f32 exp_taylor_5(f32 val);

static inline void manage_maxima(f32* pmax, f32* psubmax, f32 val);

i32 vl53l9_algo_sharpener(const f32* depth, const f32* signal, const float_t* reflectance, const float_t* confidence,

        bool* sharp_valid, f32* sharp_score,

        const sharpener_params_t* params, u32 width, u32 height, u32 step_number) {
    // if recover mode is enabled, reflectance and confidence buffers are needed
    if (params->recover_mode && (reflectance == NULL) && (confidence == NULL)) {
        errno = EINVAL;
        return EXIT_FAILURE;
    }
    // if one of the remaining input is missing, return
    // if all outputs are missing, return
    if ((depth == NULL) || (signal == NULL) || !((sharp_valid != NULL) || (sharp_score != NULL))) {
        errno = EINVAL;
        return EXIT_FAILURE;
    }

    switch (params->mode) {
    default:
    case SHARPENER_MODE_SORT:
        break;

    case SHARPENER_MODE_OPTIM:
        sharpener_optim(depth, signal, reflectance, confidence, sharp_valid, sharp_score, params, width, height,
            step_number, 0.0f);
        break;

    case SHARPENER_MODE_DOUBLE_SHARP:
        sharpener_double(depth, signal, reflectance, confidence, sharp_valid, sharp_score, params, width, height,
            step_number);
        break;
    }

    return (bool)errno ? EXIT_FAILURE : EXIT_SUCCESS;
}

void sharpener_optim(const f32* depth, const f32* signal, const float_t* reflectance, const float_t* confidence,

        bool* sharp_valid, f32* sharp_score,

        const sharpener_params_t* params, u32 width, u32 height, u32 step_number,
        f32 min_distance_grouping) {
    u32 group_id[MAX_IMAGE_SIZE] = {0u};

    info_t group_infos[MAX_GROUP_AMOUNT] = {0};

    // grouping pre-processing
    f32 max_range_threshold_mm = (step_number == 7u) ?
        params->max_range_threshold_mm_7_step : params->max_range_threshold_mm_6_step;
    const f32 max_nb_group_m1 = params->invalid_distance / max_range_threshold_mm;
    const u32 max_nb_group = (u32)max_nb_group_m1 + 1u;

    // grouping
    for (u32 y = 0; (y < height); ++y) {
        for (u32 x = 0; (x < width); ++x) {
            const u32 i = (y * width) + x;

            u32 gid = 0;
            if (depth[i] >= min_distance_grouping) {
                const f32 fgid =
                    minf(depth[i] - min_distance_grouping, params->invalid_distance) / max_range_threshold_mm;
                gid = 1u + (u32)fgid;
            }

            group_id[i] = gid;
            ++group_infos[gid].nb_pixels;

            if (y < ((height / 2u) + (u32)params->nb_lines_overlap)) {
                manage_maxima(&group_infos[gid].max_signal_top, &group_infos[gid].sub_max_signal_top, signal[i]);
                group_infos[gid].sum_signal_top += signal[i];
                group_infos[gid].x_bar_top += signal[i] * (f32)x;
                group_infos[gid].y_bar_top += signal[i] * (f32)y;
            }
            else {
                manage_maxima(&group_infos[gid].max_signal_top, &group_infos[gid].sub_max_signal_top,
                    signal[i] / params->channel_ratio);
                group_infos[gid].sum_signal_top += signal[i] / params->channel_ratio;
                group_infos[gid].x_bar_top += signal[i] * (f32)x / params->channel_ratio;
                group_infos[gid].y_bar_top += signal[i] * (f32)y / params->channel_ratio;
            }

            if (y >= ((height / 2u) - (u32)params->nb_lines_overlap)) {
                manage_maxima(&group_infos[gid].max_signal_bot, &group_infos[gid].sub_max_signal_bot, signal[i]);
                group_infos[gid].sum_signal_bot += signal[i];
                group_infos[gid].x_bar_bot += signal[i] * (f32)x;
                group_infos[gid].y_bar_bot += signal[i] * (f32)y;
            }
            else {
                manage_maxima(&group_infos[gid].max_signal_bot, &group_infos[gid].sub_max_signal_bot,
                    signal[i] / params->channel_ratio);
                group_infos[gid].sum_signal_bot += signal[i] / params->channel_ratio;
                group_infos[gid].x_bar_bot += signal[i] * (f32)x / params->channel_ratio;
                group_infos[gid].y_bar_bot += signal[i] * (f32)y / params->channel_ratio;
            }

            if (params->recover_mode) {
                group_infos[gid].retro = reflectance[i] > params->refl_aggressor_threshold;
            }
        }
    }

    for (u32 i = 0; i < max_nb_group; ++i) {
        if (group_infos[i].nb_pixels > 1u) {
            const float r_top = group_infos[i].max_signal_top / (group_infos[i].sub_max_signal_top + 1e-6f);
            if (r_top > params->th_peak_dominance_ratio) {
                group_infos[i].max_signal_top = group_infos[i].sub_max_signal_top;
            }

            const float r_bot = group_infos[i].max_signal_bot / (group_infos[i].sub_max_signal_bot + 1e-6f);
            if (r_bot > params->th_peak_dominance_ratio) {
                group_infos[i].max_signal_bot = group_infos[i].sub_max_signal_bot;
            }
        }

        group_infos[i].x_bar_top = (bool)group_infos[i].sum_signal_top ?
            (group_infos[i].x_bar_top / group_infos[i].sum_signal_top) : 0.0f;
        group_infos[i].y_bar_top = (bool)group_infos[i].sum_signal_top ?
            (group_infos[i].y_bar_top / group_infos[i].sum_signal_top) : 0.0f;
        group_infos[i].sig_score_top = (bool)group_infos[i].max_signal_top ?
            (group_infos[i].sum_signal_top / group_infos[i].max_signal_top) : 1.0f;
        group_infos[i].x_bar_bot = (bool)group_infos[i].sum_signal_bot ?
            (group_infos[i].x_bar_bot / group_infos[i].sum_signal_bot) : 0.0f;
        group_infos[i].y_bar_bot = (bool)group_infos[i].sum_signal_bot ?
            (group_infos[i].y_bar_bot / group_infos[i].sum_signal_bot) : 0.0f;
        group_infos[i].sig_score_bot = (bool)group_infos[i].max_signal_bot ?
            (group_infos[i].sum_signal_bot / group_infos[i].max_signal_bot) : 1.0f;
    }

    // compute recovery variables
    foption_t upper_min_signal = {.value = 0.0f, .valid = false};
    foption_t lower_min_signal = {.value = 0.0f, .valid = false};
    if (params->recover_mode) {
        for (u32 y = 0; y < height; ++y) {
            for (u32 x = 0; x < width; ++x) {
                const u32 i = (y * width) + x;
                const u32 gid = group_id[i];

                foption_t* min_signal_ptr = (y < (height / 2u)) ? &upper_min_signal : &lower_min_signal;
                if (!group_infos[gid].retro && (confidence[i] > params->confidence_threshold)
                        && (reflectance[i] > params->reflectance_threshold)) {
                    if (min_signal_ptr->valid) {
                        if (signal[i] < min_signal_ptr->value) {
                            min_signal_ptr->value = signal[i];
                        }
                    }
                    else {
                        min_signal_ptr->valid = true;
                        min_signal_ptr->value = signal[i];
                    }
                }
            }
        }
    }

    // set status pre-processing
    const f32 distance_power = params->distance_power / 2.0f;
    const f32 glare_ratio = params->glare_ratio * (f32)params->threshold_includes_glare;

    // set status
    for (u32 y = 0; y < height; ++y) {
        for (u32 x = 0; x < width; ++x) {
            const u32 i = (y * width) + x;

            const u32 gid = group_id[i];
            f32 max_signal, sum_signal, x_bar, y_bar, sig_score;
            const foption_t* min_signal_ptr = NULL;
            if (y < (height / 2u)) {
                max_signal = group_infos[gid].max_signal_top;
                sum_signal = group_infos[gid].sum_signal_top;
                x_bar = group_infos[gid].x_bar_top;
                y_bar = group_infos[gid].y_bar_top;
                sig_score = group_infos[gid].sig_score_top;
                min_signal_ptr = &upper_min_signal;
            }
            else {
                max_signal = group_infos[gid].max_signal_bot;
                sum_signal = group_infos[gid].sum_signal_bot;
                x_bar = group_infos[gid].x_bar_bot;
                y_bar = group_infos[gid].y_bar_bot;
                sig_score = group_infos[gid].sig_score_bot;
                min_signal_ptr = &lower_min_signal;
            }

            const f32 sig_score_sq = sig_score * sig_score * params->sigma_factor * params->sigma_factor;

            f32 score = 0.0f;
            if (params->recover_mode && group_infos[gid].retro && min_signal_ptr->valid) {
                score = signal[i] / (min_signal_ptr->value * params->recovery_signal_threshold_factor);
            }
            else {
                f32 distance = 1.0f;
                if (params->enable_distance) {
                    if (params->enable_gaussian) {
                        CHECK_ERRNO(const f32 distance_before_expf =
                            ((sqf((f32)x - x_bar) + sqf((f32)y - y_bar)) / (2.0f * sig_score_sq)));

                        if (distance_before_expf < 88.7228f) {
                            if (params->exp_optim) {
                                CHECK_ERRNO(distance = exp_taylor_5(distance_before_expf));
                            }
                            else {
                                CHECK_ERRNO(distance = expf(distance_before_expf));
                            }
                        }
                        else {
                            distance = FLT_MAX;
                        }
                    }
                    else {
                        CHECK_ERRNO(distance = powf(sqf((f32)x - x_bar) + sqf((f32)y - y_bar), distance_power));
                    }

                    distance = clampf(distance, 1.0f, params->max_distance);
                }

                const f32 signal_threshold = (max_signal * params->signal_threshold_factor)
                    + (glare_ratio * sum_signal);
                score = (bool)signal_threshold ? (signal[i] * (distance / signal_threshold)) : 0.0f;
            }

            const bool valid = (bool)((i32)score);
            group_infos[gid].invalid_pixel_amount += (u32)!valid;

            if (sharp_score) {
                sharp_score[i] = score;
            }
            if (sharp_valid) {
                sharp_valid[i] = valid;
            }
        }
    }

    // rescue
    for (u32 y = 0; y < height; ++y) {
        for (u32 x = 0; x < width; ++x) {
            const u32 i = (y * width) + x;
            const u32 gid = group_id[i];

            const bool rescue = group_infos[gid].invalid_pixel_amount == (group_infos[gid].nb_pixels - 1u);

            if (rescue) {
                if (sharp_valid) {
                    sharp_valid[i] = true;
                }
            }
        }
    }
}

void sharpener_double(const f32* depth, const f32* signal, const float_t* reflectance, const float_t* confidence,

        bool* sharp_valid, f32* sharp_score,

        const sharpener_params_t* params, u32 width, u32 height, u32 step_number) {
    bool sharp_valids[2][MAX_IMAGE_SIZE] = {0};
    f32 sharp_scores[2][MAX_IMAGE_SIZE] = {0};

    sharpener_optim(depth, signal, reflectance, confidence, sharp_valids[0], sharp_scores[0], params, width, height,
        step_number, 0.0f);
    sharpener_optim(depth, signal, reflectance, confidence, sharp_valids[1], sharp_scores[1], params, width, height,
        step_number, params->min_distance_grouping);

    for (u32 i = 0; i < (width * height); ++i) {
        const f32 final_score = sharp_scores[0][i] * sharp_scores[1][i];

        if (sharp_score) {
            sharp_score[i] = final_score;
        }
        if (sharp_valid) {
            sharp_valid[i] = final_score > params->th_score_double_sharp;
            if (sharp_valids[0][i] && sharp_valids[1][i]) sharp_valid[i] = true;
        }
    }
}

f32 exp_taylor_5(f32 val) {
    const f32 ln2 = 0.69314718056f;
    const f32 inv_ln2 = 1.44269504089f;

    const f32 kf = (val * inv_ln2) + copysignf(0.5f, val); // MISRAC2012-Rule-22.8 : errno checked at call
    const i32 ki = (i32)kf;
    const f32 r = val - ((f32)ki * ln2);

    const f32 sum = 1.0f
        + r
        + (r * r * (1.0f / (2.0f)))
        + (r * r * r * (1.0f / (2.0f * 3.0f)))
        + (r * r * r * r * (1.0f / (2.0f * 3.0f * 4.0f)))
        + (r * r * r * r * r * (1.0f / (2.0f * 3.0f * 4.0f * 5.0f)));

    return ldexpf(sum, ki); // MISRAC2012-Rule-22.8 : errno checked at call
}

static inline void manage_maxima(f32* pmax, f32* psubmax, f32 val) {
    if (val > *pmax) {
        *psubmax = *pmax;
        *pmax = val;
    }
    else if (val > *psubmax) {
        *psubmax = val;
    }
}
