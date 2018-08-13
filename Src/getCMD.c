#include "getCMD.h"
#include "stdio.h"

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
