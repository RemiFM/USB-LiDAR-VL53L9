#include <string.h>
#include "proto_tx.h"
#include "protocol.h"
#include "crc32.h"
#include "tusb.h"

/* ------------------------------------------------------------------ small-packet queue
   Records: [type u8][len u16 LE][t_us u64 LE][payload len bytes], back to back in a ring. */
#define RING_SIZE        4096U
#define RECORD_HEAD      11U

static uint8_t ring[RING_SIZE];
static uint32_t ring_head;   /* write index */
static uint32_t ring_tail;   /* read index */
static uint32_t ring_used;

static void ring_put(const void *src, uint32_t n)
{
  const uint8_t *p = (const uint8_t *)src;
  while (n--)
  {
    ring[ring_head] = *p++;
    ring_head = (ring_head + 1U) % RING_SIZE;
  }
}

static void ring_get(void *dst, uint32_t n)
{
  uint8_t *p = (uint8_t *)dst;
  while (n--)
  {
    *p++ = ring[ring_tail];
    ring_tail = (ring_tail + 1U) % RING_SIZE;
  }
}

/* ------------------------------------------------------------------ large-packet queue */
#define LARGE_QUEUE      2U
#define LARGE_PREFIX_MAX 32U

typedef struct
{
  uint8_t type;
  uint8_t prefix[LARGE_PREFIX_MAX];
  uint32_t prefix_len;
  const uint8_t *data;
  uint32_t data_len;
  uint64_t t_us;
} large_t;

static large_t large_q[LARGE_QUEUE];
static uint32_t large_count;   /* entries in large_q (index 0 = next) */

/* ------------------------------------------------------------------ packet being sent
   Up to four segments: header, body A, body B, CRC. */
static struct
{
  bool active;
  bool is_large;
  const uint8_t *seg[4];
  uint32_t seg_len[4];
  uint32_t seg_idx;
  uint32_t seg_off;
  uint32_t crc;
  const uint8_t *large_data;   /* for proto_tx_in_use() */
} cur;

static uint8_t hdr[PROTO_HEADER_SIZE];
static uint8_t crc_bytes[PROTO_CRC_SIZE];
static uint8_t small_payload[PROTO_SMALL_MAX_PAYLOAD];
static uint32_t seq;
static uint32_t dropped;

static void put_u32(uint8_t *p, uint32_t v)
{
  p[0] = (uint8_t)v; p[1] = (uint8_t)(v >> 8); p[2] = (uint8_t)(v >> 16); p[3] = (uint8_t)(v >> 24);
}

static void begin(uint8_t type, uint64_t t_us, const uint8_t *a, uint32_t a_len,
                  const uint8_t *b, uint32_t b_len, bool is_large)
{
  uint32_t len = a_len + b_len;
  hdr[0] = PROTO_SYNC0;
  hdr[1] = PROTO_SYNC1;
  hdr[2] = type;
  hdr[3] = PROTO_VERSION;
  put_u32(&hdr[4], seq++);
  put_u32(&hdr[8], (uint32_t)t_us);
  put_u32(&hdr[12], (uint32_t)(t_us >> 32));
  put_u32(&hdr[16], len);

  cur.seg[0] = hdr;       cur.seg_len[0] = PROTO_HEADER_SIZE;
  cur.seg[1] = a;         cur.seg_len[1] = a_len;
  cur.seg[2] = b;         cur.seg_len[2] = b_len;
  cur.seg[3] = crc_bytes; cur.seg_len[3] = PROTO_CRC_SIZE;
  cur.seg_idx = 0U;
  cur.seg_off = 0U;
  cur.crc = CRC32_INIT;
  cur.is_large = is_large;
  cur.active = true;
}

static bool start_next(void)
{
  if (ring_used > 0U)
  {
    uint8_t rh[RECORD_HEAD];
    ring_get(rh, RECORD_HEAD);
    uint32_t len = (uint32_t)rh[1] | ((uint32_t)rh[2] << 8);
    uint64_t t_us = 0;
    memcpy(&t_us, &rh[3], sizeof(t_us));
    ring_get(small_payload, len);
    ring_used -= RECORD_HEAD + len;
    begin(rh[0], t_us, small_payload, len, NULL, 0U, false);
    cur.large_data = NULL;
    return true;
  }
  if (large_count > 0U)
  {
    static large_t l;   /* prefix must outlive the queue slot */
    l = large_q[0];
    for (uint32_t i = 1; i < large_count; i++)
    {
      large_q[i - 1U] = large_q[i];
    }
    large_count--;
    begin(l.type, l.t_us, l.prefix, l.prefix_len, l.data, l.data_len, true);
    cur.large_data = l.data;
    return true;
  }
  return false;
}

void proto_tx_reset(void)
{
  ring_head = ring_tail = ring_used = 0U;
  large_count = 0U;
  cur.active = false;
  cur.large_data = NULL;
}

bool proto_tx_send(uint8_t type, const void *payload, uint32_t len, uint64_t t_us)
{
  if (len > PROTO_SMALL_MAX_PAYLOAD || ring_used + RECORD_HEAD + len > RING_SIZE)
  {
    dropped++;
    return false;
  }
  uint8_t rh[RECORD_HEAD];
  rh[0] = type;
  rh[1] = (uint8_t)len;
  rh[2] = (uint8_t)(len >> 8);
  memcpy(&rh[3], &t_us, sizeof(t_us));
  ring_put(rh, RECORD_HEAD);
  ring_put(payload, len);
  ring_used += RECORD_HEAD + len;
  return true;
}

bool proto_tx_send_large(uint8_t type, const void *prefix, uint32_t prefix_len,
                         const void *data, uint32_t data_len, uint64_t t_us)
{
  if (large_count >= LARGE_QUEUE || prefix_len > LARGE_PREFIX_MAX ||
      prefix_len + data_len > PROTO_MAX_PAYLOAD)
  {
    return false;
  }
  large_t *l = &large_q[large_count++];
  l->type = type;
  if (prefix_len > 0U)
  {
    memcpy(l->prefix, prefix, prefix_len);
  }
  l->prefix_len = prefix_len;
  l->data = (const uint8_t *)data;
  l->data_len = data_len;
  l->t_us = t_us;
  return true;
}

bool proto_tx_in_use(const void *data)
{
  if (cur.active && cur.large_data == data)
  {
    return true;
  }
  for (uint32_t i = 0; i < large_count; i++)
  {
    if (large_q[i].data == data)
    {
      return true;
    }
  }
  return false;
}

void proto_tx_pump(void)
{
  if (!tud_cdc_connected())
  {
    proto_tx_reset();
    return;
  }

  bool wrote = false;
  for (;;)
  {
    if (!cur.active && !start_next())
    {
      break;
    }

    /* Skip empty segments; finalize the CRC just before its segment is sent. */
    while (cur.seg_idx < 4U && cur.seg_off >= cur.seg_len[cur.seg_idx])
    {
      cur.seg_idx++;
      cur.seg_off = 0U;
      if (cur.seg_idx == 3U)
      {
        put_u32(crc_bytes, crc32_final(cur.crc));
      }
    }
    if (cur.seg_idx >= 4U)
    {
      cur.active = false;
      cur.large_data = NULL;
      continue;
    }

    uint32_t avail = tud_cdc_write_available();
    if (avail == 0U)
    {
      break;
    }
    const uint8_t *p = cur.seg[cur.seg_idx] + cur.seg_off;
    uint32_t n = cur.seg_len[cur.seg_idx] - cur.seg_off;
    if (n > avail)
    {
      n = avail;
    }
    n = tud_cdc_write(p, n);
    if (n == 0U)
    {
      break;
    }
    if (cur.seg_idx < 3U)
    {
      cur.crc = crc32_update(cur.crc, p, n);
    }
    cur.seg_off += n;
    wrote = true;
  }
  if (wrote)
  {
    tud_cdc_write_flush();
  }
}

uint32_t proto_tx_dropped(void)
{
  return dropped;
}
