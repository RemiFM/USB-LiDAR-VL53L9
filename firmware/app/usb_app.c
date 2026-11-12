/**
  * USB application layer.
  *
  * CubeMX2 is configured with USB_DRD_FS (Device) but "initialization code not
  * generated", so this file owns the peripheral: kernel clock, interrupt handler
  * and NVIC priority. TinyUSB enables the IRQ itself in tusb_init().
  */
#include "usb_app.h"
#include "stm32_hal.h"
#include "tusb.h"

/* TinyUSB uses this for timeouts when no RTOS is present. */
uint32_t tusb_time_millis_api(void)
{
  return HAL_GetTick();
}

/* Overrides the weak default in the startup file. */
void USB_DRD_FS_IRQHandler(void)
{
  tud_int_handler(0);
}

int usb_app_init(void)
{
  /* 48 MHz USB kernel clock: PSI (144 MHz from the 16 MHz HSE crystal) / 3.
     Crystal-accurate, so no CRS trimming is needed. */
  if (HAL_RCC_PSIDIV3_Enable() != HAL_OK)
  {
    return -1;
  }
  if (HAL_RCC_CK48_SetKernelClkSource(HAL_RCC_CK48_CLK_SRC_PSIDIV3) != HAL_OK)
  {
    return -1;
  }
  HAL_RCC_USB_EnableClock();
  HAL_RCC_USB_Reset();

  /* Same priority as the previous firmware; SysTick runs at 15 (lowest). */
  NVIC_SetPriority(USB_DRD_FS_IRQn, 2);

  const tusb_rhport_init_t config = { .role = TUSB_ROLE_DEVICE, .speed = TUSB_SPEED_FULL };
  return tusb_init(0, &config) ? 0 : -1;
}

void usb_app_task(void)
{
  tud_task();
}
