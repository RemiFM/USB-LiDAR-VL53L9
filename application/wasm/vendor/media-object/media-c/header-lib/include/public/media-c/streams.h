/**
 ******************************************************************************
 * @file    streams.h
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

#ifndef MEDIA_C_STREAMS_H_
#define MEDIA_C_STREAMS_H_

#include "list.h"
#include "stream.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file streams.h
 * @brief Typed list of stream descriptors.
 *
 * Provides @c streams_t (a @c list_t specialization) together with
 * creation, access, lookup and inspection helpers.
 */

/** @brief List of stream_t descriptors. */
typedef list_t streams_t;

/**
 * @brief Allocate a new streams list.
 * @param[in] initial_capacity  Number of items to pre-allocate.
 * @return Pointer to the new list, or @c NULL on failure.
 */
static inline streams_t* streams_new(size_t initial_capacity) { return list_new(initial_capacity, sizeof(stream_t)); }

/**
 * @brief Free a streams list and optionally each stream.
 * @param[in] streams    Pointer to the list.
 * @param[in] free_func  Per-item destructor (may be @c NULL).
 */
static inline void streams_free(streams_t* streams, void (*free_func)(void*)) { list_free(streams, free_func); }

/**
 * @brief Append a stream to the list.
 * @param[in,out] streams  Pointer to the list.
 * @param[in]     stream   Pointer to the stream to copy in.
 * @return @c true on success.
 */
static inline bool streams_add(streams_t* streams, stream_t* stream) { return list_add(streams, stream); }

/**
 * @brief Retrieve a stream by index.
 * @param[in] streams  Pointer to the list.
 * @param[in] index    Zero-based index.
 * @return Pointer to the stream, or @c NULL if out of range.
 */
static inline stream_t* streams_get(const streams_t* streams, size_t index) {
    return (stream_t*)list_get(streams, index);
}

/**
 * @brief Return the current number of streams.
 * @param[in] streams  Pointer to the list.
 * @return Item count.
 */
static inline size_t streams_size(const streams_t* streams) { return streams->size; }

/**
 * @brief Return the allocated capacity.
 * @param[in] streams  Pointer to the list.
 * @return Capacity.
 */
static inline size_t streams_capacity(const streams_t* streams) { return streams->capacity; }

/**
 * @brief Check whether the list is empty.
 * @param[in] streams  Pointer to the list.
 * @return @c true if the list contains no items.
 */
static inline bool streams_empty(const streams_t* streams) { return streams->size == 0U; }

/**
 * @brief Find a stream by name.
 * @param[in] streams  Pointer to the list.
 * @param[in] name     Null-terminated name to search for.
 * @return Pointer to the matching stream, or @c NULL if not found.
 */
static inline stream_t* streams_find(const streams_t* streams, const char* name) {
    stream_t* result = NULL;
    for (size_t i = 0; i < streams->size; ++i) {
        stream_t* stream = (stream_t*)list_get(streams, i);
        if (strcmp(stream->name, name) == 0) {
            result = stream;
            break;
        }
    }
    return result;
}

/**
 * @brief Remove all streams from the list, optionally freeing each one.
 * @param[in,out] streams    Pointer to the list.
 * @param[in]     free_func  Per-item destructor (may be @c NULL).
 */
static inline void streams_clear(streams_t* streams, void (*free_func)(void*)) { list_clear(streams, free_func); }

/**
 * @brief Print a human-readable dump of the streams list.
 * @param[in] streams     Pointer to the list.
 * @param[in] print_func  Printf-like callback used for output.
 */
static inline void streams_inspect(const streams_t* streams, int (*print_func)(const char*, ...)) {
    (void)print_func("Streams:\n");
    for (size_t i = 0; i < streams->size; ++i) {
        const stream_t* stream = streams_get(streams, i);
        stream_inspect(stream, print_func, "\t");
    }
}

#ifdef __cplusplus
}
#endif

#endif  // MEDIA_C_STREAMS_H_
