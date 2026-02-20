#include "matrix.h"

#include "config.h"

#define ROW_PINS_NUM sizeof(ROW_PINS) / sizeof(GPIO_Pin)
#define COL_PINS_NUM sizeof(COL_PINS) / sizeof(GPIO_Pin)

static int current_layer = 0;
static int matrix_pin_states[ROW_PINS_NUM][COL_PINS_NUM];

void update_matrix() {
    int changed = 0;
    
    for (int col = 0; col <  COL_PINS_NUM; ++col) {
        HAL_GPIO_WritePin(COL_PINS[col].letter, COL_PINS[col].num, 1);
        
        for (int row = 0; row < ROW_PINS_NUM; ++row) {
            int pin_state = HAL_GPIO_ReadPin(ROW_PINS[row].letter, ROW_PINS[row].num);
            if (pin_state == matrix_pin_states[row][col]) continue;
            matrix_pin_states[row][col] = pin_state;
            changed = 1;
        }

        HAL_GPIO_WritePin(COL_PINS[col].letter, COL_PINS[col].num, 0);
    }

    if (changed) {
        // get keycodes and send USB update
    }
}