# NEO-Rocket Flight Computer

### Description:

NEO-Rocket Flight Computer is an experimentally based ATmega2560 microcontroller based model rocket.

The aim for this project is to create a a fully stacked two stage independent flight system fitted with autonomous GPS point to point navigation, deviation monitoring and control, data logging,and vertical takeoff and landing support. Rocket comprises
of two stages: High Power Boost Stage and Propulsive Landing Stage. This program is developed in conjunction with the PlatformIO IDE system with integration into VSCode. 

### Features:

#### High Power Boost Stage

##### This Stage powers the fully stacked rocket up to apogee where it deploys the landing stage away for its independent landing system. The boost stage uses parachutes to safely bring it to the ground.

* High Power Propulsion
* Parachute landing

#### Propulsive Landing Stage

##### This stage is deployed where it uses fins to control roll, pitch and yaw during descent and thrust vectoring to control rocket direction when landing. A suicide burn is used to slow the stage down and land.

* Support for vertical landing,
* Active Flight Data Logging,
* GPS based navigation.

## Avionics

### Boost Stage

*  ATmega328P microcontroller (Arduino Uno Development Board)
*  Altimeter (Adafruit_BMP085) -> pressure
*  HC-05 Bluetooth Module (Slave)


### Landing Stage

* ATmega2560 microcontroller (Custom PCB)
* Altimeter (Adafruit_BMP085)
* MPU6050 IMU 
* MPXV7002DP - Airspeed
* ArduCam
* HC-06 Bluetooth Module (Master)
* NEO-6M GPS module
* RF 433MHz Transmitter/Receiver modules

# Contribution

You can fork this repository to introduce new features, changes or bug fixes and create a pull request to merge with master. This repository can be cloned at https://github.com/nyameaama/NEO-Rocket-Flight-Computer. 

# Documentation

The flight program for the project is written in C++. 


## Program Structure

### Landing Stage

* The Landing stage microcontroller is the main controller with the boost controller being a sub controller. It uses Bluetooth(HC-05, HC-06 ) to communicate with boost stage microcontroller to control Boost Stage Thrust Vectoring. The boost stage controller only independently handles its parachute deployment.

#### Data Logging Module
* EEPROM storage
* SD storage

#### Flight Control Module
* Axis Stability System
* Thrust Vector Control

#### Inertial Measurement
* Axis Values(X,Y,Z)
* Calculate pitch,yaw and roll from IMU

#### Flight Navigation Module
* Active Path Planning
* Path Deviation Control

#### RF Communication Module
* [EXPERIMENTAL COMMUNICATION WITH GROUND STATION]

#### Sensor Module
* Interface GPS,altimeter,airspeed

### Boost Stage 

#### Communication Module
* Recieve commands from landing Stgae
* Log Data (Errors)
* Send ejection trigger

#### Trigger Module
* Compute decceleration to send ejection trigger
* Detect altitude for chute deployment

#### Sensor Module
* Interface altimeter




