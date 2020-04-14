#include"PropThrustControl.h"

void PropThrustControl::PWM_init(uint8_t Motor,uint8_t vel) {
 	uint8_t newvel = translate(vel);
	thrustWrite(Motor,newvel);
}	 

uint8_t translate(uint8_t x){
	if(x == 0){
		return 0;
	}else{
		uint8_t *vals = (uint8_t *)malloc(8);
		vals[0] = 0;
		for(size_t i = 175;i < 255;i+=15){
			vals[i] = i;
		}
		return vals[x];
	}
}

void thrustWrite(uint8_t Motor,uint8_t speed){
	analogWrite(Motor, speed); 
	delay(10);
}