/**
 ******************************************************************************
 * @file    state.h
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

#ifndef MEDIA_C_STATE_H_
#define MEDIA_C_STATE_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file state.h
 * @brief Media instance states and state transitions.
 *
 * Defines the @c media_state_t state enumeration and the
 * @c media_state_transition_t transition enumeration that describe the
 * lifecycle state machine of a media instance.
 */

/** @brief Media instance state. */
typedef enum {
    MEDIA_STATE_NULL,        /**< Not initialised. */
    MEDIA_STATE_INITIALIZED, /**< Initialised but not yet prepared. */
    MEDIA_STATE_PREPARED,    /**< Resources allocated and ready to stream. */
    MEDIA_STATE_STREAMING    /**< Actively processing data. */
} media_state_t;

/** @brief Media state transitions. */
typedef enum {
    MEDIA_STATE_TRANSITION_NONE, /**< No transition set yet. */
    MEDIA_STATE_TRANSITION_NULL_TO_INITIALIZED,
    MEDIA_STATE_TRANSITION_INITIALIZED_TO_PREPARED,
    MEDIA_STATE_TRANSITION_PREPARED_TO_STREAMING,
    MEDIA_STATE_TRANSITION_STREAMING_TO_PREPARED,
    MEDIA_STATE_TRANSITION_PREPARED_TO_INITIALIZED,
    MEDIA_STATE_TRANSITION_INITIALIZED_TO_NULL,
} media_state_transition_t;

#ifdef __cplusplus
}
#endif

#endif  // MEDIA_C_STATE_H_
