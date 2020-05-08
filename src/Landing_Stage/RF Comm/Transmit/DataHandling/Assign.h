#ifndef ASSIGN
#define ASSIGN

#include<Arduino.h>
#include"../ExCommunication - Transmit.h"

class RF_ASSIGN {
    private:
        String *logs = (String*)malloc(5);

    private:
        String compressStrings(String x, String y);

    public:
        RF_ASSIGN();

        uint8_t RF_SEND(String RFID,String data);

};

#endif