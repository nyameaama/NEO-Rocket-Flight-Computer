#include"AxisAdjustment.h"

FinAxisAdjustment::FinAxisAdjustment(){
    //Constructor attaches servo motors to appropriate pins 
    sF1.attach(MOTOR_PIN_1);
    sF2.attach(MOTOR_PIN_2);
    sF3.attach(MOTOR_PIN_3);
    sF4.attach(MOTOR_PIN_4);
}

//Function to scale reading between range (0,180)
double FinAxisAdjustment::RANGE_TRANSLATE(double x,uint8_t LB, uint8_t UB){
    //R = (V - M1) * R2 / R1 + M2
    double temp1, translated_reading,R2 = (180 - 0),R1 = UB - LB;
	temp1 = (x - (LB));
	translated_reading = temp1 * (R2 / R1) + 0;
	return translated_reading;
}

uint8_t FinAxisAdjustment::YAW_DIR_MOVEMENT(double x){
    //Yaw movement uses Fin 1 and Fin 3
    uint8_t DELAY_TIME;
    sF1.write(x);
    delay(DELAY_TIME);
    sF3.write(x);
    delay(DELAY_TIME);
    return;
}

uint8_t FinAxisAdjustment::PITCH_DIR_MOVEMENT(double x){
    //Pitch movement uses Fin 2 and Fin 4
    uint8_t DELAY_TIME;
    sF2.write(x);
    delay(DELAY_TIME);
    sF4.write(x);
    delay(DELAY_TIME);
    return;
}

//Driver function
uint8_t FinAxisAdjustment::FIN_ADJUST(double p, double y){
    //Put pitch values in range
    double pTrans = RANGE_TRANSLATE(p,P_LB,P_UB);
    //Put yaw values in range
    double yTrans = RANGE_TRANSLATE(y,Y_LB,Y_UB);
    //Mov
    PITCH_DIR_MOVEMENT(pTrans);
    YAW_DIR_MOVEMENT(yTrans);
    return;
}