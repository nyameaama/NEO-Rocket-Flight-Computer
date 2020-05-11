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

}

boolean Inspect::SDCheck(){

}
