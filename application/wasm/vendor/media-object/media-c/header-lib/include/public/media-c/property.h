/**
 ******************************************************************************
 * @file    property.h
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

#ifndef MEDIA_C_PROPERTY_H_
#define MEDIA_C_PROPERTY_H_

#include <stdlib.h>

#include "value.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file property.h
 * @brief Named key-value property type.
 *
 * Defines @c property_t, a simple pair of a C-string key and a @c value_t
 * payload, together with a print helper.
 */

/** @brief Named key-value property. */
typedef struct {
    const char* name; /**< Property name (key). */
    value_t value;    /**< Property value. */
} property_t;

/**
 * @brief Print a property to an output using the provided print function.
 *
 * @param[in] property    Pointer to the property to print.
 * @param[in] print_func  Printf-like callback used for output.
 * @param[in] indent      Prefix string prepended to the output line.
 */
static inline void property_print(const property_t* property, int (*print_func)(const char*, ...), const char* indent) {
    (void)print_func("%s%s: ", indent, property->name);
    value_print(&property->value, print_func);
    (void)print_func("\n");
}

#ifdef __cplusplus
}
#endif

#endif  // MEDIA_C_PROPERTY_H_
