#ifndef _MOTORCONTROLLER_H
#define _MOTORCONTROLLER_H
#include "motorPin.h"
#include "timerinterrupt.h"


typedef struct MotorInfo MotorInfo;
struct MotorInfo{
  char name;
  int delta;      // selfdelta
  int deltaRef;   // compare line delta
  int error;
  int Dostepping;
  int isReferencing;
};
void try1(int x);
void setupMotorInfo(MotorInfo Motorinfo[],int start[],int end[],int numbOfMotors);
// void setupMovement(int start[],int end[],MotorInfo *MotorInfo1,MotorInfo *MotorInfo2);
// void CheckEitherChangeOrNoChange(MotorInfo *MotorInfo1, MotorInfo *MotorInfo2);
// void MotorToNextStep(MotorInfo *MotorInfo1, MotorInfo *MotorInfo2);
// void MotorMovement(MotorInfo *MotorInfo1, MotorInfo *MotorInfo2);
#endif // _MOTORCONTROLLER_H
