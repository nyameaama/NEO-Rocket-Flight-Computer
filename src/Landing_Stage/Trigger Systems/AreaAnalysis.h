#ifndef Area
#define Area

#include<Arduino.h>
#include"../Sensors/sensors.h"
#include"../Flight Control/Stability System/AxisStability.h"
#include"../Inertial Measurement/IMU.h"

#define SAMPLE_SIZE 5

class AreaAnalysis {
	private:
		uint8_t terrain_level = 61; //Meters
		Sensors get;
	private:
		 //Function to compile altitude vals with time metadata
        double *getAltitudeVals();

        //Function gets duration between two timestamps
        double timeBetweenReadings(double x,double y);

    public:	
		//Creates altimeter and ultrasonic sensor readings relationship and determines if craft is in safe alt range after 
		//launch or during landing
		uint8_t closeSurfaceDetection(double senRead,double altRead);

        //Detect launch using acceleration and change in altitude 
		uint8_t launch_detect(uint32_t current_altitude,double elapsed,double vel_change,double acc_change);

        //Detect Apogee using negative change in altitude
		boolean detectApogee();

		//Function to analyse velocity for a decceleration pattern
        boolean analyseAltDecceleration();

		//Function to check if rocket orientation is within bounds
		boolean checkState();

		//Function to determine time to Apogee
		double time_to_Apogee();
};   

#endif