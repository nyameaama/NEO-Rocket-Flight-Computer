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
		double adjustHeading(double pitch,double yaw);

    public:
         double *pathController(double latC,double longC,double alt,double *xF_pathData[64][2]);

         //Path Controller Function for altitude control
		double alt_PathController(double cLoc,uint8_t haslaunched);

		template <typename T>
		T state(T current_State);
};

#endif      


//TO-DO : Refactor path controller