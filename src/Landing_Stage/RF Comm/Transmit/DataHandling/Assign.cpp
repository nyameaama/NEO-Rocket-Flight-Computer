#include"Assign.h"

RF_ASSIGN::RF_ASSIGN(){
    logs[0] = "VEL";
    logs[1] = "ALT";
    logs[2] = "PIT";
    logs[3] = "ROL";
    logs[4] = "YAW";
}

 RF_ASSIGN::~RF_ASSIGN(){
     free(logs);
 }

 String RF_ASSIGN::cStrings(String x, String y){


 }

uint8_t RF_ASSIGN::RF_SEND(String RFID,String data){
    //Compress into one string
    String temp_data = cStrings(RFID,data);
    const char* final_data = temp_data.c_str();
    //Send 
    //ExCommunication tr;
   // tr.transmit(final_data);
    return;
}