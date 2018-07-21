#include "InfoVerifier.h"
#include "unity.h"
#include <stdarg.h>
#include <stdio.h>
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
void testAssertEqualMotorInfo(char name, int delta, int df, int err, int Dostepping, int isReferencing, int start, int end, MotorInfo *MotorInfoTable[],int index,int lineNo){
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
        error = createMessage("Expected startign point to be %d, but was %d",  \
                              start,MotorInfoTable[index]->start);
        UNITY_TEST_FAIL(lineNo,error);
      }
  else if(end != MotorInfoTable[index]->end){
      error = createMessage("Expected ending point to be %d, but was %d",  \
                                  end,MotorInfoTable[index]->end);
        UNITY_TEST_FAIL(lineNo,error);
      }

}
