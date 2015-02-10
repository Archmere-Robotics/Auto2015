#include "libHolonomics.c"

#include "ht-drivers\hitechnic-sensormux.h"
#include "ht-drivers\lego-ultrasound.h"
const tMUXSensor UltraLeft = msensor_S4_2;
const tMUXSensor UltraRight = msensor_S4_3;
const tMUXSensor IRLeft=msensor_S4_1;
const tMUXSensor IRRight=msensor_S4_4;
#define IRRIGHT
#define IRLEFT

//#define USING_TOUCH

#include "cdrivers\IRSeekerLib.h"
#include "ht-drivers\lego-touch.h"
#include "JoystickDriver.c"

#define MAX_SPEED 55
#define MIN_SPEED 10//lowest speed that still moves
#define SLOW_DOWN 700
#define LIFT_SPEED_STOP 0//speed
#define LIFT_SPEED_UP 50//speed while holding
#define LIFT_SPEED_DOWN -10//speed at which to go down at
#define LIFT_BOTTOM 500
#define LIFT_SLOW_DOWN 100
//half pipe servo value to really stop balls from falling out while going up (pretty tilted left)
#define TILT_POS 190
//half pipe servo to rest at (tilted left, almost flat)
#define HOLD_POS 172
//half pipe servo to dump balls at (pretty tilted right)
#define DUMP_POS 152

//position variables for all autos
#define FORWARD_DRIVE 3300//distance to drive forward at the beginning of auto
#define RIGHT_ALIGN 500//distance to ram side of goal
#define RIGHT_REALIGN 400//distance to back up and score
#define HIGH_GOAL 3550//height to high hoal
void align();
void action(const string s) {
	scrollText(s);
}
void error(const string s) {
	action(s);
	for(int i=0; i<100; i++){
		playTone(i,10);
		wait1Msec(95);
	}
	wait1Msec(10000);
}
void driveForward(int aTicks) {
	int offset = nMotorEncoder[wheelC];
	int speedCounter = 0;//current speed to move the motor
	const float speedRatio = 0.5;//(1:2) ratio of speed (variable):actual motor speed
	while(nMotorEncoder[wheelC]-offset < aTicks/2) {//ramps up speed for just first half of distance
		if(speedCounter*speedRatio<MAX_SPEED)
			speedCounter++;
		int speed=speedCounter*speedRatio;
		cDir(-speed,-speed,speed,speed);
		wait1Msec(5);
	}
	int speed=speedCounter*speedRatio;
	while(nMotorEncoder[wheelC]-offset < aTicks) {
		if(speed>MIN_SPEED&& nMotorEncoder[wheelC]-offset > aTicks-SLOW_DOWN )
			speed--;//if close enough to target to use slow down, will slow
		cDir(-speed,-speed,speed,speed);
		wait1Msec(5);
	}
	cDir(0,0,0,0);
}

void driveBackward(int aTicks) {
	int offset = nMotorEncoder[wheelB];
	int speedCounter = 0;//current speed to move the motor
	const float speedRatio = 0.5;//(1:2) ratio of speed (variable):actual motor speed
	while(nMotorEncoder[wheelB]-offset < aTicks/2) {//ramps up speed for first half
		if(speedCounter*speedRatio<MAX_SPEED)
			speedCounter++;
		int speed=speedCounter*speedRatio;
		cDir(speed,speed,-speed,-speed);
		wait1Msec(5);
	}
	int speed=speedCounter*speedRatio;
	while(nMotorEncoder[wheelB]-offset < aTicks) {
		if(speed>MIN_SPEED&&nMotorEncoder[wheelB]-offset>aTicks-SLOW_DOWN)
			speed--;//if close enough to target to use slow down, will slow
		cDir(speed,speed,-speed,-speed);
		wait1Msec(5);
	}
	cDir(0,0,0,0);
}

void goLeft(int aTicks) {
	int offset = nMotorEncoder[wheelA];
	int speedCounter = 0;//current speed to move the motor
	const float speedRatio = 0.5;//(1:2) ratio of speed (variable):actual motor speed
	while(nMotorEncoder[wheelA]-offset < aTicks/2) {
		if(speedCounter*speedRatio<MAX_SPEED)
			speedCounter++;
		int speed=speedCounter*speedRatio;
		cDir(speed,-speed,-speed,speed);
		wait1Msec(5);
	}
	int speed=speedCounter*speedRatio;
	while(nMotorEncoder[wheelA]-offset < aTicks) {
		if(speed>MIN_SPEED&&nMotorEncoder[wheelA]-offset> aTicks-SLOW_DOWN)
			speed--;
		cDir(speed,-speed,-speed,speed);
		wait1Msec(5);
	}
	cDir(0,0,0,0);
}
void goRight(int aTicks, int maxSpeed) {
	int offset = nMotorEncoder[wheelB];
	int speedCounter = 0;//current speed to move the motor
	const float speedRatio = 0.5;//(1:2) ratio of speed (variable):actual motor speed
	while(nMotorEncoder[wheelB]-offset < aTicks/2) {
		if(speedCounter*speedRatio<MAX_SPEED)
			speedCounter++;
		int speed=speedCounter*speedRatio;
		cDir(-speed,speed,speed,-speed);
		wait1Msec(5);
	}
	int speed=speedCounter*speedRatio;
	while(nMotorEncoder[wheelB]-offset < aTicks) {
		if(speed>MIN_SPEED&&nMotorEncoder[wheelB]-offset> aTicks-SLOW_DOWN)
			speed--;
		cDir(speed,-speed,-speed,speed);
		wait1Msec(5);
	}
	cDir(0,0,0,0);
}
void goRight(int aTicks) {
	goRight(aTicks, MOTOR_MAX);
}
void spinRight(int aTicks){
	int offset = nMotorEncoder[wheelA];
	int speedCounter = 0;//current speed to move the motor
	const float speedRatio = 0.5;//(1:2) ratio of speed (variable):actual motor speed
	while(abs(nMotorEncoder[wheelA]-offset) < aTicks/2) {
		if(speedCounter*speedRatio<MAX_SPEED)
			speedCounter++;
		int speed=speedCounter*speedRatio;
		cDir(-speed,-speed,-speed,-speed);
		wait1Msec(5);
	}
	int speed=speedCounter*speedRatio;
	while(abs(nMotorEncoder[wheelA]-offset) < aTicks) {
		if(speed>MIN_SPEED&&abs(nMotorEncoder[wheelA]-offset)>aTicks-SLOW_DOWN)speed--;
		cDir(-speed,-speed,-speed,-speed);
		wait1Msec(5);
	}
	cDir(0,0,0,0);
}

void spinLeft(int aTicks){
	int offset = nMotorEncoder[wheelA];
	int speedCounter = 0;//current speed to move the motor
	const float speedRatio = 0.5;//(1:2) ratio of speed (variable):actual motor speed
	while(abs(nMotorEncoder[wheelA]-offset) < aTicks/2) {
		if(speedCounter*speedRatio<MAX_SPEED)
			speedCounter++;
		int speed=speedCounter*speedRatio;
		cDir(speed,speed,speed,speed);
		wait1Msec(5);
	}
	int speed=speedCounter*speedRatio;
	while(abs(nMotorEncoder[wheelA]-offset) < aTicks) {
		if(speed>MIN_SPEED&&abs(nMotorEncoder[wheelA]-offset)>aTicks-SLOW_DOWN)speed--;
		cDir(speed,speed,speed,speed);
		wait1Msec(5);
	}
	cDir(0,0,0,0);
}
#ifdef USING_TOUCH
void realign(){
	action("Realigning with touch");
	int offset = nMotorEncoder[wheelB];
	int speed=0;
	//smash into the goal
	while(nMotorEncoder[wheelB]-offset < RIGHT_ALIGN) {
		if(speed<MAX_SPEED)
			speed++;
		cDir(-speed,speed,speed,-speed);
	}

	speed = 20;
	//check touch sensors
	bool right = TSreadState(TouchRight);
	bool left = TSreadState(TouchLeft);
	string store ="";
	string print = "";
	clearTimer(T1);
	while(time1(T1)<10000&&!(left&&right)){
		right = TSreadState(TouchRight);
		left = TSreadState(TouchLeft);
		if(!left&&!right)
		{
			store = "none";
			cDir(-speed,speed,speed,-speed);
		}
		else if(left&&!right)
		{
			store = "left";
			cDir(-speed,-speed,speed/2,speed/2);
		}
		else if(right&&!left)
		{
			store = "right";
			cDir(speed,speed,-speed/2,-speed/2);
		}
		else store = "got it";
		if(store!=print){
			print = store;
			scrollText(print);
		}
	}
	cDir(0,0,0,0);
	wait1Msec(100);
	offset = nMotorEncoder[wheelB];
	speed=0;
	//move back a bit
	while(abs(nMotorEncoder[wheelB]-offset) < RIGHT_REALIGN/2) {
		if(speed<25){
			speed++;
		}
		cDir(speed,-speed,-speed,speed);
		wait1Msec(20);
	}
	while(abs(nMotorEncoder[wheelB]-offset) <RIGHT_REALIGN) {
		if(speed>MIN_SPEED&&abs(nMotorEncoder[wheelA]-offset)>SLOW_DOWN)speed--;
		cDir(speed,-speed,-speed,speed);
		wait1Msec(10);
	}
	cDir(0,0,0,0);
}
#else
void realign() {
	action("Realigning");
	int offset = nMotorEncoder[wheelB];
	int speed=0;
	//smash into the goal
	while(nMotorEncoder[wheelB]-offset < RIGHT_ALIGN) {
		if(speed<MAX_SPEED)
			speed++;
		cDir(-speed,speed,speed,-speed);
	}

	cDir(0,0,0,0);
	wait1Msec(100);
	offset = nMotorEncoder[wheelB];
	speed=0;
	//move back a bit
	while(abs(nMotorEncoder[wheelB]-offset) < RIGHT_REALIGN/2) {
		if(speed<25){
			speed++;
		}
		cDir(speed,-speed,-speed,speed);
		wait1Msec(20);
	}
	while(abs(nMotorEncoder[wheelB]-offset) <RIGHT_REALIGN) {
		if(speed>MIN_SPEED&&abs(nMotorEncoder[wheelA]-offset)>SLOW_DOWN)speed--;
		cDir(speed,-speed,-speed,speed);
		wait1Msec(10);
	}
	cDir(0,0,0,0);
}
#endif

void raise(int height, bool maybefail){
	int speed=0;
	int notMoved=0;//cycles of the loop that the motor encoder value hasn't changed
	int last=nMotorEncoder[liftMotor];
	while(nMotorEncoder[liftMotor] < height-LIFT_SLOW_DOWN){//speed up and majority of movement
		if(speed<LIFT_SPEED_UP)
			speed++;
		motor[liftMotor]=speed;
		if(speed>10 && last==nMotorEncoder[liftMotor])
			notMoved++;
		else
			notMoved=0;
		if(maybefail && notMoved>500){
			scrollText("Failed to lift (A).");
			break;
		}
		last=nMotorEncoder[liftMotor];
		wait1Msec(1);
	}
	notMoved=0;
	while(nMotorEncoder[liftMotor] < height){//lift motor not yet at target
		if(speed>5)
			speed--;
		motor[liftMotor]=speed;
		if(speed>10 && last==nMotorEncoder[liftMotor])
			notMoved++;
		else
			notMoved=0;
		if(maybefail && notMoved>500){
			scrollText("Failed to lift (A).");
			break;
		}
		last=nMotorEncoder[liftMotor];
		wait1Msec(1);
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
	action("Dumping...");
	align();
	//move a bit closer to goal
	goRight(150, 30);
	//move dump to drop balls

	int temp=servo[dumpServo];
	while(servo[dumpServo]>DUMP_POS){
		servo[dumpServo]=temp--;
		wait1Msec(10);
	}
	wait1Msec(3000);
	tilt();//move dump back
	action(" Done.");
}
void lower(){
	while(nMotorEncoder[liftMotor] > LIFT_BOTTOM){//lift motor not yet at target
		motor[liftMotor]=LIFT_SPEED_DOWN;
	}
	motor[liftMotor]=LIFT_SPEED_STOP;
}
void lowerIR() {
	servo[leftIRServo]=LEFT_IR_DOWN;
	servo[rightIRServo]=RIGHT_IR_DOWN;
	servoTarget[leftIRServo]=LEFT_IR_DOWN;
	servoTarget[rightIRServo]=RIGHT_IR_DOWN;
	servoChangeRate[leftIRServo]=10;
	servoChangeRate[rightIRServo]=10;
}
void raiseIR() {
	servo[leftIRServo]=LEFT_IR_UP;
	servo[rightIRServo]=RIGHT_IR_UP;
	servoTarget[leftIRServo]=LEFT_IR_UP;
	servoTarget[rightIRServo]=RIGHT_IR_UP;
	servoChangeRate[leftIRServo]=10;
	servoChangeRate[rightIRServo]=10;
}
static int sampleHigh(bool right, int sensor, int samples) {
	int max=0;
	for(int i=0;i<samples;i++) {
		udVal();
		int current;
		if(right)
			current=racValues[sensor];
		else
			current=lacValues[sensor];
		if(max<current)
			max=current;
		wait1Msec(5);
	}
	return max;
}
void align() {
	//do stuff
}
int getUCData() {
	int left = USreadDist(UltraLeft);
	int right = USreadDist(UltraRight);
	return 0;//TODO finish
}
int getCenterThingPos() {
	action("Getting Position...");
	int answer = 2;
	if(HTIRS2readACDir(IRLeft)<0)
		return -1;
	if(HTIRS2readACDir(IRRight)<0)
		return -1;
	//int r0 = sampleHigh(true, 0, 10);//right 0
	int r1 = sampleHigh(true, 1, 10);//right 1
	int r2 = sampleHigh(true, 2, 10);//right 2
	int l1 = sampleHigh(false,1, 10);//left 1
	//int l2 = sampleHigh(false,2, 10);//left 2

	if(l1>100)
		answer = 3;
	else if(r1>50||r2>50)
		answer = 1;
	else
		answer = 2;

	scrollText("Position: %d", answer);
	for(int i=0;i<answer;i++){
		motor[heartbeat]=100;
		wait1Msec(250);
		motor[heartbeat]=0;
		wait1Msec(250);
	}
	return answer;
}
