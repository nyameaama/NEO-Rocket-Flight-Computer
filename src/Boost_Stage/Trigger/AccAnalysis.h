#ifndef ACCELERATION ANALYSIS
#define ACCELERATION ANALYSIS

#include<Arduino.h>
#include"../BSensors/B_Sensors.h"
#include"../Microcontroller_Communication/MC_Data_Parse.h"

#define SAMPLE_SIZE 5

//Acceleration analysis determines whether booster stage thrust has ended in order to begin ejection. This can be found by compiling
//a considerable amount of velocity values to analyze for deccelerating pattern as well as a deccelerating pattern in altitude. 
//Process needs to accurately trigger before apogee to successfully deploy landing stage

class ACC_ANALYSIS {
    private:
        BSensors get;
    private:
        //Function to compile altitude vals with time metadata
        double *getAltVals();

        //Function to compile altitude vals with time metadata
        double *VelVals();

        //Function gets duration between two timestamps
        double timeBetween(double x,double y);

        String waitUntil();

    public:
        //Function to analyse velocity for a decceleration pattern
          boolean analyseVelDecceleration();

        //Function to analyse velocity for a decceleration pattern
          boolean analyseAltDecceleration();

        //Function to trigger ejection of landing stage from boost stage
          boolean ejectStage();

};

#endif