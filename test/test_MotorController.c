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

MotorPin motorpinZ = {
    'A',					//name
    10,						//age
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
    TEST_ASSERT_EQUAL(1,MotorX.diff);
    TEST_ASSERT_EQUAL(2,MotorX.initial_point);
    TEST_ASSERT_EQUAL(2,MotorX.coordinate[0]);
    TEST_ASSERT_EQUAL(5,MotorX.coordinate[1]);

    TEST_ASSERT_EQUAL(1,MotorY.initial_point);
    TEST_ASSERT_EQUAL(1,MotorY.coordinate[0]);
    TEST_ASSERT_EQUAL(3,MotorY.coordinate[1]);
}

void test_MotorController_testing_interrupt_subrountine(void)
{
  togglemotorpin2_Expect();
  interruptSubRoutine(&motorpinY);
  togglemotorpin1_Expect();
  interruptSubRoutine(&motorpinX);
  togglemotorpin3_Expect();
  interruptSubRoutine(&motorpinZ);
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

void test_MotorController_setupMovement_given_coordinate_from_1_2_to_3_5(void)
{
  MotorInfo MotorX;
  MotorInfo MotorY;
  MotorX.motorPin = motorpinX;
  MotorY.motorPin = motorpinY;
  int point_start[2] = {1,2};
  int point_end[2] = {3,5};
  setupMovement(point_start,point_end,&MotorX,&MotorY);

  togglemotorpin2_Expect();
  togglemotorpin1_Expect();
  togglemotorpin2_Expect();
  togglemotorpin2_Expect();
  togglemotorpin1_Expect();
  MotorMovement(&MotorX,&MotorY);
}

void test_MotorController_setupMovement_given_3_axis(void)
{
  MotorInfo MotorX;
  MotorInfo MotorY;
  MotorInfo MotorZ;
  MotorX.motorPin = motorpinX;
  MotorY.motorPin = motorpinY;
  MotorZ.motorPin = motorpinZ;
  int point_start_XY[2] = {1,2};
  int point_end_XY[2] = {6,3};
  int point_start_XZ[2] = {1,4};
  int point_end_XZ[2] = {6,5};

  // compare X-line and Y-line
  setupMovement(point_start_XY,point_end_XY,&MotorX,&MotorY);
  togglemotorpin1_Expect();
  togglemotorpin1_Expect();
  togglemotorpin1_Expect();
  togglemotorpin2_Expect();
  togglemotorpin1_Expect();
  togglemotorpin1_Expect();
  MotorMovement(&MotorX,&MotorY);
  // compare X-line and Z-line
  setupMovement(point_start_XZ,point_end_XZ,&MotorX,&MotorZ);
  togglemotorpin1_Expect();
  togglemotorpin1_Expect();
  togglemotorpin1_Expect();
  togglemotorpin3_Expect();
  togglemotorpin1_Expect();
  togglemotorpin1_Expect();
  MotorMovement(&MotorX,&MotorZ);
}

void test_MotorController_setupMovement_given_3_axis_after_exchange_1times(void)
{
  MotorInfo MotorX;
  MotorInfo MotorY;
  MotorInfo MotorZ;
  MotorX.motorPin = motorpinX;
  MotorY.motorPin = motorpinY;
  MotorZ.motorPin = motorpinZ;
  int point_start_XY[2] = {2,1};
  int point_end_XY[2] = {3,6};
  int point_start_YZ[2] = {1,4};
  int point_end_YZ[2] = {6,5};

  // compare X-line and Y-line
  setupMovement(point_start_XY,point_end_XY,&MotorX,&MotorY);
  togglemotorpin2_Expect();
  togglemotorpin2_Expect();
  togglemotorpin2_Expect();
  togglemotorpin1_Expect();
  togglemotorpin2_Expect();
  togglemotorpin2_Expect();
  MotorMovement(&MotorX,&MotorY);
  // compare Y-line and Z-line
  setupMovement(point_start_YZ,point_end_YZ,&MotorY,&MotorZ);
  togglemotorpin2_Expect();
  togglemotorpin2_Expect();
  togglemotorpin2_Expect();
  togglemotorpin3_Expect();
  togglemotorpin2_Expect();
  togglemotorpin2_Expect();
  MotorMovement(&MotorY,&MotorZ);
}
