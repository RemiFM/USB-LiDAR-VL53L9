/** CRC-32 (IEEE / zlib), same as firmware/app/crc32.c. crc32("123456789") = 0xCBF43926. */

const TABLE = (() => {
  const t = new Uint32Array(256);
  for (let i = 0; i < 256; i++) {
    let c = i;
    for (let k = 0; k < 8; k++) c = c & 1 ? 0xedb88320 ^ (c >>> 1) : c >>> 1;
    t[i] = c >>> 0;
  }
  return t;
})();

export function crc32(data: Uint8Array, start = 0, end = data.length): number {
  let crc = 0xffffffff;
  for (let i = start; i < end; i++) crc = TABLE[(crc ^ data[i]!) & 0xff]! ^ (crc >>> 8);
  return (crc ^ 0xffffffff) >>> 0;
}
