/**
 * Depth map: one cell per zone (54 x 42), coloured by depth or reflectance,
 * shown as seen from behind the sensor. Hover a cell for its values.
 * Optional smoothing: bilinear interpolation between valid zones.
 */
import { LIDAR_H, LIDAR_W, type LidarFrame } from '../../processing/lidar';
import { TURBO_LUT, autoRange } from '../colormap';
import { displayGrid, inRange, type LidarViewSettings } from './common';

const INVALID = [226, 232, 240]; // slate-200
const SMOOTH_SCALE = 8;          // interpolated pixels per zone when smoothing

export class DepthMapView {
  private readonly ctx: CanvasRenderingContext2D;
  private readonly cells = document.createElement('canvas');
  private readonly cellsCtx: CanvasRenderingContext2D;
  private frame: LidarFrame | null = null;
  private range: [number, number] = [0, 1];
  private hover: { u: number; v: number } | null = null;
  private layout = { x: 0, y: 0, cell: 1, dw: LIDAR_W, dh: LIDAR_H };
  private dirty = true;

  constructor(private readonly canvas: HTMLCanvasElement, private readonly settings: LidarViewSettings) {
    this.ctx = canvas.getContext('2d')!;
    this.cellsCtx = this.cells.getContext('2d')!;
    canvas.addEventListener('mousemove', (e) => {
      const r = canvas.getBoundingClientRect();
      const px = (e.clientX - r.left) * devicePixelRatio, py = (e.clientY - r.top) * devicePixelRatio;
      const { x, y, cell, dw, dh } = this.layout;
      const u = Math.floor((px - x) / cell), v = Math.floor((py - y) / cell);
      this.hover = u >= 0 && v >= 0 && u < dw && v < dh ? { u, v } : null;
      this.dirty = true;
    });
    canvas.addEventListener('mouseleave', () => { this.hover = null; this.dirty = true; });
    new ResizeObserver(() => (this.dirty = true)).observe(canvas);
  }

  setFrame(f: LidarFrame | null): void {
    this.frame = f;
    this.dirty = true;
  }

  invalidate(): void {
    this.dirty = true;
  }

  render(): void {
    if (!this.dirty) return;
    this.dirty = false;
    const c = this.canvas;
    c.width = Math.max(1, Math.round(c.clientWidth * devicePixelRatio));
    c.height = Math.max(1, Math.round(c.clientHeight * devicePixelRatio));
    const ctx = this.ctx;
    ctx.clearRect(0, 0, c.width, c.height);

    const f = this.frame;
    if (!f) return; // the card's overlay explains why

    const s = this.settings;
    const values = s.colorMode === 'depth' ? f.depth : f.reflectance;
    this.range = s.colorMode === 'depth' && s.maxRangeMm > 0 ? [0, s.maxRangeMm] : autoRange(values);
    const [lo, hi] = this.range;

    // Values in display order (dw x dh), NaN = invalid zone.
    const grid = displayGrid(s.mirrorH, s.mirrorV, LIDAR_W, LIDAR_H);
    const dw = grid.width, dh = grid.height;
    const disp = new Float32Array(dw * dh);
    for (let row = 0; row < LIDAR_H; row++) {
      for (let col = 0; col < LIDAR_W; col++) {
        const [u, v] = grid.map(col, row);
        const i = row * LIDAR_W + col;
        disp[v * dw + u] = inRange(f.depth[i]!, s) ? values[i]! : NaN;  // beyond Max range: hidden
      }
    }

    // Smooth: bilinear interpolation at SMOOTH_SCALE x, using valid zones only
    // (invalid neighbours drop out of the weights instead of bleeding grey in).
    const scale = s.smooth ? SMOOTH_SCALE : 1;
    const iw = dw * scale, ih = dh * scale;
    this.cells.width = iw;
    this.cells.height = ih;
    const img = this.cellsCtx.createImageData(iw, ih);
    const put = (o: number, val: number) => {
      if (Number.isFinite(val)) {
        const k = Math.round(Math.min(1, Math.max(0, (val - lo) / (hi - lo))) * 255) * 3;
        img.data[o] = TURBO_LUT[k]!; img.data[o + 1] = TURBO_LUT[k + 1]!; img.data[o + 2] = TURBO_LUT[k + 2]!;
      } else {
        img.data[o] = INVALID[0]!; img.data[o + 1] = INVALID[1]!; img.data[o + 2] = INVALID[2]!;
      }
      img.data[o + 3] = 255;
    };
    if (scale === 1) {
      for (let i = 0; i < dw * dh; i++) put(i * 4, disp[i]!);
    } else {
      for (let py = 0; py < ih; py++) {
        const gy = (py + 0.5) / scale - 0.5;
        const y0 = Math.max(0, Math.min(dh - 1, Math.floor(gy))), y1 = Math.min(dh - 1, y0 + 1);
        const fy = Math.min(1, Math.max(0, gy - y0));
        for (let px = 0; px < iw; px++) {
          const gx = (px + 0.5) / scale - 0.5;
          const x0 = Math.max(0, Math.min(dw - 1, Math.floor(gx))), x1 = Math.min(dw - 1, x0 + 1);
          const fx = Math.min(1, Math.max(0, gx - x0));
          let sum = 0, wsum = 0, v: number, w: number;
          v = disp[y0 * dw + x0]!; w = (1 - fx) * (1 - fy); if (w > 0 && v === v) { sum += v * w; wsum += w; }
          v = disp[y0 * dw + x1]!; w = fx * (1 - fy);       if (w > 0 && v === v) { sum += v * w; wsum += w; }
          v = disp[y1 * dw + x0]!; w = (1 - fx) * fy;       if (w > 0 && v === v) { sum += v * w; wsum += w; }
          v = disp[y1 * dw + x1]!; w = fx * fy;             if (w > 0 && v === v) { sum += v * w; wsum += w; }
          // Edges: fade the colour into the background by how much valid data is
          // around (anti-aliased outline); holes keep their shape.
          const o = (py * iw + px) * 4;
          if (wsum <= 0) { put(o, NaN); continue; }
          put(o, sum / wsum);
          const t = Math.min(1, Math.max(0, (wsum - 0.3) / 0.4));
          const a = t * t * (3 - 2 * t); // smoothstep
          if (a < 1) {
            img.data[o] = Math.round(img.data[o]! * a + INVALID[0]! * (1 - a));
            img.data[o + 1] = Math.round(img.data[o + 1]! * a + INVALID[1]! * (1 - a));
            img.data[o + 2] = Math.round(img.data[o + 2]! * a + INVALID[2]! * (1 - a));
          }
        }
      }
    }
    this.cellsCtx.putImageData(img, 0, 0);

    // Fit, keeping square cells; leave room for the colour bar on the right.
    const bar = 70 * devicePixelRatio;
    const cell = Math.max(1, Math.floor(Math.min((c.width - bar) / grid.width, c.height / grid.height)));
    const x = Math.floor((c.width - bar - cell * grid.width) / 2);
    const y = Math.floor((c.height - cell * grid.height) / 2);
    this.layout = { x, y, cell, dw: grid.width, dh: grid.height };
    ctx.imageSmoothingEnabled = s.smooth;
    ctx.drawImage(this.cells, x, y, cell * grid.width, cell * grid.height);

    this.drawColorBar(x + cell * grid.width + 16 * devicePixelRatio, y, cell * grid.height);
    if (this.hover) this.drawHover(grid, values);
  }

  private drawColorBar(x: number, y: number, h: number): void {
    const ctx = this.ctx, dpr = devicePixelRatio, w = 12 * dpr;
    for (let i = 0; i < h; i++) {
      const k = Math.round((1 - i / h) * 255) * 3;
      ctx.fillStyle = `rgb(${TURBO_LUT[k]},${TURBO_LUT[k + 1]},${TURBO_LUT[k + 2]})`;
      ctx.fillRect(x, y + i, w, 1);
    }
    ctx.fillStyle = '#334155';
    ctx.font = `${11 * dpr}px system-ui, sans-serif`;
    ctx.textBaseline = 'middle';
    const [lo, hi] = this.range;
    const fmt = (v: number) => (this.settings.colorMode === 'depth' ? `${(v / 1000).toFixed(2)} m` : v.toFixed(1));
    ctx.fillText(fmt(hi), x + w + 4 * dpr, y + 6 * dpr);
    ctx.fillText(fmt(lo), x + w + 4 * dpr, y + h - 6 * dpr);
  }

  private drawHover(grid: ReturnType<typeof displayGrid>, values: Float32Array): void {
    const f = this.frame!;
    const { u, v } = this.hover!;
    // Find the zone shown at (u, v).
    let zone = -1;
    for (let row = 0; row < LIDAR_H && zone < 0; row++) {
      for (let col = 0; col < LIDAR_W; col++) {
        const [uu, vv] = grid.map(col, row);
        if (uu === u && vv === v) { zone = row * LIDAR_W + col; break; }
      }
    }
    if (zone < 0) return;
    const { x, y, cell } = this.layout;
    const ctx = this.ctx, dpr = devicePixelRatio;
    ctx.strokeStyle = '#0f172a';
    ctx.lineWidth = 2 * dpr;
    ctx.strokeRect(x + u * cell, y + v * cell, cell, cell);

    const d = f.depth[zone]!;
    const lines = [
      `zone ${zone % LIDAR_W}, ${Math.floor(zone / LIDAR_W)}`,
      Number.isFinite(d) ? `depth ${(d / 1000).toFixed(3)} m` : `invalid (status ${f.status[zone]})`,
      Number.isFinite(values[zone]!) && this.settings.colorMode === 'reflectance'
        ? `reflectance ${f.reflectance[zone]!.toFixed(1)}` : '',
    ].filter(Boolean);
    ctx.font = `${12 * dpr}px system-ui, sans-serif`;
    const tw = Math.max(...lines.map((l) => ctx.measureText(l).width)) + 12 * dpr;
    const th = lines.length * 16 * dpr + 8 * dpr;
    let tx = x + (u + 1) * cell + 8 * dpr, ty = y + v * cell;
    if (tx + tw > this.canvas.width) tx = x + u * cell - tw - 8 * dpr;
    if (ty + th > this.canvas.height) ty = this.canvas.height - th;
    ctx.fillStyle = 'rgba(255,255,255,0.95)';
    ctx.strokeStyle = '#cbd5e1';
    ctx.lineWidth = 1;
    ctx.fillRect(tx, ty, tw, th);
    ctx.strokeRect(tx, ty, tw, th);
    ctx.fillStyle = '#0f172a';
    ctx.textBaseline = 'top';
    lines.forEach((l, k) => ctx.fillText(l, tx + 6 * dpr, ty + 4 * dpr + k * 16 * dpr));
  }
}
