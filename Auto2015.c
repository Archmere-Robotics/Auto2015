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
#pragma config(Motor,  mtr_S2_C2_1,     wheelC,        tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S2_C2_2,     wheelD,        tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Servo,  srvo_S2_C1_1,    dumpServo,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    doorServo,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
#include "libHolonomics.c"

#define FORWARD_DRIVE 5000//distance to drive forward at the beginning of auto
#define MAX_SPEED 100//

inline void driveForward(int aTicks) {
	int offset = nMotorEncoder[wheelC];
	int speed=0;
	while(nMotorEncoder[wheelC]-offset < aTicks) {
		if(speed<MAX_SPEED)speed++;
		cDir(-speed,-speed,speed,speed);
	}
	cDir(0,0,0,0);
}
int getCenterThingPos() {
	//do stuff
	return 1;
}
void dieHorribly() {
	cDir(100,100,100,0);
}
task main() {
	nMotorEncoder[wheelC]=0;
	driveForward(FORWARD_DRIVE);
	switch(getCenterThingPos()) {
		case 1:
			//do stuff
			break;
		case 2:
			//do stuff
			break;
		case 3:
			//do stuff
			break;
		default:
			dieHorribly();
			break;
	}
}
