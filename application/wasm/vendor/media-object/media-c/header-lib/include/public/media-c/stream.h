/**
 ******************************************************************************
 * @file    stream.h
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

#ifndef MEDIA_C_STREAM_H_
#define MEDIA_C_STREAM_H_

#include "capabilities.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file stream.h
 * @brief Media stream descriptor.
 *
 * Defines the @c direction_t enumeration and the @c stream_t structure
 * that describes a named I/O port of a media element together with its
 * supported capabilities.
 */

/** @brief Stream direction. */
typedef enum {
    DIRECTION_NONE,  /**< Unspecified direction. */
    DIRECTION_INPUT, /**< Input (sink) stream. */
    DIRECTION_OUTPUT /**< Output (source) stream. */
} direction_t;

/** @brief Describes a media stream with its direction and capabilities. */
typedef struct {
    const char* name;             /**< Unique stream name. */
    const char* description;      /**< Human-readable stream description. */
    direction_t direction;        /**< Stream direction (input / output). */
    capabilities_t* capabilities; /**< Supported capabilities for this stream. */
} stream_t;

/**
 * @brief Print a human-readable dump of a stream descriptor.
 *
 * @param[in] stream      Pointer to the stream to inspect.
 * @param[in] print_func  Printf-like callback used for output.
 * @param[in] indent      Prefix string prepended to each line.
 */
static inline void stream_inspect(const stream_t* stream, int (*print_func)(const char*, ...), const char* indent) {
    (void)print_func("%sName: %s\n", indent, stream->name);
    (void)print_func("%sDescription: %s\n", indent, stream->description);
    (void)print_func("%sDirection: %d\n", indent, stream->direction);
    capabilities_inspect(stream->capabilities, print_func, indent);
}

#ifdef __cplusplus
}
#endif

#endif  // MEDIA_C_STREAM_H_
