
/**
  ******************************************************************************
  * @file           : mx_icache.c
  * @brief          : ICACHE Peripheral initialization
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
#include "mx_icache.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/
/* Exported variables by reference--------------------------------------------*/
static hal_icache_handle_t hICACHE;

/******************************************************************************/
/* Exported functions for ICACHE in HAL layer */
/******************************************************************************/

hal_icache_handle_t *mx_icache_init(void)
{
  if (HAL_ICACHE_Init(&hICACHE, HAL_ICACHE) != HAL_OK)
  {
    return NULL;
  }

  /* Associativity mode set to default value 2-ways */

  return &hICACHE;
}

void mx_icache_deinit(void)
{
  (void)HAL_ICACHE_DeInit(&hICACHE);
}

hal_icache_handle_t *mx_icache_gethandle(void)
{
  return &hICACHE;
}
