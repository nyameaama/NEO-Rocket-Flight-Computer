#ifndef THRUST_VECTORING
#define THRUST_VECTORING

#include"Thread.h"
#include"ThreadController.h"
#include<Arduino.h>
#include<Servo.h>

class ThrustVec {
    private:
        Servo M1,M2;
        uint8_t M1_reading, M2_reading;
    public:
        uint8_t thrustVector(uint8_t M_1,uint8_t M_2);

        void movProcess(uint8_t M_1,uint8_t M_2);

        void Motor1_Move(uint8_t val);

        void Motor2_Move(uint8_t val);
                
        void multithreadServo(uint8_t x,uint8_t y);

};


#endif