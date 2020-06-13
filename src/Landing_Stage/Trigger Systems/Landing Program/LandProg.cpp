#include"LandProg.h"

//Function to find acceleration of rocket in () time
double AutoLand::AccelerationInSetTime(double seconds){
    double rocketMass = 0.5; //kg
    double engineThrust = 25.3;

    double rocket_Weight = rocketMass * 9.8;
    double resultant_force = engineThrust - rocket_Weight;
    double Acceleration = resultant_force / rocketMass;
    return Acceleration * seconds;
}

//Function computes time propulsive acceleration will get vehicle to 1m/s
double AutoLand::calculatePropulsiveAccelerationTime(){
    Sensors comp;
    double vel = comp.AirspeedVal(); 
    double acc = AccelerationInSetTime(1);          //m/s
    double pTime = vel / acc;
    return pTime * 1000;
}