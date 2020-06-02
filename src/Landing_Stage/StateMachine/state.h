#ifndef STATE
#define STATE

#include"../Trigger Systems/AreaAnalysis.h"
#include"../Flight Control/Stability System/AxisStability.h"
#include"../Sensors/sensors.h"

class StateMachine {
    private:
        AreaAnalysis trigger;

    public:
        //Detect MECO by acceleration differential
        boolean checkforMECO();

        //Detect Launch
        boolean checkforLaunch();

        //Apogee
        boolean checkforApogeee();

        //Use of PID fin control to reorient vehicle
        uint8_t reOrient_Program();

        //Detect Coast phase
        boolean checkforCoast();

        //Detect Landing Program
        boolean checkforLand();


};

#endif