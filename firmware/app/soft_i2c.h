/**
  * Bit-banged I2C on the LiDAR bus (SDA = PA8, SCL = PB4), open-drain with the
  * board's external pull-ups. Used to discover the VL53L9 at its static address
  * before I3C takes over, and as a fallback if I3C setup fails.
  * Ported from VL53L9-UNO-Q-LiDAR (application/soft_i2c.c).
  */
#ifndef SOFT_I2C_H
#define SOFT_I2C_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Return codes: 0 ok, 1 NACK, 2 bus stuck / clock stretched too long. */
void soft_i2c_init(void);              /* pins to GPIO open-drain, ~1 MHz timing */
void soft_i2c_relax(void);             /* next init uses slow (~400 kHz) recovery timing */
int  soft_i2c_probe(uint8_t address);
int  soft_i2c_read(uint8_t address, uint16_t reg, uint8_t *data, uint32_t size);
int  soft_i2c_write(uint8_t address, uint16_t reg, const uint8_t *data, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif /* SOFT_I2C_H */
