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

uint8_t computeCounterRoll(uint8_t x){
    
}