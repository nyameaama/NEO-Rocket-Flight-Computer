#include<Servo.h>
#include"../../../Inertial Measurement/IMU.h"

#define MOTOR_PIN_1 0
#define MOTOR_PIN_2 0
#define MOTOR_PIN_3 0

#define NEG_THRESHOLD -179
#define POS_THRESHOLD 179

#define SPIN_STATE false

//If rocket is spinning counter the direction of movement.

class RollStability {
    private:
        Servo s1,s2,s3;
        boolean POS_ROLL_AXIS = true;
        String SPIN_DIRECTION= "clockwise";
    private:
        //Function to compile two roll values
        double *compileValues(uint8_t count);

        //Function to update wheter rocket is in negative or positive roll boundaries
        uint8_t updateCurrentRollAxis();

        //Function to determine roll direction
        String determineRollDirection();

        //Function to calculate counter movement for servo motors
        uint8_t computeCounterRoll(uint8_t x);

    public:
        //Driver function which takes current roll values
       uint8_t rollStabilize(uint8_t roll); 


};