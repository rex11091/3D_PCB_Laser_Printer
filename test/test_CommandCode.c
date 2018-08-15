#include "unity.h"
#include "CommandCode.h"
#include "string.h"
#include "Exception.h"
#include "CExceptionConfig.h"
#include "CException.h"
#include "mock_XYZSteps.h"

void setUp(void){}
void tearDown(void){}

void test_G00_expect_G0_cmd_X_var_100_value(void)
{
  CEXCEPTION_T ex;
  int xSteps = 800;
  StoreCMD cmd = {0,0};
  Variable xVar = {0,0,0,0};
  Variable yVar = {0,0,0,0};
  Variable zVar = {0,0,0,0};

  VariableMap g00VarTableMapping[] = {
    {'X',&xVar},
    {'Y',&yVar},
    {'Z',&zVar},
    {NULL,NULL},
  };
  GCodeMapping GCode00[] = {
    {.name = "G",.code = 0,.varMap = g00VarTableMapping,.doOperation = handleG00},
    {NULL,NULL,NULL,NULL},
  };
  char *line = "G00 X100";

  Try{
    // SetUpMotorInfo_ExpectAndReturn(NULL,xSteps,1);
    cmd = decodeGcode(line,GCode00);
    TEST_ASSERT_EQUAL('G',cmd.type);
    TEST_ASSERT_EQUAL(0,cmd.code);
    TEST_ASSERT_EQUAL('X',xVar.name);
    TEST_ASSERT_EQUAL(100,xVar.value);

  }Catch(ex){
    dumpException(ex);
  }
}

void test_space_G00_expect_G0_cmd_X_var_100_value(void)
{
  CEXCEPTION_T ex;
  int xSteps = 800;
  StoreCMD cmd = {0,0};
  Variable xVar = {0,0,0,0};
  Variable yVar = {0,0,0,0};
  Variable zVar = {0,0,0,0};

  VariableMap g00VarTableMapping[] = {
    {'X',&xVar},
    {'Y',&yVar},
    {'Z',&zVar},
    {NULL,NULL},
  };
  GCodeMapping GCode00[] = {
    {.name = "G",.code = 0,.varMap = g00VarTableMapping,.doOperation = handleG00},
    {NULL,NULL,NULL,NULL},
  };
  char *line = " G00 X100";

  Try{
    // SetUpMotorInfo_ExpectAndReturn(NULL,xSteps,1);
    cmd = decodeGcode(line,GCode00);
    TEST_ASSERT_EQUAL('G',cmd.type);
    TEST_ASSERT_EQUAL(0,cmd.code);
    TEST_ASSERT_EQUAL('X',xVar.name);
    TEST_ASSERT_EQUAL(100,xVar.value);

  }Catch(ex){
    dumpException(ex);
  }
}

void test_E00_expect_throw_exception_error_command(void)
{
  CEXCEPTION_T ex;
  StoreCMD cmd = {0,0};
  Variable xVar = {0,0,0,0};
  Variable yVar = {0,0,0,0};
  Variable zVar = {0,0,0,0};

  VariableMap g00VarTableMapping[] = {
    {'X',&xVar},
    {'Y',&yVar},
    {'Z',&zVar},
    {NULL,NULL},
  };
  GCodeMapping GCode00[] = {
    {.name = "G",.code = 0,.varMap = g00VarTableMapping,.doOperation = handleG00},
    {NULL,NULL,NULL,NULL},
  };
  char *line = "E00 X100";

  Try{
    cmd = decodeGcode(line,GCode00);

  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_COMMAND,ex->errorCode);
  }
  freeException(ex);
}

void test_G90_expect_G90_cmd(void)
{
  CEXCEPTION_T ex;
  StoreCMD SetUpcmd = {0,0};

  GCodeMapping GCode90[] = {
    {.name = "G",.code = 90,.varMap = NULL,.doOperation = handleG90orG91},
    {NULL,NULL,NULL,NULL},
  };
  char *line = "G90 ";

  Try{
    SetUpcmd = decodeGcode(line,GCode90);
    TEST_ASSERT_EQUAL('G',SetUpcmd.type);
    TEST_ASSERT_EQUAL(90,SetUpcmd.code);
  }Catch(ex){
    dumpException(ex);
  }
}

void test_G_space_00_expect_G0_cmd_X_var_100_value(void)
{
  CEXCEPTION_T ex;
  int xSteps = 800;
  StoreCMD cmd = {0,0};
  Variable xVar = {0,0,0,0};
  Variable yVar = {0,0,0,0};
  Variable zVar = {0,0,0,0};

  VariableMap g00VarTableMapping[] = {
    {'X',&xVar},
    {'Y',&yVar},
    {'Z',&zVar},
    {NULL,NULL},
  };
  GCodeMapping GCode00[] = {
    {.name = "G",.code = 0,.varMap = g00VarTableMapping,.doOperation = handleG00},
    {NULL,NULL,NULL,NULL},
  };
  char *line = "G 00 X100";

  Try{
    // SetUpMotorInfo_ExpectAndReturn(NULL,xSteps,1);
    cmd = decodeGcode(line,GCode00);
    TEST_ASSERT_EQUAL('G',cmd.type);
    TEST_ASSERT_EQUAL(0,cmd.code);
    TEST_ASSERT_EQUAL('X',xVar.name);
    TEST_ASSERT_EQUAL(100,xVar.value);
    TEST_ASSERT_EQUAL(800,xVar.steps);

  }Catch(ex){
    dumpException(ex);
  }
}

void test_GE00_expect_throw_exception_error_code(void)
{
  CEXCEPTION_T ex;
  StoreCMD cmd = {0,0};
  Variable xVar = {0,0,0,0};
  Variable yVar = {0,0,0,0};
  Variable zVar = {0,0,0,0};

  VariableMap g00VarTableMapping[] = {
    {'X',&xVar},
    {'Y',&yVar},
    {'Z',&zVar},
    {NULL,NULL},
  };
  GCodeMapping GCode00[] = {
    {.name = "G",.code = 0,.varMap = g00VarTableMapping,.doOperation = handleG00},
    {NULL,NULL,NULL,NULL},
  };
  char *line = "GE00 X100";

  Try{
    cmd = decodeGcode(line,GCode00);

  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_CODE,ex->errorCode);
  }
    freeException(ex);
}

void test_G001_expect_G1_cmd_X_var_100_val(void)
{
  CEXCEPTION_T ex;
  int xSteps = 800;
  StoreCMD cmd = {0,0};
  Variable xVar = {0,0,0,0};
  Variable yVar = {0,0,0,0};
  Variable zVar = {0,0,0,0};
  Variable fVar = {0,0,0,0};

  VariableMap g01VarTableMapping[] = {
    {'X',&xVar},
    {'Y',&yVar},
    {'Z',&zVar},
    {'F',&fVar},
    {NULL,NULL},
  };
  GCodeMapping GCode001[] = {
    {.name = "G",.code = 1,.varMap = g01VarTableMapping,.doOperation = handleG00},
    {NULL,NULL,NULL,NULL},
  };
  char *line = "G001 X100";

  Try{
    // SetUpMotorInfo_ExpectAndReturn(NULL,xSteps,1);
    cmd = decodeGcode(line,GCode001);
    TEST_ASSERT_EQUAL('G',cmd.type);
    TEST_ASSERT_EQUAL(1,cmd.code);
    TEST_ASSERT_EQUAL('X',xVar.name);
    TEST_ASSERT_EQUAL(100,xVar.value);
    TEST_ASSERT_EQUAL(800,xVar.steps);

  }Catch(ex){
    dumpException(ex);
  }
}

void test_G00_XY100_expect_throw_exception_error_value(void)
{
  CEXCEPTION_T ex;
  StoreCMD cmd = {0,0};
  Variable xVar = {0,0,0,0};
  Variable yVar = {0,0,0,0};
  Variable zVar = {0,0,0,0};

  VariableMap g00VarTableMapping[] = {
    {'X',&xVar},
    {'Y',&yVar},
    {'Z',&zVar},
    {NULL,NULL},
  };
  GCodeMapping GCode00[] = {
    {.name = "G",.code = 0,.varMap = g00VarTableMapping,.doOperation = handleG00},
    {NULL,NULL,NULL,NULL},
  };
  char *line = "G00 XY100";

  Try{
    cmd = decodeGcode(line,GCode00);

  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_VALUE,ex->errorCode);
  }
  freeException(ex);
}

void test_G00_expect_G0_cmd_X_var_101_value_Y_var_999_value(void)
{
  CEXCEPTION_T ex;
  int xSteps = 808;
  int ySteps = 7992;
  StoreCMD cmd = {0,0};
  Variable xVar = {0,0,0,0};
  Variable yVar = {0,0,0,0};
  Variable zVar = {0,0,0,0};

  VariableMap g00VarTableMapping[] = {
    {'X',&xVar},
    {'Y',&yVar},
    {'Z',&zVar},
    {NULL,NULL},
  };
  GCodeMapping GCode00[] = {
    {.name = "G",.code = 0,.varMap = g00VarTableMapping,.doOperation = handleG00},
    {NULL,NULL,NULL,NULL},
  };
  char *line = "G00 X101 Y999";
  Try{
    // SetUpMotorInfo_ExpectAndReturn(NULL,xSteps,1);
    // SetUpMotorInfo_ExpectAndReturn(NULL,ySteps,1);
    cmd = decodeGcode(line,GCode00);
    TEST_ASSERT_EQUAL('G',cmd.type);
    TEST_ASSERT_EQUAL(0,cmd.code);
    TEST_ASSERT_EQUAL('X',xVar.name);
    TEST_ASSERT_EQUAL(101,xVar.value);
    TEST_ASSERT_EQUAL('Y',yVar.name);
    TEST_ASSERT_EQUAL(999,yVar.value);
    TEST_ASSERT_EQUAL(808,xVar.steps);
    TEST_ASSERT_EQUAL(7992,yVar.steps);

  }Catch(ex){
    dumpException(ex);
  }
}

void test_G00_X101_YZ999_expect_throw_exception_error_value(void)
{
  CEXCEPTION_T ex;
  StoreCMD cmd = {0,0};
  Variable xVar = {0,0,0,0};
  Variable yVar = {0,0,0,0};
  Variable zVar = {0,0,0,0};

  VariableMap g00VarTableMapping[] = {
    {'X',&xVar},
    {'Y',&yVar},
    {'Z',&zVar},
    {NULL,NULL},
  };
  GCodeMapping GCode00[] = {
    {.name = "G",.code = 0,.varMap = g00VarTableMapping,.doOperation = handleG00},
    {NULL,NULL,NULL,NULL},
  };
  char *line = "G00 X101 YZ999";
  Try{
    cmd = decodeGcode(line,GCode00);

  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_VALUE,ex->errorCode);
  }
  freeException(ex);
}

void test_G00_X101_YZ999_expect_throw_exception_error_duplicate_variable(void)
{
  CEXCEPTION_T ex;
  StoreCMD cmd = {0,0};
  Variable xVar = {0,0,0,0};
  Variable yVar = {0,0,0,0};
  Variable zVar = {0,0,0,0};

  VariableMap g00VarTableMapping[] = {
    {'X',&xVar},
    {'Y',&yVar},
    {'Z',&zVar},
    {NULL,NULL},
  };
  GCodeMapping GCode00[] = {
    {.name = "G",.code = 0,.varMap = g00VarTableMapping,.doOperation = handleG00},
    {NULL,NULL,NULL,NULL},
  };
  char *line = "G00 X101 X999";
  Try{
    cmd = decodeGcode(line,GCode00);

  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_DUPLICATE_VARIABLE,ex->errorCode);
  }
  freeException(ex);
}

void test_G00_expect_G0_cmd_X_var_999_value_Y_var_101_value_Z_var_20_value(void)
{
  CEXCEPTION_T ex;
  int xSteps = 7992;
  int ySteps = 808;
  int zSteps = 160;
  StoreCMD cmd = {0,0};
  Variable xVar = {0,0,0,0};
  Variable yVar = {0,0,0,0};
  Variable zVar = {0,0,0,0};

  VariableMap g00VarTableMapping[] = {
    {'X',&xVar},
    {'Y',&yVar},
    {'Z',&zVar},
    {NULL,NULL},
  };
  GCodeMapping GCode00[] = {
    {.name = "G",.code = 0,.varMap = g00VarTableMapping,.doOperation = handleG00},
    {NULL,NULL,NULL,NULL},
  };
  char *line = "G00 Y101 X999 Z20";
  Try{
    // SetUpMotorInfo_ExpectAndReturn(NULL,xSteps,1);
    // SetUpMotorInfo_ExpectAndReturn(NULL,ySteps,1);
    // SetUpMotorInfo_ExpectAndReturn(NULL,zSteps,1);
    cmd = decodeGcode(line,GCode00);
    TEST_ASSERT_EQUAL('G',cmd.type);
    TEST_ASSERT_EQUAL(0,cmd.code);
    TEST_ASSERT_EQUAL('X',xVar.name);
    TEST_ASSERT_EQUAL(999,xVar.value);
    TEST_ASSERT_EQUAL('Y',yVar.name);
    TEST_ASSERT_EQUAL(101,yVar.value);
    TEST_ASSERT_EQUAL('Z',zVar.name);
    TEST_ASSERT_EQUAL(20,zVar.value);

  }Catch(ex){
    dumpException(ex);
  }
}

void test_G001_expect_G1_cmd_X_var_100_val_Y_var_20_val_Z_var_30_val_F_var_200_val(void)
{
  CEXCEPTION_T ex;
  int xSteps = 160000;
  int ySteps = 32000;
  int zSteps = 48000;
  StoreCMD cmd = {0,0};
  Variable xVar = {0,0,0,0};
  Variable yVar = {0,0,0,0};
  Variable zVar = {0,0,0,0};
  Variable fVar = {0,0,0,0};

  VariableMap g01VarTableMapping[] = {
    {'X',&xVar},
    {'Y',&yVar},
    {'Z',&zVar},
    {'F',&fVar},
    {NULL,NULL},
  };
  GCodeMapping GCode001[] = {
    {.name = "G",.code = 1,.varMap = g01VarTableMapping,.doOperation = handleG01},
    {NULL,NULL,NULL,NULL},
  };
  char *line = "G001 X100 Y20 Z30 F200";

  Try{
    // SetUpMotorInfo_ExpectAndReturn(NULL,xSteps,1);
    // SetUpMotorInfo_ExpectAndReturn(NULL,ySteps,1);
    // SetUpMotorInfo_ExpectAndReturn(NULL,zSteps,1);
    cmd = decodeGcode(line,GCode001);
    TEST_ASSERT_EQUAL('G',cmd.type);
    TEST_ASSERT_EQUAL(1,cmd.code);
    TEST_ASSERT_EQUAL('X',xVar.name);
    TEST_ASSERT_EQUAL(100,xVar.value);
    TEST_ASSERT_EQUAL('Y',yVar.name);
    TEST_ASSERT_EQUAL(20,yVar.value);
    TEST_ASSERT_EQUAL('Z',zVar.name);
    TEST_ASSERT_EQUAL(30,zVar.value);
    TEST_ASSERT_EQUAL('F',fVar.name);
    TEST_ASSERT_EQUAL(200,fVar.value);
    TEST_ASSERT_EQUAL(160000,xVar.steps);
    TEST_ASSERT_EQUAL(32000,yVar.steps);
    TEST_ASSERT_EQUAL(48000,zVar.steps);
    TEST_ASSERT_EQUAL(0,fVar.steps);

  }Catch(ex){
    dumpException(ex);
  }
}

void test_G00_expect_G0_cmd_Y_var_101_value_X_var_999_value_Z_var_21_value(void)
{
  CEXCEPTION_T ex;
  int xSteps = 7992;
  int ySteps = 808;
  int zSteps = 168;
  StoreCMD cmd = {0,0};
  Variable xVar = {0,0,0,0};
  Variable yVar = {0,0,0,0};
  Variable zVar = {0,0,0,0};

  VariableMap g00VarTableMapping[] = {
    {'X',&xVar},
    {'Y',&yVar},
    {'Z',&zVar},
    {NULL,NULL},
  };
  GCodeMapping GCode00[] = {
    {.name = "G",.code = 0,.varMap = g00VarTableMapping,.doOperation = handleG00},
    {NULL,NULL,NULL,NULL},
  };
  char *line = "G00Y101X999Z21";
  Try{
    // SetUpMotorInfo_ExpectAndReturn(NULL,xSteps,1);
    // SetUpMotorInfo_ExpectAndReturn(NULL,ySteps,1);
    // SetUpMotorInfo_ExpectAndReturn(NULL,zSteps,1);
    cmd = decodeGcode(line,GCode00);
    TEST_ASSERT_EQUAL('G',cmd.type);
    TEST_ASSERT_EQUAL(0,cmd.code);
    TEST_ASSERT_EQUAL('X',xVar.name);
    TEST_ASSERT_EQUAL(999,xVar.value);
    TEST_ASSERT_EQUAL('Y',yVar.name);
    TEST_ASSERT_EQUAL(101,yVar.value);
    TEST_ASSERT_EQUAL('Z',zVar.name);
    TEST_ASSERT_EQUAL(21,zVar.value);

  }Catch(ex){
    dumpException(ex);
  }
}

void test_G00_expect_Y_var_101_throw_exception_error_value(void)
{
  CEXCEPTION_T ex;
  StoreCMD cmd = {0,0};
  Variable xVar = {0,0,0,0};
  Variable yVar = {0,0,0,0};
  Variable zVar = {0,0,0,0};

  VariableMap g00VarTableMapping[] = {
    {'X',&xVar},
    {'Y',&yVar},
    {'Z',&zVar},
    {NULL,NULL},
  };
  GCodeMapping GCode00[] = {
    {.name = "G",.code = 0,.varMap = g00VarTableMapping,.doOperation = handleG00},
    {NULL,NULL,NULL,NULL},
  };
  char *line = "G00Y101XU999Z21";
  Try{
    cmd = decodeGcode(line,GCode00);
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_VALUE,ex->errorCode);
    TEST_ASSERT_EQUAL('Y',yVar.name);
    TEST_ASSERT_EQUAL(101,yVar.value);
  }
  freeException(ex);
}

void test_G00_expect_throw_exception_variable_does_not_exist(void)
{
  CEXCEPTION_T ex;
  StoreCMD cmd = {0,0};
  Variable xVar = {0,0,0,0};
  Variable yVar = {0,0,0,0};
  Variable zVar = {0,0,0,0};

  VariableMap g00VarTableMapping[] = {
    {'X',&xVar},
    {'Y',&yVar},
    {'Z',&zVar},
    {NULL,NULL},
  };
  GCodeMapping GCode00[] = {
    {.name = "G",.code = 0,.varMap = g00VarTableMapping,.doOperation = handleG00},
    {NULL,NULL,NULL,NULL},
  };
  char *line = "G00C101X999Z21";
  Try{
    cmd = decodeGcode(line,GCode00);
  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(VARIABLE_DOES_NOT_EXIST,ex->errorCode);
  }
  freeException(ex);
}

void test_G00_with_dash_on_var_expect_G0_cmd_X_var_99_value_Y_var_101_value_Z_var_20_value(void)
{
  CEXCEPTION_T ex;
  int xSteps = 792;
  int ySteps = 808;
  int zSteps = 160;
  StoreCMD cmd = {0,0};
  Variable xVar = {0,0,0,0};
  Variable yVar = {0,0,0,0};
  Variable zVar = {0,0,0,0};

  VariableMap g00VarTableMapping[] = {
    {'X',&xVar},
    {'Y',&yVar},
    {'Z',&zVar},
    {NULL,NULL},
  };
  GCodeMapping GCode00[] = {
    {.name = "G",.code = 0,.varMap = g00VarTableMapping,.doOperation = handleG00},
    {NULL,NULL,NULL,NULL},
  };
  char *line = "G00 Y101 X - 99 Z - 20";
  Try{
    // SetUpMotorInfo_ExpectAndReturn(NULL,xSteps,1);
    // SetUpMotorInfo_ExpectAndReturn(NULL,ySteps,1);
    // SetUpMotorInfo_ExpectAndReturn(NULL,zSteps,1);
    cmd = decodeGcode(line,GCode00);
    TEST_ASSERT_EQUAL('G',cmd.type);
    TEST_ASSERT_EQUAL(0,cmd.code);
    TEST_ASSERT_EQUAL('X',xVar.name);
    TEST_ASSERT_EQUAL(99,xVar.value);
    TEST_ASSERT_EQUAL('Y',yVar.name);
    TEST_ASSERT_EQUAL(101,yVar.value);
    TEST_ASSERT_EQUAL('Z',zVar.name);
    TEST_ASSERT_EQUAL(20,zVar.value);
    TEST_ASSERT_EQUAL(792,xVar.steps);
    TEST_ASSERT_EQUAL(808,yVar.steps);
    TEST_ASSERT_EQUAL(160,zVar.steps);
  }Catch(ex){
    dumpException(ex);
  }
}

void test_G00_expect_G0_cmd_X_var_99_point_99_value_Y_var_101_value_Z_var_20_value(void)
{
  CEXCEPTION_T ex;
  int xSteps = 799;
  int ySteps = 808;
  int zSteps = 160;
  StoreCMD cmd = {0,0};
  Variable xVar = {0,0,0,0};
  Variable yVar = {0,0,0,0};
  Variable zVar = {0,0,0,0};

  VariableMap g00VarTableMapping[] = {
    {'X',&xVar},
    {'Y',&yVar},
    {'Z',&zVar},
    {NULL,NULL},
  };
  GCodeMapping GCode00[] = {
    {.name = "G",.code = 0,.varMap = g00VarTableMapping,.doOperation = handleG00},
    {NULL,NULL,NULL,NULL},
  };
  char *line = "G00 Y101 X99.99 Z20";
  Try{
    // SetUpMotorInfo_ExpectAndReturn(NULL,xSteps,1);
    // SetUpMotorInfo_ExpectAndReturn(NULL,ySteps,1);
    // SetUpMotorInfo_ExpectAndReturn(NULL,zSteps,1);
    cmd = decodeGcode(line,GCode00);
    TEST_ASSERT_EQUAL('G',cmd.type);
    TEST_ASSERT_EQUAL(0,cmd.code);
    TEST_ASSERT_EQUAL('X',xVar.name);
    TEST_ASSERT_EQUAL(99.99,xVar.value);
    TEST_ASSERT_EQUAL('Y',yVar.name);
    TEST_ASSERT_EQUAL(101,yVar.value);
    TEST_ASSERT_EQUAL('Z',zVar.name);
    TEST_ASSERT_EQUAL(20,zVar.value);
    TEST_ASSERT_EQUAL(799,xVar.steps);
    TEST_ASSERT_EQUAL(808,yVar.steps);
    TEST_ASSERT_EQUAL(160,zVar.steps);
  }Catch(ex){
    dumpException(ex);
  }
}

void test_G00_Y101_X99_point_99_point_5_expect_throw_exception_error_value(void)
{
  CEXCEPTION_T ex;
  StoreCMD cmd = {0,0};
  Variable xVar = {0,0,0,0};
  Variable yVar = {0,0,0,0};
  Variable zVar = {0,0,0,0};

  VariableMap g00VarTableMapping[] = {
    {'X',&xVar},
    {'Y',&yVar},
    {'Z',&zVar},
    {NULL,NULL},
  };
  GCodeMapping GCode00[] = {
    {.name = "G",.code = 0,.varMap = g00VarTableMapping,.doOperation = handleG00},
    {NULL,NULL,NULL,NULL},
  };
  char *line = "G00 Y101 X99.99.5 Z20";
  Try{
    cmd = decodeGcode(line,GCode00);

  }Catch(ex){
    dumpException(ex);
    TEST_ASSERT_EQUAL(ERROR_VALUE,ex->errorCode);
  }
  freeException(ex);
}

void test_G20_G00_Y101_X99_point_99_Z_20_expect_value_from_MM_to_Steps(void)
{
  CEXCEPTION_T ex;
  int xSteps = 799;
  int ySteps = 808;
  int zSteps = 160;
  StoreCMD cmd = {0,0};
  Variable xVar = {0,0,0,0};
  Variable yVar = {0,0,0,0};
  Variable zVar = {0,0,0,0};
  VariableMap g00VarTableMapping[] = {
    {'X',&xVar},
    {'Y',&yVar},
    {'Z',&zVar},
    {NULL,NULL},
  };
  GCodeMapping GCode[] = {
    {.name = "G",.code = 0,.varMap = g00VarTableMapping,.doOperation = handleG00},
    {.name = "G",.code = 20,.varMap = NULL,.doOperation = handleG20or21},
    {NULL,NULL,NULL,NULL},
  };
  char *SetUp = "G20";
  char *line = "G00 Y101 X99.99 Z20";
  Try{
    // SetUpMotorInfo_ExpectAndReturn(NULL,xSteps,1);
    // SetUpMotorInfo_ExpectAndReturn(NULL,ySteps,1);
    // SetUpMotorInfo_ExpectAndReturn(NULL,zSteps,1);
    cmd = decodeGcode(SetUp,GCode);
    cmd = decodeGcode(line,GCode);
    TEST_ASSERT_EQUAL('G',cmd.type);
    TEST_ASSERT_EQUAL(0,cmd.code);
    TEST_ASSERT_EQUAL('X',xVar.name);
    TEST_ASSERT_EQUAL(99.99,xVar.value);
    TEST_ASSERT_EQUAL('Y',yVar.name);
    TEST_ASSERT_EQUAL(101,yVar.value);
    TEST_ASSERT_EQUAL('Z',zVar.name);
    TEST_ASSERT_EQUAL(20,zVar.value);
    TEST_ASSERT_EQUAL(799,xVar.steps);
    TEST_ASSERT_EQUAL(808,yVar.steps);
    TEST_ASSERT_EQUAL(160,zVar.steps);
  }Catch(ex){
    dumpException(ex);
  }
}

void test_G21_G00_Y101_X99_point_99_Z_20_expect_value_from_INCH_to_Steps(void)
{
  CEXCEPTION_T ex;
  int xSteps = 31;
  int ySteps = 31;
  int zSteps = 6;

  StoreCMD cmd = {0,0};
  Variable xVar = {0,0,0,0};
  Variable yVar = {0,0,0,0};
  Variable zVar = {0,0,0,0};

  VariableMap g00VarTableMapping[] = {
    {'X',&xVar},
    {'Y',&yVar},
    {'Z',&zVar},
    {NULL,NULL},
  };
  GCodeMapping GCode[] = {
    {.name = "G",.code = 0,.varMap = g00VarTableMapping,.doOperation = handleG00},
    {.name = "G",.code = 21,.varMap = NULL,.doOperation = handleG20or21},
    {NULL,NULL,NULL,NULL},
  };
  char *SetUp = "G21";
  char *line = "G00 Y101 X99.99 Z20";
  Try{
    // SetUpMotorInfo_ExpectAndReturn(NULL,xSteps,1);
    // SetUpMotorInfo_ExpectAndReturn(NULL,ySteps,1);
    // SetUpMotorInfo_ExpectAndReturn(NULL,zSteps,1);
    cmd = decodeGcode(SetUp,GCode);
    cmd = decodeGcode(line,GCode);
    TEST_ASSERT_EQUAL('G',cmd.type);
    TEST_ASSERT_EQUAL(0,cmd.code);
    TEST_ASSERT_EQUAL('X',xVar.name);
    TEST_ASSERT_EQUAL(99.99,xVar.value);
    TEST_ASSERT_EQUAL('Y',yVar.name);
    TEST_ASSERT_EQUAL(101,yVar.value);
    TEST_ASSERT_EQUAL('Z',zVar.name);
    TEST_ASSERT_EQUAL(20,zVar.value);
    TEST_ASSERT_EQUAL(31,xVar.steps);
    TEST_ASSERT_EQUAL(31,yVar.steps);
    TEST_ASSERT_EQUAL(6,zVar.steps);
  }Catch(ex){
    dumpException(ex);
  }
}

void test_g21_g00_y101_x99_point_99_z20_expect_variable_toupper_and_value_from_INCH_to_Steps(void)
{
  CEXCEPTION_T ex;
  int xSteps = 31;
  int ySteps = 31;
  int zSteps = 6;

  StoreCMD cmd = {0,0};
  Variable xVar = {0,0,0,0};
  Variable yVar = {0,0,0,0};
  Variable zVar = {0,0,0,0};

  VariableMap g00VarTableMapping[] = {
    {'X',&xVar},
    {'Y',&yVar},
    {'Z',&zVar},
    {NULL,NULL},
  };
  GCodeMapping GCode[] = {
    {.name = "G",.code = 0,.varMap = g00VarTableMapping,.doOperation = handleG00},
    {.name = "G",.code = 21,.varMap = NULL,.doOperation = handleG20or21},
    {NULL,NULL,NULL,NULL},
  };
  char *SetUp = "g21";
  char *line = "g00 y101 x99.99 Z20";
  Try{
    // SetUpMotorInfo_ExpectAndReturn(NULL,xSteps,1);
    // SetUpMotorInfo_ExpectAndReturn(NULL,ySteps,1);
    // SetUpMotorInfo_ExpectAndReturn(NULL,zSteps,1);
    cmd = decodeGcode(SetUp,GCode);
    cmd = decodeGcode(line,GCode);
    TEST_ASSERT_EQUAL('G',cmd.type);
    TEST_ASSERT_EQUAL(0,cmd.code);
    TEST_ASSERT_EQUAL('X',xVar.name);
    TEST_ASSERT_EQUAL(99.99,xVar.value);
    TEST_ASSERT_EQUAL('Y',yVar.name);
    TEST_ASSERT_EQUAL(101,yVar.value);
    TEST_ASSERT_EQUAL('Z',zVar.name);
    TEST_ASSERT_EQUAL(20,zVar.value);
    TEST_ASSERT_EQUAL(31,xVar.steps);
    TEST_ASSERT_EQUAL(31,yVar.steps);
    TEST_ASSERT_EQUAL(6,zVar.steps);
  }Catch(ex){
    dumpException(ex);
  }
}

void test_G21_G00_G91_G01_cmd_expect_absolute_steps(void)
{
  CEXCEPTION_T ex;
  int xSteps = 31;
  int ySteps = 31;
  int zSteps = 6;

  int x1Steps = 472;
  int y1Steps = 629;
  int z1Steps = 314;

  StoreCMD cmd = {0,0};
  StoreCMD cmd1 = {0,0};

  Variable xVar = {0,0,0,0};
  Variable yVar = {0,0,0,0};
  Variable zVar = {0,0,0,0};

  Variable x1Var = {0,0,0,0};
  Variable y1Var = {0,0,0,0};
  Variable z1Var = {0,0,0,0};
  Variable fVar = {0,0,0,0};

  VariableMap g00VarTableMapping[] = {
    {'X',&xVar},
    {'Y',&yVar},
    {'Z',&zVar},
    {NULL,NULL},
  };
  VariableMap g01VarTableMapping[] = {
    {'X',&x1Var},
    {'Y',&y1Var},
    {'Z',&z1Var},
    {'F',&fVar},
    {NULL,NULL},
  };
  GCodeMapping GCode[] = {
    {.name = "G",.code = 0,.varMap = g00VarTableMapping,.doOperation = handleG00},
    {.name = "G",.code = 21,.varMap = NULL,.doOperation = handleG20or21},
    {.name = "G",.code = 91,.varMap = NULL,.doOperation = handleG90orG91},
    {.name = "G",.code = 1,.varMap = g01VarTableMapping,.doOperation = handleG01},
    {NULL,NULL,NULL,NULL},
  };
  char *SetUp = "G21";
  char *line = "G00 Y101 X99.99 Z20";
  char *SetUp2 = "G91";
  char *line2 = "G01 Z10 Y20 X15 F100";
  Try{
    // SetUpMotorInfo_ExpectAndReturn(NULL,xSteps,1);
    // SetUpMotorInfo_ExpectAndReturn(NULL,ySteps,1);
    // SetUpMotorInfo_ExpectAndReturn(NULL,zSteps,1);
    cmd = decodeGcode(SetUp,GCode);
    cmd = decodeGcode(line,GCode);
    TEST_ASSERT_EQUAL('G',cmd.type);
    TEST_ASSERT_EQUAL(0,cmd.code);
    TEST_ASSERT_EQUAL('X',xVar.name);
    TEST_ASSERT_EQUAL(99.99,xVar.value);
    TEST_ASSERT_EQUAL('Y',yVar.name);
    TEST_ASSERT_EQUAL(101,yVar.value);
    TEST_ASSERT_EQUAL('Z',zVar.name);
    TEST_ASSERT_EQUAL(20,zVar.value);
    TEST_ASSERT_EQUAL(31,xVar.steps);
    TEST_ASSERT_EQUAL(31,yVar.steps);
    TEST_ASSERT_EQUAL(6,zVar.steps);
    // SetUpMotorInfo_ExpectAndReturn(NULL,x1Steps,1);
    // SetUpMotorInfo_ExpectAndReturn(NULL,y1Steps,1);
    // SetUpMotorInfo_ExpectAndReturn(NULL,z1Steps,1);
    cmd1 = decodeGcode(SetUp2,GCode);
    cmd1 = decodeGcode(line2,GCode);
    TEST_ASSERT_EQUAL('G',cmd1.type);
    TEST_ASSERT_EQUAL(1,cmd1.code);
    TEST_ASSERT_EQUAL('X',x1Var.name);
    TEST_ASSERT_EQUAL(15,x1Var.value);
    TEST_ASSERT_EQUAL('Y',y1Var.name);
    TEST_ASSERT_EQUAL(20,y1Var.value);
    TEST_ASSERT_EQUAL('Z',z1Var.name);
    TEST_ASSERT_EQUAL(10,z1Var.value);
    TEST_ASSERT_EQUAL('F',fVar.name);
    TEST_ASSERT_EQUAL(100,fVar.value);
    TEST_ASSERT_EQUAL(472,x1Var.steps);
    TEST_ASSERT_EQUAL(629,y1Var.steps);
    TEST_ASSERT_EQUAL(314,z1Var.steps);
    TEST_ASSERT_EQUAL(0,fVar.steps);
  }Catch(ex){
    dumpException(ex);
  }
}

void test_G21_(void)
{
    CEXCEPTION_T ex;
    StoreCMD cmd = {0,0};
    StoreCMD cmd1 = {0,0};

    Variable xVar = {0,0,0,0};
    Variable yVar = {0,0,0,0};
    Variable zVar = {0,0,0,0};

    VariableMap g00VarTableMapping[] = {
      {'X',&xVar},
      {'Y',&yVar},
      {'Z',&zVar},
      {NULL,NULL},
    };
    GCodeMapping GCode[] = {
      {.name = "G",.code = 0,.varMap = g00VarTableMapping,.doOperation = handleG00},
      {.name = "G",.code = 21,.varMap = NULL,.doOperation = handleG20or21},
      {NULL,NULL,NULL,NULL},
    };
    char *SetUp = "G21";
    Try{
      cmd = decodeGcode(SetUp,GCode);
      TEST_ASSERT_EQUAL('G',cmd.type);
      TEST_ASSERT_EQUAL(21,cmd.code);
    }Catch(ex)
    {
      dumpException(ex);
    }
}

void test_repetition_of_G00_(void)
{

    CEXCEPTION_T ex;
    StoreCMD cmd = {0,0};
    StoreCMD cmd1 = {0,0};

    Variable xVar = {0,0,0,0};
    Variable yVar = {0,0,0,0};
    Variable zVar = {0,0,0,0};

    VariableMap g00VarTableMapping[] = {
      {'X',&xVar},
      {'Y',&yVar},
      {'Z',&zVar},
      {NULL,NULL},
    };
    GCodeMapping GCode[] = {
      {.name = "G",.code = 0,.varMap = g00VarTableMapping,.doOperation = handleG00},
      {NULL,NULL,NULL,NULL},
    };
    Try{
    char *line = "G00 Y101 X99.99 Z20";
    char *line1 = "G00 Y100 X50 Z30";
    cmd = decodeGcode(line1,GCode);
    cmd = decodeGcode(line,GCode);
    TEST_ASSERT_EQUAL('G',cmd.type);
    TEST_ASSERT_EQUAL(0,cmd.code);
    TEST_ASSERT_EQUAL('X',xVar.name);
    TEST_ASSERT_EQUAL(99.99,xVar.value);
    TEST_ASSERT_EQUAL('Y',yVar.name);
    TEST_ASSERT_EQUAL(101,yVar.value);
    TEST_ASSERT_EQUAL('Z',zVar.name);
    TEST_ASSERT_EQUAL(20,zVar.value);
    TEST_ASSERT_EQUAL(31,xVar.steps);
    TEST_ASSERT_EQUAL(31,yVar.steps);
    TEST_ASSERT_EQUAL(6,zVar.steps);
  }Catch(ex)
  {
    dumpException(ex);
  }
}
