#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S3,     Drivetrain,     sensorI2CMuxController)
#pragma config(Motor,  mtr_S3_C1_1,     wheelA,        tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S3_C1_2,     wheelB,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S3_C2_1,     wheelC,        tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S3_C2_2,     wheelD,        tmotorTetrix, openLoop, reversed)
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
  motor[wheelA]=100;
  motor[wheelB]=-100;
  motor[wheelC]=100;
  motor[wheelD]=-100;
  wait1Msec(4560);
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
