#ifndef _STM32F1XX_H
#define _STM32F1XX_H
#include "stdint.h"
#include "stm32f103xb.h"

#define htim2 91

void HAL_GPIO_WritePin(GPIO_TypeDef *GPIO, uint32_t pin,int GPIO_PinState);
void HAL_TIM_Base_Stop_IT(int htim);
void HAL_TIM_Base_Start_IT(int htim);
#endif // _STM32F1XX_H
