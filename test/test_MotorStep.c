#include "unity.h"
#include "MotorStep.h"
#include "MotorController.h"
#include "InfoVerifier.h"
#include "step.h"
#include "mock_stm32f1xx.h"
#include "stm32f103xb.h"

void setUp(void)
{
}

void tearDown(void)
{
}
GPIO_TypeDef *GPIOA = {0};

/*
this test only doing do a step of going up and down
H  =HIGH
L  =LOW

X.DoStepping=1                              motor X : H
Y.DoStepping=1     ------------->           motor Y : H
Z.DoStepping=L                              motor Z : H

*/
void test_MockingFunction_Given_only_MotorXandY_is_stepping_expect_MotorXandY_pin_set_to_High(void)
{
MotorInfo motorX=(MotorInfo){.name='X', .delta=0, .deltaRef=0, .error=0, .Dostepping=1, \
                             .isReferencing=ISFALSE, .GPIO =GPIOA, .MotorPin=8};
MotorInfo motorY=(MotorInfo){.name='Y', .delta=0, .deltaRef=0, .error=0, .Dostepping=1,  \
                              .isReferencing=ISFALSE,.GPIO =GPIOA, .MotorPin=9};
MotorInfo motorZ=(MotorInfo){.name='Z', .delta=0, .deltaRef=0, .error=0, .Dostepping=0,  \
                            .isReferencing=ISFALSE, .GPIO =GPIOA, .MotorPin=10};

   MotorInfo *MotorInfoTable[] = {
      &motorX,
      &motorY,
      &motorZ,
       NULL,
     };

     HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,HIGH);
     StepMotor(MotorInfoTable[0]);
     HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,HIGH);
     StepMotor(MotorInfoTable[1]);
     HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,LOW);
     StepMotor(MotorInfoTable[2]);

}

void test_MockingFunction_Given_only_MotorXYZ_is_stepping_expect_call_MOCKING_Function_3times(void)
{
MotorInfo motorX=(MotorInfo){.name='X', .delta=0, .deltaRef=0, .error=0, .Dostepping=1,     \
                             .isReferencing=ISFALSE, .GPIO =GPIOA, .MotorPin=8};
MotorInfo motorY=(MotorInfo){.name='Y', .delta=0, .deltaRef=0, .error=0, .Dostepping=1,     \
                             .isReferencing=ISFALSE, .GPIO =GPIOA, .MotorPin=9};
MotorInfo motorZ=(MotorInfo){.name='Z', .delta=0, .deltaRef=0, .error=0, .Dostepping=1,     \
                             .isReferencing=ISFALSE, .GPIO =GPIOA, .MotorPin=10};

   MotorInfo *MotorInfoTable[] = {
      &motorX,
      &motorY,
      &motorZ,
       NULL,
     };
     HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,HIGH);
     HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,HIGH);
     HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,HIGH);
     SetAllmotorStep(MotorInfoTable);

}


/*
this test only doing do a step of going up and down

STATE at DO_STEPPING                              STATE at DO_DELAY
X.DoStepping=1                      motor X : H                          motor X : HL
Y.DoStepping=1     ------------->   motor Y : H     --------------->     motor Y : HL
Z.DoStepping=L                      motor Z : H                          motor Y : HL



*/
void test_DoMotorStepping_testing_case_changing_expect_writePinOn_Call_thn_WritePinOFF_Call(void)
{
MotorInfo motorX=(MotorInfo){.name='X', .delta=0, .deltaRef=0, .error=-1, .Dostepping=1, \
                             .isReferencing=0, .GPIO =GPIOA, .MotorPin=8};
MotorInfo motorY=(MotorInfo){.name='Y', .delta=0, .deltaRef=0, .error=-1, .Dostepping=1, \
                             .isReferencing=0, .GPIO =GPIOA, .MotorPin=9};
MotorInfo motorZ=(MotorInfo){.name='Z', .delta=0, .deltaRef=0, .error=-1, .Dostepping=1, \
                             .isReferencing=0,  .GPIO =GPIOA, .MotorPin=10};

   MotorInfo *MotorInfoTable[] = {
      &motorX,
      &motorY,
      &motorZ,
       NULL,
     };
     HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,HIGH);
     HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,HIGH);
     HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,HIGH);
     DoMotorStepping(MotorInfoTable);
     TEST_ASSERT_EQUAL_MOTOR_STEP(1,1,1,MotorInfoTable[0]->Dostepping,MotorInfoTable[1]->Dostepping,MotorInfoTable[2]->Dostepping);
     HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
     HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,LOW);
     HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,LOW);
     DoMotorStepping(MotorInfoTable);
     TEST_ASSERT_EQUAL_MOTOR_STEP(0,0,0,MotorInfoTable[0]->Dostepping,MotorInfoTable[1]->Dostepping,MotorInfoTable[2]->Dostepping);

}


/*
motor X is Move(3 to 8)                            HL HL HL HL HL
motor Y is Move(2 to 6)       ----------------->   HL HL LL HL HL
motor Z is Move(1 to 4)                            HL LL HL LL HL
*/
void test_DoMotorStepping_as_above_diagram_expect_stepping_as_above(void)
{
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

    int delta[] = {5,4,3};
    setupMotorInfo(MotorInfoTable,delta);
    TEST_ASSERT_EQUAL_MOTORINFO('X',5,5,0,0,ISTRUE,8,MotorInfoTable,0);
    TEST_ASSERT_EQUAL_MOTORINFO('Y',4,5,3,0,ISFALSE,9,MotorInfoTable,1);
    TEST_ASSERT_EQUAL_MOTORINFO('Z',3,5,1,0,ISFALSE,10,MotorInfoTable,2);

    //when X = 0
    //state DO_STEPPING
    HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
    HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,LOW);
    HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,LOW);
    DoMotorStepping(MotorInfoTable);
    TEST_ASSERT_EQUAL_MOTOR_STEP(0,0,0,MotorInfoTable[0]->Dostepping,MotorInfoTable[1]->Dostepping,MotorInfoTable[2]->Dostepping);
    //when x =1
    //state DO_DELAY
    HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
    HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,LOW);
    HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,LOW);
    DoMotorStepping(MotorInfoTable);
    //state DO_STEPPING
    HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,HIGH);
    HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,HIGH);
    HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,HIGH);
    DoMotorStepping(MotorInfoTable);
    TEST_ASSERT_EQUAL_MOTOR_STEP(1,1,1,MotorInfoTable[0]->Dostepping,MotorInfoTable[1]->Dostepping,MotorInfoTable[2]->Dostepping);


    //when x =2
    //state DO_DELAY
    HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
    HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,LOW);
    HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,LOW);
     DoMotorStepping(MotorInfoTable);
     TEST_ASSERT_EQUAL_MOTOR_STEP(1,1,0,MotorInfoTable[0]->Dostepping,MotorInfoTable[1]->Dostepping,MotorInfoTable[2]->Dostepping);

    //state DO_STEPPING
    HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,HIGH);
    HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,HIGH);
    HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,LOW);
     DoMotorStepping(MotorInfoTable);

     //when X=3
     //state DO_DELAY
     HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
     HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,LOW);
     HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,LOW);
     DoMotorStepping(MotorInfoTable);
     TEST_ASSERT_EQUAL_MOTOR_STEP(1,0,1,MotorInfoTable[0]->Dostepping,MotorInfoTable[1]->Dostepping,MotorInfoTable[2]->Dostepping);
     //state DO_STEPPING
     HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,HIGH);
     HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,LOW);
     HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,HIGH);
     DoMotorStepping(MotorInfoTable);

     //when X=4
     //state DO_DELAY
     HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
     HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,LOW);
     HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,LOW);
     DoMotorStepping(MotorInfoTable);
     TEST_ASSERT_EQUAL_MOTOR_STEP(1,1,0,MotorInfoTable[0]->Dostepping,MotorInfoTable[1]->Dostepping,MotorInfoTable[2]->Dostepping);
     //state DO_STEPPING
     HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,HIGH);
     HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,HIGH);
     HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,LOW);
     DoMotorStepping(MotorInfoTable);

     //when X=5
     //state DO_DELAY
     HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
     HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,LOW);
     HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,LOW);
     DoMotorStepping(MotorInfoTable);
     TEST_ASSERT_EQUAL_MOTOR_STEP(1,1,1,MotorInfoTable[0]->Dostepping,MotorInfoTable[1]->Dostepping,MotorInfoTable[2]->Dostepping);
      //state DO_STEPPING
      HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,HIGH);
      HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,HIGH);
      HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,HIGH);
     DoMotorStepping(MotorInfoTable);

     //when X=6
     //state DO_DELAY
     HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
     HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,LOW);
     HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,LOW);
     //MotorTimer_Expect(STOP);
     HAL_TIM_Base_Stop_IT_Expect(htim2);
     DoMotorStepping(MotorInfoTable);
     TEST_ASSERT_EQUAL_MOTOR_STEP(0,0,0,MotorInfoTable[0]->Dostepping,MotorInfoTable[1]->Dostepping,MotorInfoTable[2]->Dostepping);
     HAL_GPIO_WritePin_Expect(MotorInfoTable[0]->GPIO,MotorInfoTable[0]->MotorPin,LOW);
     HAL_GPIO_WritePin_Expect(MotorInfoTable[1]->GPIO,MotorInfoTable[1]->MotorPin,LOW);
     HAL_GPIO_WritePin_Expect(MotorInfoTable[2]->GPIO,MotorInfoTable[2]->MotorPin,LOW);
     DoMotorStepping(MotorInfoTable);
     start_step=0;
}
