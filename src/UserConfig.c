#include"UserConfig.h"

void settimer2Periodvalue(int value){
	htim2.Instance->ARR = value;
}
