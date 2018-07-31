#ifndef _MOTORCONTROLLER_H
#define _MOTORCONTROLLER_H

#include "stm32f103xb.h"
#define TRUE 10
#define FALSE 11
#define DO_DELAY 12
#define DO_STEPPING 13
#define LOW 0
#define HIGH 1


typedef struct MotorInfo MotorInfo;
struct MotorInfo{
  char name;
  int delta;      // selfdelta
  int deltaRef;   // compare line delta
  int error;
  int Dostepping;
  int isReferencing;
  int start;
  int end;
  GPIO_TypeDef GPIO;
  int MotorPin;
};
void motorStep(MotorInfo *MotorInfoTable[]);
void setupMotorInfo(MotorInfo *Motorinfo[],int start[],int end[]);
void makeStepbasedOnBrenseham(MotorInfo *MotorInfoTable[]);
void clearALLMotorinfoDostepping(MotorInfo *MotorInfoTable[]);


#endif // _MOTORCONTROLLER_H
