#ifndef MC_COMM
#define MC_COMM

#include<SoftwareSerial.h>

//Connecting 2 Arduinos by Bluetooth using a HC-05 and a HC-06: Pair, Bind, and Link

class MC_Communication {
    public:
        //SoftwareSerial BTSerial(2, 3); // RX | TX

        uint8_t request(uint8_t x);

        uint8_t receiveDat(uint8_t x);

        unsigned int crc32c_checksum(unsigned char *message);

};

#endif