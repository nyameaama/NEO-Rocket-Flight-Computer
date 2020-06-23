#ifndef STATE
#define STATE

#include"../Trigger Systems/AreaAnalysis.h"
#include"../Flight Control/Stability System/AxisStability.h"
#include"../Sensors/sensors.h"
#include"../Trigger Systems/Misc/LED_Buzzer.h"
#include"../Inertial Measurement/IMU.h"
#include"../Trigger Systems/Landing Program/LandProg.h"

class StateMachine {
    private:
        AreaAnalysis trigger;

    public:
        void startupRoutine();

        //Detect MECO by acceleration differential
        boolean checkforMECO();

        //Detect Launch
        boolean checkforLaunch();

        //Apogee
        boolean checkforApogeee();

        //Use of PID fin control to reorient vehicle
        boolean reOrient_Program();

        //Detect Coast phase
        boolean checkforCoast();

        //Detect Landing Program
        boolean checkforPropulsion_begin();

        //Detect successful landing
        boolean checkforSuccessLand();

        //Check if rocket orientation is within bounds and not spiraling out of control
        boolean checkState();


};

#endif