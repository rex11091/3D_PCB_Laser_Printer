#ifndef _MOTORCONTROLLER_H
#define _MOTORCONTROLLER_H

#define true 1
#define false 0

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
};

void setupMotorInfo(MotorInfo *Motorinfo[],int start[],int end[]);
void makeStepbasedOnBrenseham(MotorInfo *MotorInfoTable[]);
void TimerInterruptCheckingStepping(MotorInfo Motorinfo[],int numberOfMotors);

#endif // _MOTORCONTROLLER_H
