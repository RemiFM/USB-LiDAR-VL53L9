/**
  * VL53L9CX LiDAR: power-up, bus bring-up, sensor configuration and frame streaming.
  *
  * Configuration (validated on this board by VL53L9-UNO-Q-LiDAR, ~35 fps):
  *   manual sync (frame on trigger), ultra-low power mode, short context,
  *   binning 2 -> 54 x 42 zones, exposure 6 ms.
  * Frames are streamed raw (PKT_LIDAR_FRAME): depth is computed on the host with
  * ST's transform library and this sensor's calibration (PKT_LIDAR_CALIB).
  */
#ifndef LIDAR_H
#define LIDAR_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LIDAR_WIDTH       54U
#define LIDAR_HEIGHT      42U
#define LIDAR_ZONES       (LIDAR_WIDTH * LIDAR_HEIGHT)
#define LIDAR_RAW_SIZE    (LIDAR_ZONES * 6U + LIDAR_ZONES / 2U + 100U)   /* 14842 */
#define LIDAR_CALIB_SIZE  2332U

typedef struct
{
  uint8_t  state;          /* LIDAR_STATE_* (protocol.h) */
  uint32_t device_id;
  uint16_t patch_revision;
  uint32_t frames;         /* frames sent since the stream started */
  uint32_t dropped;        /* frames read but not queued for USB */
  uint32_t errors;         /* failed operations since boot */
  int32_t  last_error;     /* VL53L9_ERROR_* or negative stage code */
  const char *last_error_where;
} lidar_info_t;

extern lidar_info_t g_lidar;

/* Power-cycles and configures the sensor. Leaves it in standby (READY). 0 = ok. */
int lidar_init(void);
int lidar_start(void);     /* READY -> STREAMING */
void lidar_stop(void);     /* STREAMING -> READY (best effort) */
void lidar_task(void);     /* call from the main loop; streams frames while STREAMING */

/* Calibration blob read at init (NULL if not available). */
const uint8_t *lidar_calibration(void);

#ifdef __cplusplus
}
#endif

#endif /* LIDAR_H */
