#ifndef _COMMANDCODE_H
#define _COMMANDCODE_H
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "Error.h"
#include "ctype.h"



#define isAlpha(x)      (((x) >= 'a' && (x) <= 'z') || ((x) >= 'A' && (x) <= 'Z'))
#define isNumbers(x)          ((x) >= '0' && (x) <= '9')
#define isEmpty(x)          ((x) == ' ')
#define isDecimal(x)    ((x) == '.')
#define isDash(x)       ((x) == '-')

typedef struct StoreCMD StoreCMD;
struct StoreCMD{
  char SetUpcmd;
  char SetUpCode;
  char type;
  int code;

};

typedef struct Variable Variable;
struct Variable {
  char name;
  double value;
  int steps;
  int isValid;
};
typedef struct VariableMap VariableMap;
struct VariableMap{
  char name;
  Variable *var;
};

typedef struct GCodeMapping GCodeMapping;
struct GCodeMapping{
  char *name;
  int code;
  VariableMap *varMap;
  void (*doOperation)(code, varMap);
};

enum UnitType {MM_UNIT = 3,INCH_UNIT = 4}baseType;
#define MM_TO_STEPS(x) ((x)*8)
#define INCH_TO_STEPS(MM_TO_STEPS) ((MM_TO_STEPS)*8*0.0393701)

int Findfeedrate(char Fvar,VariableMap *var);
void handleG00(int code,VariableMap *g00VarTableMapping);
void handleG01(int code,VariableMap *g01VarTableMapping);
void handleG20or21(int code,VariableMap *table);
void handleG90orG91(int code,Variable *table);
StoreCMD decodeGcode(char *line,GCodeMapping *GCode);
char *getGcodeCommand(char *line,GCodeMapping *GCode,StoreCMD *cmd);
void getVariables(char *line,GCodeMapping *GCode);
char *getValue(char *line,GCodeMapping *GCode);




#endif // _COMMANDCODE_H
