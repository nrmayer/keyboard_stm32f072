// include ONLY in matrix.c

#include "types.h"

#include "keycodes.h"

const GPIO_Pin ROW_PINS[] = {
    {.letter = GPIOB, .num = GPIO_PIN_8},
    {.letter = GPIOB, .num = GPIO_PIN_7},
    {.letter = GPIOB, .num = GPIO_PIN_6},
    {.letter = GPIOB, .num = GPIO_PIN_0},
    {.letter = GPIOB, .num = GPIO_PIN_1},
};

const GPIO_Pin COL_PINS[] = {
    {.letter = GPIOA, .num = GPIO_PIN_15},
    {.letter = GPIOB, .num = GPIO_PIN_3},
    {.letter = GPIOB, .num = GPIO_PIN_4},
    {.letter = GPIOB, .num = GPIO_PIN_5},
    {.letter = GPIOB, .num = GPIO_PIN_9},
    {.letter = GPIOA, .num = GPIO_PIN_5},
    {.letter = GPIOA, .num = GPIO_PIN_6},
    {.letter = GPIOA, .num = GPIO_PIN_7},
};

const GPIO_Pin THUMBPAD_DETECT = {.letter = GPIOA, .num = GPIO_PIN_0};
const GPIO_Pin THUMBPAD_BUTTON1 = {.letter = GPIOA, .num = GPIO_PIN_0};
const GPIO_Pin THUMBPAD_BUTTON2 = {.letter = GPIOA, .num = GPIO_PIN_0};

#define ROW_PINS_NUM sizeof(ROW_PINS) / sizeof(GPIO_Pin)
#define COL_PINS_NUM sizeof(COL_PINS) / sizeof(GPIO_Pin)

#define KEYBOARD_LAYERS 2

KeyFunction KEYBOARD_DEFS[KEYBOARD_LAYERS][ROW_PINS_NUM][COL_PINS_NUM] = {
    { // layer 0 (left)
        {{.value = KEY_GRAVE},{.value = KEY_1},{.value = KEY_2},{.value = KEY_3},{.value = KEY_4},{.value = KEY_5},{.value = KEY_6},{.value = KEY_7}},
        {{.value = KEY_TAB},{.value = KEY_Q},{.value = KEY_W},{.value = KEY_E},{.value = KEY_R},{.value = KEY_T},{.value = KEY_Y},{.value = KEY_U}},
        {{.value = KEY_CAPSLOCK},{.value = KEY_A},{.value = KEY_S},{.value = KEY_D},{.value = KEY_F},{.value = KEY_G},{.value = KEY_H},{.value = KEY_J}},
        {{.function = ModifierMask, .value=KEY_MOD_LSHIFT},{.value = KEY_Z},{.value = KEY_X},{.value = KEY_C},{.value = KEY_V},{.value = KEY_B},{.value = KEY_N},{.value = KEY_M}},
        {{.value = KEY_A},{.value = KEY_A},{.value = KEY_A},{.value = KEY_A},{.value = KEY_A},{.value = KEY_A},{.value = KEY_A},{.value = KEY_A}},
    },
    { // layer 1 (right)
        {{.value = KEY_6},{.value = KEY_7},{.value = KEY_8},{.value = KEY_9},{.value = KEY_0},{.value = KEY_MINUS},{.value = KEY_EQUAL},{.value = KEY_BACKSPACE}},
        {{.value = KEY_Y},{.value = KEY_U},{.value = KEY_I},{.value = KEY_O},{.value = KEY_P},{.value = KEY_LEFTBRACE},{.value = KEY_RIGHTBRACE},{.value = KEY_BACKSLASH}},
        {{.value = KEY_G},{.value = KEY_H},{.value = KEY_J},{.value = KEY_K},{.value = KEY_L},{.value = KEY_SEMICOLON},{.value = KEY_APOSTROPHE},{.value = KEY_ENTER}},
        {{.value = KEY_V},{.value = KEY_B},{.value = KEY_N},{.value = KEY_M},{.value = KEY_COMMA},{.value = KEY_DOT},{.value = KEY_SLASH},{.function=ModifierMask, .value=KEY_MOD_RSHIFT}},
        {{.value = KEY_A},{.value = KEY_A},{.value = KEY_A},{.value = KEY_A},{.value = KEY_A},{.value = KEY_A},{.value = KEY_A},{.value = KEY_A}},
    }
};

const KeyFunction THUMBPAD_DEFS[KEYBOARD_LAYERS][2][1] = {
    { // layer 0
        {{.function = LayerSwitchHold, .value = 1}},
        {{.value = KEY_SPACE}},
    },
    { // layer 1 (default if keypad on left)
        {{.function = LayerSwitchHold, .value = 0}},
        {{.value = KEY_SPACE}},
    }
};