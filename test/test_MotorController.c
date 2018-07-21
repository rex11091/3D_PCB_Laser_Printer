#include "unity.h"
#include "MotorController.h"
#include "InfoVerifier.h"

void setUp(void)
{
}

void tearDown(void)
{
}

MotorInfo motorX={.name='X', .delta=0, .deltaRef=0, .error=0, .Dostepping=0, .isReferencing=0, .start=0, .end=0};
MotorInfo motorY={.name='Y', .delta=0, .deltaRef=0, .error=0, .Dostepping=0, .isReferencing=0, .start=0, .end=0};
MotorInfo motorZ={.name='Z', .delta=0, .deltaRef=0, .error=0, .Dostepping=0, .isReferencing=0, .start=0, .end=0};
int y=0;

// printf("%c\n",motorX.name);

/*
motor X is move (1 to 4) delta = 3
motor Y is move (2 to 6) delta = 4  ------> motor z will being reference
motor Z is move (3 to 8) delta = 5

this testing is check all the info is stored correctly into the struct of motorinfo
*/
void test_MotorController_setupMovement_given_coordinate_from_1_2_3_to_4_6_8_expect_storing_all_info_into_motor_info(void)
{
  MotorInfo *MotorInfoTable[] = {
      &motorX,
      &motorY,
      &motorZ,
      NULL,
    };
    int start_point[] = {1,2,3};
    int end_point[] = {4,6,8};
    setupMotorInfo(MotorInfoTable,start_point,end_point);
    TEST_ASSERT_EQUAL_MOTORINFO('Z',5,5,0,0,true,3,8,MotorInfoTable,2);
    TEST_ASSERT_EQUAL_MOTORINFO('Y',4,5,3,0,false,2,6,MotorInfoTable,1);
    TEST_ASSERT_EQUAL_MOTORINFO('X',3,5,1,0,false,1,4,MotorInfoTable,0);
}


/*
 motor X is move (1 to 3) delta = 2 ,err = -2
 motor Y is move (1 to 7) delta = 6 ,err = 0  ------> motor Y stepping
 motor Z is move (1 to 2) delta = 1 ,err = -4


this testing is check if the motor is being reference then the stepping will be 1(the motor is stepping)
*/
void test_MotorMovement_either_stepping_or_not_given_motorY_is_longest_is_being_referencing_expect_motorXisStepping(void)
{
  motorX=(MotorInfo){.name='X', .delta=2, .deltaRef=6, .error=-2, .Dostepping=0, .isReferencing=0, .start=1, .end=3};
  motorY=(MotorInfo){.name='Y', .delta=6, .deltaRef=6, .error=0, .Dostepping=1, .isReferencing=1, .start=1, .end=7};
  motorZ=(MotorInfo){.name='Z', .delta=1, .deltaRef=6, .error=-4, .Dostepping=0, .isReferencing=0, .start=1, .end=2};

   MotorInfo *MotorInfoTable[] = {
      &motorX,
      &motorY,
      &motorZ,
       NULL,
     };
     makeStepbasedOnBrenseham(MotorInfoTable);
     TEST_ASSERT_EQUAL(0,MotorInfoTable[0]->Dostepping); //motor x
     TEST_ASSERT_EQUAL(1,MotorInfoTable[1]->Dostepping); //motor Y
     TEST_ASSERT_EQUAL(0,MotorInfoTable[2]->Dostepping); //motor Z
}
//
//
// /*
// motor X is move (1 to 3) delta = 2 ,err = -2
// motor Y is move (1 to 7) delta = 6 ,err = 0  ------> motor Y stepping
// motor Z is move (1 to 2) delta = 1 ,err = -4
//
// this testing is check if the motor is being reference then the stepping will be 1(the motor is stepping)
// */
// void test_MotorMovement_either_stepping_or_not_given_motorY_is_longest_and_is_being_referencing_expect_motorYisStepping(void)
// {
//   MotorInfo Motorinfo[] = {
//    //name; delta; deltaRef; error; Dostepping; isReferencing; start; end;
//     {'X',2,6,-2,0,0,1,3},
//     {'Y',6,6,0,0,1,1,7},
//     {'Z',1,6,-4,0,0,1,2},
//     };
//     int numberOfMotors = sizeof(Motorinfo) / sizeof(Motorinfo[0]);
//     MotorMovement(Motorinfo,numberOfMotors);
//     TEST_ASSERT_EQUAL(0,Motorinfo[0].Dostepping); //motor X
//     TEST_ASSERT_EQUAL(1,Motorinfo[1].Dostepping); //motor Y
//     TEST_ASSERT_EQUAL(0,Motorinfo[2].Dostepping); //motor Z
// }
//
// /*
// motor X is move (1 to 2) delta = 1  ,err = -6
// motor Y is move (1 to 4) delta = 3  ,err = -2             -----> motor Z stepping
// motor Z is move (1 to 9) delta = 8  ,err = 0
//
// this testing is check if the motor is being reference then the stepping will be 1(the motor is stepping)
// */
// void test_MotorMovement_either_stepping_or_not_given_motorZ_is_longest_and_is_being_referencing_expect_motorZisStepping(void)
// {
//   MotorInfo Motorinfo[] = {
//    //name; delta; deltaRef; error; Dostepping; isReferencing; start; end;
//     {'X',1,8,-6,0,0,1,2},
//     {'Y',3,8,-2,0,0,1,4},
//     {'Z',8,8,0,0,1,1,9},
//     };
//     int numberOfMotors = sizeof(Motorinfo) / sizeof(Motorinfo[0]);
//     MotorMovement(Motorinfo,numberOfMotors);
//     TEST_ASSERT_EQUAL(0,Motorinfo[0].Dostepping); //motor X
//     TEST_ASSERT_EQUAL(0,Motorinfo[1].Dostepping); //motor Y
//     TEST_ASSERT_EQUAL(1,Motorinfo[2].Dostepping); //motor Z
// }
// /*
// motor X is move (2 to 8) delta = 6 ,err =0
// motor Y is move (1 to 4) delta = 3 ,err =0      ------> motor X and Y is stepping
// motor Z is move (1 to 3) delta = 2 ,err =-2
//
// this testing is check if the motor is being reference then the stepping will be 1(the motor is stepping)
// */
// void test_MotorMovement_either_stepping_or_not_given_motorX_is_longest_motorY_is_referencing_motorX_expect_both_Motor_stepping(void)
// {
//   MotorInfo Motorinfo[] = {
//    //name; delta; deltaRef; error; Dostepping; isReferencing; start; end;
//     {'X',6,6,0,0,1,2,8},
//     {'Y',3,6,0,0,0,1,4},
//     {'Z',2,6,-2,0,0,1,3},
//     };
//     int numberOfMotors = sizeof(Motorinfo) / sizeof(Motorinfo[0]);
//     MotorMovement(Motorinfo,numberOfMotors);
//     TEST_ASSERT_EQUAL(1,Motorinfo[0].Dostepping); //motor X
//     TEST_ASSERT_EQUAL(1,Motorinfo[1].Dostepping); //motor Y
//     TEST_ASSERT_EQUAL(0,Motorinfo[2].Dostepping); //motor Z
// }
//
// /*
// motor X is move (2 to 8) delta = 6 ,err =0
// motor Y is move (1 to 4) delta = 3 ,err =0      ------> motor Z ,Y, X is stepping
// motor Z is move (1 to 5) delta = 2 ,err =2
//
// this testing is check if the motor is being reference then the stepping will be 1(the motor is stepping)
// */
// void test_MotorMovement_either_stepping_or_not_given_motorX_is_longest_motorYandZ_is_referencing_motorX_expect_three_Motor_stepping(void)
// {
//   MotorInfo Motorinfo[] = {
//    //name; delta; deltaRef; error; Dostepping; isReferencing; start; end;
//     {'X',6,6,0,0,1,2,8},
//     {'Y',3,6,0,0,0,1,4},
//     {'Z',4,6,2,0,0,1,5},
//     };
//     int numberOfMotors = sizeof(Motorinfo) / sizeof(Motorinfo[0]);
//     MotorMovement(Motorinfo,numberOfMotors);
//     TEST_ASSERT_EQUAL(1,Motorinfo[0].Dostepping); //motor X
//     TEST_ASSERT_EQUAL(1,Motorinfo[1].Dostepping); //motor Y
//     TEST_ASSERT_EQUAL(1,Motorinfo[2].Dostepping); //motor Z
// }
// /*
// motor X is Move(3 to 8)
// motor X is Move(2 to 6)       ---->step sequence = xyz xy xz xy xyz
// motor X is Move(1 to 4)
// */
// void test_stepping_with_coordinate_given_from_3_2_1_to_8_6_4(void)
// {
//   MotorInfo Motorinfo[] = {
//      //name; delta; deltaRef; error; Dostepping; isReferencing; start; end;
//     {'X',0,0,0,0,0,0,0},
//     {'Y',0,0,0,0,0,0,0},
//     {'Z',0,0,0,0,0,0,0},
//     };
//
//     int start_point[] = {3,2,1};
//     int end_point[] = {8,6,4};
//     int numberOfMotors = sizeof(Motorinfo) / sizeof(Motorinfo[0]);
//
//     //when x =4
//     setupMotorInfo(Motorinfo,start_point,end_point,numberOfMotors);
//     TEST_ASSERT_EQUAL_MOTORINFO('X',5,5,0,0,1,3,8,Motorinfo,0);
//     TEST_ASSERT_EQUAL_MOTORINFO('Y',4,5,3,0,0,2,6,Motorinfo,1);
//     TEST_ASSERT_EQUAL_MOTORINFO('Z',3,5,1,0,0,1,4,Motorinfo,2);
//
//     MotorMovement(Motorinfo,numberOfMotors);
//     TEST_ASSERT_EQUAL_MOTORINFO('X',5,5,0,1,1,4,8,Motorinfo,0);
//     TEST_ASSERT_EQUAL_MOTORINFO('Y',4,5,1,1,0,2,6,Motorinfo,1);
//     TEST_ASSERT_EQUAL_MOTORINFO('Z',3,5,-3,1,0,1,4,Motorinfo,2);
//
//     //when x =5
//     TimerInterruptCheckingStepping(Motorinfo,numberOfMotors);
//     MotorMovement(Motorinfo,numberOfMotors);
//     TEST_ASSERT_EQUAL_MOTORINFO('X',5,5,0,1,1,5,8,Motorinfo,0);
//     TEST_ASSERT_EQUAL_MOTORINFO('Y',4,5,-1,1,0,2,6,Motorinfo,1);
//     TEST_ASSERT_EQUAL_MOTORINFO('Z',3,5,3,0,0,1,4,Motorinfo,2);
//
//
//     //when x =6
//     TimerInterruptCheckingStepping(Motorinfo,numberOfMotors);
//     MotorMovement(Motorinfo,numberOfMotors);
//     TEST_ASSERT_EQUAL_MOTORINFO('X',5,5,0,1,1,6,8,Motorinfo,0);
//     TEST_ASSERT_EQUAL_MOTORINFO('Y',4,5,7,0,0,2,6,Motorinfo,1);
//     TEST_ASSERT_EQUAL_MOTORINFO('Z',3,5,-1,1,0,1,4,Motorinfo,2);
//
//     //when x =7
//     TimerInterruptCheckingStepping(Motorinfo,numberOfMotors);
//     MotorMovement(Motorinfo,numberOfMotors);
//     TEST_ASSERT_EQUAL_MOTORINFO('X',5,5,0,1,1,7,8,Motorinfo,0);
//     TEST_ASSERT_EQUAL_MOTORINFO('Y',4,5,5,1,0,2,6,Motorinfo,1);
//     TEST_ASSERT_EQUAL_MOTORINFO('Z',3,5,5,0,0,1,4,Motorinfo,2);
//
//
//     //when x =8
//     TimerInterruptCheckingStepping(Motorinfo,numberOfMotors);
//     MotorMovement(Motorinfo,numberOfMotors);
//     TEST_ASSERT_EQUAL_MOTORINFO('X',5,5,0,1,1,8,8,Motorinfo,0);
//     TEST_ASSERT_EQUAL_MOTORINFO('Y',4,5,3,1,0,2,6,Motorinfo,1);
//     TEST_ASSERT_EQUAL_MOTORINFO('Z',3,5,1,1,0,1,4,Motorinfo,2);
//
//     //when x =9
//     TimerInterruptCheckingStepping(Motorinfo,numberOfMotors);
//     TEST_ASSERT_EQUAL(0,Motorinfo[2].Dostepping); //motor Z
//     TEST_ASSERT_EQUAL(0,Motorinfo[0].Dostepping); //motor X
//     TEST_ASSERT_EQUAL(0,Motorinfo[1].Dostepping); //motor Y
// }
//
//
// /*
// motor X is Move(1 to 4)
// motor X is Move(2 to 6)       ---->step sequence = xyz yz xz yz xyz
// motor X is Move(3 to 8)
// */
// void test_stepping_with_coordinate_given_from_1_2_3_to_4_6_8(void)
// {
//   MotorInfo Motorinfo[] = {
//      //name; delta; deltaRef; error; Dostepping; isReferencing; start; end;
//     {'X',0,0,0,0,0,0,0},
//     {'Y',0,0,0,0,0,0,0},
//     {'Z',0,0,0,0,0,0,0},
//     };
//
//     int start_point[] = {1,2,3};
//     int end_point[] = {4,6,8};
//     int numberOfMotors = sizeof(Motorinfo) / sizeof(Motorinfo[0]);
//
//     //when x =4
//     setupMotorInfo(Motorinfo,start_point,end_point,numberOfMotors);
//     TEST_ASSERT_EQUAL_MOTORINFO('Z',5,5,0,0,1,3,8,Motorinfo,2);
//     TEST_ASSERT_EQUAL_MOTORINFO('Y',4,5,3,0,0,2,6,Motorinfo,1);
//     TEST_ASSERT_EQUAL_MOTORINFO('X',3,5,1,0,0,1,4,Motorinfo,0);
//
//     MotorMovement(Motorinfo,numberOfMotors);
//     TEST_ASSERT_EQUAL_MOTORINFO('Z',5,5,0,1,1,4,8,Motorinfo,2);
//     TEST_ASSERT_EQUAL_MOTORINFO('Y',4,5,1,1,0,2,6,Motorinfo,1);
//     TEST_ASSERT_EQUAL_MOTORINFO('X',3,5,-3,1,0,1,4,Motorinfo,0);
//
//     //when x =5
//     TimerInterruptCheckingStepping(Motorinfo,numberOfMotors);
//     MotorMovement(Motorinfo,numberOfMotors);
//     TEST_ASSERT_EQUAL_MOTORINFO('Z',5,5,0,1,1,5,8,Motorinfo,2);
//     TEST_ASSERT_EQUAL_MOTORINFO('Y',4,5,-1,1,0,2,6,Motorinfo,1);
//     TEST_ASSERT_EQUAL_MOTORINFO('X',3,5,3,0,0,1,4,Motorinfo,0);
//
//
//     //when x =6
//     TimerInterruptCheckingStepping(Motorinfo,numberOfMotors);
//     MotorMovement(Motorinfo,numberOfMotors);
//     TEST_ASSERT_EQUAL_MOTORINFO('Z',5,5,0,1,1,6,8,Motorinfo,2);
//     TEST_ASSERT_EQUAL_MOTORINFO('Y',4,5,7,0,0,2,6,Motorinfo,1);
//     TEST_ASSERT_EQUAL_MOTORINFO('X',3,5,-1,1,0,1,4,Motorinfo,0);
//
//     //when x =7
//     TimerInterruptCheckingStepping(Motorinfo,numberOfMotors);
//     MotorMovement(Motorinfo,numberOfMotors);
//     TEST_ASSERT_EQUAL_MOTORINFO('Z',5,5,0,1,1,7,8,Motorinfo,2);
//     TEST_ASSERT_EQUAL_MOTORINFO('Y',4,5,5,1,0,2,6,Motorinfo,1);
//     TEST_ASSERT_EQUAL_MOTORINFO('X',3,5,5,0,0,1,4,Motorinfo,0);
//
//
//     //when x =8
//     TimerInterruptCheckingStepping(Motorinfo,numberOfMotors);
//     MotorMovement(Motorinfo,numberOfMotors);
//     TEST_ASSERT_EQUAL_MOTORINFO('Z',5,5,0,1,1,8,8,Motorinfo,2);
//     TEST_ASSERT_EQUAL_MOTORINFO('Y',4,5,3,1,0,2,6,Motorinfo,1);
//     TEST_ASSERT_EQUAL_MOTORINFO('X',3,5,1,1,0,1,4,Motorinfo,0);
//
//     //when x =9
//     TimerInterruptCheckingStepping(Motorinfo,numberOfMotors);
//     TEST_ASSERT_EQUAL(0,Motorinfo[2].Dostepping); //motor Z
//     TEST_ASSERT_EQUAL(0,Motorinfo[0].Dostepping); //motor X
//     TEST_ASSERT_EQUAL(0,Motorinfo[1].Dostepping); //motor Y
// }
