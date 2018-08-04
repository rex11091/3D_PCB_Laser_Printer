#include "MotorController.h"
#include "MotorStep.h"
#include "stdio.h"
#include "stddef.h"
#include "malloc.h"
#include "main.h"
#include "UserConfig.h"
//#include "stm32f1xx_hal.h"


int start_step =0;

//delta nid change to step
void setupMotorInfo(MotorInfo *MotorInfoTable[],int delta[]){
  int i=0,k=0,l=0,m=0;
  int j=1;
  int largest=0,deltaRef=0;
    while(MotorInfoTable[i]!=NULL){
      MotorInfoTable[i]->delta =delta[i];
    i++;
   }
   largest = MotorInfoTable[0]->delta;
   MotorInfoTable[0]->isReferencing = ISTRUE;
   while(MotorInfoTable[j]!=NULL){
     if(largest <MotorInfoTable[j]->delta){
       largest = MotorInfoTable[j]->delta;
       MotorInfoTable[j]->isReferencing = ISTRUE;
       MotorInfoTable[j-1]->isReferencing =ISFALSE;
     }
     else{
      MotorInfoTable[j]->isReferencing = ISFALSE;
     }
     j++;
   }
   while(MotorInfoTable[k]!=NULL){
     if(MotorInfoTable[k]->isReferencing ==ISTRUE){
       deltaRef = MotorInfoTable[k]->delta;
     }
   k++;
  }
  while(MotorInfoTable[l]!=NULL){
     MotorInfoTable[l]->deltaRef = deltaRef;
  l++;
 }
 while(MotorInfoTable[m]!=NULL){
   if(MotorInfoTable[m]->isReferencing !=ISTRUE){
   MotorInfoTable[m]->error =2 * MotorInfoTable[m]->delta - MotorInfoTable[m]->deltaRef;
    }
  m++;
  }
}

void makeStepbasedOnBrenseham(MotorInfo *MotorInfoTable[]){
  int i=0,j=0;
  int stop=0; //stop is like a flag that determine the Motor which being Referencing is already until the end of points
  // here is checking which motor is being Referencing and Keep stepping it when havent reach the final point
  while(MotorInfoTable[i]!=NULL){
    if(MotorInfoTable[i]->isReferencing == ISTRUE){
      if(start_step < MotorInfoTable[i]->delta){
        MotorInfoTable[i]->Dostepping =1;
      }
      else{
        MotorInfoTable[i]->Dostepping =0;
        stop =1;

      }
      start_step+=1;
    }
    i++;
    }
    /*here is checking if the motor is not as a Referencing,thn it run
    the bresenham algorithm to checking stepping or not and recalculate the error
    */
    while(MotorInfoTable[j]!=NULL){
        if(MotorInfoTable[j]->isReferencing !=ISTRUE){
          if(stop !=1){
            if(MotorInfoTable[j]->error >=0){
              MotorInfoTable[j]->Dostepping = 1;
              MotorInfoTable[j]->error = MotorInfoTable[j]->error - 2*MotorInfoTable[j]->deltaRef;
            }
            else{
                MotorInfoTable[j]->Dostepping =0;
              }
          MotorInfoTable[j]->error = MotorInfoTable[j]->error + 2*MotorInfoTable[j]->delta;
          }
          else
          {
              MotorInfoTable[j]->Dostepping =0;
          }
        }
        j++;
      }
    if(stop == 1){
      //stop timer interrupt
    //  HAL_TIM_Base_Stop_IT(&htim2);
      //take care of this when compile
        //HAL_TIM_Base_Stop_IT(htim2);
        MOTORSTATUS = MOTOR_OK;
    }
}

//set Motorinfo->Dostepping to 1
void clearALLMotorinfoDostepping(MotorInfo *MotorInfoTable[]){
  int i=0;
  while(MotorInfoTable[i]!=NULL){
    MotorInfoTable[i]->Dostepping = 0;
  i++;
 }
}
