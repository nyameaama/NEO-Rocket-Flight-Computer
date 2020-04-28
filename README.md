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

##### This stage is deployed where it uses fins to control roll and thrust vectoring to control rocket direction when landing. A suicide burn is used to slow the stage down and land.

* Support for vertical landing,
* Active Flight Data Logging,
* GPS based navigation.

## Avionics

### Boost Stage

*  ATmega2560 microcontroller
*  Altimeter (Adafruit_BMP085) -> pressure


### Landing Stage

* ATmega2560 microcontroller
* Altimeter (Adafruit_BMP085)
* MPU6050 IMU 
* MPXV7002DP
* ArduCam


# Contribution

You can fork this reposirtory to introduce new features, changes or bug fixes and create a pull request to merge with master. This repository can be cloned at https://github.com/nyameaama/NEO-Rocket-Flight-Computer. 

# Documentation

The flight program for the project is written in C++. 


## Program Structure

### Landing Stage

* The Landing stage microcontroller is the main controller with the boost controller being a sub controller. It uses I2C to communicate with boost stage microcontroller to control Boost Stage Thrust Vectoring. The boost stage controller only independently handles its parachute deployment.

#### Data Logging Module
* EEPROM storage
* SD storage

#### Flight Control Module
* Axis Stability System
* Thrust Vector Control

#### Inertial Measurement

#### Flight Navigation Module
* Active Path Planning
* Path Deviation Control

#### RF Communication Module

#### Sensor Module

### Boost Stage 



