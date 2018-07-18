#include "unity.h"
#include "MotorController.h"
#include "InfoVerifier.h"

void setUp(void)
{
}

void tearDown(void)
{
}


void test_MotorController_setupMovement_given_coordinate_from_1_2_3_to_4_6_8_expect_storing_all_info_into_motor_info(void)
{
  MotorInfo Motorinfo[] = {
     //name; delta; deltaRef; error; Dostepping; isReferencing; start; end;
    {'X',0,0,0,0,0,0,0},
    {'Y',0,0,0,0,0,0,0},
    {'Z',0,0,0,0,0,0,0},
    };

    int start_point[] = {1,2,3};
    int end_point[] = {4,6,8};
    int numberOfMotors = sizeof(Motorinfo) / sizeof(Motorinfo[0]);

    setupMotorInfo(Motorinfo,start_point,end_point,numberOfMotors);
    TEST_ASSERT_EQUAL(3,Motorinfo[0].delta);
    TEST_ASSERT_EQUAL(4,Motorinfo[1].delta);
    TEST_ASSERT_EQUAL(5,Motorinfo[2].delta);
    TEST_ASSERT_EQUAL(0,Motorinfo[0].isReferencing);
    TEST_ASSERT_EQUAL(0,Motorinfo[1].isReferencing);
    TEST_ASSERT_EQUAL(1,Motorinfo[2].isReferencing);
    TEST_ASSERT_EQUAL(5,Motorinfo[0].deltaRef);
    TEST_ASSERT_EQUAL(5,Motorinfo[1].deltaRef);
    TEST_ASSERT_EQUAL(5,Motorinfo[2].deltaRef);
    TEST_ASSERT_EQUAL(1,Motorinfo[0].error);
    TEST_ASSERT_EQUAL(3,Motorinfo[1].error);
    TEST_ASSERT_EQUAL(0,Motorinfo[2].error);
    TEST_ASSERT_EQUAL(1,Motorinfo[0].start);
    TEST_ASSERT_EQUAL(2,Motorinfo[1].start);
    TEST_ASSERT_EQUAL(3,Motorinfo[2].start);
    TEST_ASSERT_EQUAL(4,Motorinfo[0].end);
    TEST_ASSERT_EQUAL(6,Motorinfo[1].end);
    TEST_ASSERT_EQUAL(8,Motorinfo[2].end);
}


void test_MotorMovement_either_stepping_or_not_given_motorX_is_longest_is_being_referencing_expect_stepping(void)
{
  MotorInfo Motorinfo[] = {
   //name; delta; deltaRef; error; Dostepping; isReferencing; start; end;
    {'X',5,5,6,0,1,1,6},
    {'Y',2,5,-1,0,0,1,3},
    {'Z',1,5,-3,0,0,1,2},
    };
    int numberOfMotors = sizeof(Motorinfo) / sizeof(Motorinfo[0]);
    MotorMovement(Motorinfo,numberOfMotors);
    TEST_ASSERT_EQUAL(1,Motorinfo[0].Dostepping); //motor x
    TEST_ASSERT_EQUAL(0,Motorinfo[1].Dostepping); //motor Y
    TEST_ASSERT_EQUAL(0,Motorinfo[2].Dostepping); //motor Z
}

void test_MotorMovement_either_stepping_or_not_given_motorY_is_longest_and_is_being_referencing_expect_stepping(void)
{
  MotorInfo Motorinfo[] = {
   //name; delta; deltaRef; error; Dostepping; isReferencing; start; end;
    {'X',2,6,-2,0,0,1,3},
    {'Y',6,6,0,0,1,1,7},
    {'Z',1,6,-4,0,0,1,2},
    };
    int numberOfMotors = sizeof(Motorinfo) / sizeof(Motorinfo[0]);
    MotorMovement(Motorinfo,numberOfMotors);
    TEST_ASSERT_EQUAL(0,Motorinfo[0].Dostepping); //motor X
    TEST_ASSERT_EQUAL(1,Motorinfo[1].Dostepping); //motor Y
    TEST_ASSERT_EQUAL(0,Motorinfo[2].Dostepping); //motor Z
}
void test_MotorMovement_either_stepping_or_not_given_motorZ_is_longest_and_is_being_referencing_expect_stepping(void)
{
  MotorInfo Motorinfo[] = {
   //name; delta; deltaRef; error; Dostepping; isReferencing; start; end;
    {'X',1,6,-6,0,0,1,2},
    {'Y',3,6,-2,0,0,1,4},
    {'Z',8,6,0,0,1,1,9},
    };
    int numberOfMotors = sizeof(Motorinfo) / sizeof(Motorinfo[0]);
    MotorMovement(Motorinfo,numberOfMotors);
    TEST_ASSERT_EQUAL(0,Motorinfo[0].Dostepping); //motor X
    TEST_ASSERT_EQUAL(0,Motorinfo[1].Dostepping); //motor Y
    TEST_ASSERT_EQUAL(1,Motorinfo[2].Dostepping); //motor Z
}
void test_MotorMovement_either_stepping_or_not_given_motorX_is_longest_motorY_is_referencing_motorX_expect_both_Motor_stepping(void)
{
  MotorInfo Motorinfo[] = {
   //name; delta; deltaRef; error; Dostepping; isReferencing; start; end;
    {'X',6,6,0,0,1,2,8},
    {'Y',3,6,0,0,0,1,4},
    {'Z',2,6,-4,0,0,1,3},
    };
    int numberOfMotors = sizeof(Motorinfo) / sizeof(Motorinfo[0]);
    MotorMovement(Motorinfo,numberOfMotors);
    TEST_ASSERT_EQUAL(1,Motorinfo[0].Dostepping); //motor X
    TEST_ASSERT_EQUAL(1,Motorinfo[1].Dostepping); //motor Y
    TEST_ASSERT_EQUAL(0,Motorinfo[2].Dostepping); //motor Z
}

void test_MotorMovement_either_stepping_or_not_given_motorX_is_longest_motorYandZ_is_referencing_motorX_expect_three_Motor_stepping(void)
{
  MotorInfo Motorinfo[] = {
   //name; delta; deltaRef; error; Dostepping; isReferencing; start; end;
    {'X',6,6,0,0,1,2,8},
    {'Y',3,6,0,0,0,1,4},
    {'Z',4,6,2,0,0,1,5},
    };
    int numberOfMotors = sizeof(Motorinfo) / sizeof(Motorinfo[0]);
    MotorMovement(Motorinfo,numberOfMotors);
    TEST_ASSERT_EQUAL(1,Motorinfo[0].Dostepping); //motor X
    TEST_ASSERT_EQUAL(1,Motorinfo[1].Dostepping); //motor Y
    TEST_ASSERT_EQUAL(1,Motorinfo[2].Dostepping); //motor Z
}

void test_stepping_with_coordinate_given_from_1_2_3_to_4_6_8(void)
{
  MotorInfo Motorinfo[] = {
     //name; delta; deltaRef; error; Dostepping; isReferencing; start; end;
    {'X',0,0,0,0,0,0,0},
    {'Y',0,0,0,0,0,0,0},
    {'Z',0,0,0,0,0,0,0},
    };

    int start_point[] = {3,2,1};
    int end_point[] = {8,6,4};
    int numberOfMotors = sizeof(Motorinfo) / sizeof(Motorinfo[0]);

    //3
    setupMotorInfo(Motorinfo,start_point,end_point,numberOfMotors);
    MotorMovement(Motorinfo,numberOfMotors);
    TEST_ASSERT_EQUAL(1,Motorinfo[0].Dostepping); //motor X
    TEST_ASSERT_EQUAL(1,Motorinfo[1].Dostepping); //motor Y
    TEST_ASSERT_EQUAL(1,Motorinfo[2].Dostepping); //motor Z
    TEST_ASSERT_EQUAL(-3,Motorinfo[2].error); //motor X
    TEST_ASSERT_EQUAL(1,Motorinfo[1].error); //motor y

    //4
    TimerInterruptCheckingStepping(Motorinfo,numberOfMotors);
    MotorMovement(Motorinfo,numberOfMotors);
    TEST_ASSERT_EQUAL(1,Motorinfo[0].Dostepping); //motor X
    TEST_ASSERT_EQUAL(1,Motorinfo[1].Dostepping); //motor Y
    TEST_ASSERT_EQUAL(0,Motorinfo[2].Dostepping); //motor Z
    TEST_ASSERT_EQUAL(3,Motorinfo[2].error); //motor X
    TEST_ASSERT_EQUAL(-1,Motorinfo[1].error); //motor y

    //5
    TimerInterruptCheckingStepping(Motorinfo,numberOfMotors);
    MotorMovement(Motorinfo,numberOfMotors);
    TEST_ASSERT_EQUAL(1,Motorinfo[0].Dostepping); //motor X
    TEST_ASSERT_EQUAL(0,Motorinfo[1].Dostepping); //motor Y
    TEST_ASSERT_EQUAL(1,Motorinfo[2].Dostepping); //motor Z
    TEST_ASSERT_EQUAL(-1,Motorinfo[2].error); //motor X
    TEST_ASSERT_EQUAL(7,Motorinfo[1].error); //motor y

    //6
    TimerInterruptCheckingStepping(Motorinfo,numberOfMotors);
    MotorMovement(Motorinfo,numberOfMotors);
    TEST_ASSERT_EQUAL(1,Motorinfo[0].Dostepping); //motor X
    TEST_ASSERT_EQUAL(1,Motorinfo[1].Dostepping); //motor Y
    TEST_ASSERT_EQUAL(0,Motorinfo[2].Dostepping); //motor Z
    TEST_ASSERT_EQUAL(5,Motorinfo[2].error); //motor X
    TEST_ASSERT_EQUAL(5,Motorinfo[1].error); //motor y

    //7
    TimerInterruptCheckingStepping(Motorinfo,numberOfMotors);
    MotorMovement(Motorinfo,numberOfMotors);
    TEST_ASSERT_EQUAL(1,Motorinfo[0].Dostepping); //motor X
    TEST_ASSERT_EQUAL(1,Motorinfo[1].Dostepping); //motor Y
    TEST_ASSERT_EQUAL(1,Motorinfo[2].Dostepping); //motor Z
    TEST_ASSERT_EQUAL(1,Motorinfo[2].error); //motor X
    TEST_ASSERT_EQUAL(3,Motorinfo[1].error); //motor y

    //8
    TimerInterruptCheckingStepping(Motorinfo,numberOfMotors);
    MotorMovement(Motorinfo,numberOfMotors);
    TEST_ASSERT_EQUAL(0,Motorinfo[0].Dostepping); //motor Z
    TEST_ASSERT_EQUAL(0,Motorinfo[0].Dostepping); //motor X
    TEST_ASSERT_EQUAL(0,Motorinfo[1].Dostepping); //motor Y
}
