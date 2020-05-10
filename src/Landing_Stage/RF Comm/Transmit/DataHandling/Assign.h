#ifndef ASSIGN
#define ASSIGN

#include<Arduino.h>
//#include"../ExCommunication - Transmit.h"
//#include"../ExCommunication - Recieve.h"

class RF_ASSIGN {
    private:
        String *logs = (String*)malloc(5);

    private:
        //Function to compress strings into one string
        String cStrings(String x, String y);

        String *dcString(String x);

    public:
        RF_ASSIGN();

        ~RF_ASSIGN();

        uint8_t RF_SEND(String RFID,String data);

        String *RF_REC();

        uint8_t designate(String RFID,String data);

};

#endif