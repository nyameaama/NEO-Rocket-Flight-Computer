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

boolean StateMachine::reOrient_Program(){
    //check for successful reorient 


}

//Detect Landing Program
boolean StateMachine::checkforPropulsion_begin(){
    Sensors alt;
    boolean begin = false;
    AutoLand determine;
    if(determine.propulsionAltitude() >= alt.altimeter()){
        begin = true;
    }
    return begin;
}

//Detect successful landing
boolean StateMachine::checkforSuccessLand(){
    Sensors verify;
    Gyro bounds;
    uint8_t boundary = 3;
    //If vel == 0 and rocket is upright propulsive land successful
    boolean successLand = true;
    if(verify.AirspeedVal() > 5){
        successLand = false;
    }
    if((bounds.AccGyroVals(2)) > (90 + boundary) || (bounds.AccGyroVals(2)) < (90 - boundary)){
        successLand = false;
    }
    if((bounds.AccGyroVals(3)) > (90 + boundary) || (bounds.AccGyroVals(3)) < (90 - boundary)){
        successLand = false;
    }
    return successLand;
}

boolean StateMachine::checkState(){
	//Check if rocket orientation is within bounds and not spiraling out 
	//of control
	//If out of control brick all control actions
	Gyro state;
	double pitch = state.AccGyroVals(2);
	boolean inBounds = (pitch < -25.0) ? false : true;
	if(inBounds){
		return true;
	}else{
		return false;
	}
}