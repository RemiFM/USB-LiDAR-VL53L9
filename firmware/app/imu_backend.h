/**
  * Internal interface between imu.c and the per-chip backends.
  *
  * Each backend (imu_lsm6dsv*.c) includes only its own ST driver header, so the
  * three drivers never meet in one translation unit. The bus functions below
  * match ST's stmdev_write_ptr / stmdev_read_ptr / stmdev_mdelay_ptr signatures.
  */
#ifndef IMU_BACKEND_H
#define IMU_BACKEND_H

#include <stdint.h>
#include "imu.h"

#ifdef __cplusplus
extern "C" {
#endif

/* SPI bus access, implemented in imu.c */
int32_t imu_bus_write(void *handle, uint8_t reg, const uint8_t *data, uint16_t len);
int32_t imu_bus_read(void *handle, uint8_t reg, uint8_t *data, uint16_t len);
void imu_bus_delay_ms(uint32_t ms);

/* Backends: init configures the chip, read fills one sample. Return 0 on success. */
int imu_lsm6dsv_init(void);
int imu_lsm6dsv_read(imu_sample_t *out);
int imu_lsm6dsv16x_init(void);
int imu_lsm6dsv16x_read(imu_sample_t *out);
int imu_lsm6dsv16bx_init(void);
int imu_lsm6dsv16bx_read(imu_sample_t *out);

#ifdef __cplusplus
}
#endif

#endif /* IMU_BACKEND_H */
