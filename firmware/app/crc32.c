#include "crc32.h"

/* 256-entry table, built on first use (1 KB RAM, ~6 cycles/byte at -O2). */
static uint32_t table[256];
static int table_ready;

static void build_table(void)
{
  for (uint32_t i = 0; i < 256U; i++)
  {
    uint32_t c = i;
    for (int k = 0; k < 8; k++)
    {
      c = (c & 1U) ? (0xEDB88320U ^ (c >> 1)) : (c >> 1);
    }
    table[i] = c;
  }
  table_ready = 1;
}

uint32_t crc32_update(uint32_t crc, const void *data, size_t len)
{
  const uint8_t *p = (const uint8_t *)data;

  if (!table_ready)
  {
    build_table();
  }
  while (len--)
  {
    crc = table[(crc ^ *p++) & 0xFFU] ^ (crc >> 8);
  }
  return crc;
}
