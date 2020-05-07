#include"AccAnalysis.h"

 boolean ACC_ANALYSIS::analyseAltDecceleration(){
     //To detect decceleration patterns from decceleration the distance between each
     //alt value is analysed to see if over the time the difference gets smaller
    double *alt_time_samples = getAltVals();
    //New array to separate timestamps from vel values
    double *altOnly_samples = (double*)malloc(SAMPLE_SIZE); 
    uint8_t new_arr_index;
    for(size_t n = 0;n < SAMPLE_SIZE * 2;n+=2){
        altOnly_samples[new_arr_index] = alt_time_samples[n];
        new_arr_index++; 
    }
    //Find speed of increase between each pair of values
    //s = d /t --> speed_of_increase = difference / time_duration
    double *speed_of_increase = (double*)malloc(SAMPLE_SIZE);
    uint8_t SOI_index; 
    for(size_t i = 0;i < SAMPLE_SIZE;i++){
        //Get difference
        double diff = altOnly_samples[i + 1] - altOnly_samples[i];
        //Get time duration
        double duration = timeBetween(alt_time_samples[i + 1],alt_time_samples[i + 3]);
        //Compute speed of increase
        double S_O_I = diff / duration;//Samples per 
        speed_of_increase[SOI_index] = S_O_I;
        SOI_index++;
    }
    //Determine if speed of increase follws a descending trend
    boolean deccel = true;
    for(size_t j = 0;j < SAMPLE_SIZE;j++){
        if(j != SAMPLE_SIZE){
            if(speed_of_increase[j + 1] > speed_of_increase[j]){
                deccel = false;
            }
        }else{
            //Do nothing
        }
    }
    return deccel;
 }

//Function gets altitude samples with time took place. time = millis() 
//which is the number of time passed after the program started
double *ACC_ANALYSIS::getAltVals(){
    double *values = (double*)malloc(SAMPLE_SIZE);
    for(size_t i = 0;i < SAMPLE_SIZE / 2;i+=2){
        values[i] = get.BS_altimeter();
        values[i + 1] = millis();
    }
    return values;
}

//Function gets duration between two timestamps
double ACC_ANALYSIS::timeBetween(double x,double y){
    return (y - x);
}

boolean ACC_ANALYSIS::ejectStage(){
    if(analyseAltDecceleration()){
        MC_PARSE mov;
        String ID = "BS02";
        mov.assign(ID,"Y");

        
    }else{
        //Do nothing
    }
}