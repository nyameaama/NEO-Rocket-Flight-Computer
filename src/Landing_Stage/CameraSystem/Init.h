#ifndef INITOV7670
#define INITOV7670

#include <Wire.h>
#include <SD.h>
/*
OV7670 Camera module with SD card module
on Arduino Uno.
 
Author: Hardik Kalasua (hardik.kalasua@gmail.com)
NOTE: Much of the code is based on insights from the
work of the user named ComputerNerd.
NOTE: OV7670 SCCB interface does't work if XCLK not provided.
** Thanks to all the android forums and stack exchange answers. :)
*/

class Init {
    public:
        int CS_Pin = 10;
        
    public:
        void Init_YUV422();

        void Init_QVGA();

        void Init_OV7670();

        void WriteOV7670(byte regID, byte regVal);

        void ReadOV7670(byte regID);

};

#endif