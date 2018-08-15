/*
 * hardwareConfig.h
 *
 *  Created on: Aug 15, 2018
 *      Author: rex
 */
#ifndef HARDWARECONFIG_H_
#define HARDWARECONFIG_H_
#include "UserConfig.h"
#include "MotorController.h"
#include "MotorStep.h"
#include "main.h"
#include "CommandCode.h"
#include "usbd_cdc_if.h"
#include "Exception.h"
#include "CExceptionConfig.h"
#include "CException.h"
#include "Error.h"

int E;

extern GCodeMapping GCode00[];
CEXCEPTION_T ex;
extern VariableMap g01VarTableMapping[];
extern VariableMap g00VarTableMapping[];
extern StoreCMD cmd1;
extern Variable xVar;
extern Variable yVar;
extern Variable x1Var;
extern Variable y1Var;
extern Variable fVar;
extern int Steps[2];
extern char *complete;
extern char buffer1[100];
//  Variable zVar = {0,0,0,0};

void DecodeandStepMotor(void);
void configureMotorandStartTimer(void);
#endif /* HARDWARECONFIG_H_ */
