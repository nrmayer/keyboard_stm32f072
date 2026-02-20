// include ONLY in matrix.c

#include "types.h"

#include "keycodes.h"

#ifndef KEYBOARD_LAYERS
    #define KEYBOARD_LAYERS 1
#endif

const GPIO_Pin ROW_PINS[] = {
    {.letter = GPIOC, .num = GPIO_PIN_15},
    {.letter = GPIOA, .num = GPIO_PIN_1},
    {.letter = GPIOA, .num = GPIO_PIN_0},
};

const GPIO_Pin COL_PINS[] = {
    {.letter = GPIOB, .num = GPIO_PIN_9},
    {.letter = GPIOC, .num = GPIO_PIN_13},
    {.letter = GPIOC, .num = GPIO_PIN_14},
};

const KeyCode KEYBOARD_DEFS[KEYBOARD_LAYERS][sizeof(ROW_PINS)][sizeof(COL_PINS)] = {
    {
        {KEY_1, KEY_2, KEY_3},
        {KEY_4, KEY_5, KEY_6},
        {KEY_7, KEY_8, KEY_9},
    }
};