/**
 * Top view: bird's-eye projection of the zones in the board frame.
 * Up = board +Z (LiDAR view direction), left = board +X (seen from behind the
 * sensor, same as the depth map). Range rings, FoV wedge, sensor at the bottom.
 */
import { ZONES, type LidarFrame } from '../../processing/lidar';
import { TURBO_LUT, autoRange } from '../colormap';
import { inRange, type LidarViewSettings } from './common';

export class TopView {
  private readonly ctx: CanvasRenderingContext2D;
  private frame: LidarFrame | null = null;
  private dirty = true;

  constructor(private readonly canvas: HTMLCanvasElement, private readonly settings: LidarViewSettings) {
    this.ctx = canvas.getContext('2d')!;
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
    const c = this.canvas, ctx = this.ctx, dpr = devicePixelRatio;
    c.width = Math.max(1, Math.round(c.clientWidth * dpr));
    c.height = Math.max(1, Math.round(c.clientHeight * dpr));
    ctx.clearRect(0, 0, c.width, c.height);
    const f = this.frame;
    if (!f) return; // the card's overlay explains why

    const s = this.settings;
    // Horizontal FoV: 55 deg across the image width (board X).
    const halfFov = (55 / 2) * (Math.PI / 180);
    const rangeMm = s.maxRangeMm > 0 ? s.maxRangeMm : Math.max(500, (Number.isFinite(f.maxMm) ? f.maxMm : 1000) * 1.1);

    // Fit the FoV wedge (width 2*R*sin, height R) into the canvas.
    const pad = 24 * dpr;
    const scale = Math.min((c.height - 2 * pad) / rangeMm, (c.width - 2 * pad) / (2 * rangeMm * Math.sin(halfFov) + 1));
    const ox = c.width / 2, oy = c.height - pad;
    const px = (xMm: number) => ox - xMm * scale;   // board +X to the left
    const py = (zMm: number) => oy - zMm * scale;

    // Range rings + labels.
    const step = niceStep(rangeMm / 4);
    ctx.lineWidth = 1;
    ctx.font = `${11 * dpr}px system-ui, sans-serif`;
    ctx.textBaseline = 'bottom';
    for (let r = step; r <= rangeMm * 1.001; r += step) {
      ctx.strokeStyle = '#e2e8f0';
      ctx.beginPath();
      ctx.arc(ox, oy, r * scale, -Math.PI / 2 - halfFov - 0.15, -Math.PI / 2 + halfFov + 0.15);
      ctx.stroke();
      ctx.fillStyle = '#94a3b8';
      ctx.fillText(`${(r / 1000).toFixed(r < 1000 ? 2 : 1)} m`, ox + 4 * dpr, py(r) - 2 * dpr);
    }
    // FoV wedge.
    ctx.strokeStyle = '#7dd3fc';
    ctx.beginPath();
    ctx.moveTo(ox, oy);
    ctx.lineTo(ox - Math.sin(halfFov) * rangeMm * scale, oy - Math.cos(halfFov) * rangeMm * scale);
    ctx.moveTo(ox, oy);
    ctx.lineTo(ox + Math.sin(halfFov) * rangeMm * scale, oy - Math.cos(halfFov) * rangeMm * scale);
    ctx.stroke();

    // Points.
    const values = s.colorMode === 'depth' ? f.depth : f.reflectance;
    const [lo, hi] = s.colorMode === 'depth' && s.maxRangeMm > 0 ? [0, s.maxRangeMm] : autoRange(values);
    const r = Math.max(1.5, 2 * dpr);
    for (let i = 0; i < ZONES; i++) {
      const x = f.board[i * 3]!, z = f.board[i * 3 + 2]!;
      if (!Number.isFinite(z) || !inRange(f.depth[i]!, s)) continue;
      const k = Math.round(Math.min(1, Math.max(0, (values[i]! - lo) / (hi - lo))) * 255) * 3;
      ctx.fillStyle = `rgb(${TURBO_LUT[k]},${TURBO_LUT[k + 1]},${TURBO_LUT[k + 2]})`;
      ctx.fillRect(px(x) - r, py(z) - r, 2 * r, 2 * r);
    }

    // Sensor.
    ctx.fillStyle = '#0f172a';
    ctx.fillRect(ox - 6 * dpr, oy - 3 * dpr, 12 * dpr, 6 * dpr);
    ctx.fillStyle = '#64748b';
    ctx.textBaseline = 'top';
    ctx.fillText('+X ←', pad / 2, oy - 14 * dpr);
  }
}

function niceStep(x: number): number {
  const p = 10 ** Math.floor(Math.log10(x));
  const m = x / p;
  return (m < 1.5 ? 1 : m < 3.5 ? 2.5 : m < 7.5 ? 5 : 10) * p;
}
