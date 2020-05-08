#ifndef ASSIGN
#define ASSIGN

#include<Arduino.h>

class RF_ASSIGN {
    private:
        String *logs = (String*)malloc(5);
        
    private:
        String compressStrings(String x, String y);

    public:
        RF_ASSIGN();

        String RF_SEND(String RFID,String data);

};

#endif