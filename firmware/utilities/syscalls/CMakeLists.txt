# origin-pack: STMicroelectronics::syscalls@2.0.2
# file-format: 1.0.0
project(STMicroelectronics_syscalls_2_0_2)
cmake_minimum_required(VERSION 3.20)
add_library(STMicroelectronics_syscalls_2_0_2 INTERFACE)

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
if(CMSIS_ENTIRE_STMicroelectronics_syscalls_2_0_2)
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Utility#Cgroup:syscalls#Cvariant:Template syscalls#Cversion:1.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Utility#Cgroup:syscalls#Cvariant:Standalone syscalls#Cversion:1.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Utility#Cgroup:sysmem#Cvariant:Standalone sysmem#Cversion:1.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Utility#Cgroup:sysmem#Cvariant:Template sysmem#Cversion:1.0.0")
endif()

# All conditions used by this package

# condition: STMicroelectronics.syscalls.2.0.2
# description: 
if((CMSIS_Dname MATCHES "STM32.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.syscalls.2.0.2 "1")
  message(DEBUG "CMSIS condition STMicroelectronics.syscalls.2.0.2 enabled")
else()
  set(STMicroelectronics.syscalls.2.0.2 0)
endif()


# condition: STMicroelectronics.syscalls.2.0.2:GCC
# description: newlib, usually linked by GCC compilers
if(CMSIS_Tcompiler STREQUAL "GCC")
  set(STMicroelectronics.syscalls.2.0.2_GCC "1")
  message(DEBUG "CMSIS condition STMicroelectronics.syscalls.2.0.2_GCC enabled")
else()
  set(STMicroelectronics.syscalls.2.0.2_GCC 0)
endif()


# condition: STMicroelectronics.syscalls.2.0.2:GCC + linker scripts
# description: STMicroelectronics' default linker scripts + newlib
if(CMSIS_Tcompiler STREQUAL "GCC")
  set(STMicroelectronics.syscalls.2.0.2_GCC___linker_scripts "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:Startup(#.*|$)>,>>")
  message(DEBUG "CMSIS condition STMicroelectronics.syscalls.2.0.2_GCC___linker_scripts enabled")
else()
  set(STMicroelectronics.syscalls.2.0.2_GCC___linker_scripts 0)
endif()


# condition: STMicroelectronics.syscalls.2.0.2:Syscalls Config
# description: STMicroelectronics Utility Syscalls Config
set(STMicroelectronics.syscalls.2.0.2_Syscalls_Config "1")
message(DEBUG "CMSIS condition STMicroelectronics.syscalls.2.0.2_Syscalls_Config enabled")

# Files and components in this package
if("Cvendor:STMicroelectronics#Cclass:Utility#Cgroup:syscalls#Cvariant:Template syscalls#Cversion:1.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # newlib syscalls stubs: minimal dummy implementation.
  message(DEBUG "Using component Utility_syscalls_Template_syscalls_1_0_0")
  target_compile_definitions(STMicroelectronics_syscalls_2_0_2 INTERFACE "-DCMSIS_USE_Utility_syscalls_Template_syscalls_1_0_0=1")
  if(EXISTS ${CMSIS_RTE_FOLDER}/Utility/syscalls.c)
    target_sources(STMicroelectronics_syscalls_2_0_2 INTERFACE "$<${STMicroelectronics.syscalls.2.0.2_GCC}:${CMSIS_RTE_FOLDER}/Utility/syscalls.c>")
  else()
    target_sources(STMicroelectronics_syscalls_2_0_2 INTERFACE "$<${STMicroelectronics.syscalls.2.0.2_GCC}:${CMAKE_CURRENT_LIST_DIR}/syscalls.c>")
  endif()
endif()

if("Cvendor:STMicroelectronics#Cclass:Utility#Cgroup:syscalls#Cvariant:Standalone syscalls#Cversion:1.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # newlib syscalls stubs: minimal dummy implementation.
  message(DEBUG "Using component Utility_syscalls_Standalone_syscalls_1_0_0")
  target_compile_definitions(STMicroelectronics_syscalls_2_0_2 INTERFACE "-DCMSIS_USE_Utility_syscalls_Standalone_syscalls_1_0_0=1")
  target_sources(STMicroelectronics_syscalls_2_0_2 INTERFACE "$<${STMicroelectronics.syscalls.2.0.2_GCC}:${CMAKE_CURRENT_LIST_DIR}/syscalls.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Utility#Cgroup:sysmem#Cvariant:Standalone sysmem#Cversion:1.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Simple memory pool management for newlib malloc.
  message(DEBUG "Using component Utility_sysmem_Standalone_sysmem_1_0_0")
  target_compile_definitions(STMicroelectronics_syscalls_2_0_2 INTERFACE "-DCMSIS_USE_Utility_sysmem_Standalone_sysmem_1_0_0=1")
  target_sources(STMicroelectronics_syscalls_2_0_2 INTERFACE "$<${STMicroelectronics.syscalls.2.0.2_GCC___linker_scripts}:${CMAKE_CURRENT_LIST_DIR}/sysmem.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Utility#Cgroup:sysmem#Cvariant:Template sysmem#Cversion:1.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Simple memory pool management for newlib malloc.
  message(DEBUG "Using component Utility_sysmem_Template_sysmem_1_0_0")
  target_compile_definitions(STMicroelectronics_syscalls_2_0_2 INTERFACE "-DCMSIS_USE_Utility_sysmem_Template_sysmem_1_0_0=1")
  if(EXISTS ${CMSIS_RTE_FOLDER}/Utility/sysmem.c)
    target_sources(STMicroelectronics_syscalls_2_0_2 INTERFACE "$<${STMicroelectronics.syscalls.2.0.2_GCC___linker_scripts}:${CMSIS_RTE_FOLDER}/Utility/sysmem.c>")
  else()
    target_sources(STMicroelectronics_syscalls_2_0_2 INTERFACE "$<${STMicroelectronics.syscalls.2.0.2_GCC___linker_scripts}:${CMAKE_CURRENT_LIST_DIR}/sysmem.c>")
  endif()
endif()

