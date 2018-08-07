#ifndef USERCONFIG_H_
#define USERCONFIG_H_
#include "MotorController.h"
#include "main.h"

#define HANDLE_CURRENT_CMD 100
#define WAIT_FOR_CURRENT_CMD_TO_COMPLETE 101
#define HANDLE_NEXT_CMD 102
#define DOSTEPPING 103
#define COMPLETE 104

// motor step intervert period
#define MOTOR_STEP_INT_PERIOD 6000
//motor pulse period
#define MOTOR_STEPING_PERIOD  2

#define HIGH	1
#define LOW		0

//motorpin to gpio pin
#define MOTOR_STEP_GPIO_PORT	GPIOA

#define MOTORX_STEP_PIN         GPIO_PIN_8  /* Pin 8 selected    */
#define MOTORY_STEP_PIN         GPIO_PIN_9 	/* Pin 9 selected    */
#define MOTORZ_STEP_PIN       	GPIO_PIN_10  /* Pin 10 selected   */


extern TIM_HandleTypeDef htim2;



extern MotorInfo motorX;

extern MotorInfo motorY;

extern MotorInfo motorZ;

extern MotorInfo *MotorInfoTable[];

void settimer2Periodvalue(int value);

#endif /* USERCONFIG_H_ */
