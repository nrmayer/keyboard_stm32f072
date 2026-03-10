#include "usb.h"

#include "stm32f072xb.h"
#include "stm32f0xx_hal.h"

#include "usbd_core.h"
#include "usbd_desc.h"

#include "usbd_customhid.h"

extern USBD_HandleTypeDef hUsbDeviceFS;

__ALIGN_BEGIN static uint8_t HID_REPORT_DESCRIPTOR[] __ALIGN_END = {
    0x05, 0x01,                         // Usage Page (Generic Desktop)
    0x09, 0x06,                         // Usage (Keyboard)
    0xA1, 0x01,                         // Collection (Application)

    // bitfield
    // ctrl, shift, alt, meta, etc
    0x05, 0x07,                         //     Usage Page (Key Codes)
    0x19, 0xe0,                         //     Usage Minimum (224)
    0x29, 0xe7,                         //     Usage Maximum (231)
    0x15, 0x00,                         //     Logical Minimum (0)
    0x25, 0x01,                         //     Logical Maximum (1)
    0x75, 0x01,                         //     Report Size (1)
    0x95, 0x08,                         //     Report Count (8)
    0x81, 0x02,                         //     Input (Data, Variable, Absolute)

    // reserved (USB HID keyboard spec)
    0x95, 0x01,                         //     Report Count (1)
    0x75, 0x08,                         //     Report Size (8)
    0x81, 0x01,                         //     Input (Constant) reserved byte(1)

    // Actual keycodes
    0x95, 0x06,                         //     Report Count (6)
    0x75, 0x08,                         //     Report Size (8)
    0x15, 0x00,                         //     Logical Minimum (0)
    0x25, 0x65,                         //     Logical Maximum (101)
    0x05, 0x07,                         //     Usage Page (Key codes)
    0x19, 0x00,                         //     Usage Minimum (0)
    0x29, 0x65,                         //     Usage Maximum (101)
    0x81, 0x00,                         //     Input (Data, Array) Key array(6 bytes)

    0xC0                                // End Collection (Application)    
};

static int8_t handle_init_usb(void);
static int8_t handle_deinit_usb(void);
static int8_t handle_out_usb(uint8_t event_idx, uint8_t state);

USBD_CUSTOM_HID_ItfTypeDef usbd_hid_handle = {
    HID_REPORT_DESCRIPTOR,
    handle_init_usb,
    handle_deinit_usb,
    handle_out_usb,
};

void init_usb(void) {
    USBD_Init(&hUsbDeviceFS, &FS_Desc, 0);
    USBD_RegisterClass(&hUsbDeviceFS, &USBD_CUSTOM_HID);

    USBD_CUSTOM_HID_RegisterInterface(&hUsbDeviceFS, &usbd_hid_handle);

    USBD_Start(&hUsbDeviceFS);
}

void usb_hid_send_buffer(uint8_t* buffer, size_t length) {
    USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, buffer, length);
}

static int8_t handle_init_usb(void) {
    return USBD_OK;
}

static int8_t handle_deinit_usb(void) {
    return USBD_OK;
}

static int8_t handle_out_usb(uint8_t event_idx, uint8_t state) {
    return USBD_OK;
}