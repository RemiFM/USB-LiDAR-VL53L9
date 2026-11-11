# file-format: 1.0.0
if(CMAKE_BUILD_TYPE STREQUAL "debug_GCC_STM32C552KEU6")
  set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES SUFFIX ".elf")
  target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC ${CPU_FLAGS})
  target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC "SHELL:-g3 -O0 -fdata-sections -ffunction-sections -std=gnu11 -Wall -fstack-usage --specs=nano.specs --specs=nosys.specs -Werror=implicit-function-declaration ${CC_SECURE}")
  target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC  arch/cmsis/CMSIS/Core/Include generated/hal stm32c5xx_dfp/Include stm32c5xx_drivers/hal stm32c5xx_drivers/ll stm32c5xx_drivers/timebases user_modifiable/_debug_GCC_STM32C552KEU6)
  target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC STM32C552xx _RTE_)
  target_link_options(${CMAKE_PROJECT_NAME} PUBLIC -Wl,-Map=././USB-LiDAR-VL53L9-STM32C552KEU6.map -Wl,--gc-sections -Wl,--start-group -lc -lm -Wl,--end-group -static --specs=nano.specs --specs=nosys.specs ${CC_SECURE})
  target_link_options(${CMAKE_PROJECT_NAME} PUBLIC ${CPU_FLAGS})
endif()

# Clean .map and .elf file
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_CLEAN_FILES "${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/${CMAKE_PROJECT_NAME}.map")
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_CLEAN_FILES "${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/${CMAKE_PROJECT_NAME}.elf")