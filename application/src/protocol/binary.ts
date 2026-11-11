/**
 * Binary USB protocol v1, mirror of firmware/app/protocol.h (the reference).
 *
 *   sync 0xA5 0x5A | type u8 | version u8 | seq u32 | t_us u64 | length u32 | payload | crc32
 *   (little-endian, CRC-32 over header + payload)
 *
 * PacketParser turns an arbitrary byte stream into verified packets and resyncs
 * after errors; the decoders turn payloads into typed objects.
 */
import { Emitter, type ImuSample, type Vec3 } from '../types';
import { crc32 } from './crc32';

export const PROTO_VERSION = 1;
const SYNC0 = 0xa5;
const SYNC1 = 0x5a;
const HEADER = 20;
const MAX_PAYLOAD = 16384;

export const PKT = {
  INFO: 0x01,
  LOG: 0x02,
  STATUS: 0x03,
  IMU: 0x10,
  LIDAR_FRAME: 0x20,
  LIDAR_CALIB: 0x21,
} as const;

/** Host -> device single-byte commands. */
export const CMD = {
  INFO: 'V',
  CALIB: 'C',
  IMU_ON: 'I',
  IMU_OFF: 'i',
  LIDAR_ON: 'L',
  LIDAR_OFF: 'l',
  ALL_OFF: 'X',
  LED_TOGGLE: 'T',
  LED_AUTO: 'B',
  IMU_REINIT: 'U',
  LIDAR_REINIT: 'R',
} as const;

export interface Packet {
  type: number;
  seq: number;
  /** MCU time, microseconds since boot. */
  tUs: number;
  payload: Uint8Array;
}

export interface ParserStats {
  packets: number;
  bytes: number;
  crcErrors: number;
  seqGaps: number;
  skippedBytes: number;
}

export class PacketParser {
  readonly packets = new Emitter<Packet>();
  stats: ParserStats = { packets: 0, bytes: 0, crcErrors: 0, seqGaps: 0, skippedBytes: 0 };

  private buf = new Uint8Array(65536);
  private len = 0;
  private lastSeq: number | null = null;

  reset(): void {
    this.len = 0;
    this.lastSeq = null;
    this.stats = { packets: 0, bytes: 0, crcErrors: 0, seqGaps: 0, skippedBytes: 0 };
  }

  push(chunk: Uint8Array): void {
    this.stats.bytes += chunk.length;
    if (this.len + chunk.length > this.buf.length) {
      const bigger = new Uint8Array(Math.max(this.buf.length * 2, this.len + chunk.length));
      bigger.set(this.buf.subarray(0, this.len));
      this.buf = bigger;
    }
    this.buf.set(chunk, this.len);
    this.len += chunk.length;
    this.drain();
  }

  private drain(): void {
    const b = this.buf;
    let pos = 0;
    while (this.len - pos >= HEADER) {
      if (b[pos] !== SYNC0 || b[pos + 1] !== SYNC1) {
        pos++;
        this.stats.skippedBytes++;
        continue;
      }
      const view = new DataView(b.buffer, b.byteOffset + pos, HEADER);
      const version = view.getUint8(3);
      const length = view.getUint32(16, true);
      if (version !== PROTO_VERSION || length > MAX_PAYLOAD) {
        pos++;
        this.stats.skippedBytes++;
        continue;
      }
      const total = HEADER + length + 4;
      if (this.len - pos < total) break; // wait for the rest
      const crc = new DataView(b.buffer, b.byteOffset + pos + total - 4, 4).getUint32(0, true);
      if (crc32(b, pos, pos + total - 4) !== crc) {
        this.stats.crcErrors++;
        pos++;
        continue;
      }
      const seq = view.getUint32(4, true);
      if (this.lastSeq !== null && seq !== ((this.lastSeq + 1) >>> 0)) this.stats.seqGaps++;
      this.lastSeq = seq;
      this.stats.packets++;
      const tUs = view.getUint32(8, true) + view.getUint32(12, true) * 2 ** 32;
      this.packets.emit({ type: view.getUint8(2), seq, tUs, payload: b.slice(pos + HEADER, pos + HEADER + length) });
      pos += total;
    }
    if (pos > 0) {
      b.copyWithin(0, pos, this.len);
      this.len -= pos;
    }
  }
}

/** Builds the wire bytes of a packet (used to put calibration/info at the start of recordings). */
export function encodePacket(type: number, seq: number, tUs: number, payload: Uint8Array): Uint8Array {
  const out = new Uint8Array(HEADER + payload.length + 4);
  const v = new DataView(out.buffer);
  out[0] = SYNC0;
  out[1] = SYNC1;
  v.setUint8(2, type);
  v.setUint8(3, PROTO_VERSION);
  v.setUint32(4, seq >>> 0, true);
  v.setUint32(8, tUs % 2 ** 32, true);
  v.setUint32(12, Math.floor(tUs / 2 ** 32), true);
  v.setUint32(16, payload.length, true);
  out.set(payload, HEADER);
  v.setUint32(HEADER + payload.length, crc32(out, 0, HEADER + payload.length), true);
  return out;
}

// ------------------------------------------------------------------ decoders

const text = new TextDecoder();

export function decodeText(p: Packet): string {
  return text.decode(p.payload);
}

/** PKT_INFO "key=value" lines. */
export function decodeInfo(p: Packet): Record<string, string> {
  const info: Record<string, string> = {};
  for (const line of decodeText(p).split('\n')) {
    const i = line.indexOf('=');
    if (i > 0) info[line.slice(0, i)] = line.slice(i + 1);
  }
  return info;
}

/** proto_imu_t (32 bytes). */
export function decodeImu(p: Packet): ImuSample {
  const v = new DataView(p.payload.buffer, p.payload.byteOffset, p.payload.byteLength);
  const f = (o: number) => v.getFloat32(o, true);
  return {
    seq: v.getUint32(0, true),
    tMs: p.tUs / 1000,
    accelMg: [f(4), f(8), f(12)] as Vec3,
    gyroMdps: [f(16), f(20), f(24)] as Vec3,
    tempC: f(28),
  };
}

export interface DeviceStatus {
  imuVariant: number;
  imuWhoami: number;
  imuStreaming: boolean;
  lidarState: number;   // 0 off, 1 ready, 2 streaming, 3 error
  lidarBus: number;     // 0 none, 1 soft I2C, 2 I3C
  ledMode: number;
  lidarBusHz: number;
  lidarFrames: number;
  lidarDropped: number;
  lidarErrors: number;
  lidarLastError: number;
  imuSamples: number;
  txDropped: number;
}

export const LIDAR_STATE_NAMES = ['off', 'ready', 'streaming', 'error'] as const;
export const LIDAR_BUS_NAMES = ['none', 'I²C (soft)', 'I3C'] as const;

/** proto_status_t (36 bytes). */
export function decodeStatus(p: Packet): DeviceStatus {
  const v = new DataView(p.payload.buffer, p.payload.byteOffset, p.payload.byteLength);
  return {
    imuVariant: v.getUint8(0),
    imuWhoami: v.getUint8(1),
    imuStreaming: v.getUint8(2) !== 0,
    lidarState: v.getUint8(3),
    lidarBus: v.getUint8(4),
    ledMode: v.getUint8(5),
    lidarBusHz: v.getUint32(8, true),
    lidarFrames: v.getUint32(12, true),
    lidarDropped: v.getUint32(16, true),
    lidarErrors: v.getUint32(20, true),
    lidarLastError: v.getInt32(24, true),
    imuSamples: v.getUint32(28, true),
    txDropped: v.getUint32(32, true),
  };
}

export interface LidarRaw {
  frame: number;
  tUs: number;
  width: number;
  height: number;
  raw: Uint8Array;
}

/** proto_lidar_frame_t (12 bytes) + raw ST frame. */
export function decodeLidarFrame(p: Packet): LidarRaw {
  const v = new DataView(p.payload.buffer, p.payload.byteOffset, 12);
  const rawSize = v.getUint32(8, true);
  return {
    frame: v.getUint32(0, true),
    tUs: p.tUs,
    width: v.getUint16(4, true),
    height: v.getUint16(6, true),
    raw: p.payload.subarray(12, 12 + rawSize),
  };
}
