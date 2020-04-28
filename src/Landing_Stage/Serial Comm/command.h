#ifndef Command
#define Command

#include<stdint.h>
#include<stddef.h>
#include<Arduino.h>
#include"../utility/ErrorDump.h"
#define NULL 0
#define LAUNCHCONFIRM 1

class Command_Word_Break {
    private:
        char comm_byte;
        char comm_str[32];
        

    private:
        uint8_t string_len(char x[64]);

        //char ERROR(uint8_t type);
        
        void SDisplay(char x);

        void IDisplay(uint8_t x);

    public:
        char verify(char x[]);

        uint8_t parse_comm(char stringV[]);

        char subrootAnalyzer(char y[]);

        char *prompt();
};

class SYS_FUNCTIONS {
    //Flight Data Functions
    public:
        double *COMPILED_FLIGHT_DATA();

        double GET_LATITUDE(double *xF_FCoordinates);

        double GET_LONGITUDE(double *xF_FCoordinates);

        uint8_t ADD_COORDINATES(double x,double y,double *xF_FCoordinates);

        uint8_t ADD_ALTITUDE(double newAlt,double *xF_altitude);

        void CLEAR_F_DATA(double *xF_FCoordinates,double *xF_altitude);

        //Testing Functions
        uint8_t TEST_SYS();

        //Launch Functions
        uint8_t LAUNCH_DATA();
};

#endif        