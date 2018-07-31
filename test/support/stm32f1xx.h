#ifndef _STM32F1XX_H
#define _STM32F1XX_H
#include "stdint.h"
#include "stm32f103xb.h"

void HAL_GPIO_WritePin(GPIO_TypeDef *GPIO, uint32_t pin,int GPIO_PinState);

#endif // _STM32F1XX_H
