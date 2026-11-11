#!/usr/bin/env python3
"""Checks the USB protocol (firmware/app/protocol.h) end to end.

Connects to the board, requests info + calibration, streams IMU and LiDAR for a
few seconds, verifies every CRC and sequence number, and reports rates.
Optionally saves the calibration and the last raw LiDAR frame.

    python3 firmware/tools/stream_check.py [--port /dev/ttyACM0] [--seconds 10] [--save DIR]

Requires pyserial. Close the web app / minicom first (only one program may open the port).
"""
import argparse
import glob
import struct
import sys
import time
import zlib
from pathlib import Path

import serial

SYNC = b'\xa5\x5a'
HEADER = struct.Struct('<2sBBIQI')          # sync, type, version, seq, t_us, length
TYPES = {0x01: 'INFO', 0x02: 'LOG', 0x03: 'STATUS', 0x10: 'IMU', 0x20: 'LIDAR_FRAME', 0x21: 'LIDAR_CALIB'}
STATUS = struct.Struct('<6BH7I')            # proto_status_t, 36 bytes
STATUS_FIELDS = ('imu_variant', 'imu_whoami', 'imu_streaming', 'lidar_state', 'lidar_bus', 'led_mode',
                 'reserved', 'lidar_bus_hz', 'lidar_frames', 'lidar_dropped', 'lidar_errors',
                 'lidar_last_error', 'imu_samples', 'tx_dropped')


def find_port():
    ports = sorted(glob.glob('/dev/serial/by-id/usb-RemiFM_*'))
    return ports[0] if ports else '/dev/ttyACM0'


def packets(ser, stats):
    """Yields (type, seq, t_us, payload) for every packet with a valid CRC."""
    buf = bytearray()
    while True:
        chunk = ser.read(ser.in_waiting or 1)
        if chunk:
            buf += chunk
        while True:
            i = buf.find(SYNC)
            if i < 0:
                stats['skipped'] += max(0, len(buf) - 1)
                del buf[:max(0, len(buf) - 1)]
                break
            if i:
                stats['skipped'] += i
                del buf[:i]
            if len(buf) < HEADER.size:
                break
            _, ptype, version, seq, t_us, length = HEADER.unpack_from(buf)
            if length > 16384 or version != 1:
                stats['skipped'] += 1
                del buf[:1]
                continue
            total = HEADER.size + length + 4
            if len(buf) < total:
                break
            crc = struct.unpack_from('<I', buf, total - 4)[0]
            if zlib.crc32(bytes(buf[:total - 4])) != crc:
                stats['crc_errors'] += 1
                del buf[:1]
                continue
            payload = bytes(buf[HEADER.size:total - 4])
            del buf[:total]
            yield ptype, seq, t_us, payload
        yield None   # let the caller check the clock


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--port', default=None)
    ap.add_argument('--seconds', type=float, default=10.0)
    ap.add_argument('--save', type=Path, help='directory for calibration.bin and frame.bin')
    args = ap.parse_args()

    port = args.port or find_port()
    ser = serial.Serial(port, timeout=0.05)
    ser.dtr = True
    print(f'port: {port}')
    time.sleep(0.2)
    ser.write(b'XVCIL')   # stop, info, calibration, IMU on, LiDAR on

    stats = {'skipped': 0, 'crc_errors': 0, 'seq_gaps': 0}
    counts = {name: 0 for name in TYPES.values()}
    last_seq = None
    first_t = {}
    last_t = {}
    imu_seq_gaps = 0
    last_imu = None
    last_frame = None
    frame_bytes = 0
    status = None
    calib = None
    start = time.monotonic()

    for item in packets(ser, stats):
        if time.monotonic() - start > args.seconds:
            break
        if item is None:
            continue
        ptype, seq, t_us, payload = item
        name = TYPES.get(ptype, f'0x{ptype:02X}')
        counts[name] = counts.get(name, 0) + 1
        if last_seq is not None and seq != last_seq + 1:
            stats['seq_gaps'] += 1
        last_seq = seq
        first_t.setdefault(name, t_us)
        last_t[name] = t_us

        if name == 'INFO':
            print('--- INFO\n' + payload.decode(errors='replace').rstrip())
        elif name == 'LOG':
            print('LOG:', payload.decode(errors='replace'))
        elif name == 'STATUS':
            status = dict(zip(STATUS_FIELDS, STATUS.unpack(payload)))
        elif name == 'IMU':
            sample, *vals = struct.unpack('<I7f', payload)
            if last_imu is not None and sample != last_imu + 1:
                imu_seq_gaps += 1
            last_imu = sample
        elif name == 'LIDAR_CALIB':
            calib = payload
            print(f'calibration: {len(payload)} bytes, crc32 {zlib.crc32(payload):08x}')
        elif name == 'LIDAR_FRAME':
            frame, width, height, raw_size = struct.unpack_from('<IHHI', payload)
            raw = payload[12:]
            assert len(raw) == raw_size, (len(raw), raw_size)
            last_frame = raw
            frame_bytes += len(payload)
            if counts[name] == 1:
                counter = struct.unpack_from('<I', raw, width * height * 6 + width * height // 2)[0]
                print(f'first frame: #{frame} {width}x{height}, {raw_size} raw bytes, sensor counter {counter}')

    ser.write(b'X')
    ser.close()
    elapsed = time.monotonic() - start

    print('\n--- summary')
    for name in ('IMU', 'LIDAR_FRAME'):
        n = counts.get(name, 0)
        if n > 1:
            span = (last_t[name] - first_t[name]) / 1e6
            print(f'{name:12s} {n:6d} packets, {n / elapsed:6.1f}/s host, {(n - 1) / span:6.1f}/s MCU clock')
        else:
            print(f'{name:12s} {n:6d} packets')
    print(f'LiDAR data   {frame_bytes / elapsed / 1024:.0f} KiB/s')
    print(f'other        {", ".join(f"{k} {v}" for k, v in counts.items() if k not in ("IMU", "LIDAR_FRAME"))}')
    print(f'errors       crc {stats["crc_errors"]}, packet seq gaps {stats["seq_gaps"]}, '
          f'IMU sample gaps {imu_seq_gaps}, skipped bytes {stats["skipped"]}')
    if status:
        print('status       ' + ', '.join(f'{k}={v}' for k, v in status.items() if k != 'reserved'))

    if args.save:
        args.save.mkdir(parents=True, exist_ok=True)
        if calib:
            (args.save / 'calibration.bin').write_bytes(calib)
        if last_frame:
            (args.save / 'frame.bin').write_bytes(last_frame)
        print(f'saved to {args.save}')

    ok = stats['crc_errors'] == 0 and counts.get('LIDAR_FRAME', 0) > 0 and counts.get('IMU', 0) > 0
    sys.exit(0 if ok else 1)


if __name__ == '__main__':
    main()
