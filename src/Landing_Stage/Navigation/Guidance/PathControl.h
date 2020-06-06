#ifndef PathControl_F
#define PathControl_F

#include<stdlib.h>
#include<stdint.h>
#include"../Nav/PathCompute.h"
#include"../../Flight Control/Stability System/AxisStability.h"
#include"../../Flight Control/Thrust_Vector_Control/TVC.h"
#include"../../Flight Control/Thrust_Vector_Control/PTV.h"

#define BOOST_STAGE 0
#define LANDING_STAGE 1

class PathControl : public PathCompute {
	private:
		//Accepts directional values to translate to t-vector range
		//y =    0 = pitch     1 = yaw
		double translate(double x,double y);

		//Function to move thrust vectoring mount to pos
		double TVC(uint8_t M1pos,uint8_t M2pos);

    public:
		//Accepts new pitch and yaw heading values and vectors appropriately
		double adjustAltitude(double pitch);

		double adjustPath(double yaw);

        double *pathController(double latC,double longC,double alt,double *xF_pathData[64][2]);

        //Path Controller Function for altitude control
		double altitudeController(double cLoc,uint8_t haslaunched);

		//Function to change between fin based control and thrust vectoring control
		void state(uint8_t current_State);

		//Function to change between boost stage vector mount and landing stage mount
		void VECTOR_MOUNT_STATE(uint8_t state);

};

#endif      


//TO-DO : Refactor path controller