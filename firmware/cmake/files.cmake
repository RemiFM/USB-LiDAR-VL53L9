# file-format: 1.0.0
if(CMAKE_BUILD_TYPE STREQUAL "debug_GCC_STM32C552KEU6")
  target_sources(${CMAKE_PROJECT_NAME} PRIVATE main.c main.h)
endif()
