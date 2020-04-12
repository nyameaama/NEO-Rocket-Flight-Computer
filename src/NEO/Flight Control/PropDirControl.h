#include<stdint.h>
#include<stddef.h>
#include<Arduino.h>

#define HIGH 1
#define LOW 0

//Propeller Thrust Rate Control
//When each of the 4 propellers velocity is adjusted, it causes a change in direction of the craft
//Using this our primary control means we can adjust the direction of yaw movement

class PropThrustControl {
    public:
        void propeller(uint8_t inputL1,uint8_t inputL2);




};