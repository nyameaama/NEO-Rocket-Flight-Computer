#include "sensors.h"

uint32_t Sensors::ultrasonic_sensor_calib(uint8_t trigPin, uint8_t echoPin){
	long duration, microseconds_to_cm;
	pinMode(trigPin, OUTPUT);
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
	pinMode(echoPin, INPUT);
	duration = pulseIn(echoPin, HIGH);
	microseconds_to_cm = duration / 29 / 2;
	return microseconds_to_cm;
	delay(100);
}
//Function returns altitude in meters
uint32_t Sensors::altimeter(){
	Adafruit_BMP085 Psensor;
	uint32_t gps_alt = GPS_LOC(5);
	double seaLevelP = Psensor.readSealevelPressure(), cLocPressure = Psensor.readPressure();
	double cLocTemp = Psensor.readTemperature();
	double temp1, temp2, height;
	//Calculating Altitude from pressure using hypsometric formula
	temp1 = (pow((cLocPressure / seaLevelP), (1 / 5.257)) - 1);
	temp2 = temp1 * (cLocTemp + 273.15);
	height = temp2 / 0.0065;
	//If height exceeds 9000, gps alt sources will be used instead
	if (height >= 9000)
	{
		return gps_alt;
	}
	return height;
}
//Function returns Airspeed (m/s)
double Sensors::AirspeedVal(){
	double AnRead = analogRead(airspeedPin);
	double offset = AnRead - (1023 / 2);
	uint8_t zero_span = 2;
	double Airspeed;
	double AirDensity = 1.225;
	//average a few ADC readings for stability
	for (size_t i = 0; i < 20; i++){
		AnRead += analogRead(A0) - offset;
	}
	AnRead /= 20;
	// make sure if the ADC reads below 512, then we equate it to a negative velocity
	if (AnRead > 512 - zero_span && AnRead < 512 + zero_span){
		//Do nothing
	}
	else{
		if (AnRead < 512){
			Airspeed = -sqrt((-10000.0 * ((AnRead / 1023.0) - 0.5)) / AirDensity);
		}
		else{
			Airspeed = sqrt((10000.0 * ((AnRead / 1023.0) - 0.5)) / AirDensity);
		}
	}
	return Airspeed;
}

double Sensors::GPS_LOC(uint8_t coordinatePref){
	//This function takes in a parameter 1 or 2. Parameter one returns latitude and parameter 2 returns longitude
	//Special parameters 3 and 4 and 5 return time in hour(3),time in minutes(4),time in seconds(34) and altitude(5) in meters
	static const uint8_t RXPin = UNDEFINED, TXPin = UNDEFINED;
	static const uint32_t GPSBaud = 9600;
	// The TinyGPS++ object
	TinyGPSPlus gps;
	// The serial connection to the GPS device
	SoftwareSerial ss(RXPin, TXPin);
	ss.begin(GPSBaud);
	while (ss.available() > 0){
		gps.encode(ss.read());
		if (gps.location.isUpdated()){
			if (coordinatePref == 1){
				return gps.location.lat();
			}
			if (coordinatePref == 2){
				return gps.location.lng();
			}
		}
		if (coordinatePref == 3){
			return gps.time.hour();
		}
		if (coordinatePref == 4){
			return gps.time.minute();
		}
		if (coordinatePref == 34){
			return gps.time.second();
		}
		if (coordinatePref == 5){
			return gps.altitude.meters();
		}
	}
}
