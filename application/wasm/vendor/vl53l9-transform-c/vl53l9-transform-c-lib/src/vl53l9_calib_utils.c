/**
 ******************************************************************************
 * @file    vl53l9_utils.c
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

#include "vl53l9_calib_utils.h"

#include <string.h> // memcpy

#define DEBUG_SETTINGS_ADDR (0x5CCU)
#define OTP_SECTION_1_ADDR  (0x6E8U)
#define OTP_SECTION_2_ADDR  (0xD18U)

#define DEBUG_SETTINGS_OFFSET (0x0000U)
#define OTP_SECTION_1_OFFSET  (OTP_SECTION_1_ADDR - DEBUG_SETTINGS_ADDR)
#define OTP_SECTION_2_OFFSET  (OTP_SECTION_2_ADDR - DEBUG_SETTINGS_ADDR)

#define DSS_SHORT_EFF_SPAD(N) (DEBUG_SETTINGS_OFFSET + ((N) * 0x2U) + 0x0058U)
#define DSS_LONG_EFF_SPAD(N)  (DEBUG_SETTINGS_OFFSET + ((N) * 0x2U) + 0x00d8U)

#define GLOBAL_DIST_OFFSET  (OTP_SECTION_1_OFFSET + 0x0004U)
#define OPTICAL_OFFSET_X    (OTP_SECTION_1_OFFSET + 0x0420U)
#define OPTICAL_OFFSET_Y    (OTP_SECTION_1_OFFSET + 0x0421U)
#define RESIDUAL_OFFSET_X   (OTP_SECTION_1_OFFSET + 0x0422U)
#define RESIDUAL_OFFSET_Y   (OTP_SECTION_1_OFFSET + 0x0423U)
#define RAD2PERP_FOV_GAIN   (OTP_SECTION_1_OFFSET + 0x043cU)
#define CAL_AMP_COEFF       (OTP_SECTION_1_OFFSET + 0x0598U)
#define CAL_AMP_SCALER      (OTP_SECTION_1_OFFSET + 0x05bbU)
#define CAL_AMP_DISTANCE    (OTP_SECTION_1_OFFSET + 0x05bcU)
#define CAL_AMP_EXPO        (OTP_SECTION_1_OFFSET + 0x05beU)
#define CAL_AMP_REFLECTANCE (OTP_SECTION_1_OFFSET + 0x05c0U)

#define DIST_OFFSET_0_945 (OTP_SECTION_1_OFFSET + 0x0008U)
#define DIST_OFFSET_1_315 (OTP_SECTION_1_OFFSET + 0x0440U)
#define DIST_OFFSET_2_441 (OTP_SECTION_2_OFFSET + 0x0000U)

static int8_t _compute_distance_offset(uint8_t *p_buffer, size_t index, uint8_t pos);

// TODO: this implementation handles only little-endian platforms (in case of big-endian data must be swapped)
void vl53l9_calib_utils_parse_data(uint8_t *buffer, vl53l9_calib_data_t *p_data) {

    uint8_t data8;
    uint16_t data16;
    uint8_t data8_masked;

    if ((buffer == NULL) || (p_data == NULL)) {
        return; // TODO: return internal error
    }

    for (uint8_t i = 0; i < DSS_COEFFS_NB; i++) {
        data16 = *((uint16_t *)(buffer + DSS_SHORT_EFF_SPAD(i)));
        p_data->dss_short_effective_spad[i] = (float)data16 / 128.0f;
        data16 = *((uint16_t *)(buffer + DSS_LONG_EFF_SPAD(i)));
        p_data->dss_long_effective_spad[i] = (float)data16 / 128.0f;
    }

    p_data->global_offset = *((int16_t *)(buffer + GLOBAL_DIST_OFFSET));

    // S6.0
    // read distance offsets over 3 blocks and realign data taking into account the 6-bit signed format
    // i = buffer - j = p_data - k = dist_offsets_pos/size
    const size_t dist_offsets_pos[3] = { DIST_OFFSET_0_945, DIST_OFFSET_1_315, DIST_OFFSET_2_441 };
    const size_t dist_offsets_size[3] = { 945, 315, 441 };
    size_t j = 0;
    for (size_t k = 0; k < 3u; k++) {
        // NOTE: we process 3 bytes at a time (24 bits) that store 4 distance offsets (4 x 6 bits = 24 bits)
        size_t start = dist_offsets_pos[k];
        size_t end = dist_offsets_pos[k] + dist_offsets_size[k];
        for (size_t i = start; i < end; i += 3u) {
            p_data->distance_offset[j] = _compute_distance_offset(buffer, i, 0);
            p_data->distance_offset[j + 1u] = _compute_distance_offset(buffer, i, 1u);
            p_data->distance_offset[j + 2u] = _compute_distance_offset(buffer, i, 2u);
            p_data->distance_offset[j + 3u] = _compute_distance_offset(buffer, i, 3u);
            j += 4u;
        }
    }

    // S2.0
    data8 = *((uint8_t *)(buffer + OPTICAL_OFFSET_X));
    if (data8 == 3u) {
        p_data->optical_offset_x = -1;
    } else {
        p_data->optical_offset_x = (int8_t)data8;
    }

    // S2.0
    data8 = *((uint8_t *)(buffer + OPTICAL_OFFSET_Y));
    if (data8 == 3u) {
        p_data->optical_offset_y = -1;
    } else {
        p_data->optical_offset_y = (int8_t)data8;
    }

    // S2.1
    data8 = *((uint8_t *)(buffer + RESIDUAL_OFFSET_X));
    data8_masked = data8 & 0x3u;
    p_data->residual_offset_x = (float)data8_masked / 2.0f;
    if ((data8 & 0x4u) == 4u) {
        p_data->residual_offset_x -= 2.0f;
    }

    // S2.1
    data8 = *((uint8_t *)(buffer + RESIDUAL_OFFSET_Y));
    data8_masked = data8 & 0x3u;
    p_data->residual_offset_y = (float)data8_masked / 2.0f;
    if ((data8 & 0x4u) == 4u) {
        p_data->residual_offset_y -= 2.0f;
    }

    // U1.7
    data8 = *((uint8_t *)(buffer + RAD2PERP_FOV_GAIN));
    data8_masked = data8 & 0x7fu;
    if (data8 & (1u << 7u)) {
        p_data->rad2perp_fov_gain = 1.0f + ((float)data8_masked / 128.0f);
    } else {
        p_data->rad2perp_fov_gain = ((float)data8_masked / 128.0f);
    }

    for (uint16_t i = 0; i < AMP_COEFFS_NB; i++) {
        p_data->amplitude_coeffs[i] = *((uint8_t *)(buffer + CAL_AMP_COEFF + i));
    }

    data8 = *((uint8_t *)(buffer + CAL_AMP_SCALER));
    p_data->amplitude_scaler = data8;

    data16 = *((uint16_t *)(buffer + CAL_AMP_DISTANCE));
    p_data->amplitude_distance = data16;

    data16 = *((uint16_t *)(buffer + CAL_AMP_EXPO));
    p_data->amplitude_exposure = data16;

    data8 = *((uint8_t *)(buffer + CAL_AMP_REFLECTANCE));
    p_data->amplitude_reflectance = data8;
}

/* private functions */

/**
 * @brief Compute distance offset from buffer
 * @param p_buffer OTP buffer to extract data from
 * @param index Index of the OTP buffer to start from
 * @param pos Position of the requested offset starting from index (0 to 3 since handled 4 by 4)
 *
 * @return The computed distance offset
 */
static int8_t _compute_distance_offset(uint8_t *p_buffer, size_t index, uint8_t pos) {

    uint8_t value;

    switch (pos) {
    case 0:
        value = p_buffer[index] & 0x3Fu;
        break;
    case 1:
        value = ((p_buffer[index] & 0xC0u) >> 6u) | ((p_buffer[index + 1u] & 0x0Fu) << 2u);
        break;
    case 2:
        value = ((p_buffer[index + 1u] & 0xF0u) >> 4u) | ((p_buffer[index + 2u] & 0x03u) << 4u);
        break;
    case 3:
        value = (p_buffer[index + 2u] & 0xFCu) >> 2u;
        break;
    default:
        value = 0; // execution should not reach here
        break;
    }

    // convert to signed value if sign bit is set
    if (value & 0x20u) {
        value = (value & 0x1Fu) - 32u;
        return (int8_t)(value);
    } else {
        return (int8_t)(value);
    }
}
