#include<stdint.h>
#include<stddef.h>
#include<Arduino.h>

#define HIGH 1
#define LOW 0
#define OUTPUT 1
#define BPIN1 4
#define BPIN2 5
#define BPIN3 6
#define BPIN4 7

//Propeller Thrust Rate Control
//When each of the 4 propellers velocity is adjusted, it causes a change in direction of the craft
//Using this our primary control means we can adjust the direction of yaw movement

class PropThrustControl {
    public:
        PropThrustControl(){
            pinMode(BPIN1,OUTPUT);
            pinMode(BPIN2,OUTPUT);
            pinMode(BPIN3,OUTPUT);
            pinMode(BPIN4,OUTPUT);
        }
    public:

        void PWM_init(uint8_t Motor,uint8_t vel);

        //Translates 0 - 9 motor PWM values to 0,175 - 255
        uint8_t translate(uint8_t x);

        void thrustWrite(uint8_t Motor,uint8_t speed);

};