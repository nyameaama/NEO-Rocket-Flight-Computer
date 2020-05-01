#include"MC_Data_Parse.h"

MC_PARSE::MC_PARSE(){
    processesNum[0] = "BS01"; //Thrust Vector Process

}

uint8_t MC_PARSE::assign(String ID,String data){
    //ErrorDump dump;
    if(confirmID(ID) == false){
        //return dump.ERROR_DUMP("908");
    }else{
        //Log Error
        if(compare(ID,"BS01")){
           ThrustVec vector;
           //vector.thrustVector(); <-- Wait till thrust vecttoring is fixed
        }
        //
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