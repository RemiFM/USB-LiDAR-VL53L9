/**
 * Web Serial transport: opens the TinyUSB CDC port and delivers the raw byte stream.
 * Knows nothing about the packet format (that is protocol/).
 * Requires Chrome or Edge, served from localhost or https.
 */
import { Emitter } from '../types';

/** USB IDs of the firmware (app/usb_descriptors.c). */
export const USB_FILTER: SerialPortFilter = { usbVendorId: 0xcafe, usbProductId: 0x4010 };

export type SerialState = 'disconnected' | 'connecting' | 'connected';

export class SerialTransport {
  readonly data = new Emitter<Uint8Array>();
  readonly state = new Emitter<SerialState>();
  readonly errors = new Emitter<Error>();

  private port: SerialPort | null = null;
  private reader: ReadableStreamDefaultReader<Uint8Array> | null = null;
  private readLoop: Promise<void> | null = null;
  private readonly encoder = new TextEncoder();

  static isSupported(): boolean {
    return 'serial' in navigator;
  }

  get connected(): boolean {
    return this.port !== null;
  }

  /** Shows the browser's port picker (filtered to our device) and opens the port. */
  async connect(): Promise<void> {
    if (this.port) return;
    this.state.emit('connecting');
    try {
      const port = await navigator.serial.requestPort({ filters: [USB_FILTER] });
      // Baud rate is ignored by USB CDC but required by the API.
      await port.open({ baudRate: 115200, bufferSize: 1 << 20 }); // LiDAR: ~520 kB/s
      // TinyUSB only reports "connected" (tud_cdc_connected) while DTR is set.
      await port.setSignals({ dataTerminalReady: true, requestToSend: true });
      this.port = port;
      this.readLoop = this.runReadLoop(port);
      this.state.emit('connected');
    } catch (err) {
      this.port = null;
      this.state.emit('disconnected');
      // The user closing the picker is not an error worth reporting.
      if (!(err instanceof DOMException && err.name === 'NotFoundError')) {
        this.errors.emit(err instanceof Error ? err : new Error(String(err)));
      }
    }
  }

  async disconnect(): Promise<void> {
    const port = this.port;
    if (!port) return;
    this.port = null;
    try {
      await this.reader?.cancel();
      await this.readLoop;
      await port.close();
    } catch {
      /* port may already be gone (unplugged) */
    }
    this.state.emit('disconnected');
  }

  /** Sends text as-is (the firmware reacts to single command characters, see protocol/binary.ts). */
  async write(text: string): Promise<void> {
    const writable = this.port?.writable;
    if (!writable) return;
    const writer = writable.getWriter();
    try {
      await writer.write(this.encoder.encode(text));
    } finally {
      writer.releaseLock();
    }
  }

  private async runReadLoop(port: SerialPort): Promise<void> {
    while (port.readable && this.port === port) {
      this.reader = port.readable.getReader();
      try {
        for (;;) {
          const { value, done } = await this.reader.read();
          if (done) break;
          if (value.length > 0) this.data.emit(value);
        }
      } catch (err) {
        // Device unplugged or USB error: report and stop.
        if (this.port === port) {
          this.errors.emit(err instanceof Error ? err : new Error(String(err)));
          this.port = null;
          try { await port.close(); } catch { /* already closed */ }
          this.state.emit('disconnected');
        }
      } finally {
        this.reader?.releaseLock();
        this.reader = null;
      }
    }
  }
}
