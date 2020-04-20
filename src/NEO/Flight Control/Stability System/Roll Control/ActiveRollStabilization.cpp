#include"ActiveRollStabilization.h"

String RollStability::determineRollDirection(){
    //Roll direction can be calculated by using two roll values to
    // 
    uint8_t sampleAmount = 3;
    double *rollV = compileValues(sampleAmount);
    uint8_t count;
    for(size_t i = 0; i < 2;i++){
        if(rollV[i] < rollV[i + 1]){
            count++;
        }    
    }
    if(count == 2){
      SPIN_DIRECTION = "anticlockwise"; 
    }
}

uint8_t RollStability::updateCurrentRollAxis(){
     uint8_t sampleAmount = 2;
    double *Val = compileValues(sampleAmount);
    if(Val[0] < 0){
        POS_ROLL_AXIS = false;
    }
}

double *RollStability::compileValues(uint8_t count){
    Gyro rSen;
    double *vals = (double*)malloc(count);
    for(size_t i = 0;i < count;i++){
        vals[i] = rSen.AccGyroVals(1);
    }
    return vals;
}

double RollStability::getRollSpeed(){
    //We can get roll speed by dividing its roll distance(the difference between
    //roll points) with the roll time (the time it took to roll)
    double start,end,read1,read2;
    double time,dist;
    Gyro beg;
    read1 = beg.AccGyroVals(1);
    start = millis();
    read2 = beg.AccGyroVals(1);
    end = millis();
    time = (end - start) / 1000;
    dist = read2 - read1;
    return dist / time; // roll/sec
}

double RollStability::getRotationPM(){
    double rSpeed = getRollSpeed();
    double diameter; //diameter in cm
    double diameter_cm_to_m,surfaceSpeed;
    //Calculate surfaceSpeed
    double rollCycle = 360 / rSpeed; //time it takes do do one rotation cycle at given speed
    diameter_cm_to_m = diameter / 100;
    surfaceSpeed = (pi * diameter_cm_to_m);
    surfaceSpeed = surfaceSpeed / rollCycle;
    //surfaceSpeed to RPM
    double ms_to_fm;//metres per second to feet per minute
    double diam_to_feet,RPM;
    ms_to_fm = surfaceSpeed * 196.85;
    RPM = ms_to_fm * 4;
    diam_to_feet = (diameter_cm_to_m * 39.37) / 12;
    RPM = RPM / diam_to_feet;
    return RPM;
}

uint8_t RollStability::computeCounterRoll(uint8_t x){
    
}

 uint8_t RollStability::rollStabilize(uint8_t roll){
    uint8_t R_axis = 0; //Initialise to negative
    updateCurrentRollAxis();
    if(POS_ROLL_AXIS == true){
        R_axis = 1;  //If pos set to pos  
    }
    determineRollDirection();


 }