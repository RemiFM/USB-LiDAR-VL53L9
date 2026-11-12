/**
  ******************************************************************************
  * @file           : mx_cortex_nvic.c
  * @brief          : CORTEX_NVIC Peripheral initialization
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

/* Includes ------------------------------------------------------------------*/
#include "mx_cortex_nvic.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/
/* Exported variables by reference--------------------------------------------*/

/******************************************************************************/
/* Exported functions for CORTEX_NVIC in HAL layer */
/******************************************************************************/
system_status_t mx_cortex_nvic_init(void)
{
  /* Configure the Priority grouping */
  HAL_CORTEX_NVIC_SetPriorityGrouping(HAL_CORTEX_NVIC_PRIORITY_GROUP_4);

  return SYSTEM_OK;
}
