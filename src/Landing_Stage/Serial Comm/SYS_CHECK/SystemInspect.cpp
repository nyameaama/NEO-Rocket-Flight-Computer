#include"SystemInspect.h"

 boolean Inspect::altitudeCheck(){
     Sensors alt;
     return (alt.altimeter() != 0.00) ? true : false;
 }

boolean Inspect::velocityCheck(){
    Sensors vel;
    return (vel.AirspeedVal() != 0.00) ? true : false;
}

boolean Inspect::IMU_ProcessCheck(){
    Gyro get;
    boolean pitchState,yawState,rollState;
    pitchState = (get.AccGyroVals(2) != 0.00) ? true : false;
    yawState = (get.AccGyroVals(3) != 0.00) ? true : false;
    rollState = (get.AccGyroVals(1) != 0.00) ? true : false;
    if((pitchState) && (yawState) && (rollState)){
        return true;
    }else{
        return false;
    }
}

boolean Inspect::GPSCheck(){
    Sensors gpsData;
    boolean state;
    static const uint8_t RXPin = UNDEFINED, TXPin = UNDEFINED;
	static const uint32_t GPSBaud = 9600;
    SoftwareSerial GPSserial(RXPin, TXPin);
	GPSserial.begin(GPSBaud);
    state = (GPSserial.available() <= 0) ? true : false;
    return state;
}

boolean Inspect::BTCheck(){
    BT_Comm btGet;
    static const uint8_t RX= UNDEFINED, TX = UNDEFINED;
    SoftwareSerial BlueTSerial(RX, TX); // RX | TX
    BlueTSerial.begin(38400);
    return (BlueTSerial.available() <= 0) ? true : false;
}

boolean Inspect::RFCheck(){
    //RH_ASK drV;
    //return (!drV.init()) ? false : true;
}

boolean Inspect::SDCheck(){
    return (!SD.begin(PIN_OUTPUT)) ? false: true;
}

String *Inspect::InspectMain(){
    uint8_t size = 7,count;
    uint8_t *temp = (uint8_t*)malloc(size);
    uint8_t *temp2 = (uint8_t*)malloc(size);
    String *PNames = (String*)malloc(7);
    String *strReturn = (String*)malloc(5);
    //Descriptions
    PNames[0] = "Altitude Module Error";
    PNames[1] = "Velocity Module Error";
    PNames[2] = "IMU Module Error";
    PNames[3] = "GPS Module Error";
    PNames[4] = "Bluetooth Module Error";
    PNames[5] = "RF Module Error";
    PNames[6] = "SD Module Error";
    uint8_t altitude,velocity,IMU,GPS,bT,RF,SD;
    //Check to see if functions return 1(denoting fail).If 
    //fail return the errors with their description
    temp[0] = altitude = (altitudeCheck()) ? 0 : 1;
    temp[1] = velocity = (velocityCheck()) ? 0 : 1;
    temp[2] = IMU = (IMU_ProcessCheck()) ? 0 : 1;
    temp[3] = GPS = (GPSCheck()) ? 0 : 1;
    temp[4] = bT = (BTCheck()) ? 0 : 1;
    temp[5] = RF = (RFCheck()) ? 0 : 1;
    temp[6] = SD = (SDCheck()) ? 0 : 1;
    for(size_t i = 0; i < size;i++){
        if(temp[i] == 1){
            temp2[count] = i;
            count++;
        }
    }
    realloc(temp2,count);
    for(size_t j = 0;j < count;j++){
        strReturn[j] = PNames[temp2[j]];
    }
    return strReturn;

}
