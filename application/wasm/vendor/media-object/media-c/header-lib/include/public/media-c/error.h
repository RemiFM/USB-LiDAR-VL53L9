/**
 ******************************************************************************
 * @file    error.h
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

#ifndef MEDIA_C_ERROR_H_
#define MEDIA_C_ERROR_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file error.h
 * @brief Error codes and error information structures for the Media C API.
 *
 * Defines the @c media_error_codes symbols with every status code that
 * can be returned by a media operation, and the @c media_error_t structure
 * that pairs a code with a human-readable message.
 */

/** @defgroup media_error_codes Media C error codes
 *  @brief Error codes returned by Media C APIs.
 *  @{
 */

#define MEDIA_ERROR_NONE (0)
#define MEDIA_ERROR_INVALID_PARAMETER (-1)
#define MEDIA_ERROR_INVALID_STATE (-2)
#define MEDIA_ERROR_INVALID_CONFIGURATION (-3)
#define MEDIA_ERROR_UNALIGNED_MEMORY (-4)
#define MEDIA_ERROR_STATIC_CTRL (-5)
#define MEDIA_ERROR_R_ONLY_CTRL (-6)
#define MEDIA_ERROR_W_ONLY_CTRL (-7)
#define MEDIA_ERROR_PENDING (-8)
#define MEDIA_ERROR_NOT_FOUND (-9)
#define MEDIA_ERROR_INVALID_PAD_CAPS (-10)
#define MEDIA_ERROR_INVALID_PAD_NAME (-11)
#define MEDIA_ERROR_INVALID_OPERATION (-12)
#define MEDIA_ERROR_UNIMPLEMENTED (-13)
#define MEDIA_ERROR_UNKNOWN (-14)

/** @} */ /* end of media_error_codes */

/** @brief Error information containing a code and a human-readable message. */
typedef struct media_error_t {
    int code;            /**< Error code (one of @c media_error_codes). */
    const char* message; /**< Human-readable error message. */
} media_error_t;

#ifdef __cplusplus
}
#endif

#endif  // MEDIA_C_ERROR_H_
