/**
 ******************************************************************************
 * @file    depth16.c
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

#include "algo/depth16.h"

#include <errno.h>
#include <math.h>
#include <stdint.h>

#ifndef EINVAL
#define EINVAL 22
#endif

typedef int32_t i32;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef float_t f32;

static u16 minu(u16 a, u16 b) {
    return (a < b) ? a : b;
}

void vl53l9_algo_depth16_init_default_params(depth16_params_t *params) {
    params->format = DEPTH16_FORMAT_DEFAULT;
}

i32 vl53l9_algo_depth16(const f32 *depth, const u8 *filter_status, const f32 *confidence, const f32 *conf_thr,

                        u16 *depth16,

                        const depth16_params_t *params, u32 size) {
    // if one of the input is missing, return
    // if all outputs are missing, return
    if (!(bool)depth || !(bool)filter_status || !(bool)confidence || !(bool)conf_thr || !((bool)depth16)) {
        errno = EINVAL;
        return EXIT_FAILURE;
    }

    for (u32 i = 0; i < size; ++i) {
        errno = 0;
        const u16 depth_u = (u16)lroundf(depth[i]);
        if ((bool)errno) {
            return EXIT_FAILURE;
        }
        const u16 clamped_depth = minu(depth_u, (u16)(0x1FFF));

        const f32 conf = confidence[i];
        const f32 thr = conf_thr[i];
        const u8 status = filter_status[i];

        u16 android_conf = 0;
        switch (params->format) {
        default:
        case DEPTH16_FORMAT_DEFAULT:
            if (conf < thr) {
                android_conf = (u16)0u;
            } else if ((conf >= thr) && (conf < (2.0f * thr))) {
                android_conf = (u16)1u;
            } else if ((conf >= (2.0f * thr)) && (conf < (4.0f * thr))) {
                android_conf = (u16)2u;
            } else if ((conf >= (4.0f * thr)) && (conf < (6.0f * thr))) {
                android_conf = (u16)3u;
            } else if ((conf >= (6.0f * thr)) && (conf < (8.0f * thr))) {
                android_conf = (u16)4u;
            } else if ((conf >= (8.0f * thr)) && (conf < (10.0f * thr))) {
                android_conf = (u16)5u;
            } else if ((conf >= (10.0f * thr)) && (conf < (12.0f * thr))) {
                android_conf = (u16)6u;
            } else if ((conf >= (12.0f * thr))) {
                android_conf = (u16)7u;
            }
            if ((bool)status || (depth_u > (u16)0x1FFF)) {
                android_conf = (u16)0u;
            }
            android_conf += (u16)1u;
            break;

        case DEPTH16_FORMAT_3DMAX:
            if ((conf >= thr) && (conf < (3.0f * thr))) {
                android_conf = (u16)3u;
            } else if ((conf >= (3.0f * thr)) && (conf < (6.0f * thr))) {
                android_conf = (u16)4u;
            } else if ((conf >= (6.0f * thr)) && (conf < (8.0f * thr))) {
                android_conf = (u16)5u;
            } else if ((conf >= (8.0f * thr)) && (conf < (10.0f * thr))) {
                android_conf = (u16)6u;
            } else if ((conf >= (10.0f * thr)) && (conf < (12.0f * thr))) {
                android_conf = (u16)7u;
            } else if ((conf >= (12.0f * thr))) {
                android_conf = (u16)0u;
            }
            if (!((status == (u8)0u) || (status == (u8)1u) || (status == (u8)8u) || (status == (u8)9u))) {
                android_conf = (u16)1u;
            }
            if ((status == (u8)1u) || (status == (u8)8u) || (status == (u8)9u)) {
                android_conf = (u16)2u;
            }
            if (depth_u > (u16)0x1FFF) {
                android_conf = (bool)status ? (u16)1u : (u16)2u;
            }
            break;

        case DEPTH16_FORMAT_CUSTOM:
            switch (status) {
            case (u8)0u:
                android_conf = (u16)0u;
                break;
            case (u8)1u:
                android_conf = (u16)1u;
                break;
            case (u8)4u:
                android_conf = (u16)2u;
                break;
            case (u8)2u:
                android_conf = (u16)3u;
                break;
            case (u8)16u:
                android_conf = (u16)4u;
                break;
            case (u8)6u:
                android_conf = (u16)5u;
                break;
            case (u8)20u:
                android_conf = (u16)6u;
                break;
            default:
                android_conf = (u16)7u;
                break;
            }
            if (depth_u > (u16)0x1FFF) {
                android_conf = (u16)1u;
            }
            break;
        }

        depth16[i] = (android_conf << 13) | clamped_depth;
    }

    return EXIT_SUCCESS;
}
