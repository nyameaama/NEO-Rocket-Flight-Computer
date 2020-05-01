#ifndef DATAPARSE
#define DATAPARSE

#include<Arduino.h>
#include"../Control/ThrustVec.h"

#define NO_OF_PROCESSES 3

class MC_PARSE {
    private:
       String *processesNum = (String*)malloc(NO_OF_PROCESSES);

    private:
        boolean confirmID(String ID);

        boolean compare(String x, String y);

    public:
        MC_PARSE();

        uint8_t assign(String ID,String data);
};

#endif