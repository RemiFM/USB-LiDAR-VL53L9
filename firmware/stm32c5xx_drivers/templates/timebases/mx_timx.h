/**
  ******************************************************************************
  * @file           : mx_timx.h
  * @brief          : Header for mx_timx.c.
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
#ifndef STM32_TIMx_H
#define STM32_TIMx_H

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
/* Exported functions for TIM in HAL layer */
/******************************************************************************/
/**
  * @brief  mx_timx initialization function.
  *         This function configures the hardware resources used in this example.
  * @retval Pointer to the handle.
  * @retval NULL on failure.
  */
hal_tim_handle_t *mx_timx_init(void);

/**
  * @brief  Deinitialize the mx_timx instance.
  */
void mx_timx_deinit(void);

/**
  * @brief  Get the mx_timx handle.
  * @return Pointer to the mx_timx handle.
  */
hal_tim_handle_t *mx_timx_gethandle(void);

/******************************************************************************/
/*                               TIMx interrupt                               */
/******************************************************************************/
void TIMx_IRQHandler(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32_TIMx_H */
