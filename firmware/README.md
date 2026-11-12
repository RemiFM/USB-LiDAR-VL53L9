# Firmware (STM32C552KEU6)

Firmware for the board's STM32C552: streams the VL53L9 LiDAR (54×42 zones, ~35 fps) and the LSM6DSV16BX IMU (120 Hz) over USB using the binary protocol in [`app/protocol.h`](app/protocol.h).

## Requirements

- An ST-Link (V2 or V3) connected to the SWD header (J3: 1 VTref, 2 SWDIO, 3 SWCLK, 5 NRST, 6 GND), and the board powered over its own USB-C.
- **VS Code with the STM32Cube extension** (installs the GCC toolchain, CMake, Ninja and the `cube` tools), or the same tools on the command line.
- The git submodules (ST IMU drivers):

  ```bash
  git clone --recursive https://github.com/RemiFM/USB-LiDAR-VL53L9.git
  # or, in an existing clone:
  git submodule update --init
  ```

## Build and flash

**VS Code**: open the `firmware/` folder, select the CMake preset `debug_GCC_STM32C552KEU6`, build, and start debugging (F5) to flash over the ST-Link.

**Command line**:

```bash
cd firmware
cube cmake --preset debug_GCC_STM32C552KEU6
cube cmake --build --preset debug_GCC_STM32C552KEU6
STM32_Programmer_CLI -c port=SWD freq=4000 \
  -w build/debug_GCC_STM32C552KEU6/USB-LiDAR-VL53L9-STM32C552KEU6.elf -v -rst
```

`STM32_Programmer_CLI` is part of STM32CubeProgrammer (also installed by the VS Code extension under `~/.local/share/stm32cube/bundles/programmer/`).

## Check that it works

After flashing, disconnect the debugger and replug the board's USB:

```bash
lsusb | grep cafe:4010                       # RemiFM USB LiDAR & IMU
python3 tools/stream_check.py --seconds 10   # needs pyserial
```

`stream_check.py` prints the device info and reports IMU and LiDAR rates, CRC errors and lost packets. With `--save DIR` it also saves the calibration and a raw frame. Expected: ~120 IMU samples/s, ~35 LiDAR frames/s, 0 errors. Then use the web app in [`../application`](../application).

**LED**: 1 Hz blink = running, 4 Hz = LiDAR streaming, fast blink = LiDAR error (send `R` or use *Re-init LiDAR* in the app).

## Commands

The host sends single ASCII characters (also works from a serial terminal, but the device's replies are binary packets):

| Key | Action | Key | Action |
|---|---|---|---|
| `V` | send device info | `C` | send LiDAR calibration |
| `I` / `i` | IMU stream on / off | `L` / `l` | LiDAR stream on / off |
| `X` | stop all streams | `R` | re-initialize the LiDAR |
| `U` | re-detect the IMU | `T` / `B` | LED manual toggle / back to automatic |

## Code layout

| Path | Contents |
|---|---|
| `main.c` | Calls `mx_system_init()` (CubeMX2), then `app_init()` and `app_loop()` forever. |
| `app/app.c` | Main loop: USB commands, IMU sampling, status packets, LED. |
| `app/protocol.h` | USB protocol definition (packet header, types, payloads, commands). |
| `app/proto_tx.c` | Non-blocking packet transmitter (large LiDAR frames sent zero-copy). |
| `app/lidar.c` | VL53L9 power-up, configuration and frame streaming. |
| `app/lidar_bus.c`, `app/soft_i2c.c` | I3C bring-up (12 MHz) with bit-banged I²C as fallback. |
| `app/vl53l9_platform.c` | Platform layer for ST's VL53L9 driver. |
| `app/imu*.c` | IMU detection (WHO_AM_I) and one backend per supported part. |
| `app/usb_app.c`, `app/usb_descriptors.c` | TinyUSB setup and USB descriptors (serial number = chip unique ID). |
| `vendor/` | TinyUSB, ST VL53L9 driver, ST IMU drivers (submodules), HAL I3C patch. |
| `generated/`, `cmake/`, `stm32c5xx_*`, `user_modifiable/` | STM32CubeMX2 output and ST packages. |
| `tools/stream_check.py` | USB stream checker. |

## Notes

- **STM32CubeMX2**: the hardware configuration is `USB-LiDAR-VL53L9-STM32C552KEU6.ioc2`. Regenerating is safe: own code lives in `app/`, `main.c` and the "Add additional …" sections of `CMakeLists.txt`. Don't edit files in `generated/`.
- **HAL patch**: three I3C bug fixes are applied to ST's HAL at CMake configure time (`vendor/patches/apply_hal_patches.cmake`), so a HAL update by CubeMX2 cannot silently undo them.
- **IMU variants**: LSM6DSV16BX (WHO_AM_I `0x71`) is detected automatically. LSM6DSV and LSM6DSV16X both report `0x70`: the LSM6DSV driver is used unless you configure with `-DIMU_ID70_IS_LSM6DSV16X=ON`.
- **LiDAR settings** (`app/lidar.c`): manual trigger, ultra-low-power mode, short context, binning 2 (54×42), 6 ms exposure. Depth is computed on the host with ST's processing library and the sensor calibration.
- **USB IDs**: `cafe:4010` is a development ID (TinyUSB's example vendor ID); change it in `app/usb_descriptors.c` for a product.
