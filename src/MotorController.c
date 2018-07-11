#include "MotorController.h"
#include "stdio.h"


void setupMovement(int start[],int end[],MotorInfo *MotorInfo1,MotorInfo *MotorInfo2){
int delta,deltaRef,diff;

  delta = end[0] - start[0];
  deltaRef = end[1] - start[1];

  // starting1 = start[0];
  // starting2 = start[1];
  diff = 2*deltaRef - delta;

  MotorInfo1->delta = delta;
  MotorInfo1->deltaRef = deltaRef;
  MotorInfo1->initial_point = start[0];
  MotorInfo1->diff = diff;
  MotorInfo1->coordinate[0] = start[0];
  MotorInfo1->coordinate[1] = end[0];
  MotorInfo2->delta = deltaRef;
  MotorInfo2->deltaRef = delta;
  MotorInfo2->initial_point = start[1];
  MotorInfo2->diff = diff;
  MotorInfo2->coordinate[0] = start[1];
  MotorInfo2->coordinate[1] = end[1];
}
//this function is for exchange the coordinates of motors if the delta is greather than deltaRef
void CheckEitherChangeOrNoChange(MotorInfo *MotorInfo1, MotorInfo *MotorInfo2){
int temp1,temp2;
  if(MotorInfo1->delta > MotorInfo1->deltaRef){
    MotorInfo1->change = 0;
  }
  else{
    /*
     example
     (x,y) to (y,x)
    */
    temp1 = MotorInfo1->coordinate[0];
    MotorInfo1->coordinate[0]=MotorInfo2->coordinate[0];
    MotorInfo2->coordinate[0]=temp1;
    temp2 = MotorInfo1->coordinate[1];
    MotorInfo1->coordinate[1]=MotorInfo2->coordinate[1];
    MotorInfo2->coordinate[1]=temp2;

    MotorInfo1->delta = MotorInfo1->coordinate[1] - MotorInfo1->coordinate[0];
    MotorInfo1->deltaRef  = MotorInfo2->coordinate[1] - MotorInfo2->coordinate[0];
    MotorInfo1->diff = 2*(MotorInfo1->deltaRef) - MotorInfo1->delta;
    MotorInfo1->initial_point = MotorInfo1->coordinate[0];
    MotorInfo2->initial_point = MotorInfo2->coordinate[0];
    MotorInfo1->change = 1;

  }
}
void MotorToNextStep(MotorInfo *MotorInfo1, MotorInfo *MotorInfo2){

  int currentStep_motor1=MotorInfo1->coordinate[0];
	int currentStep_motor2=MotorInfo2->coordinate[0];
	int previousStep_motor1 = 0;
	int previousStep_motor2 = 0;

  if(currentStep_motor1 < (MotorInfo1->coordinate[1])){
        	previousStep_motor1 = currentStep_motor1;
        	currentStep_motor1 = MotorInfo1->initial_point;

        	previousStep_motor2 = currentStep_motor2;
        	currentStep_motor2 = MotorInfo2->initial_point;

        	if(currentStep_motor1 >previousStep_motor1){
            //call timer interrupt
            timerinterrupt(&(MotorInfo1->motorPin));

            MotorInfo1->coordinate[0]+=1;
        	}
        	if(currentStep_motor2 >previousStep_motor2){
            //call timer interrupt
            timerinterrupt(&(MotorInfo2->motorPin));

            MotorInfo2->coordinate[0]+=1;
        	}
      }
    if (MotorInfo1->diff >= 0){
            MotorInfo2->initial_point = MotorInfo2->initial_point + 1;
            MotorInfo1->diff = MotorInfo1->diff - 2* (MotorInfo1->delta);
            }
        MotorInfo1->diff = MotorInfo1->diff + 2* (MotorInfo1->deltaRef);
}

void MotorMovement(MotorInfo *MotorInfo1, MotorInfo *MotorInfo2){

    for(MotorInfo1->initial_point; MotorInfo1->initial_point< (MotorInfo1->coordinate[1]+1); (MotorInfo1->initial_point)++){
      MotorToNextStep(MotorInfo1,MotorInfo2);
    }
}



//
//
// void MotorMovement(LineInfo *lineinfo){
//
//     for(lineinfo->X; lineinfo->X < (lineinfo->EndCoord[0])+1; (lineinfo->X)++){
//
//       MotorToNextStep(lineinfo);
//       if(lineinfo->stepX == 1){
//         printf("start timer interrupt : motorX.pin toggle\n");
//         lineinfo->stepX =0;
//       }
//       if(lineinfo->stepY ==1){
//         printf("start timer interrupt : motorY.pin toggle\n");
//         lineinfo->stepY =0;
//       }
//       if(lineinfo->stepZ ==1){
//         printf("start timer interrupt : motorZ.pin toggle\n");
//         lineinfo->stepZ =0;
//       }
//     }
// }
