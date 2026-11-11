# Syscalls Software Pack

![tag](https://img.shields.io/badge/tag-v2.0.1-brightgreen.svg)
[![release note](https://img.shields.io/badge/release_note-view_html-gold.svg)](https://htmlpreview.github.io/?https://github.com/STMicroelectronics/stm32-util-syscalls/blob/main/Release_Notes.html)

## Overview

This utility implements the operating system interface documented by newlib (arm-none-eabi-gcc
links with newlib as the default libc implementation). The functions included in this
CMSIS-pack are the most common stubs used in an application for calling the kernel in a
high-level OS.

For the application to have the intended runtime behavior, the developer needs to adjust the
implementation of the called function(s) in `syscalls.c` to fulfill the application requirements.
In some cases, a warning might be issued at link stage due to a function being used that will not
have the correct runtime behavior. Two common functions that the application might want to override
are `_read()` and `_write()` as they are the low-level functions called by `printf()` and `scanf()`
to do the I/O.

The commonly used high-level function `malloc()` uses the low-level function `_sbrk()`. This
low-level function has a tight dependency on the linker script. An implementation can be found
in `sysmem.c`. The `new` keyword in C++ uses `malloc()` to allocate memory on the heap.


The documentation for the included functions in `syscalls.c` and `sysmem.c` can be found at [https://sourceware.org/newlib/libc.html#Syscalls].

## Description and Usage

This component is only applicable to projects linked against newlib.

It is recommended for both `syscalls.c` and `sysmem.c` to be included in each project using newlib.
Please note that `sysmem.c` has a tight dependency on the ST-provided linker script.

The `syscalls.c` file contains a sub-set of overridable functions that would require data from a
kernel in a high-level OS. Please note that **most** functions in `syscalls.c` are only stubbed and will
always fail at runtime. In order for the functions to be usable in an application, they need to be
updated to contain a suitable implementation.

To use the newlib provided stubs, use the `--specs=nosys.specs` linker option and remove the
`syscalls.c` file from the application source tree. The newlib provided stubs will cause runtime
failures when called.
