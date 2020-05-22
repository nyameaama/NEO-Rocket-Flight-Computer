#include"MC_Comm.h"

CommMC::CommMC(){
    //Boost Stage processes 
    processes[0] = "BS01"; // Log Error 
    processes[1] = "BS02"; // Ejection Trigger
    // Landing Stage Processes
    processes[2] = "LS02"; //Send velocity
    processes[3] = "LS03"; //Send thrust Vector gimbal position
    processes[4] = "LS04"; //Ejection confirmation
}

uint8_t CommMC::assign(String ID,String data){
    ErrorDump dump;
    if(confID(ID) == false){
        return dump.ERROR_DUMP("908");
    }
    if(verifyTransmit_Receive(ID) == 2){
        receiveDat(ID,data);
    }else if(verifyTransmit_Receive(ID) == 1){
        sendDat(ID,data);
    }else{
        return dump.ERROR_DUMP("908");
    }
}

 uint8_t CommMC::receiveDat(String ID,String data){
     ErrorDump dump;
     //Receive Log Errors
        if(st.compare<String>(ID,"BS01")){
            dump.ERROR_DUMP(data);
        }
        if(st.compare<String>(ID,"BS02")){

        }
        return;
 }

uint8_t CommMC::sendDat(String ID,String data){
     BT_Comm trans;
    Sensors get;
    //Send vehicle velocity
    if(st.compare<String>(ID,"LS02")){
        trans.send(ID,String(get.AirspeedVal()));
    }
    if(st.compare<String>(ID,"LS03")){
        //Send BS gimbal value

    }
    if(st.compare<String>(ID,"LS04")){
        //Ejection confirmation
        AreaAnalysis anal;
        String verify = "N";
        if(anal.analyseAltDecceleration()){
            verify = "Y";
        }
        trans.send(ID,verify);
    }
    return;
}

uint8_t CommMC::verifyTransmit_Receive(String ID){
    if(String(ID[0]) == String("B") && String(ID[1]) == String("S")){
        return 2;
    }else if(String(ID[0]) == String("L") && String(ID[1]) == String("S")){
        return 1;
    }else{
        return 0;
    }
}

boolean CommMC::confID(String x){
    //Confirm ID
    boolean confirm = false;
    uint8_t index;
    for (size_t i = 1; i < PROCESSES_SIZE; i += 2){
        if (st.compare<String>(x, processes[i]) == true){
            confirm = true;
        }
    }
   return confirm;
}