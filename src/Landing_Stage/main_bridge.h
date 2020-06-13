//Main bridge includes all files and dependencies required by main
//and defines all objects that would be used by main

#include<Arduino.h>
#include<EEPROM.h>
#include"Sensors/sensors.h"
#include"Inertial Measurement/IMU.h"
#include"Flight Control/Stability System/AxisStability.h" 
#include"Flight Control/Stability System/Control Fins//Roll Control/ActiveRollStabilization.h" 
#include"Trigger Systems/AreaAnalysis.h"
#include"Trigger Systems/LED_Buzzer.h"
#include"Trigger Systems/Landing Program/LandProg.h"
#include"Flight Control/Thrust_Vector_Control/TVC.h"
#include"Serial Comm/command.h"
#include"Serial Comm/SYS_CHECK/SystemInspect.h"
#include"Navigation/Nav/PathCompute.h"
#include"Navigation/Guidance/PathControl.h"
#include"Data Logging/FileSys.h"
#include"RF Comm/Transmit/DataHandling/Assign.h"
#include"Data Logging/EEPROM/EEPROMStorage.h"
#include"Flight Control/ThrustRegulation/PropThrustControl.h"
#include"StateMachine/state.h"
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
    //Object for Roll Stability class
    RollStability stab;
    //Object for RF Communication class
    RF_ASSIGN comm;
    //Object for LED_BUZZER class
    LED_BUZZER ring;
    //Object for PathControl class
    PathControl control;
    //Object for StateMachine class
    StateMachine sw;


#define VECTOR_STATE 0
#define FIN_STATE 1
    
#define BOOST_STAGE 0
#define LANDING_STAGE 1