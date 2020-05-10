#ifndef RECEIVE
#define RECEIVE

class RecRF {
    public:
        String fileReceive(){
            RH_ASK driver;
            uint8_t buf[12];
            uint8_t buflen = sizeof(buf);
            if (driver.recv(buf, &buflen)){ // Non-blocking
                return String((char*)buf);
            }    
        }

}

#endif