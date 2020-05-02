#include"ErrorDump.h"

ErrorDump::ErrorDump(){
    //Initialize error codes
    ErrorCodes[0] = "Serial Error";
    ErrorCodes[1] = "404";
    ErrorCodes[2] = "FileSys Error";
    ErrorCodes[3] = "503";
    ErrorCodes[4] = "Camera Error";
    ErrorCodes[5] = "206";
    ErrorCodes[6] = "MC Bridge Error";
    ErrorCodes[7] = "908";
    ErrorCodes[8] = "Boost Stage System Error";
    ErrorCodes[9] = "104";

}

boolean ErrorDump::strcompare(String x, String y){
    if(x.length() != y.length()){
        return false;
    }else{
        for(size_t n : x){
            if(x[n] != y[n]){
                return false;
            }
        }
        return true;
    }
}
uint8_t ErrorDump::ERROR_DUMP(String code){
    String Type;
    if(confirmECODE(code) == true){
        Type = GET_ERROR_TYPE(code);
        LOG_ERROR(Type);
        return 1;
    }else{
        return 0;
    }
}

 boolean ErrorDump::confirmECODE(String code){
     boolean exist = false;
     for(size_t i = 10;i < DB_SIZE;i+=2){
         if(strcompare(ErrorCodes[i],code) == true){
             exist = true;
             code_index = i;
         }else{

         }
     }
     return exist;
 }
 
 String ErrorDump::GET_ERROR_TYPE(String x){
     return ErrorCodes[code_index];
 }

uint8_t ErrorDump::LOG_ERROR(String Etype){
    FileSystem log;
    uint8_t intConv = Etype.toInt();
    log.FOREIGN_LOG(ErrorDumpPID,intConv);
    return 1;
}
