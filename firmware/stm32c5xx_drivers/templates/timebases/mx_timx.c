/**
  ******************************************************************************
  * @file           : mx_timx.c
  * @brief          : Peripheral initialization
  *                   File per peripheral instance that handles peripheral
  *                   initialization and IRQ handlers. Init parameters are provided
  *                   as a set of defines, configurable/generated for a given target
  *                   through hal_tim_settings.json and the config tool.
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

/**
  * @brief Template for STM32 timer peripheral initialization and IRQ handling.
  *
  * How to use this template:
  *
  * [1] Name replacement:
  *   - Replace all occurrences of "timx" with the timer instance (e.g., tim6).
  *   - Replace all occurrences of "TIMx" with the timer instance (e.g., TIM6).
  *
  * [2] Recommendation:
  *   - Prefer basic timers as timebase sources.
  *
  * [3] IRQ handler adaptation:
  *   - For non-advanced timers, use TIMx_IRQHandler.
  *   - For advanced timers (e.g., TIM1, TIM8), see section [4].
  *
  * [4] Changes required for advanced timers:
  *   - In this file and mx_timx.h: use TIMx_UPD_IRQHandler instead of TIMx_IRQHandler.
  *   - In this file: use TIMx_UPD_IRQn instead of TIMx_IRQn.
  *
  * Example:
  *   To use TIM6 as the timebase:
  *     - Replace "timx" with "tim6"
  *     - Replace "TIMx" with "TIM6"
  *     - Ensure the IRQ handler is named TIM6_IRQHandler
  */

/* Includes ------------------------------------------------------------------*/
#include "mx_timx.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/
/* Exported variables by reference--------------------------------------------*/
static hal_tim_handle_t hTIMx;

/* Exported function definition ----------------------------------------------*/

/******************************************************************************/
/* Exported functions for TIMx in HAL layer */
/******************************************************************************/
hal_tim_handle_t *mx_timx_init(void)
{
  if (HAL_TIM_Init(&hTIMx, HAL_TIMx) != HAL_OK)
  {
    return NULL;
  }

  HAL_RCC_TIMx_EnableClock();

  /* Enable the Timer interrupt */
  HAL_CORTEX_NVIC_SetPriority(TIMx_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(TIMx_IRQn);

  return &hTIMx;
}

void mx_timx_deinit(void)
{
  (void)HAL_TIM_DeInit(&hTIMx);

  HAL_RCC_TIMx_DisableClock();

  HAL_RCC_TIMx_Reset();

  /* Disable Timer interrupt */
  HAL_CORTEX_NVIC_DisableIRQ(TIMx_IRQn);
}

hal_tim_handle_t *mx_timx_gethandle(void)
{
  return &hTIMx;
}

/******************************************************************************/
/* TIMx interrupt */
/******************************************************************************/
void TIMx_IRQHandler(void)
{
  HAL_TIM_UPD_IRQHandler(&hTIMx);
}
