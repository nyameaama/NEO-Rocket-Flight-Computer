#include<Arduino.h>
#include<EEPROM.h>
//#include"Sensors/sensors.h"
#include"Inertial Measurement/IMU.h"
#include"Flight Control/Stability System/AxisStability.h"  //<-- Sensors.h 
#include"Flight Control/TVC.h"
#include"Serial Comm/command.h"
#include"Navigation/PathCompute.h"
#include"Navigation/PathControl.h"
#include"Data Logging/FileSys.h"
#include"RF Comm/ExCommunication - Transmit.cpp"
#include"Data Logging/EEPROMStorage.h"
#include"Flight Control/ThrustRegulation/PropThrustControl.h"
#include<Servo.h>
#include<stdlib.h>


    //Object for sensors class
    Sensors tel;
    //Object for Gyro class
    Gyro stat;
    //Object for RPY_CHECK class
    RPY_CHECK obj3;
    //Object for AreaAnalysis class
    AreaAnalysis lD;
    //Object for PathCompute class
    PathCompute pInit;
    //Object for FileSystem class
    FileSystem sav;
    //Object for Command_Word_Break class
    Command_Word_Break string;
    //Object for SYS_FUNCTIONS class
    SYS_FUNCTIONS sys;
    //Object for VectorCompute class
    VectorCompute change;
    //Object for Control class
    Control thrust;
    //Object for Data class
    Data inf;