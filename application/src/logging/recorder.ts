/**
 * Records a live session as two files:
 *  - session-<time>.bin: every byte received from the device (binary protocol,
 *    protocol/binary.ts), starting with the device info and LiDAR calibration so
 *    the file replays on its own (IMU + LiDAR);
 *  - imu-<time>.csv: the IMU samples in the human-readable CSV format.
 */
import type { ImuSample } from '../types';
import { CSV_HEADER, formatSample } from '../protocol/csv';

export class Recorder {
  private chunks: Uint8Array[] = [];
  private bytes = 0;
  private csv: string[] = [];
  private startedAt: Date | null = null;

  get recording(): boolean {
    return this.startedAt !== null;
  }

  get sizeBytes(): number {
    return this.bytes;
  }

  get imuCount(): number {
    return this.csv.length;
  }

  /** prelude: packets to put first (e.g. info + calibration received earlier). */
  start(prelude: Uint8Array[]): void {
    this.chunks = [];
    this.bytes = 0;
    this.csv = [];
    this.startedAt = new Date();
    for (const p of prelude) this.addBytes(p);
  }

  /** Raw bytes as received from the device. */
  addBytes(chunk: Uint8Array): void {
    if (!this.startedAt) return;
    this.chunks.push(chunk.slice());
    this.bytes += chunk.length;
  }

  addImu(s: ImuSample): void {
    if (this.startedAt) this.csv.push(formatSample(s));
  }

  /** Stops and downloads the files. Returns a short summary. */
  stopAndDownload(deviceInfo: string): string {
    const started = this.startedAt;
    this.startedAt = null;
    if (!started) return 'not recording';
    const stamp = started.toISOString().replace(/[:.]/g, '-').slice(0, 19);

    download(new Blob(this.chunks as BlobPart[], { type: 'application/octet-stream' }), `session-${stamp}.bin`);
    if (this.csv.length > 0) {
      const content = [
        '# USB LiDAR & IMU recording (IMU, raw sensor frame)',
        `# started ${started.toISOString()}`,
        `# device ${deviceInfo}`,
        CSV_HEADER,
        ...this.csv,
        '',
      ].join('\n');
      download(new Blob([content], { type: 'text/csv' }), `imu-${stamp}.csv`);
    }
    const summary = `${(this.bytes / 1e6).toFixed(1)} MB session, ${this.csv.length} IMU samples`;
    this.chunks = [];
    this.csv = [];
    return summary;
  }
}

function download(blob: Blob, name: string): void {
  const url = URL.createObjectURL(blob);
  const a = document.createElement('a');
  a.href = url;
  a.download = name;
  a.click();
  setTimeout(() => URL.revokeObjectURL(url), 1000);
}
