#ifndef IGN
#define IGN

#include<Arduino.h>

#define IGNITE_PIN 0

class IGNITE {
    public:
        uint8_t igniteBS_motor();

        uint8_t igniteLS_motor();


};


#endif