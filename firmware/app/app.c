/**
  * Application (see app.h).
  *
  * LED (PB8, active-low):  1 Hz heartbeat idle, 4 Hz while the LiDAR streams,
  *                         10 Hz if the LiDAR is in error, or manual via CMD_LED_*.
  */
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "app.h"
#include "imu.h"
#include "lidar.h"
#include "lidar_bus.h"
#include "protocol.h"
#include "proto_tx.h"
#include "timebase.h"
#include "usb_app.h"
#include "stm32_hal.h"
#include "mx_gpio_default.h"
#include "tusb.h"

#define FIRMWARE_VERSION   "0.3.0"
#define STATUS_PERIOD_US   1000000U
#define IMU_POLL_US        1000U

static bool connected;
static bool imu_streaming;
static uint32_t imu_sample;
static uint64_t last_imu_poll_us;
static uint64_t last_status_us;

/* LED */
enum { LED_HEARTBEAT = 0, LED_MANUAL_OFF = 1, LED_MANUAL_ON = 2 };
static uint8_t led_mode;
static bool led_on;
static uint32_t last_blink_ms;

/* Commands that touch the LiDAR or block run in app_loop(), never nested. */
/* LiDAR: only the most recent request counts (e.g. 'X' then 'L' in one burst = on). */
enum { LIDAR_REQ_NONE = 0, LIDAR_REQ_ON, LIDAR_REQ_OFF, LIDAR_REQ_REINIT };
static volatile uint8_t lidar_req;
static volatile bool req_imu_reinit;

/* ------------------------------------------------------------------ helpers */

static void led_set(bool on)
{
  led_on = on;
  HAL_GPIO_WritePin(LED_ONN_PORT, LED_ONN_PIN, on ? HAL_GPIO_PIN_RESET : HAL_GPIO_PIN_SET);
}

void app_log(const char *fmt, ...)
{
  char buf[160];
  va_list ap;
  va_start(ap, fmt);
  int n = vsnprintf(buf, sizeof(buf), fmt, ap);
  va_end(ap);
  if (n > 0 && tud_cdc_connected())
  {
    (void)proto_tx_send(PKT_LOG, buf, (uint32_t)((n < (int)sizeof(buf)) ? n : (int)sizeof(buf) - 1), time_us());
  }
}

void app_wait_ms(uint32_t ms)
{
  uint32_t start = HAL_GetTick();
  while (HAL_GetTick() - start < ms)
  {
    app_background();
  }
}

static const char *lidar_state_name(uint8_t s)
{
  switch (s)
  {
    case LIDAR_STATE_READY:     return "ready";
    case LIDAR_STATE_STREAMING: return "streaming";
    case LIDAR_STATE_ERROR:     return "error";
    default:                    return "off";
  }
}

static uint8_t bus_code(void)
{
  if (g_lidar.state == LIDAR_STATE_OFF && g_lidar.device_id == 0U)
  {
    return BUS_NONE;
  }
  return g_lidar_bus.mode == LIDAR_BUS_I3C ? BUS_I3C : BUS_I2C_SOFT;
}

/* PKT_INFO: "key=value\n" lines describing the device. */
static void send_info(void)
{
  char buf[PROTO_SMALL_MAX_PAYLOAD];
  int n = snprintf(buf, sizeof(buf),
    "firmware=" FIRMWARE_VERSION "\n"
    "protocol=%u\n"
    "serial=%s\n"
    "imu=%s\n"
    "imu_whoami=0x%02X\n"
    "imu_odr_hz=120\n"
    "lidar_state=%s\n"
    "lidar_device_id=0x%08lX\n"
    "lidar_patch=0x%04X\n"
    "lidar_bus=%s\n"
    "lidar_bus_hz=%lu\n"
    "lidar_zones=%ux%u\n"
    "lidar_raw_size=%u\n"
    "lidar_calib_size=%u\n"
    "lidar_last_error=%ld (%s)\n",
    PROTO_VERSION, usb_serial_number(),
    imu_name(), imu_whoami(),
    lidar_state_name(g_lidar.state), (unsigned long)g_lidar.device_id, g_lidar.patch_revision,
    bus_code() == BUS_I3C ? "i3c" : bus_code() == BUS_I2C_SOFT ? "i2c-soft" : "none",
    (unsigned long)g_lidar_bus.bus_hz,
    LIDAR_WIDTH, LIDAR_HEIGHT, LIDAR_RAW_SIZE, LIDAR_CALIB_SIZE,
    (long)g_lidar.last_error, g_lidar.last_error_where ? g_lidar.last_error_where : "none");
  if (n > 0)
  {
    (void)proto_tx_send(PKT_INFO, buf, (uint32_t)((n < (int)sizeof(buf)) ? n : (int)sizeof(buf) - 1), time_us());
  }
}

static void send_status(void)
{
  proto_status_t s = {
    .imu_variant = (uint8_t)imu_variant(),
    .imu_whoami = imu_whoami(),
    .imu_streaming = imu_streaming,
    .lidar_state = g_lidar.state,
    .lidar_bus = bus_code(),
    .led_mode = led_mode,
    .lidar_bus_hz = g_lidar_bus.bus_hz,
    .lidar_frames = g_lidar.frames,
    .lidar_dropped = g_lidar.dropped,
    .lidar_errors = g_lidar.errors,
    .lidar_last_error = g_lidar.last_error,
    .imu_samples = imu_sample,
    .tx_dropped = proto_tx_dropped(),
  };
  (void)proto_tx_send(PKT_STATUS, &s, sizeof(s), time_us());
}

static void send_calibration(void)
{
  const uint8_t *cal = lidar_calibration();
  if (!cal)
  {
    app_log("No LiDAR calibration available (LiDAR state: %s)", lidar_state_name(g_lidar.state));
    return;
  }
  if (!proto_tx_send_large(PKT_LIDAR_CALIB, NULL, 0U, cal, LIDAR_CALIB_SIZE, time_us()))
  {
    app_log("Calibration not sent: transmit queue busy, retry");
  }
}

static void handle_command(uint8_t c)
{
  switch (c)
  {
    case CMD_INFO:         send_info(); break;
    case CMD_CALIB:        send_calibration(); break;
    case CMD_IMU_ON:
      if (imu_variant() == IMU_NONE)
      {
        app_log("IMU not detected (WHO_AM_I 0x%02X)", imu_whoami());
        break;
      }
      imu_streaming = true;
      imu_sample = 0U;
      break;
    case CMD_IMU_OFF:      imu_streaming = false; break;
    case CMD_LIDAR_ON:     lidar_req = LIDAR_REQ_ON; break;
    case CMD_LIDAR_OFF:    lidar_req = LIDAR_REQ_OFF; break;
    case CMD_ALL_OFF:      imu_streaming = false; lidar_req = LIDAR_REQ_OFF; break;
    case CMD_LED_TOGGLE:   led_mode = led_on ? LED_MANUAL_OFF : LED_MANUAL_ON; break;
    case CMD_LED_AUTO:     led_mode = LED_HEARTBEAT; break;
    case CMD_IMU_REINIT:   req_imu_reinit = true; break;
    case CMD_LIDAR_REINIT: lidar_req = LIDAR_REQ_REINIT; break;
    case '\r': case '\n':  break;
    default:               app_log("Unknown command 0x%02X", c); break;
  }
}

static void service_led(void)
{
  if (led_mode != LED_HEARTBEAT)
  {
    led_set(led_mode == LED_MANUAL_ON);
    return;
  }
  uint32_t half_period = g_lidar.state == LIDAR_STATE_ERROR ? 50U
                       : g_lidar.state == LIDAR_STATE_STREAMING ? 125U : 500U;
  if (HAL_GetTick() - last_blink_ms >= half_period)
  {
    last_blink_ms = HAL_GetTick();
    led_set(!led_on);
  }
}

static void service_imu(uint64_t now)
{
  if (!imu_streaming || now - last_imu_poll_us < IMU_POLL_US)
  {
    return;
  }
  last_imu_poll_us = now;

  imu_sample_t s;
  if (imu_data_ready() == 1 && imu_read(&s) == 0)
  {
    proto_imu_t p = {.sample = imu_sample++, .temp_c = s.temp_c};
    memcpy(p.accel_mg, s.accel_mg, sizeof(p.accel_mg));
    memcpy(p.gyro_mdps, s.gyro_mdps, sizeof(p.gyro_mdps));
    (void)proto_tx_send(PKT_IMU, &p, sizeof(p), now);
  }
}

/* ------------------------------------------------------------------ public */

void app_background(void)
{
  static bool busy;
  if (busy)
  {
    return;   /* never nest (e.g. a log call from inside the background work) */
  }
  busy = true;

  tud_task();

  bool now_connected = tud_cdc_connected();
  if (now_connected && !connected)
  {
    proto_tx_reset();
    send_info();
    last_status_us = 0U;
  }
  else if (!now_connected && connected)
  {
    /* Host gone: stop streaming so the next session starts clean. */
    imu_streaming = false;
    lidar_req = LIDAR_REQ_OFF;
    proto_tx_reset();
  }
  connected = now_connected;

  if (connected)
  {
    while (tud_cdc_available())
    {
      handle_command((uint8_t)tud_cdc_read_char());
    }
    uint64_t now = time_us();
    service_imu(now);
    if (now - last_status_us >= STATUS_PERIOD_US)
    {
      last_status_us = now;
      send_status();
    }
  }

  service_led();
  proto_tx_pump();
  busy = false;
}

void app_init(void)
{
  timebase_init();

  if (usb_app_init() != 0)
  {
    /* USB failed to start: blink fast forever as a visible error. */
    for (;;)
    {
      HAL_GPIO_TogglePin(LED_ONN_PORT, LED_ONN_PIN);
      HAL_Delay(100U);
    }
  }

  (void)imu_init();
  (void)lidar_init();   /* takes ~0.5 s; USB keeps running through app_background() */
}

void app_loop(void)
{
  app_background();

  if (req_imu_reinit)
  {
    req_imu_reinit = false;
    bool was = imu_streaming;
    imu_streaming = false;
    (void)imu_init();
    imu_streaming = was && imu_variant() != IMU_NONE;
    app_log("IMU: %s (WHO_AM_I 0x%02X)", imu_name(), imu_whoami());
    send_info();
  }
  uint8_t req = lidar_req;
  lidar_req = LIDAR_REQ_NONE;
  switch (req)
  {
    case LIDAR_REQ_REINIT:
      lidar_stop();
      app_log("LiDAR: re-initializing...");
      app_log("LiDAR: %s", lidar_init() == 0 ? "ready" : "failed");
      send_info();
      break;
    case LIDAR_REQ_OFF:
      lidar_stop();
      break;
    case LIDAR_REQ_ON:
      if (g_lidar.state == LIDAR_STATE_READY && lidar_start() == 0)
      {
        app_log("LiDAR: streaming");
      }
      else if (g_lidar.state != LIDAR_STATE_STREAMING)
      {
        app_log("LiDAR not ready (state: %s); send 'R' to re-initialize", lidar_state_name(g_lidar.state));
      }
      break;
    default:
      break;
  }

  lidar_task();
}
