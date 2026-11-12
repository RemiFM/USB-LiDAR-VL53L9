/**
 ******************************************************************************
 * @file    radial_to_perp.h
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
 * @brief r2p module constants and constants computed and/or extracted from OTP
 *
 * @note Based on Python algo R_1.3.9
 *
 * @param float_t efl effective focal length in um
 * @param float_t residual_offset_x residual offset in x in SPAD
 * @param float_t residual_offset_y residual offset in y in SPAD
 * @param uint32_t max_distance maximum clipping distance (ISP driven)
 * @param bool parallax_correction Enable parallax correction
 * @param uint32_t parallax_limit minimum distance where parallax correction is computed
 * @param float_t alpha K1 distortion coeff
 * @param float_t beta K2 distortion coeff
 * @param float_t gamma K3 distortion coeff
 * @param float_t kappa K4 distortion coeff
 * @param uint32_t max_spads_x full sensor spad width
 * @param uint32_t max_spads_y full sensor spad height
 * @param float_t spad_size_um spad size in um
 */
typedef struct radial_to_perp_params_t {
    float_t efl;
    float_t residual_offset_x;
    float_t residual_offset_y;
    uint32_t max_distance;
    bool parallax_correction;
    uint32_t parallax_limit;
    float_t alpha;
    float_t beta;
    float_t gamma;
    float_t kappa;
    uint32_t max_spads_x;
    uint32_t max_spads_y;
    float_t spad_size_um;
    float_t conf_scaling;
} radial_to_perp_params_t;

/**
 * @brief init params default values
 *
 * @note Based on Python algo R_1.3.9
 */
void vl53l9_algo_radial_to_perp_init_default_params(radial_to_perp_params_t *params);

/**
 * @brief compute r2p conversion
 *
 * @note Based on Python algo R_1.3.9
 *
 * @details reference : https://developer.android.com/reference/android/graphics/ImageFormat#DEPTH_POINT_CLOUD
 *
 * @retval EXIT_SUCCESS algo ran successfuly
 * @retval EXIT_FAILURE algo ran into an issue, check errno
 *
 * @param depth input depth
 *
 * @param output_z output perpendicular distance
 * @param center_x output center_x for each coordinate (needed for pointcluod computation if parralax is enabled)
 * @param distorsion distorsion output for pointcloud computation
 * @param r2p_valid output validity map of r2p
 *
 * @param params r2p params
 * @param width image width
 * @param height image height
 * @param binning image binning
 *
 * @return int32_t 0 if success, not 0 otherwise
 */
int32_t vl53l9_algo_radial_to_perp(const float_t *depth,

                                   float_t *output_z, float_t *center_x, float_t *distorsion, bool *r2p_valid,

                                   const radial_to_perp_params_t *params, uint32_t width, uint32_t height,
                                   uint32_t binning);

/**
 * @brief compute pointcloud
 *
 * @note Based on Python algo R_1.3.9
 *
 * @retval EXIT_SUCCESS algo ran successfuly
 * @retval EXIT_FAILURE algo ran into an issue, check errno
 *
 * @param depth input depth
 * @param center_x input center_x for each coordinate
 * @param distorsion input distorsion
 * @param confidence input confidence
 * @param conf_thr input confidence threshold
 * @param filter_status input filter status
 *
 * @param pointcloud output pointcloud
 *
 * @param params r2p params
 * @param width image width
 * @param height image height
 * @param binning image binning
 *
 * @return int32_t 0 if success, not 0 otherwise
 */
int32_t vl53l9_algo_pointcloud(const float_t *depth, const float_t *center_x, const float_t *distorsion,
                               const float_t *confidence, const float_t *conf_thr, const uint8_t *filter_status,

                               float_t *pointcloud,

                               const radial_to_perp_params_t *params, uint32_t width, uint32_t height,
                               uint32_t binning);

#ifdef __cplusplus
}
#endif
