---
pagetitle: Release Notes for STM32C5xx HAL Drivers SW Pack
lang: en
header-includes: <link rel="icon" type="image/x-icon" href="_htmresc/favicon.png" />
---

::: {.row}
::: {.col-sm-12 .col-lg-4}

<center>
# Release Notes for
# <mark>STM32C5xx HAL Drivers SW Pack</mark>

[![ST logo](_htmresc/st_logo_2020.png)](https://www.st.com){.logo}
</center>

# Purpose

STM32Cube enables developers to achieve design success. With a comprehensive suite of professional development tools and embedded software components, STM32Cube allows developers to differentiate products, streamline design cycles, and reduce costs. STM32Cube ecosystem supports all design steps, including selection, configuration, development, debugging, programming, and monitoring.

The STM32Cube embedded software offer provides ready-to-use software components that can be added to a project. It includes STM32 peripheral driver APIs with two levels of abstraction, middleware, board drivers, and examples. There are several distribution channels, including the STM32CubeMX2 tool, the ST website, and GitHub. All embedded software comes with enhanced online documentation, with flowcharts and user sequences.

More detailed documentation is available at [STM32C5xx HAL Drivers online documentation](https://dev.st.com/stm32cube-docs/stm32c5xx-hal-drivers/latest/en/index.html)

:::

::: {.col-sm-12 .col-lg-8}
# Update History

::: {.collapse}
<input type="checkbox" id="collapse-section-2.1.0" checked aria-hidden="true">
<label for="collapse-section-2.1.0" aria-hidden="true">__2.1.0 / 12-June-2026__</label>
<div>

## Main changes

### Second Official release of **STM32C5xx HAL Drivers**

\

## Contents

- **HAL/LL Drivers** are available for all peripherals:
  - **System** : CORTEX, CRS, DBGMCU, DMA (Q), ICACHE, IWDG, PWR, RCC, RTC, SBS, WWDG
  - **I/O** : EXTI, GPIO
  - **Analog** : ADC, COMP, DAC, OPAMP
  - **Timers** : TIM, LPTIM
  - **Connectivity** : FDCAN, I2C, I3C, SMARTCARD, SMBUS, I2S, SPI, UART, LPUART, USART, USB (HCD/PCD), ETH
  - **Security** : AES, CCB, HASH, PKA, RNG, TAMP
  - **Computing** : CORDIC, CRC
  - **Memory** : FLASH, RAMCFG, XSPI (DLYB)
  - **Common** : OS, Timebases, Templates
- **Utils** are available for FDCAN, I2C, I3C peripherals.

\

- **HAL/LL Drivers** updates
  - HAL/LL **CORDIC**
    - Add HAL_CORDIC_GetInstance() and HAL_CORDIC_GetLLInstance() functions
  - HAL/LL **ICACHE**
    - Add HAL_ICACHE_GetInstance() and HAL_ICACHE_GetLLInstance() functions
  - HAL **GPIO**
    - Add HAL_GPIO_GetLLInstance() function
    - Update HAL_GPIO_AFn_XXX alternate function definitions to align with the reference manual. Keep the old definitions as compatibility aliases.
  - HAL **HCD**
    - Add HAL_HCD_RegisterChannelAbortTransferCallback() and HAL_HCD_ChannelAbortTransferCallback() functions
    - Remove High-Speed and ULPI-related public definitions that do not apply to STM32C5 supported devices
  - HAL **LPTIM**
    - Remove HAL_LPTIM_CompareMatchHalfCpltCallback() prototype because LPTIM peripheral does not support it
  - HAL **PCD**
    - Add HAL_PCD_RegisterEndpointAbortTransferCallback() and HAL_PCD_EndpointAbortTransferCallback() functions
    - Remove High-Speed and ULPI-related public definitions that do not apply to STM32C5 supported devices
  - LL **TIM**
    - Apply naming changes to remove duplication in functions name of LL_TIM_POSITION_BRK_SOURCE(), LL_TIM_GET_CHANNEL_INDEX(), LL_TIM_CALC_DTS(). Keep the old definitions as compatibility aliases.

\

## Development toolchains and compilers

- IAR Embedded Workbench for ARM (EWARM) toolchain V9.60.3 + ST-LINK
- MDK-ARM Keil uVision V5.42
- STM32CubeIDE for Visual Studio Code (GCC13 compiler)
- STM32CubeMX2 V1.0.0

\

## Supported devices and boards

- STM32C551xx, STM32C552xx, STM32C562xx devices
- STM32C531xx, STM32C532xx, STM32C542xx devices
- STM32C591xx, STM32C593xx, STM32C5A3xx devices
- NUCLEO-C562RE (RevB02), NUCLEO-C542RC (RevB02), NUCLEO-C5A3ZG (RevB02) boards 

\

## Known limitations

- HAL ETH
  - PTP, hardware timestamping, MAC VLAN tagging and advanced MAC filtering features are not supported in this driver version and will be considered for a future release.
- HAL I2C
	- As defined by MIPI, I2C stretch mode is not supported in I3C communication.
- HAL I2S
	- Using the -Oz optimization in ARMCC6.24.0 may reorder peripheral memory accesses causing initialization and execution issues in HAL I2S driver.
- HAL I3C
  - Acknowledgement issue is observed after 2 consecutive aborts (interrupt race condition).

\

## Backward compatibility

- None

\

## Dependencies

- STM32C5xx DFP 2.1.0

\

</div>
:::


::: {.collapse}
<input type="checkbox" id="collapse-section-2.0.0" aria-hidden="true">
<label for="collapse-section-2.0.0" aria-hidden="true">__2.0.0 / 13-March-2026__</label>
<div>

## Main changes

### First Official release of **STM32C5xx HAL Drivers**

\

## Contents

- **HAL/LL Drivers** are available for all peripherals:
  - **System** : CORTEX, CRS, DBGMCU, DMA (Q), ICACHE, IWDG, PWR, RCC, RTC, SBS, WWDG
  - **I/O** : EXTI, GPIO
  - **Analog** : ADC, COMP, DAC, OPAMP
  - **Timers** : TIM, LPTIM
  - **Connectivity** : FDCAN, I2C, I3C, SMARTCARD, SMBUS, I2S, SPI, UART, LPUART, USART, USB (HCD/PCD), ETH
  - **Security** : AES, CCB, HASH, PKA, RNG, TAMP
  - **Computing** : CORDIC, CRC
  - **Memory** : FLASH, RAMCFG, XSPI (DLYB)
  - **Common** : OS, Timebases, Templates
- **Utils** are available for FDCAN, I2C, I3C peripherals.
 

\

## Development toolchains and compilers

- IAR Embedded Workbench for ARM (EWARM) toolchain V9.60.3 + ST-LINK
- MDK-ARM Keil uVision V5.42
- STM32CubeIDE for Visual Studio Code (GCC13 compiler)
- STM32CubeMX2 V1.0.0

\

## Supported devices and boards

- STM32C551xx, STM32C552xx, STM32C562xx devices
- STM32C531xx, STM32C532xx, STM32C542xx devices
- STM32C591xx, STM32C593xx, STM32C5A3xx devices
- NUCLEO-C562RE, NUCLEO-C542RC, NUCLEO-C5A3ZG boards

\

## Known limitations

- HAL ETH
  - PTP, hardware timestamping, MAC VLAN tagging and advanced MAC filtering features are not supported in this driver version and will be considered for a future release.
- HAL HASH
	- When using HAL_HASH_Update_DMA(), no interrupt is triggered when the input is smaller than the DMA block size (4 words).
	- When using HAL_HASH_Update_IT(), no interrupt is triggered when the input is smaller than the block size.
- HAL I2C
	- As defined by MIPI, I2C stretch mode is not supported in I3C communication.
- HAL I2S
	- Using the -Oz optimization in ARMCC6.24.0 may reorder peripheral memory accesses causing initialization and execution issues in HAL I2S driver.
- HAL I3C
  - Acknowledgement issue is observed after 2 consecutive aborts (interrupt race condition).

\

## Backward compatibility

- None

\

## Dependencies

- STM32C5xx DFP 2.0.0

\

</div>
:::

\

\

:::
:::

<footer class="sticky">
::: {.columns}
::: {.column width="95%"}
For complete documentation on STM32 Microcontrollers,
visit: [www.st.com/stm32](https://www.st.com/en/microcontrollers-microprocessors/stm32-32-bit-arm-cortex-mcus.html)
:::
::: {.column width="5%"}
<abbr title="Based on template cx566953 version 2.1"></abbr>
:::
:::
</footer>
