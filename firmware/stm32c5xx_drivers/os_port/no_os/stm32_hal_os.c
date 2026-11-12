/**
  ******************************************************************************
  * @file    stm32_hal_os.c
  * @brief   STM32 HAL OS abstraction: implementation for NO_OS.
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

#include "stm32_hal.h"

/** @addtogroup STM32_HAL_OS
  * @{
  */

/** @addtogroup NO_OS
  * @{
  */

/** @defgroup NO_OS_Introduction NO_OS Introduction
  * @{

The STM32 HAL OS Abstraction Layer provides a unified interface for operating system (OS) primitives
such as semaphores and mutexes, enabling STM32 HAL drivers and middleware to be portable across different
OS environments.

This module abstracts the underlying OS-specific mechanisms, allowing application code and drivers to use
synchronization primitives without being tightly coupled to a particular RTOS or bare-metal implementation.

The main purpose of this module is to facilitate safe and efficient access to shared resources in both
multitasking (RTOS) and single-threaded (No OS) environments.
By providing a consistent API, the HAL OS layer enables developers to switch between FreeRTOS and bare-metal (No OS)
configurations with minimal code changes, improving code reusability and maintainability.

  */
/**
  * @}
  */

/** @defgroup NO_OS_How_To_Use NO_OS How To Use
  * @{

# How to use the OS HAL module driver
Use the OS HAL driver as follows:

1. Create a semaphore or mutex:
  - Create a new semaphore instance using the HAL_OS_SemaphoreCreate() function.
  - Create a new mutex instance using the HAL_OS_MutexCreate() function.
  - A semaphore or a mutex is a simple uint32 variable that is set atomically.

2. Delete a semaphore or mutex:
  - Delete a semaphore instance using the HAL_OS_SemaphoreDelete() function.
    - The HAL_OS_SemaphoreDelete() API ensures that memory operations have been completed
      using the Data Memory Barrier instruction "__DMB()" before resetting the semaphore.

  - Delete a mutex instance using the HAL_OS_MutexDelete() function.
    - The HAL_OS_MutexDelete() API ensures that memory operations have been completed
      using the Data Memory Barrier instruction "__DMB()" before resetting the semaphore.

3. Take the semaphore or mutex when required:
  - Take a semaphore using the HAL_OS_SemaphoreTake() function.
    - The HAL_OS_SemaphoreTake() API allows setting the semaphore variable atomically using exclusive
      loading and storage instructions "__LDREXW" and "__STREXW".

  - Take a mutex using the HAL_OS_MutexTake() function, which behaves the same as HAL_OS_SemaphoreTake().

4. Release the semaphore or mutex:
  - Release a semaphore using the HAL_OS_SemaphoreRelease() function.
    - The HAL_OS_SemaphoreRelease() API ensures that memory operations have been completed
      using the Data Memory Barrier instruction "__DMB()" before resetting the semaphore.

  - Release a mutex using the HAL_OS_MutexRelease() function, which behaves the same as HAL_OS_SemaphoreRelease().
  */
/**
  * @}
  */

/** @defgroup NO_OS_Configuration_Table NO_OS Configuration Table
  * @{
# Configuration inside the OS driver

Config defines             | Description           | Default value   | Note
---------------------------| --------------------- | ----------------| --------------------------------------------
USE_HAL_MUTEX  | from hal_conf.h | 0 | Allows HAL PPP drivers to enable HAL PPP acquire/release based on the HAL OS
  */
/**
  * @}
  */

#if defined (USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1)
/* Private constants --------------------------------------------------------*/
/* Private types ------------------------------------------------------------*/
/* Private variables --------------------------------------------------------*/
/* Private functions --------------------------------------------------------*/
/* Exported types -----------------------------------------------------------*/
/* Exported functions -------------------------------------------------------*/
/** @addtogroup NO_OS_Exported_Functions
  * @{
  */

/** @addtogroup NO_OS_Exported_Functions_Group1
  * @{
This subsection provides a set of functions that control access to shared resources using a semaphore:
- Call the function HAL_OS_SemaphoreCreate() to create a new semaphore instance.
- Call the function HAL_OS_SemaphoreTake() to obtain a previously created semaphore.
- Call the function HAL_OS_SemaphoreRelease() to release a semaphore.
- Call the function HAL_OS_SemaphoreDelete() to delete a semaphore.
  */

/**
  * @brief  Create a new binary semaphore instance.
  * @param  p_sem         Pointer to a hal_os_semaphore_t structure.
  * @retval HAL_OS_OK     Semaphore instance created successfully.
  */
hal_os_status_t HAL_OS_SemaphoreCreate(hal_os_semaphore_t *p_sem)
{
  hal_os_status_t status = HAL_OS_ERROR;

  if (p_sem != NULL)
  {
    status = HAL_OS_OK;
    *p_sem = 0;
  }
  return status;
}

/**
  * @brief  Take a semaphore that was created previously.
  * @param  p_sem         Pointer to a hal_os_semaphore_t structure.
  * @param  timeout_ms    The time to wait for the semaphore to become available in ms.
  * @retval HAL_OS_OK     Semaphore taken successfully.
  * @retval HAL_OS_ERROR  The timeout_ms expired without the semaphore becoming available.
  */
hal_os_status_t HAL_OS_SemaphoreTake(hal_os_semaphore_t *p_sem, uint32_t timeout_ms)
{
  hal_os_status_t status = HAL_OS_ERROR;

  uint32_t tickstart = HAL_GetTick();

  uint32_t time_over = 0;

  if ((__get_IPSR() != 0U) && (timeout_ms != 0U))
  {
    return status;
  }
  else
  {
    do
    {
      if (__LDREXW(p_sem) == 0U)
      {
        if (__STREXW(1, p_sem) == 0U)
        {
          status =  HAL_OS_OK;
        }
      }
      if (timeout_ms != HAL_OS_TIMEOUT_FOREVER)
      {
        if (((HAL_GetTick() - tickstart) > timeout_ms) || (timeout_ms == 0U))
        {
          time_over = 1;
        }
      }
    } while ((time_over == 0U) && (status != HAL_OS_OK));
  }

  /* Do not start any other memory access until the memory barrier is complete. */
  __DMB();

  return status;
}

/**
  * @brief  Release the semaphore.
  * @param  p_sem         Pointer to a hal_os_semaphore_t structure.
  * @retval HAL_OS_OK     Semaphore released successfully.
  * @retval HAL_OS_ERROR  An error occurred.
  */
hal_os_status_t HAL_OS_SemaphoreRelease(hal_os_semaphore_t *p_sem)
{
  hal_os_status_t status = HAL_OS_ERROR;

  if (p_sem != NULL)
  {
    status = HAL_OS_OK;

    /* Ensure memory operations complete before releasing p_sem. */
    __DMB();
    *p_sem = 0;
  }

  return status;
}

/**
  * @brief  Delete the semaphore.
  * @param  p_sem         Pointer to a hal_os_semaphore_t structure.
  * @retval HAL_OS_OK     Semaphore deleted successfully.
  * @retval HAL_OS_ERROR  An error occurred.
  */
hal_os_status_t HAL_OS_SemaphoreDelete(hal_os_semaphore_t *p_sem)
{
  hal_os_status_t status = HAL_OS_ERROR;

  if (p_sem != NULL)
  {
    status = HAL_OS_OK;

    /* Ensure memory operations complete before releasing p_sem. */
    __DMB();
    *p_sem = 0;
  }

  return status;
}

/**
  * @}
  */

/** @addtogroup NO_OS_Exported_Functions_Group2
  * @{
This subsection provides a set of functions that control access to shared resources using a mutex:
- Call the function HAL_OS_MutexCreate() to create a mutex.
- Call the function HAL_OS_MutexTake() to take a mutex.
- Call the function HAL_OS_MutexRelease() to release a mutex.
- Call the function HAL_OS_MutexDelete() to delete a mutex.
  */

/**
  * @brief  Create a new mutex instance.
  * @param  p_mutex       Pointer to a hal_os_mutex_t structure.
  * @retval HAL_OS_OK     Mutex created successfully.
  * @retval HAL_OS_ERROR  An error occurred.
  */
hal_os_status_t HAL_OS_MutexCreate(hal_os_mutex_t *p_mutex)
{
  return HAL_OS_SemaphoreCreate((hal_os_semaphore_t *)p_mutex);
}

/**
  * @brief  Take a mutex that was created previously.
  * @param  p_mutex       Pointer to a hal_os_mutex_t structure.
  * @param  timeout_ms    The time to wait for the mutex to become available in ms.
  * @retval HAL_OS_OK     Mutex taken successfully.
  * @retval HAL_OS_ERROR  The timeout_ms expired without the mutex becoming available.
  */
hal_os_status_t HAL_OS_MutexTake(hal_os_mutex_t *p_mutex, uint32_t timeout_ms)
{
  return HAL_OS_SemaphoreTake((hal_os_semaphore_t *)p_mutex, timeout_ms);
}

/**
  * @brief  Release the mutex.
  * @param  p_mutex       Pointer to a hal_os_mutex_t structure.
  * @retval HAL_OS_OK     Mutex released successfully.
  * @retval HAL_OS_ERROR  An error occurred.
  */
hal_os_status_t HAL_OS_MutexRelease(hal_os_mutex_t *p_mutex)
{
  return HAL_OS_SemaphoreRelease((hal_os_semaphore_t *)p_mutex);
}

/**
  * @brief  Delete the mutex.
  * @param  p_mutex   Pointer to a hal_os_mutex_t structure.
  * @retval HAL_OS_OK    Mutex deleted successfully.
  * @retval HAL_OS_ERROR  An error occurred.
  */
hal_os_status_t HAL_OS_MutexDelete(hal_os_mutex_t *p_mutex)
{
  return HAL_OS_SemaphoreDelete((hal_os_semaphore_t *)p_mutex);
}

/**
  * @}
  */

/**
  * @}
  */

#endif /* USE_HAL_MUTEX */

/**
  * @}
  */

/**
  * @}
  */
