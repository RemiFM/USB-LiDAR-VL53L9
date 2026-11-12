/**
  ******************************************************************************
  * @file           : mx_gpio_default.h
  * @brief          : Header for mx_gpio_default.c file.
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
#ifndef MX_GPIO_DEFAULT_H
#define MX_GPIO_DEFAULT_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"
#include "mx_def.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/******************************************************************************/
/* Exported defines for gpio_default in HAL layer                             */
/******************************************************************************/

/* Primary aliases for GPIO PA2 pin */
#define GPIO_OUT_PORT                                   HAL_GPIOA
#define GPIO_OUT_PIN                                    HAL_GPIO_PIN_2
#define GPIO_OUT_INIT_STATE                             HAL_GPIO_PIN_RESET
#define GPIO_OUT_ACTIVE_STATE                           HAL_GPIO_PIN_SET
#define GPIO_OUT_INACTIVE_STATE                         HAL_GPIO_PIN_RESET

/* Primary aliases for GPIO PA3 pin */
#define LIDAR_INTR_PORT                                 HAL_GPIOA
#define LIDAR_INTR_PIN                                  HAL_GPIO_PIN_3
#define LIDAR_INTR_INIT_STATE                           HAL_GPIO_PIN_SET
#define LIDAR_INTR_ACTIVE_STATE                         HAL_GPIO_PIN_SET
#define LIDAR_INTR_INACTIVE_STATE                       HAL_GPIO_PIN_RESET

/* Primary aliases for GPIO PA4 pin */
#define SPI_CSN_PORT                                    HAL_GPIOA
#define SPI_CSN_PIN                                     HAL_GPIO_PIN_4
#define SPI_CSN_INIT_STATE                              HAL_GPIO_PIN_SET
#define SPI_CSN_ACTIVE_STATE                            HAL_GPIO_PIN_SET
#define SPI_CSN_INACTIVE_STATE                          HAL_GPIO_PIN_RESET

/* Primary aliases for GPIO PB0 pin */
#define IMU_INT1_PORT                                   HAL_GPIOB
#define IMU_INT1_PIN                                    HAL_GPIO_PIN_0

/* Primary aliases for GPIO PB1 pin */
#define IMU_INT2_PORT                                   HAL_GPIOB
#define IMU_INT2_PIN                                    HAL_GPIO_PIN_1

/* Primary aliases for GPIO PB7 pin */
#define LIDAR_SHDN_PORT                                 HAL_GPIOB
#define LIDAR_SHDN_PIN                                  HAL_GPIO_PIN_7
#define LIDAR_SHDN_INIT_STATE                           HAL_GPIO_PIN_RESET
#define LIDAR_SHDN_ACTIVE_STATE                         HAL_GPIO_PIN_SET
#define LIDAR_SHDN_INACTIVE_STATE                       HAL_GPIO_PIN_RESET

/* Primary aliases for GPIO PB8 pin */
#define LED_ONN_PORT                                    HAL_GPIOB
#define LED_ONN_PIN                                     HAL_GPIO_PIN_8
#define LED_ONN_INIT_STATE                              HAL_GPIO_PIN_RESET
#define LED_ONN_ACTIVE_STATE                            HAL_GPIO_PIN_SET
#define LED_ONN_INACTIVE_STATE                          HAL_GPIO_PIN_RESET

/* Exported macros -----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/******************************************************************************/
/* Exported functions for gpio_default in HAL layer                           */
/******************************************************************************/
/**
  * @brief mx_gpio_default init function
  * This function configures the hardware resources used in this example
  * @retval 0  GPIO group correctly initialized
  * @retval -1 Issue detected during GPIO group initialization
  */
system_status_t mx_gpio_default_init(void);

/**
  * @brief  De-initialize gpio_default instance.
  */
system_status_t mx_gpio_default_deinit(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_GPIO_DEFAULT_H */
