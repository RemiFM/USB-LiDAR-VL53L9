#include "timebase.h"
#include "stm32_hal.h"

static uint32_t last_cycles;
static uint64_t total_cycles;
static uint32_t cycles_per_us;

void timebase_init(void)
{
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  DWT->CYCCNT = 0U;
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
  cycles_per_us = HAL_RCC_GetSYSCLKFreq() / 1000000U;
  last_cycles = 0U;
  total_cycles = 0U;
}

uint64_t time_us(void)
{
  uint32_t now = DWT->CYCCNT;
  total_cycles += (uint32_t)(now - last_cycles);   /* wrap-safe */
  last_cycles = now;
  return total_cycles / cycles_per_us;
}
