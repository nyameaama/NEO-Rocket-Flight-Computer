#ifndef PTV
#define PTV

#include"../../utility/SimpleKalmanFilter.h"
#include"../../Inertial Measurement/IMU.h"
#include"../../Sensors/sensors.h"

class PredictedThrustVectoring {
    private:
         Gyro vGet;
         SimpleKalmanFilter posEst;
         double DELAYTIME;

    private:
        double Rate_Of_Change_Estimate(uint8_t DOF);

        double getDelayTime();

        double *getCurrentState();

        double eq_of_Motion_estimate(uint8_t DOF); 

        double final_pitch_estimate();

        double final_yaw_estimate();

        double estimateThrustOutput();

        template <typename T>
        T forceToVel(T force);

    public:
        PredictedThrustVectoring();
        
        double computeMotorVector(double TVC_MOUNT_VALUE);

};

#endif