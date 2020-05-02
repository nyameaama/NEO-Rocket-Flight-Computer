#ifndef ERROR_ROUTE
#define ERROR_ROUTE

#include<Arduino.h>
#include"../Microcontroller_Communication/MC_Data_Parse.h"

class ERROR {
    public:
        uint8_t route(String ID);

};

#endif