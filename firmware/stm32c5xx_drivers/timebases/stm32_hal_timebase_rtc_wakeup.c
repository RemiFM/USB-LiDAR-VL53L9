/**
  ******************************************************************************
  * @file    stm32_hal_timebase_rtc_wakeup.c
  * @brief   HAL timebase based on the hardware RTC_WAKEUP.
  *
  *          This file overrides the native HAL timebase functions (defined as weak)
  *          to use the RTC WAKEUP for timebase generation:
  *           + Initializes the RTC peripheral to trigger the RTC wakeup each 1ms, 10ms, or 100ms
  *           + The wakeup is configured to assert an interrupt when the RTC reaches 1ms, 10ms, or 100ms
  *           + HAL_IncTick is called at each Wakeup event
  *           + HSE (default), LSE or LSI can be selected as RTC clock source
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"
#include "stm32_hal_timebase.h"
/** @addtogroup STM32C5xx_HAL_Driver
  * @{
  */
/** @defgroup HAL_TimeBase_RTC_Wakeup  HAL TimeBase RTC Wake-up
  * @{
  */
/** @defgroup TimeBase_RTC_Wakeup_Introduction TimeBase RTC Wake-up Introduction
  * @{
  *
  * - The RTC wake-up timebase pattern provides an alternative to the default Cortex System Timer (SysTick)
  *   for the HAL timebase in STM32 microcontrollers.
  *
  * - This is useful in applications where SysTick is reserved for an RTOS, or when an ultra-low-power
  *   timebase is required. In this case, the RTC peripheral and its wake-up timer feature are used
  *   to generate periodic interrupts for the HAL tick.
  *
  * - The RTC wake-up timebase implementation is ready-to-use, requires no customization, and integrates
  *   seamlessly with the STM32 HAL.
  *
  */
/**
  * @}
  */
/** @defgroup TimeBase_RTC_Wakeup_How_To_Use TimeBase RTC Wakeup How To Use
  * @{
# How to use this driver #####
    Copy this file to the application folder and modify it as follows:
    - Rename it to 'stm32_hal_timebase_rtc_wakeup.c'.
    - Add this file and the RTC HAL drivers to the project and uncomment the
      USE_HAL_RTC_MODULE define in stm32c5xx_hal_conf.h.
    - Do not use the HAL RTC wake-up and HAL RTC Wake-up drivers with low-power modes:
      The RTC wake-up capability can be intrusive when a prior low power mode
      configuration requires different wake-up sources.
      Application or example behavior is no longer guaranteed.
    - Use stm32_hal_timebase_rtc_wakeup.c for applications or examples requiring low-power modes.
  */
/**
  * @}
  */
/** @defgroup TimeBase_RTC_Wakeup_Configuration_Table TimeBase RTC Wake-up Configuration Table
  * @{
## Configuration inside the timebase RTC wake-up:
Config defines                  | Where            | Default value     | Note
------------------------------- | -----------------| ------------------| -------------------------------------------
USE_HAL_RTC_MODULE              | hal_conf.h       |         1         | Enable the HAL RTC module
USE_ASSERT_DBG_PARAM            | PreProcessor env |         NA        | Enable parameter assert
  */
/**
  * @}
  */
#if defined(USE_HAL_RTC_MODULE) && (USE_HAL_RTC_MODULE == 1)
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define WAKEUP_RTCCLK_DIV      2U
#define SECOND_TO_HZ_CONVERTER 1000U
#define ASYNCH_PREDIV_DEFAULT  127U
#define SYNCH_PREDIV_DEFAULT   255U
/* Private macro -------------------------------------------------------------*/
/* Exported variables by reference--------------------------------------------*/
/** @defgroup TimeBase_RTC_Wakeup_Private_Macros HAL TimeBase RTC Wakeup private macros
  * @{
  */
/*! Check the HAL tick frequency value */
#define IS_TICK_FREQ(freq) (((freq) == HAL_TICK_FREQ_10HZ)     \
                            || ((freq) == HAL_TICK_FREQ_100HZ) \
                            || ((freq) == HAL_TICK_FREQ_1KHZ))
/*! Check the HAL tick priority value */
#define IS_TICK_PRIO(prio) ((prio) <= ((1UL << __NVIC_PRIO_BITS) - 1UL))
/**
  * @}
  */
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static hal_status_t rtc_wakeup_timebase_config_tick(hal_tick_freq_t tick_freq);
/* Private functions ---------------------------------------------------------*/
static hal_status_t rtc_wakeup_timebase_config_tick(hal_tick_freq_t tick_freq)
{
  hal_rtc_wakeup_config_t wakeup_config;
  hal_rtc_date_t date;
  hal_rtc_config_t rtc_config;
  uint32_t wakeup_reload_val;

  rtc_config.asynch_prediv = ASYNCH_PREDIV_DEFAULT; /* Default LSE value; not required for WUT usage */
  rtc_config.synch_prediv = SYNCH_PREDIV_DEFAULT;  /* Default LSE value; not required for WUT usage */
  rtc_config.mode = HAL_RTC_MODE_BCD;
  if (HAL_RTC_SetConfig(&rtc_config) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Set the year to a value other than zero to trigger INITS (calendar initialized) */
  date.wday = HAL_RTC_WEEKDAY_MONDAY;
  date.mon = HAL_RTC_MONTH_JANUARY;
  date.mday = 1U;
  date.year = 1U;
  if (HAL_RTC_CALENDAR_SetDate(&date) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Set DIV2 because it is the lowest divider */
  wakeup_config.clock = (hal_rtc_wakeup_timer_clock_t) HAL_RTC_WAKEUP_TIMER_CLOCK_RTCCLK_DIV2;
  if (HAL_RTC_WAKEUP_SetConfig(&wakeup_config) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /*
    Wakeup frequency = RTC clock / WUCKSEL * (wakeup_reload_val + 1) tick_freq is the tick period in milliseconds.
    WUCKSEL = 2, then wakeup_reload_val = round((RTC clock * tick_period_ms) / (2 * 1000)) - 1
  */
  wakeup_reload_val = (uint32_t)((((uint64_t)HAL_RCC_RTC_GetKernelClkFreq() * (uint64_t)tick_freq)
                                  + (((uint64_t)WAKEUP_RTCCLK_DIV * (uint64_t)SECOND_TO_HZ_CONVERTER) / 2U))
                                 / ((uint64_t)WAKEUP_RTCCLK_DIV * (uint64_t)SECOND_TO_HZ_CONVERTER)) - 1U;
  if (HAL_RTC_WAKEUP_SetAutoReloadAndAutoClear(wakeup_reload_val, 0U) != HAL_OK)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/** @defgroup TimeBase_RTC_Wakeup_Exported_Functions HAL TimeBase RTC Wakeup Functions
  * @{
  */
/**
  * @brief Configure the timebase frequency and interrupt priority.
  * @param tick_freq  Tick frequency of type **hal_tick_freq_t** (to keep the current value, use global variable
  *        @ref uwTickFreq)
  * @param tick_priority Tick interrupt priority (to keep the current value, use global variable @ref uwTickPrio)
  * @note  Called at the beginning of the program by HAL_Init()
  *        or when the system core clock is modified (for instance, by the HAL RCC driver when needed).
  * @note  Declared as __WEAK to allow override in a user file.
  * @warning HAL tick is updated from interrupts at regular time intervals.
  *          Take care if HAL_Delay() is called from a peripheral interrupt process:
  *          the tick interrupt line needs higher priority (numerically lower) than the peripheral interrupt;
  *          otherwise, the caller interrupt process is blocked.
  * @retval HAL_OK HAL timebase correctly configured
  */
hal_status_t HAL_InitTick(hal_tick_freq_t tick_freq, uint32_t tick_priority)
{
  ASSERT_DBG_PARAM(IS_TICK_FREQ(tick_freq));
  ASSERT_DBG_PARAM(IS_TICK_PRIO(tick_priority));

  if (HAL_RTC_CALENDAR_IsInitialized() == HAL_RTC_CALENDAR_NOT_INITIALIZED)
  {
    timebase_init();
  }
  else
  {
    if (HAL_RTC_WAKEUP_Stop() != HAL_OK)
    {
      return HAL_ERROR;
    }
  }

  HAL_RTC_DisableWriteProtection();
  HAL_RTC_EnterInitMode();

  if (rtc_wakeup_timebase_config_tick(tick_freq) != HAL_OK)
  {
    return HAL_ERROR;
  }
  uwTickFreq = tick_freq;
  uwTickPrio = tick_priority;

  HAL_CORTEX_NVIC_SetPriority(TIMEBASE_IRQ, (hal_cortex_nvic_preemp_priority_t)tick_priority,
                              (hal_cortex_nvic_sub_priority_t)0U);

  /* Start RTC wake-up with interrupt */
  if (HAL_RTC_WAKEUP_Start(HAL_RTC_WAKEUP_IT_ENABLE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_RTC_ExitInitMode();
  HAL_RTC_EnableWriteProtection();

  return HAL_OK;
}

/**
  * @brief  Suspend tick increment.
  * @note   Disable tick increment by disabling the RTC wake-up interrupt.
  * @retval None
  */
void HAL_SuspendTick(void)
{
  HAL_RTC_DisableWriteProtection();

  HAL_RTC_WAKEUP_Stop();

  HAL_RTC_EnableWriteProtection();
}

/**
  * @brief  Resume tick increment.
  * @note   Enable tick increment by enabling the RTC wake-up interrupt.
  * @retval None
  */
void HAL_ResumeTick(void)
{
  HAL_RTC_DisableWriteProtection();

  HAL_RTC_WAKEUP_Start(HAL_RTC_WAKEUP_IT_ENABLE);

  HAL_RTC_EnableWriteProtection();
}

/**
  * @brief  Handle the RTC wake-up callback.
  * @param  None
  * @retval None
  */
void HAL_RTC_WakeUpTimerEventCallback(void)
{
  HAL_IncTick();
}

/**
  * @}
  */
#endif /* USE_HAL_RTC_MODULE */
/**
  * @}
  */
/**
  * @}
  */
