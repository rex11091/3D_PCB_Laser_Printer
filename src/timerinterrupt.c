#include "timerinterrupt.h"
#include "stdio.h"


int interruptSubRoutine(MotorPin *MotorPin){
    if(MotorPin->Gpio == 'A'&& MotorPin->pin ==8){
    togglemotorpin1();
    }
    if(MotorPin->Gpio == 'A'&& MotorPin->pin ==9){
    togglemotorpin2();
    }
    if(MotorPin->Gpio == 'A'&& MotorPin->pin ==10){
    togglemotorpin3();
    }
}
