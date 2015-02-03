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

#include "Auto2015.h"

task main()
{
bDisplayDiagnostics=false;
realign();
}
