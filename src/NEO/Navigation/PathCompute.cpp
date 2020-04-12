#include "PathCompute.h"

//This functions finds the next divisible number
uint16_t PathCompute::divisibleBY(uint32_t x){
	uint8_t flag = 0;
	uint16_t ar[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	for (size_t i : ar){
		if (x % ar[i] == 0){
			flag = i;
		}
	}
	return ar[flag];
}
//This function converts decimal degrees to radians
double PathCompute::deg2rad(double deg){
	return (deg * pi / 180);
}
//This function converts radians to decimal degrees
double PathCompute::rad2deg(double rad){
	return (rad * 180 / pi);
}
//Calculates cosine rule
double PathCompute::cosine_rule(double lengthA, double lengthB, double lengthC){
	double val;
	val = pow(lengthB, 2) + pow(lengthC, 2);
	val = val - pow(lengthA, 2);
	val = val / (2 * lengthB * lengthC);
	val = acos(val) * 180.0 / pi;
	return val;
}
double PathCompute::ang_to_PitchYaw(){
}
//1D array Length Function
uint8_t PathCompute::ODlength(double arr[]){
	uint8_t count;
	for (size_t i = 0; i < arr[i]; i++){
		arr[i];
		count++;
	}
	return count;
}
//2D array Length Function
uint32_t PathCompute::TDlength(double arr[][2]){
	//String str = String(arr);
}
//Convert 2D array to 1D array
double *PathCompute::arrayConversion2D_1D(double array[][2]){
	uint16_t n = 64;
	double a[n][n], b[n * n];
	uint16_t *c = (uint16_t *)malloc(n * n);
	uint16_t i, j, k = 0, l = 0;
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			b[k] = a[i][j];
			k++;
		}
	}
	free(c);
	return b;
}

//Convert 1D array to 2D array
double *PathCompute::arrayConversion1D_2D(double array[64]){
	double temp2[64][64];
	for (size_t i = 0; i < 64; i += 2){
		array[i] = temp2[i][i + 1];
	}
}
//Distance between two pairs of coordinates. Returns Kilometers
//With 6 Decimal places range,we get an gps range accuracy of about 9cm off pouint32_t
double PathCompute::distance_lat_long(double current_lat, double current_long, double final_lat, double final_long){
	//double current_lat = gps.GPS_LOC(1),current_long = gps.GPS_LOC(2);
	double theta, dist;
	if ((current_lat == final_lat) && (current_long == final_long)){
		return 0;
	}
	else{
		theta = current_long - final_long;
		dist = sin(deg2rad(current_lat)) * sin(deg2rad(final_lat)) + cos(deg2rad(current_lat)) * cos(deg2rad(final_lat)) * cos(deg2rad(theta));
		dist = acos(dist);
		dist = rad2deg(dist);
		dist = dist * 60 * 1.1515;
		dist = dist * 1.609344;
		return (dist);
	}
}
//Compiled distance is the distance from a pouint32_t to another pouint32_t including altitude as well as GPS-coord for a distance estimate
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
	//Check every distance for pouint32_ts in array and compare to determine smallest
	double smallest_dist = 0;
	uint8_t index, i = HcurrentIndex;
	for (size_t i; i < TDlength(array); i++){
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
	//Check every distance for pouint32_ts in array and compare to determine smallest
	double smallest_dist = array[0];
	uint8_t index = AcurrentIndex;
	for (size_t i; i < ODlength(array); i++){
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
double *PathCompute::Proportional_integral_derivative(double deviation){
	//function to determine the rotation of both the first servo and second servo for thrust vectoring
	//to adjust the course so that the rocket heads towards the straight line and follow that straight line.
}
//Function to compute deviation angle
double PathCompute::deviationAngle(double latStartingpouint32_t, double longStartingpouint32_t, double latEndpouint32_t, double longEndpouint32_t){
	double deviation_angle, path_line_deviation, temp1, temp2;
	//temp1 = atan2(latEndpouint32_t - latStartingpouint32_t / longEndpouint32_t - longStartingpouint32_t); //<-Fix issue
	temp2;

	return deviation_angle;
}
//Function to compute path line deviation
double PathCompute::pathLineDeviation(double devAngle){
	double temp1, temp2;
	double path_line_deviation;
	temp1 = sin(devAngle);
	//temp2 = distance_lat_long(startingpouint32_t[0],startingpouint32_t[1],endpouint32_t[0],endpouint32_t[1]);
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
		for (size_t j = current_alt; j < high; j += divisibleBY(tempDiff)){
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
//Functions to generate heading path pouint32_ts for launch stage,transfer stage and landing stage
//Function writes path pouint32_ts to a two dimensional array and is coverted to return a one dimensional array
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
	double *conv = arrayConversion2D_1D(tempPoints);
	return conv;
}