#include"../../Sensors/sensors.h"
#include<stdint.h>
#define UNDEFINED 0
#define HORIZONTAL_PITCH_VAL 87
#define HORIZONTAL_ROLL_VAL 0

//Functions to check if roll, pitch and yaw readings are in acceptable range
//Based on flight path, correct calibrated angle will change according to state in path so the standard (roll/pith/yaw) values 
//have to be dynamic

class RPY_CHECK{
    //Check functions return 0 when readings are ideal and a non-zero error margin value when readings are off
	// If function returns negative value there is movement on negative axis(left)
	//If function returns positive value there is movement on the positive axis(right)
    //standardRollval = //0 degrees
    //standardPitchval = //87 degrees
       
    public:
        double roll_range(double roll_val,uint8_t standardRollval);

        double pitch_range(double pitch_val,uint8_t standardPitchval);

        double yaw_range(double yaw_val,uint8_t standardYawVal);
 
        double *timeElapsed();

        double *velChange();

};

//Function to correct craft axis from variances in flight direction
class VectorCompute {
    public:
        int *translate_to_servo(double yawR,double pitchR);

};    
class AreaAnalysis {
	private:
		uint8_t terrain_level = 61; //Meters
    public:	
		//Creates altimeter and ultrasonic sensor readings relationship and determines if craft is in safe alt range after 
		//launch or during landing
		uint8_t closeSurfaceDetection(double senRead,double altRead);

        //Detect launch using acceleration and change in altitude 
		uint8_t launch_detect(uint32_t current_altitude,double elapsed,double vel_change,double acc_change);

        
};      