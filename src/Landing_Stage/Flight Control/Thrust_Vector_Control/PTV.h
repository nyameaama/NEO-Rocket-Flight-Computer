#ifndef PTV
#define PTV

#include"../../utility/SimpleKalmanFilter.h"
#include"../../Inertial Measurement/IMU.h"

class PredictedThrustVectoring {
    public:
         Gyro vGet;
         SimpleKalmanFilter posEst;
         double DELAYTIME;

    private:
        double Rate_Of_Change_Estimate(uint8_t DOF);

        double getDelayTime();

    public:
        double eq_of_Motion_estimate(uint8_t DOF); 

        double final_pitch_estimate();

        double final_yaw_estimate();

        double computeMotorVector(double x);

};

#endif