# origin-pack: generated_STMicroelectronics::stm32c5xx_hal_drivers@0.0.1
# file-format: 1.0.0
project(generated_STMicroelectronics_stm32c5xx_hal_drivers_0_0_1)
cmake_minimum_required(VERSION 3.20)
add_library(generated_STMicroelectronics_stm32c5xx_hal_drivers_0_0_1 INTERFACE)

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




# Include Pre_Include_Global.h globally if needed
if(CMSIS_Tcompiler STREQUAL "IAR")
    target_compile_options(generated_STMicroelectronics_stm32c5xx_hal_drivers_0_0_1 INTERFACE "SHELL:--preinclude $<QUOTE>${CMAKE_CURRENT_LIST_DIR}/Pre_Include_Global.h$<QUOTE>")
else()
    target_compile_options(generated_STMicroelectronics_stm32c5xx_hal_drivers_0_0_1 INTERFACE "SHELL:-include $<QUOTE>${CMAKE_CURRENT_LIST_DIR}/Pre_Include_Global.h$<QUOTE>")
endif()



# Enable all components in this package
if(CMSIS_ENTIRE_generated_STMicroelectronics_stm32c5xx_hal_drivers_0_0_1)
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32CubeMX2 Config#Csub:CORE#Cversion:2.1.0#generated:true")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32CubeMX2 Config#Csub:CORTEX DEBUG#Cversion:2.1.0#generated:true")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32CubeMX2 Config#Csub:CORTEX MPU#Cversion:2.1.0#generated:true")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32CubeMX2 Config#Csub:CORTEX NVIC#Cversion:2.1.0#generated:true")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32CubeMX2 Config#Csub:GPIO#Cversion:2.1.0#generated:true")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32CubeMX2 Config#Csub:I3C#Cversion:2.1.0#generated:true")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32CubeMX2 Config#Csub:ICACHE#Cversion:2.1.0#generated:true")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32CubeMX2 Config#Csub:RCC#Cversion:2.1.0#generated:true")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32CubeMX2 Config#Csub:SPI#Cversion:2.1.0#generated:true")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32CubeMX2 Config#Csub:System#Cversion:2.1.0#generated:true")
endif()

# All conditions used by this package

# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1
# description: 
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1 "1")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1 enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:CMSIS Core
# description: STMicroelectronics STM32C5 and HAL Common
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_CMSIS_Core "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_CMSIS_Core enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_CMSIS_Core 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL ADC
# description: HAL ADC dependencies
if((((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_ADC "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:ADC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:DBGMCU(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_ADC enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_ADC 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL COMP
# description: HAL COMP dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_COMP "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:COMP(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_COMP enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_COMP 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORDIC
# description: HAL CORDIC dependencies
if((((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORDIC "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:CORDIC(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORDIC enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORDIC 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE
# description: STMicroelectronics STM32C5 and HAL system
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE DMA
# description: STMicroelectronics STM32C5 and HAL with DMA
if((((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_DMA "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_DMA enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_DMA 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE DMA Init
# description: STMicroelectronics HAL CORE and DMA Init dependencies
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_DMA_Init "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_DMA_Init enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_DMA_Init 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE DMA Init and AES
# description: STMicroelectronics HAL AES Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_DMA_Init_and_AES "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:AES(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_DMA_Init_and_AES enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_DMA_Init_and_AES 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE DMA Init and CORDIC
# description: STMicroelectronics HAL CORDIC Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_DMA_Init_and_CORDIC "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:CORDIC(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_DMA_Init_and_CORDIC enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_DMA_Init_and_CORDIC 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE DMA Init and HASH
# description: STMicroelectronics HAL HASH Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_DMA_Init_and_HASH "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:HASH(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_DMA_Init_and_HASH enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_DMA_Init_and_HASH 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE GPIO DMA Init
# description: STMicroelectronics HAL CORE, GPIO and DMA Init dependencies
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:GPIO(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE GPIO DMA Init and ADC
# description: STMicroelectronics HAL ADC Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_ADC "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:GPIO(#.*|$)>,>>>,$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:ADC(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_ADC enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_ADC 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE GPIO DMA Init and DAC
# description: STMicroelectronics HAL DAC Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_DAC "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:GPIO(#.*|$)>,>>>,$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:DAC(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_DAC enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_DAC 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE GPIO DMA Init and I2C
# description: STMicroelectronics HAL I2C Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_I2C "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:GPIO(#.*|$)>,>>>,$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:I2C(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_I2C enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_I2C 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE GPIO DMA Init and I2S
# description: STMicroelectronics HAL I2S Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_I2S "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:GPIO(#.*|$)>,>>>,$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:SPI(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_I2S enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_I2S 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE GPIO DMA Init and I3C
# description: STMicroelectronics HAL I3C Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_I3C "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:GPIO(#.*|$)>,>>>,$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:I3C(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_I3C enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_I3C 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE GPIO DMA Init and LPTIM
# description: STMicroelectronics HAL LPTIM Init dependencies
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_LPTIM "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:GPIO(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:LPTIM(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_LPTIM enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_LPTIM 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE GPIO DMA Init and SMARTCARD
# description: STMicroelectronics HAL SMARTCARD Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_SMARTCARD "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:GPIO(#.*|$)>,>>>,$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:USART(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_SMARTCARD enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_SMARTCARD 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE GPIO DMA Init and SPI
# description: STMicroelectronics HAL SPI Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_SPI "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:GPIO(#.*|$)>,>>>,$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:SPI(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_SPI enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_SPI 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE GPIO DMA Init and TIM
# description: STMicroelectronics HAL TIM Init dependencies
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_TIM "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:GPIO(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:TIM(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_TIM enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_TIM 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE GPIO DMA Init and UART
# description: STMicroelectronics HAL UART Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_UART "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:GPIO(#.*|$)>,>>>,$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:USART(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_UART enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_UART 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE GPIO DMA Init and USART
# description: STMicroelectronics HAL USART Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_USART "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:GPIO(#.*|$)>,>>>,$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:USART(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_USART enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_USART 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE GPIO DMA Init and XSPI
# description: STMicroelectronics HAL SPI Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_XSPI "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:GPIO(#.*|$)>,>>>,$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:XSPI(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_XSPI enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_XSPI 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE GPIO Init and COMP
# description: STMicroelectronics HAL COMP Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND ((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_Init_and_COMP "$<AND:$<AND:$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:GPIO(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:SBS(#.*|$)>,>>>,$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:COMP(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_Init_and_COMP enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_Init_and_COMP 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE GPIO Init and ETH
# description: STMicroelectronics HAL ETH Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_Init_and_ETH "$<AND:$<AND:$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:GPIO(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:SBS(#.*|$)>,>>>,$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:ETH(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_Init_and_ETH enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_Init_and_ETH 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE GPIO Init and FDCAN
# description: STMicroelectronics HAL FDCAN Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_Init_and_FDCAN "$<AND:$<AND:$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:GPIO(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:SBS(#.*|$)>,>>>,$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:FDCAN(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_Init_and_FDCAN enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_Init_and_FDCAN 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE GPIO Init and HCD
# description: STMicroelectronics HAL HCD Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_Init_and_HCD "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<AND:$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:GPIO(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:SBS(#.*|$)>,>>>,$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:HCD(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_Init_and_HCD enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_Init_and_HCD 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE GPIO Init and OPAMP
# description: STMicroelectronics HAL OPAMP Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_Init_and_OPAMP "$<AND:$<AND:$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:GPIO(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:SBS(#.*|$)>,>>>,$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:OPAMP(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_Init_and_OPAMP enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_Init_and_OPAMP 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE GPIO Init and PCD
# description: STMicroelectronics HAL PCD Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_Init_and_PCD "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<AND:$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:GPIO(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:SBS(#.*|$)>,>>>,$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:PCD(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_Init_and_PCD enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_Init_and_PCD 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE GPIO Init and PWR
# description: STMicroelectronics HAL PWR Init
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_Init_and_PWR "$<AND:$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_Init_and_PWR enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_Init_and_PWR 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE GPIO Init and RTC
# description: STMicroelectronics HAL RTC Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_Init_and_RTC "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<AND:$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:GPIO(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:SBS(#.*|$)>,>>>,$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:RTC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_Init_and_RTC enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_Init_and_RTC 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE GPIO Init and SMBUS
# description: STMicroelectronics HAL SMBUS Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_Init_and_SMBUS "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<AND:$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:GPIO(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:SBS(#.*|$)>,>>>,$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:I2C(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_Init_and_SMBUS enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_Init_and_SMBUS 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE GPIO Init and TAMP
# description: STMicroelectronics HAL TAMP Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_Init_and_TAMP "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<AND:$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:GPIO(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:SBS(#.*|$)>,>>>,$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:TAMP(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_Init_and_TAMP enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_Init_and_TAMP 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE Init GPIO and CORTEX
# description: STMicroelectronics HAL CORTEX Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_GPIO_and_CORTEX "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<AND:$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:GPIO(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:SBS(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_GPIO_and_CORTEX enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_GPIO_and_CORTEX 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE Init GPIO and CRS
# description: STMicroelectronics HAL CRS Init dependencies
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_GPIO_and_CRS "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:CRS(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_GPIO_and_CRS enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_GPIO_and_CRS 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE Init GPIO and RCC
# description: STMicroelectronics HAL Common Init
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_GPIO_and_RCC "$<AND:$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<AND:$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:GPIO(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:SBS(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:FLASH_ITF(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_GPIO_and_RCC enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_GPIO_and_RCC 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE Init and CCB
# description: STMicroelectronics HAL CCB Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_CCB "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CCB(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_CCB enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_CCB 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE Init and CORTEX
# description: STMicroelectronics HAL CORTEX Init dependencies
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_CORTEX "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_CORTEX enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_CORTEX 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE Init and CRC
# description: STMicroelectronics HAL CRC Init dependencies
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_CRC "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:CRC(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_CRC enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_CRC 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE Init and FLASH
# description: STMicroelectronics HAL FLASH Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_FLASH "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:FLASH(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_FLASH enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_FLASH 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE Init and ICACHE
# description: STMicroelectronics HAL ICACHE Init dependencies
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_ICACHE "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:ICACHE(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_ICACHE enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_ICACHE 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE Init and IWDG
# description: STMicroelectronics HAL IWDG Init dependencies
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_IWDG "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:IWDG(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_IWDG enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_IWDG 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE Init and PKA
# description: STMicroelectronics HAL PKA Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_PKA "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PKA(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_PKA enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_PKA 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE Init and RAMCFG
# description: STMicroelectronics HAL RAMCFG Init dependencies
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_RAMCFG "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:RAMCFG(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_RAMCFG enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_RAMCFG 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE Init and RNG
# description: STMicroelectronics HAL RNG Init dependencies
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_RNG "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:RNG(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_RNG enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_RNG 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE Init and SBS
# description: STMicroelectronics HAL SBS Init dependencies
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_SBS "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:SBS(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_SBS enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_SBS 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE Init and WWDG
# description: STMicroelectronics HAL WWDG Init dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_WWDG "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:WWDG(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_WWDG enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_WWDG 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE USB
# description: HAL CORE USB dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_USB "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL DRIVERS CORE#.*Csub:USB DRD(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL DRIVERS CORE#.*Csub:USB CORE DEF(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_USB enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_USB 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORE XSPI
# description: HAL CORE XSPI dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_XSPI "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL DRIVERS CORE#.*Csub:DLYB(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_XSPI enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_XSPI 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CORTEX
# description: HAL CORTEX dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORTEX "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORTEX enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORTEX 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CRC
# description: HAL CRC dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CRC "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:CRC(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CRC enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CRC 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL CRS
# description: HAL CRS dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CRS "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:CRS(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CRS enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CRS 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL Common
# description: STMicroelectronics STM32C5 and HAL common
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_Common "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_Common enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_Common 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL DAC
# description: HAL DAC dependencies
if((((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_DAC "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:DAC(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_DAC enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_DAC 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL DBGMCU
# description: HAL DBGMCU dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_DBGMCU "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:DBGMCU(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_DBGMCU enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_DBGMCU 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL DMA
# description: HAL DMA dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_DMA "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:DMA(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Q(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_DMA enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_DMA 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL EXTI
# description: HAL EXTI dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_EXTI "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_EXTI enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_EXTI 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL FLASH
# description: HAL FLASH dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_FLASH "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:FLASH_ITF(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_FLASH enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_FLASH 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL FLASH_ITF
# description: HAL FLASH_ITF dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_FLASH_ITF "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:FLASH(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_FLASH_ITF enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_FLASH_ITF 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL GPIO
# description: HAL GPIO dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_GPIO "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:GPIO(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_GPIO enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_GPIO 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL GPIO Init
# description: STMicroelectronics HAL Common Init
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_GPIO_Init "$<AND:$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:GPIO(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:SBS(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_GPIO_Init enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_GPIO_Init 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL Generated code
# description: STMicroelectronics HAL components used for code Generation
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_Generated_code "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_Generated_code enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_Generated_code 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL I2C
# description: HAL I2C dependencies
if((((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_I2C "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:I2C(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_I2C enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_I2C 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL I2S
# description: HAL I2S dependencies
if((((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_I2S "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:SPI(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_I2S enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_I2S 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL I3C
# description: HAL I3C dependencies
if((((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_I3C "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:I3C(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_I3C enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_I3C 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL ICACHE
# description: HAL ICACHE dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_ICACHE "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:ICACHE(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_ICACHE enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_ICACHE 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL IWDG
# description: HAL IWDG dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_IWDG "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:IWDG(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_IWDG enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_IWDG 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL LPTIM
# description: HAL LPTIM dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_LPTIM "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:LPTIM(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_LPTIM enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_LPTIM 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL OPAMP
# description: HAL OPAMP dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_OPAMP "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:OPAMP(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_OPAMP enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_OPAMP 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL PKA
# description: HAL PKA dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_PKA "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PKA(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_PKA enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_PKA 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL PWR
# description: HAL PWR dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_PWR "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_PWR enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_PWR 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL RAMCFG
# description: HAL RAMCFG dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_RAMCFG "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:RAMCFG(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_RAMCFG enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_RAMCFG 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL RCC
# description: HAL RCC dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_RCC "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:BUS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_RCC enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_RCC 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL RNG
# description: HAL RNG dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_RNG "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:RNG(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_RNG enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_RNG 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL RTC
# description: HAL RTC dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_RTC "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:RTC(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_RTC enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_RTC 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL SBS
# description: HAL SBS dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_SBS "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:SBS(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_SBS enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_SBS 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL SMARTCARD
# description: HAL SMARTCARD dependencies
if((((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_SMARTCARD "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:USART(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_SMARTCARD enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_SMARTCARD 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL SMBUS
# description: HAL SMBUS dependencies
if((((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_SMBUS "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:I2C(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_SMBUS enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_SMBUS 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL SPI
# description: HAL SPI dependencies
if((((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_SPI "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:SPI(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_SPI enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_SPI 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL System Init
# description: STMicroelectronics HAL Common Init
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_System_Init "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:UTILS(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32CubeMX2 Codegen#.*Csub:Generated Code(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:timebases#.*Cvariant:SYSTICK(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_System_Init enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_System_Init 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL TAMP
# description: HAL TAMP dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_TAMP "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:TAMP(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_TAMP enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_TAMP 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL TIM
# description: HAL TIM dependencies
if((((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_TIM "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:TIM(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:SBS(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_TIM enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_TIM 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL UART
# description: HAL UART dependencies
if((((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_UART "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:USART(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_UART enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_UART 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL USART
# description: HAL USART dependencies
if((((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_USART "$<AND:$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:USART(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_USART enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_USART 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:HAL WWDG
# description: HAL WWDG dependencies
if(((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_WWDG "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:WWDG(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_WWDG enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_WWDG 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:LL
# description: STMicroelectronics STM32C5 and LL
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_LL "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:Common(#.*|$)>,>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_LL enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_LL 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:MW FreeRTOS
# description: MW FreeRTOS used for HAL OS
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_MW_FreeRTOS "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:template(#.*|$)>,>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_MW_FreeRTOS enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_MW_FreeRTOS 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:NO OS
# description: NO MW used for HAL OS
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_NO_OS "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:template(#.*|$)>,>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_NO_OS enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_NO_OS 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:STM32C5
# description: STMicroelectronics STM32C5
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_STM32C5 "1")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_STM32C5 enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_STM32C5 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:System files
# description: System files for codegen
set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_System_files "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:CORTEX(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:EXTI(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 LL#.*Csub:PWR(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RCC(#.*|$)>,>>>")
message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_System_files enabled")


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:TEMPLATE OS
# description: TEMPLATE OS used for HAL OS
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_TEMPLATE_OS "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:template(#.*|$)>,>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_TEMPLATE_OS enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_TEMPLATE_OS 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:Timebase HAL RTC ALARM or WKUP
# description: HAL timebase based on RTC ALARM or WAKEUP
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_Timebase_HAL_RTC_ALARM_or_WKUP "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RTC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:RTC timebase template(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_Timebase_HAL_RTC_ALARM_or_WKUP enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_Timebase_HAL_RTC_ALARM_or_WKUP 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:Timebase HAL TIM
# description: HAL timebase based on TIM
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_Timebase_HAL_TIM "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:TIM(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:TIM timebase template(#.*|$)>,>>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_Timebase_HAL_TIM enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_Timebase_HAL_TIM 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:Timebase NONE
# description: HAL timebase NONE
if((CMSIS_Dname MATCHES "STM32C5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_Timebase_NONE "1")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_Timebase_NONE enabled")
else()
  set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_Timebase_NONE 0)
endif()


# condition: generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1:Use mutex
# description: STMicroelectronics HAL condition to check if USE_HAL_MUTEX is enabled
set(generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_Use_mutex "1")
message(DEBUG "CMSIS condition generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_Use_mutex enabled")

# Files and components in this package
if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32CubeMX2 Config#Csub:CORE#Cversion:2.1.0#generated:true" IN_LIST CMSIS_COMPONENTS_LIST)  # TO BE DEFINED
  message(DEBUG "Using component generated_Device_STM32CubeMX2_Config_CORE_2_1_0")
  target_compile_definitions(generated_STMicroelectronics_stm32c5xx_hal_drivers_0_0_1 INTERFACE "$<${generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_Generated_code}:-DCMSIS_USE_generated_Device_STM32CubeMX2_Config_CORE_2_1_0=1>")
  target_include_directories(generated_STMicroelectronics_stm32c5xx_hal_drivers_0_0_1 INTERFACE "$<${generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_Generated_code}:${CMAKE_CURRENT_LIST_DIR}/.>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32CubeMX2 Config#Csub:CORTEX DEBUG#Cversion:2.1.0#generated:true" IN_LIST CMSIS_COMPONENTS_LIST)  # TO BE DEFINED
  message(DEBUG "Using component generated_Device_STM32CubeMX2_Config_CORTEX_DEBUG_2_1_0")
  target_compile_definitions(generated_STMicroelectronics_stm32c5xx_hal_drivers_0_0_1 INTERFACE "$<${generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_GPIO_and_CORTEX}:-DCMSIS_USE_generated_Device_STM32CubeMX2_Config_CORTEX_DEBUG_2_1_0=1>")
  target_include_directories(generated_STMicroelectronics_stm32c5xx_hal_drivers_0_0_1 INTERFACE "$<${generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_GPIO_and_CORTEX}:${CMAKE_CURRENT_LIST_DIR}/.>")
  target_sources(generated_STMicroelectronics_stm32c5xx_hal_drivers_0_0_1 INTERFACE "$<${generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_GPIO_and_CORTEX}:${CMAKE_CURRENT_LIST_DIR}/mx_cortex_debug.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32CubeMX2 Config#Csub:CORTEX MPU#Cversion:2.1.0#generated:true" IN_LIST CMSIS_COMPONENTS_LIST)  # TO BE DEFINED
  message(DEBUG "Using component generated_Device_STM32CubeMX2_Config_CORTEX_MPU_2_1_0")
  target_compile_definitions(generated_STMicroelectronics_stm32c5xx_hal_drivers_0_0_1 INTERFACE "$<${generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_CORTEX}:-DCMSIS_USE_generated_Device_STM32CubeMX2_Config_CORTEX_MPU_2_1_0=1>")
  target_include_directories(generated_STMicroelectronics_stm32c5xx_hal_drivers_0_0_1 INTERFACE "$<${generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_CORTEX}:${CMAKE_CURRENT_LIST_DIR}/.>")
  target_sources(generated_STMicroelectronics_stm32c5xx_hal_drivers_0_0_1 INTERFACE "$<${generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_CORTEX}:${CMAKE_CURRENT_LIST_DIR}/mx_cortex_mpu.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32CubeMX2 Config#Csub:CORTEX NVIC#Cversion:2.1.0#generated:true" IN_LIST CMSIS_COMPONENTS_LIST)  # TO BE DEFINED
  message(DEBUG "Using component generated_Device_STM32CubeMX2_Config_CORTEX_NVIC_2_1_0")
  target_compile_definitions(generated_STMicroelectronics_stm32c5xx_hal_drivers_0_0_1 INTERFACE "$<${generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_CORTEX}:-DCMSIS_USE_generated_Device_STM32CubeMX2_Config_CORTEX_NVIC_2_1_0=1>")
  target_include_directories(generated_STMicroelectronics_stm32c5xx_hal_drivers_0_0_1 INTERFACE "$<${generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_CORTEX}:${CMAKE_CURRENT_LIST_DIR}/.>")
  target_sources(generated_STMicroelectronics_stm32c5xx_hal_drivers_0_0_1 INTERFACE "$<${generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_CORTEX}:${CMAKE_CURRENT_LIST_DIR}/mx_cortex_nvic.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32CubeMX2 Config#Csub:GPIO#Cversion:2.1.0#generated:true" IN_LIST CMSIS_COMPONENTS_LIST)  # TO BE DEFINED
  message(DEBUG "Using component generated_Device_STM32CubeMX2_Config_GPIO_2_1_0")
  target_compile_definitions(generated_STMicroelectronics_stm32c5xx_hal_drivers_0_0_1 INTERFACE "$<${generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_GPIO_Init}:-DCMSIS_USE_generated_Device_STM32CubeMX2_Config_GPIO_2_1_0=1>")
  target_include_directories(generated_STMicroelectronics_stm32c5xx_hal_drivers_0_0_1 INTERFACE "$<${generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_GPIO_Init}:${CMAKE_CURRENT_LIST_DIR}/.>")
  target_sources(generated_STMicroelectronics_stm32c5xx_hal_drivers_0_0_1 INTERFACE "$<${generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_GPIO_Init}:${CMAKE_CURRENT_LIST_DIR}/mx_gpio_default.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32CubeMX2 Config#Csub:I3C#Cversion:2.1.0#generated:true" IN_LIST CMSIS_COMPONENTS_LIST)  # TO BE DEFINED
  message(DEBUG "Using component generated_Device_STM32CubeMX2_Config_I3C_2_1_0")
  target_compile_definitions(generated_STMicroelectronics_stm32c5xx_hal_drivers_0_0_1 INTERFACE "$<${generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_I3C}:-DCMSIS_USE_generated_Device_STM32CubeMX2_Config_I3C_2_1_0=1>")
  target_include_directories(generated_STMicroelectronics_stm32c5xx_hal_drivers_0_0_1 INTERFACE "$<${generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_I3C}:${CMAKE_CURRENT_LIST_DIR}/.>")
  target_sources(generated_STMicroelectronics_stm32c5xx_hal_drivers_0_0_1 INTERFACE "$<${generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_I3C}:${CMAKE_CURRENT_LIST_DIR}/mx_i3c1.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32CubeMX2 Config#Csub:ICACHE#Cversion:2.1.0#generated:true" IN_LIST CMSIS_COMPONENTS_LIST)  # TO BE DEFINED
  message(DEBUG "Using component generated_Device_STM32CubeMX2_Config_ICACHE_2_1_0")
  target_compile_definitions(generated_STMicroelectronics_stm32c5xx_hal_drivers_0_0_1 INTERFACE "$<${generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_ICACHE}:-DCMSIS_USE_generated_Device_STM32CubeMX2_Config_ICACHE_2_1_0=1>")
  target_include_directories(generated_STMicroelectronics_stm32c5xx_hal_drivers_0_0_1 INTERFACE "$<${generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_ICACHE}:${CMAKE_CURRENT_LIST_DIR}/.>")
  target_sources(generated_STMicroelectronics_stm32c5xx_hal_drivers_0_0_1 INTERFACE "$<${generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_and_ICACHE}:${CMAKE_CURRENT_LIST_DIR}/mx_icache.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32CubeMX2 Config#Csub:RCC#Cversion:2.1.0#generated:true" IN_LIST CMSIS_COMPONENTS_LIST)  # TO BE DEFINED
  message(DEBUG "Using component generated_Device_STM32CubeMX2_Config_RCC_2_1_0")
  target_compile_definitions(generated_STMicroelectronics_stm32c5xx_hal_drivers_0_0_1 INTERFACE "$<${generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_GPIO_and_RCC}:-DCMSIS_USE_generated_Device_STM32CubeMX2_Config_RCC_2_1_0=1>")
  target_include_directories(generated_STMicroelectronics_stm32c5xx_hal_drivers_0_0_1 INTERFACE "$<${generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_GPIO_and_RCC}:${CMAKE_CURRENT_LIST_DIR}/.>")
  target_sources(generated_STMicroelectronics_stm32c5xx_hal_drivers_0_0_1 INTERFACE "$<${generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_Init_GPIO_and_RCC}:${CMAKE_CURRENT_LIST_DIR}/mx_rcc.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32CubeMX2 Config#Csub:SPI#Cversion:2.1.0#generated:true" IN_LIST CMSIS_COMPONENTS_LIST)  # TO BE DEFINED
  message(DEBUG "Using component generated_Device_STM32CubeMX2_Config_SPI_2_1_0")
  target_compile_definitions(generated_STMicroelectronics_stm32c5xx_hal_drivers_0_0_1 INTERFACE "$<${generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_SPI}:-DCMSIS_USE_generated_Device_STM32CubeMX2_Config_SPI_2_1_0=1>")
  target_include_directories(generated_STMicroelectronics_stm32c5xx_hal_drivers_0_0_1 INTERFACE "$<${generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_SPI}:${CMAKE_CURRENT_LIST_DIR}/.>")
  target_sources(generated_STMicroelectronics_stm32c5xx_hal_drivers_0_0_1 INTERFACE "$<${generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_CORE_GPIO_DMA_Init_and_SPI}:${CMAKE_CURRENT_LIST_DIR}/mx_spi1.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:STM32CubeMX2 Config#Csub:System#Cversion:2.1.0#generated:true" IN_LIST CMSIS_COMPONENTS_LIST)  # TO BE DEFINED
  message(DEBUG "Using component generated_Device_STM32CubeMX2_Config_System_2_1_0")
  target_compile_definitions(generated_STMicroelectronics_stm32c5xx_hal_drivers_0_0_1 INTERFACE "$<${generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_System_Init}:-DCMSIS_USE_generated_Device_STM32CubeMX2_Config_System_2_1_0=1>")
  target_include_directories(generated_STMicroelectronics_stm32c5xx_hal_drivers_0_0_1 INTERFACE "$<${generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_System_Init}:${CMAKE_CURRENT_LIST_DIR}/.>")
  target_sources(generated_STMicroelectronics_stm32c5xx_hal_drivers_0_0_1 INTERFACE "$<${generated_STMicroelectronics.stm32c5xx_hal_drivers.0.0.1_HAL_System_Init}:${CMAKE_CURRENT_LIST_DIR}/mx_system.c>")
endif()

