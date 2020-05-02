#include"MC_Data_Parse.h"

MC_PARSE::MC_PARSE(){
     //Boost Stage processes 
    processesNum[0] = "BS01"; // Log Error 
    processesNum[1] = "BS02"; // Ejection Command
    // Landing Stage Processes
    processesNum[2] = "LS02"; //Send velocity
    processesNum[3] = "LS03"; //Send/Receive thrust Vector gimbal position

}

uint8_t MC_PARSE::assign(String ID,String data){
    ERROR sec;
    if(confirmID(ID) == false){
        return sec.route("908");
    }
    if(verifyTransmit_Receive(ID) == 2){
        sendDat(ID,data);
    }else if(verifyTransmit_Receive(ID) == 1){
        receiveDat(ID,data);
    }else{
        return sec.route("908");
    }

}

 uint8_t MC_PARSE::receiveDat(String ID,String data){
    if(compare(ID,"LS03")){
        ThrustVec vector;
        //vector.thrustVector(); <-- Wait till thrust vectoring is fixed    
    }
    if(compare(ID,"LS02")){

    }
    return;
 }

uint8_t MC_PARSE::sendDat(String ID,String data){
    //Send logs
    if(compare(ID,"BS01")){
        car.send(ID,data);
    }
    //Send Ejection Commands    
    if(compare(ID,"BS02")){
        car.send(ID,data);
    }
    return;
}

uint8_t MC_PARSE::verifyTransmit_Receive(String ID){
    if(String(ID[0]) == String("B") && String(ID[1]) == String("S")){
        return 2;
    }else if(String(ID[0]) == String("L") && String(ID[1]) == String("S")){
        return 1;
    }else{
        return 0;
    }
}

boolean MC_PARSE::confirmID(String x){
    //Confirm ID
    boolean confirm = false;
    uint8_t index;
    for (size_t i = 1; i < NO_OF_PROCESSES; i += 2){
        if (compare(x, processesNum[i]) == true){
            confirm = true;
        }
    }
   return confirm;
}

//Function compares two strings
boolean MC_PARSE::compare(String x, String y){
    if (x != y){
        return false;
    }
    else{
        return true;
    }
}