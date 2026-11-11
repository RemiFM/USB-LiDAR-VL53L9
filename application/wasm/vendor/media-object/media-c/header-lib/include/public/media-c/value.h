/**
 ******************************************************************************
 * @file    value.h
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

#ifndef MEDIA_C_VALUE_H_
#define MEDIA_C_VALUE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "fraction.h"

/**
 * @file value.h
 * @brief Tagged variant value system for the Media C API.
 *
 * Defines the type-identifier enumeration @c vtid_t, the variant union
 * @c vtype_t, and the tagged value @c value_t used throughout the API to
 * represent heterogeneous control and property values.
 */

/** @brief Value type identifiers for the tagged union. */
typedef enum {
    VTID_INVALID = 0,  // Reserved for uninitialized or error states
    VTID_FLOAT,
    VTID_DOUBLE,
    VTID_UINT32,
    VTID_INT32,
    VTID_UINT64,
    VTID_INT64,
    VTID_BOOL,
    VTID_STRING,
    VTID_POINTER,
    VTID_FRACTION
} vtid_t;

/** @brief Variant storage holding one typed value. */
typedef union {
    float v_float;         /**< 32-bit floating-point value. */
    double v_double;       /**< 64-bit floating-point value. */
    uint32_t v_uint32;     /**< Unsigned 32-bit integer value. */
    int32_t v_int32;       /**< Signed 32-bit integer value. */
    uint64_t v_uint64;     /**< Unsigned 64-bit integer value. */
    int64_t v_int64;       /**< Signed 64-bit integer value. */
    bool v_bool;           /**< Boolean value. */
    const char *v_string;  /**< Null-terminated string value. */
    void *v_ptr;           /**< Generic pointer value. */
    fraction_t v_fraction; /**< Fraction value (numerator / denominator). */
} vtype_t;

/** @brief Tagged value combining a variant payload with its type identifier. */
typedef struct {
    vtype_t val; /**< The variant payload. */
    vtid_t tid;  /**< Type discriminator indicating which union member is active. */
} value_t;

/**
 * @brief Print a value_t to an output using the provided print function.
 *
 * Formats and prints the variant value according to its type identifier.
 *
 * @param[in] value  Pointer to the value to print.
 * @param[in] print_func  Printf-like callback used for output.
 */
static inline void value_print(const value_t *value, int (*print_func)(const char *, ...)) {
    switch (value->tid) {
        case VTID_FLOAT:
            (void)print_func("%f", (double)value->val.v_float); // variadic functions implicitly promote float to double
            break;
        case VTID_DOUBLE:
            (void)print_func("%lf", value->val.v_double);
            break;
        case VTID_UINT32:
            (void)print_func("%u", value->val.v_uint32);
            break;
        case VTID_INT32:
            (void)print_func("%d", value->val.v_int32);
            break;
        case VTID_UINT64:
            (void)print_func("%llu", value->val.v_uint64);
            break;
        case VTID_INT64:
            (void)print_func("%lld", value->val.v_int64);
            break;
        case VTID_BOOL:
            (void)print_func("%s", value->val.v_bool ? "true" : "false");
            break;
        case VTID_STRING:
            (void)print_func("%s", value->val.v_string);
            break;
        case VTID_FRACTION:
            (void)print_func("%d/%d", value->val.v_fraction.numerator, value->val.v_fraction.denominator);
            break;
        default:
            (void)print_func("unknown");
            break;
    }
}

#ifdef __cplusplus
}
#endif

#endif  // MEDIA_C_VALUE_H_
