/**
  * CRC-32 (IEEE 802.3 / zlib: reflected, poly 0xEDB88320, init and final XOR
  * 0xFFFFFFFF). Check value: crc32("123456789") = 0xCBF43926.
  */
#ifndef CRC32_H
#define CRC32_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CRC32_INIT 0xFFFFFFFFU

/* Incremental: crc = crc32_update(CRC32_INIT, ...); ... ; result = crc32_final(crc). */
uint32_t crc32_update(uint32_t crc, const void *data, size_t len);

static inline uint32_t crc32_final(uint32_t crc)
{
  return crc ^ 0xFFFFFFFFU;
}

#ifdef __cplusplus
}
#endif

#endif /* CRC32_H */
