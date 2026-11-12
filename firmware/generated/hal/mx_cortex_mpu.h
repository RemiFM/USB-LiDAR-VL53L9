/**
  ******************************************************************************
  * @file           : mx_cortex_mpu.h
  * @brief          : Header for mx_cortex_mpu.c file.
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
#ifndef MX_CORTEX_MPU_H
#define MX_CORTEX_MPU_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/

#include "stm32_hal.h"
#include "mx_def.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/******************************************************************************/
/* Exported functions for CORTEX_MPU in HAL layer */
/******************************************************************************/
/**
  * @brief mx_cortex_mpu init function
  * This function configures the hardware resources used in this example
  * @retval pointer to handle or NULL in case of failure
  */
system_status_t mx_cortex_mpu_init(void);

/**
  * @brief  De-initialize cortex_mpu instance and return it.
  */
void mx_cortex_mpu_deinit(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_CORTEX_MPU_H */
