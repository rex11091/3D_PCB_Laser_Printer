#include "getCMD.h"
#include "stdio.h"

//This function is used to check every string passed in is stored into
//a buffer until an ASCII value of 13 or 10 is detected in the string 
//that are /r and /n respectively

//Once any of those ASCII value is detected
// A message will be printed indicating which ASCII value has detected
//and also an 'OK' message will be printed out indicating
//a full string has been typed and stored into the buffer
int getcommand(char buffer[],uint8_t *Buf,int len)
{
  int i;
  int CMD_RETRIEVED = FALSE;
  static int j=0;
  for(i=0 ; i<len ; i++)
  {
    if(*Buf != 13 && *Buf != 10)
    {
        buffer[j] = *Buf;
        Buf++;
        j++;
    }
    else
    {
      j=0;
      CMD_RETRIEVED = TRUE;
      printf("Detected ASCII value of (%d)\n",*Buf);
      printf("OK\n");
      return 1;
    }
  }
  return 0;
}
