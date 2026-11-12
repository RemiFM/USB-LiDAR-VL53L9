/**
 ******************************************************************************
 * @file    memories.h
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

#ifndef MEDIA_C_MEMORIES_H_
#define MEDIA_C_MEMORIES_H_

#include <stddef.h>
#include <stdint.h>

#include "list.h"
#include "memory.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file memories.h
 * @brief Typed list of memory_t blocks.
 *
 * Provides @c memories_t (a @c list_t specialization) together with
 * construction, access and query helpers for managing collections of
 * raw memory descriptors.
 */

/** @brief List of memory_t blocks. */
typedef list_t memories_t;

/**
 * @brief Allocate a new memories list.
 * @param[in] size  Initial capacity (number of memory_t items).
 * @return Pointer to the new list, or @c NULL on failure.
 */
static inline memories_t* memories_new(size_t size) { return list_new(size, sizeof(memory_t)); }

/**
 * @brief Free a memories list and optionally each memory block.
 * @param[in] memories   Pointer to the list.
 * @param[in] free_func  Per-item destructor (may be @c NULL).
 */
static inline void memories_free(memories_t* memories, void (*free_func)(void*)) {
    if (memories != NULL) {
        list_free(memories, free_func);
    }
}

/**
 * @brief Append a memory block to the list.
 * @param[in,out] memories  Pointer to the list.
 * @param[in]     memory    Pointer to the memory_t to copy in.
 * @return @c true on success.
 */
static inline bool memories_add(memories_t* memories, memory_t* memory) { return list_add(memories, memory); }

/**
 * @brief Retrieve a memory block by index.
 * @param[in] memories  Pointer to the list.
 * @param[in] index     Zero-based index.
 * @return Pointer to the memory_t, or @c NULL if out of range.
 */
static inline memory_t* memories_get(const memories_t* memories, size_t index) {
    return (memory_t*)list_get(memories, index);
}

/**
 * @brief Return the current number of memory blocks.
 * @param[in] memories  Pointer to the list.
 * @return Item count.
 */
static inline size_t memories_size(const memories_t* memories) { return memories->size; }

/**
 * @brief Return the allocated capacity.
 * @param[in] memories  Pointer to the list.
 * @return Capacity.
 */
static inline size_t memories_capacity(const memories_t* memories) { return memories->capacity; }

/**
 * @brief Check whether the list is empty.
 * @param[in] memories  Pointer to the list.
 * @return @c true if the list contains no items.
 */
static inline bool memories_empty(const memories_t* memories) { return memories->size == 0U; }

#ifdef __cplusplus
}
#endif

#endif  // MEDIA_C_MEMORIES_H_
