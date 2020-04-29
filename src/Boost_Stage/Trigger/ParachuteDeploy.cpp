#include"ParachuteDeploy.h"

boolean DeployP::detectAlt(){
    BSensors get;
    boolean trigger = false;
    double altReading = get.BS_altimeter();
    if(altReading < DEPLOY_ALTITUDE){
        trigger = true;
    }
    return trigger;
}

uint8_t DeployP::deployChute(){
    if(detectAlt() == true){

    }
}