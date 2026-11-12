/**
  * USB CDC binary protocol, version 1. Mirrored by application/src/protocol/binary.ts.
  * All multi-byte fields are little-endian.
  *
  * Device -> host: packets
  *   offset size  field
  *   0      2     sync      0xA5 0x5A
  *   2      1     type      PKT_* below
  *   3      1     version   PROTO_VERSION
  *   4      4     seq       packet counter over all types (gap = packet lost)
  *   8      8     t_us      MCU time in microseconds since boot
  *   16     4     length    payload length in bytes (max PROTO_MAX_PAYLOAD)
  *   20     n     payload
  *   20+n   4     crc32     CRC-32 (zlib) over bytes 0 .. 20+n-1
  *
  * Host -> device: single ASCII command bytes (CMD_* below), so a terminal can
  * still drive the device by hand.
  */
#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

#define PROTO_SYNC0          0xA5U
#define PROTO_SYNC1          0x5AU
#define PROTO_VERSION        1U
#define PROTO_HEADER_SIZE    20U
#define PROTO_CRC_SIZE       4U
#define PROTO_MAX_PAYLOAD    16384U

/* ------------------------------------------------------------------ types */
enum
{
  PKT_INFO        = 0x01, /* ASCII "key=value\n" lines, sent on connect and on CMD_INFO */
  PKT_LOG         = 0x02, /* ASCII text (one message, no trailing newline) */
  PKT_STATUS      = 0x03, /* proto_status_t, once per second while connected */
  PKT_IMU         = 0x10, /* proto_imu_t, one per IMU sample (120 Hz) while IMU stream is on */
  PKT_LIDAR_FRAME = 0x20, /* proto_lidar_frame_t + raw frame bytes */
  PKT_LIDAR_CALIB = 0x21, /* sensor calibration blob (2332 bytes), on CMD_CALIB */
};

/* ------------------------------------------------------------------ payloads */
typedef struct __attribute__((packed))
{
  uint32_t sample;        /* IMU sample counter since the stream started */
  float    accel_mg[3];   /* sensor frame, milli-g */
  float    gyro_mdps[3];  /* sensor frame, milli-degrees per second */
  float    temp_c;        /* die temperature */
} proto_imu_t;            /* 32 bytes */

typedef struct __attribute__((packed))
{
  uint32_t frame;         /* frame counter since the LiDAR stream started */
  uint16_t width;         /* zones: 54 */
  uint16_t height;        /* zones: 42 */
  uint32_t raw_size;      /* bytes of raw data that follow: 14842 */
  /* followed by raw_size bytes: ST raw frame, last 100 bytes = vl53l9_metadata_t */
} proto_lidar_frame_t;    /* 12 bytes */

enum
{
  LIDAR_STATE_OFF = 0,      /* not detected / not initialized */
  LIDAR_STATE_READY = 1,    /* configured, sensor in standby */
  LIDAR_STATE_STREAMING = 2,
  LIDAR_STATE_ERROR = 3,    /* see last_error; CMD_LIDAR_REINIT to recover */
};

enum
{
  BUS_NONE = 0,
  BUS_I2C_SOFT = 1,         /* bit-banged I2C fallback */
  BUS_I3C = 2,              /* I3C peripheral, dynamic address */
};

typedef struct __attribute__((packed))
{
  uint8_t  imu_variant;     /* imu_variant_t (0 = none) */
  uint8_t  imu_whoami;
  uint8_t  imu_streaming;
  uint8_t  lidar_state;     /* LIDAR_STATE_* */
  uint8_t  lidar_bus;       /* BUS_* */
  uint8_t  led_mode;        /* 0 heartbeat, 1 manual off, 2 manual on */
  uint16_t reserved;
  uint32_t lidar_bus_hz;
  uint32_t lidar_frames;    /* frames sent since the stream started */
  uint32_t lidar_dropped;   /* frames read but not sent (USB still busy) */
  uint32_t lidar_errors;    /* failed operations since boot */
  int32_t  lidar_last_error;/* VL53L9_ERROR_* of the last failure (0 = none) */
  uint32_t imu_samples;
  uint32_t tx_dropped;      /* small packets dropped (TX queue full) */
} proto_status_t;           /* 36 bytes */

/* ------------------------------------------------------------------ commands */
enum
{
  CMD_INFO         = 'V', /* send PKT_INFO */
  CMD_CALIB        = 'C', /* send PKT_LIDAR_CALIB */
  CMD_IMU_ON       = 'I', /* start IMU stream */
  CMD_IMU_OFF      = 'i', /* stop IMU stream */
  CMD_LIDAR_ON     = 'L', /* start LiDAR stream */
  CMD_LIDAR_OFF    = 'l', /* stop LiDAR stream */
  CMD_ALL_OFF      = 'X', /* stop all streams */
  CMD_LED_TOGGLE   = 'T', /* LED manual on/off */
  CMD_LED_AUTO     = 'B', /* LED back to heartbeat */
  CMD_IMU_REINIT   = 'U', /* re-detect and reconfigure the IMU */
  CMD_LIDAR_REINIT = 'R', /* power-cycle and reconfigure the LiDAR */
};

_Static_assert(sizeof(proto_imu_t) == 32, "proto_imu_t layout");
_Static_assert(sizeof(proto_lidar_frame_t) == 12, "proto_lidar_frame_t layout");
_Static_assert(sizeof(proto_status_t) == 36, "proto_status_t layout");

#endif /* PROTOCOL_H */
