#include "MotorController.h"
#include "stdio.h"
#include "stddef.h"
#include "malloc.h"

void setupMotorInfo(MotorInfo Motorinfo[],int start[],int end[],int numbOfMotors){
  int i,j,k,l,m;
  int largest;
  int deltaRef;
  //storing the delta and start point, end point of the motor
   for(i=0;i<numbOfMotors;i++){
     Motorinfo[i].delta = end[i]-start[i];
     Motorinfo[i].start=start[i];
     Motorinfo[i].end=end[i];
   }
   //checking which delta of motor is largest = the motor is being referecing
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
   // storing largest delta of motor into the deltaRef to all the motor
   for(k=0;k<numbOfMotors;k++){
     if(Motorinfo[k].isReferencing == 1)
      deltaRef = Motorinfo[k].delta;
    //  Motorinfo[k].Dostepping=1;
   }
   for(l=0;l<numbOfMotors;l++){
     Motorinfo[l].deltaRef = deltaRef;
   }
   //calculate the error of motor which motors is no being reference
   for(m=0;m<numbOfMotors;m++){
     if(Motorinfo[m].isReferencing !=1)
     Motorinfo[m].error =2 * Motorinfo[m].delta - Motorinfo[m].deltaRef;
   }
}
void MotorMovement(MotorInfo Motorinfo[],int numberOfMotors){
  int i,j=0;
  int stop=0; //stop is like a flag that determine the Motor which being Referencing is already until the end of points
  // here is checking which motor is being Referencing and Keep stepping it when havent reach the final point
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
    }
    /*here is checking if the motor is not as a Referencing,thn it run
    the bresenham algorithm to checking stepping or not and recalculate the error
    */
  while(j<numberOfMotors){
      if(Motorinfo[j].isReferencing !=1){
        if(stop !=1){
          if(Motorinfo[j].error >=0){
            Motorinfo[j].Dostepping = 1;
            Motorinfo[j].error = Motorinfo[j].error - 2*Motorinfo[j].deltaRef;
          }
          else{
              Motorinfo[j].Dostepping =0;
            }
        Motorinfo[j].error = Motorinfo[j].error + 2*Motorinfo[j].delta;
        }
        else
        {
            Motorinfo[j].Dostepping =0;
        }
      }
      j++;
    }
}
// here is a function to check the motors's stepping either stepping or Not
//if stepping thn toggle the pin of the motors
void TimerInterruptCheckingStepping(MotorInfo Motorinfo[],int numberOfMotors){
  int i;
  for(i=0;i<numberOfMotors;i++){
        if(Motorinfo[i].Dostepping ==1){
          //toggle pin
          printf("step %c\n",Motorinfo[i].name);
          Motorinfo[i].Dostepping =0;
        }
        else{
          Motorinfo[i].Dostepping =Motorinfo[i].Dostepping;
        }
      }
      printf("\n");
}
