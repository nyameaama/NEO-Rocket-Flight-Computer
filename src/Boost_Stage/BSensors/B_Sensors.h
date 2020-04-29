#ifndef BSENSORS
#define BSENSORS

#include<Arduino.h>
#include<Adafruit_BMP085.h>

class BSensors {
    public:
        //Function retrns altitude in meters
	    uint32_t BS_altimeter();

};

#endif