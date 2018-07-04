#include "MotorController.h"
#include "stdio.h"

void setupMovement(int start[],int end[],LineInfo *lineinfo){
int x,y,dx,dy,d;
double m;

  dx = end[0] - start[0];
  dy = end[1] - start[1];
  x = start[0];
  y = start[1];
  d = 2*dy - dx;
  m = dy/dx;

  lineinfo->dx = dx;
  lineinfo->dy = dy;
  lineinfo->X = x;
  lineinfo->Y = y;
  lineinfo->d = d;
  lineinfo->m = m;
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


  if(current_Xstep < (lineinfo->EndCoord[0]+1) && current_Ystep < (lineinfo->EndCoord[1]+1)){
        	previous_Xstep = current_Xstep;
        	current_Xstep = lineinfo->X;
        	previous_Ystep = current_Ystep;
        	current_Ystep = lineinfo->Y;

        	if(current_Xstep >previous_Xstep){
    			lineinfo->stepX =1;
          lineinfo->StartCoord[0] +=1;
        	}
        	if(current_Ystep > previous_Ystep){
    	    lineinfo->stepY =1;
          lineinfo->StartCoord[1] +=1;
        	}
      }
    if (lineinfo->d >= 0){
            lineinfo->Y = lineinfo->Y + 1;
            lineinfo->d = lineinfo->d - 2* (lineinfo->dx);
            }
        lineinfo->d = lineinfo->d + 2* (lineinfo->dy);

}


void DrawLine(LineInfo *lineinfo){


    for(lineinfo->X; lineinfo->X<lineinfo->EndCoord[0]+1; (lineinfo->X)++){
      MotorToNextStep(lineinfo);
      if(lineinfo->stepX == 1){
        printf("start timer interrupt : motorX.pin toggle\n");
        lineinfo->stepX =0;
      }
      if(lineinfo->stepY ==1)
        printf("start timer interrupt : motorY.pin toggle\n");
        lineinfo->stepY =0;
      if(lineinfo->stepY ==1)
        printf("start timer interrupt : motorX.pin toggle\n");
        lineinfo->stepX =0;
    }
}
