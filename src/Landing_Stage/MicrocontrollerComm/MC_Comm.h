#ifndef MC_Communicate
#define MC_Communicate

#include<SoftwareSerial.h>
#include"../utility/ErrorDump.h"
#include<Arduino.h>

//#define RX_PIN 0
//#define TX_PIN 0
#define PROCESSES_SIZE 2

//Connecting 2 Arduinos by Bluetooth using a HC-05 and a HC-06: Pair, Bind, and Link

class CommMC {
    private:
       String *processes = (String*)malloc(PROCESSES_SIZE);

    private:
        boolean confID(String ID);

        boolean compare(String x, String y);

    public:
        CommMC();

        uint8_t assign(String ID,String data);
};

#endif