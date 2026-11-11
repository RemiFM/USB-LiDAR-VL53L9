/** Shared data types. Every layer speaks in these, never in raw bytes or text. */

export type Vec3 = [number, number, number];

/** One IMU sample as sent by the firmware (units as on the wire, no processing). */
export interface ImuSample {
  /** Sample counter from the MCU; resets to 0 when a stream starts. Gaps = dropped lines. */
  seq: number;
  /** MCU timestamp in milliseconds since boot (HAL_GetTick). */
  tMs: number;
  /** Acceleration X, Y, Z in milli-g. */
  accelMg: Vec3;
  /** Angular rate X, Y, Z in milli-degrees per second. */
  gyroMdps: Vec3;
  /** Die temperature in degrees Celsius. */
  tempC: number;
}

/** Minimal typed event emitter used to decouple modules. */
export class Emitter<T> {
  private readonly listeners = new Set<(value: T) => void>();

  on(fn: (value: T) => void): () => void {
    this.listeners.add(fn);
    return () => this.listeners.delete(fn);
  }

  emit(value: T): void {
    for (const fn of this.listeners) fn(value);
  }
}
