#ifndef PathControl_F
#define PathControl_F

#include<stdlib.h>
#include<stdint.h>
#include"../Nav/PathCompute.h"
#include"../../Flight Control/Stability System/AxisStability.h"

class PathControl : public PathCompute {
	private:
		//Accepts directional values to translate to t-vector range
		//y =    0 = pitch     1 = yaw
		double translate(double x,double y);

        public:
		//Accepts new pitch and yaw heading values and vectors appropriately
		double adjustAltitude(double pitch);

		double adjustPath(double yaw);

    public:
         double *pathController(double latC,double longC,double alt,double *xF_pathData[64][2]);

         //Path Controller Function for altitude control
		double altitudeController(double cLoc,uint8_t haslaunched);

		//Function to change between fin based control and thrust vectoring control
		void state(uint8_t current_State);
};

#endif      


//TO-DO : Refactor path controller