/**
  ******************************************************************************
  * @file           : mx_rcc.h
  * @brief          : Exporting functions for mx_rcc.c
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the mx_stm32c5xx_hal_drivers_license.md file
  * in the same directory as the generated code.
  * If no mx_stm32c5xx_hal_drivers_license.md file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MX_RCC_H
#define MX_RCC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"
#include "mx_def.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/******************************************************************************/
/* Exported functions for RCC in HAL layer */
/******************************************************************************/
system_status_t mx_rcc_init(void);
void mx_rcc_deinit(void);

system_status_t mx_rcc_peripherals_clock_config(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_RCC_H */
