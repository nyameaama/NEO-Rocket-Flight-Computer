#ifndef LANDING_PROGRAM
#define LANDING_PROGRAM

#include"../../Sensors/sensors.h"

//Trigger program to begin firing of motor for propulsive landing sequence

class AutoLand {
    private:
         Sensors comp;
    private:
        //Function to find acceleration of rocket in () time
        double AccelerationInSetTime(double seconds);

        //Function computes time propulsive acceleration will get vehicle to 0m/s
        double calculatePropulsiveAccelerationTime();

        //Function to compensate motor ignition delay to calculation
        double compensateIgnitionDelay(double altitude);

    public:
        //Driver Function
        double propulsionAltitude();        

};

#endif