/**
 * 3D point cloud of the LiDAR zones (Three.js), with the sensor and its FoV.
 *
 * Two modes:
 *  - sensor view (default): camera behind the sensor, looking along board +Z,
 *    board +Y up (same orientation as the depth map);
 *  - level with IMU: the cloud is rotated by the board orientation from the IMU,
 *    so the floor stays horizontal when the board is tilted.
 */
import * as THREE from 'three';
import { OrbitControls } from 'three/examples/jsm/controls/OrbitControls.js';
import { ZONES, type LidarFrame } from '../../processing/lidar';
import type { Quat } from '../../processing/orientation';
import { TURBO_LUT, autoRange } from '../colormap';
import { inRange, type LidarViewSettings } from './common';

const SCALE = 0.01; // scene units per mm (1 unit = 10 cm)

/** Board frame (mm) -> group-local scene coordinates; same axes as the orientation view. */
function b(x: number, y: number, z: number): THREE.Vector3 {
  return new THREE.Vector3(x * SCALE, z * SCALE, -y * SCALE);
}

export class PointCloudView {
  private readonly renderer: THREE.WebGLRenderer;
  private readonly scene = new THREE.Scene();
  private readonly camera = new THREE.PerspectiveCamera(50, 1, 0.01, 500);
  private readonly controls: OrbitControls;
  private readonly group = new THREE.Group();
  private readonly positions = new Float32Array(ZONES * 3);
  private readonly colors = new Float32Array(ZONES * 3);
  private readonly geometry = new THREE.BufferGeometry();
  private readonly points: THREE.Points;
  private readonly sensorView = new THREE.Quaternion();
  private readonly fov = buildFov();
  private frame: LidarFrame | null = null;
  private boardQ: Quat = [1, 0, 0, 0];
  private dirty = true;
  private userMoved = false;   // stop auto-fitting once the user orbits/zooms
  active = false;
  level = false;

  constructor(private readonly container: HTMLElement, private readonly settings: LidarViewSettings) {
    this.renderer = new THREE.WebGLRenderer({ antialias: true, alpha: true });
    this.renderer.setPixelRatio(devicePixelRatio);
    this.renderer.setClearColor(0x000000, 0);
    container.appendChild(this.renderer.domElement);
    this.renderer.domElement.className = 'absolute inset-0 w-full h-full';

    this.controls = new OrbitControls(this.camera, this.renderer.domElement);
    this.controls.addEventListener('change', () => (this.dirty = true));
    this.controls.addEventListener('start', () => (this.userMoved = true));

    this.geometry.setAttribute('position', new THREE.BufferAttribute(this.positions, 3));
    this.geometry.setAttribute('color', new THREE.BufferAttribute(this.colors, 3));
    // Fixed on-screen point size: readable at any zoom level.
    this.points = new THREE.Points(this.geometry, new THREE.PointsMaterial({
      size: 4 * devicePixelRatio, vertexColors: true, sizeAttenuation: false,
    }));
    this.points.frustumCulled = false;
    this.group.add(this.points, buildSensorBody(), this.fov);
    this.scene.add(this.group);
    const grid = new THREE.GridHelper(40, 40, 0xcbd5e1, 0xe5e7eb);
    grid.position.y = -10;
    this.scene.add(grid);

    // Sensor view: board +Z away from the camera, board +Y up.
    // group-local axes are (X, Z, -Y)_board; target is (-X, Y, -Z)_board.
    this.sensorView.setFromRotationMatrix(new THREE.Matrix4().set(
      -1, 0, 0, 0,
      0, 0, -1, 0,
      0, -1, 0, 0,
      0, 0, 0, 1,
    ));
    this.applyOrientation();
    this.resetView();
    new ResizeObserver(() => this.resize()).observe(container);
    this.resize();
  }

  /** Frames the camera on the current data (90th-percentile depth), behind the sensor. */
  resetView(): void {
    this.userMoved = false;
    let d = 1000; // mm, when there is no data yet
    const f = this.frame;
    if (f && f.validCount > 0) {
      const z = Array.from(f.depth).filter(Number.isFinite).sort((a, b) => a - b);
      d = Math.max(300, z[Math.floor(z.length * 0.9)]!);
    }
    const u = d * SCALE;
    this.fov.scale.setScalar(d / 1000);   // FoV frame drawn as deep as the data
    this.camera.position.set(0.35 * u, 0.45 * u, 1.1 * u);
    this.controls.target.set(0, 0, -0.5 * u);
    this.controls.update();
    this.dirty = true;
  }

  setLevel(on: boolean): void {
    this.level = on;
    this.applyOrientation();
  }

  setBoardOrientation(q: Quat): void {
    this.boardQ = q;
    if (this.level) this.applyOrientation();
  }

  setFrame(f: LidarFrame | null): void {
    const first = !this.frame && f;
    this.frame = f;
    this.updatePoints();
    if (first && !this.userMoved) this.resetView();
  }

  invalidate(): void {
    this.updatePoints();
  }

  render(): void {
    if (!this.active || !this.dirty) return;
    this.dirty = false;
    this.renderer.render(this.scene, this.camera);
  }

  private applyOrientation(): void {
    if (this.level) {
      // World (gravity = -Y) <- board: same mapping as the orientation view.
      // Heading is relative (yaw from the IMU); orbit the camera to look around.
      const [w, x, y, z] = this.boardQ;
      const v = b(x, y, z).divideScalar(SCALE);
      this.group.quaternion.set(v.x, v.y, v.z, w);
    } else {
      this.group.quaternion.copy(this.sensorView);
    }
    this.dirty = true;
  }

  private updatePoints(): void {
    const f = this.frame;
    const pos = this.positions, col = this.colors;
    if (!f) {
      this.geometry.setDrawRange(0, 0);
      this.dirty = true;
      return;
    }
    const s = this.settings;
    const values = s.colorMode === 'depth' ? f.depth : f.reflectance;
    const [lo, hi] = s.colorMode === 'depth' && s.maxRangeMm > 0 ? [0, s.maxRangeMm] : autoRange(values);
    let n = 0;
    for (let i = 0; i < ZONES; i++) {
      const z = f.board[i * 3 + 2]!;
      if (!Number.isFinite(z) || !inRange(f.depth[i]!, s)) continue;
      const p = b(f.board[i * 3]!, f.board[i * 3 + 1]!, z);
      pos[n * 3] = p.x; pos[n * 3 + 1] = p.y; pos[n * 3 + 2] = p.z;
      const k = Math.round(Math.min(1, Math.max(0, (values[i]! - lo) / (hi - lo))) * 255) * 3;
      col[n * 3] = TURBO_LUT[k]! / 255; col[n * 3 + 1] = TURBO_LUT[k + 1]! / 255; col[n * 3 + 2] = TURBO_LUT[k + 2]! / 255;
      n++;
    }
    this.geometry.setDrawRange(0, n);
    this.geometry.attributes.position!.needsUpdate = true;
    this.geometry.attributes.color!.needsUpdate = true;
    this.dirty = true;
  }

  private resize(): void {
    const w = this.container.clientWidth || 400, h = this.container.clientHeight || 300;
    this.renderer.setSize(w, h, false);
    this.camera.aspect = w / h;
    this.camera.updateProjectionMatrix();
    this.dirty = true;
  }
}

/** Sensor body (VL53L9 outline, 13.4 x 7.3 mm, drawn at 3x) at the origin. */
function buildSensorBody(): THREE.Mesh {
  return new THREE.Mesh(
    new THREE.BoxGeometry(13.4 * SCALE * 3, 2 * SCALE * 3, 7.3 * SCALE * 3),
    new THREE.MeshBasicMaterial({ color: 0x1f2937 }),
  );
}

/** 55 x 42 deg FoV pyramid, 1 m long (scaled to the data in resetView), board frame. */
function buildFov(): THREE.Group {
  const g = new THREE.Group();
  const L = 1000, hx = Math.tan((27.5 * Math.PI) / 180) * L, hy = Math.tan((21 * Math.PI) / 180) * L;
  const apex = b(0, 0, 0);
  const c = [b(-hx, -hy, L), b(hx, -hy, L), b(hx, hy, L), b(-hx, hy, L)];
  g.add(new THREE.LineSegments(
    new THREE.BufferGeometry().setFromPoints([
      apex, c[0]!, apex, c[1]!, apex, c[2]!, apex, c[3]!,
      c[0]!, c[1]!, c[1]!, c[2]!, c[2]!, c[3]!, c[3]!, c[0]!,
    ]),
    new THREE.LineBasicMaterial({ color: 0x0284c7, transparent: true, opacity: 0.5 }),
  ));
  return g;
}
