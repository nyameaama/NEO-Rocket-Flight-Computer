#ifndef FlightRecording
#define FlightRecording

#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include"../utility/ErrorDump.h"
#include"Init.h"

/*
OV7670 Camera module with SD card module
on Arduino Uno.
 
Author: Hardik Kalasua (hardik.kalasua@gmail.com)
NOTE: Much of the code is based on insights from the
work of the user named ComputerNerd.
NOTE: OV7670 SCCB interface does't work if XCLK not provided.
** Thanks to all the android forums and stack exchange answers. :)
*/

/*Modified by Nyameaama Gambrah*/

#define OUTPUT_PIN 0
class FlightRec {
    private:
        const int CS1 = 4;
        bool CAM1_EXIST = false; 
        Init setup;
       
    private:
        char *ConstructFileName(int k,char str[28]); 
        
        void XCLK_SETUP(void);

        void TWI_SETUP(void);

        void OV7670_PINS(void);

        void QVGA_Image(String title);

    public: 
        FlightRec();

       //uint8_t SavetoSD(uint32_t length,ArduCAM myCAM);

        void camCapture(String FileName);


};

#endif