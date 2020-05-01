#include"MC_Comm.h"

CommMC::CommMC(){
    // BTserial.begin(38400); 
    processes[0] = "LS01"; // Log Error 

}

uint8_t CommMC::assign(String ID,String data){
    ErrorDump dump;
    if(confID(ID) == false){
        return dump.ERROR_DUMP("908");
    }else{
        //Log Error
        if(compare(ID,"LS01")){
            dump.ERROR_DUMP(" ");
        }
        //
    }

}

boolean CommMC::confID(String x){
    //Confirm ID
    boolean confirm = false;
    uint8_t index;
    for (size_t i = 1; i < PROCESSES_SIZE; i += 2){
        if (compare(x, processes[i]) == true){
            confirm = true;
        }
    }
   return confirm;
}

//Function compares two strings
boolean CommMC::compare(String x, String y){
    if (x != y){
        return false;
    }
    else{
        return true;
    }
}