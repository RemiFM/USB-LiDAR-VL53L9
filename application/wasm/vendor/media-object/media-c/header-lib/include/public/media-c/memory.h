/**
 ******************************************************************************
 * @file    memory.h
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

#ifndef MEDIA_C_MEMORY_H_
#define MEDIA_C_MEMORY_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file memory.h
 * @brief Raw memory block descriptor.
 *
 * Defines the @c memory_flags_t allocation flags and the @c memory_t
 * structure that describes a contiguous block of memory.
 */

/** @brief Memory allocation flags. */
typedef enum { MEM_FLAG_NONE = 0x00, MEM_FLAG_ION = 0x01 } memory_flags_t;

/** @brief Describes a contiguous block of memory with offset and flags. */
typedef struct {
    uint8_t* data;        /**< Pointer to the raw memory data. */
    size_t offset;        /**< Byte offset into @p data where valid content starts. */
    size_t size;          /**< Size in bytes of the valid content. */
    size_t maxsize;       /**< Total allocated size of @p data in bytes. */
    memory_flags_t flags; /**< Memory allocation flags. */
} memory_t;

/**
 * @brief Add one or more flags to a memory descriptor.
 *
 * @param[in,out] memory  Pointer to the memory descriptor.
 * @param[in]     flags   Flags to set (bitwise OR).
 */
static inline void memory_add_flags(memory_t* memory, memory_flags_t flags) {
    uint32_t combined = (uint32_t)memory->flags | (uint32_t)flags;
    memory->flags = (memory_flags_t)combined;
}

#ifdef __cplusplus
}
#endif

#endif  // MEDIA_C_MEMORY_H_
