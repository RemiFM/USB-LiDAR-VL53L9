/**
 ******************************************************************************
 * @file    control.h
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

#ifndef MEDIA_C_CONTROL_H_
#define MEDIA_C_CONTROL_H_

#include <stdint.h>
#include <string.h>

#include "spec.h"
#include "value.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file control.h
 * @brief Media control descriptor.
 *
 * Defines the @c ctrl_flags_t access flags and the @c control_t structure
 * that fully describes a single configurable parameter exposed by a media
 * element.
 */

/** @brief Access flag bits for a control. */

typedef uint32_t ctrl_flags_t;

#define CTRL_FLAGS_NONE     (0)       /**< No flags set. */
#define CTRL_FLAGS_READABLE (1U << 0) /**< Control value can be read. */
#define CTRL_FLAGS_WRITABLE (1U << 1) /**< Control value can be written. */
#define CTRL_FLAGS_STATIC   (1U << 2) /**< Static control: can be set at any time before prepare. */
#define CTRL_FLAGS_DYNAMIC  (1U << 3) /**< Dynamic control: can be set at any time. */

/** @brief Descriptor for a single media control. */
typedef struct {
    const char *name;        /**< Control identifier. */
    const char *nick;        /**< Nick used for UI as label. */
    const char *description; /**< Human-readable description of the control. */
    uint32_t quark;          /**< Non-zero integer which uniquely identifies the string name. */
    value_t value;           /**< Default value of the control. */
    vtid_t type;             /**< Value type identifier. */
    ctrl_flags_t flags;      /**< Access flags (readable / writable). */
    spec_t spec;             /**< Range specification for the control value. */
} control_t;

/**
 * @brief Print a control descriptor to an output using the provided print function.
 *
 * @param[in] control     Pointer to the control to print.
 * @param[in] print_func  Printf-like callback used for output.
 * @param[in] indent      Prefix string prepended to each output line.
 */
static void control_print(const control_t *control, int (*print_func)(const char *, ...), const char *indent) {
    char new_indent[10];
    size_t indent_len = 0U;

    if (indent == NULL) {
        indent = "";
    }

    while ((indent[indent_len] != '\0') && (indent_len < (sizeof(new_indent) - 2U))) {
        new_indent[indent_len] = indent[indent_len];
        ++indent_len;
    }

    new_indent[indent_len] = '\t';
    new_indent[indent_len + 1U] = '\0';
    (void)print_func("%sControl:\n", indent);
    (void)print_func("%s\tName: %s\n", indent, control->name);
    (void)print_func("%s\tNick: %s\n", indent, control->nick);
    (void)print_func("%s\tDescription: %s\n", indent, control->description);
    (void)print_func("%s\tQuark: %u\n", indent, control->quark);
    (void)print_func("%s\tValue: ", indent);
    value_print(&control->value, print_func);
    (void)print_func("\n");
    (void)print_func("%s\tType: %d\n", indent, control->type);
    (void)print_func("%s\tFlags: %d\n", indent, control->flags);
    spec_print(&control->spec, print_func, new_indent);
}

#ifdef __cplusplus
}
#endif

#endif // MEDIA_C_CONTROL_H_
