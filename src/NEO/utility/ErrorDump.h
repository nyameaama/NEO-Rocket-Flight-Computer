//#include"../Data Logging/FileSys.h"
#include<string.h>
#include<Arduino.h>
//Error Dump receives errors from system functions and saves them to SD file
//File Name = "ErrorDump"
#define DB_SIZE 10

class ErrorDump {
    private:
        String *ErrorCodes = (String*)malloc(DB_SIZE);
        uint8_t code_index = -1;
        String FileSysPID = "SYS412Y"; 

    private:
        boolean confirmECODE(String code);

        String GET_ERROR_TYPE(String x);

        uint8_t LOG_ERROR(String Etype);

        boolean strcompare(String x, String y);

    public:
        ErrorDump();

        uint8_t ERROR_DUMP(String code);
};