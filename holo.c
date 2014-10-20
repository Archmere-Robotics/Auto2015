#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Hubs,  S3, HTMotor,  HTMotor,  none,     none)
#pragma config(Hubs,  S4, HTServo,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S1,     HTSMUX,         sensorI2CCustom)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     Drivetrain,     sensorI2CMuxController)
#pragma config(Sensor, S4,     Auxillary,      sensorI2CMuxController)
#pragma config(Motor,  mtr_S3_C1_1,     wheelA,        tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S3_C1_2,     wheelB,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S3_C2_1,     wheelC,        tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S3_C2_2,     wheelD,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S4_C2_1,     winch,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C2_2,     hookLift,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C3_1,     conveyorMotor, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C3_2,     flagLift,      tmotorTetrix, openLoop)
#ifndef _AUTO2015
#define _AUTO2015
task main() {
  //drive forward
  motor[wheelA]=100;
  motor[wheelB]=-100;
  motor[wheelC]=100;
  motor[wheelD]=-100;
  wait1msec(1000);
  //stop
  motor[wheelA]=0;
  motor[wheelB]=0;
  motor[wheelC]=0;
  motor[wheelD]=0;
}
#endif
