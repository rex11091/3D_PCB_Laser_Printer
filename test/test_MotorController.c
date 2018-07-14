#include "unity.h"
#include "MotorController.h"

void setUp(void)
{
}

void tearDown(void)
{
}


void test_MotorController_setupMovement_given_coordinate_from_2_1_to_6_113(void)
{
  MotorInfo Motorinfo[] = {
    {'X',0,0,0,0,0},
    {'Y',0,0,0,0,0},
    {'Z',0,0,0,0,0},
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
    TEST_ASSERT_EQUAL(7,Motorinfo[0].error);
    TEST_ASSERT_EQUAL(6,Motorinfo[1].error);
    TEST_ASSERT_EQUAL(0,Motorinfo[2].error);
}


// void test_MotorController_setupMovement_given_coordinate_from_2_1_to_6_3(void)
// {
//     MotorInfo Motorinfo[4];
//     //Motorinfo[4]=NULL;
//     int start_point[] = {1,2,3};
//     int end_point[] = {4,6,8};
//
//     // sizeArray = sizeof(Motorinfo);
//     setupMotorInfo(Motorinfo,start_point,end_point);
//
//       TEST_ASSERT_EQUAL(3,Motorinfo[0].delta);
//       TEST_ASSERT_EQUAL(4,Motorinfo[1].delta);
//       TEST_ASSERT_EQUAL(5,Motorinfo[2].delta);
// }
