/**
 ******************************************************************************
 * @file    vl53l9_transform.c
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

#include "vl53l9_transform.h"
#include "algo/flying_pixel.h"
#include "media-c/error.h"
#include "media-c/memory.h"
#include "media-c/properties.h"
#include "media-c/property.h"
#include "media-c/stream_buffer.h"
#include "media-c/stream_buffers.h"
#include "media-c/value.h"
#include "vl53l9-transform-c/about.h"
#include "vl53l9_calib_default.h"
#include "vl53l9_calib_utils.h"
#include "vl53l9_strings.h"

#include "algo/confidence.h"
#include "algo/depth16.h"
#include "algo/distance_calibration.h"
#include "algo/distance_check.h"
#include "algo/dmax.h"
#include "algo/extract.h"
#include "algo/flying_pixel.h"
#include "algo/radial_to_perp.h"
#include "algo/ratenorm.h"
#include "algo/reflectance.h"
#include "algo/sharpener.h"
#include "algo/tnr.h"

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#if VL53L9_TRANSFORM_DEBUG
#include <stdio.h>
#define DEBUG_PRINT(fmt, ...) printf("DEBUG: %s: " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...) // Do nothing if the flag is not set
#endif

// NOTE: in case of memory allocation failure, application should call finalize() to free already allocated resources and avoid memory leaks
// TODO: use more explicit error codes to differentiate between different failure cases (e.g. memory allocation failure, invalid input, etc.)
#define CHECK_MALLOC(ptr)                                                         \
    do {                                                                          \
        if ((ptr) == NULL) {                                                      \
            DEBUG_PRINT("Memory allocation failed at %s:%d", __FILE__, __LINE__); \
            return MEDIA_ERROR_UNKNOWN;                                           \
        }                                                                         \
    } while (0)

#define CTRL_DEFAULT_SPEC { { 0 }, { 0 }, (vtid_t)0 }

#define SIX_STEP_SCALER (2.9f)

#define MAX_DISTANCE_RANGE     (8500u)
#define MAX_DISTANCE_PRECISION (8800u)

#define NB_SHOTS_STEP_1   (0)
#define NB_SHOTS_STEP_4_5 (1)
#define NB_SHOTS_STEP_6   (2)
#define NB_SHOTS_STEP_7   (3)

/* private types */

typedef enum {
    _STREAM_ID_IN_RAW = 0U,
    _STREAM_ID_OUT_DEPTH,
    _STREAM_ID_OUT_AMBIENT,
    _STREAM_ID_OUT_AMPLITUDE,
    _STREAM_ID_OUT_CONFIDENCE,
    _STREAM_ID_OUT_REFLECTANCE,
    _STREAM_ID_OUT_STATUS,
    _STREAM_ID_MAX, // NOTE: keep this entry at the end
} _stream_id_t;

typedef enum {
    _CONTROL_ID_BYPASS_R2P_ALGO = 0U,
    _CONTROL_ID_BYPASS_TNR_ALGO,
    _CONTROL_ID_BYPASS_R2P_FILTER,
    _CONTROL_ID_BYPASS_CONFIDENCE_FILTER,
    _CONTROL_ID_BYPASS_REFLECTANCE_FILTER,
    _CONTROL_ID_BYPASS_SHARPENER_FILTER,
    _CONTROL_ID_BYPASS_FLYING_PIXEL_FILTER,
    _CONTROL_ID_CALIB_BUFFER, // NOTE: this control is mandatory
    _CONTROL_ID_COVER_GLASS,
    _CONTROL_ID_MAX, // NOTE: keep this entry at the end
} _control_id_t;

// NOTE: internal buffers used for processing
typedef enum {

    // extract
    _depth_in = 0,    // float
    _amplitude_in,    // float
    _ambient_in,      // float
    _msb_in,          // bool
    _dss_lut_in,      // unsigned char
    _effective_spads, // float

    // distance_calibration
    _depth_calibrated, // float

    // tnr
    _tnr_depth,           // float
    _tnr_amplitude,       // float
    _tnr_ambient,         // float
    _tnr_msb,             // bool
    _tnr_effective_spads, // float
    _tnr_noise_reduction, // float

    // ratenorm
    _amplitude_ref,         // float
    _amplitude_ref_rad,     // float
    _signal_rate,           // float
    _ambient_rate,          // float
    _ambient_norm,          // float
    _signal_ambient_factor, // float

    // reflectance
    _reflectance,       // float
    _validity_low_refl, // bool

    // radial_to_perp
    _depth_r2p,      // float
    _center_x_r2p,   // float (required by pointcloud)
    _distortion_r2p, // float (required by pointcloud)
    _validity_r2p,   // bool

    // dmax
    _dmax, // float

    // pointcloud
    _pointcloud, // 4 * float per pixel (x, y, z, confidence)

    // sharpener
    _validity_sharpener, // bool
    _sharpener_score,    // float (required by flicker filter)

    // confidence
    _confidence,           // float
    _xtalk_estimated,      // float (required by dmax)
    _threshold_confidence, // float (required by pointcloud and depth16)
    _validity_confidence,  // bool

    // flying_pixel
    _validity_flying_pixel, // bool

    // distance_check
    _depth_out,  // float
    _status_out, // unsigned char

    // depth16
    _depth16_out, // unsigned short (uint16_t)

    _nb_buffers, // keep last

} _buffer_id_t;

typedef struct {
    /* mandatory */
    media_error_t last_error; // TODO: not fully supported yet

    /* custom */
    bool is_first_frame;
    // TODO: should use one single variable to detect which depth pixel format is requested
    bool is_pointcloud_requested;
    bool is_depth16_requested;
    void *buffers[_nb_buffers];
    value_t controls[_CONTROL_ID_MAX];
    const properties_t *properties[_STREAM_ID_MAX];

    /* algo context */
    tnr_context_t tnr;

    /* calibration data */
    vl53l9_calib_data_t calib;
    float *r2p_coeff_map;       // needed by dmax algo
    float *offset_map;          // needed by distance_calibration algo
    float *ref_amp_no_expo;     // needed by ratenorm algo
    float *ref_amp_rad_no_expo; // needed by ratenorm algo
    float *coeff_norm_no_expo;  // needed by ratenorm algo
} _context_t;

typedef struct {
    transform_t transform;
    _context_t ctx;
} _vl53l9_transform_t;

// private functions prototypes

// transform api implementation

static int _get_streams(_vl53l9_transform_t *const self, const streams_t **streams);
static int _get_controls(_vl53l9_transform_t *const self, const controls_t **controls);
static int _about(_vl53l9_transform_t *self, const properties_t **properties);
static int _query_stream_capabilities(_vl53l9_transform_t *self, const char *name, capabilities_t **caps);
static media_error_t _get_last_error(_vl53l9_transform_t *self);

static int _do_initialize(_vl53l9_transform_t *const self);
static int _do_release(_vl53l9_transform_t *const self);
static int _do_prepare(_vl53l9_transform_t *const self);
static int _do_finalize(_vl53l9_transform_t *const self);
static int _do_get_control(_vl53l9_transform_t *const self, const char *const name, value_t *value);
static int _do_set_control(_vl53l9_transform_t *const self, const char *name, const value_t value);
static int _do_get_stream_capabilities(_vl53l9_transform_t *const self, const char *const stream_name,
                                       const capabilities_t **caps);
static int _do_set_stream_capabilities(_vl53l9_transform_t *const self, const char *const stream_name,
                                       const capabilities_t *caps);
static int _do_query_memory_allocation(_vl53l9_transform_t *const self, const char *const name,
                                       properties_t **constraints);

static int _query_stream_dependencies(_vl53l9_transform_t *const self, const char *name,
                                      const strings_t **dependencies);
static int _query_compatible_stream_caps(_vl53l9_transform_t *const self, const char *name,
                                         const char *dependent_stream_name, const capabilities_t *dependent_stream_caps,
                                         capabilities_t **compatible_caps);
static int _do_process_stream(_vl53l9_transform_t *const self, const stream_buffers_t *stream_buffers);

// helpers
static void _extract_metadata(uint8_t *, size_t, vl53l9_metadata_t *);
static int _compute_calibration_maps(_context_t *, uint16_t, size_t, size_t);
static const properties_t *_check_stream_properties(const properties_t *, _stream_id_t);
static bool _check_streams_consistency(const properties_t **cap);
static _stream_id_t _get_stream_id(const char *const);
static void _build_nb_shots(vl53l9_metadata_t *const, uint32_t nb_shots[4]);

// post-processing blocks wrappers
static int _process_extract(_context_t *, vl53l9_metadata_t *, memory_t *);
static int _process_confidence(_context_t *, vl53l9_metadata_t *);
static int _process_distance_calibration(_context_t *, vl53l9_metadata_t *);
static int _process_tnr(_context_t *, vl53l9_metadata_t *);
static int _process_ratenorm(_context_t *, vl53l9_metadata_t *);
static int _process_reflectance(_context_t *, vl53l9_metadata_t *);
static int _process_radial_to_perp(_context_t *, vl53l9_metadata_t *);
static int _process_dmax(_context_t *, vl53l9_metadata_t *);
static int _process_sharpener(_context_t *, vl53l9_metadata_t *);
static int _process_flying_pixel(_context_t *, vl53l9_metadata_t *);
static int _process_distance_check(_context_t *, vl53l9_metadata_t *);
static int _process_pointcloud(_context_t *, vl53l9_metadata_t *);
static int _process_depth16(_context_t *, vl53l9_metadata_t *);
static void _process_free_buffers(_context_t *);

// NOTE: elements defined in this list should match the order of IDs in the enum
static control_t _controls_list[] = {
    { "bypass-r2p-algo",
      CTRL_BYPASS_R2P_ALGO_NICK,
      CTRL_BYPASS_R2P_ALGO_DESCRIPTION,
      _CONTROL_ID_BYPASS_R2P_ALGO,
      { .val.v_bool = false, .tid = VTID_BOOL },
      VTID_BOOL,
      CTRL_FLAGS_READABLE | CTRL_FLAGS_WRITABLE,
      CTRL_DEFAULT_SPEC },
    { "bypass-tnr-algo",
      CTRL_BYPASS_TNR_ALGO_NICK,
      CTRL_BYPASS_TNR_ALGO_DESCRIPTION,
      _CONTROL_ID_BYPASS_TNR_ALGO,
#if (VL53L9_TRANSFORM_LIGHT == 1)
      { .val.v_bool = true, .tid = VTID_BOOL },
#else
      { .val.v_bool = false, .tid = VTID_BOOL },
#endif
      VTID_BOOL,
      CTRL_FLAGS_READABLE | CTRL_FLAGS_WRITABLE,
      CTRL_DEFAULT_SPEC },

    { "bypass-r2p-filter",
      CTRL_BYPASS_R2P_FILTER_NICK,
      CTRL_BYPASS_R2P_FILTER_DESCRIPTION,
      _CONTROL_ID_BYPASS_R2P_FILTER,
      { .val.v_bool = false, .tid = VTID_BOOL },
      VTID_BOOL,
      CTRL_FLAGS_READABLE | CTRL_FLAGS_WRITABLE,
      CTRL_DEFAULT_SPEC },
    { "bypass-conf-filter",
      CTRL_BYPASS_CONFIDENCE_FILTER_NICK,
      CTRL_BYPASS_CONFIDENCE_FILTER_DESCRIPTION,
      _CONTROL_ID_BYPASS_CONFIDENCE_FILTER,
      { .val.v_bool = false, VTID_BOOL },
      VTID_BOOL,
      CTRL_FLAGS_READABLE | CTRL_FLAGS_WRITABLE,
      CTRL_DEFAULT_SPEC },
    { "bypass-refl-filter",
      CTRL_BYPASS_REFLECTANCE_FILTER_NICK,
      CTRL_BYPASS_REFLECTANCE_FILTER_DESCRIPTION,
      _CONTROL_ID_BYPASS_REFLECTANCE_FILTER,
      { .val.v_bool = false, .tid = VTID_BOOL },
      VTID_BOOL,
      CTRL_FLAGS_READABLE | CTRL_FLAGS_WRITABLE,
      CTRL_DEFAULT_SPEC },
    { "bypass-sharpener-filter",
      CTRL_BYPASS_SHARPENER_FILTER_NICK,
      CTRL_BYPASS_SHARPENER_FILTER_DESCRIPTION,
      _CONTROL_ID_BYPASS_SHARPENER_FILTER,
      { .val.v_bool = false, .tid = VTID_BOOL },
      VTID_BOOL,
      CTRL_FLAGS_READABLE | CTRL_FLAGS_WRITABLE,
      CTRL_DEFAULT_SPEC },
    { "bypass-fp-filter",
      CTRL_BYPASS_FLYING_PIXEL_FILTER_NICK,
      CTRL_BYPASS_FLYING_PIXEL_FILTER_DESCRIPTION,
      _CONTROL_ID_BYPASS_FLYING_PIXEL_FILTER,
#if (VL53L9_TRANSFORM_LIGHT == 1)
       { .val.v_bool = true, .tid = VTID_BOOL },
#else
      { .val.v_bool = false, .tid = VTID_BOOL },
#endif
      VTID_BOOL,
      CTRL_FLAGS_READABLE | CTRL_FLAGS_WRITABLE,
      CTRL_DEFAULT_SPEC },
    { "calib-buffer",
      CTRL_CALIB_BUFFER_NICK,
      CTRL_CALIB_BUFFER_DESCRIPTION,
      _CONTROL_ID_CALIB_BUFFER,
      { .val.v_ptr = NULL, .tid = VTID_POINTER },
      VTID_POINTER,
      CTRL_FLAGS_READABLE | CTRL_FLAGS_WRITABLE,
      CTRL_DEFAULT_SPEC },
    { "cover-glass",
      CTRL_COVER_GLASS_NICK,
      CTRL_COVER_GLASS_DESCRIPTION,
      _CONTROL_ID_COVER_GLASS,
      { .val.v_bool = false, VTID_BOOL },
      VTID_BOOL,
      CTRL_FLAGS_READABLE | CTRL_FLAGS_WRITABLE,
      CTRL_DEFAULT_SPEC },
};

// clang-format off
#define PROPERTY_LIST(format, width, height)                          \
    (property_t[]) {                                                  \
        { "format", { .val.v_string = format, .tid = VTID_STRING } }, \
        { "width", { .val.v_uint32 = width, .tid = VTID_UINT32 } },   \
        { "height", { .val.v_uint32 = height, .tid = VTID_UINT32 } }, \
    }

#define STREAM_PROPS(format, width, height)             \
    (properties_t) {                              \
        .items = PROPERTY_LIST(format, width, height),  \
        .size = 3,                                      \
        .capacity = 3,                                  \
        .item_size = sizeof(property_t),                \
    }
// clang-format on

static const char _raw_name[] = "raw";
static const char _depth_name[] = "depth";
static const char _amplitude_name[] = "amplitude";
static const char _ambient_name[] = "ambient";
static const char _confidence_name[] = "confidence";
static const char _reflectance_name[] = "reflectance";
static const char _status_name[] = "status";

#define MAX_OUTPUT_COMPATIBLE_CAPS (3u)

// NOTE: set csi_width to 32 or other aligned value (check that there is no padding introduced from the capture system)
static const streams_t _streams = {
    .items =
        (void *)(const stream_t[]){
            {
                .name = _raw_name,
                .description = STREAM_RAW_DESCRIPTION,
                .direction = DIRECTION_INPUT,
                .capabilities =
                    &(capabilities_t){ .items =
                                           (properties_t *[]){
                                               &STREAM_PROPS("3DMD", 100, 149), &STREAM_PROPS("3DMD", 14842, 1),
                                               &STREAM_PROPS("3DMD", 100, 39), &STREAM_PROPS("3DMD", 3844, 1),
                                               &STREAM_PROPS("3DMD", 100, 18), &STREAM_PROPS("3DMD", 1738, 1),
                                               &STREAM_PROPS("3DMD", 100, 9), &STREAM_PROPS("3DMD", 880, 1),
                                               &STREAM_PROPS("3DMD", 100, 6), &STREAM_PROPS("3DMD", 516, 1),
                                               &STREAM_PROPS("3DMD", 100, 3), &STREAM_PROPS("3DMD", 204, 1),
                                           },
                                       .size = 12,
                                       .capacity = 12,
                                       .item_size = sizeof(properties_t *) },
            },
            {
                .name = _depth_name,
                .description = STREAM_DEPTH_DESCRIPTION,
                .direction = DIRECTION_OUTPUT,
                .capabilities = &(capabilities_t){ .items =
                                                       (properties_t *[]){
                                                           &STREAM_PROPS("ZF32", 54, 42),
                                                           &STREAM_PROPS("ZF32", 24, 20),
                                                           &STREAM_PROPS("ZF32", 18, 14),
                                                           &STREAM_PROPS("ZF32", 12, 10),
                                                           &STREAM_PROPS("ZF32", 8, 6),
                                                           &STREAM_PROPS("ZF32", 4, 4),
                                                           &STREAM_PROPS("ZAPC", 54, 42),
                                                           &STREAM_PROPS("ZAPC", 24, 20),
                                                           &STREAM_PROPS("ZAPC", 18, 14),
                                                           &STREAM_PROPS("ZAPC", 12, 10),
                                                           &STREAM_PROPS("ZAPC", 8, 6),
                                                           &STREAM_PROPS("ZAPC", 4, 4),
                                                           &STREAM_PROPS("ZA16", 54, 42),
                                                           &STREAM_PROPS("ZA16", 24, 20),
                                                           &STREAM_PROPS("ZA16", 18, 14),
                                                           &STREAM_PROPS("ZA16", 12, 10),
                                                           &STREAM_PROPS("ZA16", 8, 6),
                                                           &STREAM_PROPS("ZA16", 4, 4),
                                                       },
                                                   .size = 18,
                                                   .capacity = 18,
                                                   .item_size = sizeof(properties_t *) },
            },
            {
                .name = _ambient_name,
                .description = STREAM_AMBIENT_DESCRIPTION,
                .direction = DIRECTION_OUTPUT,
                .capabilities = &(capabilities_t){ .items =
                                                       (properties_t *[]){
                                                           &STREAM_PROPS("IF32", 54, 42),
                                                           &STREAM_PROPS("IF32", 24, 20),
                                                           &STREAM_PROPS("IF32", 18, 14),
                                                           &STREAM_PROPS("IF32", 12, 10),
                                                           &STREAM_PROPS("IF32", 8, 6),
                                                           &STREAM_PROPS("IF32", 4, 4),
                                                       },
                                                   .size = 6,
                                                   .capacity = 6,
                                                   .item_size = sizeof(properties_t *) },
            },
            {
                .name = _amplitude_name,
                .description = STREAM_AMPLITUDE_DESCRIPTION,
                .direction = DIRECTION_OUTPUT,
                .capabilities = &(capabilities_t){ .items =
                                                       (properties_t *[]){
                                                           &STREAM_PROPS("AF32", 54, 42),
                                                           &STREAM_PROPS("AF32", 24, 20),
                                                           &STREAM_PROPS("AF32", 18, 14),
                                                           &STREAM_PROPS("AF32", 12, 10),
                                                           &STREAM_PROPS("AF32", 8, 6),
                                                           &STREAM_PROPS("AF32", 4, 4),
                                                       },
                                                   .size = 6,
                                                   .capacity = 6,
                                                   .item_size = sizeof(properties_t *) },
            },
            {
                .name = _confidence_name,
                .description = STREAM_CONFIDENCE_DESCRIPTION,
                .direction = DIRECTION_OUTPUT,
                .capabilities = &(capabilities_t){ .items =
                                                       (properties_t *[]){
                                                           &STREAM_PROPS("CF32", 54, 42),
                                                           &STREAM_PROPS("CF32", 24, 20),
                                                           &STREAM_PROPS("CF32", 18, 14),
                                                           &STREAM_PROPS("CF32", 12, 10),
                                                           &STREAM_PROPS("CF32", 8, 6),
                                                           &STREAM_PROPS("CF32", 4, 4),
                                                       },
                                                   .size = 6,
                                                   .capacity = 6,
                                                   .item_size = sizeof(properties_t *) },
            },
            {
                .name = _reflectance_name,
                .description = STREAM_REFLECTANCE_DESCRIPTION,
                .direction = DIRECTION_OUTPUT,
                .capabilities = &(capabilities_t){ .items =
                                                       (properties_t *[]){
                                                           &STREAM_PROPS("RF32", 54, 42),
                                                           &STREAM_PROPS("RF32", 24, 20),
                                                           &STREAM_PROPS("RF32", 18, 14),
                                                           &STREAM_PROPS("RF32", 12, 10),
                                                           &STREAM_PROPS("RF32", 8, 6),
                                                           &STREAM_PROPS("RF32", 4, 4),
                                                       },
                                                   .size = 6,
                                                   .capacity = 6,
                                                   .item_size = sizeof(properties_t *) },
            },
            {
                .name = _status_name,
                .description = STREAM_STATUS_DESCRIPTION,
                .direction = DIRECTION_OUTPUT,
                .capabilities = &(capabilities_t){ .items =
                                                       (properties_t *[]){
                                                           &STREAM_PROPS("CU32", 54, 42),
                                                           &STREAM_PROPS("CU32", 24, 20),
                                                           &STREAM_PROPS("CU32", 18, 14),
                                                           &STREAM_PROPS("CU32", 12, 10),
                                                           &STREAM_PROPS("CU32", 8, 6),
                                                           &STREAM_PROPS("CU32", 4, 4),
                                                       },
                                                   .size = 6,
                                                   .capacity = 6,
                                                   .item_size = sizeof(properties_t *) },
            } },
    .size = _STREAM_ID_MAX,
    .capacity = _STREAM_ID_MAX,
    .item_size = sizeof(stream_t)
};

static const controls_t _controls = { .items = _controls_list,
                                      .size = sizeof(_controls_list) / sizeof(_controls_list[0]),
                                      .capacity = sizeof(_controls_list) / sizeof(_controls_list[0]),
                                      .item_size = sizeof(control_t) };

// TODO: to be moved to about.h.in template, retrieve information from the build system
static const properties_t _about_props = {
    .items =
        (void *)(const property_t[]){ { "name", { .val.v_string = "vl53l9-transform-c", VTID_STRING } },
                                      { "description", { .val.v_string = "VL53L9 Transform library", VTID_STRING } },
                                      { "version", { .val.v_string = VL53L9_TRANSFORM_C_VERSION, VTID_STRING } } },
    .size = 3,
    .capacity = 3,
    .item_size = sizeof(property_t)
};

// NOTE: these symbols are defined to allow dynamic load of the library
#ifdef EXPORT_CREATE_DESTROY
media_t *media_create() {
    return (media_t *)vl53l9_transform_create();
}

void media_destroy(media_t *self) {
    vl53l9_transform_destroy((transform_t *)self);
}
#endif

transform_t *vl53l9_transform_create(void) {
    _vl53l9_transform_t *vl53l9_transform = (_vl53l9_transform_t *)malloc(sizeof(_vl53l9_transform_t));
    if (vl53l9_transform == NULL) {
        DEBUG_PRINT("Failed to allocate memory for transform instance");
        return NULL;
    }

    *vl53l9_transform = (_vl53l9_transform_t) {
        .transform = {
            .media = {
                /* public*/
                .get_version = (void (*)(const media_t*, uint32_t*, uint32_t*, uint32_t*))transform_get_version,
                .get_streams = (int (*)(const media_t*, const streams_t**))_get_streams,
                .get_controls = (int (*)(const struct _media *, const controls_t**))_get_controls,
                .about = (int (*)(const struct _media *, const properties_t**))_about,
                .query_stream_capabilities = (int (*)(const struct _media *, const char *, capabilities_t **))_query_stream_capabilities,
                .get_last_error = (media_error_t (*)(const struct _media *))_get_last_error,

                /* private */
                .do_initialize = (int (*)(const media_t*))_do_initialize,
                .do_release = (int (*)(const media_t*))_do_release,
                .do_prepare = (int (*)(const media_t*))_do_prepare,
                .do_finalize = (int (*)(const media_t*))_do_finalize,
                .do_get_control = (int (*)(const media_t*, const char*, value_t*))_do_get_control,
                .do_set_control = (int (*)(const media_t*, const char*, const value_t))_do_set_control,
                .do_get_stream_capabilities = (int (*)(const struct _media *, const char *const, const capabilities_t**))_do_get_stream_capabilities,
                .do_set_stream_capabilities = (int (*)(const struct _media *, const char *const, const capabilities_t*))_do_set_stream_capabilities,
                .do_query_memory_allocation = (int (*)(const struct _media *, const char *const, properties_t **))_do_query_memory_allocation,
            },
            .query_stream_dependencies = (int (*)(const transform_t*, const char *, const strings_t**))_query_stream_dependencies,
            .query_compatible_stream_caps = (int (*)(const transform_t*, const char *, const char *, const capabilities_t *, capabilities_t **))_query_compatible_stream_caps,
            .do_process_stream = (int (*)(const transform_t*, const stream_buffers_t *))_do_process_stream,
        }
    };

    return (transform_t *)vl53l9_transform;
}

void vl53l9_transform_destroy(transform_t *self) {
    _vl53l9_transform_t *vl53l9_transform = (_vl53l9_transform_t *)self;

    // free transform instance
    free(vl53l9_transform);
}

static int _do_initialize(_vl53l9_transform_t *self) {

    DEBUG_PRINT("Enter");
    _context_t *ctx = &self->ctx;
    ctx->last_error = (media_error_t){ .code = MEDIA_ERROR_NONE, .message = NULL };
    ctx->is_first_frame = true; // used to detect first frame in the processing pipeline
    ctx->is_pointcloud_requested = false;
    ctx->is_depth16_requested = false;

    // copy default values from global controls list to instance internal context
    for (size_t i = 0; i < _controls.size; i++) {
        control_t *ctrl = (control_t *)list_get((list_t *)&_controls, i);
        ctx->controls[ctrl->quark] = ctrl->value;
    }

    // reset capabilities to empty list of properties for each stream
    // NOTE: capabilities must be explicitly set by the user for each requested stream
    for (size_t i = 0; i < (size_t)_STREAM_ID_MAX; i++) {
        ctx->properties[i] = NULL;
    }

    // reset internal buffers used during stream processing
    for (size_t i = 0; i < (size_t)_nb_buffers; i++) {
        ctx->buffers[i] = NULL;
    }

    // reset algo contexts
    ctx->tnr = (tnr_context_t){ 0 };

    // reset calib data pointers
    ctx->r2p_coeff_map = NULL;
    ctx->offset_map = NULL;
    ctx->ref_amp_no_expo = NULL;
    ctx->ref_amp_rad_no_expo = NULL;
    ctx->coeff_norm_no_expo = NULL;

    DEBUG_PRINT("Exit");
    return MEDIA_ERROR_NONE;
}

static int _do_release(_vl53l9_transform_t *self) {
    DEBUG_PRINT("Enter");
    (void)self;

    // TODO: free resources allocated during initialization

    DEBUG_PRINT("Exit");
    return MEDIA_ERROR_NONE;
}

static int _do_prepare(_vl53l9_transform_t *self) {
    DEBUG_PRINT("Enter");

    _context_t *ctx = &self->ctx;

    // make sure that mandatory controls have been set, otherwise return error
    uint8_t *calib_buffer = (uint8_t *)ctx->controls[_CONTROL_ID_CALIB_BUFFER].val.v_ptr;

    // apply default values if control is not set
    if (calib_buffer == NULL) {
        vl53l9_calib_default_apply(&ctx->calib);
        DEBUG_PRINT("Using default calibration data");
    } else {
        // extract calibration data from buffers if all controls are set
        vl53l9_calib_utils_parse_data(calib_buffer, &ctx->calib);
    }

    DEBUG_PRINT("Exit");
    return MEDIA_ERROR_NONE;
}

static int _do_finalize(_vl53l9_transform_t *self) {
    DEBUG_PRINT("Enter");

    _context_t *ctx = &self->ctx;
    ctx->is_first_frame = true;

    // make sure that all resources allocated in process_stream are freed
    _process_free_buffers(ctx);

    if (ctx->r2p_coeff_map != NULL) {
        free(ctx->r2p_coeff_map);
        ctx->r2p_coeff_map = NULL;
    }

    if (ctx->offset_map != NULL) {
        free(ctx->offset_map);
        ctx->offset_map = NULL;
    }

    if (ctx->ref_amp_no_expo != NULL) {
        free(ctx->ref_amp_no_expo);
        ctx->ref_amp_no_expo = NULL;
    }

    if (ctx->ref_amp_rad_no_expo != NULL) {
        free(ctx->ref_amp_rad_no_expo);
        ctx->ref_amp_rad_no_expo = NULL;
    }

    if (ctx->coeff_norm_no_expo != NULL) {
        free(ctx->coeff_norm_no_expo);
        ctx->coeff_norm_no_expo = NULL;
    }

    if (ctx->controls[_CONTROL_ID_BYPASS_TNR_ALGO].val.v_bool == false) {
        // NOTE: only dynamic alloction is supported for the moment
        vl53l9_algo_tnr_destroy_dynamic_context(ctx->tnr, free);
        // TODO: add error handling

        ctx->tnr = (tnr_context_t){ 0 };
    }

    DEBUG_PRINT("Exit");
    return MEDIA_ERROR_NONE;
}

static int _do_get_control(_vl53l9_transform_t *self, const char *const name, value_t *const value) {
    DEBUG_PRINT("Enter");
    _context_t *ctx = &self->ctx;

    for (size_t i = 0; i < _controls.size; i++) {
        control_t *ctrl = (control_t *)list_get((list_t *)&_controls, i);
        if (strcmp(ctrl->name, name) == 0) {
            *value = ctx->controls[i];
            DEBUG_PRINT("Exit");
            return MEDIA_ERROR_NONE;
        }
    }
    DEBUG_PRINT("Control not found");
    return MEDIA_ERROR_INVALID_PARAMETER;
}

static int _do_set_control(_vl53l9_transform_t *self, const char *name, const value_t value) {
    DEBUG_PRINT("Enter");
    _context_t *ctx = &self->ctx;

    for (size_t i = 0; i < _controls.size; i++) {
        control_t *ctrl = (control_t *)list_get((list_t *)&_controls, i);
        if (strcmp(ctrl->name, name) == 0) {
            ctx->controls[i] = value; // NOTE: this assumes that elements in the list are in the same order as the enum
            DEBUG_PRINT("Exit");
            return MEDIA_ERROR_NONE;
        }
    }
    DEBUG_PRINT("Control not found");
    return MEDIA_ERROR_INVALID_PARAMETER;
}

// TODO: set capabilities to const to avoid modification (to avoid copying them as well)
static int _do_get_stream_capabilities(_vl53l9_transform_t *self, const char *const stream_name,
                                       const capabilities_t **caps) {

    DEBUG_PRINT("Enter");
    (void)self; // unused parameter

    _stream_id_t stream_id = _get_stream_id(stream_name);
    if (stream_id == _STREAM_ID_MAX) {
        DEBUG_PRINT("Invalid stream name");
        return MEDIA_ERROR_INVALID_PARAMETER;
    }

    if (caps) {
        *caps = streams_get(&_streams, (uint32_t)stream_id)->capabilities;
    } else {
        DEBUG_PRINT("Invalid caps pointer");
        return MEDIA_ERROR_INVALID_PARAMETER;
    }

    DEBUG_PRINT("Exit");
    return MEDIA_ERROR_NONE;
}

static int _do_set_stream_capabilities(_vl53l9_transform_t *self, const char *const stream_name,
                                       const capabilities_t *caps) {
    DEBUG_PRINT("Enter");
    _context_t *ctx = &self->ctx;

    // NOTE: this implementation supports only one capability (list of properties) per stream
    if (caps->size != 1u) {
        DEBUG_PRINT("Invalid capability size, only one capability supported per stream");
        return MEDIA_ERROR_INVALID_PARAMETER;
    }

    // retrieve stream id
    _stream_id_t stream_id = _get_stream_id(stream_name);
    if (stream_id >= _STREAM_ID_MAX) {
        DEBUG_PRINT("Invalid stream name");
        return MEDIA_ERROR_INVALID_PARAMETER;
    }

    // check if raw input stream capabilities have been set before setting output ones
    if (stream_id != _STREAM_ID_IN_RAW) {
        if (ctx->properties[_STREAM_ID_IN_RAW] == NULL) {
            DEBUG_PRINT("Raw input stream capabilities not set yet");
            return MEDIA_ERROR_INVALID_STATE;
        }
    }

    // check capability validity and store it in the internal context
    properties_t *user_props = *capabilities_get(caps, 0);
    const properties_t *requested_props = _check_stream_properties(user_props, stream_id);
    if (requested_props) {
        ctx->properties[stream_id] = requested_props;

        if (stream_id == _STREAM_ID_OUT_DEPTH) {
            const char *depth_format = properties_find(requested_props, "format")->value.val.v_string;
            if (strcmp(depth_format, "ZAPC") == 0) {
                ctx->is_pointcloud_requested = true;
                ctx->is_depth16_requested = false;
            } else if (strcmp(depth_format, "ZA16") == 0) {
                ctx->is_pointcloud_requested = false;
                ctx->is_depth16_requested = true;
            } else {
                ctx->is_pointcloud_requested = false;
                ctx->is_depth16_requested = false;
            }
        }

        DEBUG_PRINT("Format: %s, width: %d, height: %d", properties_find(requested_props, "format")->value.val.v_string,
                    properties_find(requested_props, "width")->value.val.v_uint32,
                    properties_find(requested_props, "height")->value.val.v_uint32);
    } else {
        DEBUG_PRINT("Invalid capabilities");
        return MEDIA_ERROR_INVALID_PARAMETER;
    }

    if (_check_streams_consistency(ctx->properties) == false) {
        DEBUG_PRINT("Inconsistent streams capabilities");
        return MEDIA_ERROR_INVALID_STATE;
    }

    DEBUG_PRINT("Exit");
    return MEDIA_ERROR_NONE;
}

static int _get_streams(_vl53l9_transform_t *self, const streams_t **streams) {
    DEBUG_PRINT("Enter");
    (void)self;
    *streams = &_streams;
    DEBUG_PRINT("Exit");
    return MEDIA_ERROR_NONE;
}

static int _get_controls(_vl53l9_transform_t *self, const controls_t **controls) {
    DEBUG_PRINT("Enter");
    (void)self;
    *controls = &_controls;
    DEBUG_PRINT("Exit");
    return MEDIA_ERROR_NONE;
}

static int _about(_vl53l9_transform_t *self, const properties_t **properties) {
    DEBUG_PRINT("Enter");
    (void)self;
    *properties = &_about_props;
    DEBUG_PRINT("Exit");
    return -0;
}

// TODO: once implemented, add compilation check on VL53L9_TRANSFORM_LIGHT
static int _query_stream_capabilities(_vl53l9_transform_t *self, const char *name, capabilities_t **caps) {
    (void)self;
    (void)name;
    (void)caps;
    return MEDIA_ERROR_UNIMPLEMENTED; // TODO: implement this function
}

#if (VL53L9_TRANSFORM_LIGHT == 1)
static int _query_stream_dependencies(_vl53l9_transform_t *const self, const char *name,
                                      const strings_t **dependencies) {
    (void)self;
    (void)name;
    (void)dependencies;
    return MEDIA_ERROR_UNIMPLEMENTED;
}
#else
static const strings_t _raw_dependencies = { .items = (void *)(const char *const[]){ _depth_name, _amplitude_name,
                                                                                     _ambient_name, _confidence_name,
                                                                                     _reflectance_name, _status_name },
                                             .size = 6,
                                             .capacity = 6,
                                             .item_size = sizeof(const char *) };

static const strings_t _outputs_dependencies = {
    .items = (void *)(const char *const[]){ _raw_name }, .size = 1, .capacity = 1, .item_size = sizeof(const char *)
};

static int _query_stream_dependencies(_vl53l9_transform_t *const self, const char *name,
                                      const strings_t **dependencies) {
    (void)self;

    if ((dependencies == NULL) || (name == NULL)) {
        return MEDIA_ERROR_INVALID_PARAMETER;
    }

    if (strcmp(name, _raw_name) == 0) {
        *dependencies = &_raw_dependencies;
    } else if ((strcmp(name, _depth_name) == 0) || (strcmp(name, _amplitude_name) == 0) ||
               (strcmp(name, _ambient_name) == 0) || (strcmp(name, _confidence_name) == 0) ||
               (strcmp(name, _reflectance_name) == 0) || (strcmp(name, _status_name) == 0)) {
        *dependencies = &_outputs_dependencies;
    } else {
        return MEDIA_ERROR_INVALID_PARAMETER;
    }
    return MEDIA_ERROR_NONE;
}
#endif

static int _do_process_stream(_vl53l9_transform_t *self, const stream_buffers_t *stream_buffers) {

    DEBUG_PRINT("Enter");
    int ret = MEDIA_ERROR_NONE;

    // retrieve private context associated with the current instance
    _context_t *ctx = &self->ctx;

    // retrieve input and output buffers
    stream_buffer_t *input_stream_buffer = stream_buffers_find(stream_buffers, _raw_name);
    stream_buffer_t *distance_stream_buffer = stream_buffers_find(stream_buffers, _depth_name);
    stream_buffer_t *amplitude_stream_buffer = stream_buffers_find(stream_buffers, _amplitude_name);
    stream_buffer_t *ambient_stream_buffer = stream_buffers_find(stream_buffers, _ambient_name);
    stream_buffer_t *confidence_stream_buffer = stream_buffers_find(stream_buffers, _confidence_name);
    stream_buffer_t *reflectance_stream_buffer = stream_buffers_find(stream_buffers, _reflectance_name);
    stream_buffer_t *status_stream_buffer = stream_buffers_find(stream_buffers, _status_name);

    // TODO: these flags should be stored in the context and used to determine which outputs need to be computed
    bool is_distance_output_requested = distance_stream_buffer != NULL;
    bool is_amplitude_output_requested = amplitude_stream_buffer != NULL;
    bool is_ambient_output_requested = ambient_stream_buffer != NULL;
    bool is_confidence_output_requested = confidence_stream_buffer != NULL;
    bool is_reflectance_output_requested = reflectance_stream_buffer != NULL;
    bool is_status_output_requested = status_stream_buffer != NULL;

    // TODO: return error if no output stream is requested

    // make sure capabilities have been previously set for each requested output stream
    if (input_stream_buffer == NULL) {
        DEBUG_PRINT("Raw stream not provided");
        return MEDIA_ERROR_INVALID_STATE;
    }
    if (is_distance_output_requested && (ctx->properties[_STREAM_ID_OUT_DEPTH] == NULL)) {
        DEBUG_PRINT("Depth stream is requested but capabilities are not set");
        return MEDIA_ERROR_INVALID_STATE;
    }
    if (is_amplitude_output_requested && (ctx->properties[_STREAM_ID_OUT_AMPLITUDE] == NULL)) {
        DEBUG_PRINT("Amplitude stream is requested but capabilities are not set");
        return MEDIA_ERROR_INVALID_STATE;
    }
    if (is_ambient_output_requested && (ctx->properties[_STREAM_ID_OUT_AMBIENT] == NULL)) {
        DEBUG_PRINT("Ambient stream is requested but capabilities are not set");
        return MEDIA_ERROR_INVALID_STATE;
    }
    if (is_confidence_output_requested && (ctx->properties[_STREAM_ID_OUT_CONFIDENCE] == NULL)) {
        DEBUG_PRINT("Confidence stream is requested but capabilities are not set");
        return MEDIA_ERROR_INVALID_STATE;
    }
    if (is_reflectance_output_requested && (ctx->properties[_STREAM_ID_OUT_REFLECTANCE] == NULL)) {
        DEBUG_PRINT("Reflectance stream is requested but capabilities are not set");
        return MEDIA_ERROR_INVALID_STATE;
    }
    if (is_status_output_requested && (ctx->properties[_STREAM_ID_OUT_STATUS] == NULL)) {
        DEBUG_PRINT("Status stream is requested but capabilities are not set");
        return MEDIA_ERROR_INVALID_STATE;
    }

    // TODO: make sure that the input buffer size is consistent with the provided capabilities

    // parse status line to extract metadata
    vl53l9_metadata_t meta;
    // TODO: check list size and returned pointer validity
    memory_t *input_memory = memories_get(input_stream_buffer->buffer.memories, 0);
    _extract_metadata(input_memory->data, input_memory->size, &meta);

    size_t width = (meta.crop_enable != 0u) ? meta.crop_x_size : meta.frame_width;
    size_t height = (meta.crop_enable != 0u) ? meta.crop_y_size : meta.frame_height;
    size_t resolution = width * height;

    // NOTE: calibration maps are allocated and computed during the first frame processing
    if (ctx->is_first_frame) {

        ctx->r2p_coeff_map = malloc(resolution * sizeof(float));
        ctx->offset_map = malloc(resolution * sizeof(float));
        ctx->ref_amp_no_expo = malloc(resolution * sizeof(float));
        ctx->ref_amp_rad_no_expo = malloc(resolution * sizeof(float));
        ctx->coeff_norm_no_expo = malloc(resolution * sizeof(float));

        CHECK_MALLOC(ctx->r2p_coeff_map);
        CHECK_MALLOC(ctx->offset_map);
        CHECK_MALLOC(ctx->ref_amp_no_expo);
        CHECK_MALLOC(ctx->ref_amp_rad_no_expo);
        CHECK_MALLOC(ctx->coeff_norm_no_expo);

        ret = _compute_calibration_maps(ctx, meta.binning, width, height);
        if (ret != MEDIA_ERROR_NONE) {
            DEBUG_PRINT("Failed to compute calibration maps");
            return ret;
        }

        if (ctx->controls[_CONTROL_ID_BYPASS_TNR_ALGO].val.v_bool == false) {
            // NOTE: only dynamic alloction is supported for the moment
            // reset flag is already set when creating the algo context
            ctx->tnr = vl53l9_algo_tnr_create_dynamic_context(resolution, malloc, free);
            // TODO: add error handling
        }

        if (ctx->is_pointcloud_requested && ctx->controls[_CONTROL_ID_BYPASS_R2P_ALGO].val.v_bool) {
            DEBUG_PRINT("Pointcloud output requested but r2p algo is bypassed, forcing algo execution");
            ctx->controls[_CONTROL_ID_BYPASS_R2P_ALGO].val.v_bool = false;
        }

        ctx->is_first_frame = false;
    }

    ret = _process_extract(ctx, &meta, input_memory);
    if (ret != MEDIA_ERROR_NONE) {
        DEBUG_PRINT("Failed to extract data from input buffer");
        return ret;
    }

    ret = _process_distance_calibration(ctx, &meta);
    if (ret != MEDIA_ERROR_NONE) {
        DEBUG_PRINT("Failed to apply distance calibration");
        return ret;
    }

    ret = _process_tnr(ctx, &meta);
    if (ret != MEDIA_ERROR_NONE) {
        DEBUG_PRINT("Failed to apply temporal noise reduction");
        return ret;
    }

    ret = _process_confidence(ctx, &meta);
    if (ret != MEDIA_ERROR_NONE) {
        DEBUG_PRINT("Failed to compute confidence");
        return ret;
    }

    ret = _process_ratenorm(ctx, &meta);
    if (ret != MEDIA_ERROR_NONE) {
        DEBUG_PRINT("Failed to apply rate normalization");
        return ret;
    }

    ret = _process_reflectance(ctx, &meta);
    if (ret != MEDIA_ERROR_NONE) {
        DEBUG_PRINT("Failed to compute reflectance");
        return ret;
    }

    ret = _process_radial_to_perp(ctx, &meta);
    if (ret != MEDIA_ERROR_NONE) {
        DEBUG_PRINT("Failed to apply radial to perpendicular correction");
        return ret;
    }

    ret = _process_dmax(ctx, &meta);
    if (ret != MEDIA_ERROR_NONE) {
        DEBUG_PRINT("Failed to compute dmax");
        return ret;
    }

    ret = _process_sharpener(ctx, &meta);
    if (ret != MEDIA_ERROR_NONE) {
        DEBUG_PRINT("Failed to apply sharpener filter");
        return ret;
    }

    ret = _process_flying_pixel(ctx, &meta);
    if (ret != MEDIA_ERROR_NONE) {
        DEBUG_PRINT("Failed to apply flying pixel filter");
        return ret;
    }

    ret = _process_distance_check(ctx, &meta);
    if (ret != MEDIA_ERROR_NONE) {
        DEBUG_PRINT("Failed to apply distance check");
        return ret;
    }

    ret = _process_pointcloud(ctx, &meta);
    if (ret != MEDIA_ERROR_NONE) {
        DEBUG_PRINT("Failed to compute pointcloud");
        return ret;
    }

    ret = _process_depth16(ctx, &meta);
    if (ret != MEDIA_ERROR_NONE) {
        DEBUG_PRINT("Failed to compute depth16");
        return ret;
    }

    // fill output data if data is requested

    memory_t *output_memory = NULL;

    // TODO: check list size and returned pointer validity
    // TODO: make sure memories are big enough to hold the data
    if (is_distance_output_requested) {
        output_memory = memories_get(distance_stream_buffer->buffer.memories, 0);
        if (ctx->is_pointcloud_requested) {
            (void)memcpy(output_memory->data, ctx->buffers[_pointcloud], resolution * 4u * sizeof(float));
        } else if (ctx->is_depth16_requested) {
            (void)memcpy(output_memory->data, ctx->buffers[_depth16_out], resolution * sizeof(uint16_t));
        } else {
            (void)memcpy(output_memory->data, ctx->buffers[_depth_out], resolution * sizeof(float));
        }
    }
    if (is_amplitude_output_requested) {
        output_memory = memories_get(amplitude_stream_buffer->buffer.memories, 0);
        (void)memcpy(output_memory->data, ctx->buffers[_signal_rate], resolution * sizeof(float));
    }
    if (is_ambient_output_requested) {
        output_memory = memories_get(ambient_stream_buffer->buffer.memories, 0);
        (void)memcpy(output_memory->data, ctx->buffers[_ambient_rate], resolution * sizeof(float));
    }
    if (is_confidence_output_requested) {
        output_memory = memories_get(confidence_stream_buffer->buffer.memories, 0);
        (void)memcpy(output_memory->data, ctx->buffers[_confidence], resolution * sizeof(float));
    }
    if (is_reflectance_output_requested) {
        output_memory = memories_get(reflectance_stream_buffer->buffer.memories, 0);
        (void)memcpy(output_memory->data, ctx->buffers[_reflectance], resolution * sizeof(float));
    }
    if (is_status_output_requested) {
        output_memory = memories_get(status_stream_buffer->buffer.memories, 0);
        // NOTE: need to copy data element by element to convert from uint8_t to uint32_t
        uint8_t *src = (uint8_t *)ctx->buffers[_status_out];
        uint32_t *dst = (uint32_t *)output_memory->data;

        for (size_t i = 0; i < resolution; i++) {
            dst[i] = (uint32_t)(src[i]);
        }
    }

    // free intermediate buffers
    _process_free_buffers(ctx);

    DEBUG_PRINT("Exit");
    return MEDIA_ERROR_NONE;
}

static int _retrieve_output_size(const size_t in_width, const size_t in_height, size_t *out_width, size_t *out_height) {
    if (((in_width == 100u) && (in_height == 149u)) || ((in_width == 14842u) && (in_height == 1u))) {
        *out_width = 54u;
        *out_height = 42u;
    } else if (((in_width == 100u) && (in_height == 39u)) || ((in_width == 3844u) && (in_height == 1u))) {
        *out_width = 24u;
        *out_height = 20u;
    } else if (((in_width == 100u) && (in_height == 18u)) || ((in_width == 1738u) && (in_height == 1u))) {
        *out_width = 18u;
        *out_height = 14u;
    } else if (((in_width == 100u) && (in_height == 9u)) || ((in_width == 880u) && (in_height == 1u))) {
        *out_width = 12u;
        *out_height = 10u;
    } else if (((in_width == 100u) && (in_height == 6u)) || ((in_width == 516u) && (in_height == 1u))) {
        *out_width = 8u;
        *out_height = 6u;
    } else if (((in_width == 100u) && (in_height == 3u)) || ((in_width == 204u) && (in_height == 1u))) {
        *out_width = 4u;
        *out_height = 4u;
    } else {
        return MEDIA_ERROR_INVALID_PARAMETER;
    }
    return MEDIA_ERROR_NONE;
}

#if (VL53L9_TRANSFORM_LIGHT == 1)
static int _query_compatible_stream_caps(_vl53l9_transform_t *const self, const char *name,
                                         const char *dependent_stream_name, const capabilities_t *dependent_stream_caps,
                                         capabilities_t **compatible_caps) {

    (void)self;
    (void)name;
    (void)dependent_stream_name;
    (void)dependent_stream_caps;
    (void)compatible_caps;
    return MEDIA_ERROR_UNIMPLEMENTED;
}
#else
static int get_compatible_output_caps(size_t in_width, size_t in_height, _stream_id_t out_id,
                                      capabilities_t **compatible_caps) {
    size_t out_width = 0, out_height = 0;
    int err;

    err = _retrieve_output_size(in_width, in_height, &out_width, &out_height);
    if (err != MEDIA_ERROR_NONE) {
        return err;
    }

    capabilities_t *out_supported_caps = streams_get(&_streams, (size_t)out_id)->capabilities;
    if (out_supported_caps == NULL) {
        return MEDIA_ERROR_INVALID_STATE;
    }

    capabilities_t *ret = (capabilities_t *)malloc(sizeof(capabilities_t));
    CHECK_MALLOC(ret);

    // Pre-allocation to avoid double parsing of matching caps
    // TODO: double parsing ?
    properties_t **items = (properties_t **)malloc(MAX_OUTPUT_COMPATIBLE_CAPS * sizeof(properties_t *));
    CHECK_MALLOC(items);

    size_t match_count = 0;
    size_t idx = 0;
    for (size_t i = 0; i < out_supported_caps->size; i++) {
        properties_t *props = *capabilities_get(out_supported_caps, i);
        property_t *w_prop = properties_find(props, "width");
        property_t *h_prop = properties_find(props, "height");
        if ((w_prop == NULL) || (h_prop == NULL)) {
            continue;
        }
        if ((w_prop->value.val.v_uint32 == out_width) && (h_prop->value.val.v_uint32 == out_height)) {
            match_count++;
            if (match_count > MAX_OUTPUT_COMPATIBLE_CAPS) {
                DEBUG_PRINT("Pre allocation of MAX_OUTPUT_COMPATIBLE_CAPS is not enough");
                return MEDIA_ERROR_UNKNOWN;
            }
            items[idx++] = props;
        }
    }

    if (match_count == 0u) {
        return MEDIA_ERROR_NOT_FOUND;
    }

    ret->items = items;
    ret->size = match_count;
    ret->capacity = match_count;
    ret->item_size = sizeof(properties_t *);

    *compatible_caps = ret;
    return MEDIA_ERROR_NONE;
}

// NOTE: this function allocates memory that should be freed by the caller
static int _query_compatible_stream_caps(_vl53l9_transform_t *const self, const char *name,
                                         const char *dependent_stream_name, const capabilities_t *dependent_stream_caps,
                                         capabilities_t **compatible_caps) {
    if ((self == NULL) || (name == NULL) || (dependent_stream_name == NULL) || (dependent_stream_caps == NULL) ||
        (compatible_caps == NULL)) {
        return MEDIA_ERROR_INVALID_PARAMETER;
    }

    if (dependent_stream_caps->size != 1u) {
        return MEDIA_ERROR_INVALID_PARAMETER;
    }

    // TODO: implement output->input queries ?
    // For now, return only outputs compatible caps, other direction unused.
    if (strcmp(dependent_stream_name, _raw_name) != 0) {
        if ((strcmp(name, _depth_name) == 0) || (strcmp(name, _amplitude_name) == 0) ||
            (strcmp(name, _ambient_name) == 0) || (strcmp(name, _confidence_name) == 0) ||
            (strcmp(name, _reflectance_name) == 0) || (strcmp(name, _status_name) == 0)) {
            return MEDIA_ERROR_UNIMPLEMENTED;
        }
        return MEDIA_ERROR_INVALID_PARAMETER;
    }
    if ((strcmp(name, _depth_name) != 0) && (strcmp(name, _amplitude_name) != 0) &&
        (strcmp(name, _ambient_name) != 0) && (strcmp(name, _confidence_name) != 0) &&
        (strcmp(name, _reflectance_name) != 0) && (strcmp(name, _status_name) != 0)) {
        if (strcmp(name, _raw_name) == 0) {
            return MEDIA_ERROR_UNIMPLEMENTED;
        }
        return MEDIA_ERROR_INVALID_PARAMETER;
    }

    properties_t *dependent_props = *capabilities_get(dependent_stream_caps, 0);
    if (dependent_props == NULL) {
        return MEDIA_ERROR_INVALID_PARAMETER;
    }

    property_t *dep_w_prop = properties_find(dependent_props, "width");
    property_t *dep_h_prop = properties_find(dependent_props, "height");
    if ((dep_w_prop == NULL) || (dep_h_prop == NULL)) {
        return MEDIA_ERROR_INVALID_PARAMETER;
    }
    size_t dep_width = dep_w_prop->value.val.v_uint32;
    size_t dep_height = dep_h_prop->value.val.v_uint32;
    _stream_id_t id = _get_stream_id(name);

    return get_compatible_output_caps(dep_width, dep_height, id, compatible_caps);
}
#endif

static int _do_query_memory_allocation(_vl53l9_transform_t *const self, const char *const name,
                                       properties_t **constraints) {
    // Basic implementation - for VL53L9, we can provide default memory allocation constraints
    // This is a simplified implementation that can be extended based on actual requirements

    if ((self == NULL) || (name == NULL) || (constraints == NULL)) {
        return MEDIA_ERROR_INVALID_PARAMETER;
    }

    // For now, return empty constraints (to be expanded based on actual memory requirements)
    *constraints = NULL;

    return MEDIA_ERROR_UNIMPLEMENTED;
}

static media_error_t _get_last_error(_vl53l9_transform_t *self) {
    _context_t *ctx = &self->ctx;
    DEBUG_PRINT("Enter");
    DEBUG_PRINT("Last error code: %d", self->ctx.last_error.code);
    DEBUG_PRINT("Exit");
    return ctx->last_error;
}

/* private functions */

static void _extract_metadata(uint8_t *buffer, size_t size, vl53l9_metadata_t *metadata) {

    uint32_t offset = size - sizeof(vl53l9_metadata_t);
    (void)memcpy(metadata, &buffer[offset], sizeof(vl53l9_metadata_t));
}

static int _compute_calibration_maps(_context_t *ctx, uint16_t binning, size_t width, size_t height) {

    int ret = 0;

    // offset map
    // NOTE: offset map should match input frame size assuming that crop is done at the end of the pipe
    // reorder calibration map (from columns by columns to rows by rows) and convert to float
    float reordered_offset_map[54u * 42u] = { 0 };
    float global_offset = (float)ctx->calib.global_offset;

    for (size_t i = 0; i < 54u; i++) {
        for (size_t j = 0; j < 42u; j++) {
            reordered_offset_map[(54u * j) + i] = (float)ctx->calib.distance_offset[(42u * i) + j] + global_offset;
        }
    }

    // skip bicubic resize if the frame size is the same as the calibration map (nominal binning x2)
    if ((width == 54u) && (height == 42u)) {
        (void)memcpy(ctx->offset_map, reordered_offset_map, 54u * 42u * sizeof(float));
    } else {
        const float bicubic_coeff = -0.75f;
        (void)vl53l9_algo_ratenorm_bicubic_resize(reordered_offset_map, ctx->offset_map, 54, 42, width, height,
                                                  bicubic_coeff);
    }

    // compute rad2perp coeff map
    radial_to_perp_params_t r2p_params = { 0 };
    vl53l9_algo_radial_to_perp_init_default_params(&r2p_params);
    r2p_params.residual_offset_x = ctx->calib.residual_offset_x;
    r2p_params.residual_offset_y = ctx->calib.residual_offset_y;
    r2p_params.max_distance = MAX_DISTANCE_PRECISION;
    r2p_params.parallax_correction = false;

    float *r2p_1mm_map = malloc(width * height * sizeof(float));
    CHECK_MALLOC(r2p_1mm_map);

    for (size_t i = 0; i < (width * height); i++) {
        r2p_1mm_map[i] = 1.0f;
    }

    ret = vl53l9_algo_radial_to_perp(/* input */
                                     r2p_1mm_map,

                                     /* output */
                                     ctx->r2p_coeff_map, NULL, NULL, NULL,

                                     /* parameters */
                                     &r2p_params, width, height, binning);

    if (ret != 0) {
        DEBUG_PRINT("Failed to compute radial to perpendicular map");
        free(r2p_1mm_map);
        return -1;
    }

    // compute ratenorm maps
    ratenorm_params_t ratenorm_params = { 0 };
    vl53l9_algo_ratenorm_init_default_params(&ratenorm_params);
    ratenorm_params.fast_mode = true;
    ratenorm_params.ref_scaler = ctx->calib.amplitude_scaler;
    ratenorm_params.ref_distance = ctx->calib.amplitude_distance;
    ratenorm_params.ref_reflectance = ctx->calib.amplitude_reflectance;
    ratenorm_params.ref_expo = ctx->calib.amplitude_exposure;

    // NOTE: amplitude_coeffs from calib are not reordered since only the max value is needed
    // TODO: temporary workaround to convert amplitude coeffs to float (to be removed when algo signature is updated)
    float *reference_coeffs = malloc(AMP_COEFFS_NB * sizeof(float));
    CHECK_MALLOC(reference_coeffs);

    for (size_t i = 0; i < AMP_COEFFS_NB; i++) {
        reference_coeffs[i] = (float)ctx->calib.amplitude_coeffs[i];
    }

    ret =
        vl53l9_algo_ratenorm_compute_norm_maps(/* input */
                                               reference_coeffs, ctx->r2p_coeff_map,

                                               /* output */
                                               ctx->ref_amp_no_expo, ctx->ref_amp_rad_no_expo, ctx->coeff_norm_no_expo,

                                               /* parameters */
                                               &ratenorm_params, width, height, binning);

    // free temporary buffers memory
    free(r2p_1mm_map);
    free(reference_coeffs); // TODO: temporary (to be removed when ratenorm algo is updated)

    if (ret != 0) {
        DEBUG_PRINT("Failed to compute ratenorm maps");
        return -1;
    }

    return 0;
}

static _stream_id_t _get_stream_id(const char *const stream_name) {

    if (strcmp(stream_name, _raw_name) == 0) {
        return _STREAM_ID_IN_RAW;
    } else if (strcmp(stream_name, _depth_name) == 0) {
        return _STREAM_ID_OUT_DEPTH;
    } else if (strcmp(stream_name, _ambient_name) == 0) {
        return _STREAM_ID_OUT_AMBIENT;
    } else if (strcmp(stream_name, _amplitude_name) == 0) {
        return _STREAM_ID_OUT_AMPLITUDE;
    } else if (strcmp(stream_name, _confidence_name) == 0) {
        return _STREAM_ID_OUT_CONFIDENCE;
    } else if (strcmp(stream_name, _reflectance_name) == 0) {
        return _STREAM_ID_OUT_REFLECTANCE;
    } else if (strcmp(stream_name, _status_name) == 0) {
        return _STREAM_ID_OUT_STATUS;
    } else {
        DEBUG_PRINT("Invalid stream name");
        return _STREAM_ID_MAX;
    }
}

static const properties_t *_check_stream_properties(const properties_t *provided_props, _stream_id_t id) {

    capabilities_t *supported_cap_list = NULL;

    switch (id) {
    case _STREAM_ID_IN_RAW:
    case _STREAM_ID_OUT_DEPTH:
    case _STREAM_ID_OUT_AMBIENT:
    case _STREAM_ID_OUT_AMPLITUDE:
    case _STREAM_ID_OUT_CONFIDENCE:
    case _STREAM_ID_OUT_REFLECTANCE:
    case _STREAM_ID_OUT_STATUS:
        supported_cap_list = streams_get(&_streams, (size_t)id)->capabilities;
        DEBUG_PRINT("supported_cap_list size: %d", supported_cap_list->size);
        DEBUG_PRINT("provided_props size: %d", provided_props->size);
        break;
    default:
        DEBUG_PRINT("Invalid stream id");
        break;
    }

    if (supported_cap_list == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < supported_cap_list->size; i++) {

        // NOTE: this implementation makes use only of one list of properties per stream
        const properties_t *supported_props = *capabilities_get(supported_cap_list, i);

        if (supported_props->size != provided_props->size) {
            continue;
        }

        // make sure provided format, width and height properties are supported
        property_t *supported_format = properties_find(supported_props, "format");
        property_t *provided_format = properties_find(provided_props, "format");
        if ((supported_format == NULL) || (provided_format == NULL)) {
            DEBUG_PRINT("Format property not found");
            return NULL;
        } else if (strcmp(supported_format->value.val.v_string, provided_format->value.val.v_string) != 0) {
            continue;
        }

        property_t *supported_width = properties_find(supported_props, "width");
        property_t *provided_width = properties_find(provided_props, "width");
        if ((supported_width == NULL) || (provided_width == NULL)) {
            DEBUG_PRINT("Width property not found");
            return NULL;
        } else if (supported_width->value.val.v_uint32 != provided_width->value.val.v_uint32) {
            continue;
        }

        property_t *supported_height = properties_find(supported_props, "height");
        property_t *provided_height = properties_find(provided_props, "height");
        if ((supported_height == NULL) || (provided_height == NULL)) {
            DEBUG_PRINT("Height property not found");
            return NULL;
        } else if (supported_height->value.val.v_uint32 != provided_height->value.val.v_uint32) {
            continue;
        }

        // if a configuration matching the provided one has been found, return it
        DEBUG_PRINT("Matching configuration found, index: %d", i);
        return supported_props;
    }

    // no matching configuration has been found
    return NULL;
}

static bool _check_streams_consistency(const properties_t **cap) {

    size_t in_width, in_height;
    size_t out_width, out_height;

    // retrieve width and height associated with the input stream
    in_width = properties_find(cap[_STREAM_ID_IN_RAW], "width")->value.val.v_uint32;
    in_height = properties_find(cap[_STREAM_ID_IN_RAW], "height")->value.val.v_uint32;

    if (_retrieve_output_size(in_width, in_height, &out_width, &out_height)) {
        DEBUG_PRINT("Invalid input stream size");
        return false;
    }

    // check consistency of output streams if set
    for (size_t id = 0; id < (size_t)_STREAM_ID_MAX; id++) {
        // TODO: filter streams by direction instead of using switch
        switch (id) {
        case _STREAM_ID_OUT_DEPTH:
        case _STREAM_ID_OUT_AMBIENT:
        case _STREAM_ID_OUT_AMPLITUDE:
        case _STREAM_ID_OUT_CONFIDENCE:
        case _STREAM_ID_OUT_REFLECTANCE:
        case _STREAM_ID_OUT_STATUS: {
            if (cap[id] == NULL) {
                continue;
            }
            uint32_t cap_width = properties_find(cap[id], "width")->value.val.v_uint32;
            uint32_t cap_height = properties_find(cap[id], "height")->value.val.v_uint32;
            if ((cap_width != out_width) || (cap_height != out_height)) {
                DEBUG_PRINT("Output stream size mismatch");
                return false;
            }
            break;
        }
        default:
            break;
        }
    }

    return true;
}

static void _build_nb_shots(vl53l9_metadata_t *const meta, uint32_t nb_shots[4]) {

    nb_shots[0] = ((uint32_t)meta->nb_shot_step1_lsb) | ((uint32_t)meta->nb_shot_step1_mid << 8) |
                  ((uint32_t)meta->nb_shot_step1_msb << 16);
    nb_shots[1] = ((uint32_t)meta->nb_shot_step4_5_lsb) | ((uint32_t)meta->nb_shot_step4_5_mid << 8) |
                  ((uint32_t)meta->nb_shot_step4_5_msb << 16);
    nb_shots[2] = ((uint32_t)meta->nb_shot_step6_lsb) | ((uint32_t)meta->nb_shot_step6_mid << 8) |
                  ((uint32_t)meta->nb_shot_step6_msb << 16);
    nb_shots[3] = ((uint32_t)meta->nb_shot_step7_lsb) | ((uint32_t)meta->nb_shot_step7_mid << 8) |
                  ((uint32_t)meta->nb_shot_step7_msb << 16);
}

static float _compute_max_spads(vl53l9_calib_data_t *const calib, vl53l9_metadata_t *const meta) {

    float max_dss_coeff = 0.0f;
    float *dss_coeffs = (meta->nb_step == 6u) ? calib->dss_long_effective_spad : calib->dss_short_effective_spad;

    for (uint8_t i = 0; i < DSS_COEFFS_NB; i++) {
        if (max_dss_coeff < dss_coeffs[i]) {
            max_dss_coeff = dss_coeffs[i];
        }
    }

    return max_dss_coeff * (float)meta->binning * (float)meta->binning / 4.0f;
}

/* postprocessing components wrappers */

// predecessors: none
static int _process_extract(_context_t *ctx, vl53l9_metadata_t *meta, memory_t *input) {

    size_t resolution = (meta->crop_enable != 0u) ? ((size_t)meta->crop_x_size * (size_t)meta->crop_y_size)
                                                  : ((size_t)meta->frame_width * (size_t)meta->frame_height);

    // prepare inputs
    const unsigned char *raw_in = (const unsigned char *)input->data;
    const float *dss_coeffs_in =
        (meta->nb_step == 6u) ? ctx->calib.dss_long_effective_spad : ctx->calib.dss_short_effective_spad;

    // prepare outputs
    ctx->buffers[_depth_in] = malloc(resolution * sizeof(float));
    ctx->buffers[_amplitude_in] = malloc(resolution * sizeof(float));
    ctx->buffers[_ambient_in] = malloc(resolution * sizeof(float));
    ctx->buffers[_msb_in] = malloc(resolution * sizeof(bool));
    ctx->buffers[_dss_lut_in] = malloc(resolution * sizeof(unsigned char));
    ctx->buffers[_effective_spads] = malloc(resolution * sizeof(float));

    CHECK_MALLOC(ctx->buffers[_depth_in]);
    CHECK_MALLOC(ctx->buffers[_amplitude_in]);
    CHECK_MALLOC(ctx->buffers[_ambient_in]);
    CHECK_MALLOC(ctx->buffers[_msb_in]);
    CHECK_MALLOC(ctx->buffers[_dss_lut_in]);
    CHECK_MALLOC(ctx->buffers[_effective_spads]);

    float *depth = (float *)ctx->buffers[_depth_in];
    float *amplitude = (float *)ctx->buffers[_amplitude_in];
    float *ambient = (float *)ctx->buffers[_ambient_in];
    bool *msb = (bool *)ctx->buffers[_msb_in];
    unsigned char *dss_lut_id = (unsigned char *)ctx->buffers[_dss_lut_in];
    float *effective_spads = (float *)ctx->buffers[_effective_spads];

    return vl53l9_algo_extract(/* input */
                               raw_in, dss_coeffs_in,

                               /* output */
                               depth, amplitude, ambient, msb, dss_lut_id, effective_spads,

                               /* parameters */
                               meta->frame_width, meta->frame_height, (bool)meta->crop_enable, meta->crop_x_offset,
                               meta->crop_y_offset, meta->crop_x_size, meta->crop_y_size, meta->binning);
}

// predecessors: extract
static int _process_confidence(_context_t *ctx, vl53l9_metadata_t *meta) {

    size_t resolution = (meta->crop_enable != 0u) ? ((size_t)meta->crop_x_size * (size_t)meta->crop_y_size)
                                                  : ((size_t)meta->frame_width * (size_t)meta->frame_height);

    // compute exposures from metadata
    uint32_t nb_shots[4]; // steps 1, 4-5, 6, 7
    _build_nb_shots(meta, nb_shots);

    // prepare parameters
    confidence_params_t params = { 0 };
    vl53l9_algo_confidence_init_default_params(&params);
    params.cover_glass = ctx->controls[_CONTROL_ID_COVER_GLASS].val.v_bool;
    params.xtalk_coeff = 0.9f;

    // prepare input
    const float *ambient_in = (const float *)ctx->buffers[_tnr_ambient];
    const float *amplitude_in = (const float *)ctx->buffers[_tnr_amplitude];
    const bool *msb_in = (const bool *)ctx->buffers[_tnr_msb];
    const float *effective_spads_in = (const float *)ctx->buffers[_tnr_effective_spads];
    const float *noise_reduction_in = (const float *)ctx->buffers[_tnr_noise_reduction];

    // prepare output
    ctx->buffers[_confidence] = malloc(resolution * sizeof(float));
    ctx->buffers[_validity_confidence] = malloc(resolution * sizeof(bool));
    ctx->buffers[_threshold_confidence] = malloc(resolution * sizeof(float));
    ctx->buffers[_xtalk_estimated] = malloc(resolution * sizeof(float));

    CHECK_MALLOC(ctx->buffers[_confidence]);
    CHECK_MALLOC(ctx->buffers[_validity_confidence]);
    CHECK_MALLOC(ctx->buffers[_threshold_confidence]);
    CHECK_MALLOC(ctx->buffers[_xtalk_estimated]);

    float *confidence = (float *)ctx->buffers[_confidence];
    float *threshold_confidence = (float *)ctx->buffers[_threshold_confidence];
    bool *validity_confidence = (bool *)ctx->buffers[_validity_confidence];
    float *xtalk_estimated = (float *)ctx->buffers[_xtalk_estimated];

    return vl53l9_algo_confidence(/* input */
                                  ambient_in, amplitude_in, msb_in, effective_spads_in, noise_reduction_in,

                                  /* output */
                                  confidence, threshold_confidence, validity_confidence, xtalk_estimated,

                                  /* parameters */
                                  &params, resolution, meta->nb_step, meta->ambient_attenuation, nb_shots);
}

// predecessors: extract
static int _process_distance_calibration(_context_t *ctx, vl53l9_metadata_t *meta) {

    size_t resolution = (meta->crop_enable != 0u) ? ((size_t)meta->crop_x_size * (size_t)meta->crop_y_size)
                                                  : ((size_t)meta->frame_width * (size_t)meta->frame_height);

    // prepare params
    distance_calibration_params_t params = { 0 };
    vl53l9_algo_distance_calibration_init_default_params(&params);
    params.nlc_mode = 1;
    // NOTE: when using experimental nlc_mode, then ratenorm must be executed before distance calibration

    // prepare input
    const float *depth_in = (const float *)ctx->buffers[_depth_in];
    const unsigned char *dss_lut_in = (const unsigned char *)ctx->buffers[_dss_lut_in];

    // prepare output
    ctx->buffers[_depth_calibrated] = malloc(resolution * sizeof(float));
    CHECK_MALLOC(ctx->buffers[_depth_calibrated]);
    float *depth_calibrated = (float *)ctx->buffers[_depth_calibrated];

    return vl53l9_algo_distance_calibration(/* input */
                                            depth_in, ctx->offset_map, dss_lut_in,

                                            /* output */
                                            depth_calibrated,

                                            /* parameters */
                                            &params, resolution, meta->nb_step);
}

// predecessors: distance calibration
static int _process_tnr(_context_t *ctx, vl53l9_metadata_t *meta) {

    size_t width = (meta->crop_enable != 0u) ? meta->crop_x_size : meta->frame_width;
    size_t height = (meta->crop_enable != 0u) ? meta->crop_y_size : meta->frame_height;
    size_t resolution = width * height;

    // if bypass enable point filtered outputs to raw inputs
    if (ctx->controls[_CONTROL_ID_BYPASS_TNR_ALGO].val.v_bool) {
        // allocate memory for output buffers and then copy previous algo data
        ctx->buffers[_tnr_depth] = malloc(resolution * sizeof(float));
        ctx->buffers[_tnr_amplitude] = malloc(resolution * sizeof(float));
        ctx->buffers[_tnr_ambient] = malloc(resolution * sizeof(float));
        ctx->buffers[_tnr_msb] = malloc(resolution * sizeof(bool));
        ctx->buffers[_tnr_effective_spads] = malloc(resolution * sizeof(float));
        ctx->buffers[_tnr_noise_reduction] = NULL;

        CHECK_MALLOC(ctx->buffers[_tnr_depth]);
        CHECK_MALLOC(ctx->buffers[_tnr_amplitude]);
        CHECK_MALLOC(ctx->buffers[_tnr_ambient]);
        CHECK_MALLOC(ctx->buffers[_tnr_msb]);
        CHECK_MALLOC(ctx->buffers[_tnr_effective_spads]);

        (void)memcpy(ctx->buffers[_tnr_depth], ctx->buffers[_depth_calibrated], resolution * sizeof(float));
        (void)memcpy(ctx->buffers[_tnr_amplitude], ctx->buffers[_amplitude_in], resolution * sizeof(float));
        (void)memcpy(ctx->buffers[_tnr_ambient], ctx->buffers[_ambient_in], resolution * sizeof(float));
        (void)memcpy(ctx->buffers[_tnr_msb], ctx->buffers[_msb_in], resolution * sizeof(bool));
        (void)memcpy(ctx->buffers[_tnr_effective_spads], ctx->buffers[_effective_spads], resolution * sizeof(float));

        return 0;
    }

    // prepare parameters
    tnr_params_t params = { 0 };
    vl53l9_algo_tnr_init_default_params(&params);
    params.ref_amplitude_ch1_long = meta->ref_amplitude_ch1_long;
    params.ref_amplitude_ch2_long = meta->ref_amplitude_ch2_long;
    params.ref_amplitude_ch1_short = meta->ref_amplitude_ch1_short;
    params.ref_amplitude_ch2_short = meta->ref_amplitude_ch2_short;
    params.system.pulse_width = (meta->nb_step == 6u) ? 2.6f : 1.3f;
    params.system.window_last_step = (meta->nb_step == 6u) ? 8.0f : 4.0f;

    // compute exposures from metadata
    uint32_t nb_shots[4];
    _build_nb_shots(meta, nb_shots);
    uint32_t current_expo_0 = nb_shots[0];
    uint32_t current_expo_1 = nb_shots[1];
    uint32_t current_expo_2 = nb_shots[2];
    uint32_t current_expo_3 = nb_shots[3];

    // prepare inputs
    const float *depth_in = (const float *)ctx->buffers[_depth_calibrated];
    const float *amplitude_in = (const float *)ctx->buffers[_amplitude_in];
    const float *ambient_in = (const float *)ctx->buffers[_ambient_in];
    const bool *msb_in = (const bool *)ctx->buffers[_msb_in];
    const float *effective_spads_in = (const float *)ctx->buffers[_effective_spads];

    // prepare outputs
    ctx->buffers[_tnr_depth] = malloc(resolution * sizeof(float));
    ctx->buffers[_tnr_amplitude] = malloc(resolution * sizeof(float));
    ctx->buffers[_tnr_ambient] = malloc(resolution * sizeof(float));
    ctx->buffers[_tnr_msb] = malloc(resolution * sizeof(bool));
    ctx->buffers[_tnr_effective_spads] = malloc(resolution * sizeof(float));
    ctx->buffers[_tnr_noise_reduction] = malloc(resolution * sizeof(float));

    CHECK_MALLOC(ctx->buffers[_tnr_depth]);
    CHECK_MALLOC(ctx->buffers[_tnr_amplitude]);
    CHECK_MALLOC(ctx->buffers[_tnr_ambient]);
    CHECK_MALLOC(ctx->buffers[_tnr_msb]);
    CHECK_MALLOC(ctx->buffers[_tnr_effective_spads]);
    CHECK_MALLOC(ctx->buffers[_tnr_noise_reduction]);

    float *depth_out = (float *)ctx->buffers[_tnr_depth];
    float *amplitude_out = (float *)ctx->buffers[_tnr_amplitude];
    float *ambient_out = (float *)ctx->buffers[_tnr_ambient];
    bool *msb_out = (bool *)ctx->buffers[_tnr_msb];
    float *effective_spads_out = (float *)ctx->buffers[_tnr_effective_spads];
    float *noise_reduction = (float *)ctx->buffers[_tnr_noise_reduction];

    return vl53l9_algo_tnr(/* inputs */
                           depth_in, amplitude_in, ambient_in, msb_in, effective_spads_in,
                           /* outputs */
                           depth_out, amplitude_out, ambient_out, msb_out, effective_spads_out, noise_reduction,
                           /* params */
                           &params, &ctx->tnr, width, height, current_expo_0, current_expo_1, current_expo_2,
                           current_expo_3, meta->ambient_attenuation, meta->nb_step);
}

// predecessors: extract
static int _process_ratenorm(_context_t *ctx, vl53l9_metadata_t *meta) {

    size_t resolution = (meta->crop_enable != 0u) ? ((size_t)meta->crop_x_size * (size_t)meta->crop_y_size)
                                                  : ((size_t)meta->frame_width * (size_t)meta->frame_height);

    // prepare parameters
    ratenorm_params_t params = { 0 };
    vl53l9_algo_ratenorm_init_default_params(&params);
    params.fast_mode = true;
    params.ref_scaler = ctx->calib.amplitude_scaler;
    params.ref_distance = ctx->calib.amplitude_distance;
    params.ref_reflectance = ctx->calib.amplitude_reflectance;
    params.ref_expo = ctx->calib.amplitude_exposure;
    params.max_spads = _compute_max_spads(&ctx->calib, meta);

    // compute exposures from metadata
    uint32_t nb_shots[4]; // steps 1, 4-5, 6, 7
    _build_nb_shots(meta, nb_shots);
    uint32_t expo_sf = nb_shots[1];
    uint32_t expo_sc = nb_shots[2];
    uint32_t expo_sa = nb_shots[3];

    // prepare inputs
    const float *amplitude = (const float *)ctx->buffers[_tnr_amplitude];
    const float *ambient = (const float *)ctx->buffers[_tnr_ambient];
    const bool *msb = (const bool *)ctx->buffers[_tnr_msb];
    const float *effective_spads = (const float *)ctx->buffers[_tnr_effective_spads];

    // prepare outputs
    ctx->buffers[_amplitude_ref] = malloc(resolution * sizeof(float));
    ctx->buffers[_amplitude_ref_rad] = malloc(resolution * sizeof(float));
    ctx->buffers[_signal_rate] = malloc(resolution * sizeof(float));
    ctx->buffers[_ambient_norm] = malloc(resolution * sizeof(float));
    ctx->buffers[_ambient_rate] = malloc(resolution * sizeof(float));
    ctx->buffers[_signal_ambient_factor] = malloc(resolution * sizeof(float));

    CHECK_MALLOC(ctx->buffers[_amplitude_ref]);
    CHECK_MALLOC(ctx->buffers[_amplitude_ref_rad]);
    CHECK_MALLOC(ctx->buffers[_signal_rate]);
    CHECK_MALLOC(ctx->buffers[_ambient_norm]);
    CHECK_MALLOC(ctx->buffers[_ambient_rate]);
    CHECK_MALLOC(ctx->buffers[_signal_ambient_factor]);

    float *amplitude_ref = (float *)ctx->buffers[_amplitude_ref];
    float *amplitude_ref_rad = (float *)ctx->buffers[_amplitude_ref_rad];
    float *signal_rate = (float *)ctx->buffers[_signal_rate];
    float *ambient_rate = (float *)ctx->buffers[_ambient_rate];
    float *ambient_norm = (float *)ctx->buffers[_ambient_norm];
    float *signal_ambient_factor = (float *)ctx->buffers[_signal_ambient_factor];

    return vl53l9_algo_ratenorm_compute_rates(/* input */
                                              amplitude, ambient, effective_spads, msb, ctx->ref_amp_no_expo,
                                              ctx->ref_amp_rad_no_expo, ctx->coeff_norm_no_expo,

                                              /* output */
                                              amplitude_ref, amplitude_ref_rad, signal_rate, ambient_rate, ambient_norm,
                                              signal_ambient_factor,

                                              /* parameters */
                                              &params, resolution, meta->nb_step, expo_sf, expo_sc, expo_sa,
                                              meta->ambient_attenuation);
}

// predecessors: tnr, rate norm
static int _process_reflectance(_context_t *ctx, vl53l9_metadata_t *meta) {

    /**
     * TODO: manage bypass, reflectance is both an output and required by dmax algo
     *  one solution would be output dummy data when bypass is enabled, otherwise force bypass to false
     *  if output is requested by user or any other algo on the pipeline path
     */

    size_t resolution = (meta->crop_enable != 0u) ? ((size_t)meta->crop_x_size * (size_t)meta->crop_y_size)
                                                  : ((size_t)meta->frame_width * (size_t)meta->frame_height);

    // prepare parameters
    reflectance_params_t params = { 0 };
    vl53l9_algo_reflectance_init_default_params(&params);
    params.max_spads = _compute_max_spads(&ctx->calib, meta);
    params.min_refl_thr = 1.5f;
    params.max_refl_thr = 200.0f;
    params.correction_factor = 1.05f; // NOTE: coefficient specific to this implementation
    params.sq_law_exponent = 2.0f;    // NOTE: coefficient specific to this implementation
    params.cover_glass = ctx->controls[_CONTROL_ID_COVER_GLASS].val.v_bool;

    // compute exposures from metadata
    uint32_t nb_shots[4]; // steps 1, 4-5, 6, 7
    _build_nb_shots(meta, nb_shots);
    uint32_t expo_sf = nb_shots[1];
    uint32_t expo_sc = nb_shots[2];

    // prepare input
    const float *distance = (const float *)ctx->buffers[_tnr_depth];
    const float *amplitude = (const float *)ctx->buffers[_tnr_amplitude];
    const bool *msb = (const bool *)ctx->buffers[_tnr_msb];
    const float *effective_spads = (const float *)ctx->buffers[_tnr_effective_spads];
    const float *amplitude_ref_rad = (const float *)ctx->buffers[_amplitude_ref_rad];
    const float *signal_ambient_factor = (const float *)ctx->buffers[_signal_ambient_factor];

    // prepare outputs
    ctx->buffers[_reflectance] = malloc(resolution * sizeof(float));
    ctx->buffers[_validity_low_refl] = malloc(resolution * sizeof(bool));

    CHECK_MALLOC(ctx->buffers[_reflectance]);
    CHECK_MALLOC(ctx->buffers[_validity_low_refl]);

    float *reflectance = (float *)ctx->buffers[_reflectance];
    bool *low_refl_validity = (bool *)ctx->buffers[_validity_low_refl];
    bool *high_refl_validity = NULL; // required only for validation purposes

    return vl53l9_algo_reflectance(/* input */
                                   distance, amplitude, msb, effective_spads, amplitude_ref_rad, signal_ambient_factor,

                                   /* output */
                                   reflectance, low_refl_validity, high_refl_validity,

                                   /* parameters */
                                   &params, resolution, expo_sf, expo_sc, meta->nb_step);
}

// predecessors: tnr
static int _process_radial_to_perp(_context_t *ctx, vl53l9_metadata_t *meta) {

    size_t width = (meta->crop_enable != 0u) ? (meta->crop_x_size) : (meta->frame_width);
    size_t height = (meta->crop_enable != 0u) ? (meta->crop_y_size) : (meta->frame_height);
    size_t resolution = width * height;

    // handle bypass
    if (ctx->controls[_CONTROL_ID_BYPASS_R2P_ALGO].val.v_bool) {
        // allocate memory for output buffers and then copy previous algo data
        ctx->buffers[_depth_r2p] = malloc(resolution * sizeof(float));
        CHECK_MALLOC(ctx->buffers[_depth_r2p]);
        (void)memcpy(ctx->buffers[_depth_r2p], ctx->buffers[_tnr_depth], resolution * sizeof(float));
        ctx->buffers[_distortion_r2p] = NULL;
        ctx->buffers[_center_x_r2p] = NULL;
        ctx->buffers[_validity_r2p] = NULL;
        return 0;
    }

    // prepare parameters
    radial_to_perp_params_t params = { 0 };
    vl53l9_algo_radial_to_perp_init_default_params(&params);
    params.residual_offset_x = ctx->calib.residual_offset_x;
    params.residual_offset_y = ctx->calib.residual_offset_y;
    params.max_distance = (meta->nb_step == 6u) ? MAX_DISTANCE_RANGE : MAX_DISTANCE_PRECISION;

    // prepare inputs
    const float *depth_in = (const float *)ctx->buffers[_tnr_depth];

    // prepare outputs
    ctx->buffers[_depth_r2p] = malloc(resolution * sizeof(float));
    ctx->buffers[_validity_r2p] = malloc(resolution * sizeof(bool));
    CHECK_MALLOC(ctx->buffers[_depth_r2p]);
    CHECK_MALLOC(ctx->buffers[_validity_r2p]);

    if (ctx->is_pointcloud_requested) {
        ctx->buffers[_center_x_r2p] = malloc(resolution * sizeof(float));
        ctx->buffers[_distortion_r2p] = malloc(resolution * sizeof(float));
        CHECK_MALLOC(ctx->buffers[_center_x_r2p]);
        CHECK_MALLOC(ctx->buffers[_distortion_r2p]);
    } else {
        ctx->buffers[_center_x_r2p] = NULL;
        ctx->buffers[_distortion_r2p] = NULL;
    }

    float *depth_r2p = (float *)ctx->buffers[_depth_r2p];
    float *center_x_r2p = (float *)ctx->buffers[_center_x_r2p];
    float *distortion_r2p = (float *)ctx->buffers[_distortion_r2p];
    bool *validity_r2p = (bool *)ctx->buffers[_validity_r2p];

    return vl53l9_algo_radial_to_perp(/* input */
                                      depth_in,

                                      /* output */
                                      depth_r2p, center_x_r2p, distortion_r2p, validity_r2p,

                                      /* parameters */
                                      &params, width, height, meta->binning);
}

// predecessors: tnr
static int _process_sharpener(_context_t *ctx, vl53l9_metadata_t *meta) {

    // handle bypass
    if (ctx->controls[_CONTROL_ID_BYPASS_SHARPENER_FILTER].val.v_bool) {
        ctx->buffers[_validity_sharpener] = NULL;
        ctx->buffers[_sharpener_score] = NULL;
        return 0;
    }

    size_t width = (meta->crop_enable != 0u) ? (meta->crop_x_size) : (meta->frame_width);
    size_t height = (meta->crop_enable != 0u) ? (meta->crop_y_size) : (meta->frame_height);

    // prepare parameters
    sharpener_params_t params;
    vl53l9_algo_sharpener_init_default_params(&params);
    params.mode = SHARPENER_MODE_OPTIM;
    params.max_range_threshold_mm_6_step = 1200.0f;
    params.max_range_threshold_mm_7_step = 600.0f;

    // prepare inputs
    const float *depth = (const float *)ctx->buffers[_tnr_depth];
    const float *signal = (const float *)ctx->buffers[_signal_rate];
    const float *reflectance = (const float *)ctx->buffers[_reflectance];
    const float *confidence = (const float *)ctx->buffers[_confidence];

    // prepare outputs
    ctx->buffers[_validity_sharpener] = malloc(width * height * sizeof(bool));
    ctx->buffers[_sharpener_score] = NULL; // NOTE: not required, should be allocated if needed

    CHECK_MALLOC(ctx->buffers[_validity_sharpener]);

    bool *validity_sharpener = (bool *)ctx->buffers[_validity_sharpener];
    float *sharpener_score = (float *)ctx->buffers[_sharpener_score];

    return vl53l9_algo_sharpener(/* input */
                                 depth, signal, reflectance, confidence,

                                 /* output */
                                 validity_sharpener, sharpener_score,

                                 /* parameters */
                                 &params, width, height, meta->nb_step);
}

static int _process_flying_pixel(_context_t *ctx, vl53l9_metadata_t *meta) {

    // handle bypass
    if (ctx->controls[_CONTROL_ID_BYPASS_FLYING_PIXEL_FILTER].val.v_bool) {
        ctx->buffers[_validity_flying_pixel] = NULL;
        return 0;
    }

    size_t width = (meta->crop_enable != 0u) ? (meta->crop_x_size) : (meta->frame_width);
    size_t height = (meta->crop_enable != 0u) ? (meta->crop_y_size) : (meta->frame_height);

    // prepare parameters
    flying_pixel_params_t params = { 0 };
    vl53l9_algo_flying_pixel_init_default_params(&params);
    params.depth_th = 300.0f;
    params.min_depth_occurence = 5;

    // prepare inputs
    const float *distance_in = (const float *)ctx->buffers[_depth_r2p];
    const float *confidence_in = (const float *)ctx->buffers[_confidence];

    // prepare outputs
    ctx->buffers[_validity_flying_pixel] = malloc(width * height * sizeof(bool));
    CHECK_MALLOC(ctx->buffers[_validity_flying_pixel]);
    bool *validity_fp = (bool *)ctx->buffers[_validity_flying_pixel];

    return vl53l9_algo_flying_pixel(distance_in, confidence_in,

                                    validity_fp,

                                    &params, width, height);
}

// predecessors: radial to perp, confidence, reflectance, sharpener, flying_pixel
static int _process_distance_check(_context_t *ctx, vl53l9_metadata_t *meta) {

    size_t resolution = (meta->crop_enable != 0u) ? ((size_t)meta->crop_x_size * (size_t)meta->crop_y_size)
                                                  : ((size_t)meta->frame_width * (size_t)meta->frame_height);

    // prepare inputs
    const float *depth_in = (const float *)ctx->buffers[_depth_r2p];
    const float *dmax_in = (const float *)ctx->buffers[_dmax];
    const bool *validity_r2p = (const bool *)ctx->buffers[_validity_r2p];
    const bool *validity_confidence = (const bool *)ctx->buffers[_validity_confidence];
    const bool *validity_reflectance = (const bool *)ctx->buffers[_validity_low_refl];
    const bool *validity_sharpener = (const bool *)ctx->buffers[_validity_sharpener];
    const bool *validity_fp = (const bool *)ctx->buffers[_validity_flying_pixel];

    // prepare outputs
    ctx->buffers[_depth_out] = malloc(resolution * sizeof(float));
    ctx->buffers[_status_out] = malloc(resolution * sizeof(unsigned char));

    CHECK_MALLOC(ctx->buffers[_depth_out]);
    CHECK_MALLOC(ctx->buffers[_status_out]);

    float *depth_out = (float *)ctx->buffers[_depth_out];
    unsigned char *status_out = (unsigned char *)ctx->buffers[_status_out];

    // prepare parameters
    bool r2p_algo_bypass = ctx->controls[_CONTROL_ID_BYPASS_R2P_ALGO].val.v_bool;

    bool r2p_filter = !ctx->controls[_CONTROL_ID_BYPASS_R2P_FILTER].val.v_bool;
    bool confidence_filter = !ctx->controls[_CONTROL_ID_BYPASS_CONFIDENCE_FILTER].val.v_bool;
    bool reflectance_filter = !ctx->controls[_CONTROL_ID_BYPASS_REFLECTANCE_FILTER].val.v_bool;
    bool sharpener_filter = !ctx->controls[_CONTROL_ID_BYPASS_SHARPENER_FILTER].val.v_bool;
    bool fp_filter = !ctx->controls[_CONTROL_ID_BYPASS_FLYING_PIXEL_FILTER].val.v_bool;

    // if r2p algo is bypassed, then r2p filter must be bypassed as well since it relies on r2p validity
    if (r2p_algo_bypass) {
        r2p_filter = false;
    }

    const bool dmax_select = false; // TODO: temporary set to false
    const float invalid_distance = 12000.0f;
    const bool replace_distance = true;
    const float max_distance = (meta->nb_step == 6u) ? (float)MAX_DISTANCE_RANGE : (float)MAX_DISTANCE_PRECISION;

    return vl53l9_algo_distance_check(/* input */
                                      depth_in, dmax_in, validity_r2p, validity_confidence, validity_reflectance,
                                      validity_sharpener, validity_fp,

                                      /* output */
                                      depth_out, status_out,

                                      /* parameters */
                                      resolution, r2p_filter, confidence_filter, reflectance_filter, sharpener_filter,
                                      fp_filter, dmax_select, replace_distance, max_distance, invalid_distance);
}

// predecessors: ratenorm, confidence
static int _process_dmax(_context_t *ctx, vl53l9_metadata_t *meta) {

    // TODO: temporary bypass since not used by other algos in the pipeline
    (void)meta;
    ctx->buffers[_dmax] = NULL;
    return 0;
}

static int _process_pointcloud(_context_t *ctx, vl53l9_metadata_t *meta) {

    // handle bypass
    if (!ctx->is_pointcloud_requested) {
        return 0;
    }

    size_t width = (meta->crop_enable != 0u) ? (size_t)(meta->crop_x_size) : (size_t)(meta->frame_width);
    size_t height = (meta->crop_enable != 0u) ? (size_t)(meta->crop_y_size) : (size_t)(meta->frame_height);
    size_t resolution = width * height;

    // prepare parameters
    radial_to_perp_params_t params = { 0 };
    vl53l9_algo_radial_to_perp_init_default_params(&params);
    params.residual_offset_x = ctx->calib.residual_offset_x;
    params.residual_offset_y = ctx->calib.residual_offset_y;
    params.max_distance = (meta->nb_step == 6u) ? MAX_DISTANCE_RANGE : MAX_DISTANCE_PRECISION;

    // prepare inputs
    const float *depth = (const float *)ctx->buffers[_depth_out];
    const float *center_x = (const float *)ctx->buffers[_center_x_r2p];
    const float *distorsion = (const float *)ctx->buffers[_distortion_r2p];
    const float *confidence = (const float *)ctx->buffers[_confidence];
    const float *confidence_thr = (const float *)ctx->buffers[_threshold_confidence];
    const unsigned char *filter_status = (const unsigned char *)ctx->buffers[_status_out];

    // prepare outputs
    ctx->buffers[_pointcloud] = malloc(resolution * 4u * sizeof(float)); // (x, y, z, confidence)
    CHECK_MALLOC(ctx->buffers[_pointcloud]);
    float *pointcloud = (float *)ctx->buffers[_pointcloud];

    return vl53l9_algo_pointcloud(/* input */
                                  depth, center_x, distorsion, confidence, confidence_thr, filter_status,

                                  /* output */
                                  pointcloud,

                                  /* parameters */
                                  &params, width, height, meta->binning);
}

static int _process_depth16(_context_t *ctx, vl53l9_metadata_t *meta) {

    // handle bypass
    if (!ctx->is_depth16_requested) {
        return 0;
    }

    size_t resolution = (meta->crop_enable != 0u) ? ((size_t)meta->crop_x_size * (size_t)meta->crop_y_size)
                                                  : ((size_t)meta->frame_width * (size_t)meta->frame_height);

    // prepare parameters
    depth16_params_t params;
    vl53l9_algo_depth16_init_default_params(&params);
    params.format = DEPTH16_FORMAT_3DMAX;

    // prepare inputs
    const float *depth_in = (const float *)ctx->buffers[_depth_out];
    const unsigned char *filter_status_in = (const unsigned char *)ctx->buffers[_status_out];
    const float *confidence_in = (const float *)ctx->buffers[_confidence];
    const float *confidence_thr_in = (const float *)ctx->buffers[_threshold_confidence];

    // prepare outputs
    ctx->buffers[_depth16_out] = malloc(resolution * sizeof(uint16_t));
    CHECK_MALLOC(ctx->buffers[_depth16_out]);
    uint16_t *depth16_out = (uint16_t *)ctx->buffers[_depth16_out];

    return vl53l9_algo_depth16(/* input */
                               depth_in, filter_status_in, confidence_in, confidence_thr_in,

                               /* output */
                               depth16_out,

                               /* parameters */
                               &params, resolution);
}

static void _process_free_buffers(_context_t *ctx) {
    for (size_t i = 0; i < (size_t)_nb_buffers; i++) {
        if (ctx->buffers[i] != NULL) {
            free(ctx->buffers[i]);
            ctx->buffers[i] = NULL;
        }
    }
}
