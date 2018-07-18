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
void testAssertEqualMotorInfo(char name, int delta, int df, int err, int Dostepping, int isReferencing, int start, int end, MotorInfo Motorinfo[],int index,int lineNo){
  char *error;
  if(name != Motorinfo[index].name){
      error = createMessage("Expected motor to be motor (%c), but was motor (%c)",  \
                            name,Motorinfo[index].name);
      UNITY_TEST_FAIL(lineNo,error);
    }
  else if(delta != Motorinfo[index].delta){
    error = createMessage("Expected delta to be %d, but was %d",  \
                          delta,Motorinfo[index].delta);
    UNITY_TEST_FAIL(lineNo,error);
  }
  else if(df != Motorinfo[index].deltaRef){
    error = createMessage("Expected deltaRef to be %d, but was %d",  \
                          df,Motorinfo[index].deltaRef);
    UNITY_TEST_FAIL(lineNo,error);
  }
  else if(err != Motorinfo[index].error){
    error = createMessage("Expected error to be %d, but was %d",  \
                          err,Motorinfo[index].error);
    UNITY_TEST_FAIL(lineNo,error);
  }
  else if(Dostepping != Motorinfo[index].Dostepping){
      error = createMessage("Expected Dostepping to be %d, but was %d",  \
                            Dostepping,Motorinfo[index].Dostepping);
      UNITY_TEST_FAIL(lineNo,error);
    }
  else if(isReferencing != Motorinfo[index].isReferencing){
      error = createMessage("Expected isReferencing to be %d, but was %d",  \
                            isReferencing,Motorinfo[index].isReferencing);
      UNITY_TEST_FAIL(lineNo,error);
    }
  else if(start !=Motorinfo[index].start){
        error = createMessage("Expected startign point to be %d, but was %d",  \
                              start,Motorinfo[index].start);
        UNITY_TEST_FAIL(lineNo,error);
      }
  else if(end != Motorinfo[index].end){
      error = createMessage("Expected ending point to be %d, but was %d",  \
                                  end,Motorinfo[index].end);
        UNITY_TEST_FAIL(lineNo,error);
      }

}
