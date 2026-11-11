/**
  * VL53L9 transport (see lidar_bus.h). STOP-delimited register access, bounded
  * polling transfers (needs the HAL I3C fixes, vendor/patches/), DAA at 1 MHz
  * and a reset back to the known GPIO path when anything fails.
  *
  * The I3C peripheral is driven through a private handle and reset here, because
  * the pins move between GPIO (soft I2C discovery/fallback) and I3C at runtime.
  * CubeMX2's own I3C1 init (mx_i3c1.c) runs at boot but is not used afterwards.
  */
#include <string.h>
#include "stm32_hal.h"
#include "stm32_utils_i3c.h"
#include "mx_gpio_default.h"
#include "soft_i2c.h"
#include "lidar_bus.h"

#define TRANSFER_TIMEOUT_MS   20U
#define I3C_MAX_READ          1024U   /* tested on this sensor: 12 MHz, 1024-byte blocks */
#define I2C_MAX_READ          128U
#define WRITE_MAX             256U

lidar_bus_info_t g_lidar_bus = {.mode = LIDAR_BUS_SOFT_I2C, .address = LIDAR_STATIC_ADDR};

static hal_i3c_handle_t bus;
static uint8_t tx[WRITE_MAX + 2U];

/* pure = 1: pure I3C bus at hz; pure = 0: mixed bus, legacy I2C at 400 kHz open-drain. */
static int set_timing(uint32_t hz, int pure)
{
  stm32_utils_i3c_ctrl_timing_config_t c = {
    .clock_src_freq_hz = HAL_RCC_I3C1_GetKernelClkFreq(),
    .i3c_pp_freq_hz = hz,
    .i2c_od_freq_hz = 400000U,
    .duty_cycle_purcent = 50U,
    .wait_time = STM32_UTILS_I3C_ACTIVITY_STATE_0,
    .bus_type = pure ? STM32_UTILS_I3C_PURE_I3C_BUS : STM32_UTILS_I3C_I2C_MIXED_BUS,
  };
  hal_i3c_ctrl_config_t cc = {0};

  if (STM32_UTILS_I3C_CTRL_ComputeTiming(&c, &cc.timing_reg0, &cc.timing_reg1) != STM32_UTILS_I3C_OK ||
      HAL_I3C_CTRL_SetConfig(&bus, &cc) != HAL_OK)
  {
    return -1;
  }
  g_lidar_bus.bus_hz = pure ? hz : 400000U;
  return 0;
}

static int transfer(uint8_t *data, uint32_t n, int read)
{
  hal_i3c_transfer_ctx_t ctx;
  uint32_t control;
  hal_i3c_private_desc_t desc = {
    g_lidar_bus.address, n, read ? HAL_I3C_DIRECTION_READ : HAL_I3C_DIRECTION_WRITE
  };

  hal_status_t s = HAL_I3C_CTRL_ResetTransferCtx(&ctx);
  if (s == HAL_OK) s = HAL_I3C_CTRL_InitTransferCtxTc(&ctx, &control, 1U);
  if (s == HAL_OK) s = read ? HAL_I3C_CTRL_InitTransferCtxRx(&ctx, data, n)
                            : HAL_I3C_CTRL_InitTransferCtxTx(&ctx, data, n);
  if (s == HAL_OK) s = HAL_I3C_CTRL_BuildTransferCtxPrivate(&ctx, &desc, 1U,
                         g_lidar_bus.mode == LIDAR_BUS_I3C ? HAL_I3C_PRIVATE_WITH_ARB_STOP
                                                           : HAL_I2C_PRIVATE_WITHOUT_ARB_STOP);
  if (s == HAL_OK) s = HAL_I3C_CTRL_Transfer(&bus, &ctx, TRANSFER_TIMEOUT_MS);
  if (s != HAL_OK)
  {
    g_lidar_bus.failures++;
    return -1;
  }
  return 0;
}

int lidar_bus_read(uint16_t reg, uint8_t *data, uint32_t n)
{
  if (g_lidar_bus.mode == LIDAR_BUS_SOFT_I2C)
  {
    if (soft_i2c_read(LIDAR_STATIC_ADDR, reg, data, n) != 0)
    {
      g_lidar_bus.failures++;
      return -1;
    }
    return 0;
  }
  uint8_t index[2] = {(uint8_t)(reg >> 8), (uint8_t)reg};
  if (transfer(index, 2U, 0) != 0)
  {
    return -1;
  }
  return transfer(data, n, 1);
}

int lidar_bus_write(uint16_t reg, const uint8_t *data, uint32_t n)
{
  if (g_lidar_bus.mode == LIDAR_BUS_SOFT_I2C)
  {
    if (soft_i2c_write(LIDAR_STATIC_ADDR, reg, data, n) != 0)
    {
      g_lidar_bus.failures++;
      return -1;
    }
    return 0;
  }
  if (n > WRITE_MAX)
  {
    return -1;
  }
  tx[0] = (uint8_t)(reg >> 8);
  tx[1] = (uint8_t)reg;
  memcpy(&tx[2], data, n);
  return transfer(tx, n + 2U, 0);
}

uint32_t lidar_bus_max_read(void)
{
  return g_lidar_bus.mode == LIDAR_BUS_I3C ? I3C_MAX_READ : I2C_MAX_READ;
}

int lidar_bus_speed(uint32_t hz)
{
  if (g_lidar_bus.mode != LIDAR_BUS_I3C)
  {
    return 0;
  }
  if (hz != 1000000U && hz != 6000000U && hz != 12000000U)
  {
    return -1;
  }
  return set_timing(hz, 1);
}

void lidar_bus_fallback(void)
{
  /* A target that holds a dynamic address can't be reused as I2C: power-cycle it. */
  HAL_GPIO_WritePin(LIDAR_SHDN_PORT, LIDAR_SHDN_PIN, HAL_GPIO_PIN_RESET);
  HAL_RCC_I3C1_Reset();
  HAL_RCC_I3C1_DisableClock();
  g_lidar_bus.mode = LIDAR_BUS_SOFT_I2C;
  g_lidar_bus.address = LIDAR_STATIC_ADDR;
  g_lidar_bus.bus_hz = 1000000U;
  soft_i2c_init();
  HAL_Delay(10U);
  HAL_GPIO_WritePin(LIDAR_SHDN_PORT, LIDAR_SHDN_PIN, HAL_GPIO_PIN_SET);
  HAL_Delay(50U);
}

int lidar_bus_init(void)
{
  uint32_t id = 0;
  uint64_t payload = 0;
  hal_i3c_target_detection_status_t detected;

  HAL_RCC_I3C1_EnableClock();
  HAL_RCC_I3C1_Reset();

  /* SDA = PA8 (AF2), SCL = PB4 (AF3). */
  hal_gpio_config_t g = {0};
  g.mode = HAL_GPIO_MODE_ALTERNATE;
  g.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  g.pull = HAL_GPIO_PULL_NO;
  g.speed = HAL_GPIO_SPEED_FREQ_HIGH;
  g.alternate = HAL_GPIO_AF_2;
  if (HAL_GPIO_Init(HAL_GPIOA, HAL_GPIO_PIN_8, &g) != HAL_OK) goto fail;
  g.alternate = HAL_GPIO_AF_3;
  if (HAL_GPIO_Init(HAL_GPIOB, HAL_GPIO_PIN_4, &g) != HAL_OK) goto fail;

  if (HAL_I3C_Init(&bus, HAL_I3C1) != HAL_OK) goto fail;
  if (HAL_RCC_I3C1_SetKernelClkSource(HAL_RCC_I3C1_CLK_SRC_PCLK1) != HAL_OK) goto fail;

  /* 1. Legacy I2C on the mixed bus, static address. */
  if (set_timing(1000000U, 0) != 0) goto fail;
  hal_i3c_ctrl_fifo_config_t fifo = {
    .tx_fifo_threshold = HAL_I3C_TX_FIFO_THRESHOLD_1_8,
    .rx_fifo_threshold = HAL_I3C_RX_FIFO_THRESHOLD_1_8,
    .ctrl_fifo = HAL_I3C_CTRL_FIFO_NONE,
  };
  if (HAL_I3C_CTRL_SetConfigFifo(&bus, &fifo) != HAL_OK) goto fail;
  g_lidar_bus.mode = LIDAR_BUS_HW_I2C;
  g_lidar_bus.address = LIDAR_STATIC_ADDR;
  if (lidar_bus_read(0x0000U, (uint8_t *)&id, 4U) != 0 || id != LIDAR_DEVICE_ID) goto fail;

  /* 2. ENTDAA at 1 MHz: exactly one target must answer, then none. */
  if (set_timing(1000000U, 1) != 0) goto fail;
  if (HAL_I3C_CTRL_DynAddrAssign(&bus, &payload, HAL_I3C_DYN_ADDR_ONLY_ENTDAA, &detected, 20U) != HAL_OK ||
      detected != HAL_I3C_TGT_DETECTED) goto fail;
  g_lidar_bus.pid = payload;
  if (HAL_I3C_CTRL_SetDynAddr(&bus, LIDAR_DYNAMIC_ADDR) != HAL_OK) goto fail;
  payload = 0;
  if (HAL_I3C_CTRL_DynAddrAssign(&bus, &payload, HAL_I3C_DYN_ADDR_ONLY_ENTDAA, &detected, 20U) != HAL_OK ||
      detected != HAL_I3C_TGT_NOT_DETECTED) goto fail;
  hal_i3c_ctrl_device_config_t device = {0};
  device.tgt_dynamic_addr = LIDAR_DYNAMIC_ADDR;
  if (HAL_I3C_CTRL_SetConfigBusDevices(&bus, &device, 1U) != HAL_OK) goto fail;

  /* 3. I3C SDR at the dynamic address: verify repeatedly. */
  g_lidar_bus.mode = LIDAR_BUS_I3C;
  g_lidar_bus.address = LIDAR_DYNAMIC_ADDR;
  for (unsigned i = 0; i < 8U; i++)
  {
    if (lidar_bus_read(0x0000U, (uint8_t *)&id, 4U) != 0 || id != LIDAR_DEVICE_ID) goto fail;
  }
  return 0;

fail:
  lidar_bus_fallback();
  return -1;
}
