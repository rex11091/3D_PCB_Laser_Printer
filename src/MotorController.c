#include "MotorController.h"
#include "stdio.h"
#include "stddef.h"
#include "malloc.h"


void setupMotorInfo(MotorInfo Motorinfo[],int start[],int end[],int numbOfMotors){
  int i,j,k,l,m,n;
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
      Motorinfo[i].Dostepping=1;
   }
   for(l=0;l<numbOfMotors;l++){
     Motorinfo[l].deltaRef = deltaRef;
   }
   for(m=0;m<numbOfMotors;m++){
     if(Motorinfo[m].isReferencing !=1)
     Motorinfo[m].error =2 * Motorinfo[m].delta - Motorinfo[m].deltaRef;
   }
   for(n=0;n<numbOfMotors;n++){
     Motorinfo[n].start=start[n];
     Motorinfo[n].end=end[n];
  }
}
void MotorMovement(MotorInfo Motorinfo[],int numberOfMotors){
  int i;
  int stop=0;
  for(i=0;i<numberOfMotors;i++){
    if(Motorinfo[i].isReferencing == 1){
      if(Motorinfo[i].start < Motorinfo[i].end ){
        Motorinfo[i].Dostepping =1;
      }
      else{
        Motorinfo[i].Dostepping =0;
        stop =1;
      }
      Motorinfo[i].start+=1;
    }
    else
    {
      if(stop !=1){
        if(Motorinfo[i].error >=0){
           Motorinfo[i].Dostepping = 1;
           Motorinfo[i].error = Motorinfo[i].error - 2*Motorinfo[i].deltaRef;
         }
         else{
         Motorinfo[i].Dostepping =0;
        }
        Motorinfo[i].error = Motorinfo[i].error + 2*Motorinfo[i].delta;
      }
      else{
        Motorinfo[i].Dostepping =0;
      }
    }
  }
}

void TimerInterruptCheckingStepping(MotorInfo Motorinfo[],int numberOfMotors){
  int i;
  for(i=0;i<numberOfMotors;i++){
        if(Motorinfo[i].Dostepping ==1){
          printf("step %c\n",Motorinfo[i].name);
          Motorinfo[i].Dostepping =0;
        }
        else{
          Motorinfo[i].Dostepping =Motorinfo[i].Dostepping;
        }
      }
}
