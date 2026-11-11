/**
 ******************************************************************************
 * @file    strings.h
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

#ifndef MEDIA_C_STRINGS_H_
#define MEDIA_C_STRINGS_H_

#include <stddef.h>
#include <stdint.h>

#include "list.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file strings.h
 * @brief Typed list of C strings.
 *
 * Provides @c strings_t (a @c list_t specialization) together with
 * creation, access and query helpers for managing collections of
 * null-terminated C strings.
 */

/** @brief List of C strings (char pointers). */
typedef list_t strings_t;

/**
 * @brief Allocate a new strings list.
 * @param[in] size  Initial capacity.
 * @return Pointer to the new list, or @c NULL on failure.
 */
static inline strings_t* strings_new(size_t size) { return list_new(size, sizeof(char*)); }

/**
 * @brief Free a strings list and optionally each string.
 * @param[in] strings    Pointer to the list.
 * @param[in] free_func  Per-item destructor (may be @c NULL).
 */
static inline void strings_free(strings_t* strings, void (*free_func)(void*)) {
    if (strings != NULL) {
        list_free(strings, free_func);
    }
}

/**
 * @brief Append a string to the list.
 * @param[in,out] strings  Pointer to the list.
 * @param[in]     string   Null-terminated string to add (pointer is stored, not copied).
 * @return @c true on success.
 */
static inline bool strings_add(strings_t* strings, char* string) { return list_add(strings, &string); }

/**
 * @brief Retrieve a string by index.
 * @param[in] strings  Pointer to the list.
 * @param[in] index    Zero-based index.
 * @return The stored string pointer.
 */
static inline char* strings_get(const strings_t* strings, size_t index) { return *(char**)list_get(strings, index); }

/**
 * @brief Return the current number of strings.
 * @param[in] strings  Pointer to the list.
 * @return Item count.
 */
static inline size_t strings_size(const strings_t* strings) { return strings->size; }

/**
 * @brief Return the allocated capacity.
 * @param[in] strings  Pointer to the list.
 * @return Capacity.
 */
static inline size_t strings_capacity(const strings_t* strings) { return strings->capacity; }

/**
 * @brief Check whether the list is empty.
 * @param[in] strings  Pointer to the list.
 * @return @c true if the list contains no items.
 */
static inline bool strings_empty(const strings_t* strings) { return strings->size == 0U; }

#ifdef __cplusplus
}
#endif

#endif  // MEDIA_C_STRINGS_H_
