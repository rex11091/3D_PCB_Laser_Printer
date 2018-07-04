#include "unity.h"
#include "MotorController.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_MotorController_setupMovement_given_coordinate_from_2_1_to_6_3(void)
{
    LineInfo newline;
    int point_start[2] = {2,1};
    int point_end[2] = {6,3};
    setupMovement(point_start,point_end,&newline);

    TEST_ASSERT_EQUAL(2,newline.X);
    TEST_ASSERT_EQUAL(1,newline.Y);
    TEST_ASSERT_EQUAL(0,newline.Z);
    TEST_ASSERT_EQUAL(0.5,newline.m);
    TEST_ASSERT_EQUAL(2,newline.dy);
    TEST_ASSERT_EQUAL(4,newline.dx);
    TEST_ASSERT_EQUAL(0,newline.d);
    TEST_ASSERT_EQUAL(2,newline.StartCoord[0]);
    TEST_ASSERT_EQUAL(1,newline.StartCoord[1]);
    TEST_ASSERT_EQUAL(6,newline.EndCoord[0]);
    TEST_ASSERT_EQUAL(3,newline.EndCoord[1]);
}

void test_MotorController_setupMovement_given_coordinate_from_1_2_to_6_3_expert_exchange(void)
{
    LineInfo newline;
    int point_start[2] = {1,2};
    int point_end[2] = {3,6};
    setupMovement(point_start,point_end,&newline);

    TEST_ASSERT_EQUAL(2,newline.StartCoord[0]);
    TEST_ASSERT_EQUAL(1,newline.StartCoord[1]);
    TEST_ASSERT_EQUAL(6,newline.EndCoord[0]);
    TEST_ASSERT_EQUAL(3,newline.EndCoord[1]);
}


void test_MotorController_DrawLineFunction_for_motor_Stepping_less_than_45degree(void)
{
    LineInfo newline;
    int point_start[2] = {1,2};
    int point_end[2] = {4,8};
    setupMovement(point_start,point_end,&newline);
    DrawLine(&newline);

}
void test_MotorController_DrawLineFunction_for_motor_Stepping_point_2_3_to_8_6(void)
{
    LineInfo newline;
    int point_start[2] = {2,3};
    int point_end[2] = {8,6};
    setupMovement(point_start,point_end,&newline);
    DrawLine(&newline);

}

void test_MotorController_DrawLineFunction_for_motor_Stepping_more_than_45degree(void)
{
    LineInfo newline;
    int point_start[2] = {1,2};
    int point_end[2] = {2,4};
    setupMovement(point_start,point_end,&newline);
    DrawLine(&newline);

}
