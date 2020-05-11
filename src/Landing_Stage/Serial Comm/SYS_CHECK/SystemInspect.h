#ifndef SYS
#define SYS

#include<Arduino.h>
#include<SoftwareSerial.h>
#include"../../Sensors/sensors.h"
#include"../../Inertial Measurement/IMU.h"
#include"../../MicrocontrollerComm/BT.h"

class Inspect {
    public:
        boolean altitudeCheck();

        boolean velocityCheck();

        boolean IMU_ProcessCheck();

        boolean GPSCheck();

        boolean BTCheck();

        boolean RFCheck();

        boolean SDCheck();


};

#endif