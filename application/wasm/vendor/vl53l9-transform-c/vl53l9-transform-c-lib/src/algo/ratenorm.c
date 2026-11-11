/**
 ******************************************************************************
 * @file    ratenorm.c
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

#include "algo/ratenorm.h"

#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>

#ifndef EINVAL
#define EINVAL 22
#endif

#define REF_COEF_MAP_WIDTH    (7u)
#define REF_COEF_MAP_HEIGH    (5u)
#define REF_COEF_MAP_SIZE     (REF_COEF_MAP_WIDTH * REF_COEF_MAP_HEIGH)
#define MAX_IMAGE_WIDTH       (108u)
#define MAX_IMAGE_HEIGHT      (84u)
#define MAX_IMAGE_SIZE        (MAX_IMAGE_WIDTH * MAX_IMAGE_HEIGHT)
#define MAX_PADDED_IMAGE_SIZE ((MAX_IMAGE_WIDTH + 24u) * (MAX_IMAGE_HEIGHT + 20u))

#define CHECK_ERRNO(expression) \
    errno = 0;                  \
    expression;                 \
    if ((bool)errno)            \
    return

#define CHECK_ERRNO_FAIL(expression) \
    errno = 0;                       \
    expression;                      \
    if ((bool)errno)                 \
    return EXIT_FAILURE

typedef int32_t i32;
typedef uint32_t u32;

typedef float_t f32;

static inline f32 maxf(f32 a, f32 b) {
    return (a > b) ? a : b;
}
static inline f32 over_op(f32 a, f32 b) {
    (void)a;
    return b;
}
static inline f32 mult_op(f32 a, f32 b) {
    return a * b;
}

/**
 * @brief compute norm maps in fast mode
 *
 */
static void compute_norm_maps_fast(const f32 *reference_coefs, const f32 *r2p_coefs,

                                   f32 *ref_amp_no_expo, f32 *ref_amp_rad_no_expo, f32 *coeff_norm_no_expo,

                                   const ratenorm_params_t *params, u32 width, u32 height, u32 binning);

/**
 * @brief compute norm maps in non fast mode
 *
 */
static i32 compute_norm_maps(const f32 *reference_coefs, const f32 *r2p_coefs,

                             f32 *ref_amp_no_expo, f32 *ref_amp_rad_no_expo, f32 *coeff_norm_no_expo,

                             const ratenorm_params_t *params, u32 width, u32 height, u32 binning);

/**
 * @brief bicubic interpolation helper
 *
 * @param d bicubic input
 * @param a bicubic coef (-0.75 is standard)
 * @return f32 kernel result
 */
static inline f32 cubic_kernel(f32 d, f32 a);

/**
 * @brief modified signature for u32 modf
 *
 * @param num number to process
 * @param uint_part u32 part
 * @param frac_part fractionnal part
 */
static inline void modf_custom(f32 num, u32 *uint_part, f32 *frac_part);

/**
 * @brief u32 clamp function
 *
 * @param value valeu to clamp
 * @param min min included
 * @param max max included
 * @return u32 clamped value
 */
static inline u32 clamp(u32 value, u32 min, u32 max);

/**
 * @brief crop input array to output array
 *
 * @param input input array
 * @param output output array
 * @param input_width input width
 * @param crop_width crop width
 * @param crop_height crop height
 * @param offset_x crop offset from left
 * @param offset_y crop offset from top
 */
static void crop(const f32 *input, f32 *output, u32 input_width, u32 crop_width, u32 crop_height, u32 offset_x,
                 u32 offset_y);

/**
 * @brief appy binning to input array in output array
 *
 * @param input input array
 * @param output output array
 * @param width input width
 * @param height input height
 * @param bin_x horizontal binning
 * @param bin_y vertical binning
 */
static void bin(const f32 *input, f32 *output, u32 width, u32 height, u32 bin_x, u32 bin_y);

/**
 * @brief apply hadamard product of 2 matrices and write it to output
 *
 * @param a input array 1
 * @param b input array 2
 * @param result outptu array
 * @param width input/output width
 * @param height input/output height
 */
static void matrix_hadamard_product(const f32 *a, const f32 *b, f32 *result, u32 width, u32 height);

/**
 * @brief apply binary operator to each value of an array and a constant
 *
 * @param array array to iterate over
 * @param width array width
 * @param height array height
 * @param coef rhs coef
 * @param range range to transform same form as python
 * @param op binary operator to use
 */
static i32 transform(f32 *array, u32 width, u32 height, f32 coef, const char *range, u32 range_s, f32 op(f32, f32));
#define TRANSFORM(array, width, height, coef, range, op) \
    CHECK_ERRNO_FAIL(transform(array, width, height, coef, range, sizeof(range), op));
#define MAX_RANGE_STR_SIZE (50u)

/**
 * @brief pad input array to output with nearest neighbor behaviour on edges
 *
 * @param input input array
 * @param output outptu array
 * @param width input array width
 * @param height input array height
 * @param pad_left left padding
 * @param pad_right right padding
 * @param pad_top top padding
 * @param pad_bottom bottom padding
 */
static void pad_array_nn(const f32 *input, f32 *output, u32 input_size, u32 width, u32 height, u32 pad_left,
                         u32 pad_right, u32 pad_top, u32 pad_bottom);

/**
 * @brief split str according to first separator encountered
 *
 * @param to_split string to split
 * @param str1 output left split string
 * @param str1_size output left split string size
 * @param str2 output right split string
 * @param str2_size output right split string size
 * @param size input size
 * @param sep separator
 */
static void split_str(const char *to_split, char *str1, u32 *str1_size, char *str2, u32 *str2_size, u32 size, char sep);

/**
 * @brief returns true if all str characters are digits
 *
 * @param str intput string
 * @param size input string size
 * @return true all characters are digits
 * @return false at least one character is not a digit
 */
static bool is_number(const char *str, u32 size);

i32 vl53l9_algo_ratenorm_bicubic_resize(const f32 *input,

                                        f32 *output,

                                        u32 width_in, u32 height_in, u32 width_out, u32 height_out, f32 a) {
    // if one of the input is missing, return
    // if all outputs are missing, return
    if ((input == NULL) || (output == NULL)) {
        errno = EINVAL;
        return EXIT_FAILURE;
    }

    f32 scale_x = (f32)width_in / (f32)width_out;
    f32 scale_y = (f32)height_in / (f32)height_out;

    CHECK_ERRNO_FAIL(u32 pad_x = (width_out > width_in) ? (u32)ceilf(((f32)width_out - (f32)width_in) / 2.0f)
                                                        : (u32)ceilf(((f32)width_out + (f32)width_in) / 2.0f));
    CHECK_ERRNO_FAIL(u32 pad_y = (height_out > height_in) ? (u32)ceilf(((f32)height_out - (f32)height_in) / 2.0f)
                                                          : (u32)ceilf(((f32)height_out + (f32)height_in) / 2.0f));

    u32 padded_width = width_in + (pad_x * 2u);
    u32 padded_height = height_in + (pad_y * 2u);

    f32 padded_input[MAX_PADDED_IMAGE_SIZE] = { 0.0f };

    for (u32 x = 0; x < padded_width; ++x) {
        for (u32 y = 0; y < padded_height; ++y) {
            i32 src_x = (i32)x - (i32)pad_x;
            i32 src_y = (i32)y - (i32)pad_y;
            src_x = (src_x < 0) ? 0 : ((src_x >= (i32)width_in) ? ((i32)width_in - 1) : src_x);
            src_y = (src_y < 0) ? 0 : ((src_y >= (i32)height_in) ? ((i32)height_in - 1) : src_y);
            padded_input[(y * padded_width) + x] = input[((u32)src_y * width_in) + (u32)src_x];
        }
    }

    f32 offset_x = (((((f32)width_out - 1.0f) * ((f32)width_in / (f32)width_out)) - (f32)width_in) / 2.0f) + 1.5f;
    f32 offset_y = (((((f32)height_out - 1.0f) * ((f32)height_in / (f32)height_out)) - (f32)height_in) / 2.0f) + 1.5f;

    for (u32 x1 = 0; x1 < width_out; ++x1) {
        for (u32 y1 = 0; y1 < height_out; ++y1) {
            f32 x2 = ((f32)x1 * scale_x) + (f32)pad_x - (f32)offset_x;
            f32 y2 = ((f32)y1 * scale_y) + (f32)pad_y - (f32)offset_y;

            u32 x2_floor = 0u;
            f32 dx2;
            CHECK_ERRNO_FAIL(modf_custom(x2, &x2_floor, &dx2));

            u32 y2_floor = 0u;
            f32 dy2;
            CHECK_ERRNO_FAIL(modf_custom(y2, &y2_floor, &dy2));

            f32 weights[4 * 4] = { 0 };
            for (i32 nx = -1; nx < 3; ++nx) {
                for (i32 ny = -1; ny < 3; ++ny) {
                    CHECK_ERRNO_FAIL(weights[((ny + 1) * 4) + nx + 1] =
                                         cubic_kernel(dx2 - (f32)nx, a) * cubic_kernel(dy2 - (f32)ny, a));
                }
            }

            f32 sum = 0.0f;
            for (i32 i = 0; i < 16; ++i) {
                sum += weights[i];
            }
            for (i32 i = 0; i < 16; ++i) {
                weights[i] /= sum;
            }

            f32 cropped_padded_input[4 * 4] = { 0.0f };
            crop(padded_input, cropped_padded_input, padded_width, 4, 4, x2_floor, y2_floor);

            f32 product[4 * 4];
            matrix_hadamard_product(weights, cropped_padded_input, product, 16, 1);

            f32 interpolated_value = 0.0f;
            for (i32 i = 0; i < 16; ++i) {
                interpolated_value += product[i];
            }

            output[(y1 * width_out) + x1] = interpolated_value;
        }
    }

    return EXIT_SUCCESS;
}

void vl53l9_algo_ratenorm_init_default_params(ratenorm_params_t *params) {
    params->fast_mode = false;
    params->ambient_signal_correction = true;
    params->ref_mode = 0;
    params->ref_scaler = 38;
    params->ref_distance = 400;
    params->ref_reflectance = 3;
    params->ref_expo = 29440;
    params->ref_amp_const = 275;
    params->nominal_width = 54;
    params->nominal_height = 42;
    params->nominal_binning = 2;
    params->ambient_window = 64.0f;
    params->ambient_blanking = 0.0f;
    params->signal_factor = 1.4f;
    params->ambient_correction_factor = -2e-8f;
    params->main_scaler = 1.0f;
    params->side_scaler = 0.725f;
    params->corner_scaler = 0.4f;
    params->left_side_l_scaler = 1.1f;
    params->right_side_l_scaler = 1.1f;
    params->middle_section_l_scaler = 1.1f;
    params->center_region_l_scaler = 1.125f;
    params->peak_l_scaler = 1.1f;
    params->top_row_l_scaler = 1.1f;
    params->bottom_row_l_scaler = 1.1f;
    params->corner_post_l_scaler = 1.05f;
    params->exposure_width_0 = 1.3f;
    params->exposure_width_1 = 2.6f;
    params->max_spads = 10.0f;
    params->max_spads_ref = 10.461f;
    params->bicubic_coef = -0.75f;
}

i32 vl53l9_algo_ratenorm_compute_norm_maps(const f32 *reference_coefs, const f32 *r2p_coefs,

                                           f32 *ref_amp_no_expo, f32 *ref_amp_rad_no_expo, f32 *coeff_norm_no_expo,

                                           const ratenorm_params_t *params, u32 width, u32 height, u32 binning) {
    // if one of the input is missing, return
    // if all outputs are missing, return
    if ((reference_coefs == NULL) || (r2p_coefs == NULL) ||
        !((ref_amp_no_expo != NULL) || (ref_amp_rad_no_expo != NULL) || (coeff_norm_no_expo != NULL))) {
        errno = EINVAL;
        return EXIT_FAILURE;
    }

    if (params->fast_mode) {
        compute_norm_maps_fast(reference_coefs, r2p_coefs, ref_amp_no_expo, ref_amp_rad_no_expo, coeff_norm_no_expo,
                               params, width, height, binning);
    } else {
        errno = 0;
        if (compute_norm_maps(reference_coefs, r2p_coefs, ref_amp_no_expo, ref_amp_rad_no_expo, coeff_norm_no_expo,
                              params, width, height, binning)) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

i32 vl53l9_algo_ratenorm_compute_rates(const f32 *amplitude, const f32 *ambient, const f32 *effective_spads,
                                       const bool *main_flag, const f32 *ref_amp_no_expo,
                                       const f32 *ref_amp_rad_no_expo, const f32 *coeff_norm_no_expo,

                                       f32 *ref_amp, f32 *ref_amp_rad, f32 *signal_photon_rate,
                                       f32 *ambient_photon_rate, f32 *rescaled_ambient, f32 *signal_ambient_factor,

                                       const ratenorm_params_t *params, u32 size, u32 step_number, u32 expo_sf,
                                       u32 expo_sc, u32 expo_sa, u32 ambient_attenuation) {
    // if one of the input is missing, return
    // if all outputs are missing, return
    if ((amplitude == NULL) || (ambient == NULL) || (effective_spads == NULL) || (main_flag == NULL) ||
        (ref_amp_no_expo == NULL) || (ref_amp_rad_no_expo == NULL) || (coeff_norm_no_expo == NULL) ||
        !((ref_amp_no_expo != NULL) || (ref_amp_rad_no_expo != NULL) || (coeff_norm_no_expo != NULL))) {
        errno = EINVAL;
        return EXIT_FAILURE;
    }

    const f32 expo_width = 1e-9f * ((step_number == 7u) ? params->exposure_width_0 : params->exposure_width_1);
    for (u32 i = 0; i < size; ++i) {
        const u32 expo = main_flag[i] ? expo_sf : expo_sc;
        f32 ref_amp_rad_tmp = ref_amp_rad_no_expo[i] * (f32)expo_sf;
        if (ref_amp_rad) {
            ref_amp_rad[i] = ref_amp_rad_tmp;
        }
        f32 ref_amp_tmp = ref_amp_no_expo[i] * (f32)expo_sf;
        if (ref_amp) {
            ref_amp[i] = ref_amp_tmp;
        }

        const u32 attenuation = (u32)1u << ambient_attenuation;
        const f32 rescaled_ambient_tmp = ambient[i] * (f32)attenuation;

        f32 ambient_photon_rate_val = 0.0f;
        if ((ambient_photon_rate != NULL) || (signal_ambient_factor != NULL)) {
            ambient_photon_rate_val =
                maxf(0.0f, rescaled_ambient_tmp / ((params->ambient_window + params->ambient_blanking) * 1e-9f *
                                                   (f32)expo_sa * effective_spads[i]));
        }

        f32 signal_photon_rate_val = 0.0f;
        if ((signal_photon_rate != NULL) || (signal_ambient_factor != NULL)) {
            signal_photon_rate_val = maxf(0.0f, coeff_norm_no_expo[i] * params->signal_factor * amplitude[i] /
                                                    (expo_width * (f32)expo * effective_spads[i]));
        }

        if (ambient_photon_rate) {
            ambient_photon_rate[i] = ambient_photon_rate_val;
        }
        if (rescaled_ambient) {
            rescaled_ambient[i] = rescaled_ambient_tmp;
        }
        if (signal_photon_rate) {
            signal_photon_rate[i] = signal_photon_rate_val;
        }
        if (signal_ambient_factor) {
            const f32 factor = (step_number == 7u) ? 2.0f : 1.0f;
            if (params->ambient_signal_correction) {
                signal_ambient_factor[i] = 1.0f + ((ambient_photon_rate_val - signal_photon_rate_val) * factor *
                                                   params->ambient_correction_factor);
            } else {
                signal_ambient_factor[i] = 1.0f;
            }

            if ((signal_ambient_factor[i] < 0.1f) || (signal_ambient_factor[i] > 1.0f)) {
                signal_ambient_factor[i] = 1.0f;
            }
        }
    }

    return EXIT_SUCCESS;
}

static void compute_norm_maps_fast(const f32 *reference_coefs, const f32 *r2p_coefs,

                                   f32 *ref_amp_no_expo, f32 *ref_amp_rad_no_expo, f32 *coeff_norm_no_expo,

                                   const ratenorm_params_t *params, u32 width, u32 height, u32 binning) {
    f32 bin_factor = (binning != 2u) ? ((f32)binning / 2.0f) : 1.0f;

    f32 amp_ref_val = 0.0f;
    for (u32 i = 0; i < REF_COEF_MAP_SIZE; ++i) {
        amp_ref_val = maxf(amp_ref_val, reference_coefs[i]);
    }

    amp_ref_val *= (f32)params->ref_scaler * (f32)params->ref_distance * (f32)params->ref_distance *
                   params->peak_l_scaler * bin_factor * bin_factor * params->max_spads /
                   ((f32)params->ref_expo * (f32)params->ref_reflectance * params->max_spads_ref * 1e6f);

    for (u32 i = 0; i < (width * height); ++i) {
        const f32 r2p_coef_sq = r2p_coefs[i] * r2p_coefs[i];
        const f32 ref_amp_rad_no_expo_tmp = amp_ref_val * r2p_coef_sq * r2p_coef_sq;
        if (ref_amp_rad_no_expo) {
            ref_amp_rad_no_expo[i] = ref_amp_rad_no_expo_tmp;
        }
        if (ref_amp_no_expo) {
            ref_amp_no_expo[i] = ref_amp_rad_no_expo_tmp * r2p_coef_sq;
        }
        if (coeff_norm_no_expo) {
            coeff_norm_no_expo[i] = amp_ref_val / (ref_amp_rad_no_expo_tmp * r2p_coef_sq);
        }
    }
}

static i32 compute_norm_maps(const f32 *reference_coefs, const f32 *r2p_coefs,

                             f32 *ref_amp_no_expo, f32 *ref_amp_rad_no_expo, f32 *coeff_norm_no_expo,

                             const ratenorm_params_t *params, u32 width, u32 height, u32 binning) {
    f32 bin_factor = (binning != 2u) ? ((f32)binning / 2.0f) : 1.0f;

    f32 lcoefs[REF_COEF_MAP_SIZE] = { 0.0f };
    TRANSFORM(lcoefs, REF_COEF_MAP_WIDTH, REF_COEF_MAP_HEIGH, 1.0f, ":, :", over_op);

    TRANSFORM(lcoefs, REF_COEF_MAP_WIDTH, REF_COEF_MAP_HEIGH, params->left_side_l_scaler, "0:5, 0", over_op);
    TRANSFORM(lcoefs, REF_COEF_MAP_WIDTH, REF_COEF_MAP_HEIGH, params->right_side_l_scaler, "0:5, 6", over_op);
    TRANSFORM(lcoefs, REF_COEF_MAP_WIDTH, REF_COEF_MAP_HEIGH, params->middle_section_l_scaler, "0:5, 1", over_op);
    TRANSFORM(lcoefs, REF_COEF_MAP_WIDTH, REF_COEF_MAP_HEIGH, params->middle_section_l_scaler, "0:5, 5", over_op);
    TRANSFORM(lcoefs, REF_COEF_MAP_WIDTH, REF_COEF_MAP_HEIGH, params->middle_section_l_scaler, "1, 1:6", over_op);
    TRANSFORM(lcoefs, REF_COEF_MAP_WIDTH, REF_COEF_MAP_HEIGH, params->middle_section_l_scaler, "3, 1:6", over_op);
    TRANSFORM(lcoefs, REF_COEF_MAP_WIDTH, REF_COEF_MAP_HEIGH, params->top_row_l_scaler, "0, 1:6", over_op);
    TRANSFORM(lcoefs, REF_COEF_MAP_WIDTH, REF_COEF_MAP_HEIGH, params->top_row_l_scaler, "1, 1", over_op);
    TRANSFORM(lcoefs, REF_COEF_MAP_WIDTH, REF_COEF_MAP_HEIGH, params->top_row_l_scaler, "1, 5", over_op);
    TRANSFORM(lcoefs, REF_COEF_MAP_WIDTH, REF_COEF_MAP_HEIGH, params->bottom_row_l_scaler, "4, 1:6", over_op);
    TRANSFORM(lcoefs, REF_COEF_MAP_WIDTH, REF_COEF_MAP_HEIGH, params->bottom_row_l_scaler, "3, 1", over_op);
    TRANSFORM(lcoefs, REF_COEF_MAP_WIDTH, REF_COEF_MAP_HEIGH, params->bottom_row_l_scaler, "3, 5", over_op);
    TRANSFORM(lcoefs, REF_COEF_MAP_WIDTH, REF_COEF_MAP_HEIGH, params->center_region_l_scaler, "1:4, 2:5", over_op);
    TRANSFORM(lcoefs, REF_COEF_MAP_WIDTH, REF_COEF_MAP_HEIGH, params->peak_l_scaler, "2, 3", over_op);

    TRANSFORM(lcoefs, REF_COEF_MAP_WIDTH, REF_COEF_MAP_HEIGH, params->corner_post_l_scaler, "0, 0", mult_op);
    TRANSFORM(lcoefs, REF_COEF_MAP_WIDTH, REF_COEF_MAP_HEIGH, params->corner_post_l_scaler, "4, 0", mult_op);
    TRANSFORM(lcoefs, REF_COEF_MAP_WIDTH, REF_COEF_MAP_HEIGH, params->corner_post_l_scaler, "0, 6", mult_op);
    TRANSFORM(lcoefs, REF_COEF_MAP_WIDTH, REF_COEF_MAP_HEIGH, params->corner_post_l_scaler, "4, 6", mult_op);

    f32 corr_ref[REF_COEF_MAP_SIZE] = { 0.0f };
    for (u32 i = 0; i < REF_COEF_MAP_SIZE; ++i) {
        corr_ref[i] = reference_coefs[i] * lcoefs[i];
    }

    f32 corr_ref_padded[(REF_COEF_MAP_WIDTH + 2u) * (REF_COEF_MAP_HEIGH + 2u)];
    CHECK_ERRNO_FAIL(
        pad_array_nn(corr_ref, corr_ref_padded, REF_COEF_MAP_SIZE, REF_COEF_MAP_WIDTH, REF_COEF_MAP_HEIGH, 1, 1, 1, 1));

    f32 (*mul)(f32, f32) = mult_op; // convenience alias
    TRANSFORM(corr_ref_padded, REF_COEF_MAP_WIDTH + 2u, REF_COEF_MAP_HEIGH + 2u, params->side_scaler, "1:6, 0", mul);
    TRANSFORM(corr_ref_padded, REF_COEF_MAP_WIDTH + 2u, REF_COEF_MAP_HEIGH + 2u, params->side_scaler, "1:6, 8", mul);
    TRANSFORM(corr_ref_padded, REF_COEF_MAP_WIDTH + 2u, REF_COEF_MAP_HEIGH + 2u, params->side_scaler, "0, 1:8", mul);
    TRANSFORM(corr_ref_padded, REF_COEF_MAP_WIDTH + 2u, REF_COEF_MAP_HEIGH + 2u, params->side_scaler, "6, 1:8", mul);
    TRANSFORM(corr_ref_padded, REF_COEF_MAP_WIDTH + 2u, REF_COEF_MAP_HEIGH + 2u, params->corner_scaler, "0, 0", mul);
    TRANSFORM(corr_ref_padded, REF_COEF_MAP_WIDTH + 2u, REF_COEF_MAP_HEIGH + 2u, params->corner_scaler, "6, 0", mul);
    TRANSFORM(corr_ref_padded, REF_COEF_MAP_WIDTH + 2u, REF_COEF_MAP_HEIGH + 2u, params->corner_scaler, "0, 8", mul);
    TRANSFORM(corr_ref_padded, REF_COEF_MAP_WIDTH + 2u, REF_COEF_MAP_HEIGH + 2u, params->corner_scaler, "6, 8", mul);

    u32 output_width_bin = width;
    u32 output_height_bin = height;

    if ((f32)params->nominal_binning == 0.0f) { // MISRAC2012-Dir-4.11_c
        errno = EINVAL;
        return EXIT_FAILURE;
    }

    CHECK_ERRNO_FAIL(bool is_remainder_zero = !(bool)remainderf((f32)binning, (f32)params->nominal_binning));

    if ((bin_factor > 1.0f) && is_remainder_zero) {
        output_width_bin = params->nominal_width;
        output_height_bin = params->nominal_height;
    }

    f32 corr_ref_padded_resized[MAX_PADDED_IMAGE_SIZE] = { 0.0f };
    CHECK_ERRNO_FAIL(vl53l9_algo_ratenorm_bicubic_resize(
        corr_ref_padded, corr_ref_padded_resized, REF_COEF_MAP_WIDTH + 2u, REF_COEF_MAP_HEIGH + 2u,
        output_width_bin + 10u, output_height_bin + 8u, params->bicubic_coef));

    f32 corr_ref_padded_resized_cropped[MAX_PADDED_IMAGE_SIZE] = { 0.0f };
    crop(corr_ref_padded_resized, corr_ref_padded_resized_cropped, output_width_bin + 10u, output_width_bin,
         output_height_bin, 5u, 4u);
    TRANSFORM(corr_ref_padded_resized_cropped, output_width_bin, output_height_bin, params->main_scaler,
              ":, :", mult_op);

    if ((bin_factor > 1.0f) && is_remainder_zero) {
        u32 bin_x = ((params->nominal_width * params->nominal_binning) < (width * binning))
                        ? (params->nominal_width / width * params->nominal_binning)
                        : binning;
        u32 bin_y = ((params->nominal_height * params->nominal_binning) < (height * binning))
                        ? (params->nominal_height / height * params->nominal_binning)
                        : binning;

        u32 offset_x =
            ((params->nominal_width * params->nominal_binning) - (width * bin_x)) / (2u * params->nominal_binning);
        u32 offset_y =
            ((params->nominal_height * params->nominal_binning) - (height * bin_y)) / (2u * params->nominal_binning);

        f32 corr_ref_padded_resized_cropped_cropped[MAX_IMAGE_SIZE] = { 0.0f };
        crop(corr_ref_padded_resized_cropped, corr_ref_padded_resized_cropped_cropped, params->nominal_width,
             params->nominal_width - (2u * offset_x), params->nominal_height - (2u * offset_y), offset_x, offset_y);
        memset(corr_ref_padded_resized_cropped, 0, sizeof(corr_ref_padded_resized_cropped));
        bin(corr_ref_padded_resized_cropped_cropped, corr_ref_padded_resized_cropped,
            params->nominal_width - (2u * offset_x), params->nominal_height - (2u * offset_y),
            bin_x / params->nominal_binning, bin_y / params->nominal_binning);
    }

    if (!is_remainder_zero) {
        TRANSFORM(corr_ref_padded_resized_cropped, output_width_bin, output_height_bin, bin_factor * bin_factor,
                  ":, :", mult_op);
    }

    const f32 coef = (f32)params->ref_scaler * (f32)params->ref_distance * (f32)params->ref_distance *
                     params->max_spads /
                     ((f32)params->ref_expo * (f32)params->ref_reflectance * 1e6f * params->max_spads_ref);

    TRANSFORM(corr_ref_padded_resized_cropped, width, height, coef, ":, :", mult_op);

    if (ref_amp_no_expo) {
        memcpy(ref_amp_no_expo, corr_ref_padded_resized_cropped, (width * height) * sizeof(f32));
    }

    f32 ref_max = 0.0f;
    for (u32 i = 0; i < (width * height); ++i) {
        ref_max = maxf(ref_max, corr_ref_padded_resized_cropped[i]);
    }

    f32 ref_amp_rad_no_expo_tmp[MAX_IMAGE_SIZE] = { 0.0f };
    switch (params->ref_mode) {
    default:
    case 0:
        for (u32 i = 0; i < (width * height); ++i) {
            ref_amp_rad_no_expo_tmp[i] = corr_ref_padded_resized_cropped[i] / (r2p_coefs[i] * r2p_coefs[i]);
        }
        break;

    case 1:
        for (u32 i = 0; i < (width * height); ++i) {
            ref_amp_rad_no_expo_tmp[i] = ref_max * r2p_coefs[i] * r2p_coefs[i];
        }
        break;

    case 2:
        for (u32 i = 0; i < (width * height); ++i) {
            ref_amp_rad_no_expo_tmp[i] = (f32)params->ref_amp_const * r2p_coefs[i] * r2p_coefs[i];
        }
        break;
    }

    if (coeff_norm_no_expo) {
        for (u32 i = 0; i < (width * height); ++i) {
            coeff_norm_no_expo[i] = ref_max / ref_amp_rad_no_expo_tmp[i];
        }
    }

    for (u32 i = 0; i < (width * height); ++i) {
        ref_amp_rad_no_expo_tmp[i] /= r2p_coefs[i] * r2p_coefs[i];
    }

    if (ref_amp_rad_no_expo) {
        memcpy(ref_amp_rad_no_expo, ref_amp_rad_no_expo_tmp, width * height * sizeof(f32));
    }

    return EXIT_SUCCESS;
}

inline f32 cubic_kernel(f32 d, f32 a) { // errno value is checked at call
    errno = 0;
    if (fabsf(d) < 1.0f) {
        return ((a + 2.0f) * powf(fabsf(d), 3.0f)) - ((a + 3.0f) * powf(d, 2.0f)) + 1.0f;
    } else if (fabsf(d) < 2.0f) {
        return (a * powf(fabsf(d), 3.0f)) - (5.0f * a * powf(d, 2.0f)) + (8.0f * a * fabsf(d)) - (4.0f * a);
    } else {
        return 0.0f;
    }
}

inline void modf_custom(f32 num, u32 *uint_part, f32 *frac_part) {
    f32 fuint_part;
    CHECK_ERRNO(*frac_part = modff(num, &fuint_part));
    *uint_part = (u32)fuint_part;
}

inline u32 clamp(u32 value, u32 min, u32 max) {
    return (value <= min) ? min : ((value >= max) ? max : value);
}

void crop(const f32 *input, f32 *output, u32 input_width, u32 crop_width, u32 crop_height, u32 offset_x, u32 offset_y) {
    for (u32 i = 0; i < crop_height; ++i) {
        for (u32 j = 0; j < crop_width; ++j) {
            u32 src_x = offset_x + j;
            u32 src_y = offset_y + i;
            src_x = (src_x >= input_width) ? (input_width - 1u) : src_x;
            src_y = (src_y >= input_width) ? (input_width - 1u) : src_y;
            output[(i * crop_width) + j] = input[(src_y * input_width) + src_x];
        }
    }
}

void bin(const f32 *input, f32 *output, u32 width, u32 height, u32 bin_x, u32 bin_y) {
    for (u32 line = 0; line < height; ++line) {
        for (u32 col = 0; col < width; ++col) {
            const u32 input_id = (line * width) + col;
            const u32 output_id = ((line / bin_y) * (width / bin_x)) + (col / bin_x);
            output[output_id] += input[input_id];
        }
    }
}

void matrix_hadamard_product(const f32 *a, const f32 *b, f32 *result, u32 width, u32 height) {
    for (u32 column = 0; column < width; ++column) {
        for (u32 line = 0; line < height; ++line) {
            result[(line * width) + column] = a[(line * width) + column] * b[(line * width) + column];
        }
    }
}

i32 transform(f32 *array, u32 width, u32 height, f32 coef, const char *range, u32 range_s, f32 op(f32, f32)) {
    char range_to_filter[50] = { 0 };
    memcpy(range_to_filter, range, range_s);

    char range_filtered[MAX_RANGE_STR_SIZE] = { 0 };
    u32 j = 0;
    for (u32 i = 0u; i < range_s; ++i) {
        if (range_to_filter[i] != ' ') {
            range_filtered[j++] = range_to_filter[i];
        }
    }

    u32 column_start, column_end, line_start, line_end;

    char columns[50] = { 0 };
    u32 columns_size = 0;
    char lines[50] = { 0 };
    u32 lines_size = 0;
    split_str(range_filtered, lines, &lines_size, columns, &columns_size, 50, ',');

    if (lines[0] == ':') {
        line_start = 0u;
        line_end = height - 1u;
    } else if (is_number(lines, lines_size)) {
        CHECK_ERRNO_FAIL(line_start = strtoul(lines, NULL, 10)); // MISRAC2012-Rule-22.9
        line_end = line_start;
    } else {
        char line_start_str[50] = { 0 };
        u32 line_start_str_size = 0;
        char line_end_str[50] = { 0 };
        u32 line_end_str_size = 0;
        split_str(lines, line_start_str, &line_start_str_size, line_end_str, &line_end_str_size, 50, ':');
        CHECK_ERRNO_FAIL(line_start = strtoul(line_start_str, NULL, 10));  // MISRAC2012-Rule-22.9
        CHECK_ERRNO_FAIL(line_end = strtoul(line_end_str, NULL, 10) - 1u); // MISRAC2012-Rule-22.9
    }

    if (columns[0] == ':') {
        column_start = 0u;
        column_end = width - 1u;
    } else if (is_number(columns, columns_size)) {
        CHECK_ERRNO_FAIL(column_start = strtoul(columns, NULL, 10)); // MISRAC2012-Rule-22.9
        column_end = column_start;
    } else {
        char column_start_str[50] = { 0 };
        u32 column_start_str_size = 0;
        char column_end_str[50] = { 0 };
        u32 column_end_str_size = 0;
        split_str(columns, column_start_str, &column_start_str_size, column_end_str, &column_end_str_size, 50, ':');
        CHECK_ERRNO_FAIL(column_start = strtoul(column_start_str, NULL, 10));  // MISRAC2012-Rule-22.9
        CHECK_ERRNO_FAIL(column_end = strtoul(column_end_str, NULL, 10) - 1u); // MISRAC2012-Rule-22.9
    }

    for (u32 line = line_start; line <= line_end; ++line) {
        for (u32 column = column_start; column <= column_end; ++column) {
            u32 linear_id = (line * width) + column;
            array[linear_id] = op(array[linear_id], coef);
        }
    }

    return EXIT_SUCCESS;
}

void pad_array_nn(const f32 *input, f32 *output, u32 input_size, u32 width, u32 height, u32 pad_left, u32 pad_right,
                  u32 pad_top, u32 pad_bottom) {
    for (u32 line = 0; line < (height + pad_top + pad_bottom); ++line) {
        for (u32 column = 0; column < (width + pad_left + pad_right); ++column) {
            u32 input_id = ((clamp(line, pad_top, height + pad_top - 1u) - pad_top) * width) +
                           (clamp(column, pad_left, width + pad_left - 1u) - pad_left);
            if (input_id >= input_size) {
                errno = ERANGE;
                return;
            }
            output[(line * (width + pad_left + pad_right)) + column] = input[input_id];
        }
    }
}

void split_str(const char *to_split, char *str1, u32 *str1_size, char *str2, u32 *str2_size, u32 size, char sep) {
    bool sep_encountered = false;
    *str2_size = 0;
    *str1_size = 0;
    for (u32 i = 0; i < size; ++i) {
        if (sep_encountered) {
            if (to_split[i] != '\0') {
                str2[(*str2_size)++] = to_split[i];
            } else {
                // EOL of str2 encountered, returning
                return;
            }
        } else {
            if (to_split[i] == sep) {
                sep_encountered = true;
                *str1_size = i;
            } else {
                str1[i] = to_split[i];
            }
        }
    }

    ++(*str2_size);
}

bool is_number(const char *str, u32 size) {
    for (u32 i = 0; i < size; ++i) {
        const i32 str_i32 = (i32)str[i];
        if (str_i32 > 255) {
            errno = ERANGE;
            return false;
        }
        if (!(bool)isdigit(str_i32)) {
            return false;
        }
    }
    return true;
}
