/**
 * How the IMU is mounted on the board: converts IMU (sensor) axes into board axes.
 *
 * Board frame (used for orientation, plots and the 3D view):
 *   +X  to the right, looking at the top side with the USB connector at the bottom
 *   +Y  from the USB connector towards the LiDAR
 *   +Z  out of the top side = the LiDAR's viewing direction
 *
 * Derivation (pcb/USB-LiDAR-VL53L9.kicad_pcb, LSM6DSV16BX datasheet Figure 5):
 *   - Datasheet: pin-1 dot at the (min X, max Y) corner of the package top, Z out
 *     of the top. With the footprint's pin 1 at top-left this gives, in footprint
 *     coordinates (top view): sensor X = right, sensor Y = up, sensor Z = out.
 *   - U3 is on B.Cu (flipped, so its top faces down) and rotated 90 degrees.
 *   - Result: sensor X -> board +Y, sensor Y -> board +X, sensor Z -> board -Z.
 * Check: board flat, LiDAR facing up => raw accel Z is about -1000 mg.
 *
 * LSM6DSV and LSM6DSV16X use the same axes and footprint, so this applies to all three.
 */
import type { Vec3 } from '../types';

/** Rotation matrix (rows = board axes expressed in sensor axes). det = +1. */
export const SENSOR_TO_BOARD: readonly [Vec3, Vec3, Vec3] = [
  [0, 1, 0],  // board X = sensor Y
  [1, 0, 0],  // board Y = sensor X
  [0, 0, -1], // board Z = -sensor Z
];

/**
 * LiDAR (camera frame from ST's transform: x right, y down, z forward) -> board frame.
 * The sensor looks along board +Z, so board Z = z. Default: image rotated 180 deg
 * about Z (U1's rotation in the PCB file): X = -x, Y = -y.
 * mirrorH / mirrorV flip the image horizontally / vertically on top of that
 * (both = 0 deg mounting). Verify once: an object at the board's +X side must
 * appear at +X; a single flip mirrors the scene, so normally use none or both.
 */
export function lidarToBoard(mirrorH: boolean, mirrorV: boolean) {
  const sx = mirrorH ? 1 : -1;
  const sy = mirrorV ? 1 : -1;
  return (x: number, y: number, z: number, out: Float32Array, o: number): void => {
    out[o] = sx * x;
    out[o + 1] = sy * y;
    out[o + 2] = z;
  };
}

export function sensorToBoard(v: Vec3): Vec3 {
  const m = SENSOR_TO_BOARD;
  return [
    m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2],
    m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2],
    m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2],
  ];
}
