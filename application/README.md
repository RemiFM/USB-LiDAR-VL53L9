# USB LiDAR & IMU viewer

Browser app for the board over USB: LiDAR (3D point cloud, depth map, top view),
IMU graphs and 3D orientation, stream statistics, recording and playback.

![Web application: LiDAR point cloud, depth map and IMU orientation](../doc/application.gif)

Stack: TypeScript + Vite, Web Serial, uPlot, Three.js, Tailwind CSS, and ST's
VL53L9 processing library compiled to WebAssembly.

## Run

Requires Node 20.19+ and **Chrome or Edge** (Web Serial is Chromium-only).

```bash
cd application
npm install
npm run dev        # open http://localhost:5173
```

Click **Connect** (in the LiDAR card), pick "USB LiDAR & IMU" (`cafe:4010`). The app requests the
device info and LiDAR calibration and starts the IMU and LiDAR streams. On Linux
your user must be in the `dialout` group, and no other program (minicom, …)
may hold the port.

Without hardware: `http://localhost:5173/?replay=<url-of-session.bin>` loads and
plays a recording (optionally `&tab=cloud|depth|top`).

## Usage

- **IMU / LiDAR** (header): stream on/off; green = streaming (from device status).
- **Link icon** (header, right): green link = connected (click to disconnect),
  red broken link = not connected (click to connect).
- **Record** (red dot; pulsing square while recording), **upload** (load a
  recording), **play/pause** (greyed out until a recording is loaded).
- **Board LED** (no button needed): 1 Hz blink idle, 4 Hz while the LiDAR
  streams, fast on a LiDAR error.
- **LiDAR card**: **3D** point cloud (orbit with the mouse, *Reset view* refits),
  **Depth map** (hover a zone for its values; *Smooth* interpolates between valid
  zones with soft edges, off = one sharp cell per zone) and **Top view** (bird's-eye with
  range rings and the field of view). Colour by depth or reflectance, **Max range**
  (hides everything further away in all views; depth colours then span 0 to that
  distance), ST's temporal filter, and **Level with IMU** (3D: rotates the
  cloud with the board orientation so the floor stays horizontal).
  *Re-init LiDAR* power-cycles and reconfigures the sensor.
- **Calibrate gyro**: runs automatically on the first 2 s after connecting
  (keep the board still), or on demand from the Orientation card.
- **Reset yaw**: sets yaw back to 0. Roll/pitch are always measured against
  gravity; yaw is relative and drifts slowly (there is no magnetometer).
- **Record** / stop: downloads `session-<time>.bin` (everything the
  device sent, replayable: LiDAR + IMU) and `imu-<time>.csv` (readable IMU log).
- **Upload** + **Play**: replays a `session-*.bin` or `imu-*.csv` (disconnect
  first) at 0.25–4×.
- **Stream card**: USB throughput, packets, CRC errors / sequence gaps; LiDAR
  frame rate, valid zones, depth range, WASM processing time, frames sent /
  dropped on the MCU, bus; IMU rate and drops; firmware and sensor info.

## Frames

The IMU sits on the **bottom** of the board, the LiDAR on the **top**.
`src/processing/mounting.ts` rotates both into the **board frame**: X right,
Y towards the LiDAR (away from USB), Z out of the top side (LiDAR viewing
direction). Plots, orientation and LiDAR views use the board frame; recordings
keep the raw values exactly as the firmware sent them.

- IMU check: board flat, LiDAR facing up → raw accel Z ≈ −1000 mg, plotted
  board Z ≈ +1000 mg, roll/pitch ≈ 0°.
- LiDAR check (default orientation from the PCB file): hold a hand at the
  board's +X side (right, seen from the top). In the depth map and top view
  (both seen from behind the sensor, so +X is on the **left**), it must appear
  on the left; otherwise use the **mirror** buttons in the LiDAR card
  (normally none or both: both = sensor rotated 180°).

## LiDAR processing (WebAssembly)

Raw 54×42 frames (14 842 bytes) are turned into 3D points by ST's
`vl53l9-transform-c` library with the connected sensor's own calibration, in the
browser. `wasm/l9_bridge.c` wraps it; the build uses `@yowasp/clang` (clang +
wasi-libc running in Node, no system toolchain):

```bash
npm run build-wasm      # -> src/processing/wasm/vl53l9.wasm (~85 kB, no imports)
```

Output was verified bit-identical to ST's native build on a real frame
(~1 ms per frame).

## 3D board model

`public/models/board.glb` is exported from the KiCad PCB (real outline and the
component STEP models from `pcb/3d/`). Regenerate it after PCB changes:

```bash
npm run export-board    # needs kicad-cli (KiCad 8+); takes a few seconds
```

The export origin is the board centre (`--user-origin 150x101.9mm` in
`package.json`); update it if the board moves in the KiCad file. The LiDAR FoV
cone is attached to the part named `U1`.

## Data format

USB protocol: binary packets, see `firmware/app/protocol.h` (reference) and
`src/protocol/binary.ts` (mirror). Recordings: `session-*.bin` is the raw packet
stream; `imu-*.csv` is

```
#I,seq,t_ms,ax_mg,ay_mg,az_mg,gx_mdps,gy_mdps,gz_mdps,temp_cdeg
I,1234,56789.125,76.25,-1003.08,192.03,-140.00,2485.00,630.00,2579
```

## Structure

```
src/
  types.ts                  ImuSample, Vec3, small event emitter
  transport/serial.ts       Web Serial: connect, byte stream, write
  protocol/binary.ts        packet parser (CRC, resync), decoders, commands
  protocol/crc32.ts         CRC-32 (same as the firmware)
  protocol/csv.ts           IMU CSV log format
  processing/stats.ts       IMU rate, dropped samples
  processing/mounting.ts    IMU (bottom side) and LiDAR -> board frame
  processing/orientation.ts gyro calibration, Mahony filter, Euler angles
  processing/lidar.ts       WASM wrapper: raw frame -> points, depth, reflectance
  processing/wasm/          compiled vl53l9.wasm
  logging/recorder.ts       session .bin + IMU .csv recording
  logging/playback.ts       replay .bin (all packets) or .csv (IMU)
  ui/plots.ts               uPlot rolling plots
  ui/orientation3d.ts       Three.js board view
  ui/console.ts             device console
  ui/colormap.ts            Turbo colour map
  ui/lidar/                 depth map, top view, point cloud
  main.ts                   wiring only
wasm/                       C bridge, build script, vendored ST library
```

Live device and playback feed the same `handlePacket()` pipeline, so processing
and views never know where data comes from.

## Third-party licenses

The VL53L9 processing library (`wasm/vendor/`, compiled into
`src/processing/wasm/vl53l9.wasm`) is © STMicroelectronics, licensed under
**SLA0111** (see `wasm/vendor/*/**/LICENSE.txt`): it may only be used with ST
sensors, and binary redistributions must reproduce ST's copyright notice,
conditions and disclaimer. It is not covered by this project's own license.
`wasm/l9_bridge.c` is adapted from VL53L9-UNO-Q-LiDAR (MIT).
