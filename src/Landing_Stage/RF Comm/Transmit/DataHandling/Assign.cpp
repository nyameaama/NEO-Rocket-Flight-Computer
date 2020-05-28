#include"Assign.h"

RF_ASSIGN::RF_ASSIGN(){
    logs[0] = "VEL";
    logs[1] = "ALT";
    logs[2] = "PIT";
    logs[3] = "ROL";
    logs[4] = "YAW";
    logs[5] = "E-BRICK";
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

String *dcString(String x){

}

String *RF_ASSIGN::RF_REC(){
    //return array
    //String *result = (String*)malloc(2);
    //Get string
    //RecRF str;
    //String rfStr = str.fileReceive();
    //Decompress string
    //String *decomp = dcString(rfStr);
    //result[0] = decomp[0];
    //result[1] = decomp[1];
    //return result;
}

uint8_t RF_ASSIGN::designate(String RFID,String data){
    

}