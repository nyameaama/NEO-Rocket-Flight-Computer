#include<stdlib.h>
#include<stdint.h>

class PathControl {
	private:
		//Accepts directional values to translate to t-vector range
		//y =    0 = pitch     1 = yaw
		double translate(double x,double y);

        public:
		//Accepts new pitch and yaw heading values and vectors appropriately
		double *adjustHeading(double pitch,double yaw,double current_pitch,double current_yaw);

    public:
         double *pathController(double latC,double longC,double alt,double *xF_pathData[64][2]);

         //Path Controller Function for altitude control
		double alt_PathController(double cLoc,uint8_t haslaunched);    
};       