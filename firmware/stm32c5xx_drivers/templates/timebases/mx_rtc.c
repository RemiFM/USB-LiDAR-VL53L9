/**
  ******************************************************************************
  * @file           : mx_rtc.c
  * @brief          : RTC Peripheral initialization
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
/* Includes ------------------------------------------------------------------*/
#include "mx_rtc.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototypes-----------------------------------------------*/
/* Exported variables by reference--------------------------------------------*/

/******************************************************************************/
/* Exported functions for RTC timebase in HAL layer                           */
/******************************************************************************/
void mx_rtc_init(void)
{
  /* Enable RTC Clock */
  HAL_RCC_RTCAPB_EnableClock();
  HAL_RCC_RTC_EnableKernelClock();

  /* Enable the interrupt for RTC */
  HAL_CORTEX_NVIC_SetPriority(RTC_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(RTC_IRQn);
}

void mx_rtc_deinit(void)
{
  /* Disable RTC kernel clock */
  HAL_RCC_RTC_DisableKernelClock();
  HAL_RCC_RTCAPB_DisableClock();

  /* Disable the interrupt for RTC */
  HAL_CORTEX_NVIC_DisableIRQ(RTC_IRQn);
}

/******************************************************************************/
/**                     RTC global non-secure interrupts                     **/
/******************************************************************************/
void RTC_IRQHandler(void)
{
  HAL_RTC_IRQHandler();
}
