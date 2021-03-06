#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Hubs,  S2, HTMotor,  HTMotor,  none,     none)
#pragma config(Motor,  motorA,          Input,         tmotorNXT, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     wheelC,        tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     wheelD,        tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S2_C1_1,     wheelB,        tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S2_C1_2,     wheelA,        tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S2_C2_1,     collectorMotor, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_2,     liftMotor,     tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Servo,  srvo_S1_C2_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_3,    rightHook,            tServoStandard)
#pragma config(Servo,  srvo_S1_C2_4,    dumpServo,            tServoStandard)
#pragma config(Servo,  srvo_S1_C2_5,    rightIRServo,         tServoStandard)
#pragma config(Servo,  srvo_S1_C2_6,    leftIRServo,          tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
const TServoIndex toTest = rightIRServo;
task main(){
	nMotorEncoder[Input]=0;
	while(true){
		int pos=nMotorEncoder[Input]/8;
		displayBigTextLine(1,"%4d",pos);
		servo[toTest]=pos;
		servoTarget[toTest]=pos;
		servoChangeRate[toTest]=5;
	}
}
