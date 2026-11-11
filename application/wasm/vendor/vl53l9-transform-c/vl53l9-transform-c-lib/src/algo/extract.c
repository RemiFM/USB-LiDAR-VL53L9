/**
 ******************************************************************************
 * @file    extract.c
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

#include "algo/extract.h"

/**
 * Extract data from the input buffer
 *
 *  - 1st block: distance (2 bytes per pixel)
 *   o distance: bits [0:14]
 *   o main_flag: bit [15]
 *
 *  - 2nd block: amplitude (2 bytes per pixel)
 *
 *  - 3rd block: ambient (2 bytes per pixel)
 *
 *  - 4th block: dss_id (4 bits per pixel)
 */

int32_t vl53l9_algo_extract(const uint8_t *input, const float_t *dss_coeffs_in,

                            float_t *distance_out, float_t *amplitude_out, float_t *ambient_out, bool *msb_out,
                            uint8_t *dss_lut, float_t *dss_out,

                            uint32_t frame_width, uint32_t frame_height, bool crop, uint32_t crop_offset_x,
                            uint32_t crop_offset_y, uint32_t crop_width, uint32_t crop_height, uint16_t binning) {

    if ((input == NULL) || (dss_coeffs_in == NULL) || (distance_out == NULL) || (amplitude_out == NULL) ||
        (ambient_out == NULL) || (msb_out == NULL) || (dss_lut == NULL) || (dss_out == NULL)) {
        return -1; // invalid parameters
    }

    uint32_t frame_size = (crop) ? (crop_width * crop_height) : (frame_width * frame_height); // size in pixels
    uint32_t block_size = (frame_width * frame_height * 2u);                                  // size in bytes
    const float_t binning_coeff = ((float_t)binning * (float_t)binning) / 4.0f;

    for (uint32_t i = 0; i < frame_size; i++) {
        uint32_t idx = (crop) ? (((frame_width * crop_offset_y) + crop_offset_x + i) * 2u) : (i * 2u);

        uint16_t distance = ((uint16_t)input[idx + 1u] << 8u) | input[idx];
        uint16_t distance_without_msb = distance & 0x7FFFu;
        distance_out[i] = (float_t)distance_without_msb;

        uint16_t amplitude = ((uint16_t)input[idx + 1u + block_size] << 8u) | (input[idx + block_size]);
        amplitude_out[i] = (float_t)amplitude;

        uint16_t ambient = ((uint16_t)input[idx + 1u + (block_size * 2u)] << 8u) | (input[idx + (block_size * 2u)]);
        ambient_out[i] = (float_t)ambient;

        msb_out[i] = ((distance >> 15u) != 0u);

        // dss_id are encoded on 4 bits, 2 dss_id per byte
        uint32_t dss_idx = (crop) ? (((frame_width * crop_offset_y) + crop_offset_x + i) / 2u) : (i / 2u);
        uint8_t dss_id = (input[dss_idx + (block_size * 3u)] >> (((i % 2u) != 0u) ? 4u : 0u)) & 0b111u;
        dss_lut[i] = dss_id;
        dss_out[i] = dss_coeffs_in[dss_id] * binning_coeff;
    }

    return 0;
}
