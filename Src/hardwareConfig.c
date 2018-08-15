/*
 * hardwareConfig.c
 *
 *  Created on: Aug 15, 2018
 *      Author: rex
 */
#include "hardwareConfig.h"
#include "Error.h"
#include "CommandCode.h"

void DecodeandStepMotor(void){
 if(status == DATA_IS_READY){
			 Try{
			      cmd1 = decodeGcode(buffer,GCode00);
					memset(buffer,0,sizeof(buffer));
					if(cmd1.code == 1)
					{
						E = 1;
					}
					if(cmd1.code == 0)
					{
						E = 0;
					}

//					if(cmd1.code == 21 ||cmd1.code==90 ||cmd1.code==91 || cmd1.code==20)
//					{
//						throwException(CONFIG_NXT_GCODE,"Configuration Set",cmd1.code);
//					}
					if(E==0){

						memset(Steps,0,sizeof(Steps));
					   for(int i=0;i<3;i++)
					   {
							Steps[i] = g00VarTableMapping[i].var->steps;
					   }
					   	   ClearVariablesValue(g00VarTableMapping);
						   setupMotorInfo(MotorInfoTable,Steps);

						}
					else if(E==1){


						memset(Steps,0,sizeof(Steps));
					 	for(int i=0;i<3;i++)
					 	{
					 	    Steps[i] = g01VarTableMapping[i].var->steps;
					 	}
					 	   	ClearVariablesValue(g01VarTableMapping);
					 	   	setupMotorInfo(MotorInfoTable,Steps);
					}
			 	configureMotorandStartTimer();
			 	while(MOTORSTATUS != MOTOR_OK)
			 	{
			 	}
			 if(MOTORSTATUS == MOTOR_OK)
			 {
				 CDC_Transmit_FS(complete,strlen(complete));
				 MOTORSTATUS = MOTOR_BUSY;
				 status = WAIT_FOR_NXT_CMD;
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
			 }
		 }
}

void configureMotorandStartTimer(void)
{
	HAL_GPIO_WritePin(MOTOR_ENABLE_GPIO_PORT,MOTOR_ENABLE_PIN, LOW);
	HAL_TIM_Base_Start_IT(&htim2);
}

