#ifndef MC_Communicate
#define MC_Communicate

#include<SoftwareSerial.h>
#include<Arduino.h>

//#define RX_PIN 0
//#define TX_PIN 0

//Connecting 2 Arduinos by Bluetooth using a HC-05 and a HC-06: Pair, Bind, and Link

class CommMC {
    private:
       uint8_t RX_PIN;
       uint8_t TX_PIN;

    public:
        CommMC();
 // Connect the HC-05 TX to Arduino pin 2 RX. 
        // Connect the HC-05 RX to Arduino pin 3 TX through a voltage divider.
       // SoftwareSerial BTserial(RX_PIN, TX_PIN); // RX | TX

};

#endif