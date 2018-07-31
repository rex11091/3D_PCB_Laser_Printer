#ifndef _INFOVERIFIER_H
#define _INFOVERIFIER_H
#include "MotorController.h"
#include "stm32f103xb.h"


#define TEST_ASSERT_EQUAL_MOTORINFO(name,delta,df,err,Dostepping,isReferencing,MotorPin,Motorinfo,index) \
                          testAssertEqualMotorInfo(name,delta,df,err,Dostepping,isReferencing,MotorPin,Motorinfo,index,__LINE__)


#define TEST_ASSERT_EQUAL_MOTOR_STEP(motorX,motorY,motorZ,DosteppingX,DosteppingY,DosteppingZ) \
                          testAssertEqualMotorStepping(motorX,motorY,motorZ,DosteppingX,DosteppingY,DosteppingZ,__LINE__)


void testAssertEqualMotorInfo(char name, int delta, int df, int err, int Dostepping, int isReferencing,\
                              int MotorPin, MotorInfo *MotorInfoTable[],int index,int lineNo);

void testAssertEqualMotorStepping(int motorX,int motorY,int motorZ, int DosteppingX, int DosteppingY,\
                              int DosteppingZ,int lineNo);
#endif // _INFOVERIFIER_H
