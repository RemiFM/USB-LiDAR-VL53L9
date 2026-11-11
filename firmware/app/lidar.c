/**
  * VL53L9CX LiDAR (see lidar.h). Bring-up and configuration follow the sequence
  * validated by VL53L9-UNO-Q-LiDAR (application/example.c, lidar_smoke.c):
  *   AP clock (16 MHz HSE on MCO2/PA9, started by CubeMX2's mx_rcc_init) running
  *   -> XSHUT high -> wait for READY-TO-BOOT -> ID over bit-banged I2C
  *   -> I3C bring-up -> vl53l9_init (boot + firmware patch) -> calibration -> config.
  * Start/stop run at 1 MHz; streaming switches the I3C bus to 12 MHz.
  */
#include <string.h>
#include "stm32_hal.h"
#include "mx_gpio_default.h"
#include "lidar.h"
#include "lidar_bus.h"
#include "soft_i2c.h"
#include "protocol.h"
#include "proto_tx.h"
#include "timebase.h"
#include "app.h"
#include "vl53l9.h"
#include "vl53l9_platform.h"
#include "vl53l9_reg.h"

#define AP_CLOCK_HZ          16000000U  /* Y1 crystal via MCO2 */
#define BINNING              2U
#define EXPOSURE_MS          6U
#define FRAME_TIMEOUT_MS     2000U
#define POLL_INTERVAL_US     500U
#define STREAM_BUS_HZ        12000000U
#define CONTROL_BUS_HZ       1000000U

lidar_info_t g_lidar;

static uint32_t ap_clock_hz = AP_CLOCK_HZ;   /* driver's p_dev */
static uint8_t calibration[LIDAR_CALIB_SIZE];
static bool calibration_valid;

/* Ping-pong frame buffers: one may be on its way to USB while the other is read. */
static uint8_t frames[2][LIDAR_RAW_SIZE];
static uint32_t next_buf;
static bool triggered;
static uint32_t trigger_ms;
static uint64_t last_poll_us;

_Static_assert(LIDAR_RAW_SIZE == 14842U, "raw frame size for binning 2");
_Static_assert(LIDAR_CALIB_SIZE == VL53L9_CALIB_DATA_SIZE, "calibration size");

/* ------------------------------------------------------------------ helpers */

static int fail(int ret, const char *where)
{
  g_lidar.errors++;
  g_lidar.last_error = ret;
  g_lidar.last_error_where = where;
  app_log("LiDAR error %d in %s", ret, where);
  return ret;
}

#define TRY(call, where) do { int _r = (call); if (_r != 0) return fail(_r, where); } while (0)

/* XSHUT low -> high with the AP clock already running, then wait for READY-TO-BOOT. */
static void power_cycle(void)
{
  /* AP clock: 16 MHz on PA9 (MCO2). The pin needs a fast output driver for clean
     16 MHz edges (the reference firmware uses HIGH; CubeMX2's default is LOW). */
  hal_gpio_config_t g = {0};
  g.mode = HAL_GPIO_MODE_ALTERNATE;
  g.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  g.pull = HAL_GPIO_PULL_NO;
  g.speed = HAL_GPIO_SPEED_FREQ_HIGH;
  g.alternate = HAL_GPIO_AF_0;
  (void)HAL_GPIO_Init(HAL_GPIOA, HAL_GPIO_PIN_9, &g);

  HAL_GPIO_WritePin(LIDAR_SHDN_PORT, LIDAR_SHDN_PIN, HAL_GPIO_PIN_RESET);
  app_wait_ms(50U);
  HAL_GPIO_WritePin(LIDAR_SHDN_PORT, LIDAR_SHDN_PIN, HAL_GPIO_PIN_SET);
  app_wait_ms(200U);
}

static int configure(void)
{
  uint32_t id = 0;
  uint16_t size = 0;

  TRY(vl53l9_get_device_id(&ap_clock_hz, &id), "get_device_id");
  g_lidar.device_id = id;
  if (id != LIDAR_DEVICE_ID)
  {
    return fail(VL53L9_ERROR_INVALID_STATE, "device id");
  }
  TRY(vl53l9_init(&ap_clock_hz), "init (boot + patch)");
  TRY(vl53l9_read16(&ap_clock_hz, VL53L9_REGADDR_PATCH_REVISION, &g_lidar.patch_revision), "patch revision");
  TRY(vl53l9_get_calib_data(&ap_clock_hz, calibration), "calibration");
  calibration_valid = true;

  vl53l9_hw_config_t hw = {0};
  TRY(vl53l9_get_hw_config(&ap_clock_hz, &hw), "get_hw_config");
  hw.output_interface = true;     /* I3C/I2C, not CSI-2 */
  hw.signaling_mode = true;       /* interrupt pad, not in-band interrupt */
  hw.interrupt_pad_mode = true;   /* open drain */
  TRY(vl53l9_set_hw_config(&ap_clock_hz, hw), "set_hw_config");
  TRY(vl53l9_set_sync_mode(&ap_clock_hz, VL53L9_SYNC_MANUAL), "sync mode");
  TRY(vl53l9_set_power_mode(&ap_clock_hz, VL53L9_POWER_ULTRA_LOW), "power mode");
  TRY(vl53l9_set_context(&ap_clock_hz, VL53L9_CONTEXT_SHORT), "context");
  TRY(vl53l9_set_binning(&ap_clock_hz, VL53L9_CONTEXT_SHORT, BINNING), "binning");
  TRY(vl53l9_set_exposure(&ap_clock_hz, VL53L9_CONTEXT_SHORT, EXPOSURE_MS), "exposure");
  TRY(vl53l9_get_raw_buffer_size(BINNING, &size), "raw buffer size");
  if (size != LIDAR_RAW_SIZE)
  {
    return fail(VL53L9_ERROR_INVALID_PARAM, "raw buffer size");
  }
  return 0;
}

/* ------------------------------------------------------------------ public */

int lidar_init(void)
{
  uint8_t id[4] = {0};

  g_lidar.state = LIDAR_STATE_OFF;
  g_lidar.device_id = 0U;
  g_lidar.patch_revision = 0U;
  calibration_valid = false;
  triggered = false;

  power_cycle();

  /* Is anything there? Bit-banged I2C at the static address.
     The first register access after reset is NACKed unless an address-only
     transaction (START, address, STOP) comes first: measured on this board, 5/5
     failures without the probe, 5/5 successes with it. The reference firmware
     uses the same probe-then-read order. */
  soft_i2c_init();
  int bus = 2;
  for (int attempt = 0; attempt < 10 && bus != 0; attempt++)
  {
    if (attempt > 0)
    {
      app_wait_ms(10U);
    }
    bus = soft_i2c_probe(LIDAR_STATIC_ADDR);
  }
  if (bus == 0)
  {
    bus = soft_i2c_read(LIDAR_STATIC_ADDR, 0x0000U, id, 4U);
  }
  if (bus != 0)
  {
    /* 1 = no ACK at the address, 2 = bus stuck (SDA/SCL held low). */
    return fail(VL53L9_ERROR_PLATFORM, bus == 1 ? "detect: no ACK at 0x29" : "detect: I2C bus stuck");
  }
  uint32_t id32 = (uint32_t)id[0] | ((uint32_t)id[1] << 8) | ((uint32_t)id[2] << 16) | ((uint32_t)id[3] << 24);
  if (id32 != LIDAR_DEVICE_ID)
  {
    g_lidar.device_id = id32;
    return fail(VL53L9_ERROR_INVALID_STATE, "detect: unexpected device ID");
  }

  if (lidar_bus_init() != 0)
  {
    app_log("LiDAR: I3C bring-up failed, using bit-banged I2C (slower)");
  }

  int ret = configure();
  if (ret != 0 && g_lidar_bus.mode == LIDAR_BUS_I3C)
  {
    /* Same recovery as the reference firmware: retry once on the known-good I2C path. */
    app_log("LiDAR: retrying on bit-banged I2C");
    soft_i2c_relax();
    lidar_bus_fallback();
    ret = configure();
  }
  if (ret != 0)
  {
    g_lidar.state = LIDAR_STATE_ERROR;
    HAL_GPIO_WritePin(LIDAR_SHDN_PORT, LIDAR_SHDN_PIN, HAL_GPIO_PIN_RESET);
    return ret;
  }

  g_lidar.state = LIDAR_STATE_READY;
  return 0;
}

int lidar_start(void)
{
  if (g_lidar.state == LIDAR_STATE_STREAMING)
  {
    return 0;
  }
  if (g_lidar.state != LIDAR_STATE_READY)
  {
    return -1;
  }
  int ret = vl53l9_start(&ap_clock_hz);
  if (ret == 0)
  {
    ret = lidar_bus_speed(STREAM_BUS_HZ);
  }
  if (ret != 0)
  {
    (void)lidar_bus_speed(CONTROL_BUS_HZ);
    (void)vl53l9_stop(&ap_clock_hz);
    g_lidar.state = LIDAR_STATE_ERROR;
    return fail(ret, "start");
  }
  g_lidar.frames = 0U;
  g_lidar.dropped = 0U;
  triggered = false;
  g_lidar.state = LIDAR_STATE_STREAMING;
  return 0;
}

void lidar_stop(void)
{
  if (g_lidar.state != LIDAR_STATE_STREAMING)
  {
    return;
  }
  (void)lidar_bus_speed(CONTROL_BUS_HZ);
  int ret = vl53l9_stop(&ap_clock_hz);
  triggered = false;
  if (ret != 0)
  {
    g_lidar.state = LIDAR_STATE_ERROR;
    (void)fail(ret, "stop");
    return;
  }
  g_lidar.state = LIDAR_STATE_READY;
}

static void stream_error(int ret, const char *where)
{
  (void)fail(ret, where);
  (void)lidar_bus_speed(CONTROL_BUS_HZ);
  (void)vl53l9_stop(&ap_clock_hz);
  triggered = false;
  g_lidar.state = LIDAR_STATE_ERROR;
}

void lidar_task(void)
{
  if (g_lidar.state != LIDAR_STATE_STREAMING)
  {
    return;
  }

  if (!triggered)
  {
    int ret = vl53l9_trigger_frame(&ap_clock_hz);
    if (ret != 0)
    {
      stream_error(ret, "trigger_frame");
      return;
    }
    triggered = true;
    trigger_ms = HAL_GetTick();
    return;
  }

  /* Poll the frame-ready flag at most every POLL_INTERVAL_US. */
  uint64_t now = time_us();
  if (now - last_poll_us < POLL_INTERVAL_US)
  {
    return;
  }
  last_poll_us = now;

  uint8_t ready = 0;
  int ret = vl53l9_poll_frame(&ap_clock_hz, &ready);
  if (ret != 0)
  {
    stream_error(ret, "poll_frame");
    return;
  }
  if (!ready)
  {
    if (HAL_GetTick() - trigger_ms > FRAME_TIMEOUT_MS)
    {
      stream_error(VL53L9_ERROR_TIMEOUT, "frame timeout");
    }
    return;
  }

  /* Frame ready. Read it only into a buffer USB has finished with; otherwise
     leave it in the sensor and try again shortly (back-pressure, no drop). */
  uint8_t *buf = frames[next_buf];
  if (proto_tx_in_use(buf))
  {
    trigger_ms = HAL_GetTick();   /* not a sensor timeout: we are waiting for USB */
    return;
  }
  uint64_t t_ready = now;
  ret = vl53l9_get_frame(&ap_clock_hz, buf, (uint16_t)LIDAR_RAW_SIZE);
  if (ret != 0)
  {
    stream_error(ret, "get_frame");
    return;
  }
  triggered = false;   /* next call triggers the next frame */

  proto_lidar_frame_t hdr = {
    .frame = g_lidar.frames,
    .width = LIDAR_WIDTH,
    .height = LIDAR_HEIGHT,
    .raw_size = LIDAR_RAW_SIZE,
  };
  if (proto_tx_send_large(PKT_LIDAR_FRAME, &hdr, sizeof(hdr), buf, LIDAR_RAW_SIZE, t_ready))
  {
    g_lidar.frames++;
    next_buf ^= 1U;
  }
  else
  {
    g_lidar.dropped++;
  }
}

const uint8_t *lidar_calibration(void)
{
  return calibration_valid ? calibration : NULL;
}
