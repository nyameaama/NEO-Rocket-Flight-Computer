#ifndef SYS
#define SYS

#include<Arduino.h>
#include<SoftwareSerial.h>
#include<SPI.h>
#include"SD.h"
#include"RH_ASK.h"
#include"../../Sensors/sensors.h"
#include"../../Inertial Measurement/IMU.h"
#include"../../MicrocontrollerComm/BT.h"

#define  PIN_OUTPUT 0

class Inspect {
    public:
        boolean altitudeCheck();

        boolean velocityCheck();

        boolean IMU_ProcessCheck();

        boolean GPSCheck();

        boolean BTCheck();

        boolean RFCheck();

        boolean SDCheck();

        String *InspectMain();
};

#endif