# vl53l9-transform-c

Postprocessing pipeline C library for VL53L9 sensor.

## Dependencies

This library implements the `transform-c` class which inherits from the `media-c` one. Both are part of the `media-object` project and thus are needed to build this component.

## Pipeline Architecture

Data coming from the sensor are first parsed in order to extract metadata and separate the depth, amplitude and ambient raw images.

The pipeline architecture allows to bypass some components that might not be required by your application to reduce the execution time through dedicated controls (i.e. `bypass-tnr-algo`).

Filtering is done at the end of the pipe, through the `distance_check` block, depending on the information provided by each algorithm and the associated pixel-validity filters. The configuration of the filters is exposed to the user through dedicated controls (i.e. `bypass-r2p-filter`).

The supported controls are:

| Control                 | Type    | Default value | Description |
|-------------------------|---------|---------------|-------------|
| bypass-r2p-algo         | bool    | false         | Bypasses the radial-to-perpendicular conversion stage. |
| bypass-tnr-algo         | bool    | false         | Bypasses the temporal noise reduction stage. |
| bypass-r2p-filter       | bool    | false         | Disables the radial-to-perpendicular validity filter in the final stage. |
| bypass-conf-filter      | bool    | false         | Disables the confidence-based validity filter in the final stage. |
| bypass-refl-filter      | bool    | false         | Disables the reflectance-based validity filter in the final stage. |
| bypass-sharpener-filter | bool    | false         | Disables the sharpener-based validity filter in the final stage. |
| bypass-fp-filter        | bool    | false         | Disables the flying-pixel validity filter in the final stage. |
| calib-buffer            | pointer | NULL          | Pointer to the buffer storing calibration data (mandatory). |
| cover-glass             | bool    | false         | Enables cover-glass compensation. |

> `bypass-tnr-algo` and `bypass-fp-filter` are set to `true` when VL53L9_TRANSFORM_LIGHT is set

The supported streams are:

| Name         | Direction | Pixel Format         |  Resolution                                    |
|--------------|-----------|----------------------|------------------------------------------------|
| raw          | input     | 3DMD                 | [(100, 149), (14842, 1), (100, 39), (3844, 1)] |
| depth        | output    | [ZF32, ZAPC, ZA16]   | [(54, 42), (24, 20)]                           |
| ambient      | output    | IF32                 | [(54, 42), (24, 20)]                           |
| amplitude    | output    | AF32                 | [(54, 42), (24, 20)]                           |
| confidence   | output    | CF32                 | [(54, 42), (24, 20)]                           |
| reflectance  | output    | RF32                 | [(54, 42), (24, 20)]                           |
| status       | output    | CU32                 | [(54, 42), (24, 20)]                           |

> Note: the `depth` stream can output information through different pixel formats:
> - ZF32: standard depth
> - ZAPC: Android depth point cloud format, each point is represented by four floats: [x, y, z, confidence]. The confidence value is between 0 and 1.
> - ZA16: Android depth16 format, each pixel is 16 bits with the confidence value being encoded in the 3 most significant bits and the depth value on the remaining 13 bits.

The following block diagram shows the data path to process the `depth` stream:

```mermaid
graph LR
    extract --> confidence
    extract --> distance_calib
    extract --> rate_norm
    distance_calib --> tnr
    tnr --> radial_to_perp
    tnr --> sharpener
    tnr --> reflectance
    radial_to_perp --> flying_pixel
    confidence --> flying_pixel
    flying_pixel --> distance_check
    sharpener --> distance_check
    radial_to_perp --> distance_check
    rate_norm --> reflectance
    reflectance --> distance_check
    confidence --> distance_check

    subgraph extract
        direction LR
    end

    subgraph confidence
        direction LR
    end

    subgraph distance_calib
        direction LR
    end

    subgraph radial_to_perp
        direction LR
    end

    subgraph sharpener
        direction LR
    end

    subgraph rate_norm
        direction LR
    end

    subgraph reflectance
        direction LR
    end

    subgraph distance_check
        direction LR
    end
```

## Getting Started

The typical lifecycle of an instance is:

1. `vl53l9_transform_create()`: create the handle.
2. `transform_initialize()`: initialize the instance and apply default settings.
3. `transform_inspect()` list the supported streams and controls [optional].
4. `transform_set_control()`: set controls to a given value.
5. `transform_prepare()`: apply controls to the instance and allocate resources required for the processing.
6. `transform_set_stream_capabilities()`: configure the input and output stream capabilities (pixel format, resolution).
7. `transform_process_stream()`: generate requested output streams from input.
8. `transform_release()`: release the instance resources.
9. `vl53l9_transform_destroy()`: destroy the handle.

### Build-Time Customization

The `vl53l9_transform.h` public header exposes the following customization flags:

- `VL53L9_TRANSFORM_DEBUG`: enables internal debug prints when set to `1`. The default value is `0`.
- `VL53L9_TRANSFORM_LIGHT`: enables a reduced-feature build when set to `1`. This mode lowers code size and memory usage, which can be useful on constrained embedded targets. The default value is `1`.

These flags can be overridden at compile time through the build system.

### Initialization

To be able to use the `vl53l9-transform-c` you must first of all allocate a handle through the `vl53l9_transform_create()` method.

Then the software needs to call the `initialize` method of the table which will take care of creating and setup a dedicated context for the provided instance. This will be stored in the `private_data` field of the handle.

```c
transform_t *p_transform = vl53l9_transform_create();
transform_initialize(p_transform);
```

Resources associated with a given instance can be freed calling the `release` method. Then the handle can be deallocated calling the destructor.

```c
transform_release(p_transform);
vl53l9_transform_destroy(p_transform);
```

### Configuration

It is possible to programmatically inspect the list of supported streams and controls with the following lines:

```c
const streams_t *stream_list;
transform_get_streams(p_transform, &stream_list);
streams_inspect(stream_list, printf);

const controls_t *control_list;
transform_get_controls(p_transform, &control_list);
controls_inspect(control_list, printf);
```

#### Controls

Set mandatory controls to provide calibration data:

```c
transform_set_control(p_transform, "calib-buffer", (value_t){ .val.v_ptr = calib_data, .tid = VTID_POINTER });
```

> Note: the ownership of `calib-buffer` remains with the caller. Its content is parsend and stored  within the internal context of the `transform_t` instance after preparation.

Controls are taken into account when calling the `prepare` method:

```c
transform_prepare(p_transform);
```

#### Capabilities

At least one input and output stream must be configured, this is a mandatory step since no default value is provided by the implementation. The desired configuration must be explicitly set. Additionally, input streams must be configured before output ones.

For instance, to define raw input stream properties (pixel format and resolution should match one of the capabilities supported by the stream):

```c
property_t raw_format = { "format", { .val.v_string = "3DMD", .tid = VTID_STRING } };
property_t raw_width = { "width", { .val.v_uint32 = in_width, .tid = VTID_UINT32 } };
property_t raw_height = { "height", { .val.v_uint32 = in_height, .tid = VTID_UINT32 } };

properties_t *raw_props = properties_new(3); // format, width, height
properties_add(raw_props, &raw_format);
properties_add(raw_props, &raw_width);
properties_add(raw_props, &raw_height);
capabilities_t *raw_caps = capabilities_new_simple(&raw_props);

properties_free(raw_props, NULL);
```

```c
transform_set_stream_capabilities(p_transform, "raw", raw_caps);
```

When setting capabilities for an output stream, the library checks the consistency of the resolution based on the input.

### Processing

Data exchanges between the application side and the postprocessing library happen through `stream_buffers_t` objects. They contain an entry for each `stream_buffer_t` associated with a given stream. Each `stream_buffer_t` comes with a memory pool (`memories_t`) that must be previously allocated for each buffer (`memory_t`). This operation can be done either with static or dynamic allocation.

At the moment, the current implementation of `vl53l9-transform-c` requires dynamic memory allocation internally. On embedded targets, make sure the linker script and heap configuration are adjusted accordingly so that enough memory is available at runtime. Static-memory support is planned for a future release.

Refer to the example code to see how to allocate memory and properly initialize the structure.

For instance, the following lines allow to provide the raw input data and request depth output:

```c
stream_buffers_t *stream_buffers = stream_buffers_new(2);
stream_buffers_add(stream_buffers, &in_raw_stream_buffer);
stream_buffers_add(stream_buffers, &out_depth_stream_buffer);
```

Calling the `process_stream` method triggers the computation of the requested streams.
The first call might take more time to be executed due to the computation of calibration maps.

```c
while (1) {
    // retrieve raw data from the sensor

    transform_process_stream(p_transform, stream_buffers);

    // application logic
}
```

## Known Limitations

- The `get_last_error` method is not properly supported yet.
- The `metadata` and `timestamp` fields of the `buffer_t` objects are not filled.
