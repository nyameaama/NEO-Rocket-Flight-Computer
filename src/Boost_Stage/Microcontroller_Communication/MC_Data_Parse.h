#ifndef DATAPARSE
#define DATAPARSE

#include<Arduino.h>
#include"../Control/ThrustVec.h"
#include"../utility/ErrorRoute.h"
#include"BT_communication.h"

#define NO_OF_PROCESSES 4

class MC_PARSE {
    private:
       String *processesNum = (String*)malloc(NO_OF_PROCESSES);
       MC_Communication car;

    private:
        boolean confirmID(String ID);

        boolean compare(String x, String y);

        uint8_t receiveDat(String ID,String data);

        uint8_t sendDat(String ID,String data);

        uint8_t verifyTransmit_Receive(String ID);

    public:
        MC_PARSE();

        uint8_t assign(String ID,String data);
};

#endif