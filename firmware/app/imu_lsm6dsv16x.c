/**
  * LSM6DSV16X backend (WHO_AM_I 0x70), using ST's lsm6dsv16x-pid driver.
  * Selected for 0x70 when built with IMU_ID70_IS_LSM6DSV16X=1 (see imu.h).
  */
#include "imu_backend.h"
#include "mx_spi1.h"
#include "lsm6dsv16x_reg.h"

static stmdev_ctx_t ctx;

int imu_lsm6dsv16x_init(void)
{
  uint8_t id = 0U;

  ctx.write_reg = imu_bus_write;
  ctx.read_reg  = imu_bus_read;
  ctx.mdelay    = imu_bus_delay_ms;
  ctx.handle    = mx_spi1_gethandle();

  if (lsm6dsv16x_device_id_get(&ctx, &id) != 0 || id != LSM6DSV16X_ID)
  {
    return -1;
  }

  /* Power down, software reset, wait until done (handled by ST's driver). */
  if (lsm6dsv16x_sw_reset(&ctx) != 0)
  {
    return -1;
  }

  int32_t ret = 0;
  ret += lsm6dsv16x_ui_i2c_i3c_mode_set(&ctx, LSM6DSV16X_I2C_I3C_DISABLE); /* SPI only */
  ret += lsm6dsv16x_block_data_update_set(&ctx, PROPERTY_ENABLE);         /* no torn L/H bytes */
  ret += lsm6dsv16x_xl_mode_set(&ctx, LSM6DSV16X_XL_HIGH_PERFORMANCE_MD);
  ret += lsm6dsv16x_gy_mode_set(&ctx, LSM6DSV16X_GY_HIGH_PERFORMANCE_MD);
  ret += lsm6dsv16x_xl_full_scale_set(&ctx, LSM6DSV16X_4g);
  ret += lsm6dsv16x_gy_full_scale_set(&ctx, LSM6DSV16X_1000dps);
  ret += lsm6dsv16x_xl_data_rate_set(&ctx, LSM6DSV16X_ODR_AT_120Hz);
  ret += lsm6dsv16x_gy_data_rate_set(&ctx, LSM6DSV16X_ODR_AT_120Hz);
  return (ret == 0) ? 0 : -1;
}

int imu_lsm6dsv16x_read(imu_sample_t *out)
{
  int16_t a[3], g[3], t;

  if (lsm6dsv16x_acceleration_raw_get(&ctx, a) != 0 ||
      lsm6dsv16x_angular_rate_raw_get(&ctx, g) != 0 ||
      lsm6dsv16x_temperature_raw_get(&ctx, &t) != 0)
  {
    return -1;
  }
  for (int i = 0; i < 3; i++)
  {
    out->accel_mg[i]  = lsm6dsv16x_from_fs4_to_mg(a[i]);
    out->gyro_mdps[i] = lsm6dsv16x_from_fs1000_to_mdps(g[i]);
  }
  out->temp_c = lsm6dsv16x_from_lsb_to_celsius(t);
  return 0;
}
