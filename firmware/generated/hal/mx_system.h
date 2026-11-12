/**
  ******************************************************************************
  * @file           : mx_system.h
  * @brief          : Exporting peripherals initialization
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
#ifndef MX_SYSTEM_H
#define MX_SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "mx_hal_def.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/**
  * @brief  System initialization
  * @retval Status
  */
system_status_t mx_system_init(void);

void SysTick_Handler(void);

system_status_t pre_system_init_hook(void);

system_status_t post_system_init_hook(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_SYSTEM_H */
