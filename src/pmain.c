#include "pmain.h"

#include "stm32f0xx_hal.h"

#include "usb.h"

void pmain(void) {
    init_usb();

    for (;;) {}
}