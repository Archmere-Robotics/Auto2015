#pragma config(Hubs,  S1, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,          Input,         tmotorNXT, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C1_1,    servo1,               tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main(){
	nMotorEncoder[Input]=0;
	while(true){
		int pos=nMotorEncoder[Input];
		string s;
		stringFormat(s,"Servo:%4d",pos);
		nxtDisplayTextLine(1,s);
		servo[servo1]=pos;
		servoTarget[servo1]=pos;
		servoChangeRate[servo1]=5;
	}
}
