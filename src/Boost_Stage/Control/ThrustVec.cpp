#include"ThrustVec.h"

uint8_t currentServo_1_Position;
uint8_t currentServo_2_Position;


ThrustVec::ThrustVec(){
	M1.attach(SERVOPIN1);
	M2.attach(SERVOPIN2);
}

uint8_t ThrustVec::thrustVector(uint8_t M_1, uint8_t M_2){
	//M_1 and M_2 values will be in the range of 0 - 90
	//but servo moves from 0 - 180 so numbers will have to
	//be scaled
	//Vertical Moving Motor
	uint8_t servoLoc[2];
	servoLoc[0] = getHorizontalMotorValue(M_2);
	//Horizontal Moving Motor
	servoLoc[1] = getVerticalMotorValue(M_2);
	MoveMotors(servoLoc[0],servoLoc[1]);
	return;
}

uint8_t ThrustVec::getHorizontalMotorValue(uint8_t M_2){
	//M_2 values will be in the range of 0 - 90
	//but servo moves from 0 - 180 so numbers will have to
	//be scaled
	//Horizontal Moving Motor
	uint8_t M2temp1, M2_reading;
	M2temp1 = M_2 * 180;
	M2_reading = M2temp1 / 90;
	return M2_reading;
}

uint8_t ThrustVec::getVerticalMotorValue(uint8_t M_1){
	//Vertical Moving Motor
	//M_1 values will be in the range of 0 - 90
	//but servo moves from 0 - 180 so numbers will have to
	//be scaled
	uint8_t M1temp1, M1_reading;
	M1temp1 = M_1 * 180;
	M1_reading = M1temp1 / 90;
	return M1_reading;
}

 void ThrustVec::MoveMotors(uint8_t val1,uint8_t val2){
	 uint16_t forecastT;
	 M1.write(val1);
	 delay(forecastT);
	 M2.write(val2);
	 delay(forecastT);
	 //Update current motor position
	 currentServo_1_Position = val1;
	 currentServo_2_Position = val2;
 }

