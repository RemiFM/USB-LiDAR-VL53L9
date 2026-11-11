import { defineConfig } from 'vite';
import tailwindcss from '@tailwindcss/vite';

export default defineConfig({
  plugins: [tailwindcss()],
  // Three.js alone is ~500 kB; fine for a local tool.
  build: { chunkSizeWarningLimit: 1000 },
  server: {
    // Web Serial requires a secure context; localhost counts as one.
    host: 'localhost',
    port: 5173,
  },
});
