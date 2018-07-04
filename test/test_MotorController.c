#include "unity.h"
#include "MotorController.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_MotorController_setupMovement_given_coordinate(void)
{
    LineInfo newline;
    int point_start[2] = {2,1};
    int point_end[2] = {6,3};
    setupMovement(point_start,point_end,&newline);

    TEST_ASSERT_EQUAL(2,newline.X);
    TEST_ASSERT_EQUAL(1,newline.Y);
    TEST_ASSERT_EQUAL(4,newline.dx);
    TEST_ASSERT_EQUAL(2,newline.dy);
    TEST_ASSERT_EQUAL(0,newline.d);
}

void test_MotorController_moveToNextStep(void)
{
    LineInfo newline;
    int point_start[2] = {2,1};
    int point_end[2] = {4,2};
    setupMovement(point_start,point_end,&newline);
    DrawLine(&newline);

}
