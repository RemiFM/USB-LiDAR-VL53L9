# STM32C5xx Device Support for IAR Embedded Workbench for ARM

IAR Embedded Workbench for ARM (EWARM) is the reference integrated development environment for this patch set. Additional details regarding EWARM are available at [iar.com](https://www.iar.com/).

## Overview

This document outlines the procedure required to extend an existing EWARM installation with STM32C5xx device support. The patch is applicable to EWARM version **9.20.1** or any later release.

## Distribution Contents

The `STMicroelectronics.stm32c5xx.2.1.0.iar.zip` archive provides the following STM32C5xx collateral:

- Device part-number definitions
- Linker configuration files
- Flash loader implementations
- System View Description (SVD) files

## Prerequisites

- A working installation of **IAR Embedded Workbench for ARM** (version 9.20.1 or later).
- Permissions to modify files inside the EWARM installation directory (administrator/root rights may be required).

## Installation Options

The patch may be deployed either automatically by using the provided scripts (recommended) or manually by copying the files into the EWARM installation tree.

### Automatic Installation

Use the script that matches your operating system:

| Operating System | Install Script      |
|------------------|---------------------|
| **Windows**      | `install_patch.bat` |
| **Linux**        | `install_patch.sh`  |

1. Locate your EWARM installation directory, typically something like:
   - Windows: `C:\Program Files\IAR Systems\Embedded Workbench 9.x` or `C:\iar\ewarm-9.xx.x`
   - Linux: `/opt/iarsystems/bxarm-9.xx.x`
2. Close all running instances of EWARM.
3. Run the appropriate install script (from a terminal or command prompt), specifying the EWARM installation directory when prompted.

    > **Linux** : Ensure `install_patch.sh` is executable: `chmod +x install_patch.sh`

    > If required by your environment, run the script with elevated permissions (e.g., "Run as administrator" on Windows or `sudo` on Linux).

The script performs the following actions:

- Requests the EWARM installation directory.
- Removes any previous STM32C5xx patch content.
- Installs the updated STM32C5xx patch files.

### Manual Installation

1. Close all running instances of EWARM.
2. Extract the contents of `STMicroelectronics.stm32c5xx.2.1.0.iar.zip` into `<IAR install directory>/arm` and allow the operating system to overwrite existing STM32C5xx files if prompted.
