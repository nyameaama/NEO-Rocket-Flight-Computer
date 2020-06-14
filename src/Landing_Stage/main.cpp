#include"main_bridge.h"

#define FLIGHT_STATE 0

//limCalcs
String launch_time;
boolean has_launched = false;

//Path
double xF_pathData[1024][2];
double xF_FCoordinates[64];
void adjustHeadingHelper(double orientVals[2]);
//Variable to store the index of the most recent valid heading and Altitude path point;
uint8_t HcurrentIndex;
uint8_t AcurrentIndex;
double flightDistance;
double *xF_apPoints;

void InterruptServiceRoutine();


void setup(){
    //If button is held for 5 seconds computer will brick all processes
    interrupts();
    attachInterrupt(digitalPinToInterrupt(0),InterruptServiceRoutine,HIGH);
    #if FLIGHT_STATE == 0 //<-- Startup Idle
        sw.startupRoutine();
        #undef FLIGHT_STATE
        #define FLIGHT_STATE 1
    #endif
  
    #if FLIGHT_STATE == 1 //<-- Pad Idle 
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
    //Listen to ground station for flight data (GPS Dest loc) through RF

    //Compute Path to dest
    double FINAL_LAT = sys.GET_LATITUDE(xF_FCoordinates);
    double FINAL_LONG = sys.GET_LONGITUDE(xF_FCoordinates);
    //double *pInitPoints = pInit.generate_path_points(tel.GPS_LOC(1),tel.GPS_LOC(2),FINAL_LAT,FINAL_LONG);
    //pInit.generate_path_points_helper(pInitPoints);
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
            ring.blink(1);
            ring.playTone();
        }
    }else{
        //Check passed. Continue to launch
    }
    //Launch signal
    //10 sec wait before launch
    delay(10000);
    //Check for next flight state - Launch Detect
    if(sw.checkforLaunch()){
        #undef FLIGHT_STATE
        #define FLIGHT_STATE 2
        has_launched = true;
    }else{
        //Do nothing 
    }

    #endif

}

void loop(){
    #if FLIGHT_STATE == 2 //<--  Launch
    //Begin navigation with active thrust Vectoring
    control.state(VECTOR_STATE);
    control.VECTOR_MOUNT_STATE(BOOST_STAGE);

    //Begin fin based active roll stabilization
    stab.rollStabilize(stat.AccGyroVals(1));
    //Check for next flight state - Detect MECO by acceleration differential
    if(sw.checkforMECO()){
        #undef FLIGHT_STATE
        #define FLIGHT_STATE 3
    }else{

    }
    #endif

    #if FLIGHT_STATE == 3 //<-- MECO/Eject
    //Compute approximate time till Apogee
    if(sw.checkforApogeee()){
        #undef FLIGHT_STATE
        #define FLIGHT_STATE 4
    }else{

    }
    //Begin fin based path navigation
    control.state(FIN_STATE);
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
    control.state(FIN_STATE);
    //Check for next flight state
    if(sw.checkforPropulsion_begin()){
        #undef FLIGHT_STATE
        #define FLIGHT_STATE 6
    }
    #endif
    
    #if FLIGHT_STATE == 6  //<-- Motor Burn/Propulsive Land
    // Continue fin based active roll stabilization
    stab.rollStabilize(stat.AccGyroVals(1));
    //Ignite Motor

    //Begin navigation with active thrust Vectoring
    control.state(VECTOR_STATE);
    control.VECTOR_MOUNT_STATE(LANDING_STAGE);
    //Check for successful landing
    if(sw.checkforSuccessLand()){
        #undef FLIGHT_STATE //<-- Come back
        #define FLIGHT_STATE 7
    }
    #endif

     #if FLIGHT_STATE == 7 //<-- Land
    // Continue fin based active roll stabilization
    stab.rollStabilize(stat.AccGyroVals(1));


     #endif
    //Continuous Processes
    //Send flight state data to ground station
    comm.RF_SEND("VEL",String(tel.AirspeedVal()));
    comm.RF_SEND("ALT",String(tel.altimeter()));
    comm.RF_SEND("PIT",String(stat.AccGyroVals(2)));
    comm.RF_SEND("YAW",String(stat.AccGyroVals(3)));

    //Continue Flight State SD storage 
    String VelID = "6C298Y3";
    String AltID = "67U34PO";
    String PitchID = "376FG0T";
    String YawID = "7GN31Q0";
    sav.FOREIGN_LOG(AltID,tel.altimeter());
    sav.FOREIGN_LOG(VelID,tel.AirspeedVal());
    sav.FOREIGN_LOG(PitchID,stat.AccGyroVals(2));
    sav.FOREIGN_LOG(YawID,stat.AccGyroVals(3));
    //Check flight State to see if orientation is in bounds else 
    //begin emergency routine
    if(lD.checkState()){
        lD.BRICK_ALL_PROCESSES();
    }
}

//If button is held for 5 seconds computer will brick all processes
void InterruptServiceRoutine(){
    ring.PIN_HOLD_DOWN();
}
