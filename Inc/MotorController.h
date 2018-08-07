#ifndef _MOTORCONTROLLER_H
#define _MOTORCONTROLLER_H

#include "step.h"
#include "Integration.h"
#define ISTRUE 10
#define ISFALSE 11
#define DO_DELAY 12
#define DO_STEPPING 13
#define LOW 0
#define HIGH 1

extern int start_step;

typedef struct MotorInfo MotorInfo;
struct MotorInfo{
  char name;
  int delta;      // selfdelta
  int deltaRef;   // compare line delta
  int error;
  int Dostepping;
  int isReferencing;
  int totalStep;
  GPIO_TypeDef *GPIO;
  int MotorPin;
};
void setupMotorInfo(MotorInfo *Motorinfo[],int delta[]);
void makeStepbasedOnBrenseham(MotorInfo *MotorInfoTable[]);
void clearALLMotorinfoDostepping(MotorInfo *MotorInfoTable[]);


#endif // _MOTORCONTROLLER_H
