#ifndef AXIS_ADJUSTMENT
#define AXIS_ADJUSTMENT

#include<Servo.h>
#include<Arduino.h>

#define MOTOR_PIN_1 0
#define MOTOR_PIN_2 0
#define MOTOR_PIN_3 0
#define MOTOR_PIN_4 0

// Vehicle moves in direction of fin movement

//Gyro Bounds
//yaw = (-90 , 90)
//pitch = ()

#define Y_LB -90
#define Y_UB 90
#define P_LB 0
#define P_UB 0

class FinAxisAdjustment {
    private:
        Servo sF1,sF2,sF3,sF4;
    private:
        //Function to scale reading between range (0,180)
        double RANGE_TRANSLATE(double x,uint8_t LB, uint8_t UB);

        uint8_t YAW_DIR_MOVEMENT(double x);

        uint8_t PITCH_DIR_MOVEMENT(double x);

    public:
        //Constructor
        FinAxisAdjustment();

        //Driver function
        uint8_t FIN_ADJUST(double p, double y);


};


#endif