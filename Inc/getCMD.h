#ifndef _GETCMD_H
#define _GETCMD_H
#include "stdint.h"

#define TRUE 1
#define FALSE 0
//extern int CMD_RETRIEVED;
int getcommand(char buffer[],uint8_t *Buf,int len);

#endif // _GETCMD_H
