# ST VL53L9 driver

Portable driver for the VL53L9CX, from ST's STSW-IMG053 package
(`vl53l9-stm32n6570-dk-1.0.1/drivers/vl53l9`), including sensor firmware patch
0.17 (`vl53l9_patch.h`). License: BSD-3-Clause (`LICENSE.txt`,
`STSW-IMG053-LICENSE.md`). ST does not publish this driver as a git repository,
so it is vendored here instead of added as a submodule.

Copied unchanged from the VL53L9-UNO-Q-LiDAR repository
(`firmware/vendor/vl53l9`), which documents the upstream source in
`PROVENANCE.json`.

## Local change (inherited)

`vl53l9.c` carries one small fix, so its hash differs from the upstream hash in
`PROVENANCE.json` (upstream `2b88b0c0…`, this copy `cf6292f9…`):
initialize `sync_mode` before the one-byte read into an enum in
`vl53l9_trigger_frame()`, use `uint8_t` for FSM and command reads, and return an
invalid FSM on a transport failure. This avoids indeterminate upper enum bytes
causing spurious state/command errors. All other files are ST's originals.

## Platform

The STM32 platform layer (bus access, delays, clock/voltage config) is
`firmware/app/vl53l9_platform.c`.
