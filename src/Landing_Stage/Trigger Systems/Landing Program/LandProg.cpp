#include"LandProg.h"

//Function to find acceleration of rocket in () time
double AutoLand::AccelerationInSetTime(double seconds){
    double rocketMass = 1.0; //kg
    double engineThrust = 25.3;
    double rocket_Weight = rocketMass * 9.8;
    double resultant_force = engineThrust - rocket_Weight;
    double Acceleration = resultant_force / rocketMass;
    return Acceleration * seconds;
}

//Function computes time (returns ms) propulsive acceleration will get vehicle to 1m/s
double AutoLand::calculatePropulsiveAccelerationTime(){
    double vel = comp.AirspeedVal(); 
    double acc = AccelerationInSetTime(1);          //m/s
    double pTime = vel / acc;
    return pTime * 1000;
}

//Function to compensate motor ignition delay to calculation
double AutoLand::compensateIgnitionDelay(double altitude){
    double IGNITION_DELAY; //seconds
    double revAlt = comp.AirspeedVal() * IGNITION_DELAY;
    revAlt = altitude + revAlt;
    return revAlt;
}

//Driver function
double AutoLand::propulsionAltitude(){
    //To get the trigger altitude we use the time the motor takes to 
    //slow the vehicle down to 1 and add it to the terrain level
    //s * t
    //Altitude at landing area
    double terrainGroundLevel;
    double PAT = calculatePropulsiveAccelerationTime() / 1000;
    //Current vel * Propulsive time to find distance
    double tempDist = comp.AirspeedVal() * PAT;
    double propulAlt = terrainGroundLevel + tempDist;
    //Compensate for ignition delay
    propulAlt = compensateIgnitionDelay(propulAlt);
    return propulAlt;

}       