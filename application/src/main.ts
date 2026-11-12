/**
 * Wiring only: connects the data sources (live device, playback) to processing,
 * logging and views. Each module stays independent of the others.
 *
 *   SerialTransport --bytes--> PacketParser --packets--+
 *                       \--> Recorder (raw session)    +--> handlePacket --> IMU: stats, orientation, plots
 *   Playback (session .bin / imu .csv) --packets/IMU---+                 \-> LiDAR: WASM processing, views
 */
import './style.css';
import type { ImuSample, Vec3 } from './types';
import { SerialTransport } from './transport/serial';
import {
  CMD, PKT, PacketParser, decodeImu, decodeInfo, decodeLidarFrame, decodeStatus, decodeText, encodePacket,
  LIDAR_STATE_NAMES, type DeviceStatus, type LidarRaw, type Packet,
} from './protocol/binary';
import { StreamStats } from './processing/stats';
import { GyroCalibrator, OrientationEstimator, quatToEulerDeg } from './processing/orientation';
import { sensorToBoard } from './processing/mounting';
import { icon, renderIcons } from './ui/icons';
import { LidarProcessor, ZONES, type LidarFrame } from './processing/lidar';
import { Recorder } from './logging/recorder';
import { Playback } from './logging/playback';
import { RollingPlot } from './ui/plots';
import { OrientationView } from './ui/orientation3d';
import { DeviceConsole } from './ui/console';
import { DepthMapView } from './ui/lidar/depthMap';
import { TopView } from './ui/lidar/topView';
import { PointCloudView } from './ui/lidar/pointCloud';
import type { ColorMode, LidarViewSettings } from './ui/lidar/common';

// ---------------------------------------------------------------- DOM helpers
function $<T extends HTMLElement = HTMLElement>(id: string): T {
  const el = document.getElementById(id);
  if (!el) throw new Error(`#${id} missing`);
  return el as T;
}
const ui = {
  connect: $<HTMLButtonElement>('btn-connect'),
  imu: $<HTMLButtonElement>('btn-imu'),
  lidar: $<HTMLButtonElement>('btn-lidar'),
  calibrate: $<HTMLButtonElement>('btn-calibrate'),
  reset: $<HTMLButtonElement>('btn-reset'),
  record: $<HTMLButtonElement>('btn-record'),
  loadLabel: $('lbl-load'),
  load: $<HTMLInputElement>('file-load'),
  play: $<HTMLButtonElement>('btn-play'),
  speed: $<HTMLSelectElement>('sel-speed'),
  progress: $<HTMLProgressElement>('prog-play'),
  sendForm: $<HTMLFormElement>('form-send'),
  sendInput: $<HTMLInputElement>('input-send'),
  sendBtn: $<HTMLButtonElement>('btn-send'),
  roll: $('val-roll'), pitch: $('val-pitch'), yaw: $('val-yaw'),
  rate: $('val-rate'), count: $('val-count'), anorm: $('val-anorm'),
  temp: $('val-temp'), bias: $('val-bias'),
  tabNote: $('tab-note'),
  // LiDAR card
  lidarSummary: $('lidar-summary'),
  lidarOverlay: $('lidar-overlay'),
  color: $<HTMLSelectElement>('sel-color'),
  range: $<HTMLSelectElement>('sel-range'),
  temporal: $<HTMLInputElement>('chk-temporal'),
  level: $<HTMLInputElement>('chk-level'),
  mirrorH: $<HTMLButtonElement>('btn-mirror-h'),
  mirrorV: $<HTMLButtonElement>('btn-mirror-v'),
  link: $<HTMLButtonElement>('btn-link'),
  cloudView: $<HTMLButtonElement>('btn-cloud-view'),
  lidarReinit: $<HTMLButtonElement>('btn-lidar-reinit'),
  // Stream card
  usbRate: $('st-usb-rate'), usbPackets: $('st-usb-packets'), usbErrors: $('st-usb-errors'), rec: $('st-rec'),
  lidarFps: $('st-lidar-fps'), lidarValid: $('st-lidar-valid'), lidarDepth: $('st-lidar-depth'),
  lidarProc: $('st-lidar-proc'), lidarMcu: $('st-lidar-mcu'), lidarMedian: $('st-lidar-median'),
  smooth: $<HTMLInputElement>('chk-smooth'),
  devFw: $('st-dev-fw'), devImu: $('st-dev-imu'), devLidar: $('st-dev-lidar'), devSerial: $('st-dev-serial'),
};

// ---------------------------------------------------------------- settings (per browser)
const SETTINGS_KEY = 'usb-lidar-imu:lidar-view';
const settings: LidarViewSettings & { tab: string; temporal: boolean; level: boolean } = {
  tab: 'depth', colorMode: 'depth', maxRangeMm: 0, mirrorH: false, mirrorV: false, smooth: true, temporal: false, level: false,
};
try {
  Object.assign(settings, JSON.parse(localStorage.getItem(SETTINGS_KEY) ?? '{}'));
} catch { /* storage unavailable: defaults */ }
function saveSettings(): void {
  try { localStorage.setItem(SETTINGS_KEY, JSON.stringify(settings)); } catch { /* ignore */ }
}

// ---------------------------------------------------------------- modules
const serial = new SerialTransport();
const parser = new PacketParser();
const playback = new Playback();
const imuStats = new StreamStats();
const orientation = new OrientationEstimator();
const recorder = new Recorder();
const log = new DeviceConsole($('console'));
const accelPlot = new RollingPlot($('plot-accel'), 'mg');
const gyroPlot = new RollingPlot($('plot-gyro'), 'mdps');
const view3d = new OrientationView($('view-3d'));
const depthView = new DepthMapView($<HTMLCanvasElement>('lidar-depth'), settings);
const topView = new TopView($<HTMLCanvasElement>('lidar-top'), settings);
const cloudView = new PointCloudView($('lidar-cloud'), settings);
let processor: LidarProcessor | null = null;

let source: 'none' | 'live' | 'playback' = 'none';
let playing = false;
let calibrator: GyroCalibrator | null = null;
let latestImu: ImuSample | null = null;
let deviceInfo: Record<string, string> = {};
let deviceStatus: DeviceStatus | null = null;
let infoPacket: Packet | null = null;
let calibPacket: Packet | null = null;
let lastRaw: LidarRaw | null = null;
let latestFrame: LidarFrame | null = null;
let lidarFrames = 0;
let lidarProcMs = 0;
let lidarErrors = 0;
let calibRequestedAt = 0;

// ---------------------------------------------------------------- IMU pipeline
function resetPipeline(): void {
  imuStats.reset();
  orientation.reset();
  accelPlot.clear();
  gyroPlot.clear();
  latestImu = null;
  latestFrame = null;
  lastRaw = null;
  lidarFrames = 0;
  for (const v of [depthView, topView, cloudView]) v.setFrame(null);
}

function handleImu(s: ImuSample): void {
  imuStats.feed(s);

  if (calibrator) {
    try {
      const bias = calibrator.feed(s);
      if (bias) {
        orientation.gyroBiasMdps = bias;
        calibrator = null;
        log.app(`Gyro bias: ${fmtVec(bias, 0)} mdps`);
        orientation.reset();
      }
    } catch (err) {
      calibrator = null;
      log.error(`${(err as Error).message} (press "Calibrate gyro" to retry)`);
    }
  }

  const q = orientation.update(s);
  view3d.setQuaternion(q);
  cloudView.setBoardOrientation(q);
  // Plots in the board frame (same axes as the 3D view); recordings stay raw sensor data.
  const t = s.tMs / 1000;
  accelPlot.push(t, sensorToBoard(s.accelMg));
  gyroPlot.push(t, sensorToBoard(s.gyroMdps));
  if (source === 'live') recorder.addImu(s);
  latestImu = s;
}

// ---------------------------------------------------------------- LiDAR pipeline
function handleLidarRaw(raw: LidarRaw): void {
  lastRaw = raw;
  if (!processor) return;
  if (!processor.hasCalibration) {
    // Frames before calibration: ask for it (live), at most once per second.
    if (source === 'live' && performance.now() - calibRequestedAt > 1000) {
      calibRequestedAt = performance.now();
      void send(CMD.CALIB);
    }
    return;
  }
  processLidar(raw);
}

function processLidar(raw: LidarRaw): void {
  try {
    const f = processor!.process(raw);
    latestFrame = f;
    lidarFrames++;
    lidarProcMs = lidarProcMs ? lidarProcMs * 0.9 + f.processMs * 0.1 : f.processMs;
    for (const v of [depthView, topView, cloudView]) v.setFrame(f);
  } catch (err) {
    if (lidarErrors++ % 50 === 0) log.error(`LiDAR processing: ${(err as Error).message}`);
  }
}

function setCalibration(p: Packet): void {
  calibPacket = p; // kept for recordings, and applied once the WASM module is loaded
  if (!processor) return;
  try {
    processor.setCalibration(p.payload);
    log.app(`LiDAR calibration loaded (${p.payload.length} bytes)`);
  } catch (err) {
    log.error(`LiDAR calibration rejected: ${(err as Error).message}`);
  }
}

// ---------------------------------------------------------------- packets
function handlePacket(p: Packet): void {
  switch (p.type) {
    case PKT.IMU:
      handleImu(decodeImu(p));
      break;
    case PKT.LIDAR_FRAME:
      handleLidarRaw(decodeLidarFrame(p));
      break;
    case PKT.LIDAR_CALIB:
      setCalibration(p);
      break;
    case PKT.STATUS:
      deviceStatus = decodeStatus(p);
      refreshToggles();
      break;
    case PKT.INFO:
      deviceInfo = decodeInfo(p);
      infoPacket = p;
      log.device(`Device: firmware ${deviceInfo.firmware ?? '?'}, IMU ${deviceInfo.imu ?? '?'}, ` +
        `LiDAR ${deviceInfo.lidar_state ?? '?'} (${deviceInfo.lidar_bus ?? '?'})` +
        (deviceInfo.lidar_last_error && !deviceInfo.lidar_last_error.startsWith('0 ') ? `, last error ${deviceInfo.lidar_last_error}` : ''));
      break;
    case PKT.LOG:
      log.device(decodeText(p));
      break;
    default:
      break;
  }
}

serial.data.on((chunk) => {
  if (recorder.recording) recorder.addBytes(chunk);
  parser.push(chunk);
});
parser.packets.on((p) => {
  if (source === 'live') handlePacket(p);
});
serial.errors.on((err) => log.error(err.message));

serial.state.on((state) => {
  if (state === 'connected') {
    playback.stop();
    source = 'live';
    parser.reset();
    resetPipeline();
    deviceStatus = null;
    log.app('Connected');
    // Device sends its info on connect; then: stop leftovers, LED back to automatic
    // blinking, info, calibration, IMU + LiDAR on.
    setTimeout(() => {
      void send(CMD.ALL_OFF + CMD.LED_AUTO + CMD.INFO + CMD.CALIB + CMD.IMU_ON + CMD.LIDAR_ON);
      startCalibration();
    }, 300);
  } else if (state === 'disconnected') {
    if (source === 'live') source = 'none';
    deviceStatus = null;
    if (recorder.recording) stopRecording();
    log.app('Disconnected');
  }
  refreshControls(state);
});

playback.packets.on((p) => handlePacket(p));
playback.samples.on((s) => handleImu(s));
playback.progress.on((p) => (ui.progress.value = p));
playback.state.on((state) => {
  playing = state === 'playing';
  ui.play.innerHTML = icon(playing ? 'pause' : 'play');
  ui.play.title = playing ? 'Pause' : 'Play the loaded recording';
  ui.play.setAttribute('aria-label', playing ? 'Pause' : 'Play');
  if (state === 'ended') log.app('Playback finished');
  refreshControls();
});

// ---------------------------------------------------------------- actions
async function send(cmd: string): Promise<void> {
  if (serial.connected) await serial.write(cmd);
}

function stopRecording(): void {
  const summary = recorder.stopAndDownload(`${deviceInfo.imu ?? '?'} / LiDAR ${deviceInfo.lidar_device_id ?? '?'}, serial ${deviceInfo.serial ?? '?'}`);
  log.app(`Saved recording: ${summary}`);
  setRecordIcon(false);
}

function setRecordIcon(recording: boolean): void {
  ui.record.innerHTML = icon(recording ? 'stop' : 'record');
  ui.record.classList.toggle('animate-pulse', recording);
  ui.record.title = recording ? 'Stop recording and save' : 'Record (session .bin + IMU CSV)';
  ui.record.setAttribute('aria-label', recording ? 'Stop recording' : 'Record');
}

// Link icon: connected = click to disconnect, broken = click to connect.
ui.link.addEventListener('click', () => {
  void (serial.connected ? serial.disconnect() : serial.connect());
});
ui.connect.addEventListener('click', () => {
  void (serial.connected ? serial.disconnect() : serial.connect());
});
ui.imu.addEventListener('click', () => void send(deviceStatus?.imuStreaming ? CMD.IMU_OFF : CMD.IMU_ON));
ui.lidar.addEventListener('click', () => void send(deviceStatus?.lidarState === 2 ? CMD.LIDAR_OFF : CMD.LIDAR_ON));
ui.lidarReinit.addEventListener('click', () => {
  if (processor) processor.setTemporal(settings.temporal); // restart temporal state
  void send(CMD.LIDAR_REINIT + CMD.CALIB + CMD.LIDAR_ON);
});

function startCalibration(): void {
  calibrator = new GyroCalibrator();
  log.app('Calibrating gyro: keep the board still for 2 s…');
}

ui.calibrate.addEventListener('click', startCalibration);
$<HTMLButtonElement>('btn-view-reset').addEventListener('click', () => view3d.resetView());
ui.reset.addEventListener('click', () => {
  // Roll and pitch are measured against gravity, so only yaw can be reset.
  orientation.reset();
  log.app('Yaw reset to 0 (roll/pitch stay gravity-referenced)');
});

ui.record.addEventListener('click', () => {
  if (recorder.recording) {
    stopRecording();
  } else {
    // Put info + calibration first so the session file replays on its own.
    const prelude = [infoPacket, calibPacket].filter((p): p is Packet => p !== null)
      .map((p) => encodePacket(p.type, p.seq, p.tUs, p.payload));
    recorder.start(prelude);
    setRecordIcon(true);
    log.app('Recording…');
  }
});

ui.load.addEventListener('change', async () => {
  const file = ui.load.files?.[0];
  ui.load.value = '';
  if (!file) return;
  if (serial.connected) {
    log.error('Disconnect from the device before playing a recording.');
    return;
  }
  const summary = await playback.load(file);
  if (playback.length === 0) {
    log.error(`${file.name}: nothing to replay`);
    return;
  }
  source = 'playback';
  resetPipeline();
  log.app(`Loaded ${file.name}: ${summary}`);
  refreshControls();
});

ui.play.addEventListener('click', () => {
  if (playing) {
    playback.pause();
  } else {
    if (ui.progress.value === 0 || ui.progress.value >= 1) resetPipeline();
    playback.play();
  }
});
ui.speed.addEventListener('change', () => (playback.speed = Number(ui.speed.value)));

// Motion card tabs: one plot visible at a time.
const TAB_NOTES: Record<string, string> = {
  accel: 'board frame, mg',
  gyro: 'board frame, mdps, raw (bias not removed)',
};
for (const tab of document.querySelectorAll<HTMLButtonElement>('[data-tab]')) {
  tab.addEventListener('click', () => {
    const name = tab.dataset.tab ?? '';
    for (const t of document.querySelectorAll<HTMLButtonElement>('[data-tab]')) {
      t.classList.toggle('tab-active', t === tab);
      t.setAttribute('aria-selected', String(t === tab));
    }
    for (const panel of document.querySelectorAll<HTMLElement>('[data-tab-panel]')) {
      panel.classList.toggle('hidden', panel.dataset.tabPanel !== name);
    }
    ui.tabNote.textContent = TAB_NOTES[name] ?? '';
  });
}

// LiDAR card tabs: 3D / depth map / top view.
function showLidarTab(name: string): void {
  settings.tab = name;
  for (const t of document.querySelectorAll<HTMLButtonElement>('[data-lidar-tab]')) {
    t.classList.toggle('tab-active', t.dataset.lidarTab === name);
    t.setAttribute('aria-selected', String(t.dataset.lidarTab === name));
  }
  for (const p of document.querySelectorAll<HTMLElement>('[data-lidar-panel]')) {
    p.classList.toggle('hidden', p.dataset.lidarPanel !== name);
  }
  for (const el of document.querySelectorAll<HTMLElement>('[data-only]')) {
    el.classList.toggle('hidden', el.dataset.only !== name);
  }
  cloudView.active = name === 'cloud';
  for (const v of [depthView, topView, cloudView]) v.invalidate();
  saveSettings();
}
for (const t of document.querySelectorAll<HTMLButtonElement>('[data-lidar-tab]')) {
  t.addEventListener('click', () => showLidarTab(t.dataset.lidarTab ?? 'depth'));
}

// LiDAR view settings.
ui.color.value = settings.colorMode;
ui.range.value = String(settings.maxRangeMm);
refreshMirrors();
ui.temporal.checked = settings.temporal;
ui.smooth.checked = settings.smooth;
ui.level.checked = settings.level;
cloudView.setLevel(settings.level);
function viewSettingsChanged(): void {
  settings.colorMode = ui.color.value as ColorMode;
  settings.maxRangeMm = Number(ui.range.value);
  for (const v of [depthView, topView, cloudView]) v.invalidate();
  saveSettings();
}
ui.color.addEventListener('change', viewSettingsChanged);
ui.range.addEventListener('change', viewSettingsChanged);
function refreshMirrors(): void {
  for (const [b, on] of [[ui.mirrorH, settings.mirrorH], [ui.mirrorV, settings.mirrorV]] as const) {
    b.classList.toggle('btn-on', on);
    b.setAttribute('aria-pressed', String(on));
  }
  if (processor) {
    processor.mirrorH = settings.mirrorH;
    processor.mirrorV = settings.mirrorV;
  }
}
function mirrorChanged(): void {
  refreshMirrors();
  if (lastRaw && processor?.hasCalibration && !settings.temporal) processLidar(lastRaw);
  viewSettingsChanged();
}
ui.mirrorH.addEventListener('click', () => { settings.mirrorH = !settings.mirrorH; mirrorChanged(); });
ui.mirrorV.addEventListener('click', () => { settings.mirrorV = !settings.mirrorV; mirrorChanged(); });
ui.temporal.addEventListener('change', () => {
  settings.temporal = ui.temporal.checked;
  processor?.setTemporal(settings.temporal);
  saveSettings();
});
ui.level.addEventListener('change', () => {
  settings.level = ui.level.checked;
  cloudView.setLevel(settings.level);
  saveSettings();
});
ui.cloudView.addEventListener('click', () => cloudView.resetView());
ui.smooth.addEventListener('change', () => {
  settings.smooth = ui.smooth.checked;
  depthView.invalidate();
  saveSettings();
});

ui.sendForm.addEventListener('submit', (e) => {
  e.preventDefault();
  const text = ui.sendInput.value;
  if (!text) return;
  ui.sendInput.value = '';
  void send(text);
});

// ---------------------------------------------------------------- view state
function refreshControls(serialState = serial.connected ? 'connected' : 'disconnected'): void {
  const live = serialState === 'connected';
  const hasPlayback = source === 'playback' && playback.length > 0;

  // Connect button lives in the LiDAR card's empty state; the link icon in the header.
  ui.connect.textContent = serialState === 'connecting' ? 'Connecting…' : 'Connect';
  ui.connect.disabled = serialState === 'connecting' || !SerialTransport.isSupported();
  ui.connect.classList.toggle('hidden', live || hasPlayback);
  ui.link.innerHTML = icon(live ? 'link' : 'unlink');
  ui.link.classList.toggle('btn-link-on', live);
  ui.link.classList.toggle('btn-link-off', !live);
  ui.link.disabled = serialState === 'connecting' || !SerialTransport.isSupported();
  const label = live ? 'Connected: click to disconnect'
    : hasPlayback ? `Not connected (playback: ${playback.fileName}): click to connect` : 'Not connected: click to connect';
  ui.link.title = label;
  ui.link.setAttribute('aria-label', live ? 'Disconnect' : 'Connect');
  for (const b of [ui.imu, ui.lidar, ui.record, ui.sendBtn, ui.lidarReinit]) b.disabled = !live;
  ui.sendInput.disabled = !live;
  ui.calibrate.disabled = !(live || hasPlayback);
  ui.reset.disabled = !(live || hasPlayback);
  ui.play.disabled = !hasPlayback;
  ui.speed.disabled = !hasPlayback;
  ui.progress.classList.toggle('hidden', !hasPlayback);
  ui.loadLabel.classList.toggle('opacity-40', live);
  refreshToggles();
}

function refreshToggles(): void {
  const s = serial.connected ? deviceStatus : null;
  ui.imu.classList.toggle('btn-on', !!s?.imuStreaming);
  ui.lidar.classList.toggle('btn-on', s?.lidarState === 2);
  ui.lidar.title = s ? `LiDAR: ${LIDAR_STATE_NAMES[s.lidarState] ?? s.lidarState}` : 'LiDAR stream on/off';
}

function fmtVec(v: Vec3, digits: number): string {
  return v.map((x) => x.toFixed(digits).padStart(7)).join(' ');
}

function lidarOverlayText(): string {
  if (latestFrame) return '';
  if (source === 'none') return 'Connect the board or load a session recording';
  if (!processor) return 'Loading LiDAR processing…';
  if (source === 'live' && deviceStatus?.lidarState === 3) return 'LiDAR error: press "Re-init LiDAR"';
  if (source === 'live' && deviceStatus?.lidarState === 0) return 'No LiDAR detected';
  if (lastRaw && !processor.hasCalibration) return 'Waiting for LiDAR calibration…';
  if (source === 'live' && deviceStatus && deviceStatus.lidarState !== 2) return 'LiDAR stream is off';
  return 'Waiting for LiDAR frames…';
}

// ---------------------------------------------------------------- render loop
let lastText = 0;
let last = { t: performance.now(), bytes: 0, frames: 0, packets: 0 };
function frame(now: number): void {
  accelPlot.render();
  gyroPlot.render();
  view3d.render();
  if (settings.tab === 'depth') depthView.render();
  else if (settings.tab === 'top') topView.render();
  else cloudView.render();

  // Text values at ~5 Hz is plenty for reading.
  if (now - lastText > 200) {
    const dt = (now - last.t) / 1000;
    const st = parser.stats;
    if (dt >= 1) {
      ui.usbRate.textContent = source === 'live' ? `${((st.bytes - last.bytes) / dt / 1024).toFixed(0)} KiB/s` : '–';
      ui.lidarFps.textContent = `${((lidarFrames - last.frames) / dt).toFixed(1)} fps`;
      last = { t: now, bytes: st.bytes, frames: lidarFrames, packets: st.packets };
    }
    lastText = now;

    if (latestImu) {
      const [r, p, y] = quatToEulerDeg(orientation.filter.q);
      ui.roll.textContent = `${r.toFixed(1)}°`;
      ui.pitch.textContent = `${p.toFixed(1)}°`;
      ui.yaw.textContent = `${y.toFixed(1)}°`;
      ui.anorm.textContent = `${Math.hypot(...latestImu.accelMg).toFixed(0)} mg`;
      ui.temp.textContent = `${latestImu.tempC.toFixed(2)} °C`;
    }
    ui.rate.textContent = imuStats.received ? `${imuStats.rateHz.toFixed(1)} Hz` : '–';
    ui.count.textContent = imuStats.received ? `${imuStats.received} / ${imuStats.dropped}` : '–';
    const b = orientation.gyroBiasMdps;
    ui.bias.textContent = calibrator
      ? `calibrating… ${Math.round(calibrator.progress * 100)} %`
      : b.some((v) => v !== 0) ? fmtVec(b, 0) : '–';
    ui.bias.title = b.some((v) => v !== 0) || calibrator ? '' : 'Not calibrated yet (Orientation card: Calibrate gyro)';

    ui.usbPackets.textContent = source === 'live' ? String(st.packets) : '–';
    ui.usbErrors.textContent = source === 'live' ? `${st.crcErrors} / ${st.seqGaps}` : '–';
    ui.rec.textContent = recorder.recording ? `${(recorder.sizeBytes / 1e6).toFixed(1)} MB` : '–';

    const f = latestFrame;
    ui.lidarValid.textContent = f ? `${f.validCount} (${((100 * f.validCount) / ZONES).toFixed(0)} %)` : '–';
    ui.lidarValid.title = f ? `${f.validCount} of ${ZONES} zones` : '';
    ui.lidarDepth.textContent = f && f.validCount ? `${(f.minMm / 1000).toFixed(2)}–${(f.maxMm / 1000).toFixed(2)} m` : '–';
    ui.lidarMedian.textContent = f && f.validCount ? `${(f.medianMm / 1000).toFixed(2)} m` : '–';
    ui.lidarProc.textContent = f ? `${lidarProcMs.toFixed(2)} ms` : '–';
    const s = deviceStatus;
    ui.lidarMcu.textContent = s ? `${s.lidarFrames} / ${s.lidarDropped}` : '–';
    ui.lidarSummary.textContent = f
      ? `#${f.frame} · ${ui.lidarFps.textContent} · ${f.validCount} valid · median ${(f.medianMm / 1000).toFixed(2)} m` : '';
    ui.lidarOverlay.textContent = lidarOverlayText();

    ui.devFw.textContent = deviceInfo.firmware ?? '–';
    ui.devImu.textContent = deviceInfo.imu ? `${deviceInfo.imu} (${deviceInfo.imu_whoami})` : '–';
    ui.devLidar.textContent = deviceInfo.lidar_patch ? `VL53L9 patch ${deviceInfo.lidar_patch}` : '–';
    ui.devSerial.textContent = deviceInfo.serial ?? '–';
    ui.devSerial.title = deviceInfo.serial ?? '';
  }
  requestAnimationFrame(frame);

}

// ---------------------------------------------------------------- start
if (!SerialTransport.isSupported()) {
  $('unsupported').classList.remove('hidden');
  ui.connect.disabled = true;
}
navigator.serial?.addEventListener('disconnect', () => void serial.disconnect());
renderIcons();
showLidarTab(new URLSearchParams(location.search).get('tab') ?? settings.tab);
refreshControls();
void view3d.loadBoardModel().then((ok) => {
  if (!ok) log.app('3D board model not found (run "npm run export-board"); showing simplified board.');
});
LidarProcessor.load().then((p) => {
  processor = p;
  p.mirrorH = settings.mirrorH;
  p.mirrorV = settings.mirrorV;
  p.setTemporal(settings.temporal);
  if (calibPacket) setCalibration(calibPacket);
}).catch((err) => log.error(`LiDAR processing (WASM) failed to load: ${(err as Error).message}`));
requestAnimationFrame(frame);

// ?replay=<url>: load a session recording and play it (demos, testing without hardware).
const replayUrl = new URLSearchParams(location.search).get('replay');
if (replayUrl) {
  void (async () => {
    const res = await fetch(replayUrl);
    if (!res.ok) return log.error(`replay: ${replayUrl}: HTTP ${res.status}`);
    const file = new File([await res.blob()], replayUrl.split('/').pop() ?? 'session.bin');
    const summary = await playback.load(file);
    source = 'playback';
    resetPipeline();
    log.app(`Loaded ${file.name}: ${summary}`);
    refreshControls();
    playback.play();
  })();
}

