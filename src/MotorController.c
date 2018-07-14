#include "MotorController.h"
#include "stdio.h"
#include "stddef.h"
#include "malloc.h"


void setupMotorInfo(MotorInfo Motorinfo[],int start[],int end[],int numbOfMotors){
  int i,j,k,l,m;
  int largest;
  int deltaRef;

   for(i=0;i<numbOfMotors;i++){
     Motorinfo[i].delta = end[i]-start[i];
   }
   largest = Motorinfo[0].delta;
   Motorinfo[0].isReferencing = 1;
   for(j=1; j<numbOfMotors;j++){
     if(largest < Motorinfo[j].delta)
     {
       largest = Motorinfo[j].delta;
       Motorinfo[j].isReferencing = 1;
       Motorinfo[j-1].isReferencing =0;
     }
     else
      Motorinfo[j].isReferencing = 0;
   }
   for(k=0;k<numbOfMotors;k++){
     if(Motorinfo[k].isReferencing == 1)
      deltaRef = Motorinfo[k].delta;
   }
   for(l=0;l<numbOfMotors;l++){
     Motorinfo[l].deltaRef = deltaRef;
   }
   for(m=0;m<numbOfMotors;m++){
     if(Motorinfo[m].isReferencing !=1)
     Motorinfo[m].error =2 * Motorinfo[m].deltaRef - Motorinfo[m].delta;
   }
}

//
// void MotorMovement(MotorInfo *MotorInfo1, MotorInfo *MotorInfo2){
//
//     for(MotorInfo1->initial_point; MotorInfo1->initial_point< (MotorInfo1->coordinate[1]+1); (MotorInfo1->initial_point)++){
//       MotorToNextStep(MotorInfo1,MotorInfo2);
//     }
// }
