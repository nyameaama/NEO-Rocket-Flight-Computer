#ifndef Comm
#define Comm

#include"RH_ASK.h"
#include<SPI.h>
#include"../../utility/ErrorDump.h"

//Using RF Transmitter to wirelessly send data from vehicle
class ExCommunication{
    private:
        RH_ASK driver;
        int delayTime = 250;
    public:
        void transmit(const char *msg){
    if (!driver.init()){
        //Init Error
        ErrorDump dmp;
        dmp.ERROR_DUMP("662");
    }
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    delay(delayTime);
}

};
#endif