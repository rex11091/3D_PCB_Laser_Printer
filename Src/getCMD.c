#include "getCMD.h"

int getcommand(char buffer[],uint8_t *Buf,int len)
{
  int i;
  static int j=0;
  int CMD_RETRIEVED = FALSE;
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
      return 1;
    }
  }
  return 0;
}
