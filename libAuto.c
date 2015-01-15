#include "libHolonomics.c"

#include "ht-drivers\hitechnic-sensormux.h"
#define IRLEFT
#define IRRIGHT
const tMUXSensor IRLeft=msensor_S1_1;
const tMUXSensor IRRight=msensor_S1_2;
#include "cdrivers\IRSeekerLib.h"
#include "JoystickDriver.c"

#define IR_TOLERANCE 25
#define MAX_SPEED 55
#define MIN_SPEED 10//lowest speed still moves
#define SLOW_DOWN 700
#define LIFT_SPEED_STOP 0//speed
#define LIFT_SPEED_UP 30//speed whwhile holding
#define LIFT_SPEED_DOWN -10
#define LIFT_BOTTOM 500
#define LIFT_SLOW_DOWN 100
#define HOLD_POS 172
#define DUMP_POS 148
#define TILT_POS 190

//position variables for all autos
#define FORWARD_DRIVE 3300//distance to drive forward at the beginning of auto
#define RIGHT_ALIGN 1200//distance to ram side of goal
#define RIGHT_REALIGN 350//distance to back up and score
#define HIGH_GOAL 3550

void action(const string s) {
	displayCenteredTextLine(3,s);
}
void driveForward(int aTicks) {
	int offset = nMotorEncoder[wheelC];
	int speed=0;
	bool changeSpeed=true;//increases speed every other update
	while(nMotorEncoder[wheelC]-offset < aTicks/2) {//ramps up speed for just first half of distance
		if(speed<MAX_SPEED&&changeSpeed){
			speed++;
			changeSpeed=false;
		}
		else changeSpeed=true;
		cDir(-speed,-speed,speed,speed);
		wait1Msec(5);
	}
	while(nMotorEncoder[wheelC]-offset < aTicks) {
		if(speed>MIN_SPEED&& nMotorEncoder[wheelC]-offset > aTicks-SLOW_DOWN ) speed--;//if close enough to target to use slow down, will slow
		cDir(-speed,-speed,speed,speed);
		wait1Msec(5);
	}
	cDir(0,0,0,0);
}

void driveBackward(int aTicks) {
	int offset = nMotorEncoder[wheelB];
	int speed=0;
	bool changeSpeed = true;//increases speed every other update
	while(nMotorEncoder[wheelB]-offset < aTicks/2) {//ramps up speed for first half
		if(speed<MAX_SPEED&&changeSpeed){
			speed++
			changeSpeed=false;
		}
		else changeSpeed=true;
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
	bool changeSpeed=true;//only increases speed every other update
	while(nMotorEncoder[wheelA]-offset < aTicks/2) {
		if(speed<MAX_SPEED&&changeSpeed){
			speed++;
			changeSpeed=false;
		}
		else changeSpeed=true;
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

void goRight(int aTicks) {
	int offset = nMotorEncoder[wheelB];
	int speed=0;
	bool changeSpeed=true;
	while(nMotorEncoder[wheelB]-offset < aTicks/2) {
		if(speed<MAX_SPEED&&changeSpeed){
			speed++;
			changeSpeed=false;
		}
		else changeSpeed=true;
		cDir(-speed,speed,speed,-speed);
		wait1Msec(5);
	}
	while(nMotorEncoder[wheelB]-offset < aTicks) {
		if(speed>MIN_SPEED&&nMotorEncoder[wheelB]-offset> aTicks-SLOW_DOWN)speed--;
		cDir(speed,-speed,-speed,speed);
		wait1Msec(5);
	}
	cDir(0,0,0,0);
}

void spinRight(int aTicks){
	int offset = nMotorEncoder[wheelA];
	int speed=0;
	bool changeSpeed=true;
	while(abs(nMotorEncoder[wheelA]-offset) < aTicks/2) {
		if(speed<MAX_SPEED&&changeSpeed){
			speed++;
			changeSpeed=false;
		}
		else changeSpeed=true;
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

void spinLeft(int aTicks){
	int offset = nMotorEncoder[wheelA];
	int speed=0;
	bool changeSpeed=true;
	while(abs(nMotorEncoder[wheelA]-offset) < aTicks/2) {
		if(speed<MAX_SPEED&&changeSpeed){
			speed++;
			changeSpeed=false;
		}
		else changeSpeed=true;
		cDir(speed,speed,speed,speed);
		wait1Msec(5);
	}
	while(abs(nMotorEncoder[wheelA]-offset) < aTicks) {
		if(speed>MIN_SPEED&&abs(nMotorEncoder[wheelA]-offset)>aTicks-SLOW_DOWN)speed--;
		cDir(speed,speed,speed,speed);
		wait1Msec(5);
	}
	cDir(0,0,0,0);
}

void realign() {
	action("Realigning");
	int offset = nMotorEncoder[wheelB];
	int speed=0;
	bool changeSpeed=true;
	while(nMotorEncoder[wheelB]-offset < RIGHT_ALIGN) {
		if(speed<MAX_SPEED&&changeSpeed){
			speed++;
			changeSpeed=false;
		}
		else changeSpeed=true;
		cDir(-speed,speed,speed,-speed);
	}
	cDir(0,0,0,0);
	wait1Msec(100);
	offset = nMotorEncoder[wheelB];
	speed=0;
	changeSpeed=true;
	while(abs(nMotorEncoder[wheelB]-offset) < RIGHT_REALIGN/2) {
		if(speed<25&&changeSpeed){
			speed++;
			changeSpeed=false;
		}
		else changeSpeed=true;
		cDir(speed,-speed,-speed,speed);
		wait1Msec(10);
	}
	while(abs(nMotorEncoder[wheelB]-offset) <RIGHT_REALIGN) {
		if(speed>MIN_SPEED&&abs(nMotorEncoder[wheelA]-offset)>SLOW_DOWN)speed--;
		cDir(speed,-speed,-speed,speed);
		wait1Msec(10);
	}
	cDir(0,0,0,0);
}
int sampleHigh(int sensor,int samples) {
	int max=0;
	for(int i=0;i<samples;i++) {
		udVal();
		max=(max>lacValues[sensor])?max:lacValues[sensor];
		wait1Msec(5);
	}
	return max;
}
int getCenterThingPos() {
	action("Getting Position");
	return 3;
	int answer = 1;
	bool ir1 = sampleHigh(1,10)>IR_TOLERANCE,ir2=sampleHigh(2,10)>IR_TOLERANCE;
	if(ir1&&ir2)
		answer=3;//position 3 if IR beacon directly ahead
	else if(ir1||ir2)
		answer=2;//position 2 if IR beacons to mid left and right (left more detectable)
	displayString(0,"Pos:%d,1:%d,2:%d",answer,lacValues[1],lacValues[2]);
	for(int i=0;i<answer;i++){
		motor[heartbeat]=100;
		wait1Msec(250);
		motor[heartbeat]=0;
		wait1Msec(250);
	}
	return answer;
}

void raise(int height){
	int speed = 0;
	while(nMotorEncoder[liftMotor] < height-LIFT_SLOW_DOWN){//speed up and majority of movement
		if(speed<LIFT_SPEED_UP)
			speed++;
		motor[liftMotor]=speed;
	}
	while(nMotorEncoder[liftMotor] < height){//lift motor not yet at target
		if(speed>5)
			speed--;
		motor[liftMotor]=speed;
	}
	motor[liftMotor]=LIFT_SPEED_STOP;
	wait1Msec(500);
}
void tilt(){
	action("Tilting");
	int temp=servo[dumpServo];
	while(servo[dumpServo]<TILT_POS){
		servo[dumpServo]=temp++;
		wait1Msec(10);
	}
	wait1Msec(500);
}
void dump(){
	action("Dumping");
	int temp=servo[dumpServo];
	while(servo[dumpServo]>DUMP_POS){
		servo[dumpServo]=temp--;
		wait1Msec(10);
	}
	wait1Msec(3000);
	tilt();
}

void lower(){
	while(nMotorEncoder[liftMotor] > LIFT_BOTTOM){//lift motor not yet at target
		motor[liftMotor]=LIFT_SPEED_DOWN;
	}
	motor[liftMotor]=LIFT_SPEED_STOP;
}
