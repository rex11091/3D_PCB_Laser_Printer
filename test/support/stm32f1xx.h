#ifndef _STM32F1XX_H
#define _STM32F1XX_H
#include "stdint.h"
#include "stm32f103xb.h"


void HAL_GPIO_WritePin(GPIO_TypeDef *GPIO, uint32_t pin,int GPIO_PinState);
void HAL_TIM_Base_Stop_IT(TIM_HandleTypeDef *htim);
void HAL_TIM_Base_Start_IT(TIM_HandleTypeDef *htim);
#endif // _STM32F1XX_H
