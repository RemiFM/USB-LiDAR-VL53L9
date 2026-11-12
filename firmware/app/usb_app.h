/**
  * USB application layer: TinyUSB bring-up and a CDC echo for testing.
  */
#ifndef USB_APP_H
#define USB_APP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Clocks the USB peripheral from PSIDIV3 (48 MHz, crystal-derived) and starts TinyUSB.
   Call once after mx_system_init(). Returns 0 on success. */
int usb_app_init(void);

/* Run often from the main loop: services TinyUSB. */
void usb_app_task(void);

/* USB serial number: the chip's 96-bit unique ID as 24 hex characters. */
char const *usb_serial_number(void);

#ifdef __cplusplus
}
#endif

#endif /* USB_APP_H */
