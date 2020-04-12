#include<stdint.h>
#include<stddef.h>
#define NULL 0

class Command_Word_Break {
    private:
        uint8_t string_len(char x[64]);

        char ERROR(uint8_t type);

    public:
        char verify(char x[]);

        uint8_t parse_comm(char stringV[]);

        char subrootAnalyzer(char y[]);

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