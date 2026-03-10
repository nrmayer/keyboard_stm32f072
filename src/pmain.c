#include "pmain.h"

#include "stm32f0xx_hal.h"

#include "usb.h"
#include "matrix.h"

uint8_t buffer[8];

void pmain(void) {
    init_usb();

    start_matrix_scan();

    for (;;) {}
}