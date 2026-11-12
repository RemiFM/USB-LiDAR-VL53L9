# origin-pack: STMicroelectronics::stm32c5xx_hal_drivers@2.1.0
# file-format: 1.0.0
project(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0)
cmake_minimum_required(VERSION 3.20)
add_library(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE)

# List of all CMSIS properties that influence conditions for this package
if(NOT DEFINED CMSIS_Dname)
  set(CMSIS_Dname "CMSIS_Dname not set")
  message(DEBUG "CMSIS_Dname is not set to any value")
endif()

if(NOT DEFINED CMSIS_Dvendor)
  set(CMSIS_Dvendor "CMSIS_Dvendor not set")
  message(DEBUG "CMSIS_Dvendor is not set to any value")
endif()


# Device specific defined symbols








# Enable all components in this package
if(CMSIS_ENTIRE_STMicroelectronics_stm32c5xx_hal_drivers_2_1_0)
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:timebases#Cvariant:SYSTICK#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:RTC timebase template#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:timebases#Cvariant:RTC_ALARM#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:timebases#Cvariant:RTC_WAKEUP#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:TIM timebase template#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:timebases#Cvariant:TIM#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:Core#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL UTILS#Csub:I2C#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL UTILS#Csub:I3C#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL UTILS#Csub:FDCAN#Cversion:2.0.1")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:ASSERT#Cversion:2.1.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:template#Cversion:2.1.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:ADC#Cversion:2.0.1")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:AES#Cversion:2.0.1")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:COMP#Cversion:2.1.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:CORDIC#Cversion:2.1.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:CORTEX#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:CRC#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:CRS#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:CCB#Cversion:2.0.1")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:DAC#Cversion:2.0.1")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:DBGMCU#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL DRIVERS CORE#Csub:DLYB#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:DMA#Cversion:2.1.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:ETH#Cversion:2.1.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:EXTI#Cversion:2.1.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:FDCAN#Cversion:2.1.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:FLASH#Cversion:2.0.1")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:FLASH_ITF#Cversion:2.1.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:GPIO#Cversion:2.1.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:HASH#Cversion:2.0.1")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:HCD#Cversion:2.1.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:I2C#Cversion:2.0.1")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:I3C#Cversion:2.0.1")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:I2S#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:ICACHE#Cversion:2.1.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:IWDG#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:LPTIM#Cversion:2.1.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:OPAMP#Cversion:2.1.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:PCD#Cversion:2.1.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:PKA#Cversion:2.0.1")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:PWR#Cversion:2.0.1")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:Q#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:RAMCFG#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:RCC#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:RNG#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:RTC#Cversion:2.0.1")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:SMARTCARD#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:SMBUS#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:SPI#Cversion:2.0.1")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:SBS#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:TAMP#Cversion:2.0.1")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:TIM#Cversion:2.0.1")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:UART#Cversion:2.0.1")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:USART#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL DRIVERS CORE#Csub:USB CORE DEF#Cversion:2.1.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL DRIVERS CORE#Csub:USB DRD#Cversion:2.1.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:WWDG#Cversion:2.0.1")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:XSPI#Cversion:2.0.1")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:Common#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:ADC#Cversion:2.1.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:BUS#Cversion:2.0.1")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:COMP#Cversion:2.1.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:CORDIC#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:CRC#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:CRS#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:DAC#Cversion:2.0.1")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:DBGMCU#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:DMA#Cversion:2.1.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:FLASH#Cversion:2.1.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:EXTI#Cversion:2.1.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:GPIO#Cversion:2.1.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:I2C#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:I3C#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:ICACHE#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:IWDG#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:LPTIM#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:LPUART#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:OPAMP#Cversion:2.0.1")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:PKA#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:PWR#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:RAMCFG#Cversion:2.0.1")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:RCC#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:RNG#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:RTC#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:TAMP#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:SPI#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:SBS#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:SYSTEM#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:TIM#Cversion:2.1.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:USART#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:UTILS#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:WWDG#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:HAL OS#Cvariant:NO_OS#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:HAL OS#Cvariant:FreeRTOS#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:HAL OS#Cvariant:TEMPLATE OS#Cversion:2.0.0")
endif()

# All conditions used by this package

# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0
# description: 
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0 "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0 enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:CMSIS Core
# description: STMicroelectronics STM32C5 and HAL Common
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_CMSIS_Core "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_CMSIS_Core enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_CMSIS_Core 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL ADC
# description: HAL ADC dependencies
if((((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_ADC "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:DMA(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:ADC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:DBGMCU(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_ADC enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_ADC 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL COMP
# description: HAL COMP dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_COMP "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:COMP(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_COMP enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_COMP 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORDIC
# description: HAL CORDIC dependencies
if((((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORDIC "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:DMA(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:CORDIC(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORDIC enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORDIC 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE
# description: STMicroelectronics STM32C5 and HAL system
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE DMA
# description: STMicroelectronics STM32C5 and HAL with DMA
if((((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_DMA "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:DMA(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_DMA enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_DMA 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE DMA Init
# description: STMicroelectronics HAL CORE and DMA Init dependencies
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_DMA_Init "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_DMA_Init enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_DMA_Init 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE DMA Init and AES
# description: STMicroelectronics HAL AES Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_DMA_Init_and_AES "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_DMA_Init_and_AES enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_DMA_Init_and_AES 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE DMA Init and CORDIC
# description: STMicroelectronics HAL CORDIC Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_DMA_Init_and_CORDIC "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_DMA_Init_and_CORDIC enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_DMA_Init_and_CORDIC 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE DMA Init and HASH
# description: STMicroelectronics HAL HASH Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_DMA_Init_and_HASH "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:HASH(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_DMA_Init_and_HASH enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_DMA_Init_and_HASH 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE GPIO DMA Init
# description: STMicroelectronics HAL CORE, GPIO and DMA Init dependencies
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE GPIO DMA Init and ADC
# description: STMicroelectronics HAL ADC Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_ADC "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_ADC enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_ADC 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE GPIO DMA Init and DAC
# description: STMicroelectronics HAL DAC Init dependencies
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_DAC "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_DAC enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_DAC 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE GPIO DMA Init and I2C
# description: STMicroelectronics HAL I2C Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_I2C "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_I2C enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_I2C 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE GPIO DMA Init and I2S
# description: STMicroelectronics HAL I2S Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_I2S "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_I2S enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_I2S 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE GPIO DMA Init and I3C
# description: STMicroelectronics HAL I3C Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_I3C "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_I3C enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_I3C 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE GPIO DMA Init and LPTIM
# description: STMicroelectronics HAL LPTIM Init dependencies
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_LPTIM "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_LPTIM enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_LPTIM 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE GPIO DMA Init and SMARTCARD
# description: STMicroelectronics HAL SMARTCARD Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_SMARTCARD "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_SMARTCARD enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_SMARTCARD 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE GPIO DMA Init and SPI
# description: STMicroelectronics HAL SPI Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_SPI "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_SPI enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_SPI 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE GPIO DMA Init and TIM
# description: STMicroelectronics HAL TIM Init dependencies
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_TIM "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_TIM enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_TIM 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE GPIO DMA Init and UART
# description: STMicroelectronics HAL UART Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_UART "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_UART enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_UART 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE GPIO DMA Init and USART
# description: STMicroelectronics HAL USART Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_USART "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_USART enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_USART 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE GPIO DMA Init and XSPI
# description: STMicroelectronics HAL SPI Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_XSPI "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:XSPI(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_XSPI enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_DMA_Init_and_XSPI 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE GPIO Init and COMP
# description: HAL COMP Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND ((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_Init_and_COMP "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>,$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_Init_and_COMP enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_Init_and_COMP 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE GPIO Init and ETH
# description: STMicroelectronics HAL ETH Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_Init_and_ETH "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>,$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:ETH(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_Init_and_ETH enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_Init_and_ETH 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE GPIO Init and FDCAN
# description: STMicroelectronics HAL FDCAN Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_Init_and_FDCAN "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>,$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:FDCAN(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_Init_and_FDCAN enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_Init_and_FDCAN 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE GPIO Init and HCD
# description: STMicroelectronics HAL HCD Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_Init_and_HCD "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>,$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:HCD(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_Init_and_HCD enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_Init_and_HCD 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE GPIO Init and OPAMP
# description: STMicroelectronics HAL OPAMP Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_Init_and_OPAMP "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>,$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_Init_and_OPAMP enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_Init_and_OPAMP 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE GPIO Init and PCD
# description: STMicroelectronics HAL PCD Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_Init_and_PCD "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>,$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:PCD(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_Init_and_PCD enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_Init_and_PCD 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE GPIO Init and PWR
# description: STMicroelectronics HAL PWR Init
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_Init_and_PWR "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_Init_and_PWR enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_Init_and_PWR 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE GPIO Init and RTC
# description: STMicroelectronics HAL RTC Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_Init_and_RTC "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>,$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_Init_and_RTC enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_Init_and_RTC 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE GPIO Init and SMBUS
# description: STMicroelectronics HAL SMBUS Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_Init_and_SMBUS "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>,$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_Init_and_SMBUS enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_Init_and_SMBUS 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE GPIO Init and TAMP
# description: STMicroelectronics HAL TAMP Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_Init_and_TAMP "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>,$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_Init_and_TAMP enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_GPIO_Init_and_TAMP 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE Init GPIO and CORTEX
# description: STMicroelectronics HAL CORTEX Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_GPIO_and_CORTEX "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_GPIO_and_CORTEX enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_GPIO_and_CORTEX 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE Init GPIO and CRS
# description: STMicroelectronics HAL CRS Init dependencies
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_GPIO_and_CRS "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_GPIO_and_CRS enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_GPIO_and_CRS 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE Init GPIO and RCC
# description: STMicroelectronics HAL Common Init
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_GPIO_and_RCC "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_GPIO_and_RCC enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_GPIO_and_RCC 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE Init and CCB
# description: STMicroelectronics HAL CCB Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_and_CCB "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CCB(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_and_CCB enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_and_CCB 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE Init and CORTEX
# description: STMicroelectronics HAL CORTEX Init dependencies
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_and_CORTEX "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_and_CORTEX enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_and_CORTEX 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE Init and CRC
# description: STMicroelectronics HAL CRC Init dependencies
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_and_CRC "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_and_CRC enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_and_CRC 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE Init and FLASH
# description: STMicroelectronics HAL FLASH Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_and_FLASH "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_and_FLASH enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_and_FLASH 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE Init and ICACHE
# description: STMicroelectronics HAL ICACHE Init dependencies
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_and_ICACHE "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_and_ICACHE enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_and_ICACHE 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE Init and IWDG
# description: STMicroelectronics HAL IWDG Init dependencies
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_and_IWDG "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_and_IWDG enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_and_IWDG 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE Init and PKA
# description: STMicroelectronics HAL PKA Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_and_PKA "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_and_PKA enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_and_PKA 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE Init and RAMCFG
# description: STMicroelectronics HAL RAMCFG Init dependencies
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_and_RAMCFG "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_and_RAMCFG enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_and_RAMCFG 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE Init and RNG
# description: STMicroelectronics HAL RNG Init dependencies
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_and_RNG "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_and_RNG enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_and_RNG 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE Init and SBS
# description: STMicroelectronics HAL SBS Init dependencies
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_and_SBS "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_and_SBS enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_and_SBS 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE Init and WWDG
# description: STMicroelectronics HAL WWDG Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_and_WWDG "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_and_WWDG enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_Init_and_WWDG 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE USB
# description: HAL CORE USB dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_USB "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL DRIVERS CORE#.*Csub:USB DRD(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL DRIVERS CORE#.*Csub:USB CORE DEF(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_USB enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_USB 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORE XSPI
# description: HAL CORE XSPI dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_XSPI "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL DRIVERS CORE#.*Csub:DLYB(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_XSPI enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_XSPI 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CORTEX
# description: HAL CORTEX dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORTEX "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORTEX enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORTEX 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CRC
# description: HAL CRC dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CRC "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:CRC(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CRC enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CRC 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL CRS
# description: HAL CRS dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CRS "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:CRS(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CRS enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CRS 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL Common
# description: STMicroelectronics STM32C5 and HAL common
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_Common "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_Common enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_Common 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL DAC
# description: HAL DAC dependencies
if((((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_DAC "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:DMA(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:DAC(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_DAC enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_DAC 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL DBGMCU
# description: HAL DBGMCU dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_DBGMCU "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:DBGMCU(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_DBGMCU enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_DBGMCU 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL DMA
# description: HAL DMA dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_DMA "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:DMA(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Q(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_DMA enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_DMA 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL EXTI
# description: HAL EXTI dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_EXTI "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_EXTI enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_EXTI 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL FLASH
# description: HAL FLASH dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_FLASH "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:FLASH_ITF(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_FLASH enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_FLASH 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL FLASH_ITF
# description: HAL FLASH_ITF dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_FLASH_ITF "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:FLASH(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_FLASH_ITF enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_FLASH_ITF 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL GPIO
# description: HAL GPIO dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_GPIO "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:GPIO(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_GPIO enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_GPIO 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL GPIO Init
# description: STMicroelectronics HAL Common Init
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_GPIO_Init "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_GPIO_Init enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_GPIO_Init 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL Generated code
# description: STMicroelectronics HAL components used for code Generation
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_Generated_code "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_Generated_code enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_Generated_code 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL I2C
# description: HAL I2C dependencies
if((((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_I2C "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:DMA(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:I2C(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_I2C enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_I2C 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL I2S
# description: HAL I2S dependencies
if((((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_I2S "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:DMA(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:SPI(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_I2S enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_I2S 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL I3C
# description: HAL I3C dependencies
if((((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_I3C "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:DMA(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:I3C(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_I3C enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_I3C 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL ICACHE
# description: HAL ICACHE dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_ICACHE "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:ICACHE(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_ICACHE enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_ICACHE 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL IWDG
# description: HAL IWDG dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_IWDG "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:IWDG(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_IWDG enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_IWDG 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL LPTIM
# description: HAL LPTIM dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_LPTIM "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:LPTIM(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_LPTIM enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_LPTIM 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL OPAMP
# description: HAL OPAMP dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_OPAMP "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:OPAMP(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_OPAMP enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_OPAMP 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL PKA
# description: HAL PKA dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_PKA "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PKA(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_PKA enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_PKA 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL PWR
# description: HAL PWR dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_PWR "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_PWR enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_PWR 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL RAMCFG
# description: HAL RAMCFG dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_RAMCFG "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:RAMCFG(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_RAMCFG enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_RAMCFG 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL RCC
# description: HAL RCC dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_RCC "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:BUS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_RCC enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_RCC 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL RNG
# description: HAL RNG dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_RNG "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:RNG(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_RNG enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_RNG 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL RTC
# description: HAL RTC dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_RTC "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:RTC(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_RTC enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_RTC 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL SBS
# description: HAL SBS dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_SBS "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:SBS(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_SBS enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_SBS 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL SMARTCARD
# description: HAL SMARTCARD dependencies
if((((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_SMARTCARD "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:DMA(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:USART(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_SMARTCARD enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_SMARTCARD 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL SMBUS
# description: HAL SMBUS dependencies
if((((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_SMBUS "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:DMA(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:I2C(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_SMBUS enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_SMBUS 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL SPI
# description: HAL SPI dependencies
if((((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_SPI "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:DMA(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:SPI(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_SPI enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_SPI 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL System Init
# description: STMicroelectronics HAL Common Init
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_System_Init "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_System_Init enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_System_Init 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL TAMP
# description: HAL TAMP dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_TAMP "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:TAMP(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_TAMP enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_TAMP 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL TIM
# description: HAL TIM dependencies
if((((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_TIM "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:DMA(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:TIM(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:SBS(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_TIM enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_TIM 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL UART
# description: HAL UART dependencies
if((((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_UART "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:DMA(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:USART(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_UART enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_UART 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL USART
# description: HAL USART dependencies
if((((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_USART "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:DMA(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:USART(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_USART enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_USART 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:HAL WWDG
# description: HAL WWDG dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_WWDG "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:WWDG(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_WWDG enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_WWDG 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:LL
# description: STMicroelectronics STM32C5 and LL
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:Common(#.*|$)>,>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:MW FreeRTOS
# description: MW FreeRTOS used for HAL OS
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_MW_FreeRTOS "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:template(#.*|$)>,>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_MW_FreeRTOS enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_MW_FreeRTOS 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:NO OS
# description: NO MW used for HAL OS
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_NO_OS "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:template(#.*|$)>,>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_NO_OS enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_NO_OS 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:STM32C5
# description: STMicroelectronics STM32C5
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_STM32C5 "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_STM32C5 enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_STM32C5 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:TEMPLATE OS
# description: TEMPLATE OS used for HAL OS
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_TEMPLATE_OS "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:template(#.*|$)>,>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_TEMPLATE_OS enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_TEMPLATE_OS 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:Timebase HAL RTC ALARM or WKUP
# description: HAL timebase based on RTC ALARM or WAKEUP
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_Timebase_HAL_RTC_ALARM_or_WKUP "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RTC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RTC timebase template(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_Timebase_HAL_RTC_ALARM_or_WKUP enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_Timebase_HAL_RTC_ALARM_or_WKUP 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:Timebase HAL TIM
# description: HAL timebase based on TIM
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_Timebase_HAL_TIM "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:TIM(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:TIM timebase template(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_Timebase_HAL_TIM enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_Timebase_HAL_TIM 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:Timebase NONE
# description: HAL timebase NONE
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_Timebase_NONE "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_Timebase_NONE enabled")
else()
  set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_Timebase_NONE 0)
endif()


# condition: STMicroelectronics.stm32c5xx_hal_drivers.2.1.0:Use mutex
# description: STMicroelectronics HAL condition to check if USE_HAL_MUTEX is enabled
set(STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_Use_mutex "1")
message(DEBUG "CMSIS condition STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_Use_mutex enabled")

# Files and components in this package
if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:timebases#Cvariant:SYSTICK#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # HAL timebases based on Systick
  message(DEBUG "Using component Device_STM32_HAL_timebases_SYSTICK_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_Timebase_NONE}:-DCMSIS_USE_Device_STM32_HAL_timebases_SYSTICK_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_Timebase_NONE}:${CMAKE_CURRENT_LIST_DIR}/timebases/>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:RTC timebase template#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # HAL RTC templates used for timebases based on RTC alarm or RTC wakeup
  message(DEBUG "Using component Device_STM32_HAL_RTC_timebase_template_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_Common}:-DCMSIS_USE_Device_STM32_HAL_RTC_timebase_template_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_Common}:${CMAKE_CURRENT_LIST_DIR}/templates/timebases>")
  if(EXISTS ${CMSIS_RTE_FOLDER}/Device/mx_rtc.c)
    target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_Common}:${CMSIS_RTE_FOLDER}/Device/mx_rtc.c>")
  else()
    target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_Common}:${CMAKE_CURRENT_LIST_DIR}/templates/timebases/mx_rtc.c>")
  endif()
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:timebases#Cvariant:RTC_ALARM#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # HAL timebases based on RTC alarm
  message(DEBUG "Using component Device_STM32_HAL_timebases_RTC_ALARM_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_Timebase_HAL_RTC_ALARM_or_WKUP}:-DCMSIS_USE_Device_STM32_HAL_timebases_RTC_ALARM_2_0_0=1>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_Timebase_HAL_RTC_ALARM_or_WKUP}:${CMAKE_CURRENT_LIST_DIR}/timebases/stm32_hal_timebase_rtc_alarm.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:timebases#Cvariant:RTC_WAKEUP#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # HAL timebases based on RTC wakeup
  message(DEBUG "Using component Device_STM32_HAL_timebases_RTC_WAKEUP_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_Timebase_HAL_RTC_ALARM_or_WKUP}:-DCMSIS_USE_Device_STM32_HAL_timebases_RTC_WAKEUP_2_0_0=1>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_Timebase_HAL_RTC_ALARM_or_WKUP}:${CMAKE_CURRENT_LIST_DIR}/timebases/stm32_hal_timebase_rtc_wakeup.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:TIM timebase template#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # HAL templates
  message(DEBUG "Using component Device_STM32_HAL_TIM_timebase_template_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_Common}:-DCMSIS_USE_Device_STM32_HAL_TIM_timebase_template_2_0_0=1>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:timebases#Cvariant:TIM#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # HAL timebases based on TIM
  message(DEBUG "Using component Device_STM32_HAL_timebases_TIM_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_Timebase_HAL_TIM}:-DCMSIS_USE_Device_STM32_HAL_timebases_TIM_2_0_0=1>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_Timebase_HAL_TIM}:${CMAKE_CURRENT_LIST_DIR}/timebases/stm32_hal_timebase_tim.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:Core#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Common HAL driver
  message(DEBUG "Using component Device_STM32_HAL_Core_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_Common}:-DCMSIS_USE_Device_STM32_HAL_Core_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_Common}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_Common}:${CMAKE_CURRENT_LIST_DIR}/hal/>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_Common}:${CMAKE_CURRENT_LIST_DIR}/ll/>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_Common}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL UTILS#Csub:I2C#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Utilities I2C
  message(DEBUG "Using component Device_STM32_HAL_UTILS_I2C_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_Common}:-DCMSIS_USE_Device_STM32_HAL_UTILS_I2C_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_Common}:${CMAKE_CURRENT_LIST_DIR}/utils/i2c_timing>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_Common}:${CMAKE_CURRENT_LIST_DIR}/utils/i2c_timing/stm32_utils_i2c.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL UTILS#Csub:I3C#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Utilities I3C
  message(DEBUG "Using component Device_STM32_HAL_UTILS_I3C_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_Common}:-DCMSIS_USE_Device_STM32_HAL_UTILS_I3C_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_Common}:${CMAKE_CURRENT_LIST_DIR}/utils/i3c_timing>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_Common}:${CMAKE_CURRENT_LIST_DIR}/utils/i3c_timing/stm32_utils_i3c.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL UTILS#Csub:FDCAN#Cversion:2.0.1" IN_LIST CMSIS_COMPONENTS_LIST)  # Utilities FDCAN
  message(DEBUG "Using component Device_STM32_HAL_UTILS_FDCAN_2_0_1")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_Common}:-DCMSIS_USE_Device_STM32_HAL_UTILS_FDCAN_2_0_1=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_Common}:${CMAKE_CURRENT_LIST_DIR}/utils/fdcan_timing>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_Common}:${CMAKE_CURRENT_LIST_DIR}/utils/fdcan_timing/stm32_utils_fdcan.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:ASSERT#Cversion:2.1.0" IN_LIST CMSIS_COMPONENTS_LIST)  # HAL ASSERT template
  message(DEBUG "Using component Device_STM32_HAL_ASSERT_2_1_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_Common}:-DCMSIS_USE_Device_STM32_HAL_ASSERT_2_1_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_Common}:${CMAKE_CURRENT_LIST_DIR}/templates/common>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:template#Cversion:2.1.0" IN_LIST CMSIS_COMPONENTS_LIST)  # HAL templates
  message(DEBUG "Using component Device_STM32_HAL_template_2_1_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_Common}:-DCMSIS_USE_Device_STM32_HAL_template_2_1_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_Common}:${CMAKE_CURRENT_LIST_DIR}/templates/common>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:ADC#Cversion:2.0.1" IN_LIST CMSIS_COMPONENTS_LIST)  # Analog-to-digital converter (ADC) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_ADC_2_0_1")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_ADC}:-DCMSIS_USE_Device_STM32_HAL_ADC_2_0_1=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_ADC}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_ADC}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_adc.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:AES#Cversion:2.0.1" IN_LIST CMSIS_COMPONENTS_LIST)  # Advanced Encryption Standard (AES) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_AES_2_0_1")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_DMA}:-DCMSIS_USE_Device_STM32_HAL_AES_2_0_1=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_DMA}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_DMA}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_aes.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:COMP#Cversion:2.1.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Comparator (COMP) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_COMP_2_1_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_COMP}:-DCMSIS_USE_Device_STM32_HAL_COMP_2_1_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_COMP}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_COMP}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_comp.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:CORDIC#Cversion:2.1.0" IN_LIST CMSIS_COMPONENTS_LIST)  # CORDIC HAL driver
  message(DEBUG "Using component Device_STM32_HAL_CORDIC_2_1_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORDIC}:-DCMSIS_USE_Device_STM32_HAL_CORDIC_2_1_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORDIC}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORDIC}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_cordic.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:CORTEX#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Cortex (CORTEX) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_CORTEX_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORTEX}:-DCMSIS_USE_Device_STM32_HAL_CORTEX_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORTEX}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORTEX}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_cortex.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:CRC#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # CRC calculation unit (CRC) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_CRC_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CRC}:-DCMSIS_USE_Device_STM32_HAL_CRC_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CRC}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CRC}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_crc.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:CRS#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Clock Recovery CORE (CRS) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_CRS_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CRS}:-DCMSIS_USE_Device_STM32_HAL_CRS_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CRS}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CRS}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_crs.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:CCB#Cversion:2.0.1" IN_LIST CMSIS_COMPONENTS_LIST)  # CCB HAL driver
  message(DEBUG "Using component Device_STM32_HAL_CCB_2_0_1")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE}:-DCMSIS_USE_Device_STM32_HAL_CCB_2_0_1=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_ccb.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:DAC#Cversion:2.0.1" IN_LIST CMSIS_COMPONENTS_LIST)  # Digital-to-analog converter (DAC) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_DAC_2_0_1")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_DAC}:-DCMSIS_USE_Device_STM32_HAL_DAC_2_0_1=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_DAC}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_DAC}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_dac.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:DBGMCU#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Microcontroller debug unit (DBGMCU) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_DBGMCU_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_DBGMCU}:-DCMSIS_USE_Device_STM32_HAL_DBGMCU_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_DBGMCU}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_DBGMCU}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_dbgmcu.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL DRIVERS CORE#Csub:DLYB#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Delay Block (DLYB) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_DRIVERS_CORE_DLYB_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE}:-DCMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_DLYB_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_dlyb_core.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:DMA#Cversion:2.1.0" IN_LIST CMSIS_COMPONENTS_LIST)  # DMA controller (DMA) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_DMA_2_1_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_DMA}:-DCMSIS_USE_Device_STM32_HAL_DMA_2_1_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_DMA}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_DMA}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_dma.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:ETH#Cversion:2.1.0" IN_LIST CMSIS_COMPONENTS_LIST)  # ETH HAL driver
  message(DEBUG "Using component Device_STM32_HAL_ETH_2_1_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE}:-DCMSIS_USE_Device_STM32_HAL_ETH_2_1_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_eth.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:EXTI#Cversion:2.1.0" IN_LIST CMSIS_COMPONENTS_LIST)  # External interrupts and events (EXTI) controller
  message(DEBUG "Using component Device_STM32_HAL_EXTI_2_1_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_EXTI}:-DCMSIS_USE_Device_STM32_HAL_EXTI_2_1_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_EXTI}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_EXTI}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_exti.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:FDCAN#Cversion:2.1.0" IN_LIST CMSIS_COMPONENTS_LIST)  # FDCAN HAL Driver
  message(DEBUG "Using component Device_STM32_HAL_FDCAN_2_1_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE}:-DCMSIS_USE_Device_STM32_HAL_FDCAN_2_1_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_fdcan.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:FLASH#Cversion:2.0.1" IN_LIST CMSIS_COMPONENTS_LIST)  # Embedded FLASH memory HAL driver
  message(DEBUG "Using component Device_STM32_HAL_FLASH_2_0_1")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_FLASH}:-DCMSIS_USE_Device_STM32_HAL_FLASH_2_0_1=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_FLASH}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_FLASH}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_flash.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:FLASH_ITF#Cversion:2.1.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Embedded FLASH Option Bytes HAL driver
  message(DEBUG "Using component Device_STM32_HAL_FLASH_ITF_2_1_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_FLASH_ITF}:-DCMSIS_USE_Device_STM32_HAL_FLASH_ITF_2_1_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_FLASH_ITF}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_FLASH_ITF}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_flash_itf.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:GPIO#Cversion:2.1.0" IN_LIST CMSIS_COMPONENTS_LIST)  # General-purpose I/O (GPIO) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_GPIO_2_1_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_GPIO}:-DCMSIS_USE_Device_STM32_HAL_GPIO_2_1_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_GPIO}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_GPIO}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_gpio.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:HASH#Cversion:2.0.1" IN_LIST CMSIS_COMPONENTS_LIST)  # HASH HAL driver
  message(DEBUG "Using component Device_STM32_HAL_HASH_2_0_1")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_DMA}:-DCMSIS_USE_Device_STM32_HAL_HASH_2_0_1=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_DMA}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_DMA}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_hash.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:HCD#Cversion:2.1.0" IN_LIST CMSIS_COMPONENTS_LIST)  # HCD HAL driver
  message(DEBUG "Using component Device_STM32_HAL_HCD_2_1_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_USB}:-DCMSIS_USE_Device_STM32_HAL_HCD_2_1_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_USB}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_USB}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_hcd.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:I2C#Cversion:2.0.1" IN_LIST CMSIS_COMPONENTS_LIST)  # Inter-integrated circuit (I2C) interface HAL driver
  message(DEBUG "Using component Device_STM32_HAL_I2C_2_0_1")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_I2C}:-DCMSIS_USE_Device_STM32_HAL_I2C_2_0_1=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_I2C}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_I2C}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_i2c.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:I3C#Cversion:2.0.1" IN_LIST CMSIS_COMPONENTS_LIST)  # Improved inter-integrated circuit (I3C) interface HAL driver
  message(DEBUG "Using component Device_STM32_HAL_I3C_2_0_1")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_I3C}:-DCMSIS_USE_Device_STM32_HAL_I3C_2_0_1=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_I3C}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_I3C}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_i3c.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:I2S#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Integrated Inter-IC Sound Bus (I2S) interface HAL driver
  message(DEBUG "Using component Device_STM32_HAL_I2S_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_I2S}:-DCMSIS_USE_Device_STM32_HAL_I2S_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_I2S}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_I2S}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_i2s.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:ICACHE#Cversion:2.1.0" IN_LIST CMSIS_COMPONENTS_LIST)  # ICACHE HAL driver
  message(DEBUG "Using component Device_STM32_HAL_ICACHE_2_1_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_ICACHE}:-DCMSIS_USE_Device_STM32_HAL_ICACHE_2_1_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_ICACHE}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_ICACHE}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_icache.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:IWDG#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Independent watchdog (IWDG) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_IWDG_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_IWDG}:-DCMSIS_USE_Device_STM32_HAL_IWDG_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_IWDG}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_IWDG}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_iwdg.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:LPTIM#Cversion:2.1.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Low-power timer (LPTIM) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_LPTIM_2_1_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_LPTIM}:-DCMSIS_USE_Device_STM32_HAL_LPTIM_2_1_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_LPTIM}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_LPTIM}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_lptim.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:OPAMP#Cversion:2.1.0" IN_LIST CMSIS_COMPONENTS_LIST)  # OPAMP HAL driver
  message(DEBUG "Using component Device_STM32_HAL_OPAMP_2_1_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_OPAMP}:-DCMSIS_USE_Device_STM32_HAL_OPAMP_2_1_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_OPAMP}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_OPAMP}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_opamp.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:PCD#Cversion:2.1.0" IN_LIST CMSIS_COMPONENTS_LIST)  # USB Peripheral controller (PCD) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_PCD_2_1_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_USB}:-DCMSIS_USE_Device_STM32_HAL_PCD_2_1_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_USB}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_USB}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_pcd.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:PKA#Cversion:2.0.1" IN_LIST CMSIS_COMPONENTS_LIST)  # PKA HAL driver
  message(DEBUG "Using component Device_STM32_HAL_PKA_2_0_1")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_PKA}:-DCMSIS_USE_Device_STM32_HAL_PKA_2_0_1=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_PKA}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_PKA}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_pka.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:PWR#Cversion:2.0.1" IN_LIST CMSIS_COMPONENTS_LIST)  # Power controller (PWR) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_PWR_2_0_1")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_PWR}:-DCMSIS_USE_Device_STM32_HAL_PWR_2_0_1=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_PWR}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_PWR}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_pwr.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:Q#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Queue (Q) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_Q_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE}:-DCMSIS_USE_Device_STM32_HAL_Q_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_q.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:RAMCFG#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # RAMCFG HAL driver
  message(DEBUG "Using component Device_STM32_HAL_RAMCFG_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_RAMCFG}:-DCMSIS_USE_Device_STM32_HAL_RAMCFG_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_RAMCFG}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_RAMCFG}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_ramcfg.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:RCC#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Reset and clock control (RCC) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_RCC_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_RCC}:-DCMSIS_USE_Device_STM32_HAL_RCC_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_RCC}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_RCC}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_rcc.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:RNG#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Random number generator (RNG) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_RNG_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_RNG}:-DCMSIS_USE_Device_STM32_HAL_RNG_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_RNG}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_RNG}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_rng.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:RTC#Cversion:2.0.1" IN_LIST CMSIS_COMPONENTS_LIST)  # Real-time clock (RTC) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_RTC_2_0_1")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_RTC}:-DCMSIS_USE_Device_STM32_HAL_RTC_2_0_1=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_RTC}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_RTC}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_rtc.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:SMARTCARD#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # SMARTCARD HAL driver
  message(DEBUG "Using component Device_STM32_HAL_SMARTCARD_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_SMARTCARD}:-DCMSIS_USE_Device_STM32_HAL_SMARTCARD_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_SMARTCARD}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_SMARTCARD}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_smartcard.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:SMBUS#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # SMBus (SMBUS) interface HAL driver
  message(DEBUG "Using component Device_STM32_HAL_SMBUS_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_SMBUS}:-DCMSIS_USE_Device_STM32_HAL_SMBUS_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_SMBUS}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_SMBUS}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_smbus.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:SPI#Cversion:2.0.1" IN_LIST CMSIS_COMPONENTS_LIST)  # Serial peripheral interface (SPI) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_SPI_2_0_1")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_SPI}:-DCMSIS_USE_Device_STM32_HAL_SPI_2_0_1=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_SPI}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_SPI}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_spi.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:SBS#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # CORE configuration controller (SBS) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_SBS_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_SBS}:-DCMSIS_USE_Device_STM32_HAL_SBS_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_SBS}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_SBS}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_sbs.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:TAMP#Cversion:2.0.1" IN_LIST CMSIS_COMPONENTS_LIST)  # Tampers (TAMP) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_TAMP_2_0_1")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_TAMP}:-DCMSIS_USE_Device_STM32_HAL_TAMP_2_0_1=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_TAMP}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_TAMP}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_tamp.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:TIM#Cversion:2.0.1" IN_LIST CMSIS_COMPONENTS_LIST)  # Timers (TIM) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_TIM_2_0_1")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_TIM}:-DCMSIS_USE_Device_STM32_HAL_TIM_2_0_1=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_TIM}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_TIM}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_tim.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:UART#Cversion:2.0.1" IN_LIST CMSIS_COMPONENTS_LIST)  # Universal asynchronous receiver transmitter (UART) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_UART_2_0_1")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_UART}:-DCMSIS_USE_Device_STM32_HAL_UART_2_0_1=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_UART}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_UART}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_uart.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:USART#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Universal synchronous asynchronous receiver transmitter (USART) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_USART_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_USART}:-DCMSIS_USE_Device_STM32_HAL_USART_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_USART}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_USART}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_usart.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL DRIVERS CORE#Csub:USB CORE DEF#Cversion:2.1.0" IN_LIST CMSIS_COMPONENTS_LIST)  # USB Core Def (USB CORE DEF) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_DRIVERS_CORE_USB_CORE_DEF_2_1_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE}:-DCMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_USB_CORE_DEF_2_1_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE}:${CMAKE_CURRENT_LIST_DIR}/hal>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL DRIVERS CORE#Csub:USB DRD#Cversion:2.1.0" IN_LIST CMSIS_COMPONENTS_LIST)  # USB DRD Core (USB DRD) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_DRIVERS_CORE_USB_DRD_2_1_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE}:-DCMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_USB_DRD_2_1_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_usb_drd_core.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:WWDG#Cversion:2.0.1" IN_LIST CMSIS_COMPONENTS_LIST)  # Window watchdog (WWDG) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_WWDG_2_0_1")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_WWDG}:-DCMSIS_USE_Device_STM32_HAL_WWDG_2_0_1=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_WWDG}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_WWDG}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_wwdg.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:XSPI#Cversion:2.0.1" IN_LIST CMSIS_COMPONENTS_LIST)  # Octo-SPI/Hexa-SPI (XSPI) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_XSPI_2_0_1")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_XSPI}:-DCMSIS_USE_Device_STM32_HAL_XSPI_2_0_1=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_XSPI}:${CMAKE_CURRENT_LIST_DIR}/hal>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_HAL_CORE_XSPI}:${CMAKE_CURRENT_LIST_DIR}/hal/stm32c5xx_hal_xspi.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:Common#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Common LL driver
  message(DEBUG "Using component Device_STM32_LL_Common_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_CMSIS_Core}:-DCMSIS_USE_Device_STM32_LL_Common_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_CMSIS_Core}:${CMAKE_CURRENT_LIST_DIR}/ll/>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:ADC#Cversion:2.1.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Analog-to-digital converter (ADC) LL driver
  message(DEBUG "Using component Device_STM32_LL_ADC_2_1_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:-DCMSIS_USE_Device_STM32_LL_ADC_2_1_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:${CMAKE_CURRENT_LIST_DIR}/ll>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:BUS#Cversion:2.0.1" IN_LIST CMSIS_COMPONENTS_LIST)  # LL BUS driver
  message(DEBUG "Using component Device_STM32_LL_BUS_2_0_1")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:-DCMSIS_USE_Device_STM32_LL_BUS_2_0_1=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:${CMAKE_CURRENT_LIST_DIR}/ll>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:COMP#Cversion:2.1.0" IN_LIST CMSIS_COMPONENTS_LIST)  # COMP LL driver
  message(DEBUG "Using component Device_STM32_LL_COMP_2_1_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:-DCMSIS_USE_Device_STM32_LL_COMP_2_1_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:${CMAKE_CURRENT_LIST_DIR}/ll>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:CORDIC#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # CORDIC LL driver
  message(DEBUG "Using component Device_STM32_LL_CORDIC_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:-DCMSIS_USE_Device_STM32_LL_CORDIC_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:${CMAKE_CURRENT_LIST_DIR}/ll>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:CRC#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # CRC calculation unit (CRC) LL driver
  message(DEBUG "Using component Device_STM32_LL_CRC_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:-DCMSIS_USE_Device_STM32_LL_CRC_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:${CMAKE_CURRENT_LIST_DIR}/ll>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:CRS#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # (CRS) LL driver
  message(DEBUG "Using component Device_STM32_LL_CRS_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:-DCMSIS_USE_Device_STM32_LL_CRS_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:${CMAKE_CURRENT_LIST_DIR}/ll>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:DAC#Cversion:2.0.1" IN_LIST CMSIS_COMPONENTS_LIST)  # Digital-to-analog converter (DAC) LL driver
  message(DEBUG "Using component Device_STM32_LL_DAC_2_0_1")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:-DCMSIS_USE_Device_STM32_LL_DAC_2_0_1=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:${CMAKE_CURRENT_LIST_DIR}/ll>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:DBGMCU#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # System configuration (DBGMCU) LL driver
  message(DEBUG "Using component Device_STM32_LL_DBGMCU_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:-DCMSIS_USE_Device_STM32_LL_DBGMCU_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:${CMAKE_CURRENT_LIST_DIR}/ll>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:DMA#Cversion:2.1.0" IN_LIST CMSIS_COMPONENTS_LIST)  # DMA controller (DMA) LL driver
  message(DEBUG "Using component Device_STM32_LL_DMA_2_1_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:-DCMSIS_USE_Device_STM32_LL_DMA_2_1_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:${CMAKE_CURRENT_LIST_DIR}/ll>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:FLASH#Cversion:2.1.0" IN_LIST CMSIS_COMPONENTS_LIST)  # FLASH LL driver
  message(DEBUG "Using component Device_STM32_LL_FLASH_2_1_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:-DCMSIS_USE_Device_STM32_LL_FLASH_2_1_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:${CMAKE_CURRENT_LIST_DIR}/ll>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:EXTI#Cversion:2.1.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Extended interrupts and events controller (EXTI) LL driver
  message(DEBUG "Using component Device_STM32_LL_EXTI_2_1_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:-DCMSIS_USE_Device_STM32_LL_EXTI_2_1_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:${CMAKE_CURRENT_LIST_DIR}/ll>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:GPIO#Cversion:2.1.0" IN_LIST CMSIS_COMPONENTS_LIST)  # General-purpose I/O (GPIO) LL driver
  message(DEBUG "Using component Device_STM32_LL_GPIO_2_1_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:-DCMSIS_USE_Device_STM32_LL_GPIO_2_1_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:${CMAKE_CURRENT_LIST_DIR}/ll>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:I2C#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Inter-integrated circuit (I2C) interface LL driver
  message(DEBUG "Using component Device_STM32_LL_I2C_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:-DCMSIS_USE_Device_STM32_LL_I2C_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:${CMAKE_CURRENT_LIST_DIR}/ll>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:I3C#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Improved inter-integrated circuit (I3C) interface LL driver
  message(DEBUG "Using component Device_STM32_LL_I3C_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:-DCMSIS_USE_Device_STM32_LL_I3C_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:${CMAKE_CURRENT_LIST_DIR}/ll>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:ICACHE#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # ICACHE interface LL driver
  message(DEBUG "Using component Device_STM32_LL_ICACHE_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:-DCMSIS_USE_Device_STM32_LL_ICACHE_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:${CMAKE_CURRENT_LIST_DIR}/ll>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:IWDG#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Independent watchdog (IWDG) LL driver
  message(DEBUG "Using component Device_STM32_LL_IWDG_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:-DCMSIS_USE_Device_STM32_LL_IWDG_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:${CMAKE_CURRENT_LIST_DIR}/ll>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:LPTIM#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Low-power timer (LPTIM) interface LL driver
  message(DEBUG "Using component Device_STM32_LL_LPTIM_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:-DCMSIS_USE_Device_STM32_LL_LPTIM_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:${CMAKE_CURRENT_LIST_DIR}/ll>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:LPUART#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Low-power universal asynchronous receiver transmitter (LPUART) LL driver
  message(DEBUG "Using component Device_STM32_LL_LPUART_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:-DCMSIS_USE_Device_STM32_LL_LPUART_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:${CMAKE_CURRENT_LIST_DIR}/ll>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:OPAMP#Cversion:2.0.1" IN_LIST CMSIS_COMPONENTS_LIST)  # (OPAMP) LL driver
  message(DEBUG "Using component Device_STM32_LL_OPAMP_2_0_1")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:-DCMSIS_USE_Device_STM32_LL_OPAMP_2_0_1=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:${CMAKE_CURRENT_LIST_DIR}/ll>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:PKA#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # PKA LL driver
  message(DEBUG "Using component Device_STM32_LL_PKA_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:-DCMSIS_USE_Device_STM32_LL_PKA_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:${CMAKE_CURRENT_LIST_DIR}/ll>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:PWR#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Power controller (PWR) LL driver
  message(DEBUG "Using component Device_STM32_LL_PWR_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:-DCMSIS_USE_Device_STM32_LL_PWR_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:${CMAKE_CURRENT_LIST_DIR}/ll>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:RAMCFG#Cversion:2.0.1" IN_LIST CMSIS_COMPONENTS_LIST)  # RAM configuration controller (RAMCFG) LL driver
  message(DEBUG "Using component Device_STM32_LL_RAMCFG_2_0_1")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:-DCMSIS_USE_Device_STM32_LL_RAMCFG_2_0_1=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:${CMAKE_CURRENT_LIST_DIR}/ll>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:RCC#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Reset and clock control (RCC) LL driver
  message(DEBUG "Using component Device_STM32_LL_RCC_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:-DCMSIS_USE_Device_STM32_LL_RCC_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:${CMAKE_CURRENT_LIST_DIR}/ll>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:RNG#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Random number generator (RNG) LL driver
  message(DEBUG "Using component Device_STM32_LL_RNG_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:-DCMSIS_USE_Device_STM32_LL_RNG_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:${CMAKE_CURRENT_LIST_DIR}/ll>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:RTC#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Real-time clock (RTC) LL driver
  message(DEBUG "Using component Device_STM32_LL_RTC_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:-DCMSIS_USE_Device_STM32_LL_RTC_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:${CMAKE_CURRENT_LIST_DIR}/ll>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:TAMP#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # (TAMP) LL driver
  message(DEBUG "Using component Device_STM32_LL_TAMP_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:-DCMSIS_USE_Device_STM32_LL_TAMP_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:${CMAKE_CURRENT_LIST_DIR}/ll>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:SPI#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Serial peripheral interface (SPI) LL driver
  message(DEBUG "Using component Device_STM32_LL_SPI_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:-DCMSIS_USE_Device_STM32_LL_SPI_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:${CMAKE_CURRENT_LIST_DIR}/ll>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:SBS#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # System configuration (SBS) LL driver
  message(DEBUG "Using component Device_STM32_LL_SBS_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:-DCMSIS_USE_Device_STM32_LL_SBS_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:${CMAKE_CURRENT_LIST_DIR}/ll>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:SYSTEM#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # System configuration LL driver
  message(DEBUG "Using component Device_STM32_LL_SYSTEM_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:-DCMSIS_USE_Device_STM32_LL_SYSTEM_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:${CMAKE_CURRENT_LIST_DIR}/ll>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:TIM#Cversion:2.1.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Timers (TIM) LL driver
  message(DEBUG "Using component Device_STM32_LL_TIM_2_1_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:-DCMSIS_USE_Device_STM32_LL_TIM_2_1_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:${CMAKE_CURRENT_LIST_DIR}/ll>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:USART#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Universal synchronous asynchronous receiver transmitter (USART) LL driver
  message(DEBUG "Using component Device_STM32_LL_USART_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:-DCMSIS_USE_Device_STM32_LL_USART_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:${CMAKE_CURRENT_LIST_DIR}/ll>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:UTILS#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Utils LL driver
  message(DEBUG "Using component Device_STM32_LL_UTILS_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_STM32C5}:-DCMSIS_USE_Device_STM32_LL_UTILS_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_STM32C5}:${CMAKE_CURRENT_LIST_DIR}/ll>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 LL#Csub:WWDG#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # System window watchdog (WWDG) LL driver
  message(DEBUG "Using component Device_STM32_LL_WWDG_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:-DCMSIS_USE_Device_STM32_LL_WWDG_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_LL}:${CMAKE_CURRENT_LIST_DIR}/ll>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:HAL OS#Cvariant:NO_OS#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # HAL OS port without OS
  message(DEBUG "Using component Device_STM32_HAL_HAL_OS_NO_OS_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_NO_OS}:-DCMSIS_USE_Device_STM32_HAL_HAL_OS_NO_OS_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_NO_OS}:${CMAKE_CURRENT_LIST_DIR}/os_port/no_os>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_NO_OS}:${CMAKE_CURRENT_LIST_DIR}/os_port/no_os/>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_NO_OS}:${CMAKE_CURRENT_LIST_DIR}/os_port/no_os/stm32_hal_os.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:HAL OS#Cvariant:FreeRTOS#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # HAL OS port with MW FreeRTOS
  message(DEBUG "Using component Device_STM32_HAL_HAL_OS_FreeRTOS_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_MW_FreeRTOS}:-DCMSIS_USE_Device_STM32_HAL_HAL_OS_FreeRTOS_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_MW_FreeRTOS}:${CMAKE_CURRENT_LIST_DIR}/os_port/freertos>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_MW_FreeRTOS}:${CMAKE_CURRENT_LIST_DIR}/os_port/freertos/>")
  target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_MW_FreeRTOS}:${CMAKE_CURRENT_LIST_DIR}/os_port/freertos/stm32_hal_os.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32 HAL#Csub:HAL OS#Cvariant:TEMPLATE OS#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # HAL OS port with CMSIS OS
  message(DEBUG "Using component Device_STM32_HAL_HAL_OS_TEMPLATE_OS_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_TEMPLATE_OS}:-DCMSIS_USE_Device_STM32_HAL_HAL_OS_TEMPLATE_OS_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_TEMPLATE_OS}:${CMAKE_CURRENT_LIST_DIR}/templates/os_port>")
  if(EXISTS ${CMSIS_RTE_FOLDER}/Device/stm32_hal_os.c)
    target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_TEMPLATE_OS}:${CMSIS_RTE_FOLDER}/Device/stm32_hal_os.c>")
  else()
    target_sources(STMicroelectronics_stm32c5xx_hal_drivers_2_1_0 INTERFACE "$<${STMicroelectronics.stm32c5xx_hal_drivers.2.1.0_TEMPLATE_OS}:${CMAKE_CURRENT_LIST_DIR}/templates/os_port/stm32_hal_os.c>")
  endif()
endif()

