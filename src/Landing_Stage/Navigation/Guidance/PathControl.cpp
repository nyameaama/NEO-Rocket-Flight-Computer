#include "PathControl.h"

uint8_t STATE;
uint8_t motor_state;

uint8_t altitudeTotal;

double *final_coordinates = (double*)malloc(2);
double *xF_altitudePoints = (double*)malloc(20);

//Accepts directional values to translate to t-vector range
//y =    0 = pitch     1 = yaw
double PathControl::translate(double x, double y){
	signed int low = -90;
	signed int mid = 90;
	signed int translateY, translateP;
	//Yaw
	if (y == 1){
		if (x < 0){
			translateY = -(low + -(x));
		}
		else if (x > 0){
			translateY = mid + x;
		}
		else{
			translateY = 90;
		}
		return translateY;
	}
	//Pitch
	if (y == 0){
		if (x < 0){
			translateP = -(low + -(x));
		}
		else if (x > 0){
			translateP = mid + x;
		}
		else{
			translateP = 90;
		}
		return translateP;
	}
}

//Function to move thrust vectoring mount to pos
double PathControl::TVC(uint8_t M1pos, uint8_t M2pos){
	Control vec;
	double x;
	PredictedThrustVectoring pvec;
	uint8_t stage = (motor_state == LANDING_STAGE) ? 0 : BOOST_STAGE;
	double tvc = (stage == LANDING_STAGE) ? vec.thrustVector(M1pos,M2pos) : pvec.computeMotorVector(x); // <-- Change pvec function
	return tvc;
}

//Function accepts new pitch value to adjust altittude, sends through PID
//and sends determined value for control method assignment
double PathControl::adjustAltitude(double pitch){
	VectorCompute axis;
	Gyro bet;
	double currentY = bet.AccGyroVals(3);
	//PID tuned pitch value
	double PID_tunedP = axis.transitionPitch(pitch);
	CONTROL_ASSIGNMENT(PID_tunedP,currentY);
	return;
}

//Function to determine which control method to send by using current state
double PathControl::CONTROL_ASSIGNMENT(double p, double y){
	if(STATE == FIN_STATE){
		FinAxisAdjustment cmAssign;
		cmAssign.FIN_ADJUST(p,y);
	}else if(STATE == VECTOR_STATE){
		TVC(p,y);
	}
	return;
}

//Function accepts new yaw value to adjust path/heading, sends through PID
//and sends determined value for control method assignment
double PathControl::adjustPath(double yaw){
	VectorCompute axis;
	Gyro bet;
	double currentP = bet.AccGyroVals(2);
	//PID tuned yaw value
	double PID_tunedY = axis.transitionYaw(yaw);
	CONTROL_ASSIGNMENT(currentP,PID_tunedY);
	return;
}


double *PathControl::pathController(double latC, double longC, double alt, double *xF_pathData[64][2]){
	//double pouint32_ts[32][64] = path_pouint32_ts;
	//Firstly, current loc is compared to generated path pouint32_ts to determine which pouint32_t vehicle
	//is closest to. If current loc has passed some stored path pouint32_ts,those path pouint32_ts are
	//discarded
	double threshold_dist;
	double *currentCoord = (double *)malloc(3);
	currentCoord[0] = latC;
	currentCoord[1] = longC;
	currentCoord[2] = alt;
	//double cPouint32_t = HeadingclosestPouint32_t(currentCoord[0],currentCoord[1],xF_pathData,4);
}

//Path Controller Function for altitude control
double PathControl::altitudeController(){
	//To control vehicle altitude, the altitude guidance function
	//compares the current altitude to the altitude path reference, the
	//closest altitude point reference which is greater than the current altitude
	//is then determined and an adjustion is made
	uint8_t tempIndex;
	double currentAltitude = readings.altimeter();
	double *temp = (double*)malloc(altitudeTotal);
	for(size_t i = 0; i < altitudeTotal;++i){
		double diff = currentAltitude - i;
		if(diff < 0){
			temp[tempIndex] = diff;
			tempIndex++;
		}
	}
	//Find largest negative difference
	double largest = temp[0],index;
	for(size_t i = 0; i < altitudeTotal;++i){
		if(temp[i] > largest){
			largest = temp[i];
			index = i;
		}
	}
	

}

void PathControl::state(uint8_t current_State){
	STATE = current_State;
}

void PathControl::VECTOR_MOUNT_STATE(uint8_t state){
	motor_state = state;
}


uint8_t PathControl::INITIALISE_DEST(double latitude,double longitude){
	final_coordinates[0] = latitude;
	final_coordinates[1] = longitude;
	return;
}
