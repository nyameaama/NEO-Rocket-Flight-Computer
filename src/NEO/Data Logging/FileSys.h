#include<SPI.h>
#include"SD.h"
//#include "DateTimeStrings.h"
#include"time.h"
#define ERROR 0
#define SUCCESS 1
#define TRUE 1
#define FALSE 0
#define PASS 1
#define FAIL 0

class FileSystem{
    public:
        FileSystem();
    private:
        String *PrIDS = (String*)malloc(16);
        uint8_t PIN_OUTPUT;
        uint32_t remainingCapacity;
        uint8_t DataLogRate;
        uint16_t Activity;
        uint16_t ApproxFlightDuration;
        File DataFILE;
        SdFile root;

    private:

        boolean compare(String x, String y);

        uint16_t total(double *arr);

        double TimeHelper(double x);

        uint8_t WRITE_TO_FILE(String x,String tag);

        String toString(uint32_t num);

        uint8_t parse(String x);

        double *volume_size_used();

        uint8_t *confirmPID(String x);

        uint8_t fileHandler(String PID);

        uint8_t LogRateManagement(String x,String PID);

        void ACTIVITY_LOG();

        

    public:

         String *GET_TIME();

         String formatToData(String PID,String data);

        uint8_t VELOCITY_RECORD(double vel);

        uint8_t ALTITUDE_RECORD(double alt);

        uint8_t PITCH_RECORD(double pitch);

        uint8_t YAW_RECORD(double yaw);

        uint8_t FOREIGN_LOG(String PID,uint8_t x);

        String FOREIGN_READ(String PID,String searchParam);


};    