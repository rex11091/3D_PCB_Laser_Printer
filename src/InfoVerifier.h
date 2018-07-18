#ifndef _INFOVERIFIER_H
#define _INFOVERIFIER_H
#include "MotorController.h"


#define TEST_ASSERT_EQUAL_MOTORINFO(name,delta,df,err,Dostepping,isReferencing,start,end,Motorinfo,index) \
                          testAssertEqualMotorInfo(name,delta,df,err,Dostepping,isReferencing,start,end,Motorinfo,index,__LINE__)



void testAssertEqualMotorInfo(char name, int delta, int df, int err, int Dostepping, int isReferencing, int start, int end, MotorInfo Motorinfo[],int index,int lineNo);


#endif // _INFOVERIFIER_H
