#ifndef LRM
#define LRM

#include<Arduino.h>
#include<SPI.h>
#include"SD.h"
#include"FileSys.h"

class LogRateManagement {
    private:
        File DataFILE;

    private:
         uint16_t total(double *arr);        
    public:
        double *volume_size_used();

        double getLogRate();

        double logMain();
};

#endif