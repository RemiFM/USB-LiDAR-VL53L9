# file-format: 1.0.0
cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_C_COMPILER_FORCED TRUE)
set(CMAKE_CXX_COMPILER_FORCED TRUE)

include(cmake/target.cmake)
include(cmake/${TOOLCHAIN_FILE})

project(USB-LiDAR-VL53L9-STM32C552KEU6)
add_executable(USB-LiDAR-VL53L9-STM32C552KEU6)
include(cmake/files.cmake)
include(cmake/flags.cmake)
include(cmake/components.cmake)

# Re-apply the I3C fixes to ST's HAL copy (CubeMX2 may replace it); see the script.
include(vendor/patches/apply_hal_patches.cmake)

# Stubs to be able to add compiler flag overrides, e.g. -Os
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
  # Add additional source files here
  app/app.c
  app/usb_app.c
  app/usb_descriptors.c
  app/proto_tx.c
  app/crc32.c
  app/timebase.c
  # TinyUSB: core, device stack, CDC class, STM32 FSDEV port
  vendor/tinyusb/tusb.c
  vendor/tinyusb/common/tusb_fifo.c
  vendor/tinyusb/device/usbd.c
  vendor/tinyusb/class/cdc/cdc_device.c
  vendor/tinyusb/portable/st/stm32_fsdev/dcd_stm32_fsdev.c
  vendor/tinyusb/portable/st/stm32_fsdev/fsdev_common.c
  # IMU: detection layer + one backend per supported part
  app/imu.c
  app/imu_lsm6dsv.c
  app/imu_lsm6dsv16x.c
  app/imu_lsm6dsv16bx.c
  # ST IMU drivers (git submodules, pinned to release tags)
  vendor/lsm6dsv/lsm6dsv_reg.c
  vendor/lsm6dsv16x/lsm6dsv16x_reg.c
  vendor/lsm6dsv16bx/lsm6dsv16bx_reg.c
  # LiDAR: sensor control, I3C/I2C transport, ST driver platform layer
  app/lidar.c
  app/lidar_bus.c
  app/soft_i2c.c
  app/vl53l9_platform.c
  # ST VL53L9 driver (vendored: not available as a git repository)
  vendor/vl53l9/vl53l9.c
  # ST I3C timing calculator (part of the HAL package, not added by CubeMX2)
  stm32c5xx_drivers/utils/i3c_timing/stm32_utils_i3c.c
)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
  # Add additional include directories here
  app
  vendor/tinyusb
  vendor/lsm6dsv
  vendor/lsm6dsv16x
  vendor/lsm6dsv16bx
  vendor/vl53l9
  stm32c5xx_drivers/utils/i3c_timing
)

# The ST IMU drivers are git submodules: fail early with a clear message if missing.
foreach(imu_drv lsm6dsv lsm6dsv16x lsm6dsv16bx)
  if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/vendor/${imu_drv}/${imu_drv}_reg.c)
    message(FATAL_ERROR "vendor/${imu_drv} is empty. Run: git submodule update --init")
  endif()
endforeach()

# LSM6DSV and LSM6DSV16X both report WHO_AM_I 0x70 and cannot be told apart at
# runtime. Pick which ST driver handles 0x70 (LSM6DSV16BX, 0x71, is always detected).
option(IMU_ID70_IS_LSM6DSV16X "Use the LSM6DSV16X driver for WHO_AM_I 0x70 (default: LSM6DSV)" OFF)

target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC
  # Add additional defined symbols here
  $<$<BOOL:${IMU_ID70_IS_LSM6DSV16X}>:IMU_ID70_IS_LSM6DSV16X=1>
)

target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC
  # Add additional compiler flags here
)

# The CRC runs over every transmitted byte (~520 kB/s with LiDAR): optimize it
# even in debug builds.
set_source_files_properties(app/crc32.c PROPERTIES COMPILE_OPTIONS "-O2")

target_link_options(${CMAKE_PROJECT_NAME} PUBLIC
  # Add additional linker flags here
)

# Relink when the linker script changes (e.g. STACK_SIZE); Ninja doesn't track it otherwise.
set_property(TARGET ${CMAKE_PROJECT_NAME} APPEND PROPERTY LINK_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/user_modifiable/Device/STM32C552KEU6/stm32c552xe_flash.ld)

target_link_directories(${CMAKE_PROJECT_NAME} PUBLIC
  # Add additional linker search directories here
)

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC
  # Add additional linker libraries here
)
