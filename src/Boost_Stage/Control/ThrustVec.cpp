#include"ThrustVec.h"

uint8_t ThrustVec::thrustVector(uint8_t M_1, uint8_t M_2){
	//M_1 and M_2 values will be in the range of 0 - 90
	//but servo moves from 0 - 180 so numbers will have to
	//be scaled
	//Vertical Moving Motor
	uint8_t servoLoc[2];
	uint8_t M1temp1, M1_reading;
	M1temp1 = M_1 * 180;
	M1_reading = M1temp1 / 90;
	servoLoc[0] = M1_reading;
	//Horizontal Moving Motor
	uint8_t M2temp1, M2_reading;
	M2temp1 = M_2 * 180;
	M2_reading = M2temp1 / 90;
	servoLoc[1] = M2_reading;
	//Multithread servo move process
	multithreadServo(servoLoc[0],servoLoc[1]);
}

void ThrustVec::Motor1_Move(uint8_t val){
	M1.write(M1_reading);
}
void ThrustVec::Motor2_Move(uint8_t val){
	M2.write(M2_reading);
}
void ThrustVec::multithreadServo(uint8_t x,uint8_t y){
	//Thread Controller to control Threads		
	ThreadController control = ThreadController();
	//Servo #1 thread
	Thread servo1 = Thread();
	//Servo #2 thread
	Thread servo2 = Thread();
	//Configure Servo #1 thread
	//Interval set to 10ms
	//servo1.onRun(Motor1_Move);
	servo1.setInterval(10);
	//Configure Servo #2 thread
	//Interval set to 10ms
	//servo2.onRun(Motor2_Move);
	servo2.setInterval(10);
	//Add both threads to thread controller
	control.add(&servo1);
	control.add(&servo2);
	//Thread controller will run both threads based on interval
	control.run();
 }