/**
  ******************************************************************************
  * @file           : mx_def.h
  * @brief          : Exporting definition
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
#ifndef MX_DEF_H
#define MX_DEF_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include <stddef.h>

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  SYSTEM_OK                        = 0xEAEAEAEAU,        /* System initialization successfully       */
  SYSTEM_PRESYSTEM_ERROR           = 0xF5F5F5F5U,        /* Error during System pre-initialization   */
  SYSTEM_STARTUP_ERROR             = 0x96969696U,        /* Error during startup initialization      */
  SYSTEM_INTERRUPTS_ERROR          = 0x5A5A5A5AU,        /* Error during interrupts initialization   */
  SYSTEM_CLOCK_ERROR               = 0xA5A5A5A5U,        /* Error during clock initialization        */
  SYSTEM_RESOURCES_ISOLATION_ERROR = 0x3C3C3C3CU,        /* Error during Cortex MPU initialization   */
  SYSTEM_POWER_ERROR               = 0xC3C3C3C3U,        /* Error during power initialization        */
  SYSTEM_PERIPHERAL_ERROR          = 0x6D6D6D6DU,        /* Error during peripherals initialization  */
  SYSTEM_POSTSYSTEM_ERROR          = 0xB2B2B2B2U         /* Error during System post-initialization  */
} system_status_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_DEF_H */
