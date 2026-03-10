#include "pmain.h"

#include "stm32f0xx_hal.h"

#include "usb.h"
#include "matrix.h"

void pmain(void) {
    init_usb();

    start_matrix_scan();

    for (;;) {}
}