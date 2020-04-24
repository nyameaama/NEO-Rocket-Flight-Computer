#ifndef Sensors_F
#define Sensors_F
#include<SoftwareSerial.h>
#include<TinyGPS++.h>
#include<Adafruit_BMP085.h>

#define UNDEFINED 0

class Sensors {
    private:
	    const uint8_t airspeedPin = UNDEFINED;

    public:
          //Functions returns distance from nearest object from ultrasonic sensor
	    uint32_t ultrasonic_sensor_calib(uint8_t trigPin, uint8_t echoPin);    

        //Function retrns altitude in meters
	    uint32_t altimeter();

        //Function returns Airspeed (m/s)
	    double AirspeedVal();

        //This function takes in a parameter 1 or 2. Parameter one returns latitude and parameter 2 returns longitude
        double GPS_LOC(uint8_t coordinatePref);

}; 
#endif   