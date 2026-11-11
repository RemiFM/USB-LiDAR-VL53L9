/**
  ******************************************************************************
  * @file           : mx_system.c
  * @brief          : STM32 system program body
  *                   Applicative target system level initialization
  *                   (system clock, cache, TZ...) and system level peripherals
  *                   initialization. mx_system_init() service is called by the main
  *                   before jumping the example entry point.
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
#include "mx_system.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

system_status_t mx_system_init(void)
{
  if (pre_system_init_hook() != SYSTEM_OK)
  {
    return SYSTEM_PRESYSTEM_ERROR;
  }

  /*
    CORTEX MPU initialization in case of isolation is not activated
  */
  if (mx_cortex_mpu_init() != SYSTEM_OK)
  {
    return SYSTEM_RESOURCES_ISOLATION_ERROR;
  }

  /*
    startup system section
  */
  if (HAL_Init() != HAL_OK)
  {
    return SYSTEM_STARTUP_ERROR;
  }

  /*
    Interruptions section
  */
  if (mx_cortex_nvic_init() != SYSTEM_OK)
  {
    return SYSTEM_INTERRUPTS_ERROR;
  }

  /*
    ICACHE section
  */
  if (mx_icache_init() == NULL)
  {
    return SYSTEM_STARTUP_ERROR;
  }

  /* ICACHE automatically started at startup */
  if (HAL_ICACHE_Start(mx_icache_gethandle(), HAL_ICACHE_IT_NONE) != HAL_OK)
  {
    return SYSTEM_STARTUP_ERROR;
  }

  /*
    Clock system section
  */

  /* Initialize RCC peripheral */
  if (mx_rcc_init() != SYSTEM_OK)
  {
    return SYSTEM_CLOCK_ERROR;
  }

  /* peripherals clock configuration and activation
    is centralized: no clock activation/deactivation in pppi_init */

  if (mx_rcc_peripherals_clock_config() != SYSTEM_OK)
  {
    return SYSTEM_CLOCK_ERROR;
  }

  /*
    Peripheral init section
  */

  /** Cortex_DEBUG */
  if (mx_cortex_debug_init() != SYSTEM_OK)
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }

  /** Cortex_Systick: _init() has not been generated */

  /** I3C1 */
  if (mx_i3c1_init() == NULL)
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }

  /** SPI1 */
  if (mx_spi1_init() == NULL)
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }

  /** gpio_default */
  if (mx_gpio_default_init() != SYSTEM_OK)
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }

  /** USB_DRD_FS_DEVICE: mx_usb_drd_fs_device_init() has not been generated */

  if (post_system_init_hook() != SYSTEM_OK)
  {
    return SYSTEM_POSTSYSTEM_ERROR;
  }

  return SYSTEM_OK;
}

/******************************************************************************/
/*                            Systick Handler                                 */
/******************************************************************************/
/**
  * @brief   This function handles SysTick Handler
  * @warning Systick_Handler is generated as NVIC peripheral has not been activated
  *          By default it is generated in HAL.
  *          It must be located into mx_cortex_nvic.c file
  */
void SysTick_Handler(void)
{
  HAL_IncTick();
  HAL_CORTEX_SYSTICK_IRQHandler();
}

/**
  * @brief  User hook function called before the HAL_Init() function
  * @retval system_status_t System status
  */
__WEAK system_status_t pre_system_init_hook(void)
{
  /* NOTE : This function must not be modified. When the callback is needed,
            the pre_system_init_hook can be implemented in the user file
   */
  return SYSTEM_OK;
}

/**
  * @brief  User hook function called after the HAL_Init() and Peripheral init functions
  * @retval system_status_t System status
  */
__WEAK system_status_t post_system_init_hook(void)
{
  /* NOTE : This function must not be modified. When the callback is needed,
            the post_system_init_hook can be implemented in the user file
   */
  return SYSTEM_OK;
}
