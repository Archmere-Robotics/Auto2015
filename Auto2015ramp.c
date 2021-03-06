#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Hubs,  S2, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S4,     HTSMUX,         sensorI2CCustom)
#pragma config(Motor,  motorA,          sweeperA,       tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          sweeperB,       tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          heartbeat,     tmotorNXT, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     wheelC,        tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     wheelD,        tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S2_C1_1,     wheelB,        tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S2_C1_2,     wheelA,        tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S2_C2_1,     collectorMotor, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_2,     liftMotor,     tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Servo,  srvo_S1_C2_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_3,    rightHook,            tServoStandard)
#pragma config(Servo,  srvo_S1_C2_4,    dumpServo,            tServoStandard)
#pragma config(Servo,  srvo_S1_C2_5,    rightIRServo,         tServoStandard)
#pragma config(Servo,  srvo_S1_C2_6,    leftIRServo,          tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "libAuto.c"
#include "JoystickDriver.c"

//position variables
#define LEFT_DRIVE 6000//distance to drive forward at the beginning of auto
#define MED_GOAL 1500//distance to top of medium goal


void driveForward(int aTicks) {
	int offset = nMotorEncoder[wheelC];
	int speed=0;
	while(nMotorEncoder[wheelC]-offset < aTicks/2) {//ramps up speed for just first half of distance
		if(speed<MAX_SPEED)speed++;
		cDir(-speed,-speed,speed,speed);
		wait1Msec(5);
	}
	while(nMotorEncoder[wheelC]-offset < aTicks) {
		if(speed>MIN_SPEED&&nMotorEncoder[wheelC]-offset> aTicks-SLOW_DOWN)speed--;//if close enough to target to use slow down, will slow
		cDir(-speed,-speed,speed,speed);
		wait1Msec(5);
	}
	cDir(0,0,0,0);
}

void driveBackward(int aTicks) {
	int offset = nMotorEncoder[wheelB];
	int speed=0;
	while(nMotorEncoder[wheelB]-offset < aTicks/2) {//ramps up speed for first half
		if(speed<MAX_SPEED)speed++;
		cDir(speed,speed,-speed,-speed);
		wait1Msec(5);
	}
	while(nMotorEncoder[wheelB]-offset < aTicks) {
		if(speed>MIN_SPEED&&nMotorEncoder[wheelB]-offset>aTicks-SLOW_DOWN)speed--;//if close enough to target to use slow down, will slow
		cDir(speed,speed,-speed,-speed);
		wait1Msec(5);
	}
	cDir(0,0,0,0);
}

void goLeft(int aTicks) {
	int offset = nMotorEncoder[wheelA];
	int speed=0;
	while(nMotorEncoder[wheelA]-offset < aTicks/2) {
		if(speed<MAX_SPEED)speed++;
		cDir(speed,-speed,-speed,speed);
		wait1Msec(5);
	}
	while(nMotorEncoder[wheelA]-offset < aTicks) {
		if(speed>MIN_SPEED&&nMotorEncoder[wheelA]-offset> aTicks-SLOW_DOWN)speed--;
		cDir(speed,-speed,-speed,speed);
		wait1Msec(5);
	}
	cDir(0,0,0,0);
}

void spinRight(int aTicks){
	int offset = nMotorEncoder[wheelA];
	int speed=0;
	while(abs(nMotorEncoder[wheelA]-offset) < aTicks/2) {
		if(speed<MAX_SPEED)speed++;
		cDir(-speed,-speed,-speed,-speed);
		wait1Msec(5);
	}
	while(abs(nMotorEncoder[wheelA]-offset) < aTicks) {
		if(speed>MIN_SPEED&&abs(nMotorEncoder[wheelA]-offset)>aTicks-SLOW_DOWN)speed--;
		cDir(-speed,-speed,-speed,-speed);
		wait1Msec(5);
	}
	cDir(0,0,0,0);
}



void raise(int height){
	int speed = 0;
	while(nMotorEncoder[liftMotor] < height-LIFT_SLOW_DOWN){//speed up and majority of movement
		if(speed<LIFT_SPEED_UP)speed++;
		motor[liftMotor]=speed;
	}
	while(nMotorEncoder[liftMotor] < height){//lift motor not yet at target
		if(speed>5)speed--;
		motor[liftMotor]=speed;
	}
	motor[liftMotor]=LIFT_SPEED_STOP;
	wait1Msec(500);
}

void dump(){
	int temp=servo[dumpServo];
	while(servo[dumpServo]<DUMP_POS){
		servo[dumpServo]=temp;temp++;
		wait1Msec(10);
	}
	wait1Msec(5000);
	servo[dumpServo]=HOLD_POS;
}

void lower(){
	while(nMotorEncoder[liftMotor] > LIFT_BOTTOM){//lift motor not yet at target
		motor[liftMotor]=LIFT_SPEED_DOWN;
	}
	motor[liftMotor]=LIFT_SPEED_STOP;
}

void init(){
	nMotorEncoder[wheelA]=0;nMotorEncoder[wheelB]=0;nMotorEncoder[wheelC]=0;nMotorEncoder[wheelD]=0;nMotorEncoder[liftMotor]=0;
	servoChangeRate[dumpServo]=0.1;
	servo[dumpServo]=HOLD_POS;
	wait1Msec(500);
	//raise(LIFT_BOTTOM);
}

task main() {
	waitForStart();
	init();

	goLeft(LEFT_DRIVE);
	//raise(MED_GOAL);
	//motor[leftHook]=-30;
	//dump();
	//motor[leftHook]=0;
	//lower();
}
