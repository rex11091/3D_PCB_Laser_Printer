#include "timerinterrupt.h"
#include "stdio.h"

//int result[100];
int timerinterrupt(MotorPin *MotorPin){
//  int i=0;
    if(MotorPin->Gpio == 'A'&& MotorPin->pin ==8){
    //  result[i]= 1;
    //  i++;
    //printf("sss\n");
    togglemotorpin1();
    }
    if(MotorPin->Gpio == 'A'&& MotorPin->pin ==9){
      // result[i]= 2;
      // i++;
          //printf("yyy\n");
    togglemotorpin2();
    }
}
