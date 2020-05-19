#ifndef ThrustVectorControl
#define ThrustVectorControl

#include<stdint.h>
#include<stddef.h>
#include<Arduino.h>
#include<Servo.h>
#include<Thread.h>
#include<ThreadController.h>

#define SERVOPIN1 0
#define SERVOPIN2 0

class Control {
 	private:
                Servo M1,M2;
                uint8_t M2_reading,M1_reading;

 	public:
                Control();

                uint8_t thrustVector(uint8_t M_1,uint8_t M_2);

                uint8_t getHorizontalMotorValue(uint8_t x);

                uint8_t getVerticalMotorValue(uint8_t x);

                void MoveMotors(uint8_t val1,uint8_t val2);

};        

#endif