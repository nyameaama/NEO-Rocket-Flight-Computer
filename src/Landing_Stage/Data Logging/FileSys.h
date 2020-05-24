#ifndef FileSys
#define FileSys

#include<SPI.h>
#include"SD.h"
#include"LRM.h"
#include"time.h"
#include"../utility/ErrorDump.h"

#define ERROR 0
#define SUCCESS 1
#define TRUE 1
#define FALSE 0
#define PASS 1
#define FAIL 0
#define  PIN_OUTPUT 0

class FileSystem {
    public:
        FileSystem();
        ~FileSystem();
        
    public:
        String *PrIDS = (String*)malloc(16);
        uint8_t DataLogRate;
        uint16_t Activity;
        uint16_t ApproxFlightDuration;
        File DataFILE;
        SdFile root;

    private:
        template <typename FC>
        boolean compare(FC x, FC y);

        double TimeHelper(double x);

        uint8_t WRITE_TO_FILE(String x,String tag);

        String toString(uint32_t num);

        uint8_t parse(String x);

        uint8_t *confirmPID(String x);

        uint8_t fileHandler(String PID);

        uint8_t FILE_LOG(String x,String PID);

        void ACTIVITY_LOG();

         String formatToData(String PID,String data);

    public:
        String *GET_TIME();

        uint8_t FOREIGN_LOG(String PID,double x);

        uint8_t FOREIGN_READ(String PID,String searchParam);


}; 

#endif   