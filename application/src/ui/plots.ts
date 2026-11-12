/** Rolling time-series plot of a 3-axis quantity (uPlot). */
import uPlot from 'uplot';
import 'uplot/dist/uPlot.min.css';
import type { Vec3 } from '../types';

const AXIS_COLORS = ['#dc2626', '#16a34a', '#2563eb']; // X red, Y green, Z blue
const AXIS_STYLE = { stroke: '#475569', grid: { stroke: '#e2e8f0' }, ticks: { stroke: '#cbd5e1' } };

export class RollingPlot {
  private readonly plot: uPlot;
  private readonly t: number[] = [];
  private readonly v: [number[], number[], number[]] = [[], [], []];
  private dirty = false;

  constructor(
    container: HTMLElement,
    unit: string,
    private readonly windowSec = 10,
  ) {
    const opts: uPlot.Options = {
      width: container.clientWidth || 600,
      height: 220,
      legend: { show: true, live: true },
      cursor: { drag: { x: false, y: false } },
      scales: {
        x: {
          time: false,
          range: (_u, _min, max) => [max - this.windowSec, max],
        },
      },
      axes: [
        { label: 'MCU time [s]', ...AXIS_STYLE },
        { label: unit, ...AXIS_STYLE, size: 60 },
      ],
      series: [
        { label: 't' },
        ...(['X', 'Y', 'Z'] as const).map((label, i) => ({
          label,
          stroke: AXIS_COLORS[i],
          width: 1.5,
          points: { show: false },
        })),
      ],
    };
    this.plot = new uPlot(opts, [[], [], [], []], container);
    new ResizeObserver(() => {
      this.plot.setSize({ width: container.clientWidth, height: 220 });
    }).observe(container);
  }

  push(tSec: number, value: Vec3): void {
    this.t.push(tSec);
    for (let i = 0; i < 3; i++) this.v[i]!.push(value[i]!);

    // Drop points that scrolled out of the window (in batches, cheap).
    const cutoff = tSec - this.windowSec;
    if (this.t.length > 64 && this.t[63]! < cutoff) {
      let n = 0;
      while (n < this.t.length && this.t[n]! < cutoff) n++;
      this.t.splice(0, n);
      for (const arr of this.v) arr.splice(0, n);
    }
    this.dirty = true;
  }

  clear(): void {
    this.t.length = 0;
    for (const arr of this.v) arr.length = 0;
    this.dirty = true;
  }

  /** Call once per animation frame; redraws only when new data arrived. */
  render(): void {
    if (!this.dirty) return;
    this.dirty = false;
    this.plot.setData([this.t, this.v[0], this.v[1], this.v[2]]);
  }
}
