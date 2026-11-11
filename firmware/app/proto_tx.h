/**
  * Non-blocking packet transmitter for the USB CDC protocol (protocol.h).
  *
  * - Small packets (info, log, status, IMU) are copied into a queue and can be
  *   sent from anywhere in the main context.
  * - Large packets (LiDAR frame, calibration) are sent zero-copy from the
  *   caller's buffer, which must stay untouched until proto_tx_in_use() says so.
  * - Packets never interleave on the wire; sequence numbers and CRCs are filled
  *   in when a packet starts transmitting, so seq is always in wire order.
  * - proto_tx_pump() moves bytes into TinyUSB; call it often.
  */
#ifndef PROTO_TX_H
#define PROTO_TX_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PROTO_SMALL_MAX_PAYLOAD 480U

/* Drops everything queued (call when the host disconnects). */
void proto_tx_reset(void);

/* Queues a small packet (payload copied). False if it doesn't fit: counted as dropped. */
bool proto_tx_send(uint8_t type, const void *payload, uint32_t len, uint64_t t_us);

/* Queues a large packet = prefix (copied, <= 32 bytes) + data (NOT copied).
   False if the large-packet queue is full. */
bool proto_tx_send_large(uint8_t type, const void *prefix, uint32_t prefix_len,
                         const void *data, uint32_t data_len, uint64_t t_us);

/* True while `data` is queued or being sent by proto_tx_send_large(). */
bool proto_tx_in_use(const void *data);

/* Writes as many bytes as TinyUSB accepts. */
void proto_tx_pump(void);

uint32_t proto_tx_dropped(void);

#ifdef __cplusplus
}
#endif

#endif /* PROTO_TX_H */
