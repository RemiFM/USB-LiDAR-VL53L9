/**
 ******************************************************************************
 * @file    transform.h
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

#ifndef TRANSFORM_C_H_
#define TRANSFORM_C_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "media-c/stream_buffers.h"
#include "media.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file transform.h
 * @brief Public API for the Transform C library.
 *
 * The Transform C API extends the base Media C API with stream-processing
 * capabilities. A @c transform_t handle embeds a @c media_t as its first
 * member, allowing direct reuse of all media lifecycle, control and stream
 * operations. On top of that the Transform API adds:
 *
 * - **Stream dependency queries** – determine which input streams an output
 *   stream depends on.
 * - **Compatible capability queries** – negotiate output capabilities given
 *   constraints from a dependent input stream.
 * - **Stream processing** – push/pull data through the transform.
 *
 * All functions in this header are thin inline wrappers that delegate to
 * the underlying media handle or to the transform-specific virtual
 * function pointers.
 *
 * @section transform_lifecycle Lifecycle Management
 *
 * @ref transform_get_state   — Query the current lifecycle state.
 *
 * @ref transform_initialize  — Transition from @c MEDIA_STATE_NULL to
 *                               @c MEDIA_STATE_INITIALIZED. Acquires
 *                               hardware handles and internal resources.
 *
 * @ref transform_prepare     — Transition from @c MEDIA_STATE_INITIALIZED to
 *                               @c MEDIA_STATE_PREPARED. Validates and applies
 *                               static controls, allocates resources that
 *                               depend on the static configuration.
 *
 * @ref transform_finalize    — Transition from @c MEDIA_STATE_PREPARED back to
 *                               @c MEDIA_STATE_INITIALIZED. Releases resources
 *                               allocated during preparation.
 *
 * @ref transform_release     — Transition from @c MEDIA_STATE_INITIALIZED back
 *                               to @c MEDIA_STATE_NULL. Frees all resources
 *                               acquired during initialization.
 *
 * @section transform_info Information & Inspection
 *
 * @ref transform_about       — Retrieve element metadata (name, description,
 *                               version, license, URL, open-source dependencies).
 *
 * @ref transform_get_version — Get the implemented Transform API version
 *                               (major, minor, patch).
 *
 * @ref transform_inspect     — Print a human-readable dump of the element
 *                               (about, streams, controls) via a printf-like
 *                               callback.
 *
 * @section transform_streams Streams & Capabilities
 *
 * @ref transform_get_streams                  — List all input/output streams.
 *
 * @ref transform_get_stream_capabilities      — Get the current capabilities
 *                                                of a named stream.
 *
 * @ref transform_set_stream_capabilities      — Set desired capabilities on a
 *                                                named stream.
 *
 * @ref transform_query_stream_dependencies    — Query which input streams a
 *                                                given output stream depends on.
 *
 * @ref transform_query_compatible_stream_caps — Query compatible output
 *                                                capabilities given constraints
 *                                                from a dependent input stream.
 *
 * @section transform_ctrls Controls
 *
 * @ref transform_get_controls — List all available controls (static and
 *                                dynamic).
 *
 * @ref transform_get_control  — Read the current value of a control by name.
 *                                Can be called at any time.
 *
 * @ref transform_set_control  — Write a new value to a control by name.
 *                                Static controls can only be set before
 *                                @ref transform_prepare; dynamic controls can
 *                                be changed at any time.
 *
 * @section transform_processing Processing
 *
 * @ref transform_process_stream — Process one iteration of stream buffers
 *                                  through the transform.
 */

/** @brief Transform C API handle, extending the base media handle. */
typedef struct _transform {
    /** @brief Base media handle (inherited). */
    media_t media;

    /**
     * @brief Query the dependencies of a stream
     * @param[in] self Instance of the IPP handle
     * @param[in] name Name of the stream
     * @param[out] dependencies List of dependent streams
     * @note @p dependencies is a NULL-terminated array
     */
    int (*query_stream_dependencies)(const struct _transform *self, const char *name, const strings_t **dependencies);

    /**
     * @brief Query stream capabilities with dependent stream constraints
     * @param[in] self Instance of the transform handle
     * @param[in] name Name of the stream to query capabilities for
     * @param[in] dependent_stream_name Name of the dependent stream
     * @param[in] dependent_stream_caps Capabilities of the dependent stream
     * @param[out] compatible_caps Compatible capabilities for the queried stream
     */
    int (*query_compatible_stream_caps)(const struct _transform *self, const char *name,
                                        const char *dependent_stream_name, const capabilities_t *dependent_stream_caps,
                                        capabilities_t **compatible_caps);

    // Private members
    /**
     * @brief Process a stream
     * @param[in] self Instance of the IPP handle
     * @param[in] input Input stream buffer
     * @param[out] output Output stream buffer
     *
     * @note Some output streams may have multiple dependencies with several input streams, so not necessarily ready
     * to be computed. If an output stream is not ready to be computed due to pending input stream dependencies, its
     * processing is deferred until all dependencies are completed.
     *
     * TODO: how to inform how many output streams are requested?
     *
     */
    int (*do_process_stream)(const struct _transform *self, const stream_buffers_t *stream_buffers);

} transform_t;

/**
 * @brief Transition from Null to Initialized.
 *
 * Delegates to media_initialize() on the embedded media handle.
 * Acquires hardware handles, internal bookkeeping structures, and
 * any resources needed for the transform to operate.
 *
 * @param[in,out] self Pointer to the transform instance.
 *
 * @pre  State is @c MEDIA_STATE_NULL.
 * @post State is @c MEDIA_STATE_INITIALIZED on success; unchanged on failure.
 *
 * @retval MEDIA_ERROR_NONE              Success.
 * @retval MEDIA_ERROR_INVALID_PARAMETER @p self is @c NULL.
 * @retval MEDIA_ERROR_INVALID_STATE     Instance is not in @c MEDIA_STATE_NULL.
 * @retval MEDIA_ERROR_UNIMPLEMENTED     One or more virtual functions are not set.
 *
 * @see transform_release(), transform_prepare()
 */
static inline int transform_initialize(transform_t *self) {
    media_t *media = (media_t *)self;
    return media_initialize(media);
}

/**
 * @brief Transition from Initialized back to Null.
 *
 * Delegates to media_release() on the embedded media handle.
 * Frees every resource acquired during transform_initialize().
 *
 * After this call the instance returns to its initial state and can be
 * re-initialized with a new call to transform_initialize().
 *
 * @param[in,out] self Pointer to the transform instance.
 *
 * @pre  State is @c MEDIA_STATE_INITIALIZED (transform_finalize() must have
 *       been called first if the instance was previously prepared).
 * @post State is @c MEDIA_STATE_NULL on success; unchanged on failure.
 *
 * @retval MEDIA_ERROR_NONE              Success.
 * @retval MEDIA_ERROR_INVALID_PARAMETER @p self is @c NULL.
 * @retval MEDIA_ERROR_INVALID_STATE     Instance is not in @c MEDIA_STATE_INITIALIZED.
 * @retval MEDIA_ERROR_UNIMPLEMENTED     Virtual function not set.
 *
 * @see transform_initialize(), transform_finalize()
 */
static inline int transform_release(transform_t *self) {
    media_t *media = (media_t *)self;
    return media_release(media);
}

/**
 * @brief Apply and validate static controls, then transition from
 *        Initialized to Prepared.
 *
 * Delegates to media_prepare() on the embedded media handle.
 * Validates and applies static controls, then allocates resources
 * that depend on the static configuration (kernel programs,
 * look-up tables, calibration data, …).
 *
 * All static controls **must** be set via transform_set_control()
 * before calling this function.
 *
 * @param[in,out] self Pointer to the transform instance.
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
 * @see transform_finalize(), transform_set_control()
 */
static inline int transform_prepare(transform_t *self) {
    media_t *media = (media_t *)self;
    return media_prepare(media);
}

/**
 * @brief Undo preparation and transition from Prepared back to Initialized.
 *
 * Delegates to media_finalize() on the embedded media handle.
 * Tears down everything that was allocated during transform_prepare():
 * compiled GPU kernels, look-up tables, calibration data, etc.
 *
 * After this call, static controls can be changed again and the instance
 * can be re-prepared with a subsequent call to transform_prepare().
 *
 * @param[in,out] self Pointer to the transform instance.
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
 * @see transform_prepare(), transform_release()
 */
static inline int transform_finalize(transform_t *self) {
    media_t *media = (media_t *)self;
    return media_finalize(media);
}

/**
 * @brief Query the current lifecycle state.
 *
 * Returns the current state of the transform element.
 *
 * @note This function is stateless and can be called at any time.
 *
 * @param[in]  self  Pointer to the transform instance.
 * @param[out] state Pointer to receive the current @ref media_state_t value.
 *
 * @retval MEDIA_ERROR_NONE              Success.
 * @retval MEDIA_ERROR_INVALID_PARAMETER @p self or @p state is @c NULL.
 *
 * @see transform_initialize(), transform_prepare(),
 *      transform_finalize(), transform_release()
 */
static inline int transform_get_state(const transform_t *self, media_state_t *state) {
    int ret = MEDIA_ERROR_INVALID_PARAMETER;
    if ((self != NULL) && (state != NULL)) {
        ret = media_get_state((const media_t *)self, state);
    }
    return ret;
}

/**
 * @brief Get the version of the Transform C API implemented by this instance.
 *
 * Returns the compile-time version constants defined in version.h.
 *
 * @note This function is stateless and can be called at any time.
 *
 * @param[in]  self  Pointer to the transform instance.
 * @param[out] major Pointer to receive the major version number.
 * @param[out] minor Pointer to receive the minor version number.
 * @param[out] patch Pointer to receive the patch version number.
 */
static inline void transform_get_version(const transform_t *self, uint32_t *major, uint32_t *minor, uint32_t *patch) {
    (void)self;
    *major = MEDIA_C_VERSION_MAJOR;
    *minor = MEDIA_C_VERSION_MINOR;
    *patch = MEDIA_C_VERSION_PATCH;
}

/**
 * @brief Retrieve the list of streams available in the transform instance.
 *
 * Delegates to media_get_streams() on the embedded media handle.
 * Streams are the input and output interfaces of the transform element.
 *
 * @note This function is stateless and can be called at any time.
 * @note Ownership of the returned list is **not** transferred to the
 *       caller; do not free it.
 *
 * @param[in]  self    Pointer to the transform instance.
 * @param[out] streams Pointer to receive the @ref streams_t list.
 *
 * @retval MEDIA_ERROR_NONE              Success.
 * @retval MEDIA_ERROR_INVALID_PARAMETER @p self or @p streams is @c NULL.
 * @retval MEDIA_ERROR_UNIMPLEMENTED     Virtual function not set.
 *
 * @see transform_get_stream_capabilities(),
 *      transform_set_stream_capabilities()
 */
static inline int transform_get_streams(const transform_t *self, const streams_t **streams) {
    const media_t *media = (const media_t *)self;
    return media_get_streams(media, streams);
}

/**
 * @brief Get the current capabilities of a stream.
 *
 * Delegates to media_get_stream_capabilities() on the embedded media handle.
 *
 * @param[in]  self Pointer to the transform instance.
 * @param[in]  name Name of the stream (must match a name from
 *                  transform_get_streams()).
 * @param[out] caps Pointer to receive the @ref capabilities_t.
 *                  Ownership is not transferred to the caller.
 *
 * @retval MEDIA_ERROR_NONE              Success.
 * @retval MEDIA_ERROR_INVALID_PARAMETER @p self, @p name, or @p caps is @c NULL.
 * @retval MEDIA_ERROR_UNIMPLEMENTED     Virtual function not set.
 *
 * @see transform_set_stream_capabilities(), transform_get_streams()
 */
static inline int transform_get_stream_capabilities(const transform_t *self, const char *const name,
                                                    const capabilities_t **caps) {
    const media_t *media = (const media_t *)self;
    return media_get_stream_capabilities(media, name, caps);
}

/**
 * @brief Set desired capabilities on a stream.
 *
 * Delegates to media_set_stream_capabilities() on the embedded media handle.
 * The implementation validates that the requested capabilities are compatible
 * with the current configuration.
 *
 * @param[in] self Pointer to the transform instance.
 * @param[in] name Name of the stream (must match a name from
 *                 transform_get_streams()).
 * @param[in] caps Pointer to the @ref capabilities_t to apply.
 *
 * @retval MEDIA_ERROR_NONE              Success.
 * @retval MEDIA_ERROR_INVALID_PARAMETER @p self, @p name, or @p caps is @c NULL.
 * @retval MEDIA_ERROR_UNIMPLEMENTED     Virtual function not set.
 *
 * @see transform_get_stream_capabilities(),
 *      transform_query_compatible_stream_caps()
 */
static inline int transform_set_stream_capabilities(const transform_t *self, const char *const name,
                                                    const capabilities_t *caps) {
    const media_t *media = (const media_t *)self;
    return media_set_stream_capabilities(media, name, caps);
}

/**
 * @brief Retrieve the list of controls supported by the transform instance.
 *
 * Delegates to media_get_controls() on the embedded media handle.
 * Controls may be static (cannot be changed after transform_prepare())
 * or dynamic (can be changed at any time).
 *
 * @note This function is stateless and can be called at any time.
 * @note Ownership of the returned list is **not** transferred to the
 *       caller; do not free it.
 *
 * @param[in]  self     Pointer to the transform instance.
 * @param[out] controls Pointer to receive the @ref controls_t list.
 *
 * @retval MEDIA_ERROR_NONE              Success.
 * @retval MEDIA_ERROR_INVALID_PARAMETER @p self or @p controls is @c NULL.
 * @retval MEDIA_ERROR_UNIMPLEMENTED     Virtual function not set.
 *
 * @see transform_get_control(), transform_set_control()
 */
static inline int transform_get_controls(const transform_t *self, const controls_t **controls) {
    const media_t *media = (const media_t *)self;
    return media_get_controls(media, controls);
}

/**
 * @brief Read the current value of a control.
 *
 * Delegates to media_get_control() on the embedded media handle.
 * Controls can be read as soon as a transform instance is available,
 * regardless of the lifecycle state.
 *
 * @param[in]  self  Pointer to the transform instance.
 * @param[in]  name  Name of the control (must match a name from
 *                   transform_get_controls()).
 * @param[out] value Pointer to a @ref value_t that receives the current
 *                   control value.
 *
 * @retval MEDIA_ERROR_NONE              Success.
 * @retval MEDIA_ERROR_INVALID_PARAMETER @p self, @p name, or @p value is
 *                                       @c NULL.
 * @retval MEDIA_ERROR_NOT_FOUND         No control with name @p name exists.
 * @retval MEDIA_ERROR_UNIMPLEMENTED     Virtual function not set.
 *
 * @see transform_set_control(), transform_get_controls()
 */
static inline int transform_get_control(const transform_t *self, const char *const name, value_t *value) {
    const media_t *media = (const media_t *)self;
    return media_get_control(media, name, value);
}

/**
 * @brief Write a new value to a control.
 *
 * Delegates to media_set_control() on the embedded media handle.
 * Controls can be set as soon as a transform instance is available.
 *
 * - **Static controls** (@ref CTRL_FLAGS_STATIC) — can be set at any
 *   time *before* transform_prepare() is called. Attempting to change
 *   a static control once the instance is in @c MEDIA_STATE_PREPARED
 *   or later returns @c MEDIA_ERROR_INVALID_STATE.
 * - **Dynamic controls** (@ref CTRL_FLAGS_DYNAMIC) — can be changed at
 *   any time, regardless of the current state.
 *
 * @param[in] self  Pointer to the transform instance.
 * @param[in] name  Name of the control (must match a name from
 *                  transform_get_controls()).
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
 * @see transform_get_control(), transform_get_controls(),
 *      transform_prepare()
 */
static inline int transform_set_control(const transform_t *self, const char *name, const value_t value) {
    const media_t *media = (const media_t *)self;
    return media_set_control(media, name, value);
}

/**
 * @brief Retrieve element metadata (name, description, version, …).
 *
 * Delegates to media_about() on the embedded media handle.
 * Returns properties such as name, description, version, license, URL,
 * and open-source dependencies.
 *
 * @note This function is stateless and can be called at any time.
 * @note Ownership of the returned properties is **not** transferred to
 *       the caller; do not free them.
 *
 * @param[in]  self       Pointer to the transform instance.
 * @param[out] properties Pointer to receive the @ref properties_t.
 *
 * @retval MEDIA_ERROR_NONE              Success.
 * @retval MEDIA_ERROR_INVALID_PARAMETER @p self or @p properties is @c NULL.
 * @retval MEDIA_ERROR_UNIMPLEMENTED     Virtual function not set.
 */
static inline int transform_about(const transform_t *self, const properties_t **properties) {
    const media_t *media = (const media_t *)self;
    return media_about(media, properties);
}

/**
 * @brief Process one iteration of stream buffers through the transform.
 *
 * Pushes input stream buffers into the transform and retrieves processed
 * output buffers. Some output streams may depend on multiple input streams;
 * their processing is deferred until all dependencies are satisfied.
 *
 * @param[in] self           Pointer to the transform instance.
 * @param[in] stream_buffers Collection of named @ref stream_buffers_t.
 *
 * @pre  State is @c MEDIA_STATE_PREPARED or @c MEDIA_STATE_STREAMING.
 *
 * @retval MEDIA_ERROR_NONE              Success.
 * @retval MEDIA_ERROR_INVALID_PARAMETER @p self or @p stream_buffers is @c NULL.
 * @retval MEDIA_ERROR_UNIMPLEMENTED     Virtual function not set.
 *
 * @see transform_prepare()
 */
static inline int transform_process_stream(const transform_t *self, const stream_buffers_t *stream_buffers) {
    int ret = MEDIA_ERROR_INVALID_PARAMETER;
    if ((self != NULL) && (stream_buffers != NULL)) {
        if (self->do_process_stream == NULL) {
            ret = MEDIA_ERROR_UNIMPLEMENTED;
        } else {
            ret = self->do_process_stream(self, stream_buffers);
        }
    }
    return ret;
}

/**
 * @brief Query which input streams a given output stream depends on.
 *
 * Returns the list of input stream names that the specified output stream
 * depends on for its processing.
 *
 * @note This function is stateless and can be called at any time.
 * @note Ownership of the returned list is **not** transferred to the
 *       caller; do not free it.
 *
 * @param[in]  self         Pointer to the transform instance.
 * @param[in]  name         Name of the stream to query.
 * @param[out] dependencies Pointer to receive the @ref strings_t list of
 *                          dependent stream names.
 *
 * @retval MEDIA_ERROR_NONE              Success.
 * @retval MEDIA_ERROR_INVALID_PARAMETER @p self, @p name, or @p dependencies
 *                                       is @c NULL.
 * @retval MEDIA_ERROR_UNIMPLEMENTED     Virtual function not set.
 *
 * @see transform_query_compatible_stream_caps(), transform_get_streams()
 */
static inline int transform_query_stream_dependencies(const transform_t *self, const char *name,
                                                      const strings_t **dependencies) {
    int ret = MEDIA_ERROR_INVALID_PARAMETER;
    if ((self != NULL) && (name != NULL) && (dependencies != NULL)) {
        if (self->query_stream_dependencies == NULL) {
            ret = MEDIA_ERROR_UNIMPLEMENTED;
        } else {
            ret = self->query_stream_dependencies(self, name, dependencies);
        }
    }
    return ret;
}

/**
 * @brief Query compatible output capabilities given dependent input
 *        constraints.
 *
 * Given the capabilities of a dependent (input) stream, returns the set of
 * output capabilities that are compatible with those constraints.
 *
 * @note This function is stateless and can be called at any time.
 *
 * @param[in]  self                  Pointer to the transform instance.
 * @param[in]  name                  Name of the stream to query.
 * @param[in]  dependent_stream_name Name of the dependent stream providing
 *                                   constraints.
 * @param[in]  dependent_stream_caps Capabilities of the dependent stream.
 * @param[out] compatible_caps       Pointer to receive the compatible
 *                                   @ref capabilities_t.
 *
 * @retval MEDIA_ERROR_NONE              Success.
 * @retval MEDIA_ERROR_INVALID_PARAMETER Any argument is @c NULL.
 * @retval MEDIA_ERROR_UNIMPLEMENTED     Virtual function not set.
 *
 * @see transform_query_stream_dependencies(),
 *      transform_get_stream_capabilities()
 */
static inline int transform_query_compatible_stream_caps(const transform_t *self, const char *name,
                                                         const char *dependent_stream_name,
                                                         const capabilities_t *dependent_stream_caps,
                                                         capabilities_t **compatible_caps) {
    int ret = MEDIA_ERROR_INVALID_PARAMETER;
    if ((self != NULL) && (name != NULL) && (dependent_stream_name != NULL) && (dependent_stream_caps != NULL) &&
        (compatible_caps != NULL)) {
        if (self->query_compatible_stream_caps == NULL) {
            ret = MEDIA_ERROR_UNIMPLEMENTED;
        } else {
            ret = self->query_compatible_stream_caps(self, name, dependent_stream_name, dependent_stream_caps,
                                                     compatible_caps);
        }
    }
    return ret;
}

/**
 * @brief Print a human-readable dump of the transform element.
 *
 * Delegates to media_inspect() on the embedded media handle.
 * Writes a summary including the about properties, stream list, and
 * control list.
 *
 * @note This function is stateless and can be called at any time.
 *
 * @param[in] self       Pointer to the transform instance.
 * @param[in] print_func Printf-like callback used for output.
 *
 * @see transform_about(), transform_get_streams(),
 *      transform_get_controls()
 */
static inline void transform_inspect(const transform_t *self, int (*print_func)(const char *, ...)) {
    media_inspect((const media_t *)self, print_func);
}

#ifdef __cplusplus
}
#endif

#endif  // TRANSFORM_C_H_
