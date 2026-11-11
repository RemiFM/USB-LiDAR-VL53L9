/**
 ******************************************************************************
 * @file    stream_buffer.h
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

#ifndef MEDIA_C_STREAM_BUFFER_H_
#define MEDIA_C_STREAM_BUFFER_H_

#include "buffer.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file stream_buffer.h
 * @brief Named stream buffer.
 *
 * Defines @c stream_buffer_t, which associates a stream name with a
 * @c buffer_t payload used during media processing.
 */

/** @brief Associates a stream name with its buffer. */
typedef struct {
    const char *name; /**< Name of the stream. */
    buffer_t buffer;  /**< Buffer payload for this stream. */
} stream_buffer_t;

#ifdef __cplusplus
}
#endif

#endif  // MEDIA_C_STREAM_BUFFER_H_
