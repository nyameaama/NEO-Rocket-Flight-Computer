#include<Wire.h>
#include<math.h>
#include"Arduino.h"

//3RD Party code
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
		double calculate_IMU_error(uint8_t SENSOR,uint8_t XY_ERROR) {
  // We can call this funtion in the setup section to calculate the accelerometer and gyro data error. From here we will get the error values used in the above equations printed on the Serial Monitor.
  // Note that we should place the IMU flat in order to get the proper values, so that we then can the correct values
  // Read accelerometer values 200 times
  uint32_t c;
  if(SENSOR == 2){			
  while (c < 200) {
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 6, true);
    AccX = (Wire.read() << 8 | Wire.read()) / 16384.0 ;
    AccY = (Wire.read() << 8 | Wire.read()) / 16384.0 ;
    AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0 ;
    // Sum all readings
    AccErrorX = AccErrorX + ((atan((AccY) / sqrt(pow((AccX), 2) + pow((AccZ), 2))) * 180 / PI));
    AccErrorY = AccErrorY + ((atan(-1 * (AccX) / sqrt(pow((AccY), 2) + pow((AccZ), 2))) * 180 / PI));
    c++;
  }
  //Divide the sum by 200 to get the error value
  AccErrorX = AccErrorX / 200;
  AccErrorY = AccErrorY / 200;
  if(XY_ERROR == 1) {
  	return AccErrorX;
  }	else{
  	return AccErrorY;
  }	
  }
  if(SENSOR == 1) {
  c = 0;
  // Read gyro values 200 times
  while (c < 200) {
    Wire.beginTransmission(MPU);
    Wire.write(0x43);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 6, true);
    GyroX = Wire.read() << 8 | Wire.read();
    GyroY = Wire.read() << 8 | Wire.read();
    GyroZ = Wire.read() << 8 | Wire.read();
    // Sum all readings
    GyroErrorX = GyroErrorX + (GyroX / 131.0);
    GyroErrorY = GyroErrorY + (GyroY / 131.0);
    GyroErrorZ = GyroErrorZ + (GyroZ / 131.0);
    c++;
  }
  //Divide the sum by 200 to get the error value
  GyroErrorX = GyroErrorX / 200;
  GyroErrorY = GyroErrorY / 200;
  GyroErrorZ = GyroErrorZ / 200;
  
  if(XY_ERROR == 1) {
  	return GyroErrorX;
  }	else if(XY_ERROR == 2) {
  		return GyroErrorY;
  	}else if(XY_ERROR == 3) {
  		return GyroErrorZ;
  	}
  }	  		
  }

  public:
  	double AccGyroVals(uint8_t SenData){
  		// === Read acceleromter data === //
 		 Wire.beginTransmission(MPU);
  		 Wire.write(0x3B); // Start with register 0x3B (ACCEL_XOUT_H)
  		 Wire.endTransmission(false);
  		 Wire.requestFrom(MPU, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
  		//For a range of +-2g, we need to divide the raw values by 16384, according to the datasheet
  		AccX = (Wire.read() << 8 | Wire.read()) / 16384.0; // X-axis value
  		AccY = (Wire.read() << 8 | Wire.read()) / 16384.0; // Y-axis value
  		AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0; // Z-axis value
  		// Calculating Roll and Pitch from the accelerometer data
  		accAngleX = (atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / PI)-calculate_IMU_error(2,1) ; // AccErrorX ~(0.58) See the calculate_IMU_error()custom function
  		accAngleY = (atan(-1 * AccX / sqrt(pow(AccY, 2) + pow(AccZ, 2))) * 180 / PI) + calculate_IMU_error(2,2); // AccErrorY ~(-1.58)
  
  		// === Read gyroscope data === //
  		previousTime = currentTime;        // Previous time is stored before the actual time read
  		currentTime = millis();            // Current time actual time read
  		elapsedTime = (currentTime - previousTime) / 1000; // Divide by 1000 to get seconds
  		Wire.beginTransmission(MPU);
  		Wire.write(0x43); // Gyro data first register address 0x43
  		Wire.endTransmission(false);
  		Wire.requestFrom(MPU, 6, true); // Read 4 registers total, each axis value is stored in 2 registers
  		GyroX = (Wire.read() << 8 | Wire.read()) / 131.0; // For a 250deg/s range we have to divide first the raw value by 131.0, according to the datasheet
  		GyroY = (Wire.read() << 8 | Wire.read()) / 131.0;
  		GyroZ = (Wire.read() << 8 | Wire.read()) / 131.0;
  		// Correct the outputs with the calculated error values
  		GyroX = GyroX + calculate_IMU_error(1,1); // GyroErrorX 
  		GyroY = GyroY - calculate_IMU_error(1,2); // GyroErrorY
  		GyroZ = GyroZ + calculate_IMU_error(1,3); // GyroErrorZ
  		// Currently the raw values are in degrees per seconds, deg/s, so we need to multiply by sendonds (s) to get the angle in degrees
  		gyroAngleX = gyroAngleX + GyroX * elapsedTime; // deg/s * s = deg
  		gyroAngleY = gyroAngleY + GyroY * elapsedTime;
  		yaw =  yaw + GyroZ * elapsedTime;
  	
  		// Complementary filter - combine acceleromter and gyro angle values
  		roll = 0.96 * gyroAngleX + 0.04 * accAngleX;
  		pitch = 0.96 * gyroAngleY + 0.04 * accAngleY;
  		
		 if(SenData == 1){
			 return roll;
		 } else if(SenData == 2){
			 return pitch;
		 }else if(SenData == 3){
			 return yaw;
		 }
  	}	
		
};	