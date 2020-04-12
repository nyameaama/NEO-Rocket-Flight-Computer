#include<math.h>
#include<stdlib.h>
#include<stdint.h>
#define pi 3.14159265358979323846

//Gyro path;
//double pitch_read = path.AccGyroVals(2);
//double yaw_read = path.AccGyroVals(3);
//double final_lat, final_long;
//double path_pouint32_ts[32][64];
//Path anchor index shows the pouint32_ts the current loc in the path the vehicle is in. All prehand pouint32_ts are discarded
//uint32_t numPouint32_ts,path_anchor_index;
//double currentHeading[2] = {AccGyroVals(2),AccGyroVals(3)};// <— Pitch = [0] Yaw = [1]

class PathCompute {
	private:
        //This functions finds the next divisible number
		uint16_t divisibleBY(uint32_t x);

        //This function converts decimal degrees to radians       
		double deg2rad(double deg);

        //This function converts radians to decimal degrees 
		double rad2deg(double rad);

         //Calculates cosine rule
		double cosine_rule(double lengthA,double lengthB,double lengthC);

        double ang_to_PitchYaw();

        //1D array Length Function
		uint8_t ODlength(double arr[]);

        //2D array Length Function
		uint32_t TDlength(double arr[][2]);

        //Convert 2D array to 1D array    
        double *arrayConversion2D_1D(double array[][2]);

    public: 
		 //Convert 1D array to 2D array 
        double *arrayConversion1D_2D(double array[64]);

        //Distance between two pairs of coordinates. Returns Kilometers
		double distance_lat_long(double current_lat,double current_long,double final_lat,double final_long);

        //Compiled distance is the distance from a pouint32_t to another pouint32_t including altitude as well as GPS-coord for a distance estimate
		double compiled_distance(double current_lat,double current_long,double current_alt,double final_lat,double final_long,double final_alt);

        //Function to determine peak altitude
		double peak_altitude(double distance);

        double *LatLongDist_gen(double latitude,double longitude,double metres);

        //Function to determine Heading closest point
		uint8_t HeadingclosestPoint(double FLat,double FLong,double array[64][2],uint32_t HcurrentIndex);

        //Function to determine Altitude closest point
		double AltitudeclosestPoint(double current_alt,double array[64],uint8_t AcurrentIndex);

        //Function to determine the rotation of both the first servo and second servo for thrust vectoring
		//to adjust the course so that the rocket heads towards the straight line and follow that straight line.
        double *Proportional_integral_derivative(double deviation);

        //Function to compute deviation angle 
		double deviationAngle(double latStartingpouint32_t,double longStartingpouint32_t,double latEndpouint32_t,double longEndpouint32_t);

        //Function to compute path line deviation
		double pathLineDeviation(double devAngle);

        //Function to Generate Altitude path
		double *generate_alt(double current_alt,double high);

        //Helper function for LatLongDist()
		double LatLongDist_helper(double current_lat,double current_long, double latlong,double distance);

        //Functions to generate heading path pouint32_ts for launch stage,transfer stage and landing stage
		//Function writes path pouint32_ts to a two dimensional array and is coverted to return a one dimensional array
		double *generate_path_points(double current_lat,double current_long,double final_lat,double final_long);

        
};    