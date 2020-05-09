#include"main_bridge.h"

#define FLIGHT_STATE 1

//limCalcs
String launch_time;
uint8_t has_launched = 0;

//Data
uint16_t alt_address,vel_address,pitch_address,yaw_address;
uint16_t addr,eepromCycle;
uint8_t fData();

//ControlSystems
void axisCorrect(uint8_t mov1,uint8_t mov2);

//Path
double xF_pathData[1024][2];
double xF_FCoordinates[64];
void adjustHeadingHelper(double orientVals[2]);
//Variable to store the index of the most recent valid heading and Altitude path point;
uint8_t HcurrentIndex;
uint8_t AcurrentIndex;
double flightDistance;
double *xF_apPoints;


//FileSys
uint8_t FileBridge();


void setup(){
    Serial.begin(9600);
    char *function = string.prompt();
    char *stat = string.prompt();
    string.parse_comm(function);
    Serial.print("SETUP COMPLETE?");
    if(stat == "N"){
        setup();
    }else if(stat == "Y"){
        Serial.println("FLIGHT STATS");
    }
    
    //SET LAUNCH
    sys.TEST_SYS();
    //30 sec wait before launch
    delay(30000);

}

void loop(){
    #if FLIGHT_STATE == 1
    //Listen to ground station for flight data (GPS Dest loc) through RF

    //Compute Path to dest
    double FINAL_LAT = sys.GET_LATITUDE(xF_FCoordinates);
    double FINAL_LONG = sys.GET_LONGITUDE(xF_FCoordinates);
    double *pInitPoints = pInit.generate_path_points(tel.GPS_LOC(1),tel.GPS_LOC(2),FINAL_LAT,FINAL_LONG);
    pInit.generate_path_points_helper(pInitPoints);
    flightDistance = pInit.distance_lat_long(tel.GPS_LOC(1),tel.GPS_LOC(2),FINAL_LAT,FINAL_LONG);
    xF_apPoints = pInit.generate_alt(tel.altimeter(),pInit.peak_altitude(flightDistance));
    //Test Microcontroller Bluetooth communication

    //Perform system check (Landing stage and Boost Stage)

    //Launch signal

    //Check for next flight state - Launch Detect
    double *elaps = obj3.timeElapsed();
    double *ret = obj3.velChange();
    if(lD.launch_detect(tel.altimeter(),elaps[2],ret[0],ret[1]) != 1){
        #undef FLIGHT_STATE
        #define FLIGHT_STATE 2
    }else{
        //Do nothing 
    }     
    #endif
    
    #if FLIGHT_STATE == 2
    //Begin navigation with actuve thrust Vectoring

    //Begin fin based active roll stabilization

    //Check for next flight state - Detect MECO by acceleration differential
    if(lD.analyseAltDecceleration()){
        #undef FLIGHT_STATE
        #define FLIGHT_STATE 3
    }else{

    }
    #endif

    #if FLIGHT_STATE == 3
    //Compute approximate time till Apogee
    if(lD.time_to_Apogee() == 0){
        #undef FLIGHT_STATE
        #define FLIGHT_STATE 4
    }else{

    }
    //Begin fin based path navigation

    //Continue fin based active roll stabilization

    //wait for Boost stage ejection signal

     #endif

    #if FLIGHT_STATE == 4


    #endif

    #if FLIGHT_STATE == 5



    #endif
    //Continuous Processes
    //Send flight state data to ground station

    //Continue Flight State SD storage 

}
//Control Systems
void axisCorrect(uint8_t mov1,uint8_t mov2){
    int *translate = change.translate_to_servo(mov1,mov2);
    //Gimbal will thrust opposite to the axis misdirection, correcting orientation and direction
	//By using the negative axis - servo translated value, gimbal can thrust opposite to direction of movement
	//Vector
    uint8_t *servoPos = thrust.thrustVector(-(translate[1]),-(translate[0]));
    thrust.multithreadServo(servoPos[0],servoPos[1]);
}

uint8_t fData(){
    inf.Flight_Data_Save(alt_address,vel_address,pitch_address,yaw_address,tel.altimeter(),tel.AirspeedVal(),stat.AccGyroVals(2),stat.AccGyroVals(3),eepromCycle,addr);
    return 1;
}

uint8_t FileBridge(){
    //Send data to file    
    sav.VELOCITY_RECORD(tel.AirspeedVal());
    sav.ALTITUDE_RECORD(tel.altimeter());
    sav.PITCH_RECORD(stat.AccGyroVals(2));
    sav.YAW_RECORD(stat.AccGyroVals(3));
    //transmit data through RF
    //teld Flight Data
    FileSystem data;
    char* Vdatateld = "VELdata";
    char* Adatateld = "ALTdata";
    char* Pdatateld = "PITCHdata";
    char* Ydatateld = "YAWdata";
    /*String data[4][4] = {{"VELdata",String(tel.AirspeedVal())},
                         {"ALTdata",String(tel.altimeter())},
                         {"PITCHdata",String(stat.AccGyroVals(2))},
                         {"YAWdata",String(stat.AccGyroVals(3))}};*/
    //ExCommunication comm;
    //comm.transmit(Vdatateld);
}

//Path
void adjustHeadingHelper(double orientVals[2]){
    thrust.thrustVector(orientVals[0],orientVals[1]);
}