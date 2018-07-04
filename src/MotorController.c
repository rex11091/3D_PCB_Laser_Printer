#include "MotorController.h"
#include "stdio.h"

// void setupMovement(int start[],int end[],LineInfo *lineinfo){
// int x,y,dx,dy,d,change;
// double m;
//
//   dx = end[0] - start[0];
//   dy = end[1] - start[1];
//   x = start[0];
//   y = start[1];
//   d = 2*dy - dx;
//   m = dy/dx;
//
//
//   lineinfo->dx = dx;
//   lineinfo->dy = dy;
//   lineinfo->X = x;
//   lineinfo->Y = y;
//   lineinfo->d = d;
//   lineinfo->m = m;
//   lineinfo->StartCoord[0]= start[0];
//   lineinfo->StartCoord[1]= start[1];
//   lineinfo->EndCoord[0]= end[0];
//   lineinfo->EndCoord[1]= end[1];
//   lineinfo->stepX= 0;
//   lineinfo->stepY= 0;
//   lineinfo->stepZ= 0;
//   lineinfo->change=0;
// }

void setupMovement(int start[],int end[],LineInfo *lineinfo){
int x,y,dx,dy,d,change;
int tempForExchange1,tempForExchange2;
double m;

  dx = end[0] - start[0];
  dy = end[1] - start[1];
  m = dy/dx;

  if(m > 1){  // here is determine whether the angle is more than 45 or not
    // exchange X
    tempForExchange1 =start[0];
    start[0] = start[1];
    start[1] =tempForExchange1;
    //exchange Y
    tempForExchange2 = end[0];
    end[0] = end[1];
    end[1]  = tempForExchange2;
    //redo the calculation of dx dy
    dx = end[0] - start[0];
    dy = end[1] - start[1];
    change = 1;
    }
  else{
    change = 0;
    }

  x = start[0];
  y = start[1];
  d = 2*dy - dx;


  lineinfo->dx = dx;
  lineinfo->dy = dy;
  lineinfo->X = x;
  lineinfo->Y = y;
  lineinfo->d = d;
  lineinfo->m = m;
  lineinfo->change = change;
  lineinfo->StartCoord[0]= start[0];
  lineinfo->StartCoord[1]= start[1];
  lineinfo->EndCoord[0]= end[0];
  lineinfo->EndCoord[1]= end[1];
  lineinfo->stepX= 0;
  lineinfo->stepY= 0;
  lineinfo->stepZ= 0;
}

void MotorToNextStep(LineInfo *lineinfo){

  int current_Xstep=lineinfo->StartCoord[0];
	int current_Ystep=lineinfo->StartCoord[1];
	int previous_Xstep = 0;
	int previous_Ystep = 0;
  int temp;

  if(current_Xstep < (lineinfo->EndCoord[0]+1) && current_Ystep < (lineinfo->EndCoord[1]+1)){
        	previous_Xstep = current_Xstep;
        	current_Xstep = lineinfo->X;
        	previous_Ystep = current_Ystep;
        	current_Ystep = lineinfo->Y;

        	if(current_Xstep >previous_Xstep){
    			lineinfo->stepX =1;
          lineinfo->StartCoord[0]+=1;
        	}
        	if(current_Ystep > previous_Ystep){
    	    lineinfo->stepY =1;
          lineinfo->StartCoord[1]+=1;
        	}

          if(lineinfo->change == 1){
            temp= lineinfo->stepX;
            lineinfo->stepX = lineinfo->stepY;
            lineinfo->stepY = temp;
            // printf("change");
          }
      }
    if (lineinfo->d >= 0){
            lineinfo->Y = lineinfo->Y + 1;
            lineinfo->d = lineinfo->d - 2* (lineinfo->dx);
            }
        lineinfo->d = lineinfo->d + 2* (lineinfo->dy);

}


void DrawLine(LineInfo *lineinfo){

// only for angle of 45 degree
    for(lineinfo->X; lineinfo->X < (lineinfo->EndCoord[0])+1; (lineinfo->X)++){

      MotorToNextStep(lineinfo);
      if(lineinfo->stepX == 1){
        printf("start timer interrupt : motorX.pin toggle\n");
        lineinfo->stepX =0;
      }
      if(lineinfo->stepY ==1)
        printf("start timer interrupt : motorY.pin toggle\n");
        lineinfo->stepY =0;
      if(lineinfo->stepZ ==1)
        printf("start timer interrupt : motorZ.pin toggle\n");
        lineinfo->stepZ =0;
    }
}
