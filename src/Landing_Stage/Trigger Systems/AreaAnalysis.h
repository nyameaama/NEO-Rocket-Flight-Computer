#ifndef Area
#define Area

#include<Arduino.h>
#include"../Sensors/sensors.h"
#include"../Flight Control/Stability System/AxisStability.h"

class AreaAnalysis {
	private:
		uint8_t terrain_level = 61; //Meters
    public:	
		//Creates altimeter and ultrasonic sensor readings relationship and determines if craft is in safe alt range after 
		//launch or during landing
		uint8_t closeSurfaceDetection(double senRead,double altRead);

        //Detect launch using acceleration and change in altitude 
		uint8_t launch_detect(uint32_t current_altitude,double elapsed,double vel_change,double acc_change);

        //Detect Apogee using negative change in altitude
		boolean detectApogee();
};   

#endif