// Compiles ST's VL53L9 transform library + l9_bridge.c to WebAssembly with
// @yowasp/clang (clang + wasi-libc running in Node: no system toolchain needed).
//   npm run build-wasm   ->   src/processing/wasm/vl53l9.wasm
import { runClang } from '@yowasp/clang';
import { readFileSync, readdirSync, statSync, writeFileSync, mkdirSync } from 'node:fs';
import { join, relative, dirname } from 'node:path';
import { fileURLToPath } from 'node:url';

const here = dirname(fileURLToPath(import.meta.url));
const transform = 'vendor/vl53l9-transform-c/vl53l9-transform-c-lib';
const media = 'vendor/media-object';
const out = join(here, '../src/processing/wasm/vl53l9.wasm');

// Virtual filesystem tree for clang: all headers and sources under wasm/.
function addTree(tree, dir) {
  for (const name of readdirSync(join(here, dir))) {
    const rel = join(dir, name);
    if (statSync(join(here, rel)).isDirectory()) addTree(tree, rel);
    else if (/\.(c|h)$/.test(name)) tree[rel] = readFileSync(join(here, rel));
  }
}
function toNested(flat) {
  const root = {};
  for (const [path, data] of Object.entries(flat)) {
    const parts = path.split('/');
    let node = root;
    for (const p of parts.slice(0, -1)) node = node[p] ??= {};
    node[parts.at(-1)] = data;
  }
  return root;
}

const flat = {};
addTree(flat, 'vendor');
flat['l9_bridge.c'] = readFileSync(join(here, 'l9_bridge.c'));
const sources = ['l9_bridge.c', ...Object.keys(flat).filter((p) => p.startsWith(`${transform}/src/`) && p.endsWith('.c'))];

const args = [
  'clang', '--target=wasm32-wasip1', '-O2', '-std=c11',
  '-DVL53L9_TRANSFORM_LIGHT=0',
  `-I${transform}/include/public`, `-I${transform}/include/private`,
  `-I${media}/media-c/header-lib/include/public`, `-I${media}/transform-c/header-lib/include/public`,
  '-mexec-model=reactor',          // library: no main(), exports only
  '-Wl,--export-dynamic',
  '-Wl,-z,stack-size=262144',
  '-o', 'vl53l9.wasm',
  ...sources,
];

console.log(`compiling ${sources.length} C files...`);
const started = Date.now();
let stderr = '';
let result;
try {
  result = await runClang(args, toNested(flat), {
    stderr: (bytes) => { if (bytes) stderr += new TextDecoder().decode(bytes); },
    fetchProgress: () => {},
  });
} catch (err) {
  console.error(stderr.trim() || err);
  process.exit(1);
}
if (stderr.trim()) console.log(stderr.trim());
mkdirSync(dirname(out), { recursive: true });
writeFileSync(out, result['vl53l9.wasm']);

const module = await WebAssembly.compile(result['vl53l9.wasm']);
const imports = WebAssembly.Module.imports(module).map((i) => `${i.module}.${i.name}`);
const exports = WebAssembly.Module.exports(module).map((e) => e.name).filter((n) => n.startsWith('l9_'));
console.log(`wrote ${relative(process.cwd(), out)} (${(result['vl53l9.wasm'].length / 1024).toFixed(0)} KiB) in ${((Date.now() - started) / 1000).toFixed(1)} s`);
console.log(`exports: ${exports.join(', ')}`);
console.log(`imports: ${imports.join(', ') || 'none'}`);
