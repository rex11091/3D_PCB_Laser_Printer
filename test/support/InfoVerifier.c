#include "InfoVerifier.h"
#include "unity.h"
#include <stdarg.h>
#include <stdio.h>
#include "string.h"
#include <malloc.h>
#include "MotorController.h"


char *createMessage(char *message, ...){
  va_list args;
  char *buffer;
  int length;

  va_start(args,message);

  length = vsnprintf(buffer, 0, message, args);
  buffer = malloc(length+1);
  vsnprintf(buffer, length+1, message, args);

  return buffer;
}
void testAssertEqualMotorInfo(char name, int delta, int df, int err, int Dostepping, int isReferencing, int start, int end,int MotorPin, MotorInfo *MotorInfoTable[],int index,int lineNo){
  char *error;
  if(name != MotorInfoTable[index]->name){
      error = createMessage("Expected motor to be motor (%c), but was motor (%c)",  \
                            name,MotorInfoTable[index]->name);
      UNITY_TEST_FAIL(lineNo,error);
    }
  else if(delta != MotorInfoTable[index]->delta){
    error = createMessage("Expected delta to be %d, but was %d",  \
                          delta,MotorInfoTable[index]->delta);
    UNITY_TEST_FAIL(lineNo,error);
  }
  else if(df != MotorInfoTable[index]->deltaRef){
    error = createMessage("Expected deltaRef to be %d, but was %d",  \
                          df,MotorInfoTable[index]->deltaRef);
    UNITY_TEST_FAIL(lineNo,error);
  }
  else if(err != MotorInfoTable[index]->error){
    error = createMessage("Expected error to be %d, but was %d",  \
                          err,MotorInfoTable[index]->error);
    UNITY_TEST_FAIL(lineNo,error);
  }
  else if(Dostepping != MotorInfoTable[index]->Dostepping){
      error = createMessage("Expected Dostepping to be %d, but was %d",  \
                            Dostepping,MotorInfoTable[index]->Dostepping);
      UNITY_TEST_FAIL(lineNo,error);
    }
  else if(isReferencing != MotorInfoTable[index]->isReferencing){
      error = createMessage("Expected isReferencing to be %d, but was %d",  \
                            isReferencing,MotorInfoTable[index]->isReferencing);
      UNITY_TEST_FAIL(lineNo,error);
    }
  else if(start !=MotorInfoTable[index]->start){
        error = createMessage("Expected starting point to be %d, but was %d",  \
                              start,MotorInfoTable[index]->start);
        UNITY_TEST_FAIL(lineNo,error);
      }
  else if(end != MotorInfoTable[index]->end){
      error = createMessage("Expected ending point to be %d, but was %d",  \
                                  end,MotorInfoTable[index]->end);
        UNITY_TEST_FAIL(lineNo,error);
      }
else if(MotorPin != MotorInfoTable[index]->MotorPin){
      error = createMessage("Expected MotorPin to be %d, but was %d",  \
                                      MotorPin,MotorInfoTable[index]->MotorPin);
        UNITY_TEST_FAIL(lineNo,error);
      }

}


void testAssertEqualMotorStepping(int motorX,int motorY,int motorZ, int DosteppingX, int DosteppingY,\
                              int DosteppingZ,int lineNo){
  char *error;
  if(motorX != DosteppingX){
      error = createMessage("Expected DoStepping X to be motor (%d), but was (%d)",  \
                            motorX,DosteppingX);
      UNITY_TEST_FAIL(lineNo,error);
    }
  else if(motorY != DosteppingY){
      error = createMessage("Expected DoStepping Y to be motor (%d), but was (%d)",  \
                            motorY,DosteppingY);
      UNITY_TEST_FAIL(lineNo,error);
    }
  else if(motorZ != DosteppingZ){
      error = createMessage("Expected DoStepping Z to be motor (%d), but was (%d)",  \
                            motorZ,DosteppingZ);
      UNITY_TEST_FAIL(lineNo,error);
    }

}
