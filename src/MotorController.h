#ifndef _MOTORCONTROLLER_H
#define _MOTORCONTROLLER_H

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


void setupMotorInfo(MotorInfo Motorinfo[],int start[],int end[],int numbOfMotors);
void MotorMovement(MotorInfo Motorinfo[],int numberOfMotors);
void TimerInterruptCheckingStepping(MotorInfo Motorinfo[],int numberOfMotors);

#endif // _MOTORCONTROLLER_H
