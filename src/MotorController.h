#ifndef _MOTORCONTROLLER_H
#define _MOTORCONTROLLER_H
#include "motorPin.h"
#include "timerinterrupt.h"


typedef struct MotorInfo MotorInfo;
struct MotorInfo {
  int delta;      // selfdelta
  int deltaRef;   // compare line delta
  int initial_point; //self starting point
  int diff;
  int coordinate[2];   //from starting point to ending point
  int change;          // change =1 if delta < deltaRef;
  MotorPin motorPin;
};
void setupMovement(int start[],int end[],MotorInfo *MotorInfo1,MotorInfo *MotorInfo2);
void CheckEitherChangeOrNoChange(MotorInfo *MotorInfo1, MotorInfo *MotorInfo2);
void MotorToNextStep(MotorInfo *MotorInfo1, MotorInfo *MotorInfo2);
void MotorMovement(MotorInfo *MotorInfo1, MotorInfo *MotorInfo2);
#endif // _MOTORCONTROLLER_H
