#include "CommandCode.h"
#include "CException.h"
#include "Exception.h"
#include "error.h"
#include "XYZSteps.h"
#include "Integration.h"
int isInMM = TRUE;
int isAbsolute = TRUE;

StoreCMD decodeGcode(char *line,GCodeMapping *GCode)
{
  StoreCMD cmd;

    line = getGcodeCommand(line,GCode,&cmd);
    while(cmd.code != (GCode)->code)
    {
    *GCode++;
    }
    getVariables(line,GCode);
    while(cmd.code != (GCode)->code)
    {
    *GCode++;
    }
    MOTORSTATUS = MOTOR_BUSY;
    (GCode)->doOperation(GCode->code,GCode->varMap);
    return cmd;
}

char *getGcodeCommand(char *line,GCodeMapping *GCode,StoreCMD *cmd)
{
  int i=0;
  char storecode[20] = {0};
  //Check name of the command
  //Whether 'G' or 'M'
  while(isEmpty(*line))
  {
    line  += 1;
  }
  while(*(GCode)->name == NULL)
  {
    *GCode++;
  }
    if(toupper(*line) == *(GCode)->name)
    {
      cmd->type = toupper(*line);
      line += 1;
    }
    else
    {
      throwException(ERROR_COMMAND,"Error! No such command exist\n \
      Expect to be 'G' but was ",*line);
    }
    //Check code
  while(isEmpty(*line))
  {
    line += 1;
  }
  if(isAlpha(*line))
  {
    throwException(ERROR_CODE,"Error! Spotted more than 1 alphabet in a command\n \
    Expect to be an integer but was ",*line);
  }
  while(isNumbers(*line))
  {
      storecode[i] = *line;
      line += 1;
      i++;
  }
  cmd->code = atoi(storecode);
  while(GCode->name != NULL)
  {
    if(cmd->code == GCode->code)
    {
      return line;
    }
    else
    {
      *GCode++;
    }
  }
  Throw(createException("Error! Code either is not in the same group sharing the \
  same variable or code does not exist\n",ERROR_CODE));
}


void getVariables(char *line,GCodeMapping *GCode)
{

  int j,i=0;
  const int len = strlen(line);
  if(isNumbers(*line))
  {
    throwException(ERROR_VARIABLE,"Error! Invalid variable,expect variable to be \n\
    a character but was ",*line);
  }
  while(isEmpty(*line))
  {
    if(len > 0  && line[len-1] == ' ')
    {
      return ;
    }
    line += 1;
  }
  if(len == 0)
  {
    return;
  }
  for(j=0;j<strlen(line);j++)
  {
  if(isAlpha(*line))
  {
    while(((GCode)->varMap->name)!=NULL)
    {
      if(isEmpty(*line))
      {
        line += 1;
      }
      if(toupper(*line) == (GCode)->varMap->name)
      {
        if((GCode)->varMap->var->isValid == 0)
        {
          (GCode)->varMap->var->name = toupper(*line);
          line += 1;
          line = getValue(line,GCode);
          (GCode)->varMap->var->isValid = 1;
        }
        else
        {
          throwException(ERROR_DUPLICATE_VARIABLE,"Error! Variable has been declared once",*line);
        }
      }
      else
      {
        *(GCode)->varMap++;
        i++;
      }
    }
  }
  else{
    throwException(NOT_ALPHA,"Error! Expect it to be a character but was ",*line);
  }
  while(i!=0)
  {
    *(GCode)->varMap--;
    i--;
  }
}
  while(((GCode)->varMap->name)!=NULL)
  {
    (GCode)->varMap->var->isValid = 0;
    *(GCode)->varMap++;
    i++;
  }
  while(i!=0)
  {
    *(GCode)->varMap--;
    i--;
  }
  if((*line == 10)||(*line == 13)||(*line == 64))
  {

  }
  else if(*line != NULL)
  {
    throwException(VARIABLE_DOES_NOT_EXIST,"Error! Variable does not exist in this command ",*line);
  }
}

char *getValue(char *line,GCodeMapping *GCode)
{
  int i=0;
  int validate_decimal = FALSE;
  char storenum[20] = {0};
  double value;
  if(isAlpha(*line))
  {
    throwException(ERROR_VALUE,"Error! Expect integer since variable has been declared but was ",*line);
  }
  while(isEmpty(*line) || isDash(*line))
  {
    line += 1;
  }
  while(isNumbers(*line)||isDecimal(*line))
  {
      if(isDecimal(*line))
      {
        if(validate_decimal == FALSE)
        {
          storenum[i] = *line;
          line += 1;
          i++;
          validate_decimal = TRUE;
        }
        else{
          throwException(ERROR_VALUE,"Error! Value contains more than 1 ",*line);
        }
      }
    storenum[i] = *line;
    i++;
    line += 1;
  }

  value = atof(storenum);
  (GCode)->varMap->var->value = value;
  return line;

}
void handleG20or21(int code,VariableMap *table)
{
  if(code == 20 || code == 70)
  {
    isInMM = TRUE;
  }
  else
  {
    isInMM = FALSE;
  }
}

void handleG90orG91(int code,Variable *table)
{
  if(code == 90)
  {
    isAbsolute = TRUE;
  }
  else
  {
    isAbsolute = TRUE;
  }
}
void handleG00(int code,VariableMap *g00VarTableMapping)
{
  int steps;
  if(isInMM == TRUE)
  {
        while(g00VarTableMapping->var!=NULL)
        {
            g00VarTableMapping->var->steps = MM_TO_STEPS(g00VarTableMapping->var->value);
          //  steps = g00VarTableMapping->var->steps;
          // if(steps != 0)
          // {
          //   SetUpMotorInfo(NULL,steps);
          // }
            *(g00VarTableMapping)++;
        }
  }
  else
  {
    while(g00VarTableMapping->var!=NULL)
    {
        g00VarTableMapping->var->steps = INCH_TO_STEPS(g00VarTableMapping->var->value);
      // steps = g00VarTableMapping->var->steps;
      // if(steps != 0)
      // {
      //   SetUpMotorInfo(NULL,steps);
      // }
        *(g00VarTableMapping)++;
    }
  }
  // while(i != 0)
  // {
  //   *(g00VarTableMapping)--;
  //   i--;
  // }
}

void handleG01(int code,VariableMap *g01VarTableMapping)
{
  int feedrate = 0;
  int steps;
  feedrate = Findfeedrate('F',g01VarTableMapping);

  if(isInMM == TRUE)
  {
        while(g01VarTableMapping->var!=NULL)
        {
          //Feed Rate is per min
          //E.g. : F20 in mm => 20mm/min
          //E.g. : F30 in inch => 30inch/min
          // steps/min  = steps/mm * mm/min
          if(g01VarTableMapping->var->name == 'F')
          {
            *(g01VarTableMapping)++;
          }
          else
          {
            g01VarTableMapping->var->steps = MM_TO_STEPS(g01VarTableMapping->var->value) * feedrate;
          // steps = g01VarTableMapping->var->steps;
          // if(steps != 0)
          // {
          //   SetUpMotorInfo(NULL,steps);
          // }
            *(g01VarTableMapping)++;
          }
        }
  }
  else
  {
    while(g01VarTableMapping->var!=NULL)
    {
        if(g01VarTableMapping->var->name == 'F')
        {
          *(g01VarTableMapping)++;
        }
        else
        {
          g01VarTableMapping->var->steps = INCH_TO_STEPS(g01VarTableMapping->var->value) * feedrate;
        // steps = g01VarTableMapping->var->steps;
        // if(steps != 0)
        // {
        //   SetUpMotorInfo(NULL,steps);
        // }
          *(g01VarTableMapping)++;
        }

    }
  }
  // while(i != 0)
  // {
  //   *(g01VarTableMapping)--;
  //   i--;
  // }

}

int Findfeedrate(char Fvar,VariableMap *var)
{
  int feedrateVal;
  while(var->var != NULL)
  {
    if(Fvar == var->var->name)
    {
      if(var->var->value==0)
      {
        feedrateVal = 1;
        return feedrateVal;
      }
      else
      {
        feedrateVal = var->var->value;
        return feedrateVal;
      }
    }
    else
    {
      *var++;
    }
  }
  feedrateVal = 1;
  return feedrateVal;
}
