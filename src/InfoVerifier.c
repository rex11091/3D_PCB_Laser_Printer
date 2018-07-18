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
void testAssertEqualArray(char name, int delta, int df, int err, int Dostepping, int isReferencing, int start, int end, MotorInfo Motorinfo[],int lineNo){
  char *error;
  if(name != Motorinfo->name){
      error = createMessage("Expected motor to be motor %s, but was motor %s",  \
                            name,Motorinfo->name);
      UNITY_TEST_FAIL(lineNo,error);
    }
  else if(delta != Motorinfo->delta){
    error = createMessage("Expected delta to be %d, but was %d",  \
                          delta,Motorinfo->delta);
    UNITY_TEST_FAIL(lineNo,error);
  }
  else if(df != Motorinfo->deltaRef){
    error = createMessage("Expected deltaRef to be %d, but was %d",  \
                          df,Motorinfo->deltaRef);
    UNITY_TEST_FAIL(lineNo,error);
  }
  else if(Dostepping != Motorinfo->Dostepping){
      error = createMessage("Expected Dostepping to be %d, but was %d",  \
                            Dostepping,Motorinfo->Dostepping);
      UNITY_TEST_FAIL(lineNo,error);
    }
  else if(isReferencing != Motorinfo->isReferencing){
      error = createMessage("Expected isReferencing to be %d, but was %d",  \
                            isReferencing,Motorinfo->isReferencing);
      UNITY_TEST_FAIL(lineNo,error);
    }
  else if(start != Motorinfo->start){
        error = createMessage("Expected startign point to be %d, but was %d",  \
                              start,Motorinfo->start);
        UNITY_TEST_FAIL(lineNo,error);
      }
  else if(end != Motorinfo->end){
      error = createMessage("Expected ending point to be %d, but was %d",  \
                                  end,Motorinfo->end);
        UNITY_TEST_FAIL(lineNo,error);
      }

}
