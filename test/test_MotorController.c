#include "unity.h"
#include "MotorController.h"
#include "InfoVerifier.h"

void setUp(void)
{
}

void tearDown(void)
{
}


GPIO_TypeDef *GPIOA = {0};

/*
motor X is move (1 to 4) delta = 3
motor Y is move (2 to 6) delta = 4  ------> motor z will being reference
motor Z is move (3 to 8) delta = 5

this testing is check all the info is stored correctly into the struct of motorinfo
*/


void test_MotorController_setupMovement_given_coordinate_from_1_2_3_to_4_6_8_expect_storing_all_info_into_motor_info(void)
{
  MotorInfo motorX={.name='X', .delta=0, .deltaRef=0, .error=0, .Dostepping=0, \
                    .isReferencing=ISFALSE, .GPIO =GPIOA, .MotorPin=8};

  MotorInfo motorY={.name='Y', .delta=0, .deltaRef=0, .error=0, .Dostepping=0, \
                    .isReferencing=ISFALSE, .GPIO =GPIOA, .MotorPin=9};

  MotorInfo motorZ={.name='Z', .delta=0, .deltaRef=0, .error=0, .Dostepping=0, \
                    .isReferencing=ISFALSE, .GPIO =GPIOA, .MotorPin=10};

  MotorInfo *MotorInfoTable[] = {
      &motorX,
      &motorY,
      &motorZ,
      NULL,
    };
    int delta[] = {5,3,2};
    setupMotorInfo(MotorInfoTable,delta);
    TEST_ASSERT_EQUAL_MOTORINFO('Z',2,5,-1,0,ISFALSE,10,MotorInfoTable,2);
    TEST_ASSERT_EQUAL_MOTORINFO('Y',3,5,1,0,ISFALSE,9,MotorInfoTable,1);
    TEST_ASSERT_EQUAL_MOTORINFO('X',5,5,0,0,ISTRUE,8,MotorInfoTable,0);
}
/*
this testing is checking either the motor is being reference or
not then the stepping will be 1(the motor is stepping)
else run the bresenham algorithm to calculate either want stepping or not.

motor X is move (1 to 3) delta = 2,deltaRef=6 ,err = -2
motor Y is move (1 to 7) delta = 6,deltaRef=6 ,err = 0       ------> motor Y stepping
motor Z is move (1 to 2) delta = 1,deltaRef=6 ,err = -4

*/


void test_makeStepbasedOnBrenseham_either_stepping_or_not_given_motorY_is_longest_is_being_referencing_expect_motorXisStepping(void)
{
  MotorInfo motorX=(MotorInfo){.name='X', .delta=2, .deltaRef=6, .error=-2, .Dostepping=0,       \
                                .isReferencing=ISFALSE, .GPIO =GPIOA, .MotorPin=8};
  MotorInfo motorY=(MotorInfo){.name='Y', .delta=6, .deltaRef=6, .error=0, .Dostepping=0,        \
                                .isReferencing=ISTRUE, .GPIO =GPIOA, .MotorPin=9};
  MotorInfo motorZ=(MotorInfo){.name='Z', .delta=1, .deltaRef=6, .error=-4, .Dostepping=0,       \
                                .isReferencing=ISFALSE, .GPIO =GPIOA, .MotorPin=10};
   MotorInfo *MotorInfoTable[] = {
      &motorX,
      &motorY,
      &motorZ,
       NULL,
     };
     makeStepbasedOnBrenseham(MotorInfoTable);
     TEST_ASSERT_EQUAL_MOTORINFO('X',2,6,2,0,ISFALSE,8,MotorInfoTable,0);
     TEST_ASSERT_EQUAL_MOTORINFO('Y',6,6,0,1,ISTRUE,9,MotorInfoTable,1);
     TEST_ASSERT_EQUAL_MOTORINFO('Z',1,6,-2,0,ISFALSE,10,MotorInfoTable,2);
     start_step=0;
}
void test_clearALLMotorinfoDostepping_expect_all_the_motorinfo_Dostepping_set_to_zero(void)
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
     clearALLMotorinfoDostepping(MotorInfoTable);
     TEST_ASSERT_EQUAL_MOTORINFO('X',0,0,0,0,ISFALSE,8,MotorInfoTable,0);
     TEST_ASSERT_EQUAL_MOTORINFO('Y',0,0,0,0,ISFALSE,9,MotorInfoTable,1);
     TEST_ASSERT_EQUAL_MOTORINFO('Z',0,0,0,0,ISFALSE,10,MotorInfoTable,2);
}
