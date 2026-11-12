/**
  * Cycle-timed open-drain I2C (see soft_i2c.h). Register index is 16-bit big-endian,
  * as the VL53L9 expects; a STOP separates the index write from the data read.
  * GPIO registers are accessed directly to avoid per-edge HAL overhead.
  */
#include "stm32_hal.h"
#include "soft_i2c.h"

static uint32_t low_cycles, high_cycles;
static int recovery_timing;

static inline __attribute__((always_inline)) void cycles(uint32_t n)
{
  uint32_t start = DWT->CYCCNT;
  while ((uint32_t)(DWT->CYCCNT - start) < n)
  {
    __NOP();
  }
}
static inline __attribute__((always_inline)) void delay(void) { cycles(low_cycles); }
static inline __attribute__((always_inline)) void sda(int high) { GPIOA->BSRR = high ? (1U << 8) : (1U << 24); }
static inline __attribute__((always_inline)) void scl(int high) { GPIOB->BSRR = high ? (1U << 4) : (1U << 20); }
static inline __attribute__((always_inline)) int rd_sda(void) { return (GPIOA->IDR & (1U << 8)) != 0U; }

/* Releases SCL and waits (max 5 ms) while the target stretches the clock. */
static inline __attribute__((always_inline)) int high_scl(void)
{
  scl(1);
  if (!(GPIOB->IDR & (1U << 4)))
  {
    uint32_t start = HAL_GetTick();
    while (!(GPIOB->IDR & (1U << 4)))
    {
      if (HAL_GetTick() - start >= 5U)
      {
        return 2;
      }
    }
  }
  cycles(high_cycles);
  return 0;
}

static int stop(void)
{
  scl(0); sda(0); delay();
  int ret = high_scl();
  sda(1); delay();
  return ret;
}

static int start(void)
{
  sda(1);
  if (high_scl() || !rd_sda())
  {
    return 2;
  }
  sda(0); delay(); scl(0);
  return 0;
}

static int put(uint8_t b)
{
  for (unsigned i = 0; i < 8U; i++)
  {
    sda((b & 0x80U) != 0U);
    b <<= 1;
    delay();
    if (high_scl())
    {
      return 2;
    }
    scl(0);
  }
  sda(1); delay();
  if (high_scl())
  {
    return 2;
  }
  int nack = rd_sda();
  scl(0);
  return nack;
}

void soft_i2c_relax(void)
{
  recovery_timing = 1;
}

void soft_i2c_init(void)
{
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;   /* never reset CYCCNT: timebase.c uses it */

  uint32_t mhz = HAL_RCC_GetSYSCLKFreq() / 1000000U;
  low_cycles = (mhz + 1U) / 2U;           /* >= 500 ns (Fast-mode Plus) */
  high_cycles = mhz * 27U / 100U + 1U;    /* >= 270 ns */
  if (recovery_timing)
  {
    low_cycles = mhz * 13U / 10U + 1U;    /* >= 1.3 us (Fast mode) */
    high_cycles = mhz * 7U / 10U + 1U;    /* >= 0.7 us */
  }

  hal_gpio_config_t g = {0};
  g.mode = HAL_GPIO_MODE_OUTPUT;
  g.output_type = HAL_GPIO_OUTPUT_OPENDRAIN;
  g.pull = HAL_GPIO_PULL_NO;
  g.speed = HAL_GPIO_SPEED_FREQ_LOW;
  g.init_state = HAL_GPIO_PIN_SET;
  HAL_RCC_GPIOA_EnableClock();
  HAL_RCC_GPIOB_EnableClock();
  HAL_GPIO_Init(HAL_GPIOA, HAL_GPIO_PIN_8, &g);
  HAL_GPIO_Init(HAL_GPIOB, HAL_GPIO_PIN_4, &g);
  delay();
}

int soft_i2c_probe(uint8_t address)
{
  int ret = start();
  if (!ret)
  {
    ret = put((uint8_t)(address << 1));
  }
  int end = stop();
  return ret ? ret : end;
}

int soft_i2c_read(uint8_t address, uint16_t reg, uint8_t *data, uint32_t size)
{
  int ret = start();
  if (!ret) ret = put((uint8_t)(address << 1));
  if (!ret) ret = put((uint8_t)(reg >> 8));
  if (!ret) ret = put((uint8_t)reg);
  int end = stop();
  if (ret || end)
  {
    return ret ? ret : end;
  }

  ret = start();
  if (!ret) ret = put((uint8_t)((address << 1) | 1U));
  for (uint32_t n = 0; !ret && n < size; n++)
  {
    uint8_t b = 0;
    sda(1);
    for (unsigned i = 0; i < 8U; i++)
    {
      delay();
      ret = high_scl();
      if (ret)
      {
        break;
      }
      b = (uint8_t)((b << 1) | rd_sda());
      scl(0);
    }
    if (ret)
    {
      break;
    }
    data[n] = b;
    sda(n == size - 1U);   /* ACK all but the last byte */
    delay();
    ret = high_scl();
    scl(0);
    sda(1);
  }
  end = stop();
  return ret ? ret : end;
}

int soft_i2c_write(uint8_t address, uint16_t reg, const uint8_t *data, uint32_t size)
{
  int ret = start();
  if (!ret) ret = put((uint8_t)(address << 1));
  if (!ret) ret = put((uint8_t)(reg >> 8));
  if (!ret) ret = put((uint8_t)reg);
  for (uint32_t n = 0; !ret && n < size; n++)
  {
    ret = put(data[n]);
  }
  int end = stop();
  return ret ? ret : end;
}
