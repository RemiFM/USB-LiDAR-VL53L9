/**
 ******************************************************************************
 * @file    stream_buffers.h
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

#ifndef MEDIA_C_STREAM_BUFFERS_H_
#define MEDIA_C_STREAM_BUFFERS_H_

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "list.h"
#include "stream_buffer.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file stream_buffers.h
 * @brief Typed list of named stream buffers.
 *
 * Provides @c stream_buffers_t (a @c list_t specialization) together with
 * creation, access, lookup and iteration helpers for managing collections
 * of @c stream_buffer_t entries.
 */

/** @brief List of stream_buffer_t entries. */
typedef list_t stream_buffers_t;

/**
 * @brief Allocate a new stream_buffers list.
 * @param[in] initial_capacity  Number of items to pre-allocate.
 * @return Pointer to the new list, or @c NULL on failure.
 */
static inline stream_buffers_t* stream_buffers_new(size_t initial_capacity) {
    return list_new(initial_capacity, sizeof(stream_buffer_t));
}

/**
 * @brief Free a stream_buffers list and optionally each entry.
 * @param[in] stream_buffers  Pointer to the list.
 * @param[in] free_func       Per-item destructor (may be @c NULL).
 */
static inline void stream_buffers_free(stream_buffers_t* stream_buffers, void (*free_func)(void*)) {
    list_free(stream_buffers, free_func);
}

/**
 * @brief Append a stream buffer to the list.
 * @param[in,out] stream_buffers  Pointer to the list.
 * @param[in]     stream_buffer   Pointer to the entry to copy in.
 * @return @c true on success.
 */
static inline bool stream_buffers_add(stream_buffers_t* stream_buffers, stream_buffer_t* stream_buffer) {
    return list_add(stream_buffers, stream_buffer);
}

/**
 * @brief Retrieve a stream buffer by index.
 * @param[in] stream_buffers  Pointer to the list.
 * @param[in] index           Zero-based index.
 * @return Pointer to the entry, or @c NULL if out of range.
 */
static inline stream_buffer_t* stream_buffers_get(const stream_buffers_t* stream_buffers, size_t index) {
    return (stream_buffer_t*)list_get(stream_buffers, index);
}

/**
 * @brief Return the current number of stream buffers.
 * @param[in] stream_buffers  Pointer to the list.
 * @return Item count.
 */
static inline size_t stream_buffers_size(const stream_buffers_t* stream_buffers) { return stream_buffers->size; }

/**
 * @brief Return the allocated capacity.
 * @param[in] stream_buffers  Pointer to the list.
 * @return Capacity.
 */
static inline size_t stream_buffers_capacity(const stream_buffers_t* stream_buffers) {
    return stream_buffers->capacity;
}

/**
 * @brief Check whether the list is empty.
 * @param[in] stream_buffers  Pointer to the list.
 * @return @c true if the list contains no items.
 */
static inline bool stream_buffers_empty(const stream_buffers_t* stream_buffers) { return stream_buffers->size == 0U; }

/**
 * @brief Find a stream buffer by stream name.
 * @param[in] stream_buffers  Pointer to the list.
 * @param[in] name            Null-terminated stream name to search for.
 * @return Pointer to the matching entry, or @c NULL if not found.
 */
static inline stream_buffer_t* stream_buffers_find(const stream_buffers_t* stream_buffers, const char* name) {
    stream_buffer_t* result = NULL;
    for (size_t i = 0; i < stream_buffers->size; ++i) {
        stream_buffer_t* stream_buffer = (stream_buffer_t*)list_get(stream_buffers, i);
        if (strcmp(stream_buffer->name, name) == 0) {
            result = stream_buffer;
            break;
        }
    }
    return result;
}

/**
 * @brief Remove all entries from the list, optionally freeing each one.
 * @param[in,out] stream_buffers  Pointer to the list.
 * @param[in]     free_func       Per-item destructor (may be @c NULL).
 */
static inline void stream_buffers_clear(stream_buffers_t* stream_buffers, void (*free_func)(void*)) {
    list_clear(stream_buffers, free_func);
}

/**
 * @brief Iterate over all entries and invoke a callback for each.
 * @param[in] stream_buffers  Pointer to the list.
 * @param[in] callback        Function called for each stream_buffer_t pointer.
 */
static inline void stream_buffers_iterate(const stream_buffers_t* stream_buffers, void (*callback)(stream_buffer_t*)) {
    if ((stream_buffers != NULL) && (callback != NULL)) {
        for (size_t i = 0; i < stream_buffers->size; ++i) {
            stream_buffer_t* stream_buffer = (stream_buffer_t*)list_get(stream_buffers, i);
            callback(stream_buffer);
        }
    }
}

#ifdef __cplusplus
}
#endif

#endif  // MEDIA_C_STREAM_BUFFERS_H_
