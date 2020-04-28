#include"B_Sensors.h"

//Function returns altitude in meters
uint32_t BSensors::BS_altimeter(){
	Adafruit_BMP085 Psensor;
	double seaLevelP = Psensor.readSealevelPressure(), cLocPressure = Psensor.readPressure();
	double cLocTemp = Psensor.readTemperature();
	double temp1, temp2, height;
	//Calculating Altitude from pressure using hypsometric formula
	temp1 = (pow((cLocPressure / seaLevelP), (1 / 5.257)) - 1);
	temp2 = temp1 * (cLocTemp + 273.15);
	height = temp2 / 0.0065;
	return height;
}