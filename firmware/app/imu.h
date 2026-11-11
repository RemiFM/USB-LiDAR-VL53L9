/**
  * IMU layer for the LSM6DSV family on SPI1 (SCK=PA5, MISO=PA6, MOSI=PA7, CS=PA4).
  *
  * Supported (same footprint, detected at runtime via WHO_AM_I):
  *   0x71 -> LSM6DSV16BX
  *   0x70 -> LSM6DSV or LSM6DSV16X. Both report 0x70 and cannot be told apart in
  *           software; their accel/gyro/temperature core is identical. Which ST
  *           driver handles 0x70 is chosen at build time (IMU_ID70_IS_LSM6DSV16X).
  */
#ifndef IMU_H
#define IMU_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
  IMU_NONE = 0,       /* not detected / not initialized */
  IMU_LSM6DSV,
  IMU_LSM6DSV16X,
  IMU_LSM6DSV16BX,
} imu_variant_t;

typedef struct
{
  float accel_mg[3];     /* X, Y, Z in milli-g (sensor frame) */
  float gyro_mdps[3];    /* X, Y, Z in milli-degrees per second (sensor frame) */
  float temp_c;          /* die temperature in degC */
} imu_sample_t;

/* Configures SPI1, detects the IMU and configures it:
   accel +/-4 g, gyro +/-1000 dps, both 120 Hz high-performance.
   Returns 0 on success, negative on failure (see imu_whoami()). */
int imu_init(void);

/* Reads the latest accel, gyro and temperature. Returns 0 on success. */
int imu_read(imu_sample_t *out);

/* Returns 1 when a new accel AND gyro sample is ready (STATUS_REG XLDA+GDA),
   0 when not, negative on bus error. Same register on all supported parts. */
int imu_data_ready(void);

imu_variant_t imu_variant(void);
char const *imu_name(void);
uint8_t imu_whoami(void);   /* raw WHO_AM_I from the last imu_init() */

#ifdef __cplusplus
}
#endif

#endif /* IMU_H */
