#ifndef THRUST_VECTORING
#define THRUST_VECTORING

#include"Thread.h"
#include"ThreadController.h"
#include<Arduino.h>
#include<Servo.h>


#define SERVOPIN1 0
#define SERVOPIN2 0

class ThrustVec {
    private:
        Servo M1,M2;
        uint8_t M1_reading, M2_reading;

    public:
        uint8_t thrustVector(uint8_t M_1,uint8_t M_2);

        ThrustVec();

        uint8_t getHorizontalMotorValue(uint8_t x);

        uint8_t getVerticalMotorValue(uint8_t x);

        void MoveMotors(uint8_t val1,uint8_t val2);

};


#endif