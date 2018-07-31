#include "MotorController.h"
#include "MotorStep.h"
#include "stdio.h"
#include "stddef.h"
#include "malloc.h"
#include "main.h"
#include "UserConfig.h"
#include "MotorStep.h"
//#include "stm32f1xx_hal.h"




void setupMotorInfo(MotorInfo *MotorInfoTable[],int start[],int end[]){
  int i=0,k=0,l=0,m=0;
  int j=1;
  int largest=0,deltaRef=0;
    while(MotorInfoTable[i]!=NULL){
      MotorInfoTable[i]->start = start[i];
      MotorInfoTable[i]->end = end[i];
      MotorInfoTable[i]->delta = end[i]-start[i];
    i++;
   }
   largest = MotorInfoTable[0]->delta;
   MotorInfoTable[0]->isReferencing = TRUE;
   while(MotorInfoTable[j]!=NULL){
     if(largest <MotorInfoTable[j]->delta){
       largest = MotorInfoTable[j]->delta;
       MotorInfoTable[j]->isReferencing = TRUE;
       MotorInfoTable[j-1]->isReferencing =FALSE;
     }
     else{
      MotorInfoTable[j]->isReferencing = FALSE;
     }
     j++;
   }
   while(MotorInfoTable[k]!=NULL){
     if(MotorInfoTable[k]->isReferencing ==TRUE){
       deltaRef = MotorInfoTable[k]->delta;
     }
   k++;
  }
  while(MotorInfoTable[l]!=NULL){
     MotorInfoTable[l]->deltaRef = deltaRef;
  l++;
 }
 while(MotorInfoTable[m]!=NULL){
   if(MotorInfoTable[m]->isReferencing !=TRUE){
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
    if(MotorInfoTable[i]->isReferencing == TRUE){
      if(MotorInfoTable[i]->start < MotorInfoTable[i]->end ){
        MotorInfoTable[i]->Dostepping =1;
      }
      else{
        MotorInfoTable[i]->Dostepping =0;
        stop =1;

      }
      MotorInfoTable[i]->start+=1;
    }
    i++;
    }
    /*here is checking if the motor is not as a Referencing,thn it run
    the bresenham algorithm to checking stepping or not and recalculate the error
    */
  while(MotorInfoTable[j]!=NULL){
      if(MotorInfoTable[j]->isReferencing !=TRUE){
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
}

//set Motorinfo->Dostepping to 1
void clearALLMotorinfoDostepping(MotorInfo *MotorInfoTable[]){
  int i=0;
  while(MotorInfoTable[i]!=NULL){
    MotorInfoTable[i]->Dostepping = 0;
  i++;
 }
}
