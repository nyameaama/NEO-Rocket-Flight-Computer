#include"AxisAdjustment.h"

FinAxisAdjustment::FinAxisAdjustment(){
    //Constructor attaches servo motors to appropriate pins 
    sF1.attach(MOTOR_PIN_1);
    sF2.attach(MOTOR_PIN_2);
    sF3.attach(MOTOR_PIN_3);
    sF4.attach(MOTOR_PIN_4);
}

//Function to scale reading between range (0,180)
double  FinAxisAdjustment::RANGE_TRANSLATE(double x){
    double temp1, translated_reading;
	temp1 = x * 180;
	translated_reading = temp1 / 90;
	return translated_reading;
}

