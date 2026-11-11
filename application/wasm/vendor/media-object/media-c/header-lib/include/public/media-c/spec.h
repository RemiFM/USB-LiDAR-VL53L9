/**
 ******************************************************************************
 * @file    spec.h
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

#ifndef MEDIA_C_SPEC_H_
#define MEDIA_C_SPEC_H_

#include <stdint.h>

#include "value.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file spec.h
 * @brief Range specification types for control values.
 *
 * Defines the @c num_type_t union for holding numeric boundary values and
 * the @c spec_t structure that specifies valid ranges for media controls.
 */

/** @brief Numeric value that can hold a float, signed or unsigned 32-bit integer. */
typedef union {
    float v_float;   /**< Floating-point value. */
    int32_t v_int;   /**< Signed 32-bit integer value. */
    uint32_t v_uint; /**< Unsigned 32-bit integer value. */
} num_type_t;

/** @brief Range specification defined by a minimum, maximum and type. */
typedef struct {
    num_type_t min; /**< Minimum allowed value. */
    num_type_t max; /**< Maximum allowed value. */
    vtid_t tid;     /**< Type identifier selecting the active union member. */
} spec_t;

/**
 * @brief Print a spec_t range to an output using the provided print function.
 *
 * @param[in] spec       Pointer to the range specification to print.
 * @param[in] print_func Printf-like callback used for output.
 * @param[in] indent     Prefix string prepended to each output line.
 */
static void spec_print(const spec_t* spec, int (*print_func)(const char*, ...), const char* indent) {
    (void)print_func("%sSpec: min = ", indent);
    switch (spec->tid) {
        case VTID_FLOAT:
            (void)print_func("%f", (double)spec->min.v_float); // variadic functions implicitly promote float to double
            break;
        case VTID_INT32:
            (void)print_func("%d", spec->min.v_int);
            break;
        case VTID_UINT32:
            (void)print_func("%u", spec->min.v_uint);
            break;
        default:
            (void)print_func("unknown");
            break;
    }
    (void)print_func(", max = ");
    switch (spec->tid) {
        case VTID_FLOAT:
            (void)print_func("%f", (double)spec->max.v_float); // variadic functions implicitly promote float to double
            break;
        case VTID_INT32:
            (void)print_func("%d", spec->max.v_int);
            break;
        case VTID_UINT32:
            (void)print_func("%u", spec->max.v_uint);
            break;
        default:
            (void)print_func("unknown");
            break;
    }
    (void)print_func("\n");
}

#ifdef __cplusplus
}
#endif

#endif  // MEDIA_C_SPEC_H_
