/**
  * STM32C552 platform layer for ST's portable VL53L9 driver (vendor/vl53l9).
  * Register index big-endian, register values little-endian.
  * Long transfers are split into chunks, and app_background() runs between chunks
  * and during waits so USB and the IMU keep working while the LiDAR is busy.
  * p_dev points to the AP clock frequency (uint32_t, Hz).
  * Ported from VL53L9-UNO-Q-LiDAR (application/vl53l9_platform.c).
  */
#include "stm32_hal.h"
#include "lidar_bus.h"
#include "app.h"
#include "vl53l9_platform.h"

#define WRITE_CHUNK 128U

int vl53l9_read(void *const p_dev, uint16_t address, uint8_t *p_values, uint32_t size)
{
  (void)p_dev;
  uint32_t limit = lidar_bus_max_read();
  for (uint32_t i = 0; i < size;)
  {
    uint32_t k = size - i;
    if (k > limit)
    {
      k = limit;
    }
    if (lidar_bus_read((uint16_t)(address + i), p_values + i, k) != 0)
    {
      return VL53L9_ERROR_PLATFORM;
    }
    i += k;
    app_background();
  }
  return VL53L9_ERROR_NONE;
}

int vl53l9_write(void *const p_dev, uint16_t address, uint8_t *p_values, uint32_t size)
{
  (void)p_dev;
  for (uint32_t i = 0; i < size;)
  {
    uint32_t k = size - i;
    if (k > WRITE_CHUNK)
    {
      k = WRITE_CHUNK;
    }
    if (lidar_bus_write((uint16_t)(address + i), p_values + i, k) != 0)
    {
      return VL53L9_ERROR_PLATFORM;
    }
    i += k;
    app_background();
  }
  return VL53L9_ERROR_NONE;
}

int vl53l9_read8(void *const p_dev, uint16_t address, uint8_t *p_value)
{
  return vl53l9_read(p_dev, address, p_value, 1U);
}

int vl53l9_read16(void *const p_dev, uint16_t address, uint16_t *p_value)
{
  uint8_t b[2];
  int e = vl53l9_read(p_dev, address, b, 2U);
  if (e == 0)
  {
    *p_value = (uint16_t)(b[0] | ((uint16_t)b[1] << 8));
  }
  return e;
}

int vl53l9_read32(void *const p_dev, uint16_t address, uint32_t *p_value)
{
  uint8_t b[4];
  int e = vl53l9_read(p_dev, address, b, 4U);
  if (e == 0)
  {
    *p_value = (uint32_t)b[0] | ((uint32_t)b[1] << 8) | ((uint32_t)b[2] << 16) | ((uint32_t)b[3] << 24);
  }
  return e;
}

int vl53l9_write8(void *const p_dev, uint16_t address, uint8_t value)
{
  return vl53l9_write(p_dev, address, &value, 1U);
}

int vl53l9_write16(void *const p_dev, uint16_t address, uint16_t value)
{
  uint8_t b[2] = {(uint8_t)value, (uint8_t)(value >> 8)};
  return vl53l9_write(p_dev, address, b, 2U);
}

int vl53l9_write32(void *const p_dev, uint16_t address, uint32_t value)
{
  uint8_t b[4] = {(uint8_t)value, (uint8_t)(value >> 8), (uint8_t)(value >> 16), (uint8_t)(value >> 24)};
  return vl53l9_write(p_dev, address, b, 4U);
}

int vl53l9_wait_ms(void *const p_dev, uint32_t delay_ms)
{
  (void)p_dev;
  uint32_t start = HAL_GetTick();
  while (HAL_GetTick() - start < delay_ms)
  {
    app_background();
  }
  return VL53L9_ERROR_NONE;
}

/* Board supplies: IOVDD 1.8 V, AVDD 2.8 V (TLV73318 / TLV73328). */
int vl53l9_get_config_vddio(void *const p_dev, vl53l9_vddio_t *voltage)
{
  (void)p_dev;
  *voltage = VDDIO_1V8;
  return VL53L9_ERROR_NONE;
}

int vl53l9_get_config_vdda(void *const p_dev, vl53l9_vdda_t *voltage)
{
  (void)p_dev;
  *voltage = VDDA_2V8;
  return VL53L9_ERROR_NONE;
}

int vl53l9_get_config_ext_clock(void *const p_dev, uint32_t *ext_clock)
{
  *ext_clock = *(const uint32_t *)p_dev;
  return VL53L9_ERROR_NONE;
}

/* Asynchronous reads are not supported by this platform. */
int vl53l9_read_async(void *const p_dev, uint16_t address, volatile uint8_t *p_values, uint32_t size)
{
  (void)p_dev; (void)address; (void)p_values; (void)size;
  return VL53L9_ERROR_INVALID_OPERATION;
}
