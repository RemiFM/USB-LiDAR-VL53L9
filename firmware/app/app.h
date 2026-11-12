/**
  * Application: USB protocol (protocol.h), IMU and LiDAR streaming, status LED.
  *
  * Main loop:            app_loop() -> app_background() + LiDAR state machine
  * During long LiDAR operations (frame reads, sensor boot), the VL53L9 platform
  * layer calls app_background() between bus transfers, so USB, commands, IMU
  * sampling and the LED keep running. app_background() never touches the LiDAR.
  */
#ifndef APP_H
#define APP_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void app_init(void);        /* after mx_system_init(); never returns on USB failure */
void app_loop(void);        /* call forever */
void app_background(void);  /* USB, commands, IMU, status, LED; re-entrancy safe */
void app_wait_ms(uint32_t ms);                 /* delay that keeps app_background() running */
void app_log(const char *fmt, ...) __attribute__((format(printf, 1, 2)));  /* PKT_LOG */

#ifdef __cplusplus
}
#endif

#endif /* APP_H */
