# USB-C LiDAR Node (VL53L9)

![Status](https://img.shields.io/badge/status-schematics_done_%E2%80%94_PCB_layout_in_progress-yellow?style=for-the-badge)

<img src="doc/render.png" alt="PCB render" width="75%">

A compact and low-cost USB device with integrated LiDAR sensor and IMU. This hardware node packages STMicroelectronics' VL53L9 advanced direct Time-of-Flight (dToF) matrix LiDAR with a 6-axis IMU into a plug-and-play USB-C device. Designed for mobile robotics, micro-UAVs, and academic SLAM research. The hardware is designed in KiCad 10.

## System Architecture
![Block diagram showing VL53L9 LiDAR and LSM6DSV IMU connected via I3C to an STM32C55xx MCU, which interfaces to the host over USB Full-Speed](doc/block_diagram.png)

| Feature | Detail | Datasheet |
|---|---|---|
| **LiDAR** | ST VL53L9CX dToF module with up to 54×42 (2.3 k) discrete ranging zones, 5 cm–8.8 m range | [link](https://www.st.com/resource/en/datasheet/vl53l9cx.pdf)
| **IMU** | ST LSM6DSV 6-axis IMU with embedded sensor fusion engine, orientation quaternions generated on-chip | [link](https://www.st.com/resource/en/datasheet/lsm6dsv.pdf)

## Data Format
Raw binary packet framing is used instead of verbose text formats (JSON/CSV) to stay well within the 12 Mbps USB Full-Speed ceiling while imposing zero processing overhead on the MCU.

Per the VL53L9CX datasheet (DS14879, Table 2), the I3C interface is specified for a 12.5 MHz bus clock and a 12.5 Mbps output data rate. Full resolution is hard-limited to 30 Hz. Two pre-configured profiles are available:

| Profile | Output Matrix | Frame Rate |
|---|---|---|
| **Full Resolution** *(default)* | 54 × 42 zones | 30 Hz |
| **Binned Navigation** *(high-velocity)* | 24 × 20 zones | 60 Hz |

## Mechanical Specs

The PCB measures 34 × 34 mm and has 4× M3 mounting holes on a 20 mm square pitch, fitting small drone frame stacks.
