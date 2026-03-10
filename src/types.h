#ifndef TYPES_H
#define TYPES_H

#include "stm32f072xb.h" // GPIOA, B, C, etc
#include "stm32f0xx_hal.h" // HAL_*()

typedef struct GPIO_Pin {
    GPIO_TypeDef* letter;
    uint16_t num;
} GPIO_Pin;

typedef enum KeyFunctionType {
    KeyLiteral = 0,
    LayerSwitchHold,
    ModifierMask,
} KeyFunctionType;

typedef struct KeyFunction {
    KeyFunctionType function;
    uint8_t value;
} KeyFunction;

#endif