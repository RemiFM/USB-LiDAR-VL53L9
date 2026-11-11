/** Device console: shows informational lines from the firmware and app messages. */

const MAX_LINES = 400;

export class DeviceConsole {
  constructor(private readonly el: HTMLElement) {}

  device(text: string): void {
    this.append(text, 'text-slate-700');
  }

  app(text: string): void {
    this.append(`» ${text}`, 'text-sky-700');
  }

  error(text: string): void {
    this.append(`✖ ${text}`, 'text-red-600');
  }

  clear(): void {
    this.el.replaceChildren();
  }

  private append(text: string, cls: string): void {
    const atBottom = this.el.scrollTop + this.el.clientHeight >= this.el.scrollHeight - 4;
    const div = document.createElement('div');
    div.className = cls;
    div.textContent = text;
    this.el.appendChild(div);
    while (this.el.childElementCount > MAX_LINES) this.el.firstElementChild?.remove();
    if (atBottom) this.el.scrollTop = this.el.scrollHeight;
  }
}
