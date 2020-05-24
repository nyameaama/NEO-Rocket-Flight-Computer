#ifndef LRM
#define LRM

#include<Arduino.h>
#include<SPI.h>
#include"SD.h"
//#include"FileSys.h"

class LogRateManagement {
    private:
        //File DataFILE;

    private:
         uint16_t total(double *arr);

         double getRemainingCapacity();

         double getDiskUsed();

    public:
        double *compileFileSizes();

        double getLogRate();

        template <typename DataType>
        boolean logMain(DataType x);

};

#endif