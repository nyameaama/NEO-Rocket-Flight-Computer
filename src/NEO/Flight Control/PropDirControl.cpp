#include"PropDirControl.h"

void PropThrustControl::propeller(uint8_t inputL1,uint8_t inputL2) {
 	//Motor Left (Direction - clockwise)
	digitalWrite(inputL1, HIGH);
	digitalWrite(inputL2, LOW);
}

