/**
 ******************************************************************************
 * @file    media.h
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

#ifndef MEDIA_C_H_
#define MEDIA_C_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "media-c/buffer.h"
#include "media-c/capabilities.h"
#include "media-c/control.h"
#include "media-c/controls.h"
#include "media-c/error.h"
#include "media-c/properties.h"
#include "media-c/spec.h"
#include "media-c/state.h"
#include "media-c/stream.h"
#include "media-c/stream_buffers.h"
#include "media-c/streams.h"
#include "media-c/strings.h"
#include "media-c/value.h"
#include "media-c/version.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file media.h
 * @brief Public API for the Media Processing Library.
 *
 * This header defines the public interface for the Media Processing Library,
 * including functions to manage the lifecycle, streams, controls, and
 * capabilities of a media element.
 *
 * @section lifecycle Lifecycle Management
 *
 * @ref media_get_state       — Query the current lifecycle state.
 *
 * @ref media_initialize      — Transition from @c MEDIA_STATE_NULL to
 *                               @c MEDIA_STATE_INITIALIZED. Acquires
 *                               hardware handles and internal resources.
 *
 * @ref media_prepare         — Transition from @c MEDIA_STATE_INITIALIZED to
 *                               @c MEDIA_STATE_PREPARED. Validates and applies
 *                               static controls, allocates resources that
 *                               depend on the static configuration.
 *
 * @ref media_finalize        — Transition from @c MEDIA_STATE_PREPARED back to
 *                               @c MEDIA_STATE_INITIALIZED. Releases resources
 *                               allocated during preparation.
 *
 * @ref media_release         — Transition from @c MEDIA_STATE_INITIALIZED back
 *                               to @c MEDIA_STATE_NULL. Frees all resources
 *                               acquired during initialization.
 *
 * @section info Information & Inspection
 *
 * @ref media_about           — Retrieve element metadata (name, description,
 *                               version, license, URL, open-source dependencies).
 *
 * @ref media_get_version     — Get the implemented media API version
 *                               (major, minor, patch).
 *
 * @ref media_inspect         — Print a human-readable dump of the element
 *                               (about, streams, controls) via a printf-like
 *                               callback.
 *
 * @section streams Streams & Capabilities
 *
 * @ref media_get_streams               — List all input/output streams.
 *
 * @ref media_get_stream_capabilities   — Get the current capabilities of a
 *                                         named stream.
 *
 * @ref media_set_stream_capabilities   — Set desired capabilities on a named
 *                                         stream.
 *
 * @ref media_query_stream_capabilities — Query capabilities compatible with
 *                                         the current configuration context.
 *
 * @ref media_query_memory_allocation   — Query memory alignment constraints
 *                                         for a stream's input buffers.
 *
 * @section ctrls Controls
 *
 * @ref media_get_controls    — List all available controls (static and dynamic).
 *
 * @ref media_get_control     — Read the current value of a control by name.
 *                               Can be called at any time.
 *
 * @ref media_set_control     — Write a new value to a control by name.
 *                               Static controls can only be set before
 *                               @ref media_prepare; dynamic controls can be
 *                               changed at any time.
 */
/** @brief Media C API handle providing the public and private virtual interface. */
typedef struct _media {
    /* ============================================================================
       ============================== Public members ============================== */

    /**
     * @brief Get the version of the implementated media API
     * @param[in] self Instance of the media handle
     * @param[out] major
     * @param[out] minor
     * @param[out] patch
     */
    void (*get_version)(const struct _media *self, uint32_t *major, uint32_t *minor, uint32_t *patch);

    /**
     * @brief Get the list of available streams for a given instance
     * @param[in] self Instance of the media handle
     * @param[out] streams List of streams. Ownership is not transferred to the caller (const)
     * @note @p streams is a NULL-terminated array
     */
    int (*get_streams)(const struct _media *self, const streams_t **streams);

    /**
     * @brief Get the list of available controls for a given instance
     * @param[in] self Instance of the media handle
     * @param[out] controls List of controls
     * @note @p controls is a NULL-terminated array
     */
    int (*get_controls)(const struct _media *self, const controls_t **controls);

    /**
     * @brief Get the value of a control by its ID
     * @param[in] self Instance of the media handle
     * @param[in] id ID of the control
     * @param[out] value Value of the control
     */
    int (*about)(const struct _media *self, const properties_t **properties);

    /**
     * @brief Determine the compatible capabilities of a stream in the current configuration context.
     *
     * This method queries the capabilities of the specified stream, taking into account the current configuration
     * and dependencies between streams. For input streams, it lists all available capabilities. For output streams,
     * it returns only the capabilities compatible with the current configuration of its dependent input streams.
     *
     * @note This function is stateless and can be called at any time.
     * @param[in] self Instance of the media handle
     * @param[in] name The name of the stream whose compatible capabilities are to be determined
     * @param[out] caps Pointer to receive the stream capabilities
     * @return int Error code indicating the success or failure of the operation.
     *         Returns MEDIA_ERROR_NONE on success.
     */
    int (*query_stream_capabilities)(const struct _media *self, const char *name, capabilities_t **caps);

    /**
     * @brief Get the error information of the media instance.
     * @note This is a private member and should not be called directly by users.
     * It is used internally by the public API to retrieve error details.
     */
    media_error_t (*get_last_error)(const struct _media *self);

    /* =============================================================================
       ============================== Private members ============================== */

    /**
     * @brief Initialize the private context of the handle.
     * @note This is a private member and should not be called directly by users.
     * It is used internally by the public API.
     */
    int (*do_initialize)(const struct _media *self);

    /**
     * @brief Release the private context of the handle.
     * @note This is a private member and should not be called directly by users.
     * It is used internally by the public API.
     */
    int (*do_release)(const struct _media *self);

    /**
     * @brief Prepare the media instance for processing.
     * @note This is a private member and should not be called directly by users.
     * It is used internally by the public API.
     */
    int (*do_prepare)(const struct _media *self);

    /**
     * @brief Finalize the media instance after processing.
     * @note This is a private member and should not be called directly by users.
     * It is used internally by the public API.
     */
    int (*do_finalize)(const struct _media *self);

    /**
     * @brief Get the value of a control by its name
     * @param[in] self Instance of the media handle
     * @param[in] name Name of the control
     * @param[out] value Value of the control
     */
    int (*do_get_control)(const struct _media *self, const char *const name, value_t *value);

    /**
     * @brief Set the value of a control by its name
     * @param[in] self Instance of the media handle
     * @param[in] name Name of the control
     * @param[in] value Value of the control
     */
    int (*do_set_control)(const struct _media *self, const char *name, const value_t value);

    /**
     * @brief Get the capabilities of a given stream
     * @param[in] self Instance of the media handle
     * @param[in] name Name of the stream
     * @param[out] caps List of capabilities
     * @note @p caps is a NULL-terminated array
     */
    int (*do_get_stream_capabilities)(const struct _media *self, const char *const name, const capabilities_t **caps);

    /**
     * @brief Set the desired capabilities of a given stream
     * @param[in] self Instance of the media handle
     * @param[in] name Name of the stream
     * @param[in] caps List of capabilities
     */
    int (*do_set_stream_capabilities)(const struct _media *self, const char *const name, const capabilities_t *caps);

    /**
     * @brief Query memory allocation constraints for input buffers
     * @param[in] self Instance of the media handle
     * @param[in] name Name of the stream
     * @param[out] constraints Memory allocation constraints as properties
     * @note This is a private member and should not be called directly by users.
     * It is used internally by the public API.
     */
    int (*do_query_memory_allocation)(const struct _media *self, const char *const name, properties_t **constraints);

    /**
     * @brief Set the current state of the media instance.
     * @note This is a private member and should not be called directly by users.
     * It is used internally by the public API to update the state.
     */
    int (*set_state)(const struct _media *self, media_state_t state);

    media_state_t state;                       /**< Current state of the media instance. */
    media_state_transition_t state_transition; /**< Current state transition of the media instance. */

} media_t;

/// Private function to set the state of the Media instance
static inline int set_state(media_t *self, media_state_t state) {
    int ret = MEDIA_ERROR_INVALID_PARAMETER;
    if (self != NULL) {
        ret = MEDIA_ERROR_INVALID_STATE;
        media_state_t current = self->state;
        media_state_transition_t transition = MEDIA_STATE_TRANSITION_NONE;
        bool update = false;

        if (current == state) {
            ret = MEDIA_ERROR_NONE;
        } else if ((current == MEDIA_STATE_NULL) && (state == MEDIA_STATE_INITIALIZED)) {
            transition = MEDIA_STATE_TRANSITION_NULL_TO_INITIALIZED;
            update = true;
        } else if ((current == MEDIA_STATE_INITIALIZED) && (state == MEDIA_STATE_PREPARED)) {
            transition = MEDIA_STATE_TRANSITION_INITIALIZED_TO_PREPARED;
            update = true;
        } else if ((current == MEDIA_STATE_PREPARED) && (state == MEDIA_STATE_STREAMING)) {
            transition = MEDIA_STATE_TRANSITION_PREPARED_TO_STREAMING;
            update = true;
        } else if ((current == MEDIA_STATE_STREAMING) && (state == MEDIA_STATE_PREPARED)) {
            transition = MEDIA_STATE_TRANSITION_STREAMING_TO_PREPARED;
            update = true;
        } else if ((current == MEDIA_STATE_PREPARED) && (state == MEDIA_STATE_INITIALIZED)) {
            transition = MEDIA_STATE_TRANSITION_PREPARED_TO_INITIALIZED;
            update = true;
        } else if ((current == MEDIA_STATE_INITIALIZED) && (state == MEDIA_STATE_NULL)) {
            transition = MEDIA_STATE_TRANSITION_INITIALIZED_TO_NULL;
            update = true;
        } else {
            /* Invalid transition - ret remains MEDIA_ERROR_INVALID_STATE */
        }

        if (update) {
            self->state = state;
            self->state_transition = transition;
            ret = MEDIA_ERROR_NONE;
        }
    }
    return ret;
}

/// Public functions

/**
 * @brief Query the current lifecycle state.
 *
 * Returns the current state of the media element. This function is
 * stateless and can be called at any time.
 *
 * @param[in]  self  Pointer to the media instance.
 * @param[out] state Pointer to receive the current @ref media_state_t value.
 *
 * @retval MEDIA_ERROR_NONE              Success.
 * @retval MEDIA_ERROR_INVALID_PARAMETER @p self or @p state is @c NULL.
 *
 * @see media_initialize(), media_prepare(), media_finalize(), media_release()
 */
static inline int media_get_state(const media_t *self, media_state_t *state) {
    int ret = MEDIA_ERROR_INVALID_PARAMETER;
    if ((self != NULL) && (state != NULL)) {
        *state = self->state;
        ret = MEDIA_ERROR_NONE;
    }
    return ret;
}

/**
 * @brief Transition from Null to Initialized.
 *
 * This is the first mandatory step of the media lifecycle. It acquires
 * the resources needed for the media element to operate:
 * - Hardware handles (sensor, accelerator, DMA channel, …)
 * - Internal bookkeeping structures
 *
 * @note Processing framework contexts (OpenCL, CUDA, CPU backend, …)
 *       are set up by the implementation's constructor so that controls
 *       can query hardware capabilities before this call.
 *
 * @param[in,out] self Pointer to the media instance.
 *
 * @pre  State is @c MEDIA_STATE_NULL.
 * @post State is @c MEDIA_STATE_INITIALIZED on success; unchanged on failure.
 *
 * @retval MEDIA_ERROR_NONE              Success.
 * @retval MEDIA_ERROR_INVALID_PARAMETER @p self is @c NULL.
 * @retval MEDIA_ERROR_INVALID_STATE     Instance is not in @c MEDIA_STATE_NULL.
 * @retval MEDIA_ERROR_UNIMPLEMENTED     One or more virtual functions are not set.
 *
 * @see media_release(), media_prepare()
 */
static inline int media_initialize(media_t *self) {
    int ret = MEDIA_ERROR_INVALID_PARAMETER;
    if (self != NULL) {
        media_state_t state;
        int state_ret = media_get_state(self, &state);
        if (state_ret != MEDIA_ERROR_NONE) {
            ret = state_ret;
        } else if ((self->do_initialize == NULL) || (self->do_release == NULL) || (self->do_prepare == NULL) ||
                   (self->do_finalize == NULL) || (self->get_streams == NULL) || (self->get_controls == NULL) ||
                   (self->about == NULL) || (self->query_stream_capabilities == NULL) ||
                   (self->get_last_error == NULL) || (self->do_get_control == NULL) || (self->do_set_control == NULL) ||
                   (self->do_get_stream_capabilities == NULL) || (self->do_set_stream_capabilities == NULL) ||
                   (self->do_query_memory_allocation == NULL)) {
            ret = MEDIA_ERROR_UNIMPLEMENTED;
        } else {
            ret = self->do_initialize(self);
            if (ret == MEDIA_ERROR_NONE) {
                (void)set_state(self, MEDIA_STATE_INITIALIZED);
            }
        }
    }
    return ret;
}

/**
 * @brief Transition from Initialized back to Null.
 *
 * Releases every resource that was set up during media_initialize():
 * - Hardware handles and device connections
 * - Allocated buffers and internal structures
 *
 * After this call the instance returns to its initial state and can be
 * re-initialized with a new call to media_initialize().
 *
 * @param[in,out] self Pointer to the media instance.
 *
 * @pre  State is @c MEDIA_STATE_INITIALIZED (media_finalize() must have
 *       been called first if the instance was previously prepared).
 * @post State is @c MEDIA_STATE_NULL on success; unchanged on failure.
 *
 * @retval MEDIA_ERROR_NONE              Success.
 * @retval MEDIA_ERROR_INVALID_PARAMETER @p self is @c NULL.
 * @retval MEDIA_ERROR_INVALID_STATE     Instance is not in @c MEDIA_STATE_INITIALIZED.
 * @retval MEDIA_ERROR_UNIMPLEMENTED     Virtual function not set.
 *
 * @see media_initialize(), media_finalize()
 */
static inline int media_release(media_t *self) {
    int ret = MEDIA_ERROR_INVALID_PARAMETER;
    if (self != NULL) {
        media_state_t state;
        int state_ret = media_get_state(self, &state);
        if (state_ret != MEDIA_ERROR_NONE) {
            ret = state_ret;
        } else if (self->do_release == NULL) {
            ret = MEDIA_ERROR_UNIMPLEMENTED;
        } else {
            ret = self->do_release(self);
            if (ret == MEDIA_ERROR_NONE) {
                (void)set_state(self, MEDIA_STATE_NULL);
            }
        }
    }
    return ret;
}

/**
 * @brief Apply and validate static controls, then transition from
 *        Initialized to Prepared.
 *
 * During this step the implementation:
 * 1. Validates every **static** control — some are mandatory and the call
 *    fails if they have not been set or hold invalid values.
 * 2. Applies the static control values (e.g. selects an OpenCL device,
 *    configures a processing mode, sets sensor registers).
 * 3. Allocates additional resources that depend on the static
 *    configuration (kernel programs, look-up tables, calibration data, …).
 *
 * All static controls **must** be set via media_set_control() before
 * calling this function. Dynamic controls can still be changed after
 * preparation.
 *
 * @param[in,out] self Pointer to the media instance.
 *
 * @pre  State is @c MEDIA_STATE_INITIALIZED.
 * @pre  All mandatory static controls have been set with valid values.
 * @post State is @c MEDIA_STATE_PREPARED on success; unchanged on failure.
 *
 * @retval MEDIA_ERROR_NONE              Success.
 * @retval MEDIA_ERROR_INVALID_PARAMETER @p self is @c NULL.
 * @retval MEDIA_ERROR_INVALID_STATE     Instance is not in @c MEDIA_STATE_INITIALIZED.
 * @retval MEDIA_ERROR_UNIMPLEMENTED     Virtual function not set.
 *
 * @note This function may block while the implementation compiles GPU
 *       kernels, loads calibration files, or performs other heavyweight
 *       preparation.
 *
 * @see media_finalize(), media_set_control()
 */
static inline int media_prepare(media_t *self) {
    int ret = MEDIA_ERROR_INVALID_PARAMETER;
    if (self != NULL) {
        media_state_t state;
        int state_ret = media_get_state(self, &state);
        if (state_ret != MEDIA_ERROR_NONE) {
            ret = state_ret;
        } else if (self->do_prepare == NULL) {
            ret = MEDIA_ERROR_UNIMPLEMENTED;
        } else {
            ret = self->do_prepare(self);
            if (ret == MEDIA_ERROR_NONE) {
                ret = set_state(self, MEDIA_STATE_PREPARED);
            }
        }
    }
    return ret;
}

/**
 * @brief Undo preparation and transition from Prepared back to Initialized.
 *
 * This is the reverse of media_prepare(). It tears down everything that
 * was set up during preparation:
 * - Compiled GPU kernels and programs
 * - Look-up tables, calibration data
 * - Any resource allocated based on static control values
 *
 * After this call, static controls can be changed again and the instance
 * can be re-prepared with a subsequent call to media_prepare().
 *
 * @param[in,out] self Pointer to the media instance.
 *
 * @pre  State is @c MEDIA_STATE_PREPARED.
 * @post State is @c MEDIA_STATE_INITIALIZED on success; unchanged on failure.
 *
 * @retval MEDIA_ERROR_NONE              Success.
 * @retval MEDIA_ERROR_INVALID_PARAMETER @p self is @c NULL.
 * @retval MEDIA_ERROR_INVALID_STATE     Instance is not in @c MEDIA_STATE_PREPARED.
 * @retval MEDIA_ERROR_UNIMPLEMENTED     Virtual function not set.
 *
 * @note This function may block while the implementation releases GPU
 *       resources or waits for pending operations to complete.
 *
 * @see media_prepare(), media_release()
 */
static inline int media_finalize(media_t *self) {
    int ret = MEDIA_ERROR_INVALID_PARAMETER;
    if (self != NULL) {
        media_state_t state;
        int state_ret = media_get_state(self, &state);
        if (state_ret != MEDIA_ERROR_NONE) {
            ret = state_ret;
        } else if (self->do_finalize == NULL) {
            ret = MEDIA_ERROR_UNIMPLEMENTED;
        } else {
            ret = self->do_finalize(self);
            if (ret == MEDIA_ERROR_NONE) {
                (void)set_state(self, MEDIA_STATE_INITIALIZED);
            }
        }
    }
    return ret;
}

/**
 * @brief Get the version of the media API implemented by this instance.
 *
 * @note This function is stateless and can be called at any time.
 *
 * @param[in]  self  Pointer to the media instance.
 * @param[out] major Pointer to receive the major version number.
 * @param[out] minor Pointer to receive the minor version number.
 * @param[out] patch Pointer to receive the patch version number.
 */
static inline void media_get_version(const media_t *self, uint32_t *major, uint32_t *minor, uint32_t *patch) {
    self->get_version(self, major, minor, patch);
}

/**
 * @brief Retrieve the list of streams available in the media instance.
 *
 * Streams are the input and output interfaces of the media element.
 * Each stream has a name, direction (input or output), and capabilities.
 *
 * @note This function is stateless and can be called at any time.
 * @note Ownership of the returned list is **not** transferred to the
 *       caller; do not free it.
 *
 * @param[in]  self    Pointer to the media instance.
 * @param[out] streams Pointer to receive the @ref streams_t list.
 *
 * @retval MEDIA_ERROR_NONE              Success.
 * @retval MEDIA_ERROR_INVALID_PARAMETER @p self or @p streams is @c NULL.
 * @retval MEDIA_ERROR_UNIMPLEMENTED     Virtual function not set.
 *
 * @see media_get_stream_capabilities(), media_set_stream_capabilities()
 */
static inline int media_get_streams(const media_t *self, const streams_t **streams) {
    int ret = MEDIA_ERROR_INVALID_PARAMETER;
    if ((self != NULL) && (streams != NULL)) {
        if (self->get_streams == NULL) {
            ret = MEDIA_ERROR_UNIMPLEMENTED;
        } else {
            ret = self->get_streams(self, streams);
        }
    }
    return ret;
}

/**
 * @brief Get the current capabilities of a stream.
 *
 * Queries the capabilities associated with the given stream name.
 * This is a stateful function that returns the capabilities currently
 * configured for the stream.
 *
 * @param[in]  self Pointer to the media instance.
 * @param[in]  name Name of the stream (must match a name from
 *                  media_get_streams()).
 * @param[out] caps Pointer to receive the @ref capabilities_t.
 *                  Ownership is not transferred to the caller.
 *
 * @retval MEDIA_ERROR_NONE              Success.
 * @retval MEDIA_ERROR_INVALID_PARAMETER @p self, @p name, or @p caps is @c NULL.
 * @retval MEDIA_ERROR_UNIMPLEMENTED     Virtual function not set.
 *
 * @see media_set_stream_capabilities(), media_get_streams()
 */
static inline int media_get_stream_capabilities(const media_t *self, const char *const name,
                                                const capabilities_t **caps) {
    int ret = MEDIA_ERROR_INVALID_PARAMETER;
    if ((self != NULL) && (name != NULL) && (caps != NULL)) {
        if (self->do_get_stream_capabilities == NULL) {
            ret = MEDIA_ERROR_UNIMPLEMENTED;
        } else {
            ret = self->do_get_stream_capabilities(self, name, caps);
        }
    }
    return ret;
}

/**
 * @brief Set desired capabilities on a stream.
 *
 * Configures the capabilities for the specified stream. The implementation
 * validates that the requested capabilities are compatible with the
 * current configuration.
 *
 * @param[in] self Pointer to the media instance.
 * @param[in] name Name of the stream (must match a name from
 *                 media_get_streams()).
 * @param[in] caps Pointer to the @ref capabilities_t to apply.
 *
 * @retval MEDIA_ERROR_NONE              Success.
 * @retval MEDIA_ERROR_INVALID_PARAMETER @p self, @p name, or @p caps is @c NULL.
 * @retval MEDIA_ERROR_UNIMPLEMENTED     Virtual function not set.
 *
 * @see media_get_stream_capabilities(), media_query_stream_capabilities()
 */
static inline int media_set_stream_capabilities(const media_t *self, const char *const name,
                                                const capabilities_t *caps) {
    int ret = MEDIA_ERROR_INVALID_PARAMETER;
    if ((self != NULL) && (name != NULL) && (caps != NULL)) {
        if (self->do_set_stream_capabilities == NULL) {
            ret = MEDIA_ERROR_UNIMPLEMENTED;
        } else {
            ret = self->do_set_stream_capabilities(self, name, caps);
        }
    }
    return ret;
}

/**
 * @brief Retrieve the list of controls supported by the media instance.
 *
 * Populates @p controls with all controls available. Controls may be
 * static (cannot be changed after media_prepare()) or dynamic (can be
 * changed at any time).
 *
 * @note This function is stateless and can be called at any time.
 * @note Ownership of the returned list is **not** transferred to the
 *       caller; do not free it.
 *
 * @param[in]  self     Pointer to the media instance.
 * @param[out] controls Pointer to receive the @ref controls_t list.
 *
 * @retval MEDIA_ERROR_NONE              Success.
 * @retval MEDIA_ERROR_INVALID_PARAMETER @p self or @p controls is @c NULL.
 * @retval MEDIA_ERROR_UNIMPLEMENTED     Virtual function not set.
 *
 * @see media_get_control(), media_set_control()
 */
static inline int media_get_controls(const media_t *self, const controls_t **controls) {
    int ret = MEDIA_ERROR_INVALID_PARAMETER;
    if ((self != NULL) && (controls != NULL)) {
        if (self->get_controls == NULL) {
            ret = MEDIA_ERROR_UNIMPLEMENTED;
        } else {
            ret = self->get_controls(self, controls);
        }
    }
    return ret;
}

/**
 * @brief Read the current value of a control.
 *
 * Controls can be read as soon as a media instance is available,
 * regardless of the lifecycle state.
 *
 * @param[in]  self  Pointer to the media instance.
 * @param[in]  name  Name of the control (must match a name from
 *                   media_get_controls()).
 * @param[out] value Pointer to a @ref value_t that receives the current
 *                   control value.
 *
 * @retval MEDIA_ERROR_NONE              Success.
 * @retval MEDIA_ERROR_INVALID_PARAMETER @p self, @p name, or @p value is
 *                                       @c NULL.
 * @retval MEDIA_ERROR_NOT_FOUND         No control with name @p name exists.
 * @retval MEDIA_ERROR_UNIMPLEMENTED     Virtual function not set.
 *
 * @see media_set_control(), media_get_controls()
 */
static inline int media_get_control(const media_t *self, const char *const name, value_t *value) {
    int ret = MEDIA_ERROR_INVALID_PARAMETER;
    if ((self != NULL) && (name != NULL) && (value != NULL)) {
        if (self->do_get_control == NULL) {
            ret = MEDIA_ERROR_UNIMPLEMENTED;
        } else {
            ret = self->do_get_control(self, name, value);
            if ((ret == MEDIA_ERROR_NONE) && (value->tid == VTID_INVALID)) {
                ret = MEDIA_ERROR_NOT_FOUND;
            }
        }
    }
    return ret;
}

/**
 * @brief Write a new value to a control.
 *
 * Controls can be set as soon as a media instance is available.
 * Controls come in two flavours:
 *
 * - **Static controls** (@ref CTRL_FLAGS_STATIC) — can be set at any
 *   time *before* media_prepare() is called (i.e. while in
 *   @c MEDIA_STATE_NULL or @c MEDIA_STATE_INITIALIZED). Attempting to
 *   change a static control once the instance is in
 *   @c MEDIA_STATE_PREPARED or later returns @c MEDIA_ERROR_INVALID_STATE.
 *   Some static controls are mandatory: media_prepare() will fail if
 *   they have not been set to a valid value.
 * - **Dynamic controls** (@ref CTRL_FLAGS_DYNAMIC) — can be changed at
 *   any time, regardless of the current state (e.g. gain, exposure,
 *   threshold).
 *
 * @param[in] self  Pointer to the media instance.
 * @param[in] name  Name of the control (must match a name from
 *                  media_get_controls()).
 * @param[in] value The @ref value_t to assign.
 *
 * @retval MEDIA_ERROR_NONE              Success.
 * @retval MEDIA_ERROR_INVALID_PARAMETER @p self or @p name is @c NULL,
 *                                       or @p value has an invalid type.
 * @retval MEDIA_ERROR_INVALID_STATE     @p name is a static control and
 *                                       the instance is already in
 *                                       @c MEDIA_STATE_PREPARED or later.
 * @retval MEDIA_ERROR_NOT_FOUND         No control with name @p name exists.
 * @retval MEDIA_ERROR_UNIMPLEMENTED     Virtual function not set.
 *
 * @see media_get_control(), media_get_controls(), media_prepare()
 */
static inline int media_set_control(const media_t *self, const char *name, const value_t value) {
    int ret = MEDIA_ERROR_INVALID_PARAMETER;
    if ((self != NULL) && (name != NULL)) {
        if ((self->do_set_control == NULL) || (self->get_controls == NULL)) {
            ret = MEDIA_ERROR_UNIMPLEMENTED;
        } else if (value.tid == VTID_INVALID) {
            ret = MEDIA_ERROR_INVALID_PARAMETER;
        } else {
            const controls_t *controls = NULL;
            int ctrl_ret = self->get_controls(self, &controls);
            if (ctrl_ret != MEDIA_ERROR_NONE) {
                ret = ctrl_ret;
            } else {
                const control_t *ctrl = controls_find(controls, name);
                if (ctrl == NULL) {
                    ret = MEDIA_ERROR_NOT_FOUND;
                } else if (((ctrl->flags & CTRL_FLAGS_STATIC) != 0u) &&
                           (self->state >= MEDIA_STATE_PREPARED)) {
                    ret = MEDIA_ERROR_INVALID_STATE;
                } else {
                    ret = self->do_set_control(self, name, value);
                }
            }
        }
    }
    return ret;
}

/**
 * @brief Retrieve element metadata (name, description, version, …).
 *
 * Returns the properties of the media implementation such as:
 * - @c name — Name of the implementation
 * - @c description — Human-readable description
 * - @c version — Implementation version string
 * - @c license — License description
 * - @c url — Project URL
 * - @c opensource — Open-source dependency list
 *
 * @note This function is stateless and can be called at any time.
 * @note Ownership of the returned properties is **not** transferred to
 *       the caller; do not free them.
 *
 * @param[in]  self       Pointer to the media instance.
 * @param[out] properties Pointer to receive the @ref properties_t.
 *
 * @retval MEDIA_ERROR_NONE              Success.
 * @retval MEDIA_ERROR_INVALID_PARAMETER @p self or @p properties is @c NULL.
 * @retval MEDIA_ERROR_UNIMPLEMENTED     Virtual function not set.
 */
static inline int media_about(const media_t *self, const properties_t **properties) {
    int ret = MEDIA_ERROR_INVALID_PARAMETER;
    if ((self != NULL) && (properties != NULL)) {
        if (self->about == NULL) {
            ret = MEDIA_ERROR_UNIMPLEMENTED;
        } else {
            ret = self->about(self, properties);
        }
    }
    return ret;
}

/**
 * @brief Query compatible capabilities in the current configuration.
 *
 * Determines the compatible capabilities of a stream taking into account
 * the current configuration and dependencies between streams:
 * - For **input** streams, lists all available capabilities.
 * - For **output** streams, returns only the capabilities compatible
 *   with the current configuration of its dependent input streams.
 *
 * @note This function is stateless and can be called at any time.
 *
 * @param[in]  self Pointer to the media instance.
 * @param[in]  name Name of the stream (must match a name from
 *                  media_get_streams()).
 * @param[out] caps Pointer to receive the @ref capabilities_t.
 *
 * @retval MEDIA_ERROR_NONE              Success.
 * @retval MEDIA_ERROR_INVALID_PARAMETER @p self, @p name, or @p caps is @c NULL.
 * @retval MEDIA_ERROR_UNIMPLEMENTED     Virtual function not set.
 *
 * @see media_get_stream_capabilities(), media_set_stream_capabilities()
 */
static inline int media_query_stream_capabilities(const media_t *self, const char *name, capabilities_t **caps) {
    int ret = MEDIA_ERROR_INVALID_PARAMETER;
    if ((self != NULL) && (name != NULL) && (caps != NULL)) {
        if (self->query_stream_capabilities == NULL) {
            ret = MEDIA_ERROR_UNIMPLEMENTED;
        } else {
            ret = self->query_stream_capabilities(self, name, caps);
        }
    }
    return ret;
}

/**
 * @brief Query memory allocation constraints for a stream's input buffers.
 *
 * Retrieves the memory allocation constraints required for optimal
 * performance with the specified stream. Applications can use this
 * information to allocate properly aligned buffers, avoiding runtime
 * memory copies.
 *
 * Constraint types supported:
 * - @c memory-alignment — Base memory address alignment (bytes)
 * - @c stride-alignment — Row stride alignment (bytes)
 * - @c size-alignment — Buffer size granularity (bytes)
 * - @c plane-alignment — Plane offset alignment (bytes)
 *
 * @note This function can be called after the instance is initialized.
 * @note In some systems like OpenCL, constraints are device-specific and
 *       can only be queried after the device has been selected by a control.
 *
 * @param[in]  self        Pointer to the media instance.
 * @param[in]  name        Name of the stream.
 * @param[out] constraints Pointer to receive the @ref properties_t
 *                         describing the constraints.
 *
 * @retval MEDIA_ERROR_NONE              Success.
 * @retval MEDIA_ERROR_INVALID_PARAMETER @p self, @p name, or @p constraints
 *                                       is @c NULL.
 * @retval MEDIA_ERROR_UNIMPLEMENTED     Virtual function not set.
 *
 * @see media_get_streams()
 */
static inline int media_query_memory_allocation(const media_t *self, const char *name, properties_t **constraints) {
    int ret = MEDIA_ERROR_INVALID_PARAMETER;
    if ((self != NULL) && (name != NULL) && (constraints != NULL)) {
        if (self->do_query_memory_allocation == NULL) {
            ret = MEDIA_ERROR_UNIMPLEMENTED;
        } else {
            ret = self->do_query_memory_allocation(self, name, constraints);
        }
    }
    return ret;
}

/**
 * @brief Print a human-readable dump of the media element.
 *
 * Writes a summary of the media instance to the provided print function,
 * including the about properties, stream list, and control list.
 *
 * @note This function is stateless and can be called at any time.
 *
 * @param[in] self       Pointer to the media instance.
 * @param[in] print_func Printf-like callback used for output.
 *
 * @see media_about(), media_get_streams(), media_get_controls()
 */
static inline void media_inspect(const media_t *self, int (*print_func)(const char *, ...)) {
    if (self == NULL) {
        (void)print_func("Invalid media instance.\n");
    } else {
        // Print about information
        const properties_t *properties;
        if (self->about(self, &properties) == 0) {
            (void)print_func("About:\n  ");
            properties_inspect(properties, print_func, "\t");
        } else {
            (void)print_func("Failed to get about information.\n");
        }

        // Print streams
        const streams_t *streams;
        if (self->get_streams(self, &streams) == 0) {
            streams_inspect(streams, print_func);
        } else {
            (void)print_func("Failed to get stream list.\n");
        }

        // Print controls
        const controls_t *controls;
        if (self->get_controls(self, &controls) == 0) {
            controls_inspect(controls, print_func);
        } else {
            (void)print_func("Failed to get control list.\n");
        }
    }
}

#ifdef __cplusplus
}
#endif

#endif  // MEDIA_C_H_
