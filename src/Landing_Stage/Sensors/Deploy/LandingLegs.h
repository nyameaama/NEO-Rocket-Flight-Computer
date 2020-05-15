#include<Arduino.h>
#include<Servo.h>
#include"../sensors.h"
#include<stdint.h>
#include<stddef.h>

#define DEPLOYED_POSITION 90 // <-- Adjust position
#define RETRACTED_POSITION 0 // Adjust
#define ECHO_PIN 0
#define TRIG_PIN 0 //<-- Add pin allocations

class LLDeploy{
    private:
        Servo l1,l2,l3,l4;
        Sensors ul;

    public:
        LLDeploy();    

    private:
    //Function to move all servos into deployed position
        uint8_t deploy();

    //Function to move all servos into retracted position    
        uint8_t retract();

        uint8_t* compilePos();

    //Function to verify deployment
        boolean verifyStatus(uint8_t x);

    //Function to flag when craft is in landing conditions
        boolean LLtrigger();

        uint8_t sequentialMove(uint8_t iter);

    public:
        //Landing Leg Controller
        uint8_t LL_controller();


};