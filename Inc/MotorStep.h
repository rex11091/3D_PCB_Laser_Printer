#ifndef _MOTORSTEP_H
#define _MOTORSTEP_H

#include "MotorController.h"
#include "step.h"

void DoMotorStepping(MotorInfo *MotorInfoTable[]);
void StepMotor(MotorInfo *motorInfo);
void SetAllmotorStep(MotorInfo *MotorInfoTable[]);

#endif // _MOTORSTEP_H
