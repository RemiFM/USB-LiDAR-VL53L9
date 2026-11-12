/**
  ******************************************************************************
  * @file           : mx_cortex_mpu.c
  * @brief          : CORTEX_MPU Peripheral initialization
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
#include "mx_cortex_mpu.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/
/* Exported variables by reference--------------------------------------------*/
/******************************************************************************/
/* Exported functions for CORTEX_MPU in HAL layer */
/******************************************************************************/

system_status_t mx_cortex_mpu_init(void)
{
  /* Disables the MPU */
  HAL_CORTEX_MPU_Disable();

  /*
     Initializes and configures the MPU attributes
  */
  HAL_CORTEX_MPU_SetCacheMemAttr(HAL_CORTEX_MPU_MEM_ATTR_0, HAL_CORTEX_MPU_NORMAL_MEM_NCACHEABLE);

  /*
     Initializes and configures the MPU Region
  */
  hal_cortex_mpu_region_config_t p_region_config = {0};

  p_region_config.base_addr = 0x8FFE000;
  p_region_config.limit_addr = 0x8FFFFFF;
  p_region_config.access_attr = HAL_CORTEX_MPU_REGION_ALL_RO;
  p_region_config.exec_attr = HAL_CORTEX_MPU_EXECUTION_ATTR_DISABLE;
  p_region_config.attr_idx = HAL_CORTEX_MPU_MEM_ATTR_0;
  HAL_CORTEX_MPU_SetConfigRegion(HAL_CORTEX_MPU_REGION_0, &p_region_config);

  HAL_CORTEX_MPU_EnableRegion(HAL_CORTEX_MPU_REGION_0);

  /* Enables the MPU */
  HAL_CORTEX_MPU_Enable(HAL_CORTEX_MPU_HARDFAULT_NMI_DISABLE, HAL_CORTEX_MPU_ACCESS_FAULT_ONLY_PRIV);

  return SYSTEM_OK;
}

void mx_cortex_mpu_deinit(void)
{
  /* Disables the MPU and MPU regions*/
  HAL_CORTEX_MPU_Disable();

  HAL_CORTEX_MPU_DisableRegion(HAL_CORTEX_MPU_REGION_0);
  HAL_CORTEX_MPU_DisableRegion(HAL_CORTEX_MPU_REGION_1);
  HAL_CORTEX_MPU_DisableRegion(HAL_CORTEX_MPU_REGION_2);
  HAL_CORTEX_MPU_DisableRegion(HAL_CORTEX_MPU_REGION_3);
  HAL_CORTEX_MPU_DisableRegion(HAL_CORTEX_MPU_REGION_4);
  HAL_CORTEX_MPU_DisableRegion(HAL_CORTEX_MPU_REGION_5);
  HAL_CORTEX_MPU_DisableRegion(HAL_CORTEX_MPU_REGION_6);
  HAL_CORTEX_MPU_DisableRegion(HAL_CORTEX_MPU_REGION_7);
  /*
     Deinitializes and configures the MPU attributes to default
  */
  HAL_CORTEX_MPU_SetDeviceMemAttr(HAL_CORTEX_MPU_MEM_ATTR_0, HAL_CORTEX_MPU_DEVICE_MEM_NGNRNE);
  HAL_CORTEX_MPU_SetDeviceMemAttr(HAL_CORTEX_MPU_MEM_ATTR_1, HAL_CORTEX_MPU_DEVICE_MEM_NGNRNE);
  HAL_CORTEX_MPU_SetDeviceMemAttr(HAL_CORTEX_MPU_MEM_ATTR_2, HAL_CORTEX_MPU_DEVICE_MEM_NGNRNE);
  HAL_CORTEX_MPU_SetDeviceMemAttr(HAL_CORTEX_MPU_MEM_ATTR_3, HAL_CORTEX_MPU_DEVICE_MEM_NGNRNE);
  HAL_CORTEX_MPU_SetDeviceMemAttr(HAL_CORTEX_MPU_MEM_ATTR_4, HAL_CORTEX_MPU_DEVICE_MEM_NGNRNE);
  HAL_CORTEX_MPU_SetDeviceMemAttr(HAL_CORTEX_MPU_MEM_ATTR_5, HAL_CORTEX_MPU_DEVICE_MEM_NGNRNE);
  HAL_CORTEX_MPU_SetDeviceMemAttr(HAL_CORTEX_MPU_MEM_ATTR_6, HAL_CORTEX_MPU_DEVICE_MEM_NGNRNE);
  HAL_CORTEX_MPU_SetDeviceMemAttr(HAL_CORTEX_MPU_MEM_ATTR_7, HAL_CORTEX_MPU_DEVICE_MEM_NGNRNE);

  /*
     Deinitializes and configures the MPU Region to default
  */
  hal_cortex_mpu_region_config_t p_region_config = {0};

  p_region_config.base_addr = 0x00000000;
  p_region_config.limit_addr = 0x00000000;
  p_region_config.access_attr = HAL_CORTEX_MPU_REGION_ONLY_PRIV_RW;
  p_region_config.exec_attr = HAL_CORTEX_MPU_EXECUTION_ATTR_ENABLE;
  p_region_config.attr_idx = HAL_CORTEX_MPU_MEM_ATTR_0;

  HAL_CORTEX_MPU_SetConfigRegion(HAL_CORTEX_MPU_REGION_0, &p_region_config);
  HAL_CORTEX_MPU_SetConfigRegion(HAL_CORTEX_MPU_REGION_1, &p_region_config);
  HAL_CORTEX_MPU_SetConfigRegion(HAL_CORTEX_MPU_REGION_2, &p_region_config);
  HAL_CORTEX_MPU_SetConfigRegion(HAL_CORTEX_MPU_REGION_3, &p_region_config);
  HAL_CORTEX_MPU_SetConfigRegion(HAL_CORTEX_MPU_REGION_4, &p_region_config);
  HAL_CORTEX_MPU_SetConfigRegion(HAL_CORTEX_MPU_REGION_5, &p_region_config);
  HAL_CORTEX_MPU_SetConfigRegion(HAL_CORTEX_MPU_REGION_6, &p_region_config);
  HAL_CORTEX_MPU_SetConfigRegion(HAL_CORTEX_MPU_REGION_7, &p_region_config);
}