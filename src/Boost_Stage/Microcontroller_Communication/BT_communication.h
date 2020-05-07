#ifndef MC_COMM
#define MC_COMM

#include<SoftwareSerial.h>
#include<Arduino.h>

#define RXPIN 10
#define TXPIN 11

//Connecting 2 Arduinos by Bluetooth using a HC-05 and a HC-06: Pair, Bind, and Link

//SoftwareSerial BSerial(RXPIN, TXPIN);

class MC_Communication {
    private:
        String compStrings(String x, String y);

        String *decompString(String x);

    public:
        MC_Communication();

        String *request();

        uint8_t send(String ID, String x);

        unsigned int crc32c_checksum(String dataS);

};

#endif