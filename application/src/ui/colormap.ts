/** Colour maps for LiDAR views. */

/** Google "Turbo" (polynomial approximation), t in [0, 1] -> [r, g, b] in [0, 255]. */
export function turbo(t: number): [number, number, number] {
  const x = Math.min(1, Math.max(0, t));
  const r = 0.13572138 + x * (4.6153926 + x * (-42.66032258 + x * (132.13108234 + x * (-152.94239396 + x * 59.28637943))));
  const g = 0.09140261 + x * (2.19418839 + x * (4.84296658 + x * (-14.18503333 + x * (4.27729857 + x * 2.82956604))));
  const b = 0.1066733 + x * (12.64194608 + x * (-60.58204836 + x * (110.36276771 + x * (-89.90310912 + x * 27.34824973))));
  return [clamp255(r), clamp255(g), clamp255(b)];
}

function clamp255(v: number): number {
  return Math.round(Math.min(1, Math.max(0, v)) * 255);
}

/** 256-entry lookup table for fast per-zone colouring. */
export const TURBO_LUT: Uint8Array = (() => {
  const lut = new Uint8Array(256 * 3);
  for (let i = 0; i < 256; i++) lut.set(turbo(i / 255), i * 3);
  return lut;
})();

/** Robust display range: 2nd..98th percentile of the finite values. */
export function autoRange(values: Float32Array): [number, number] {
  const v: number[] = [];
  for (const x of values) if (Number.isFinite(x)) v.push(x);
  if (v.length === 0) return [0, 1];
  v.sort((a, b) => a - b);
  const lo = v[Math.floor(v.length * 0.02)]!;
  const hi = v[Math.min(v.length - 1, Math.floor(v.length * 0.98))]!;
  return hi > lo ? [lo, hi] : [lo, lo + 1];
}
