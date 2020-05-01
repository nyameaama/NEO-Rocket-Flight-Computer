#ifndef BT
#define BT

#include<SoftwareSerial.h>

//Connecting 2 Arduinos by Bluetooth using a HC-05 and a HC-06: Pair, Bind, and Link

class BT_Comm {
    private:
        uint8_t RX_PIN;
        uint8_t TX_PIN;
    public:
        // Connect the HC-05 TX to Arduino pin 2 RX. 
        // Connect the HC-05 RX to Arduino pin 3 TX through a voltage divider.
        // SoftwareSerial BTserial(RX_PIN, TX_PIN); // RX | TX
        //SoftwareSerial BTSerial(2, 3); // RX | TX

        uint8_t request(uint8_t x);

        uint8_t receiveDat(uint8_t x);

        unsigned int crc32c_checksum(unsigned char *message);

};

#endif