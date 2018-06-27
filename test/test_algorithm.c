#include "unity.h"
#include "algorithm.h"
#include "mock_motorStep.h"
#include "motorStep.h"
#include "stdio.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_algorithm_step_of_motorXandY(void)
{

  int x[2]={2,8};
  int y[2]={1,4};
  char *MotorResult;
  // motorGroup motorgroup;
  // motorstepX_ExpectAndReturn(motorgroup.X);
  // motorstepY_ExpectAndReturn(motorgroup.Y);
  // motorstepX_ExpectAndReturn(motorgroup.X);
  // motorstepX_ExpectAndReturn(motorgroup.X);
  // motorstepY_ExpectAndReturn(motorgroup.Y);
  // motorstepX_ExpectAndReturn(motorgroup.X);
  // motorstepX_ExpectAndReturn(motorgroup.X);
  // motorstepY_ExpectAndReturn(motorgroup.Y);
  // motorstepX_ExpectAndReturn(motorgroup.X);
  // motorstepX_ExpectAndReturn(motorgroup.X);
  // motorstepY_ExpectAndReturn(motorgroup.Y);
  // motorstepX_ExpectAndReturn(motorgroup.X);
  // motorstepX_ExpectAndReturn(motorgroup.X);
  // motorstepY_ExpectAndReturn(motorgroup.Y);
  // motorstepX_ExpectAndReturn(motorgroup.X);
  // motorstepX_ExpectAndReturn(motorgroup.X);
  // motorstepY_ExpectAndReturn(motorgroup.Y);
  // motorstepX_ExpectAndReturn(motorgroup.X);
  // motorstepX_ExpectAndReturn(motorgroup.X);
  // motorstepY_ExpectAndReturn(motorgroup.Y);
  // motorstepX_ExpectAndReturn(motorgroup.X);

  //motorstepZ_ExpectAndReturn(motorgroup.Z);

  MotorResult= moveHead(x,y);
  printf("%s\n",MotorResult);
}

int fake_getStep(int NumCalls) {
  if(idx++ < dataSize) {
    return *(dataPtr ++);
  } else {
    FAIL_WITH_MESSAGE("Error: Array out of bound. Requested number more than %d", dataSize);
  }
  return 0;
}

void setupArrayOfNumbersForGetStep(char array[], int size) {
  dataPtr = array;
  dataSize = size;
  idx = 0;
  getNumber_StubWithCallback(fake_getNumber);
}

void test_giveMeNumbers_step_of_X_Y_motor(void) {

  int x[2]={2,8};
  int y[2]={1,4};
  char *MotorResult;

  MotorResult= moveHead(x,y);

  char expectedValues[] = {'x','y', 'x', 'x', 'y', 'x','x','y','x'};
  char values[6];

  setupArrayOfNumbersForGetStep(fakeValues, sizeof(fakeValues) / sizeof(char));

  giveMeSteps(values,6);

  TEST_ASSERT_EQUAL_INT8_ARRAY(expectedValues, values, 6);
}
