/** Stream health: sample rate (host clock) and dropped samples (sequence gaps). */
import type { ImuSample } from '../types';

export class StreamStats {
  received = 0;
  dropped = 0;
  rateHz = 0;

  private lastSeq: number | null = null;
  private windowStart = performance.now();
  private windowCount = 0;

  reset(): void {
    this.received = 0;
    this.dropped = 0;
    this.rateHz = 0;
    this.lastSeq = null;
    this.windowStart = performance.now();
    this.windowCount = 0;
  }

  feed(s: ImuSample): void {
    this.received++;
    if (this.lastSeq !== null) {
      if (s.seq > this.lastSeq + 1) this.dropped += s.seq - this.lastSeq - 1;
      // s.seq <= lastSeq: firmware restarted the stream; not a drop.
    }
    this.lastSeq = s.seq;

    this.windowCount++;
    const now = performance.now();
    const elapsed = now - this.windowStart;
    if (elapsed >= 1000) {
      this.rateHz = (this.windowCount * 1000) / elapsed;
      this.windowStart = now;
      this.windowCount = 0;
    }
  }
}
