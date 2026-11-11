/**
 * LiDAR processing: raw VL53L9 frames -> per-zone 3D points, with ST's transform
 * library compiled to WebAssembly (wasm/l9_bridge.c, `npm run build-wasm`).
 * Uses the connected sensor's own calibration (PKT_LIDAR_CALIB); bit-identical to
 * ST's native build.
 *
 * ST output (camera frame): x right, y down, z forward along the optical axis, mm.
 * Zone i = row * 54 + col; row 0 is the top of the sensor image.
 */
import wasmUrl from './wasm/vl53l9.wasm?url';
import type { LidarRaw } from '../protocol/binary';
import { lidarToBoard } from './mounting';

export const LIDAR_W = 54;
export const LIDAR_H = 42;
export const ZONES = LIDAR_W * LIDAR_H;
const RAW_SIZE = 14842;
const CALIB_SIZE = 2332;

export interface LidarFrame {
  frame: number;
  tMs: number;
  /** Zone positions in the board frame (mm): X right, Y towards LiDAR, Z view direction. */
  board: Float32Array;   // ZONES * 3
  /** Distance along the optical axis (mm), NaN when invalid. */
  depth: Float32Array;   // ZONES
  /** ST reflectance estimate (relative), NaN when invalid. */
  reflectance: Float32Array;
  /** ST filter status per zone: 0 = valid. */
  status: Uint32Array;
  validCount: number;
  minMm: number;
  medianMm: number;
  maxMm: number;
  processMs: number;
}

interface Exports {
  memory: WebAssembly.Memory;
  _initialize?: () => void;
  l9_alloc(size: number): number;
  l9_free(ptr: number): void;
  l9_create(cal: number, len: number, temporal: number): number;
  l9_destroy(handle: number): void;
  l9_process(handle: number, raw: number, len: number, xyzc: number, status: number, refl: number): number;
}

export class LidarProcessor {
  private handle = 0;
  private calibration: Uint8Array | null = null;
  private temporal = false;
  private lastFrame: number | null = null;
  private readonly pRaw: number;
  private readonly pCal: number;
  private readonly pXyzc: number;
  private readonly pStatus: number;
  private readonly pRefl: number;

  /** Image mirroring on top of the PCB orientation (see mounting.ts). */
  mirrorH = false;
  mirrorV = false;

  private constructor(private readonly e: Exports) {
    this.pRaw = e.l9_alloc(RAW_SIZE);
    this.pCal = e.l9_alloc(CALIB_SIZE);
    this.pXyzc = e.l9_alloc(ZONES * 16);
    this.pStatus = e.l9_alloc(ZONES * 4);
    this.pRefl = e.l9_alloc(ZONES * 4);
  }

  static async load(): Promise<LidarProcessor> {
    const { instance } = await WebAssembly.instantiateStreaming(fetch(wasmUrl), {});
    const e = instance.exports as unknown as Exports;
    e._initialize?.();
    return new LidarProcessor(e);
  }

  get hasCalibration(): boolean {
    return this.handle !== 0;
  }

  setCalibration(cal: Uint8Array): void {
    if (cal.length !== CALIB_SIZE) throw new Error(`calibration is ${cal.length} bytes, expected ${CALIB_SIZE}`);
    this.calibration = cal.slice();
    this.recreate();
  }

  /** ST temporal noise reduction: smoother, slightly laggy; needs consecutive frames. */
  setTemporal(on: boolean): void {
    this.temporal = on;
    if (this.calibration) this.recreate();
  }

  private recreate(): void {
    if (this.handle) this.e.l9_destroy(this.handle);
    this.handle = 0;
    this.lastFrame = null;
    if (!this.calibration) return;
    new Uint8Array(this.e.memory.buffer, this.pCal, CALIB_SIZE).set(this.calibration);
    this.handle = this.e.l9_create(this.pCal, CALIB_SIZE, this.temporal ? 1 : 0);
    if (!this.handle) throw new Error('ST transform rejected the calibration');
  }

  process(f: LidarRaw): LidarFrame {
    if (!this.handle) throw new Error('no calibration');
    if (f.raw.length !== RAW_SIZE) throw new Error(`raw frame is ${f.raw.length} bytes`);
    // Temporal filtering assumes consecutive frames: restart it after a gap.
    if (this.temporal && this.lastFrame !== null && f.frame !== this.lastFrame + 1) this.recreate();
    this.lastFrame = f.frame;

    const t0 = performance.now();
    const mem = this.e.memory.buffer;
    new Uint8Array(mem, this.pRaw, RAW_SIZE).set(f.raw);
    const rc = this.e.l9_process(this.handle, this.pRaw, RAW_SIZE, this.pXyzc, this.pStatus, this.pRefl);
    if (rc !== 0) {
      this.recreate();
      throw new Error(`ST transform failed (${rc})`);
    }
    const buf = this.e.memory.buffer; // may have grown
    const xyzc = new Float32Array(buf, this.pXyzc, ZONES * 4);
    const status = new Uint32Array(buf, this.pStatus, ZONES).slice();
    const refl = new Float32Array(buf, this.pRefl, ZONES);

    const board = new Float32Array(ZONES * 3);
    const depth = new Float32Array(ZONES).fill(NaN);
    const reflectance = new Float32Array(ZONES).fill(NaN);
    const valid: number[] = [];
    const toBoard = lidarToBoard(this.mirrorH, this.mirrorV);
    for (let i = 0; i < ZONES; i++) {
      const x = xyzc[i * 4]!, y = xyzc[i * 4 + 1]!, z = xyzc[i * 4 + 2]!;
      if (status[i] === 0 && Number.isFinite(z) && z > 0) {
        depth[i] = z;
        reflectance[i] = refl[i]!;
        valid.push(z);
        toBoard(x, y, z, board, i * 3);
      } else {
        board[i * 3] = board[i * 3 + 1] = board[i * 3 + 2] = NaN;
      }
    }
    valid.sort((a, b) => a - b);
    return {
      frame: f.frame,
      tMs: f.tUs / 1000,
      board, depth, reflectance, status,
      validCount: valid.length,
      minMm: valid[0] ?? NaN,
      medianMm: valid[valid.length >> 1] ?? NaN,
      maxMm: valid[valid.length - 1] ?? NaN,
      processMs: performance.now() - t0,
    };
  }
}
