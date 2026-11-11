/**
  ******************************************************************************
  * @file    stm32_hal_timebase.h
  * @brief   STM32 HAL time base template file.
  *          This file is a template file to be used when customizing the HAL time base
  *          to use a TIMER or the RTC as a HAL time base.
  *          It is designed to include the required file, the mx_timx.h or mx_rtc.h.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32_HAL_TIMEBASE_H
#define STM32_HAL_TIMEBASE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
/* When using a TIMER as a time base:
  Update this line to include the header file of the corresponding TIMx,
  for example mx_tim6.h.

  Remove this line when using the RTC as a time base. */
#include "mx_timx.h"

/* Keep it when using RTC ALARM or WAKEUP as a HAL time base.
  Remove it when using a TIMER as a HAL time base. */
#include "mx_rtc.h"

/******************************************************************************/
/*   TIMEBASE ALIASES   (private aliases)                                     */
/******************************************************************************/
/*
When using a TIMER as a time base: these aliases must be updated to point to the corresponding timx,
for example #define timebase_gethandle   mx_tim6_gethandle

Otherwise, remove it.
*/

#define timebase_gethandle   mx_timx_gethandle

#define timebase_init        mx_timx_init
#define timebase_deinit      mx_timx_deinit

/* For advanced timers, use TIMx_UPD_IRQn. */
#define TIMEBASE_IRQ         TIMx_IRQn

/*
When using RTC (Alarm or Wakeup) as a time base, keep these aliases.
Otherwise, remove them.
*/

#define timebase_init        mx_rtc_init
#define timebase_deinit      mx_rtc_deinit

#define TIMEBASE_IRQ         RTC_IRQn

/* Exported functions ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32_HAL_TIMEBASE_H */
