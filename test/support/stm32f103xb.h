#ifndef _STM32F103XB_H
#define _STM32F103XB_H
#include "stdint.h"

#define __IO
typedef struct
{
  __IO uint32_t CRL;
  __IO uint32_t CRH;
  __IO uint32_t IDR;
  __IO uint32_t ODR;
  __IO uint32_t BSRR;
  __IO uint32_t BRR;
  __IO uint32_t LCKR;
} GPIO_TypeDef;


typedef struct
{
int x;
}TIM_HandleTypeDef;

#endif // _STM32F103XB_H
