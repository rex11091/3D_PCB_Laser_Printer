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

  int x[2]={2,16};
  int y[2]={1,8};

  motorGroup motorgroup;

  motorstepX_ExpectAndReturn(motorgroup.X);
  motorstepY_ExpectAndReturn(motorgroup.Y);
  motorstepX_ExpectAndReturn(motorgroup.X);
  motorstepX_ExpectAndReturn(motorgroup.X);
  motorstepY_ExpectAndReturn(motorgroup.Y);
  motorstepX_ExpectAndReturn(motorgroup.X);
  motorstepX_ExpectAndReturn(motorgroup.X);
  motorstepY_ExpectAndReturn(motorgroup.Y);
  motorstepX_ExpectAndReturn(motorgroup.X);
  motorstepX_ExpectAndReturn(motorgroup.X);
  motorstepY_ExpectAndReturn(motorgroup.Y);
  motorstepX_ExpectAndReturn(motorgroup.X);
  motorstepX_ExpectAndReturn(motorgroup.X);
  motorstepY_ExpectAndReturn(motorgroup.Y);
  motorstepX_ExpectAndReturn(motorgroup.X);
  motorstepX_ExpectAndReturn(motorgroup.X);
  motorstepY_ExpectAndReturn(motorgroup.Y);
  motorstepX_ExpectAndReturn(motorgroup.X);
  motorstepX_ExpectAndReturn(motorgroup.X);
  motorstepY_ExpectAndReturn(motorgroup.Y);
  motorstepX_ExpectAndReturn(motorgroup.X);

  //motorstepZ_ExpectAndReturn(motorgroup.Z);
  moveHead(x,y);
}
