#ifndef InertialMeasurement
#define InertialMeasurement
#include<Wire.h>
#include<math.h>
#include"Arduino.h"

class Gyro {
	/*Gyro() {
	 	Serial.begin(19200);
  		Wire.begin();                      // Initialize comunication
  		Wire.beginTransmission(MPU);       // Start communication with MPU6050 // MPU=0x68
  		Wire.write(0x6B);                  // Talk to the register 6B
  		Wire.write(0x00);                  // Make reset - place a 0 into the 6B register
  		Wire.endTransmission(true);        //end the transmission
	}*/
	private:
		const uint8_t MPU = 0x68;
		float AccX, AccY, AccZ;
		float GyroX, GyroY, GyroZ;
		float accAngleX, accAngleY, gyroAngleX, gyroAngleY, gyroAngleZ;
		float AccErrorX, AccErrorY, GyroErrorX, GyroErrorY, GyroErrorZ;
		float elapsedTime, currentTime, previousTime;
		uint32_t c = 0;
	public:
		float roll, pitch, yaw;
										//Gyro = 1  Accel = 2
	private:
		double calculate_IMU_error(uint8_t SENSOR,uint8_t XY_ERROR);

    public:
        double AccGyroVals(uint8_t SenData);
        
};            
#endif