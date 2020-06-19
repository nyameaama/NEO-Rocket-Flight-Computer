#ifndef AXIS_ADJUSTMENT
#define AXIS_ADJUSTMENT

#include<Servo.h>

#define MOTOR_PIN_1 0
#define MOTOR_PIN_2 0
#define MOTOR_PIN_3 0
#define MOTOR_PIN_4 0

// Vehicle moves in direction of fin movement
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
        double RANGE_TRANSLATE(double x);

    public:
        //Constructor
        FinAxisAdjustment();

        //Driver function
        uint8_t FIN_ADJUST(double x, double y);


};


#endif