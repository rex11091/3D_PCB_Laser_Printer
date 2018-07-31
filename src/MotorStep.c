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
         //motorStep(MotorInfoTable);
         makeStepbasedOnBrenseham(MotorInfoTable);
        // timer period = original value (200ms)
        //  settimer2Periodvalue(MOTOR_STEP_INT_PERIOD);
        state = DO_STEPPING;
        break;
    case DO_STEPPING:
    	  SetAllmotorStep(MotorInfoTable);
        //motorStep(MotorInfoTable);
        //timer period = 2(50us)
        state =DO_DELAY;
        //  settimer2Periodvalue(MOTOR_STEP_INT_PERIOD);
        //    HAL_TIM_Base_Stop_IT(&htim2);
        break;
    default:
    	break;
      }
}
