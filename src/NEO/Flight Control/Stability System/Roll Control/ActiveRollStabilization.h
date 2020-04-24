#ifndef ActiveRollStabilization
#define ActiveRollStabilization

#include<Servo.h>
#include"../../../Inertial Measurement/IMU.h"
#include"../../../Data Logging/FileSys.h"
#include<Thread.h>
#include<ThreadController.h>

#define MOTOR_PIN_1 0
#define MOTOR_PIN_2 0
#define MOTOR_PIN_3 0

#define NEG_THRESHOLD -179
#define POS_THRESHOLD 179

#define SPIN_STATE false
#define pi 3.14159265358979

//If rocket is spinning counter the direction of movement.

class RollStability {
    private:
        Servo s1,s2,s3;
        boolean POS_ROLL_AXIS = true;
        String SPIN_DIRECTION= "clockwise";
        uint8_t arSize = 1;
        double RPM_HIGH;
        double *RPM_COMP = (double*)malloc(arSize);
        String PID;
        uint8_t CURRENT_SERVO_POSITION;
    private:
        //Function to compile two roll values
        double *compileValues(uint8_t count);

        //Function to update wheter rocket is in negative or positive roll boundaries
        uint8_t updateCurrentRollAxis();

        //Function to determine roll direction
        String determineRollDirection();

        //Function to calculate counter movement for servo motors
        uint8_t computeCounterRoll(uint8_t RPM);

        //Function to update Highest RPM
        double updateHighestRPM();

        //Function to get vehicle roll speed
        double getRollSpeed();

        //Function to get Rotations per minute
        double getRotationPM();

        //Function to move fins accordingly
        void finMovement(double x);

    public:
        //Constructor
        RollStability();

        //Destructor
        ~RollStability();

        //Driver function which takes current roll values
       uint8_t rollStabilize(uint8_t roll); 


};

#endif