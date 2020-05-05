/*

#include<Arduino.h>
#include"Microcontroller_Communication/MC_Data_Parse.h"
#include"Microcontroller_Communication/BT_communication.h"
#include"Trigger/AccAnalysis.h"
#include"Trigger/ParachuteDeploy.h"

boolean FLIGHT_STAGE_1 = true;
boolean FLIGHT_STAGE_2 = false;
boolean CHUTE_DEPLOYED = false;
 

void setup(){
    //Receive motor ignition command


}

void loop(){
    //FLIGHT STAGE 1

    if(FLIGHT_STAGE_1){
        //Receive Landing stage commands
        MC_Communication rec;
        String *data = rec.request();
        //Parse and execute commands
        MC_PARSE init;
        init.assign(data[0],data[1]);
        //Send data to Landing Stage

        //Check for vehicle decceleration and send ejection trigger
        ACC_ANALYSIS trig;
        if(trig.ejectStage()){
            String ejectionProcessID = "BS02";
            String ejectisTrue = "1";
            init.assign(ejectionProcessID,ejectisTrue);
            FLIGHT_STAGE_1 = false;
            FLIGHT_STAGE_2 = true;
        }else{
            //Do nothing
        }
    }else{
    //FLIGHT STAGE 2

    //Check for parachute deploy point and deploy
        DeployP dep;
        if(dep.deployChute()){
            CHUTE_DEPLOYED = true;
        }else{
            //Do nothing
        }
    }
}

*/

