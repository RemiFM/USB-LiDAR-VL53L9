/**
  * Microsecond timebase for packet timestamps, from the Cortex-M33 cycle counter
  * (DWT CYCCNT at SYSCLK = 144 MHz), extended to 64 bits so it never wraps.
  */
#ifndef TIMEBASE_H
#define TIMEBASE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Enables the cycle counter. Call once after the clocks are configured. */
void timebase_init(void);

/* Microseconds since timebase_init(). Main context only (not from interrupts);
   must be called at least every ~29 s (CYCCNT wraps at 2^32 cycles). */
uint64_t time_us(void);

#ifdef __cplusplus
}
#endif

#endif /* TIMEBASE_H */
