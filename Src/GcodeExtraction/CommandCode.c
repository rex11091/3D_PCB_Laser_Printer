#include "CommandCode.h"
#include "CException.h"
#include "Exception.h"
#include "error.h"
#include "XYZSteps.h"
#include "Integration.h"
int isInMM = TRUE;
int isAbsolute = TRUE;

//This function is to take in a length of string
//that is keyed in by the user as well an array of structure
//that is used to map with the string

//This function is basically just to take in these two parameters
//and to call other functions to execute on mapping the string
// with the array of structure

//The return value of this function is a structure that is used to store
//G-Code command such as the letter 'G' follow by the code
//that leads to different instructions with different code
StoreCMD decodeGcode(char *line,GCodeMapping *GCode)
{
  StoreCMD cmd;

    line = getGcodeCommand(line,GCode,&cmd);
    //After storing the 'G' command as well the code in their respective
    //places in the structure, this while will be used to compare with
    //the code so that the Table of instructions is used correctly
    //when mapping the following variables
    while(cmd.code != (GCode)->code)
    {
    *GCode++;
    }
    getVariables(line,GCode);
    // while(cmd.code != (GCode)->code)
    // {
    // *GCode++;
    // }
    //MOTORSTATUS is set to busy getting a valid G-Code command
    //to indicate that the motor going to start stepping now
    //and unable to take in new G-Code command until the status
    //is changed
    MOTORSTATUS = MOTOR_BUSY;
    (GCode)->doOperation(GCode->code,GCode->varMap);
    return cmd;
}

//This function is to extract the character 'G' as well as the Code
// indicating it is a valid command that exist in the G-Code language.

//The code extracted from the string will be converted into an Integer
//for more convenience in mapping with the code in the array structure

//Throw exception will be executed whenever an invalid G command
//or code in the string that is keyed in by the user

//The value return by this function is in the form of string
//in order to resume the next variable mapping

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

//This function is to map variables from the string with the array structure

//After mapping a valid variable in the string, an integer called 'isValid'
//will be trigger to 1 in order to avoid the same variable to exist in this command

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
    if(len <= 1  && line[len-1] == ' ')
    {
      return ;
    }

    line += 1;
  }
  //This 'if' statement is exceptionally for the USB CDC communication as the string
  //passed in includes some random ASCII values at the end of the string
  //In order to avoid this, a '\n'(ASCII value of 10) is stored into the end of the string
  if(len == 0 || *line == 10)
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
  //This 'if' statement is to double check the end of the string
  //is not one of these ASCII values
  //It is to deal with USB CDC communication as well
  if((*line == 10)||(*line == 13)||(*line == 64))
  {
	  return;
  }
  else if(*line != NULL)
  {
    throwException(VARIABLE_DOES_NOT_EXIST,"Error! Variable does not exist in this command ",*line);
  }
}

//This function is used to extract the value of the variables
//and convert it to a double
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

//This function is to check the code of the command
//whether is a command that converts the value of the variable
//to inch or mm
//Default : MM -> steps
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

//This function is to check the code of the command
//whether to execute the next G-Code command
//in absolute form or relative form
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

//This function handles the 0 code command of the G-Code by converting
// the values of the variables
//into steps
void handleG00(int code,VariableMap *g00VarTableMapping)
{
  double steps;

  if(isInMM == TRUE)
  {
        while(g00VarTableMapping->var!=NULL)
        {
            g00VarTableMapping->var->steps = MM_TO_STEPS(g00VarTableMapping->var->value);
            // g00VarTableMapping->var->value = 0;
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
        // g00VarTableMapping->var->value = 0;
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

//This function handles the 0 code command of the G-Code by converting
// the values of the variables
//into steps with an additional variable called feedrate

void handleG01(int code,VariableMap *g01VarTableMapping)
{
  int feedrate = 0;
  double steps;
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
            // g01VarTableMapping->var->value = 0;
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
          // g01VarTableMapping->var->value = 0;
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

//This function is to extract the value of the feedrate from code 1 of G-code
//If feedrate is not keyed in by the user
//The feedrate will be automatically be 1
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

//This function is to clear all the variables in the structure
//to avoid the next command passed in to take in the old values

void ClearVariablesValue(VariableMap *var)
{
  while(var->name != NULL)
  {
    var->var->name = NULL;
    var->var->value = 0;
    var->var->steps = 0;
    *var++;
  }
  isInMM = TRUE;
}
