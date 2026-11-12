/**
 * Replays a recording in (scaled) real time, emitting the same things the live
 * device produces, so all processing and views work unchanged:
 *  - session-*.bin: binary protocol packets (IMU, LiDAR, calibration, info, ...)
 *  - imu-*.csv: IMU samples only
 */
import { Emitter, type ImuSample } from '../types';
import { parseLine } from '../protocol/csv';
import { PacketParser, type Packet } from '../protocol/binary';

export type PlaybackState = 'empty' | 'paused' | 'playing' | 'ended';

type Item = { tMs: number; packet?: Packet; imu?: ImuSample };

export class Playback {
  readonly packets = new Emitter<Packet>();
  readonly samples = new Emitter<ImuSample>();
  readonly state = new Emitter<PlaybackState>();
  readonly progress = new Emitter<number>(); // 0..1

  speed = 1;
  fileName = '';
  kind: 'session' | 'csv' = 'session';
  private items: Item[] = [];
  private index = 0;
  private playTimeMs = 0;
  private lastFrame = 0;
  private raf = 0;
  private current: PlaybackState = 'empty';

  get length(): number {
    return this.items.length;
  }

  get durationMs(): number {
    const first = this.items[0], last = this.items[this.items.length - 1];
    return first && last ? last.tMs - first.tMs : 0;
  }

  /** Returns a short description of what was loaded. */
  async load(file: File): Promise<string> {
    this.stop();
    const bytes = new Uint8Array(await file.arrayBuffer());
    this.items = [];
    if (bytes[0] === 0xa5 && bytes[1] === 0x5a) {
      this.kind = 'session';
      const parser = new PacketParser();
      const counts = new Map<number, number>();
      parser.packets.on((p) => {
        this.items.push({ tMs: p.tUs / 1000, packet: p });
        counts.set(p.type, (counts.get(p.type) ?? 0) + 1);
      });
      parser.push(bytes);
      // The recorder puts info + calibration (received earlier, possibly minutes
      // before) at the start: replay them right at the first data packet.
      const firstData = this.items.find((it) => it.packet!.type === 0x10 || it.packet!.type === 0x20);
      if (firstData) for (const it of this.items) if (it.tMs < firstData.tMs) it.tMs = firstData.tMs;
      this.items.sort((a, b) => a.tMs - b.tMs);
      const frames = counts.get(0x20) ?? 0, imu = counts.get(0x10) ?? 0;
      this.fileName = file.name;
      this.rewind();
      this.setState(this.items.length > 0 ? 'paused' : 'empty');
      return `${frames} LiDAR frames, ${imu} IMU samples, ${(this.durationMs / 1000).toFixed(1)} s` +
        (parser.stats.crcErrors ? `, ${parser.stats.crcErrors} CRC errors skipped` : '');
    }
    this.kind = 'csv';
    for (const line of new TextDecoder().decode(bytes).split(/\r?\n/)) {
      const p = parseLine(line);
      if (p.kind === 'imu') this.items.push({ tMs: p.sample.tMs, imu: p.sample });
    }
    this.fileName = file.name;
    this.rewind();
    this.setState(this.items.length > 0 ? 'paused' : 'empty');
    return `${this.items.length} IMU samples, ${(this.durationMs / 1000).toFixed(1)} s`;
  }

  play(): void {
    if (this.items.length === 0) return;
    if (this.current === 'ended') this.rewind();
    this.lastFrame = performance.now();
    this.setState('playing');
    this.raf = requestAnimationFrame(this.tick);
  }

  pause(): void {
    if (this.current !== 'playing') return;
    cancelAnimationFrame(this.raf);
    this.setState('paused');
  }

  stop(): void {
    cancelAnimationFrame(this.raf);
    this.rewind();
    if (this.items.length > 0) this.setState('paused');
  }

  private rewind(): void {
    this.index = 0;
    this.playTimeMs = 0;
    this.progress.emit(0);
  }

  private readonly tick = (now: number): void => {
    // rAF timestamps can be slightly older than the performance.now() taken in play().
    this.playTimeMs += Math.max(0, now - this.lastFrame) * this.speed;
    this.lastFrame = now;

    const t0 = this.items[0]!.tMs;
    while (this.index < this.items.length && this.items[this.index]!.tMs - t0 <= this.playTimeMs) {
      const it = this.items[this.index]!;
      if (it.packet) this.packets.emit(it.packet);
      else if (it.imu) this.samples.emit(it.imu);
      this.index++;
    }
    this.progress.emit(this.durationMs > 0 ? Math.min(1, this.playTimeMs / this.durationMs) : 1);

    if (this.index >= this.items.length) {
      this.setState('ended');
      return;
    }
    this.raf = requestAnimationFrame(this.tick);
  };

  private setState(s: PlaybackState): void {
    this.current = s;
    this.state.emit(s);
  }
}
