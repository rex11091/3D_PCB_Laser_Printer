#ifndef _USBD_CDC_IF_H
#define _USBD_CDC_IF_H
int status;
#define DATA_IS_READY 15
#define START_TIMER 16
#define COUNTING_TIMER 17
#define START_NEW_DATA 18
#define WAIT_FOR_NXT_CMD 19
char buffer[30];
char buffer1[100];
void CDC_Transmit_FS(buffer1, strlen(buffer1));
#endif // _USBD_CDC_IF_H
