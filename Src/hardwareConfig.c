/*
 * hardwareConfig.c
 *
 *  Created on: Aug 15, 2018
 *      Author: rex
 */
#include "hardwareConfig.h"

void DecodeandStepMotor(void){
 if(status == DATA_IS_READY){
			 Try{
			      cmd1 = decodeGcode(buffer,GCode00);
					memset(buffer,0,sizeof(buffer));
//			 	  cmd1 = decodeGcode(line,GCode00);
					if(cmd1.code == 1)
					{
						E = 1;
					}
					else if(cmd1.code == 0)
					{
						E = 0;
					}
					else{
						status = WAIT_FOR_NXT_CMD;
						return;
					}
					if(E==0){
					   for(int i=0;i<3;i++)
					   {
							Steps[i] = g00VarTableMapping[i].var->steps;
					   }
						   setupMotorInfo(MotorInfoTable,Steps);

						}
					else{
					 	   for(int i=0;i<3;i++)
					 	   {
					 	        Steps[i] = g01VarTableMapping[i].var->steps;
					 	   }
					 	setupMotorInfo(MotorInfoTable,Steps);
					}
			 	configureMotorandStartTimer();
//			 	HAL_TIM_Base_Start_IT(&htim2);
			 	while(MOTORSTATUS != MOTOR_OK)
			 	{
			 	}
			 if(MOTORSTATUS == MOTOR_OK)
			 {
				 CDC_Transmit_FS(complete,strlen(complete));
				 MOTORSTATUS = MOTOR_DO_NEXT;
				 status = WAIT_FOR_NXT_CMD;
//				 buffer[0] = 0;
				 //memset(input,0,sizeof(input));
			 }
			}
			 Catch(ex)
			 {
				 dumpException(ex);
				 if(ex!=NULL){
				 snprintf(buffer1, 100, "%s %c (err=%d)\n",ex->msg,ex->data,ex->errorCode);
				 CDC_Transmit_FS(buffer1, strlen(buffer1));
				 }
				 freeException(ex);
				 status = WAIT_FOR_NXT_CMD;
				 volatile int i;
				 //CDC_Transmit_FS(ex->msg, strlen(ex->msg));
			 }
		 }
}

void configureMotorandStartTimer(void)
{
	HAL_GPIO_WritePin(MOTOR_ENABLE_GPIO_PORT,MOTOR_ENABLE_PIN, LOW);
	HAL_TIM_Base_Start_IT(&htim2);
}

