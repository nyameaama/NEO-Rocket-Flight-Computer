#include"state.h"

 void StateMachine::startupRoutine(){
     LED_BUZZER ring;
      while(!ring.buttonPressed()){
            ring.blink(3);
            ring.playTone();
            delay(60000);
        }
 }

//Detect MECO by acceleration differential
boolean StateMachine::checkforMECO(){
    boolean MECO = false;
    if(trigger.analyseAltDecceleration()){
        MECO = true;
    }
    return MECO;    

}

//Detect Launch
boolean StateMachine::checkforLaunch(){
    RPY_CHECK lim;
    Sensors alt;
    boolean LAUNCH_SUCCESS = false;
    double *elaps = lim.timeElapsed();
    double *ret = lim.velChange();
    if(trigger.launch_detect(alt.altimeter(),elaps[2],ret[0],ret[1]) != 1){
        LAUNCH_SUCCESS = true;
    } 
    return LAUNCH_SUCCESS;   
}

 //Apogee
 boolean StateMachine::checkforApogeee(){
    boolean Apogee =  (trigger.time_to_Apogee() <= 0) ? true : false;
    return Apogee;
 }

