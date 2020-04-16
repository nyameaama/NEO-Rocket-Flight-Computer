#include"bridge.h"

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
    Command_Word_Break string;
    SYS_FUNCTIONS sys;
    char *function = string.prompt();
    char *temp = string.prompt();
    string.parse_comm(function);
    Serial.print("SETUP COMPLETE?");
    if(temp == "N"){
        setup();
    }else if(temp == "Y"){
        Serial.println("FLIGHT STATS");
    }
    //Set Path
    Sensors tel;
    PathCompute hp;
    Utility funcs;
    //uint32_t length;
    double FINAL_LAT = sys.GET_LATITUDE(xF_FCoordinates);
    double FINAL_LONG = sys.GET_LONGITUDE(xF_FCoordinates);
    double *hpPoints = hp.generate_path_points(tel.GPS_LOC(1),tel.GPS_LOC(2),FINAL_LAT,FINAL_LONG);
    hp.generate_path_points_helper(hpPoints);
   // double *Fdata = sys.COMPILED_FLIGHT_DATA();
    flightDistance = hp.distance_lat_long(tel.GPS_LOC(1),tel.GPS_LOC(2),FINAL_LAT,FINAL_LONG);
    xF_apPoints = hp.generate_alt(tel.altimeter(),hp.peak_altitude(flightDistance));
    //SET LAUNCH
    sys.TEST_SYS();
    //1 sec wait before launch
    delay(30000);

}

void loop(){
    //Objects
 //Object for sensors class
    Sensors obj;
    //Object for Gyro class
    Gyro obj2;
    //Object for RPY_CHECK class
    RPY_CHECK obj3;
    //Object for AreaAnalysis class
    AreaAnalysis lD;
    //Object for PathCompute class
    PathCompute pInit;
    FileSystem sav;
    //Launch Detect
    double *elaps = obj3.timeElapsed();
    double *ret = obj3.velChange();
    if(lD.launch_detect(obj.altimeter(),elaps[2],ret[0],ret[1]) != 1){
        //Pre - Launch
    }else{
        //Define Launch Time
        String*time = sav.GET_TIME();
        launch_time = time[3];
        has_launched = 1;
        //Check functions
        uint8_t mov1,mov2,mov3;
        double standardPitchval = 87;   
        double standardYawval = 0; 
        Gyro stat;
        if(obj3.pitch_range(stat.AccGyroVals(2),standardPitchval) != 0){
            axisCorrect(mov1,mov2);
        }else if(obj3.yaw_range(stat.AccGyroVals(3),standardYawval) != 0){
            axisCorrect(mov1,mov2);
        }
    }
    //pInit.pathController(4.6,5.8,20.4,&xF_pathData);
    //Record Flight Data
    FileBridge();
}
//Control Systems
void axisCorrect(uint8_t mov1,uint8_t mov2){
    VectorCompute change;
    int *translate = change.translate_to_servo(mov1,mov2);
    //Gimbal will thrust opposite to the axis misdirection, correcting orientation and direction
	//By using the negative axis - servo translated value, gimbal can thrust opposite to direction of movement
	//Vector
	Control thrust;
    uint8_t *servoPos = thrust.thrustVector(-(translate[1]),-(translate[0]));
    thrust.multithreadServo(servoPos[0],servoPos[1]);
}

uint8_t fData(){
    Data inf;
    Sensors sen;
    Gyro temp;
    inf.Flight_Data_Save(alt_address,vel_address,pitch_address,yaw_address,sen.altimeter(),sen.AirspeedVal(),temp.AccGyroVals(2),temp.AccGyroVals(3),eepromCycle,addr);
    return 1;
}

uint8_t FileBridge(){
    FileSystem rec;
    Sensors sen;
    Gyro temp;
    //Send data to file    
    rec.VELOCITY_RECORD(sen.AirspeedVal());
    rec.ALTITUDE_RECORD(sen.altimeter());
    rec.PITCH_RECORD(temp.AccGyroVals(2));
    rec.YAW_RECORD(temp.AccGyroVals(3));
    //transmit data through RF
    //Send Flight Data
    FileSystem data;
    char* VdataSend = "VELdata";
    char* AdataSend = "ALTdata";
    char* PdataSend = "PITCHdata";
    char* YdataSend = "YAWdata";
    /*String data[4][4] = {{"VELdata",String(sen.AirspeedVal())},
                         {"ALTdata",String(sen.altimeter())},
                         {"PITCHdata",String(temp.AccGyroVals(2))},
                         {"YAWdata",String(temp.AccGyroVals(3))}};*/
    //ExCommunication comm;
    //comm.transmit(VdataSend);
}

//Path
void adjustHeadingHelper(double orientVals[2]){
    Control system;
    system.thrustVector(orientVals[0],orientVals[1]);
}