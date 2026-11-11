# origin-pack: generated_STMicroelectronics::syscalls@2.0.0
# file-format: 1.0.0
project(generated_STMicroelectronics_syscalls_2_0_0)
cmake_minimum_required(VERSION 3.20)
add_library(generated_STMicroelectronics_syscalls_2_0_0 INTERFACE)

# List of all CMSIS properties that influence conditions for this package
if(NOT DEFINED CMSIS_Dname)
  set(CMSIS_Dname "CMSIS_Dname not set")
  message(DEBUG "CMSIS_Dname is not set to any value")
endif()

if(NOT DEFINED CMSIS_Dvendor)
  set(CMSIS_Dvendor "CMSIS_Dvendor not set")
  message(DEBUG "CMSIS_Dvendor is not set to any value")
endif()

if(NOT DEFINED CMSIS_Tcompiler)
  set(CMSIS_Tcompiler "CMSIS_Tcompiler not set")
  message(DEBUG "CMSIS_Tcompiler is not set to any value")
endif()


# Device specific defined symbols








# Enable all components in this package
if(CMSIS_ENTIRE_generated_STMicroelectronics_syscalls_2_0_0)
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Utility#Cgroup:STM32CubeMX2 Config#Csub:syscalls#Cversion:1.0.0#generated:true")
endif()

# All conditions used by this package

# condition: generated_STMicroelectronics.syscalls.2.0.0
# description: 
if((CMSIS_Dname MATCHES "STM32.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(generated_STMicroelectronics.syscalls.2.0.0 "1")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.syscalls.2.0.0 enabled")
else()
  set(generated_STMicroelectronics.syscalls.2.0.0 0)
endif()


# condition: generated_STMicroelectronics.syscalls.2.0.0:GCC
# description: newlib, usually linked by GCC compilers
if(CMSIS_Tcompiler STREQUAL "GCC")
  set(generated_STMicroelectronics.syscalls.2.0.0_GCC "1")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.syscalls.2.0.0_GCC enabled")
else()
  set(generated_STMicroelectronics.syscalls.2.0.0_GCC 0)
endif()


# condition: generated_STMicroelectronics.syscalls.2.0.0:GCC + linker scripts
# description: STMicroelectronics' default linker scripts + newlib
if(CMSIS_Tcompiler STREQUAL "GCC")
  set(generated_STMicroelectronics.syscalls.2.0.0_GCC___linker_scripts "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:Startup(#.*|$)>,>>")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.syscalls.2.0.0_GCC___linker_scripts enabled")
else()
  set(generated_STMicroelectronics.syscalls.2.0.0_GCC___linker_scripts 0)
endif()


# condition: generated_STMicroelectronics.syscalls.2.0.0:Syscalls Config
# description: selection of Syscalls and sysmem usage pattern is required to use the component
set(generated_STMicroelectronics.syscalls.2.0.0_Syscalls_Config "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Utility#.*Cgroup:syscalls#.*Cvariant:Standalone syscalls(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Utility#.*Cgroup:sysmem#.*Cvariant:Standalone sysmem(#.*|$)>,>>>")
message(DEBUG "CMSIS condition generated_STMicroelectronics.syscalls.2.0.0_Syscalls_Config enabled")

# Files and components in this package
if("Cvendor:STMicroelectronics#Cclass:Utility#Cgroup:STM32CubeMX2 Config#Csub:syscalls#Cversion:1.0.0#generated:true" IN_LIST CMSIS_COMPONENTS_LIST)  # TO BE DEFINED
  message(DEBUG "Using component generated_Utility_STM32CubeMX2_Config_syscalls_1_0_0")
  target_compile_definitions(generated_STMicroelectronics_syscalls_2_0_0 INTERFACE "$<${generated_STMicroelectronics.syscalls.2.0.0_Syscalls_Config}:-DCMSIS_USE_generated_Utility_STM32CubeMX2_Config_syscalls_1_0_0=1>")
endif()

