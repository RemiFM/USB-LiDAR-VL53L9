/**
  * IMU layer: SPI1 bus access, runtime detection and dispatch to the right
  * ST driver backend. See imu.h for the supported parts.
  */
#include "imu.h"
#include "imu_backend.h"
#include "stm32_hal.h"
#include "mx_gpio_default.h"
#include "mx_spi1.h"

#define IMU_REG_WHO_AM_I   0x0FU
#define IMU_REG_STATUS     0x1EU   /* bit0 XLDA (accel ready), bit1 GDA (gyro ready) */
#define IMU_ID_70          0x70U   /* LSM6DSV, LSM6DSV16X */
#define IMU_ID_71          0x71U   /* LSM6DSV16BX */
#define IMU_SPI_READ       0x80U   /* MSB of the address byte set = read */
#define IMU_SPI_TIMEOUT_MS 10U

static imu_variant_t variant = IMU_NONE;
static uint8_t whoami;

/* ------------------------------------------------------------------------- */
/* SPI bus                                                                   */
/* ------------------------------------------------------------------------- */

static void cs_low(void)  { HAL_GPIO_WritePin(SPI_CSN_PORT, SPI_CSN_PIN, HAL_GPIO_PIN_RESET); }
static void cs_high(void) { HAL_GPIO_WritePin(SPI_CSN_PORT, SPI_CSN_PIN, HAL_GPIO_PIN_SET); }

int32_t imu_bus_write(void *handle, uint8_t reg, const uint8_t *data, uint16_t len)
{
  hal_spi_handle_t *hspi = (hal_spi_handle_t *)handle;
  uint8_t addr = reg & 0x7FU;
  int32_t ret = 0;

  cs_low();
  if (HAL_SPI_Transmit(hspi, &addr, 1U, IMU_SPI_TIMEOUT_MS) != HAL_OK ||
      HAL_SPI_Transmit(hspi, data, len, IMU_SPI_TIMEOUT_MS) != HAL_OK)
  {
    ret = -1;
  }
  cs_high();
  return ret;
}

int32_t imu_bus_read(void *handle, uint8_t reg, uint8_t *data, uint16_t len)
{
  hal_spi_handle_t *hspi = (hal_spi_handle_t *)handle;
  uint8_t addr = reg | IMU_SPI_READ;
  int32_t ret = 0;

  cs_low();
  if (HAL_SPI_Transmit(hspi, &addr, 1U, IMU_SPI_TIMEOUT_MS) != HAL_OK ||
      HAL_SPI_Receive(hspi, data, len, IMU_SPI_TIMEOUT_MS) != HAL_OK)
  {
    ret = -1;
  }
  cs_high();
  return ret;
}

void imu_bus_delay_ms(uint32_t ms)
{
  HAL_Delay(ms);
}

/* SPI1 itself is configured by CubeMX2 (generated/hal/mx_spi1.c): master,
   8-bit, mode 0, prescaler 32 -> 144 MHz / 32 = 4.5 MHz, software CS on PA4.
   The LSM6DSV family allows at most 10 MHz (datasheet fc(SPC)) and supports
   SPI mode 0 and mode 3. Keep the prescaler at 16 or higher in CubeMX2. */

/* ------------------------------------------------------------------------- */
/* Detection and dispatch                                                    */
/* ------------------------------------------------------------------------- */

int imu_init(void)
{
  hal_spi_handle_t *hspi = mx_spi1_gethandle();
  int ret;

  variant = IMU_NONE;
  whoami = 0U;

  cs_high();
  if (hspi == NULL)
  {
    return -1;
  }

  /* Boot time after power-up is max ~10 ms; we usually start later than that. */
  HAL_Delay(10U);

  /* The chip starts in I2C/I3C/SPI auto-detect mode: the first SPI transfer
     may be lost while it switches, so read WHO_AM_I twice. */
  (void)imu_bus_read(hspi, IMU_REG_WHO_AM_I, &whoami, 1U);
  if (imu_bus_read(hspi, IMU_REG_WHO_AM_I, &whoami, 1U) != 0)
  {
    return -2;
  }

  switch (whoami)
  {
    case IMU_ID_71:
      variant = IMU_LSM6DSV16BX;
      ret = imu_lsm6dsv16bx_init();
      break;

    case IMU_ID_70:
#if defined(IMU_ID70_IS_LSM6DSV16X) && (IMU_ID70_IS_LSM6DSV16X != 0)
      variant = IMU_LSM6DSV16X;
      ret = imu_lsm6dsv16x_init();
#else
      variant = IMU_LSM6DSV;
      ret = imu_lsm6dsv_init();
#endif
      break;

    default:
      return -3; /* 0x00/0xFF: no answer (wiring, power, SPI mode); other: unknown part */
  }

  if (ret != 0)
  {
    variant = IMU_NONE;
    return -4;
  }
  return 0;
}

int imu_read(imu_sample_t *out)
{
  switch (variant)
  {
    case IMU_LSM6DSV:     return imu_lsm6dsv_read(out);
    case IMU_LSM6DSV16X:  return imu_lsm6dsv16x_read(out);
    case IMU_LSM6DSV16BX: return imu_lsm6dsv16bx_read(out);
    default:              return -1;
  }
}

int imu_data_ready(void)
{
  uint8_t status;

  if (variant == IMU_NONE)
  {
    return -1;
  }
  if (imu_bus_read(mx_spi1_gethandle(), IMU_REG_STATUS, &status, 1U) != 0)
  {
    return -1;
  }
  return ((status & 0x03U) == 0x03U) ? 1 : 0;
}

imu_variant_t imu_variant(void)
{
  return variant;
}

char const *imu_name(void)
{
  switch (variant)
  {
    case IMU_LSM6DSV:     return "LSM6DSV";
    case IMU_LSM6DSV16X:  return "LSM6DSV16X";
    case IMU_LSM6DSV16BX: return "LSM6DSV16BX";
    default:              return "none";
  }
}

uint8_t imu_whoami(void)
{
  return whoami;
}
