/**
  * LSM6DSV backend (WHO_AM_I 0x70), using ST's lsm6dsv-pid driver.
  * Used for 0x70 unless IMU_ID70_IS_LSM6DSV16X is set (see imu.h).
  */
#include "imu_backend.h"
#include "mx_spi1.h"
#include "lsm6dsv_reg.h"

static stmdev_ctx_t ctx;

int imu_lsm6dsv_init(void)
{
  uint8_t id = 0U;

  ctx.write_reg = imu_bus_write;
  ctx.read_reg  = imu_bus_read;
  ctx.mdelay    = imu_bus_delay_ms;
  ctx.handle    = mx_spi1_gethandle();

  if (lsm6dsv_device_id_get(&ctx, &id) != 0 || id != LSM6DSV_ID)
  {
    return -1;
  }

  /* Power down, software reset, wait until done (handled by ST's driver). */
  if (lsm6dsv_sw_reset(&ctx) != 0)
  {
    return -1;
  }

  int32_t ret = 0;
  ret += lsm6dsv_ui_i2c_i3c_mode_set(&ctx, LSM6DSV_I2C_I3C_DISABLE); /* SPI only */
  ret += lsm6dsv_block_data_update_set(&ctx, PROPERTY_ENABLE);      /* no torn L/H bytes */
  ret += lsm6dsv_xl_mode_set(&ctx, LSM6DSV_XL_HIGH_PERFORMANCE_MD);
  ret += lsm6dsv_gy_mode_set(&ctx, LSM6DSV_GY_HIGH_PERFORMANCE_MD);
  ret += lsm6dsv_xl_full_scale_set(&ctx, LSM6DSV_4g);
  ret += lsm6dsv_gy_full_scale_set(&ctx, LSM6DSV_1000dps);
  ret += lsm6dsv_xl_data_rate_set(&ctx, LSM6DSV_ODR_AT_120Hz);
  ret += lsm6dsv_gy_data_rate_set(&ctx, LSM6DSV_ODR_AT_120Hz);
  return (ret == 0) ? 0 : -1;
}

int imu_lsm6dsv_read(imu_sample_t *out)
{
  int16_t a[3], g[3], t;

  if (lsm6dsv_acceleration_raw_get(&ctx, a) != 0 ||
      lsm6dsv_angular_rate_raw_get(&ctx, g) != 0 ||
      lsm6dsv_temperature_raw_get(&ctx, &t) != 0)
  {
    return -1;
  }
  for (int i = 0; i < 3; i++)
  {
    out->accel_mg[i]  = lsm6dsv_from_fs4_to_mg(a[i]);
    out->gyro_mdps[i] = lsm6dsv_from_fs1000_to_mdps(g[i]);
  }
  out->temp_c = lsm6dsv_from_lsb_to_celsius(t);
  return 0;
}
