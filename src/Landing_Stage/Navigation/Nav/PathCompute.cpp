#include "PathCompute.h"

//double kp = 0.5,ki = 0.2,kd = 0.1;
//double error_previous = 0,error_integral = 0;

//Convert 1D array to 2D array
double *PathCompute::arrayConversion1D_2D(double array[64]){
	double temp2[64][64];
	for (size_t i = 0; i < 64; i += 2){
		array[i] = temp2[i][i + 1];
	}
}
//Distance between two pairs of coordinates. Returns Kilometers
//With 6 Decimal places range,we get an gps range accuracy of about 9cm off point
double PathCompute::distance_lat_long(double current_lat, double current_long, double final_lat, double final_long){
	//double current_lat = gps.GPS_LOC(1),current_long = gps.GPS_LOC(2);
	double theta, dist;
	if ((current_lat == final_lat) && (current_long == final_long)){
		return 0;
	}
	else{
		theta = current_long - final_long;
		dist = sin(funcs.deg2rad(current_lat)) * sin(funcs.deg2rad(final_lat)) + cos(funcs.deg2rad(current_lat)) * cos(funcs.deg2rad(final_lat)) * cos(funcs.deg2rad(theta));
		dist = acos(dist);
		dist = funcs.rad2deg(dist);
		dist = dist * 60 * 1.1515;
		dist = dist * 1.609344;
		return (dist);
	}
}

double PathCompute::computeBearing(double current_lat,double current_long,double final_lat,double final_long){
	double temp1,temp2,bearing;
	temp1 = sin(final_long - current_long) * cos(final_lat);
	temp2 = cos(current_lat) * sin(final_lat) -  sin(current_lat) * cos(final_lat) * cos(final_long - current_long);
	 bearing = atan2(temp2, funcs.rad2deg(temp1));
	 return bearing;
}
//Compiled distance is the distance from a point to another point including altitude as well as GPS-coord for a distance estimate
double PathCompute::compiled_distance(double current_lat, double current_long, double current_alt, double final_lat, double final_long, double final_alt){
	//Pythagoras theorem is used to find compiled distance
	//Problem!! = equation assumes current altitude will be the same as final altitiude <-Fixed
	double compiled_dist, temp;
	double base_distance = distance_lat_long(current_lat, current_long, final_lat, final_long);
	double height = final_alt - current_alt;
	temp = pow(base_distance, 2) + pow(height, 2);
	compiled_dist = sqrt(temp);
	return compiled_dist;
}
//Function to determine peak altitude
double PathCompute::peak_altitude(double distance){ //The distance of the flight derived prehand from the flight setup data
	//Peak altitude is directly proportional to distance travelled
	//Minimum distance = 5m == 0.005km && Minimum altitude = 2m == 0.002km
	double minimum_alt_limit = 2, alt_thresh_limit = 5000; //5km
	double minimum_dist_limit = 5, distance_limit = 10000; //10km
	double temp1, temp2;
	temp1 = distance * minimum_alt_limit;
	temp2 = temp1 / minimum_dist_limit;
	return temp2;
}
double *PathCompute::LatLongDist_gen(double latitude, double longitude, double metres){
	double newCOORD[2];
	//Latitude
	double earth_radius = 6378.137;							 //radius of the earth in kilometer
	double m = (1 / ((2 * pi / 360) * earth_radius)) / 1000; //1 meter in degree
	double new_latitude = latitude + (metres * m);
	newCOORD[0] = new_latitude;
	//Longitude
	double new_longitude = longitude + (metres * m) / cos(latitude * (pi / 180));
	newCOORD[1] = new_longitude;
	return newCOORD;
}
//Function to determine Heading closest point
uint8_t PathCompute::HeadingclosestPoint(double FLat, double FLong, double array[64][2], uint32_t HcurrentIndex){
	//Check every distance for points in array and compare to determine smallest
	double smallest_dist = 0;
	uint8_t index, i = HcurrentIndex;
	for (size_t i; i < funcs.TDlength(array); i++){
		if (distance_lat_long(FLat, FLong, array[i][0], array[i][1]) < smallest_dist){
			smallest_dist = distance_lat_long(FLat, FLong, array[i][0], array[i][1]);
			index = i;
		}
	}
	HcurrentIndex = index;
	return index;
}
//Function to determine Altitude closest point
double PathCompute::AltitudeclosestPoint(double current_alt, double array[64], uint8_t AcurrentIndex){
	//Check every distance for points in array and compare to determine smallest
	double smallest_dist = array[0];
	uint8_t index = AcurrentIndex;
	for (size_t i; i < funcs.ODlength(array); i++){
		if (array[i] < 0){
			if (-(array[i] - current_alt) < smallest_dist){
				smallest_dist = (array[i] - current_alt);
				index = i;
			}
		}
		else{
			if ((array[i] - current_alt) < smallest_dist){
				smallest_dist = (array[i] - current_alt);
				index = i;
			}
		}
	}
	AcurrentIndex = index;
	return index;
}
/*double PathCompute::Proportional_integral_derivative(double rocketPos,double setpoint){
	//function to determine the rotation of both the first servo and second servo for thrust vectoring
	//to adjust the course so that the rocket heads towards the straight line and follow that straight line.
	uint8_t dt;
	double error,processVar;
	double derivative,proportional,integral;
	processVar = rocketPos;
	error = setpoint - processVar;
	error_integral += error * dt;
    derivative = (error - error_previous) / dt;
    error_previous = error;
    proportional = kp * error;
    integral = ki * error_integral;
    derivative = kd * derivative;
	auto servoRotation = proportional + integral + derivative;
    return servoRotation;
}*/
//Function to compute deviation angle
double PathCompute::deviationAngle(double latStartingpoint, double longStartingpoint, double latEndpoint, double longEndpoint){
	double deviation_angle, path_line_deviation, temp1, temp2;
	//temp1 = atan2(latEndpoint - latStartingpoint / longEndpoint - longStartingpoint); //<-Fix issue
	temp2;

	return deviation_angle;
}
//Function to compute path line deviation
double PathCompute::pathLineDeviation(double devAngle){
	double temp1, temp2;
	double path_line_deviation;
	temp1 = sin(devAngle);
	//temp2 = distance_lat_long(startingpoint[0],startingpoint[1],endpoint[0],endpoint[1]);
	path_line_deviation = temp1 * temp2;
	return path_line_deviation;
}
//Function to Generate Altitude path
double *PathCompute::generate_alt(double current_alt, double high){
	//Launch Stage
	uint8_t point_count = 0;
	//double tempPath[64];
	double *tempPath = (double *)malloc(64);
	uint8_t tempDiff = high - current_alt;
	if (tempDiff % 2 != 0){
		for (size_t j = current_alt; j < high; j += funcs.divisibleBY(tempDiff)){
			tempPath[point_count] = j;
		}
	}
	for (size_t i = current_alt; i < high; i += 2){
		tempPath[point_count] = i;
	}
	return tempPath;
}
//Helper function for LatLongDist()
double PathCompute::LatLongDist_helper(double current_lat, double current_long, double latlong, double distance){
	//double current_lat = gps.GPS_LOC(1),current_long = gps.GPS_LOC(2);
	if (latlong == 0){
		double *temp1 = LatLongDist_gen(current_lat, current_long, distance);
		return temp1[0];
	}
	else if (latlong == 1){
		double *temp2 = LatLongDist_gen(current_lat, current_long, distance);
		return temp2[1];
	}
	return;
}
//Functions to generate heading path points for launch stage,transfer stage and landing stage
//Function writes path points to a two dimensional array and is coverted to return a one dimensional array
double *PathCompute::generate_path_points(double current_lat, double current_long, double final_lat, double final_long){
	//array - xF_pathData
	//double current_lat = gps.GPS_LOC(1),current_long = gps.GPS_LOC(2);
	double lat_increment, long_increment;
	//Distance between location and final location
	double dist = distance_lat_long(current_lat, current_long, final_lat, final_long); //Returns kilometres
	//Translates from km to m
	uint32_t translateMetric = dist * 1000;
	double tempPoints[translateMetric][2];
	//For every metre create a path point
	for (size_t i = 0; i < translateMetric; i++){
		tempPoints[i][0] = LatLongDist_helper(lat_increment, long_increment, 0, 1.0);
		tempPoints[i][1] = LatLongDist_helper(lat_increment, long_increment, 1, 1.0);
		lat_increment = tempPoints[i][0];
		long_increment = tempPoints[i][1];
	}
	double *conv = funcs.arrayConversion2D_1D(tempPoints);
	return conv;
}
double **PathCompute::generate_path_points_helper(double array[]){
	double **ret;
	//ret =  funcs.arrayConversion1D_2D(array);

}