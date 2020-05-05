#ifndef BT
#define BT

#include<SoftwareSerial.h>
#include<CRC32.h>

//Connecting 2 Arduinos by Bluetooth using a HC-05 and a HC-06: Pair, Bind, and Link

class BT_Comm {
    private:
        uint8_t RX_PIN;
        uint8_t TX_PIN;
        
    private:
        String compressStrings(String x, String y);

        String *decompressString(String x);

    public:
        // Connect the HC-05 TX to Arduino pin 2 RX. 
        // Connect the HC-05 RX to Arduino pin 3 TX through a voltage divider.
        // SoftwareSerial BTserial(RX_PIN, TX_PIN); // RX | TX
        //SoftwareSerial BTSerial(2, 3); // RX | TX

        String *request();

        uint8_t send(String ID, String x);

        unsigned int crc32c_checksum(char *message);

};

#endif