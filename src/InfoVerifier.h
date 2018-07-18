#ifndef _INFOVERIFIER_H
#define _INFOVERIFIER_H
#include "MotorController.h"


#define TEST_ASSERT_EQUAL_ARRAY(name,delta,df,err,Dostepping,isReferencing,start,end,Motorinfo) \
                          testAssertEqualArray(name,delta,df,err,Dostepping,isReferencing,start,end,Motorinfo,__LINE__)


void testAssertEqualArray(char name, int delta, int df, int err, int Dostepping, int isReferencing, int start, int end, MotorInfo Motorinfo[],int lineNo);



#endif // _INFOVERIFIER_H
