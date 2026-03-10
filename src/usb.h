#ifndef KEYBOARD_USB_H
#define KEYBOARD_USB_H

#include <stdint.h>
#include <stddef.h>

void init_usb(void);

// static length defined in CubeMX
void usb_hid_send_buffer(uint8_t* buffer, size_t length);

#endif