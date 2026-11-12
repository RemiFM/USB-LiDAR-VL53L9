/**
 ******************************************************************************
 * @file    controls.h
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

#ifndef MEDIA_C_CONTROLS_H_
#define MEDIA_C_CONTROLS_H_

#include <stddef.h>
#include <stdint.h>

#include "control.h"
#include "list.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file controls.h
 * @brief Typed list of control descriptors.
 *
 * Provides @c controls_t (a @c list_t specialization) together with
 * creation, access, lookup and inspection helpers.
 */

/** @brief List of control_t descriptors. */
typedef list_t controls_t;

/**
 * @brief Allocate a new controls list.
 * @param[in] size  Initial capacity.
 * @return Pointer to the new list, or @c NULL on failure.
 */
static inline controls_t* controls_new(size_t size) { return list_new(size, sizeof(control_t)); }

/**
 * @brief Free a controls list and optionally each control.
 * @param[in] controls   Pointer to the list.
 * @param[in] free_func  Per-item destructor (may be @c NULL).
 */
static inline void controls_free(controls_t* controls, void (*free_func)(void*)) {
    if (controls != NULL) {
        list_free(controls, free_func);
    }
}

/**
 * @brief Append a control to the list.
 * @param[in,out] controls  Pointer to the list.
 * @param[in]     control   Pointer to the control to copy in.
 * @return @c true on success.
 */
static inline bool controls_add(controls_t* controls, control_t* control) { return list_add(controls, control); }

/**
 * @brief Retrieve a control by index.
 * @param[in] controls  Pointer to the list.
 * @param[in] index     Zero-based index.
 * @return Pointer to the control, or @c NULL if out of range.
 */
static inline control_t* controls_get(const controls_t* controls, size_t index) {
    return (control_t*)list_get(controls, index);
}

/**
 * @brief Return the current number of controls.
 * @param[in] controls  Pointer to the list.
 * @return Item count.
 */
static inline size_t controls_size(const controls_t* controls) { return controls->size; }

/**
 * @brief Return the allocated capacity.
 * @param[in] controls  Pointer to the list.
 * @return Capacity.
 */
static inline size_t controls_capacity(const controls_t* controls) { return controls->capacity; }

/**
 * @brief Check whether the list is empty.
 * @param[in] controls  Pointer to the list.
 * @return @c true if the list contains no items.
 */
static inline bool controls_empty(const controls_t* controls) { return controls->size == 0U; }

/**
 * @brief Find a control by name.
 * @param[in] controls  Pointer to the list.
 * @param[in] name      Null-terminated name to search for.
 * @return Pointer to the matching control, or @c NULL if not found.
 */
static inline control_t* controls_find(const controls_t* controls, const char* name) {
    control_t* result = NULL;
    for (size_t i = 0; i < controls->size; i++) {
        control_t* control = controls_get(controls, i);
        if (strcmp(control->name, name) == 0) {
            result = control;
            break;
        }
    }
    return result;
}

/**
 * @brief Iterate over all controls and invoke a callback for each.
 * @param[in] controls  Pointer to the list.
 * @param[in] callback  Function called for each control_t pointer.
 */
static inline void controls_iterate(const controls_t* controls, void (*callback)(control_t*)) {
    if ((controls != NULL) && (callback != NULL)) {
        for (size_t i = 0; i < controls->size; i++) {
            control_t* control = controls_get(controls, i);
            callback(control);
        }
    }
}

/**
 * @brief Print a human-readable dump of the controls list.
 * @param[in] controls    Pointer to the list.
 * @param[in] print_func  Printf-like callback used for output.
 */
static inline void controls_inspect(const controls_t* controls, int (*print_func)(const char*, ...)) {
    (void)print_func("Controls:\n");
    for (size_t i = 0; i < controls->size; ++i) {
        const control_t* control = controls_get(controls, i);
        control_print(control, print_func, "\t");
    }
}

#ifdef __cplusplus
}
#endif

#endif  // MEDIA_C_CONTROLS_H_
