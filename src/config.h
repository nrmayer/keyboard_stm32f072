// include ONLY in matrix.c

#include "types.h"

#include "keycodes.h"

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

const GPIO_Pin THUMBPAD_DETECT = {.letter = GPIOA, .num = GPIO_PIN_0};
const GPIO_Pin THUMBPAD_BUTTON1 = {.letter = GPIOA, .num = GPIO_PIN_0};
const GPIO_Pin THUMBPAD_BUTTON2 = {.letter = GPIOA, .num = GPIO_PIN_0};

#define ROW_PINS_NUM sizeof(ROW_PINS) / sizeof(GPIO_Pin)
#define COL_PINS_NUM sizeof(COL_PINS) / sizeof(GPIO_Pin)

#define KEYBOARD_LAYERS 2

const KeyFunction KEYBOARD_DEFS[KEYBOARD_LAYERS][ROW_PINS_NUM][COL_PINS_NUM] = {
    { // layer 1
        {{.value = KEY_A}, {.value = KEY_B}, {.value = KEY_C}},
        {{.value = KEY_D}, {.value = KEY_E}, {.value = KEY_F}},
        {{.value = KEY_G}, {.value = KEY_H}, {.value = KEY_I}}
    },
    { // layer 2
        {{.value = KEY_A}, {.value = KEY_B}, {.value = KEY_C}},
        {{.value = KEY_D}, {.value = KEY_E}, {.value = KEY_F}},
        {{.value = KEY_G}, {.value = KEY_H}, {.value = KEY_I}}
    }
};

const KeyFunction THUMBPAD_DEFS[KEYBOARD_LAYERS][2][1] = {
    { // layer 1
        {{.function = LayerSwitchHold, .value = 1}},
        {{.value = KEY_SPACE}},
    },
    { // layer 2 (same)
        {{.function = LayerSwitchHold, .value = 1}},
        {{.value = KEY_SPACE}},
    }
};