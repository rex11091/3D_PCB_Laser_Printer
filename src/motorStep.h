#ifndef _MOTORSTEP_H
#define _MOTORSTEP_H

typedef struct motorGroup motorGroup;
typedef struct MotorInfo MotorInfo;


struct motorGroup{
    MotorInfo *X;
    MotorInfo *Y;
    MotorInfo *Z;
};

struct MotorInfo{
  char *gpio;
  char *Pin;
};

int motorstepX();
int motorstepY();
int motorstepZ();

#endif // _MOTORSTEP_H
