/**
 ******************************************************************************
 * @file    vl53l9_calib_utils.h
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

#ifndef VL53L9_CALIB_UTILS_H
#define VL53L9_CALIB_UTILS_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DSS_COEFFS_NB (7u)
#define AMP_COEFFS_NB (35u)

typedef struct {
    uint32_t frame_counter;
    uint16_t temperature;
    uint16_t reserved_ldd[15];

    uint16_t ref_amplitude_ch1_long;
    uint16_t ref_distance_ch1_long;
    uint16_t ref_amplitude_ch2_long;
    uint16_t ref_distance_ch2_long;
    uint16_t ref_amplitude_ch1_short;
    uint16_t ref_distance_ch1_short;
    uint16_t ref_amplitude_ch2_short;
    uint16_t ref_distance_ch2_short;

    uint16_t frame_width;
    uint16_t frame_height;

    // static settings
    uint8_t sync_mode : 2;
    uint8_t power_mode : 2;
    uint8_t format : 2;
    uint8_t acquisition_mode : 2;

    uint8_t ambient_attenuation;

    // dynamic settings
    uint16_t reserved_dyn : 4;
    uint16_t dss_mode : 2;
    uint16_t binning : 5;
    uint16_t context : 1;
    uint16_t nb_step : 4;

    uint16_t error_code;
    uint8_t error_status;

    uint8_t reserved_ldd_error[5];
    uint32_t frame_period;

    uint32_t crop_x_size : 6;
    uint32_t crop_y_size : 6;
    uint32_t crop_x_offset : 6;
    uint32_t crop_y_offset : 6;
    uint32_t crop_enable : 1;

    uint8_t nb_shot_step1_lsb;
    uint8_t nb_shot_step1_mid;
    uint8_t nb_shot_step1_msb;

    uint8_t nb_shot_step4_5_lsb;
    uint8_t nb_shot_step4_5_mid;
    uint8_t nb_shot_step4_5_msb;

    uint8_t nb_shot_step6_lsb;
    uint8_t nb_shot_step6_mid;
    uint8_t nb_shot_step6_msb;

    uint8_t nb_shot_step7_lsb;
    uint8_t nb_shot_step7_mid;
    uint8_t nb_shot_step7_msb;

    uint32_t sest_reserved[3];

} vl53l9_metadata_t;

typedef struct {
    int16_t global_offset;
    int8_t distance_offset[54 * 42];
    int8_t optical_offset_x;
    int8_t optical_offset_y;
    float residual_offset_x;
    float residual_offset_y;
    float rad2perp_fov_gain;
    uint8_t amplitude_coeffs[AMP_COEFFS_NB]; // 5x7 coefficients grid (starting from bottom left)
    uint8_t amplitude_scaler;
    uint16_t amplitude_distance;
    uint16_t amplitude_exposure;
    uint8_t amplitude_reflectance;
    float dss_short_effective_spad[DSS_COEFFS_NB];
    float dss_long_effective_spad[DSS_COEFFS_NB];
} vl53l9_calib_data_t;

/**
 * @brief Parse and process raw calibration data
 * @param[in] buffer The OTP buffer to extract calibration data from
 * @param[out] p_data The calibration data structure to fill
 *
 * @note The buffer consists of the concatenation of otp sections 1 and 2
 */
void vl53l9_calib_utils_parse_data(uint8_t *buffer, vl53l9_calib_data_t *p_data);

#ifdef __cplusplus
}
#endif

#endif // VL53L9_CALIB_UTILS_H
