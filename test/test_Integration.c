#include "unity.h"
#include "CommandCode.h"
#include "MotorController.h"
#include "string.h"
#include "Exception.h"
#include "CExceptionConfig.h"
#include "CException.h"
#include "MotorStep.h"
#include "InfoVerifier.h"
#include "mock_XYZSteps.h"
#include "UserConfig.h"
#include "mock_stm32f1xx.h"

void setUp(void){}
void tearDown(void){}



GPIO_TypeDef *GPIOA = {0};
GPIO_TypeDef *GPIOB = {0};
void test_G00_X100_Expect_Converted_To_Steps_And_Motor_Run_Steps(void)
{
  CEXCEPTION_T ex;
  int xSteps = 800;
  int i;
  int Steps[2]={0,0,0};
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

//Rex part
MotorInfo motorX=(MotorInfo){.name='X', .delta=0, .deltaRef=0, .error=0, .Dostepping=0, \
                             .isReferencing=ISFALSE, .GPIO =GPIOA, .MotorPin=8};
MotorInfo motorY=(MotorInfo){.name='Y', .delta=0, .deltaRef=0, .error=0, .Dostepping=0,  \
                              .isReferencing=ISFALSE,.GPIO =GPIOA, .MotorPin=9};
MotorInfo motorZ=(MotorInfo){.name='Z', .delta=0, .deltaRef=0, .error=0, .Dostepping=0,  \
                            .isReferencing=ISFALSE, .GPIO =GPIOA, .MotorPin=10};

  MotorInfo *MotorInfoTable[] = {
        &motorX,
        &motorY,
        &motorZ,
         NULL,
       };
  Try{
    // SetUpMotorInfo_ExpectAndReturn(NULL,xSteps,1);
    cmd = decodeGcode(line,GCode00);
    for(i=0 ; i<3 ; i++)
    {
      Steps[i] = g00VarTableMapping[i].var->steps;
    }
    setupMotorInfo(MotorInfoTable,Steps);
    TEST_ASSERT_EQUAL_MOTORINFO('X',800,800,0,0,ISTRUE,8,MotorInfoTable,0);
}Catch(ex){
  dumpException(ex);
  }
}


/*
motor X is Move(3 steps)                            ll ll HL ll ll ll ll HL LL LL LL LL HL LL LL
motor Y is Move(9 steps)       ----------------->   HL LL HL LL HL HL LL HL LL HL HL LL HL LL HL
motor Z is Move(15 steps)                           HL HL HL HL HL HL HL HL HL HL HL HL HL HL HL
*/


void test_G01_X100_Y99_Z50_F30_Expect_Converted_To_Steps_And_Motor_Run_Steps(void)
{
  CEXCEPTION_T ex;
  int xSteps = 3;
  int ySteps = 9;
  int zSteps = 15;
  int i;
  int Steps[2]={0,0,0};
  StoreCMD cmd = {0,0};
  Variable xVar = {0,0,0,0};
  Variable yVar = {0,0,0,0};
  Variable zVar = {0,0,0,0};
  Variable fVar = {0,0,0,0};

  VariableMap g00VarTableMapping[] = {
    {'X',&xVar},
    {'Y',&yVar},
    {'Z',&zVar},
    {'F',&fVar},
    {NULL,NULL},
  };

  GCodeMapping GCode00[] = {
    {.name = "G",.code = 1,.varMap = g00VarTableMapping,.doOperation = handleG01},
    {.name = "G",.code = 21,.varMap = NULL,.doOperation = handleG20or21},
    {NULL,NULL,NULL,NULL},
  };
  char *SetUp = "G21";
  char *line = "G01 X1 Z5Y3 f10";

//Rex part
  MotorInfo motorX={.name='X', .delta=0, .deltaRef=0, .error=0, .Dostepping=0, \
                    .isReferencing=ISFALSE,  .GPIO =GPIOA, .MotorPin=8};

  MotorInfo motorY={.name='Y', .delta=0, .deltaRef=0, .error=0, .Dostepping=0, \
                    .isReferencing=ISFALSE,  .GPIO =GPIOA, .MotorPin=9};

  MotorInfo motorZ={.name='Z', .delta=0, .deltaRef=0, .error=0, .Dostepping=0, \
                    .isReferencing=ISFALSE,  .GPIO =GPIOA, .MotorPin=10};

  MotorInfo *MotorInfoTable[] = {
        &motorX,
        &motorY,
        &motorZ,
         NULL,
       };

  Try{
       // SetUpMotorInfo_ExpectAndReturn(NULL,xSteps,1);
       // SetUpMotorInfo_ExpectAndReturn(NULL,ySteps,1);
       // SetUpMotorInfo_ExpectAndReturn(NULL,zSteps,1);
       cmd = decodeGcode(SetUp,GCode00);
       cmd = decodeGcode(line,GCode00);
        for(i=0 ; i<3 ; i++)
        {
             Steps[i] = g00VarTableMapping[i].var->steps;
        }
        setupMotorInfo(MotorInfoTable,Steps);

        TEST_ASSERT_EQUAL_MOTORINFO('X',3,15,-9,0,ISFALSE,8,MotorInfoTable,0);
        TEST_ASSERT_EQUAL_MOTORINFO('Y',9,15,3,0,ISFALSE,9,MotorInfoTable,1);
        TEST_ASSERT_EQUAL_MOTORINFO('Z',15,15,0,0,ISTRUE,10,MotorInfoTable,2);
        //when Z = 0
        //state DO_STEPPING
        HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,LOW);
        //when Z = 1
        //state DO_DELAY
        HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,LOW);
        //state DO_STEPPING
        HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,HIGH);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,HIGH);
        //when Z = 2
        //state DO_DELAY
        HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,LOW);
        //state DO_STEPPING
        HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,HIGH);
        //when Z = 3
        //state DO_DELAY
        HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,LOW);
        //state DO_STEPPING
        HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,HIGH);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,HIGH);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,HIGH);
        //when Z = 4
        //state DO_DELAY
        HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,LOW);
        //state DO_STEPPING
        HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,HIGH);
        //when Z = 5
        //state DO_DELAY
        HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,LOW);
        //state DO_STEPPING
        HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,HIGH);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,HIGH);
        //when Z = 6
        //state DO_DELAY
        HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,LOW);
        //state DO_STEPPING
        HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,HIGH);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,HIGH);
        //when Z = 7
        //state DO_DELAY
        HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,LOW);
        //state DO_STEPPING
        HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,HIGH);
        //when Z = 8
        //state DO_DELAY
        HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,LOW);
        //state DO_STEPPING
        HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,HIGH);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,HIGH);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,HIGH);
        //when Z = 9
        //state DO_DELAY
        HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,LOW);
        //state DO_STEPPING
        HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,HIGH);
        //when Z = 10
        //state DO_DELAY
        HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,LOW);
        //state DO_STEPPING
        HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,HIGH);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,HIGH);
        //when Z = 11
        //state DO_DELAY
        HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,LOW);
        //state DO_STEPPING
        HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,HIGH);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,HIGH);
        //when Z = 12
        //state DO_DELAY
        HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,LOW);
        //state DO_STEPPING
        HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,HIGH);
        //when Z = 13
        //state DO_DELAY
        HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,LOW);
        //state DO_STEPPING
        HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,HIGH);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,HIGH);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,HIGH);
        //when Z = 14
        //state DO_DELAY
        HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,LOW);
        //state DO_STEPPING
        HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,HIGH);
        //when Z = 15
        //state DO_DELAY
        HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,LOW);
        //state DO_STEPPING
        HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,HIGH);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,HIGH);
        //when Z = 16
        //state DO_DELAY
        HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,LOW);
        HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,LOW);
        HAL_TIM_Base_Stop_IT_Expect(htim3);
        checkCommandCompletion(MotorInfoTable,HANDLE_CURRENT_CMD);

       }Catch(ex){
         dumpException(ex);
         }
       }
