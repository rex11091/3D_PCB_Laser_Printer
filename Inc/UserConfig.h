#ifndef USERCONFIG_H_
#define USERCONFIG_H_
#include "MotorController.h"
#include "MotorStep.h"
#include "main.h"
#include "CommandCode.h"
#include "usbd_cdc_if.h"
#include "Exception.h"
#include "CExceptionConfig.h"
#include "CException.h"
#include "Error.h"

#define HANDLE_CURRENT_CMD 100
#define WAIT_FOR_CURRENT_CMD_TO_COMPLETE 101
#define HANDLE_NEXT_CMD 102
#define DOSTEPPING 103
#define COMPLETE 104
#define MOTOR_DO_NEXT 105

// motor step intervert period
#define MOTOR_STEP_INT_PERIOD 6000
//motor pulse period
#define MOTOR_STEPING_PERIOD  2

#define HIGH	1
#define LOW		0

//motorpin to gpio pin
#define MOTOR_STEP_GPIO_PORT	GPIOA
 #define MOTOR_ENABLE_GPIO_PORT	GPIOB
// #define GPIOB 56

#define MOTORX_STEP_PIN         GPIO_PIN_8  /* Pin 8 selected    */
#define MOTORY_STEP_PIN         GPIO_PIN_9 	/* Pin 9 selected    */
#define MOTORZ_STEP_PIN       	GPIO_PIN_10  /* Pin 10 selected   */
#define MOTOR_ENABLE_PIN       	GPIO_PIN_15  /* Pin 10 selected   */

#define GPIO_PIN_15  15
int E;

extern TIM_HandleTypeDef htim2;

volatile int timerstart;

extern MotorInfo motorX;

extern MotorInfo motorY;

extern MotorInfo motorZ;

extern MotorInfo *MotorInfoTable[];

extern GCodeMapping GCode00[];
CEXCEPTION_T ex;
extern VariableMap g01VarTableMapping[];
extern VariableMap g00VarTableMapping[];
extern StoreCMD cmd1;
extern Variable xVar;
extern Variable yVar;
extern Variable x1Var;
extern Variable y1Var;
extern int Steps[2];
extern char *complete;
extern char buffer1[100];
//  Variable zVar = {0,0,0,0};
extern Variable fVar;
void settimer2Periodvalue(int value);
void DecodeandStepMotor(void);

#endif /* USERCONFIG_H_ */
