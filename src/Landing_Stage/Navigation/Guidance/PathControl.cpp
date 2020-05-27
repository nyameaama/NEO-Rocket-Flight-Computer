#include "PathControl.h"

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
//Accepts new pitch and yaw heading values and vectors appropriately
double PathControl::adjustHeading(double pitch, double yaw){
	//Calculate Distance of values from the current axis pouint32_t to new axis pouint32_t
	//double stable_axis_pouint32_t[2] = {}; //<— Come back and compensate for Dynamic board orientation
	VectorCompute axis;
	axis.transitionPitch(pitch);
	axis.transitionYaw(yaw);
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
double PathControl::alt_PathController(double cLoc, uint8_t haslaunched){
	if (haslaunched == 1){
		//double cLoc = gps.altimeter();
	}
	else{
		//Do nothing
	}
}