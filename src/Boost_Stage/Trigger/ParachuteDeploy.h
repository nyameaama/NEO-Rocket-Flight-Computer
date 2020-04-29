#ifndef PARACHUTE
#define PARACHUTE

#include "../BSensors/B_Sensors.h"
#include<Arduino.h>

#define DEPLOY_ALTITUDE 200

class DeployP {
    public:
        boolean detectAlt();

        uint8_t deployChute();

};

#endif