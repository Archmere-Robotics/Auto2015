#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Hubs,  S2, HTServo,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,          heartbeat,     tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorB,          leftHook,      tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          rightHook,     tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     wheelB,        tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     wheelA,        tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     collectorMotor, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     liftMotor,     tmotorTetrix, PIDControl, reversed)
#pragma config(Motor,  mtr_S2_C2_1,     wheelD,        tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S2_C2_2,     wheelC,        tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Servo,  srvo_S2_C1_1,    dumpServo,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    doorServo,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#define(USING_resetPos)
#define(USING_getPos)
#define USING_setLiftAuto
#define USING_setLiftTarget
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Autonomous Mode Code Template
//
// This file contains a template for simplified creation of an autonomous program for an TETRIX robot
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of autonomous mode, you may want to perform some initialization on your robot.
// Things that might be performed during initialization include:
//   1. Move motors and servos to a preset position.
//   2. Some sensor types take a short while to reach stable values during which time it is best that
//      robot is not moving. For example, gyro sensor needs a few seconds to obtain the background
//      "bias" value.
//
// In many cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot()
{
  // Place code here to sinitialize servos to starting positions.
  // Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.

  return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the autonomous robot operation. Customize as appropriate for
// your specific robot.
//
// The types of things you might do during the autonomous phase (for the 2008-9 FTC competition)
// are:
//
//   1. Have the robot follow a line on the game field until it reaches one of the puck storage
//      areas.
//   2. Load pucks into the robot from the storage bin.
//   3. Stop the robot and wait for autonomous phase to end.
//
// This simple template does nothing except play a periodic tone every few seconds.
//
// At the end of the autonomous period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{
  initializeRobot();

  //waitForStart();

  setLiftAuto(true);
  leftEncoderCount = 0; // It is good practice to reset encoder values at the start of a program.

  //Calculate total amount of encoder ticks needed by multiplying our factor (194 ticks for 100 inches) by the desired
  //amount of inches, then dividing out the 100. We don't want to calculate this every iteration, so before the loop starts,
  //we write this to the variable 'tickGoal'.
  int tickGoal = (194 * 10) / 100;

  while(leftEncoderCount < tickGoal)
  {
    motor[leftServo] = 20;  // The nice thing about encoders is that we can use any power value we want, and
    motor[rightServo] = 20; // still get the same distance.
  }
  motor[leftServo] = 0; // Stop the loop once the encoders have counted up the correct number of encoder ticks.
  motor[rightServo] = 0;
  while (true)
  {}
}
