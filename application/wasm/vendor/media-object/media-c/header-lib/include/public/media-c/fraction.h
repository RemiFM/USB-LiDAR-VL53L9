/**
 ******************************************************************************
 * @file    fraction.h
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

#ifndef MEDIA_C_FRACTION_H_
#define MEDIA_C_FRACTION_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file fraction.h
 * @brief Fraction (rational number) type for the Media C API.
 *
 * Provides the @c fraction_t type used to represent rational quantities
 * such as frame rates and aspect ratios.
 */

/** @brief Rational number represented as numerator / denominator. */
typedef struct {
    int32_t numerator;   /**< Numerator of the fraction. */
    int32_t denominator; /**< Denominator of the fraction. */
} fraction_t;

#ifdef __cplusplus
}
#endif

#endif  // MEDIA_C_FRACTION_H_
