#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Hubs,  S2, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S4,     HTSMUX,         sensorI2CCustom)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorB,          sweeper,       tmotorNXT, PIDControl, encoder)
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
#include "ht-drivers\hitechnic-sensormux.h"
const tMUXSensor IRLeft=msensor_S4_1;
const tMUXSensor IRRight=msensor_S4_4;

#define NXT_GOOD 8500//8.5v
#define NXT_OK 8000//8v
#define NXT_LOW 7000//7v
#define EXT_GOOD 13000//11v
#define EXT_OK 12000//10.5v
#define EXT_LOW 10000//10v
task main() {
	while(true) {
		int nbt = nAvgBatteryLevel;
		int ebt = externalBatteryAvg;
		string nxtStat = "BAD";
		if(nbt>NXT_GOOD)
			nxtStat="GOOD";
		else if(nbt>NXT_OK)
			nxtStat="OK";
		else if(nbt>NXT_LOW)
			nxtStat="LOW";
		displayTextLine(2,"NXT %4d %s", nbt, nxtStat);
		string extStat = "BAD";
		if(ebt>EXT_GOOD)
			extStat="GOOD";
		else if(ebt>EXT_OK)
			extStat="OK";
		else if(ebt>EXT_LOW)
			extStat="LOW";
		else if(ebt==-1)
			extStat="OFF";
		displayTextLine(3,"EXT %4d %s", ebt, extStat);
		bool SMUX=HTSMUXreadPowerStatus(HTSMUX);
		displayTextLine(4, "SMUX: %s",SMUX?"ON":"OFF");
	}
}
