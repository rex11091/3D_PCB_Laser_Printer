#ifndef _EXCEPTION_H
#define _EXCEPTION_H
#include "CExceptionConfig.h"
#include "Error.h"

typedef struct Exception Exception;
typedef Exception* ExceptionPtr;
struct Exception {
  char *msg;
  int  errorCode;
  void *data;
};

Exception *createException(char *msg, int errorCode);
void freeException(Exception *e);
void dumpException(Exception *e);
//void dumpErrorMessage(Exception *e, int lineNo);
void throwException(int errorCode, char *message,void *data ,...);



#endif // _EXCEPTION_H
