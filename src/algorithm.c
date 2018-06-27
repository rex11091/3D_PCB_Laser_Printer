#include "algorithm.h"
#include "motorStep.h"
#include "stdio.h"
#include "malloc.h"
#include "string.h"


char Result[100];

char *moveHead(int X[], int Y[]){
	int i=0;
	int x,y,dx,dy,m,d;
	dx = X[1]- X[0];
	dy = Y[1]- Y[0];

    x = X[0];
    y = Y[0];
    d = 2*dy - dx;

	int current_Xstep=X[0];
	int current_Ystep=Y[0];
	int previous_Xstep = 0;
	int previous_Ystep = 0;

    for(x =X[0]; x<X[1]+1; x++){
    	previous_Xstep = current_Xstep;
    	current_Xstep = x;
    	previous_Ystep = current_Ystep;
    	current_Ystep = y;

    	if(current_Xstep > previous_Xstep){
				Result[i]='x';
				i++;

				  //printf("step X\n");
				// motorstepX();
    	}
    	if(current_Ystep > previous_Ystep){
    			 //printf("step y\n");
					Result[i]='y';
					i++;

    	}

        if (d >= 0){
            y = y + 1;
            d = d - 2*dx;
        	}
        d = d + 2* dy;
    }
		return Result;
}


//fake

void giveMeSteps(char values[], int size) {
  int i;
  for(i = 0; i < size; i++)
    values[i] = getNumber();
}

// void moveHead1(int X[], int Y[]){
// 	int x,y,dx,dy,m,d;
//
// 	dx = X[1]- X[0];
// 	dy = Y[1]- Y[0];
// 	m = dy/dx;
//
//     x = X[0];
//     y = Y[0];
//     d = 2*dy - dx;
//
// 	int current_Xstep=X[0];
// 	int current_Ystep=Y[0];
// 	int previous_Xstep = 0;
// 	int previous_Ystep = 0;
//
//     for(x =X[0]; x<X[1]+1; x++){
//     	previous_Xstep = current_Xstep;
//     	current_Xstep = x;
//     	previous_Ystep = current_Ystep;
//     	current_Ystep = y;
//
//     	if(current_Xstep > previous_Xstep){
//     			printf("step X\n");
//     	}
//     	if(current_Ystep > previous_Ystep){
//     			printf("step y\n");
//
//     	}
//
//         if (d >= 0){
//             y = y + 1;
//             d = d - 2*dx;
//         	}
//         d = d + 2* dy;
//     }
// }
