/**
  ******************************************************************************
  * @file           : mx_gpio_default.c
  * @brief          : gpio_default Peripheral initialization
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
#include "mx_gpio_default.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported variables by reference -------------------------------------------*/

/******************************************************************************/
/* Exported functions for GPIO in HAL layer                                   */
/******************************************************************************/
system_status_t mx_gpio_default_init(void)
{
  hal_gpio_config_t  gpio_config;

  HAL_RCC_GPIOA_EnableClock();

  HAL_RCC_GPIOB_EnableClock();

  /*
    GPIO pin labels :
    PA2   ---------> GPIO_OUT
    */
  /* Configure PA2 GPIO pin in output mode */
  gpio_config.mode            = HAL_GPIO_MODE_OUTPUT;
  gpio_config.speed           = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.pull            = HAL_GPIO_PULL_NO;
  gpio_config.output_type     = HAL_GPIO_OUTPUT_OPENDRAIN;
  gpio_config.init_state      = GPIO_OUT_INIT_STATE;
  if (HAL_GPIO_Init(GPIO_OUT_PORT, GPIO_OUT_PIN, &gpio_config) != HAL_OK)
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }

  /*
    GPIO pin labels :
    PA3   ---------> LIDAR_INTR
    */
  /* Configure PA3 GPIO pin in output mode */
  gpio_config.mode            = HAL_GPIO_MODE_OUTPUT;
  gpio_config.speed           = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.pull            = HAL_GPIO_PULL_NO;
  gpio_config.output_type     = HAL_GPIO_OUTPUT_OPENDRAIN;
  gpio_config.init_state      = LIDAR_INTR_INIT_STATE;
  if (HAL_GPIO_Init(LIDAR_INTR_PORT, LIDAR_INTR_PIN, &gpio_config) != HAL_OK)
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }

  /*
    GPIO pin labels :
    PA4   ---------> SPI_CSN
    */
  /* Configure PA4 GPIO pin in output mode */
  gpio_config.mode            = HAL_GPIO_MODE_OUTPUT;
  gpio_config.speed           = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.pull            = HAL_GPIO_PULL_NO;
  gpio_config.output_type     = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.init_state      = SPI_CSN_INIT_STATE;
  if (HAL_GPIO_Init(SPI_CSN_PORT, SPI_CSN_PIN, &gpio_config) != HAL_OK)
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }

  /*
    GPIO pin labels :
    PB0   ---------> IMU_INT1
    PB1   ---------> IMU_INT2
    */
  /* Configure PB0, PB1 GPIO pins in input mode */
  gpio_config.mode            = HAL_GPIO_MODE_INPUT;
  gpio_config.pull            = HAL_GPIO_PULL_NO;
  if (HAL_GPIO_Init(HAL_GPIOB, IMU_INT1_PIN | IMU_INT2_PIN, &gpio_config) != HAL_OK)
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }

  /*
    GPIO pin labels :
    PB7   ---------> LIDAR_SHDN
    PB8   ---------> LED_ONN
    */
  /* Configure PB7, PB8 GPIO pins in output mode */
  gpio_config.mode            = HAL_GPIO_MODE_OUTPUT;
  gpio_config.speed           = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.pull            = HAL_GPIO_PULL_NO;
  gpio_config.output_type     = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.init_state      = HAL_GPIO_PIN_RESET;
  if (HAL_GPIO_Init(HAL_GPIOB, LIDAR_SHDN_PIN | LED_ONN_PIN, &gpio_config) != HAL_OK)
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }

  return SYSTEM_OK;
}

system_status_t mx_gpio_default_deinit(void)
{
  /* De-initialize pins of GPIOA port */
  HAL_GPIO_DeInit(HAL_GPIOA, GPIO_OUT_PIN | LIDAR_INTR_PIN | SPI_CSN_PIN);

  /* De-initialize pins of GPIOB port */
  HAL_GPIO_DeInit(HAL_GPIOB, IMU_INT1_PIN | IMU_INT2_PIN | LIDAR_SHDN_PIN | LED_ONN_PIN);

  return SYSTEM_OK;
}
