#include "AxisStability.h"

//Functions to check if roll, pitch and yaw readings are in acceptable range
//Based on flight path, correct calibrated angle will change according to state in path so the standard (roll/pith/yaw) values
//have to be dynamic

//Check functions return 0 when readings are ideal and a non-zero error margin value when readings are off
// If function returns negative value there is movement on negative axis(left)
//If function returns positive value there is movement on the positive axis(right)
//standardRollval = //0 degrees
//standardPitchval = //87 degrees

double RPY_CHECK::roll_range(double roll_val, uint8_t standardRollval){
	//Acceptable margin 
	double A_margin = 0.5;
	//Error margin rerurn value
	double readingError = 0;
	//Find if axis value exceeds acceptable margin 
	if (roll_val < (standardRollval - A_margin)){
		readingError = standardRollval - roll_val;
	}
	if (roll_val > (standardRollval + A_margin)){
		readingError = roll_val - standardRollval;
	}
	return readingError;
}

double RPY_CHECK::pitch_range(double pitch_val, uint8_t standardPitchval){
	//Acceptable margin 
	double Acceptable_margin = 5.0;
	//Error margin rerurn value
	double readError = 0;
	//Find if axis value exceeds acceptable margin
	if (pitch_val < (standardPitchval - Acceptable_margin)){
		readError = standardPitchval - pitch_val;
	}
	return readError;
}

double RPY_CHECK::yaw_range(double yaw_val, uint8_t standardYawVal){
	//Acceptable margin 
	double AccMargin = 0.1;
	//Error margin rerurn value
	double readError = 0;
	//Find if axis value exceeds acceptable margin
	if (yaw_val < (standardYawVal - AccMargin)){
		readError = standardYawVal - yaw_val;
	}
	if (yaw_val > (standardYawVal + AccMargin)){
		readError = yaw_val - standardYawVal;
	}
	return readError;
}

double *RPY_CHECK::timeElapsed(){
	//timeElapsed() takes sample readings and measures 
	//the time taken between them. Function returns both readings
	//and time elapsed. Helper function for velChange()
    Sensors sp;
    double time[3];
    double readings[2];
	double startTime,endTime,elapsed;
	startTime = micros();
	for(size_t i = 0; i < 2;i++){
		readings[i] = sp.AirspeedVal();
	}
    time[0] = readings[0];
    time[1] = readings[1];
	endTime = micros();
	elapsed = (endTime - startTime);
    time[2] = elapsed;
    return time;
}

double *RPY_CHECK::velChange(){
	//Function takes sample vel readings and computes acceleration change
    double ret[2];
    double *vel = timeElapsed();
    double vel_change,acc_change;
    vel_change = vel[1] - vel[0];
    ret[0] = vel_change;
	acc_change = vel_change / vel[2];
    ret[1] = acc_change;
    return ret;
}

//Function to correct craft axis from variances in flight direction
int *VectorCompute::translate_to_servo(double yawR, double pitchR){
	//Translate gyro range to support servo range
	int ranges[2];
	int low = -90;
	int mid = 90;
	int translateY, translateP;
	//Yaw
	if (yawR < 0){
		translateY = -(low + -(yawR));
	}
	else if (yawR > 0){
		translateY = mid + yawR;
	}
	else{
		translateY = 90;
	}
	//Pitch
	if (pitchR < 0){
		translateP = -(low + -(pitchR));
	}
	else if (pitchR > 0){
		translateP = mid + pitchR;
	}
	else{
		translateP = 90;
	}
	ranges[0] = translateP;
	ranges[1] = translateY;
	return ranges;
}

//---------EXPERIMENTAL-------------//


