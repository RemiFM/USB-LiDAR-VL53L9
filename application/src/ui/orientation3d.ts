/**
 * 3D view of the board orientation (Three.js).
 *
 * Board model: public/models/board.glb, exported from KiCad with the real board
 * outline and component STEP models (`npm run export-board`). If that file is
 * missing, a simple box model is shown instead.
 *
 * Model and quaternion are in the board frame (processing/mounting.ts):
 *   X right, Y towards the LiDAR, Z out of the top side (LiDAR viewing direction).
 * Three.js uses Y up, so board (x, y, z) is shown as three (x, z, -y). KiCad's GLB
 * export uses the same axes (glTF is Y up, KiCad Y down becomes +Z), in metres,
 * with its origin set to the board centre (KiCad 150, 101.9 mm).
 */
import * as THREE from 'three';
import { OrbitControls } from 'three/examples/jsm/controls/OrbitControls.js';
import { GLTFLoader } from 'three/examples/jsm/loaders/GLTFLoader.js';
import { RoomEnvironment } from 'three/examples/jsm/environments/RoomEnvironment.js';
import type { Quat } from '../processing/orientation';

const MM = 0.1; // scene units per millimetre
const GLB_SCALE = 1000 * MM; // GLB is in metres

export const BOARD_MODEL_URL = `${import.meta.env.BASE_URL}models/board.glb`;
const LIDAR_REF = 'U1'; // VL53L9CX reference designator in the PCB

/** Board-frame millimetres -> Three.js scene coordinates. */
function b(x: number, y: number, z: number): THREE.Vector3 {
  return new THREE.Vector3(x * MM, z * MM, -y * MM);
}

const PCB = { w: 34, h: 30.2, t: 1.6 };
const TOP = PCB.t / 2;
const BOTTOM = -PCB.t / 2;
const LIDAR_FOV_H_DEG = 55; // along board X (VL53L9CX datasheet, Table 3)
const LIDAR_FOV_V_DEG = 42; // along board Y
const LIDAR_FOV_LEN_MM = 28; // how far the FoV pyramid is drawn

// ------------------------------------------------------------------ LiDAR FoV

/** Pyramid with the sensor's FoV, apex at the origin, opening along +Z (board). */
function buildFov(): THREE.Group {
  const hx = Math.tan((LIDAR_FOV_H_DEG / 2) * (Math.PI / 180)) * LIDAR_FOV_LEN_MM;
  const hy = Math.tan((LIDAR_FOV_V_DEG / 2) * (Math.PI / 180)) * LIDAR_FOV_LEN_MM;
  const z = LIDAR_FOV_LEN_MM;
  const apex = b(0, 0, 0);
  const c = [b(-hx, -hy, z), b(hx, -hy, z), b(hx, hy, z), b(-hx, hy, z)] as const;

  const faces = new THREE.BufferGeometry().setFromPoints([
    apex, c[0], c[1], apex, c[1], c[2], apex, c[2], c[3], apex, c[3], c[0],
  ]);
  const fill = new THREE.Mesh(faces, new THREE.MeshBasicMaterial({
    color: 0x0ea5e9, transparent: true, opacity: 0.1, side: THREE.DoubleSide, depthWrite: false,
  }));
  const edges = new THREE.LineSegments(
    new THREE.BufferGeometry().setFromPoints([
      apex, c[0], apex, c[1], apex, c[2], apex, c[3],
      c[0], c[1], c[1], c[2], c[2], c[3], c[3], c[0],
    ]),
    new THREE.LineBasicMaterial({ color: 0x0284c7, transparent: true, opacity: 0.55 }),
  );
  return new THREE.Group().add(fill, edges);
}

// ------------------------------------------------------------------ fallback model

function box(
  sizeMm: [number, number, number],
  centreMm: [number, number, number],
  color: number,
  opts: THREE.MeshStandardMaterialParameters = {},
): THREE.Mesh {
  const [sx, sy, sz] = sizeMm;
  const mesh = new THREE.Mesh(
    new THREE.BoxGeometry(sx * MM, sz * MM, sy * MM),
    new THREE.MeshStandardMaterial({ color, roughness: 0.6, ...opts }),
  );
  mesh.position.copy(b(...centreMm));
  return mesh;
}

/** Box model (positions from the PCB file), used until/unless the GLB loads. */
function buildFallbackBoard(): THREE.Group {
  const g = new THREE.Group();
  g.add(box([PCB.w, PCB.h, PCB.t], [0, 0, 0], 0x15803d, { roughness: 0.8 }));
  const lidar = box([13.4, 7.3, 1.8], [0, 7.24, TOP + 0.9], 0x1f2937, { roughness: 0.35 });
  lidar.name = LIDAR_REF;
  g.add(lidar);
  g.add(box([5, 5, 0.55], [10.5, -0.1, TOP + 0.275], 0x374151));                    // MCU
  g.add(box([8.9, 7.3, 3.2], [0, -11.4, TOP + 1.6], 0xcbd5e1, { metalness: 0.6 })); // USB-C
  g.add(box([3, 2.5, 0.83], [0, 0.65, BOTTOM - 0.415], 0x111827));                  // IMU
  return g;
}

// ------------------------------------------------------------------ view

export class OrientationView {
  private readonly renderer: THREE.WebGLRenderer;
  private readonly scene = new THREE.Scene();
  private readonly camera: THREE.PerspectiveCamera;
  /** Rotated by the measured orientation; holds model, FoV and axes. */
  private readonly board = new THREE.Group();
  private model: THREE.Object3D = buildFallbackBoard();
  private readonly fov = buildFov();
  private readonly controls: OrbitControls;
  private dirty = true;

  private static readonly CAMERA_HOME = new THREE.Vector3(4.6, 4.4, 6.0);
  private static readonly TARGET_HOME = new THREE.Vector3(0, 0.9, 0);

  constructor(private readonly container: HTMLElement) {
    this.renderer = new THREE.WebGLRenderer({ antialias: true, alpha: true });
    this.renderer.setPixelRatio(window.devicePixelRatio);
    this.renderer.setClearColor(0x000000, 0);
    container.appendChild(this.renderer.domElement);

    // Soft studio lighting so the exported PBR materials (metal, plastic) look right.
    const pmrem = new THREE.PMREMGenerator(this.renderer);
    this.scene.environment = pmrem.fromScene(new RoomEnvironment(), 0.04).texture;
    const sun = new THREE.DirectionalLight(0xffffff, 1.0);
    sun.position.set(3, 8, 5);
    this.scene.add(sun);

    this.camera = new THREE.PerspectiveCamera(40, 1, 0.05, 200);
    this.controls = new OrbitControls(this.camera, this.renderer.domElement);
    this.controls.enablePan = false;
    this.controls.minDistance = 2;
    this.controls.maxDistance = 20;
    this.controls.addEventListener('change', () => (this.dirty = true));
    this.resetView();

    const grid = new THREE.GridHelper(10, 20, 0xcbd5e1, 0xe5e7eb);
    grid.position.y = -2;
    this.scene.add(grid);

    this.board.add(this.model, this.fov, buildAxes());
    this.scene.add(this.board);
    this.placeFovOnLidar();

    new ResizeObserver(() => this.resize()).observe(container);
    this.resize();
  }

  /** Replaces the box model with the KiCad export. Resolves false if unavailable. */
  async loadBoardModel(url = BOARD_MODEL_URL): Promise<boolean> {
    try {
      const gltf = await new GLTFLoader().loadAsync(url);
      const model = gltf.scene;
      model.scale.setScalar(GLB_SCALE);
      this.board.remove(this.model);
      this.model = model;
      this.board.add(model);
      this.placeFovOnLidar();
      this.dirty = true;
      return true;
    } catch {
      return false;
    }
  }

  /** Restores the default camera position after the user orbited or zoomed. */
  resetView(): void {
    this.camera.position.copy(OrientationView.CAMERA_HOME);
    this.controls.target.copy(OrientationView.TARGET_HOME);
    this.controls.update();
    this.dirty = true;
  }

  /** Board orientation in the board frame. */
  setQuaternion([w, x, y, z]: Quat): void {
    // Same rotation in Three.js axes (the vector part maps like a vector).
    const v = b(x, y, z).divideScalar(MM);
    this.board.quaternion.set(v.x, v.y, v.z, w);
    this.dirty = true;
  }

  /** Call once per animation frame. */
  render(): void {
    if (!this.dirty) return;
    this.dirty = false;
    this.renderer.render(this.scene, this.camera);
  }

  /** Puts the FoV apex on the centre of the LiDAR's top face (from the model). */
  private placeFovOnLidar(): void {
    const lidar = this.model.getObjectByName(LIDAR_REF);
    if (!lidar) {
      this.fov.position.copy(b(0, 7.24, TOP + 1.8));
      return;
    }
    // Measure in board coordinates: temporarily undo the current orientation.
    const q = this.board.quaternion.clone();
    this.board.quaternion.identity();
    this.board.updateMatrixWorld(true);
    const bounds = new THREE.Box3().setFromObject(lidar);
    this.board.quaternion.copy(q);
    this.board.updateMatrixWorld(true);

    const centre = bounds.getCenter(new THREE.Vector3());
    this.fov.position.set(centre.x, bounds.max.y, centre.z);
  }

  private resize(): void {
    const w = this.container.clientWidth || 400;
    const h = this.container.clientHeight || 300;
    this.renderer.setSize(w, h);
    this.camera.aspect = w / h;
    this.camera.updateProjectionMatrix();
    this.dirty = true;
  }
}

/** Board axes from just outside the lower-left corner: X red, Y green, Z blue. */
function buildAxes(): THREE.Group {
  const g = new THREE.Group();
  const origin = b(-PCB.w / 2 - 3, -PCB.h / 2 - 3, 0);
  const axes: [THREE.Vector3, number][] = [
    [b(1, 0, 0), 0xdc2626],
    [b(0, 1, 0), 0x16a34a],
    [b(0, 0, 1), 0x2563eb],
  ];
  for (const [dir, color] of axes) {
    g.add(new THREE.ArrowHelper(dir.normalize(), origin, 1.6, color, 0.3, 0.16));
  }
  return g;
}
