/**
 * Orientation from accelerometer + gyroscope (no magnetometer):
 * - roll and pitch are absolute (gravity reference),
 * - yaw is relative to the last reset and slowly drifts.
 *
 * Uses a Mahony complementary filter and a gyro bias estimated while the board
 * is held still. Samples arrive in the IMU's sensor frame; the gyro bias is
 * removed there, then everything is rotated into the board frame (mounting.ts).
 * Quaternions are [w, x, y, z] and describe the board's orientation.
 */
import type { ImuSample, Vec3 } from '../types';
import { sensorToBoard } from './mounting';

export type Quat = [number, number, number, number];

const DEG2RAD = Math.PI / 180;

/** Nominal IMU output data rate set by the firmware (imu_lsm6dsv*.c: 120 Hz). */
export const IMU_ODR_HZ = 120;

/** Averages the gyro over N samples while the board is still. */
export class GyroCalibrator {
  private sum: Vec3 = [0, 0, 0];
  private accelNormMin = Infinity;
  private accelNormMax = -Infinity;
  private count = 0;

  constructor(private readonly samples = 2 * IMU_ODR_HZ) {}

  get progress(): number {
    return this.count / this.samples;
  }

  /** Returns the bias in mdps once enough samples were collected, else null.
   *  Throws if the board moved during calibration. */
  feed(s: ImuSample): Vec3 | null {
    for (let i = 0; i < 3; i++) this.sum[i]! += s.gyroMdps[i]!;
    const norm = Math.hypot(...s.accelMg);
    this.accelNormMin = Math.min(this.accelNormMin, norm);
    this.accelNormMax = Math.max(this.accelNormMax, norm);
    this.count++;

    if (this.count < this.samples) return null;
    if (this.accelNormMax - this.accelNormMin > 50) {
      throw new Error('Board moved during gyro calibration; keep it still and retry.');
    }
    return this.sum.map((v) => v / this.count) as Vec3;
  }
}

export class MahonyFilter {
  q: Quat = [1, 0, 0, 0];
  private integral: Vec3 = [0, 0, 0];

  /** kp: accel correction strength; ki: online gyro bias correction (0 = off). */
  constructor(public kp = 1.0, public ki = 0.02) {}

  /** Initializes roll/pitch from gravity, yaw = 0. */
  resetFromAccel(a: Vec3): void {
    const [ax, ay, az] = a;
    const roll = Math.atan2(ay, az);
    const pitch = Math.atan2(-ax, Math.hypot(ay, az));
    const cr = Math.cos(roll / 2), sr = Math.sin(roll / 2);
    const cp = Math.cos(pitch / 2), sp = Math.sin(pitch / 2);
    this.q = [cr * cp, sr * cp, cr * sp, -sr * sp];
    this.integral = [0, 0, 0];
  }

  /** gyro in rad/s, accel in any unit (normalized), dt in seconds. */
  update(g: Vec3, a: Vec3, dt: number): void {
    let [gx, gy, gz] = g;
    const [ax0, ay0, az0] = a;
    let [qw, qx, qy, qz] = this.q;

    const an = Math.hypot(ax0, ay0, az0);
    if (an > 0) {
      const ax = ax0 / an, ay = ay0 / an, az = az0 / an;
      // Gravity direction predicted by the current orientation.
      const vx = 2 * (qx * qz - qw * qy);
      const vy = 2 * (qw * qx + qy * qz);
      const vz = qw * qw - qx * qx - qy * qy + qz * qz;
      // Error = measured x predicted.
      const ex = ay * vz - az * vy;
      const ey = az * vx - ax * vz;
      const ez = ax * vy - ay * vx;
      if (this.ki > 0) {
        this.integral[0] += this.ki * ex * dt;
        this.integral[1] += this.ki * ey * dt;
        this.integral[2] += this.ki * ez * dt;
      }
      gx += this.kp * ex + this.integral[0];
      gy += this.kp * ey + this.integral[1];
      gz += this.kp * ez + this.integral[2];
    }

    // Integrate the rate of change of the quaternion.
    const h = 0.5 * dt;
    const dw = (-qx * gx - qy * gy - qz * gz) * h;
    const dx = (qw * gx + qy * gz - qz * gy) * h;
    const dy = (qw * gy - qx * gz + qz * gx) * h;
    const dz = (qw * gz + qx * gy - qy * gx) * h;
    qw += dw; qx += dx; qy += dy; qz += dz;
    const n = Math.hypot(qw, qx, qy, qz);
    this.q = [qw / n, qx / n, qy / n, qz / n];
  }
}

/** Glue: bias removal (sensor frame), board-frame rotation, unit conversion,
 *  dt from sequence numbers. */
export class OrientationEstimator {
  readonly filter = new MahonyFilter();
  /** Gyro zero-rate offset in the sensor frame (as calibrated on raw data). */
  gyroBiasMdps: Vec3 = [0, 0, 0];
  private lastSeq: number | null = null;
  private needsReset = true;

  reset(): void {
    this.lastSeq = null;
    this.needsReset = true;
  }

  update(s: ImuSample): Quat {
    const accel = sensorToBoard(s.accelMg);
    if (this.needsReset) {
      this.filter.resetFromAccel(accel);
      this.needsReset = false;
      this.lastSeq = s.seq;
      return this.filter.q;
    }
    // dt from the sample counter: the MCU timestamp has only 1 ms resolution
    // (12 % jitter at 120 Hz), the IMU's own sample clock is far steadier.
    const steps = this.lastSeq !== null && s.seq > this.lastSeq ? s.seq - this.lastSeq : 1;
    this.lastSeq = s.seq;
    const dt = Math.min(steps, 10) / IMU_ODR_HZ;

    const gSensor = s.gyroMdps.map((v, i) => (v - this.gyroBiasMdps[i]!) * 1e-3 * DEG2RAD) as Vec3;
    this.filter.update(sensorToBoard(gSensor), accel, dt);
    return this.filter.q;
  }
}

/** Roll, pitch, yaw in degrees (Z-Y-X convention) for display. */
export function quatToEulerDeg([w, x, y, z]: Quat): Vec3 {
  const roll = Math.atan2(2 * (w * x + y * z), 1 - 2 * (x * x + y * y));
  const pitch = Math.asin(Math.max(-1, Math.min(1, 2 * (w * y - z * x))));
  const yaw = Math.atan2(2 * (w * z + x * y), 1 - 2 * (y * y + z * z));
  return [roll / DEG2RAD, pitch / DEG2RAD, yaw / DEG2RAD];
}
