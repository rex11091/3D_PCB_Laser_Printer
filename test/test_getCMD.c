#include "unity.h"
#include "getCMD.h"
#include "string.h"
#include "stdio.h"
#include "stdint.h"
#include "InfoVerifier.h"
#include "CommandCode.h"
#include "Exception.h"
#include "CExceptionConfig.h"
#include "CException.h"

void setUp(void){}
void tearDown(void){}

void test_getCMD(void)
{
    char buffer[30] = {0};
    CEXCEPTION_T ex;
    int xSteps = 80;
    int ySteps = 160;
    int zSteps = 240;
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
    uint8_t *Buf = "G00 X";
    uint8_t *Buf1 = "10Y";
    uint8_t *Buf2 = "20 Z30\n ";


    int a = getcommand(buffer,Buf,strlen(Buf));
    TEST_ASSERT_EQUAL(0,a);
    TEST_ASSERT_EQUAL_ARRAY(buffer,0,Buf);
    a = getcommand(buffer,Buf1,strlen(Buf1));
    TEST_ASSERT_EQUAL(0,a);
    TEST_ASSERT_EQUAL_ARRAY(buffer,strlen(Buf),Buf1);
    a = getcommand(buffer,Buf2,strlen(Buf2));
    TEST_ASSERT_EQUAL(1,a);
    TEST_ASSERT_EQUAL_ARRAY(buffer,strlen(Buf)+strlen(Buf1),Buf2);

    Try{
      cmd = decodeGcode(buffer,GCode00);
      TEST_ASSERT_EQUAL('G',cmd.type);
      TEST_ASSERT_EQUAL(0,cmd.code);
      TEST_ASSERT_EQUAL('X',xVar.name);
      TEST_ASSERT_EQUAL(10,xVar.value);
      TEST_ASSERT_EQUAL('Y',yVar.name);
      TEST_ASSERT_EQUAL(20,yVar.value);
      TEST_ASSERT_EQUAL('Z',zVar.name);
      TEST_ASSERT_EQUAL(30,zVar.value);
    }Catch(ex){
      dumpException(ex);
    }
}

void test_getCMD_two_buffer_(void)
{
    char buffer[30] = {0};
    char buffer1[30] = {0};
    CEXCEPTION_T ex;
    int xSteps = 16000;
    int ySteps = 64000;
    int zSteps = 48000;
    int x1Steps = 120;
    int y1Steps = 480;
    int z1Steps = 280;
    StoreCMD cmd = {0,0};
    Variable xVar = {0,0,0,0};
    Variable yVar = {0,0,0,0};
    Variable zVar = {0,0,0,0};
    Variable fVar = {0,0,0,0};

    Variable x1Var = {0,0,0,0};
    Variable y1Var = {0,0,0,0};
    Variable z1Var = {0,0,0,0};

    VariableMap g01VarTableMapping[] = {
      {'X',&xVar},
      {'Y',&yVar},
      {'Z',&zVar},
      {'F',&fVar},
      {NULL,NULL},
    };
    VariableMap g00VarTableMapping[] = {
      {'X',&x1Var},
      {'Y',&y1Var},
      {'Z',&z1Var},
      {NULL,NULL},
    };
    GCodeMapping GCode001[] = {
      {.name = "G",.code = 0,.varMap = g00VarTableMapping,.doOperation = handleG00},
      {.name = "G",.code = 1,.varMap = g01VarTableMapping,.doOperation = handleG01},
      {NULL,NULL,NULL,NULL},
    };

    uint8_t *Buf = "G01X";
    uint8_t *Buf1 = " 10Y40 Z30";
    uint8_t *Buf2 = " F200 \r";
    int a = getcommand(buffer,Buf,strlen(Buf));
    TEST_ASSERT_EQUAL(0,a);
    TEST_ASSERT_EQUAL_ARRAY(buffer,0,Buf);
    a = getcommand(buffer,Buf1,strlen(Buf1));
    TEST_ASSERT_EQUAL(0,a);
    TEST_ASSERT_EQUAL_ARRAY(buffer,strlen(Buf),Buf1);
    a = getcommand(buffer,Buf2,strlen(Buf2));
    TEST_ASSERT_EQUAL(1,a);
    TEST_ASSERT_EQUAL_ARRAY(buffer,strlen(Buf)+strlen(Buf1),Buf2);

    Try{
      cmd = decodeGcode(buffer,GCode001);
      TEST_ASSERT_EQUAL('G',cmd.type);
      TEST_ASSERT_EQUAL(1,cmd.code);
      TEST_ASSERT_EQUAL('X',xVar.name);
      TEST_ASSERT_EQUAL(10,xVar.value);
      TEST_ASSERT_EQUAL('Y',yVar.name);
      TEST_ASSERT_EQUAL(40,yVar.value);
      TEST_ASSERT_EQUAL('Z',zVar.name);
      TEST_ASSERT_EQUAL(30,zVar.value);
      TEST_ASSERT_EQUAL('F',fVar.name);
      TEST_ASSERT_EQUAL(200,fVar.value);
      TEST_ASSERT_EQUAL(16000,xVar.steps);
      TEST_ASSERT_EQUAL(64000,yVar.steps);
      TEST_ASSERT_EQUAL(48000,zVar.steps);
      TEST_ASSERT_EQUAL(0,fVar.steps);
    }Catch(ex){
      dumpException(ex);
    }
    Buf = "G00X15";
    Buf1 = " Y60 Z35\r";
    a = getcommand(buffer1,Buf,strlen(Buf));
    TEST_ASSERT_EQUAL(0,a);
    TEST_ASSERT_EQUAL_ARRAY(buffer1,0,Buf);
    a = getcommand(buffer1,Buf1,strlen(Buf1));
    TEST_ASSERT_EQUAL(1,a);
    TEST_ASSERT_EQUAL_ARRAY(buffer1,strlen(Buf),Buf1);
    Try{
      cmd = decodeGcode(buffer1,GCode001);
      TEST_ASSERT_EQUAL('G',cmd.type);
      TEST_ASSERT_EQUAL(0,cmd.code);
      TEST_ASSERT_EQUAL('X',x1Var.name);
      TEST_ASSERT_EQUAL(15,x1Var.value);
      TEST_ASSERT_EQUAL('Y',y1Var.name);
      TEST_ASSERT_EQUAL(60,y1Var.value);
      TEST_ASSERT_EQUAL('Z',z1Var.name);
      TEST_ASSERT_EQUAL(35,z1Var.value);
      TEST_ASSERT_EQUAL(120,x1Var.steps);
      TEST_ASSERT_EQUAL(480,y1Var.steps);
      TEST_ASSERT_EQUAL(280,z1Var.steps);
    }Catch(ex){
      dumpException(ex);
    }
}

void test_getCMD_with_Long_Buf(void)
{
    char buffer[30] = {0};
    uint8_t *Buf = "G01X10 Y40.56789 Z30 F300\n\r";
    int a = getcommand(buffer,Buf,strlen(Buf));
    TEST_ASSERT_EQUAL(1,a);
    TEST_ASSERT_EQUAL_ARRAY(buffer,0,Buf);

}
