/**
  * LSM6DSV16BX backend (WHO_AM_I 0x71), using ST's lsm6dsv16bx-pid driver.
  * Note: on this part the accelerometer output registers are ordered Z, Y, X;
  * lsm6dsv16bx_acceleration_raw_get() already returns them as X, Y, Z.
  */
#include "imu_backend.h"
#include "mx_spi1.h"
#include "lsm6dsv16bx_reg.h"

static stmdev_ctx_t ctx;

int imu_lsm6dsv16bx_init(void)
{
  lsm6dsv16bx_reset_t rst;
  uint8_t id = 0U;
  uint32_t tries = 0U;

  ctx.write_reg = imu_bus_write;
  ctx.read_reg  = imu_bus_read;
  ctx.mdelay    = imu_bus_delay_ms;
  ctx.handle    = mx_spi1_gethandle();

  if (lsm6dsv16bx_device_id_get(&ctx, &id) != 0 || id != LSM6DSV16BX_ID)
  {
    return -1;
  }

  /* Restore default control registers and wait for the reset to finish. */
  if (lsm6dsv16bx_reset_set(&ctx, LSM6DSV16BX_RESTORE_CTRL_REGS) != 0)
  {
    return -1;
  }
  do
  {
    imu_bus_delay_ms(1U);
    if (lsm6dsv16bx_reset_get(&ctx, &rst) != 0)
    {
      return -1;
    }
  } while (rst != LSM6DSV16BX_READY && ++tries < 50U);
  if (rst != LSM6DSV16BX_READY)
  {
    return -1;
  }

  int32_t ret = 0;
  ret += lsm6dsv16bx_ui_i2c_i3c_mode_set(&ctx, LSM6DSV16BX_I2C_I3C_DISABLE); /* SPI only */
  ret += lsm6dsv16bx_block_data_update_set(&ctx, PROPERTY_ENABLE);  /* no torn L/H bytes */
  ret += lsm6dsv16bx_xl_mode_set(&ctx, LSM6DSV16BX_XL_HIGH_PERFORMANCE_MD);
  ret += lsm6dsv16bx_gy_mode_set(&ctx, LSM6DSV16BX_GY_HIGH_PERFORMANCE_MD);
  ret += lsm6dsv16bx_xl_full_scale_set(&ctx, LSM6DSV16BX_4g);
  ret += lsm6dsv16bx_gy_full_scale_set(&ctx, LSM6DSV16BX_1000dps);
  ret += lsm6dsv16bx_xl_data_rate_set(&ctx, LSM6DSV16BX_XL_ODR_AT_120Hz);
  ret += lsm6dsv16bx_gy_data_rate_set(&ctx, LSM6DSV16BX_GY_ODR_AT_120Hz);
  return (ret == 0) ? 0 : -1;
}

int imu_lsm6dsv16bx_read(imu_sample_t *out)
{
  int16_t a[3], g[3], t;

  if (lsm6dsv16bx_acceleration_raw_get(&ctx, a) != 0 ||
      lsm6dsv16bx_angular_rate_raw_get(&ctx, g) != 0 ||
      lsm6dsv16bx_temperature_raw_get(&ctx, &t) != 0)
  {
    return -1;
  }
  for (int i = 0; i < 3; i++)
  {
    out->accel_mg[i]  = lsm6dsv16bx_from_fs4_to_mg(a[i]);
    out->gyro_mdps[i] = lsm6dsv16bx_from_fs1000_to_mdps(g[i]);
  }
  out->temp_c = lsm6dsv16bx_from_lsb_to_celsius(t);
  return 0;
}
