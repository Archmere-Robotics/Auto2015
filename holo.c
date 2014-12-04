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
#include "libHolonomics.c"
#ifndef _AUTO2015
#define _AUTO2015
const byte CR = 0x13;					// define CR (carriage return)
const byte LF = 0x10;					// define LF (line feed)
void saveDataToFile(string sMsg) {
	TFileHandle   hFileHandle;			// will keep track of our file
	TFileIOResult nIOResult;				// will store our IO results
	string        sFileName = "encoderData.txt";	// the name of our file
	short           nFileSize = sizeof(sMsg)+32;	// will store our file size. Should be size of string, plus a bit of padding.

	Delete(sFileName,nIOResult);
	OpenWrite(hFileHandle, nIOResult, sFileName, nFileSize);    // open the file for writing (creates the file if it does not exist)
	WriteString(hFileHandle, nIOResult, sMsg);         // write 'sMessageToWrite' to the file
	Close(hFileHandle, nIOResult);
}
task main() {
  //reset encoders
  nMotorEncoder[wheelA]=0;
  nMotorEncoder[wheelC]=0;
  //drive forward
  cDir(-100,-100,100,100);//drive foreward
  wait1Msec(4560);
  return;
  //store encoder values
  int A1= nMotorEncoder[wheelA];
  int C1= nMotorEncoder[wheelC];
  //reset encoders
  nMotorEncoder[wheelA]=0;
  nMotorEncoder[wheelC]=0;
  //drive right  TODO: check positioning
  motor[wheelA]=100;
  motor[wheelB]=-100;
  motor[wheelC]=-100;
  motor[wheelD]=100;
  wait1Msec(700);
  //stop
  motor[wheelA]=0;
  motor[wheelB]=0;
  motor[wheelC]=0;
  motor[wheelD]=0;
  int A2= nMotorEncoder[wheelA];
  int C2= nMotorEncoder[wheelC];
  string output;
  stringFormat(output, "Forward:%c%c\tA: %4d ticks%c%c\tC: %4d ticks%c%cRight:%c%c\tA: %4d ticks%c%c\tC: %4d ticks.",CR,LF,A1,CR,LF,C1,CR,LF,CR,LF,A2,CR,LF,C2);
  saveDataToFile(output);
}
#endif
