/**
  * VL53L9 register transport: I3C (preferred) or bit-banged I2C (fallback).
  * Register index: 16-bit big-endian. Each register access is
  * START/WRITE index/STOP, then START/READ or WRITE data/STOP (datasheet 4.2:
  * no repeated start between the index write and the read).
  *
  * Bring-up (lidar_bus_init):
  *   1. I3C peripheral in I2C mode, 1 MHz, static address 0x29: read the device ID.
  *   2. ENTDAA at 1 MHz (datasheet: DAA must run at <= 1 MHz) -> dynamic address 0x30.
  *   3. Verify the ID 8x over I3C. On any failure: back to bit-banged I2C.
  * Ported from VL53L9-UNO-Q-LiDAR (application/lidar_bus.c).
  */
#ifndef LIDAR_BUS_H
#define LIDAR_BUS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LIDAR_STATIC_ADDR   0x29U
#define LIDAR_DYNAMIC_ADDR  0x30U
#define LIDAR_DEVICE_ID     0x53334C39U   /* "9L3S" little-endian */

typedef enum
{
  LIDAR_BUS_SOFT_I2C = 0,   /* bit-banged I2C at 0x29 */
  LIDAR_BUS_HW_I2C = 1,     /* I3C peripheral in legacy I2C mode (discovery only) */
  LIDAR_BUS_I3C = 2,        /* I3C SDR at the dynamic address */
} lidar_bus_mode_t;

typedef struct
{
  lidar_bus_mode_t mode;
  uint8_t address;
  uint32_t bus_hz;
  uint32_t failures;        /* failed transfers since boot */
  uint64_t pid;             /* I3C provisional ID from ENTDAA */
} lidar_bus_info_t;

extern lidar_bus_info_t g_lidar_bus;

/* Brings up I3C; returns 0 if I3C works, -1 if it fell back to soft I2C. */
int lidar_bus_init(void);
/* Power-cycles the sensor via XSHUT and returns to bit-banged I2C. */
void lidar_bus_fallback(void);
/* I3C only: 1, 6 or 12 MHz. No-op on the I2C fallback. */
int lidar_bus_speed(uint32_t hz);
/* Largest single read the transport handles in one transfer. */
uint32_t lidar_bus_max_read(void);
int lidar_bus_read(uint16_t reg, uint8_t *data, uint32_t n);
int lidar_bus_write(uint16_t reg, const uint8_t *data, uint32_t n);

#ifdef __cplusplus
}
#endif

#endif /* LIDAR_BUS_H */
