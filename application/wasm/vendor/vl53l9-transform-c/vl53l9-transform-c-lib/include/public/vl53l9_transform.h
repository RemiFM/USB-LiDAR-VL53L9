/**
 ******************************************************************************
 * @file    vl53l9_transform.h
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

#ifndef VL53L9_TRANSFORM_C_H
#define VL53L9_TRANSFORM_C_H

#include "transform.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Flag to enable debug prints
 */
#define VL53L9_TRANSFORM_DEBUG (0)

/**
 * @brief Flag to enable light version of the transform
 * When set to 1, the transform will be built with a reduced set of features and capabilities, allowing for a smaller code size and lower memory usage.
 * This can be useful for resource-constrained environments or when only basic functionality is required.
 *
 * The following algorithms are bypassed by default when this symbol is set:
 * - temporal noise reduction (TNR)
 * - flying pixel
 * 
 * The following methods will return MEDIA_ERROR_UNIMPLEMENTED when this symbol is set:
 * - _query_compatible_stream_caps
 * - _query_stream_dependencies
 * - _do_query_memory_allocation
 */
#ifndef VL53L9_TRANSFORM_LIGHT
#define VL53L9_TRANSFORM_LIGHT (1)
#endif

transform_t *vl53l9_transform_create(void);
void vl53l9_transform_destroy(transform_t *self);

#ifdef __cplusplus
}
#endif

#endif // VL53L9_TRANSFORM_C_H
