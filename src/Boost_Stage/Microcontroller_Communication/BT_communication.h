#ifndef MC_COMM
#define MC_COMM

#include<SoftwareSerial.h>

//Connecting 2 Arduinos by Bluetooth using a HC-05 and a HC-06: Pair, Bind, and Link

class MC_Communication {
    private:
        String compressStrings(String x, String y);

        String *decompressString(String x);

    public:
        //SoftwareSerial BTSerial(2, 3); // RX | TX

        String *request();

        uint8_t send(String ID, String x);

        unsigned int crc32c_checksum(unsigned char *message);

};

#endif