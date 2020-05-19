#include"PID.h"

uint8_t tagCount, PR_count;
double PID_PR[64][5];
String *tags = (String*)malloc(12);

//Important for PID process identification
double kp = 0.5,ki = 0.2,kd = 0.1;
double error_previous = 0,error_integral = 0;

double error,processVar;
double derivative,proportional,integral;

double PROPORTIONAL_INTEGRAL_DERIVATIVE::getProportional(){
    proportional = kp * error;
    return proportional;
}

double PROPORTIONAL_INTEGRAL_DERIVATIVE::getIntegral(){
    integral = ki * error_integral;
    return integral;
}

double PROPORTIONAL_INTEGRAL_DERIVATIVE::getDerivative(){
    derivative = kd * derivative;
    return derivative;
}

double PROPORTIONAL_INTEGRAL_DERIVATIVE::PID_MAIN(String Process,double current,double setpoint){
    updateConstants(Process);
    processVar = current;
	error = setpoint - processVar;
	error_integral += error * dt;
    derivative = (error - error_previous) / dt;
    error_previous = error;
    double dv = getDerivative();
    double it = getIntegral();
    double prop = getProportional();
    auto result = proportional + integral + derivative;
    return result;
}

void PROPORTIONAL_INTEGRAL_DERIVATIVE::createPIDinstance(String tag,double kp,double ki,double kd){ 
    if(!checkforInstance(tag)){
        tags[tagCount] = tag;
        tagCount++;
        PID_PR[PR_count][0] = kp;
        PID_PR[PR_count][1] = ki;
        PID_PR[PR_count][2] = kd;
        //Create error variables
        double erPrev = 0,erInteg = 0;
        PID_PR[PR_count][3] = erPrev;
        PID_PR[PR_count][4] = erInteg;
        PR_count++;
    }else{
        //Do nothing
    }
    
}

void PROPORTIONAL_INTEGRAL_DERIVATIVE::updateConstants(String Process){
    uint8_t index = -1;
    for(size_t i = 0; i < tagCount;i++){
        if(compare(tags[i],Process)){
            index = i;
        }
    }
    ErrorDump sen;
    if(index != -1){
        kp = PID_PR[index][0];
        ki = PID_PR[index][1];
        kd = PID_PR[index][2];
        error_previous = PID_PR[index][3];
        error_integral = PID_PR[index][4];
   }else{
       sen.ERROR_DUMP("311");
   }
}

boolean PROPORTIONAL_INTEGRAL_DERIVATIVE::compare(String x, String y){
    if (x != y){
        return false;
    }
    else{
        return true;
    }
}

boolean PROPORTIONAL_INTEGRAL_DERIVATIVE::checkforInstance(String tag){
    boolean instanceTrue = false;
    for(size_t i = 0; i < tagCount;i++){
        if(compare(tag,tags[i])){
            instanceTrue = true;
        }
    }
    return instanceTrue;
}