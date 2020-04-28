#ifndef Axis_Stability
#define Axis_Stability

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
        //Compute roll axis position error
        double roll_range(double roll_val,uint8_t standardRollval);

        //Compute pitch axis position error
        double pitch_range(double pitch_val,uint8_t standardPitchval);

        //Compute yaw axis position error
        double yaw_range(double yaw_val,uint8_t standardYawVal);
 
        //Compute time elapsed
        double *timeElapsed();

        //Compute change in velocity
        double *velChange();

};

//Function to correct craft axis from variances in flight direction
class VectorCompute {
    public:
        //Function to translate gyro to servo range
        int *translate_to_servo(double yawR,double pitchR);

};    

#endif