/**
  * USB descriptors: one CDC ACM interface (shows up as /dev/ttyACMx).
  * VID:PID cafe:4010 is the development ID also used by the VL53L9-UNO-Q-LiDAR
  * firmware (0xcafe is TinyUSB's example vendor ID, not a registered production VID).
  */
#include <string.h>
#include "stm32c5xx.h"   /* UID_BASE */
#include "tusb.h"

#define USB_VID   0xCAFEU
#define USB_PID   0x4010U

enum { ITF_NUM_CDC = 0, ITF_NUM_CDC_DATA, ITF_NUM_TOTAL };

#define EPNUM_CDC_NOTIF   0x81U
#define EPNUM_CDC_OUT     0x02U
#define EPNUM_CDC_IN      0x82U

enum { STR_LANGID = 0, STR_MANUFACTURER, STR_PRODUCT, STR_SERIAL, STR_CDC, STR_COUNT };

static tusb_desc_device_t const desc_device =
{
  .bLength            = sizeof(tusb_desc_device_t),
  .bDescriptorType    = TUSB_DESC_DEVICE,
  .bcdUSB             = 0x0200,
  /* IAD so hosts group the two CDC interfaces into one function */
  .bDeviceClass       = TUSB_CLASS_MISC,
  .bDeviceSubClass    = MISC_SUBCLASS_COMMON,
  .bDeviceProtocol    = MISC_PROTOCOL_IAD,
  .bMaxPacketSize0    = CFG_TUD_ENDPOINT0_SIZE,
  .idVendor           = USB_VID,
  .idProduct          = USB_PID,
  .bcdDevice          = 0x0001,
  .iManufacturer      = STR_MANUFACTURER,
  .iProduct           = STR_PRODUCT,
  .iSerialNumber      = STR_SERIAL,
  .bNumConfigurations = 1
};

uint8_t const *tud_descriptor_device_cb(void)
{
  return (uint8_t const *)&desc_device;
}

#define CONFIG_TOTAL_LEN  (TUD_CONFIG_DESC_LEN + TUD_CDC_DESC_LEN)

static uint8_t const desc_configuration[] =
{
  /* config number, interface count, string index, total length, attributes, power in mA */
  TUD_CONFIG_DESCRIPTOR(1, ITF_NUM_TOTAL, 0, CONFIG_TOTAL_LEN, 0, 500),
  /* interface number, string index, notification EP & size, data OUT & IN EPs, EP size */
  TUD_CDC_DESCRIPTOR(ITF_NUM_CDC, STR_CDC, EPNUM_CDC_NOTIF, 8, EPNUM_CDC_OUT, EPNUM_CDC_IN, 64),
};

uint8_t const *tud_descriptor_configuration_cb(uint8_t index)
{
  (void)index;
  return desc_configuration;
}

static char const *const string_desc[STR_COUNT] =
{
  [STR_LANGID]       = "",                    /* handled separately below */
  [STR_MANUFACTURER] = "RemiFM",
  [STR_PRODUCT]      = "USB LiDAR & IMU",
  [STR_SERIAL]       = "",                    /* built from the chip's unique ID */
  [STR_CDC]          = "USB LiDAR & IMU CDC",
};

/* 24 uppercase hex characters from the 96-bit factory unique ID (UID_BASE),
   so every board gets its own serial and its own /dev/serial/by-id/ link. */
char const *usb_serial_number(void)
{
  static char serial[24 + 1];
  static char const hex[] = "0123456789ABCDEF";
  uint32_t const *uid = (uint32_t const *)UID_BASE;

  if (serial[0] == '\0')
  {
    for (unsigned w = 0; w < 3U; w++)
    {
      /* Most significant word first, matching how ST tools print the UID. */
      uint32_t v = uid[2U - w];
      for (unsigned n = 0; n < 8U; n++)
      {
        serial[w * 8U + n] = hex[(v >> (28U - 4U * n)) & 0xFU];
      }
    }
    serial[24] = '\0';
  }
  return serial;
}

uint16_t const *tud_descriptor_string_cb(uint8_t index, uint16_t langid)
{
  static uint16_t desc_str[32 + 1];
  size_t chr_count;
  (void)langid;

  if (index == STR_LANGID)
  {
    desc_str[1] = 0x0409; /* English (US) */
    chr_count = 1;
  }
  else
  {
    if (index >= STR_COUNT)
    {
      return NULL;
    }
    char const *str = (index == STR_SERIAL) ? usb_serial_number() : string_desc[index];
    chr_count = strlen(str);
    if (chr_count > 32U)
    {
      chr_count = 32U;
    }
    for (size_t i = 0; i < chr_count; i++)
    {
      desc_str[1 + i] = (uint8_t)str[i];
    }
  }

  /* first element: length (bytes, incl. header) and descriptor type */
  desc_str[0] = (uint16_t)((TUSB_DESC_STRING << 8) | (2U * chr_count + 2U));
  return desc_str;
}
