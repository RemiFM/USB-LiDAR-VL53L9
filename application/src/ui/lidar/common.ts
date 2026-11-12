/** Shared settings for the LiDAR views. */
export type ColorMode = 'depth' | 'reflectance';

export interface LidarViewSettings {
  colorMode: ColorMode;
  /** Maximum distance (mm): zones further away are hidden in all views and the depth
   *  colour scale runs 0..max. 0 = no limit, automatic colour scale (2nd..98th pct). */
  maxRangeMm: number;
  /** Mirror the LiDAR image horizontally / vertically (see processing/mounting.ts). */
  mirrorH: boolean;
  mirrorV: boolean;
  /** Depth map: bilinear interpolation between valid zones instead of sharp cells. */
  smooth: boolean;
}

/** True if zone i is valid and within the Max range setting. */
export function inRange(depthMm: number, s: LidarViewSettings): boolean {
  return Number.isFinite(depthMm) && (s.maxRangeMm <= 0 || depthMm <= s.maxRangeMm);
}

/**
 * Display mapping for 2D views "as seen from behind the sensor": board +Y up,
 * board +X to the left (the sensor looks away from the viewer along board +Z).
 * With the default orientation that is the sensor image as-is; the mirror
 * settings flip it. Returns the grid size and zone (col, row) -> display (u, v).
 */
export function displayGrid(mirrorH: boolean, mirrorV: boolean, w: number, h: number) {
  return {
    width: w,
    height: h,
    map(col: number, row: number): [number, number] {
      return [mirrorH ? w - 1 - col : col, mirrorV ? h - 1 - row : row];
    },
  };
}
