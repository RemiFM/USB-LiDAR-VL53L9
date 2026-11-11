/**
 * Human-readable IMU log format (recordings), one line per sample:
 *   #I,seq,t_ms,ax_mg,ay_mg,az_mg,gx_mdps,gy_mdps,gz_mdps,temp_cdeg   header
 *   I,1234,56789.125,76.25,-1003.08,192.03,-140.00,2485.00,630.00,2579
 * Values are raw IMU sensor-frame readings. Lines not starting with "I," are
 * comments. (Early firmware sent this format live; it now uses protocol/binary.ts.)
 */
import type { ImuSample } from '../types';

export const CSV_HEADER = '#I,seq,t_ms,ax_mg,ay_mg,az_mg,gx_mdps,gy_mdps,gz_mdps,temp_cdeg';

export type ParsedLine =
  | { kind: 'imu'; sample: ImuSample }
  | { kind: 'info'; text: string }
  | { kind: 'invalid'; text: string };

export function parseLine(line: string): ParsedLine {
  if (!line.startsWith('I,')) return { kind: 'info', text: line };

  const f = line.split(',');
  if (f.length !== 10) return { kind: 'invalid', text: line };
  const n = f.slice(1).map((v) => Number.parseFloat(v));
  if (n.some((v) => !Number.isFinite(v))) return { kind: 'invalid', text: line };

  const [seq, tMs, ax, ay, az, gx, gy, gz, tc] = n as [
    number, number, number, number, number, number, number, number, number,
  ];
  return {
    kind: 'imu',
    sample: { seq, tMs, accelMg: [ax, ay, az], gyroMdps: [gx, gy, gz], tempC: tc / 100 },
  };
}

/** Inverse of parseLine for data lines (used by the recorder). */
export function formatSample(s: ImuSample): string {
  return [
    'I', s.seq, s.tMs.toFixed(3),
    ...s.accelMg.map((v) => v.toFixed(2)), ...s.gyroMdps.map((v) => v.toFixed(2)),
    Math.round(s.tempC * 100),
  ].join(',');
}
