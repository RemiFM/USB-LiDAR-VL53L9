/**
  ******************************************************************************
  * @file           : mx_rtc.h
  * @brief          : Header for the mx_rtc.c file.
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
#ifndef MX_RTC_H
#define MX_RTC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/******************************************************************************/
/* Exported functions for RTC in HAL layer */
/******************************************************************************/
/**
  * @brief Initialize the mx_rtc instance.
  * Configure the hardware resources used in this example.
  * @retval Pointer to handle or NULL in case of failure.
  */
void mx_rtc_init(void);

/**
  * @brief  Deinitialize the mx_rtc instance.
  */
void mx_rtc_deinit(void);

/******************************************************************************/
/**                     RTC global non-secure interrupts                     **/
/******************************************************************************/
void RTC_IRQHandler(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_RTC_H */
