#ifndef FlightRecording
#define FlightRecording

#include <Wire.h>
#include <ArduCAM.h>
#include <SPI.h>
#include <SD.h>
#include "memorysaver.h"

class FlightRec {
    private:
        const int CS1 = 4;
        bool CAM1_EXIST = false; 
       
    private:
        char *ConstructFileName(int k,char str[28]);

    public: 
        void SPI_BUS_CHECK(ArduCAM myCAM1);

        FlightRec();

        byte camCapture(ArduCAM myCAM);

        uint8_t SavetoSD(uint32_t length,ArduCAM myCAM);


};

#endif