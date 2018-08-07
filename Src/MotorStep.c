#include "MotorStep.h"

static int state = DO_STEPPING;

//motorinfo gpio and pin to hardware gpio
void StepMotor(MotorInfo *info){
	if(info->Dostepping==1){
		HAL_GPIO_WritePin(info->GPIO,info->MotorPin,HIGH);
  }
	else{
		HAL_GPIO_WritePin(info->GPIO,info->MotorPin,LOW);
  }
}

void SetAllmotorStep(MotorInfo *MotorInfoTable[]){
  int i=0;
    while(MotorInfoTable[i] !=NULL){
    	StepMotor(MotorInfoTable[i]);
      i++;
    }
}

// here is a function to check the motors's stepping either stepping or Not
//if stepping thn toggle the pin of the motors
void DoMotorStepping(MotorInfo *MotorInfoTable[]){
  switch(state){
    case DO_DELAY:
         clearALLMotorinfoDostepping(MotorInfoTable);
         SetAllmotorStep(MotorInfoTable);
         makeStepbasedOnBrenseham(MotorInfoTable);
        /* timer period = original value (1.25ms)
				rmb comment it when compile in ide
				*/
          settimer2Periodvalue(100);
        state = DO_STEPPING;
        break;
    case DO_STEPPING:
    	  SetAllmotorStep(MotorInfoTable);
				 state =DO_DELAY;
				/* timer period = 2(50us)
				rmb comment it when compile in ide
				*/
          settimer2Periodvalue(2);
        break;
    default:
    	break;
      }
}

void checkCommandCompletion(MotorInfo *MotorInfoTable[],int state)
{
  int i = DOSTEPPING;
  while(i == DOSTEPPING)
  {
  	switch(state)
  	{
  		case HANDLE_CURRENT_CMD:
  				DoMotorStepping(MotorInfoTable);
  				state = WAIT_FOR_CURRENT_CMD_TO_COMPLETE;
  				break;
  		case WAIT_FOR_CURRENT_CMD_TO_COMPLETE:
  				if(MOTORSTATUS == MOTOR_OK)
  				{
  					state = HANDLE_NEXT_CMD;
            i = COMPLETE;
  				}
  				else
  				{
  					state = HANDLE_CURRENT_CMD;

  				}
          break;
      case HANDLE_NEXT_CMD:
          return;
  				break;
  		default:
  				break;
  	}
  }
}
