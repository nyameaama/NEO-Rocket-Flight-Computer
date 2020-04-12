#include"bridge.h"

//limCalcs
String launch_time;
uint8_t has_launched = 0;
double *timeElapsed();
double *velChange();

//Data
uint16_t alt_address,vel_address,pitch_address,yaw_address;
uint16_t addr,eepromCycle;
uint8_t fData();

//ControlSystems
uint8_t currentM1; // Current degrees for motor M1 and M2
uint8_t currentM2; 
Servo M1,M2;
uint8_t M2_reading,M1_reading;
void Motor1_Move();
void Motor2_Move();
void multithreadServo(uint8_t x,uint8_t y);
void propeller(uint8_t inputL1,uint8_t inputL2);
void axisCorrect(uint8_t mov1,uint8_t mov2);

//Command
#define LAUNCHCONFIRM 1
char comm_byte;
char comm_str[32];
void SDisplay(char x);
void IDisplay(uint32_t x);
char *prompt();

//Path
double xF_pathData[1024][2];
double xF_FCoordinates[64];
void adjustHeadingHelper(double orientVals[2]);
double copyELements(double array[1024][2],double arr[][2],uint8_t arrlength);
double arrayConversion1D_2D(double array[64]);
//Variable to store the index of the most recent valid heading and Altitude path point;
uint8_t HcurrentIndex;
uint8_t AcurrentIndex;
double flightDistance;
double *xF_apPoints;

//Sensors
uint8_t UltrasonicSensor1[3] = {};

//FileSys
uint8_t FileBridge();


void setup(){
    Serial.begin(9600);
    Command_Word_Break string;
    SYS_FUNCTIONS sys;
    char *function = prompt();
    char *temp = prompt();
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
    //uint32_t length;
    double FINAL_LAT = sys.GET_LATITUDE(xF_FCoordinates);
    double FINAL_LONG = sys.GET_LONGITUDE(xF_FCoordinates);
    double *hpPoints = hp.generate_path_points(tel.GPS_LOC(1),tel.GPS_LOC(2),FINAL_LAT,FINAL_LONG);
    arrayConversion1D_2D(hpPoints);
   // double *Fdata = sys.COMPILED_FLIGHT_DATA();
    flightDistance = hp.distance_lat_long(tel.GPS_LOC(1),tel.GPS_LOC(2),FINAL_LAT,FINAL_LONG);
    xF_apPoints = hp.generate_alt(tel.altimeter(),hp.peak_altitude(flightDistance));
    //SET LAUNCH
    sys.TEST_SYS();
    //1 sec wait before launch
    delay(30000);

}

void loop(){
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
    double *elaps = timeElapsed();
    double *ret = velChange();
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
    multithreadServo(servoPos[0],servoPos[1]);
}
void Motor1_Move(){
	M1.write(M1_reading);
}
void Motor2_Move(){
	M2.write(M2_reading);
}
void multithreadServo(uint8_t x,uint8_t y){
	//Thread Controller to control Threads		
	ThreadController control = ThreadController();
	//Servo #1 thread
	Thread servo1 = Thread();
	//Servo #2 thread
	Thread servo2 = Thread();
	//Configure Servo #1 thread
	//Interval set to 10ms
	servo1.onRun(Motor1_Move);
	servo1.setInterval(10);
	//Configure Servo #2 thread
	//Interval set to 10ms
	servo2.onRun(Motor2_Move);
	servo2.setInterval(10);
	//Add both threads to thread controller
	control.add(&servo1);
	control.add(&servo2);
	//Thread controller will run both threads based on interval
	control.run();
 }
 void propeller(uint8_t inputL1,uint8_t inputL2) {
 	//Motor Left (Direction - clockwise)
	digitalWrite(inputL1, HIGH);
	digitalWrite(inputL2, LOW);
}

//limCalcs
double *timeElapsed(){
    Sensors sp;
    double time[3];
    double readings[2];
	double startTime,endTime,elapsed;
	startTime = micros();
	for(size_t i = 0; i < 2;i++){
		readings[i] = sp.AirspeedVal();
	}
    time[0] = readings[0];
    time[1] = readings[1];
	endTime = micros();
	elapsed = (endTime - startTime);
    time[2] = elapsed;
    return time;
}

double *velChange(){
    double ret[2];
    double *vel = timeElapsed();
    double vel_change,acc_change;
    vel_change = vel[1] - vel[0];
    ret[0] = vel_change;
	acc_change = vel_change / vel[2];
    vel[1] = acc_change;
    return ret;
}
//Command
 //Display Strings
void SDisplay(char x){
    Serial.println(x);
}
//Display Integers
void IDisplay(uint8_t x){
   Serial.println(x);
}
char *prompt(){
    char comm_byte;
    char comm_str[32];
     //Call prompt
  //Read characters from Serial Monitor
  Command_Word_Break string;
  uint8_t comm_index;
  while(comm_byte != '\n'){
    if (Serial.available() > 0) {  
        comm_byte = Serial.read();// get the character
    }
    if (comm_byte != '\n') {
      // a character of the string was received
      comm_str[comm_index] = comm_byte;
      comm_index++;
    }
    else{
      // end of string
      //string.parse_comm(functionParam);
      /*if(string.parse_comm(comm_str) != LAUNCHCONFIRM){
        setup();
      }*/
    }
  }                   
    return comm_str;
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
//Function to copy all elements in one array to another
double copyELements(double array[1024][2],double arr[][2],uint8_t arrlength){
    //double tempArr[1024][2];
	for(size_t i = 0;i < arrlength;i++){
		arr[i][0] = array[i][0];
		arr[i][1] = array[i][1];
    }

    return 1;
}
double arrayConversion1D_2D(double array[64]){
    //double temp2[64][64];
    for(size_t i = 0; i < 64;i += 2){
        array[i] = xF_pathData[i][i+1];
    }
            
 }