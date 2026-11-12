/**
 ******************************************************************************
 * @file    buffer.h
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

#ifndef MEDIA_C_BUFFER_H_
#define MEDIA_C_BUFFER_H_

#include <stddef.h>
#include <stdint.h>

#include "memories.h"
#include "properties.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file buffer.h
 * @brief Media buffer type.
 *
 * Defines @c buffer_t, which groups one or more memory blocks together
 * with a presentation timestamp, a sequence number and optional metadata.
 *
 * A buffer can hold several memory blocks (planes), making it suitable
 * for planar data formats where each colour component is stored in a
 * separate contiguous region.  Typical examples include:
 *
 * - **YUV planar** – one memory block per plane: one for the Y (luma)
 *   component and one or two for the U/V (chroma) components
 *   (e.g. I420, NV12, NV21).
 * - **RGB planar** – one memory block per colour channel (R, G, B).
 * - **Interleaved / packed** – all components are stored in a single
 *   memory block (e.g. YUYV, RGB888).  Only the first memory block
 *   (index 0) is used.
 *
 * Use @ref buffer_get_data to retrieve a pointer to the valid data
 * region of each plane by its zero-based index.
 */

/**
 * @brief Buffer containing memory blocks, timestamp and metadata.
 *
 * Each element of the @c memories array represents one plane of the
 * buffer.  For interleaved (packed) formats the array contains a single
 * entry; for planar formats it contains one entry per plane.
 */
typedef struct {
    memories_t* memories;   /**< Array of memory blocks (one per plane). */
    uint64_t timestamp;     /**< Presentation timestamp in nanoseconds. */
    uint32_t nb;            /**< Sequence number of the buffer. */
    properties_t* metadata; /**< Optional metadata properties. */
} buffer_t;

/**
 * @brief Allocate a new buffer.
 *
 * @param[in] memories   Pointer to the memory block list.
 * @param[in] timestamp  Presentation timestamp in nanoseconds.
 * @param[in] nb         Sequence number.
 * @param[in] metadata   Optional metadata properties (may be @c NULL).
 * @return Pointer to the newly created buffer, or @c NULL on failure.
 */
static inline buffer_t* buffer_new(memories_t* memories, uint64_t timestamp, uint32_t nb, properties_t* metadata) {
    buffer_t* buffer = (buffer_t*)malloc(sizeof(buffer_t));
    if (buffer != NULL) {
        buffer->memories = memories;
        buffer->timestamp = timestamp;
        buffer->nb = nb;
        buffer->metadata = metadata;
    }
    return buffer;
}

/**
 * @brief Free a buffer.
 *
 * Only the buffer structure itself is freed; the memory blocks and metadata
 * are left untouched.
 *
 * @param[in] buffer  Pointer to the buffer to free (may be @c NULL).
 */
static inline void buffer_free(buffer_t* buffer) {
    if (buffer != NULL) {
        free(buffer);
    }
}

/**
 * @brief Get a pointer to the valid data of a memory block by index.
 *
 * Returns a pointer to @c memory->data + @c memory->offset for the
 * memory block at position @p index in the buffer's memory list.
 *
 * @param[in] buffer  Pointer to the buffer.
 * @param[in] index   Zero-based index of the memory block.
 * @return Pointer to the start of valid data, or @c NULL if @p buffer
 *         is @c NULL or @p index is out of range.
 */
static inline uint8_t* buffer_get_data(const buffer_t* buffer, size_t index) {
    uint8_t* result = NULL;
    if ((buffer != NULL) && (buffer->memories != NULL)) {
        memory_t* mem = memories_get(buffer->memories, index);
        if (mem != NULL) {
            result = &mem->data[mem->offset];
        }
    }
    return result;
}

#ifdef __cplusplus
}
#endif

#endif  // MEDIA_C_BUFFER_H_
