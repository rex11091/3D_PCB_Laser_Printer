#include "unity.h"
#include "MotorController.h"
#include "motorPin.h"
#include "timerinterrupt.h"
#include "mock_togglePin.h"
#include "togglePin.h"

void setUp(void)
{
}

void tearDown(void)
{
}
MotorPin motorpinX = {
  'A',					//name
  8,						//age
  };

MotorPin motorpinY = {
    'A',					//name
    9,						//age
    };


void test_MotorController_setupMovement_given_coordinate_from_2_1_to_6_3(void)
{
    MotorInfo MotorX;
    MotorInfo MotorY;
    int point_start[2] = {2,1};
    int point_end[2] = {5,3};
    setupMovement(point_start,point_end,&MotorX,&MotorY);

    TEST_ASSERT_EQUAL(3,MotorX.delta);
    TEST_ASSERT_EQUAL(2,MotorX.deltaRef);
     TEST_ASSERT_EQUAL(2,MotorX.initial_point);
    TEST_ASSERT_EQUAL(1,MotorX.diff);
    TEST_ASSERT_EQUAL(2,MotorX.coordinate[0]);
    TEST_ASSERT_EQUAL(5,MotorX.coordinate[1]);

    TEST_ASSERT_EQUAL(2,MotorY.delta);
    TEST_ASSERT_EQUAL(3,MotorY.deltaRef);
     TEST_ASSERT_EQUAL(1,MotorY.initial_point);
    TEST_ASSERT_EQUAL(1,MotorY.diff);
    TEST_ASSERT_EQUAL(1,MotorY.coordinate[0]);
    TEST_ASSERT_EQUAL(3,MotorY.coordinate[1]);
}

void test_MotorController_setupMovement_When_deltaRef_greather_than_delta_expect_exchange(void)
{
    MotorInfo MotorX;
    MotorInfo MotorY;
    int point_start[2] = {1,2};
    int point_end[2] = {3,5};
    setupMovement(point_start,point_end,&MotorX,&MotorY);
    CheckEitherChangeOrNoChange(&MotorX,&MotorY);
    TEST_ASSERT_EQUAL(3,MotorX.delta);
    TEST_ASSERT_EQUAL(2,MotorX.deltaRef);
     TEST_ASSERT_EQUAL(2,MotorX.initial_point);
    TEST_ASSERT_EQUAL(1,MotorX.diff);
    TEST_ASSERT_EQUAL(2,MotorX.coordinate[0]);
    TEST_ASSERT_EQUAL(5,MotorX.coordinate[1]);

     TEST_ASSERT_EQUAL(1,MotorY.initial_point);
    TEST_ASSERT_EQUAL(1,MotorY.coordinate[0]);
    TEST_ASSERT_EQUAL(3,MotorY.coordinate[1]);
}


void test_MotorController_Stepping_on_motor_given_more_1_step_than_previous_value_expect_call_toggle_motor1_one_time(void)
{
  MotorInfo MotorX;
  MotorInfo MotorY;
  MotorX.motorPin = motorpinX;
  MotorX.initial_point = 2;
  MotorX.coordinate[0] =1;
  MotorX.coordinate[1] =3;
  togglemotorpin1_Expect();
  MotorToNextStep(&MotorX,&MotorY);
}
void test_MotorController_Stepping_on_motor_given_more_1_step_than_previous_value_expect_call_toggle_motor2_one_time(void)
{
  MotorInfo MotorX;
  MotorInfo MotorY;
  MotorY.motorPin = motorpinY;
  MotorX.coordinate[0] =1;
  MotorX.coordinate[1] =3;
  MotorY.initial_point = 2;
  MotorY.coordinate[0] =1;
  MotorY.coordinate[1] =3;
  togglemotorpin2_Expect();
  MotorToNextStep(&MotorX,&MotorY);
}

void test_MotorController_setupMovement_given_coordinate_from_1_2_to_6_3(void)
{
  MotorInfo MotorX;
  MotorInfo MotorY;
  MotorX.motorPin = motorpinX;
  MotorY.motorPin = motorpinY;
  int point_start[2] = {1,2};
  int point_end[2] = {6,3};
  setupMovement(point_start,point_end,&MotorX,&MotorY);

  togglemotorpin1_Expect();
  togglemotorpin1_Expect();
  togglemotorpin1_Expect();
  togglemotorpin2_Expect();
  togglemotorpin1_Expect();
  togglemotorpin1_Expect();
  MotorMovement(&MotorX,&MotorY);

}
void test_MotorController_setupMovement_given_coordinate_from_2_1_to_3_6(void)
{
  MotorInfo MotorX;
  MotorInfo MotorY;
  MotorX.motorPin = motorpinX;
  MotorY.motorPin = motorpinY;
  int point_start[2] = {2,1};
  int point_end[2] = {3,6};
  setupMovement(point_start,point_end,&MotorX,&MotorY);

  togglemotorpin2_Expect();
  togglemotorpin2_Expect();
  togglemotorpin2_Expect();
  togglemotorpin1_Expect();
  togglemotorpin2_Expect();
  togglemotorpin2_Expect();
  MotorMovement(&MotorX,&MotorY);

}



//
//
// void test_MotorController_DrawLineFunction_for_motor_Stepping_less_than_45degree(void)
// {
//     LineInfo newline;
//     int point_start[2] = {1,2};
//     int point_end[2] = {4,8};
//     setupMovement(point_start,point_end,&newline);
//     DrawLine(&newline);
//
// }
// void test_MotorController_DrawLineFunction_for_motor_Stepping_point_2_3_to_8_6(void)
// {
//     LineInfo newline;
//     int point_start[2] = {2,3};
//     int point_end[2] = {8,6};
//     setupMovement(point_start,point_end,&newline);
//     DrawLine(&newline);
//
// }
//
// void test_MotorController_DrawLineFunction_for_motor_Stepping_more_than_45degree(void)
// {
//     LineInfo newline;
//     int point_start[2] = {1,2};
//     int point_end[2] = {2,4};
//     setupMovement(point_start,point_end,&newline);
//     DrawLine(&newline);
//
// }
