#include"main_bridge.h"

#define FLIGHT_STATE 1

//limCalcs
String launch_time;
uint8_t has_launched = 0;

//Data
uint16_t alt_address,vel_address,pitch_address,yaw_address;
uint16_t addr,eepromCycle;
uint8_t fData();


//Path
double xF_pathData[1024][2];
double xF_FCoordinates[64];
void adjustHeadingHelper(double orientVals[2]);
//Variable to store the index of the most recent valid heading and Altitude path point;
uint8_t HcurrentIndex;
uint8_t AcurrentIndex;
double flightDistance;
double *xF_apPoints;


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
   
  
    #if FLIGHT_STATE == 1 //<-- Pad Idle 
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
    String *systemProblems = sys.TEST_SYS();
    //If greater than 1, errors are present
    if(systemProblems[0].toInt() > 1){
        //Send Problems to ground
        
        //Set unbreakable loop and blink LED and buzzer till controller is restarted
        while(true){
            ring.blink();
            ring.playTone();
        }
    }else{
        //Check passed. Continue to launch
    }
    //Launch signal
    //10 sec wait before launch
    delay(10000);
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

}

void loop(){
    #if FLIGHT_STATE == 2 //<--  Launch
    //Begin navigation with actuve thrust Vectoring

    //Begin fin based active roll stabilization
    stab.rollStabilize(stat.AccGyroVals(1));
    //Check for next flight state - Detect MECO by acceleration differential
    if(lD.analyseAltDecceleration()){
        #undef FLIGHT_STATE
        #define FLIGHT_STATE 3
    }else{

    }
    #endif

    #if FLIGHT_STATE == 3 //<-- MECO/Eject
    //Compute approximate time till Apogee
    if(lD.time_to_Apogee() <= 0){
        #undef FLIGHT_STATE
        #define FLIGHT_STATE 4
    }else{

    }
    //Begin fin based path navigation

    //Continue fin based active roll stabilization
     stab.rollStabilize(stat.AccGyroVals(1));
    //wait for Boost stage ejection signal

     #endif

    #if FLIGHT_STATE == 4 //<-- Apogee/ReOrient 
    //Continue fin based active roll stabilization
    stab.rollStabilize(stat.AccGyroVals(1));

    #endif

    #if FLIGHT_STATE == 5 //<-- Controlled Coast
    // Continue fin based active roll stabilization
    stab.rollStabilize(stat.AccGyroVals(1));
    //Continue fin based path navigation

    //Check for next flight state

    #endif
    
    #if FLIGHT_STATE == 6  //<-- Motor Burn/Propulsive Land
    // Continue fin based active roll stabilization
    stab.rollStabilize(stat.AccGyroVals(1));



    #endif

     #if FLIGHT_STATE == 7 //<-- Land


     #endif
    //Continuous Processes
    //Send flight state data to ground station
    comm.RF_SEND("VEL",String(tel.AirspeedVal()));
    comm.RF_SEND("ALT",String(tel.altimeter()));
    comm.RF_SEND("PIT",String(stat.AccGyroVals(2)));
    comm.RF_SEND("YAW",String(stat.AccGyroVals(3)));

    //Continue Flight State SD storage 
    sav.ALTITUDE_RECORD(tel.altimeter());
    sav.VELOCITY_RECORD(tel.AirspeedVal());
    sav.PITCH_RECORD(stat.AccGyroVals(2));
    sav.YAW_RECORD(stat.AccGyroVals(3));
}

//Control Systems
//Path
void adjustHeadingHelper(double orientVals[2]){
    thrust.thrustVector(orientVals[0],orientVals[1]);
}