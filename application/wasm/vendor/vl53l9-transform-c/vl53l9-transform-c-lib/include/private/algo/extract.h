/**
 ******************************************************************************
 * @file    extract.h
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

#ifndef EXTRACT_H
#define EXTRACT_H

#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @brief Extract distance, amplitude and ambient from raw data buffer
 *
 * @param[in] input raw data buffer
 * @param[in] dss_coeffs_in dss coeffs LUT
 *
 * @param[out] distance_out raw distance output image
 * @param[out] amplitude_out raw amplitude output image
 * @param[out] ambient_out raw ambient output image
 * @param[out] msb_out main flag per pixel
 * @param[out] dss_lut dss LUT id per pixel
 * @param[out] dss_out aperture per pixel (effective spads)
 *
 * @param[in] frame_width raw image width
 * @param[in] frame_height raw image height
 * @param[in] crop
 * @param[in] crop_offset_x
 * @param[in] crop_offset_y
 * @param[in] crop_width
 * @param[in] crop_height
 * @param[in] binning
 */
int32_t vl53l9_algo_extract(const uint8_t *input, const float_t *dss_coeffs_in,

                            float_t *distance_out, float_t *amplitude_out, float_t *ambient_out, bool *msb_out,
                            uint8_t *dss_lut, float_t *dss_out,

                            uint32_t frame_width, uint32_t frame_height, bool crop, uint32_t crop_offset_x,
                            uint32_t crop_offset_y, uint32_t crop_width, uint32_t crop_height, uint16_t binning);

#endif // EXTRACT_H
