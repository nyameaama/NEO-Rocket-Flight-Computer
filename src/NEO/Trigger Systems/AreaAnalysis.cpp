#include"AreaAnalysis.h"

//Creates altimeter and ultrasonic sensor readings relationship and determines if craft is in safe alt range after
//launch or during landing
uint8_t AreaAnalysis::closeSurfaceDetection(double senRead, double altRead){
	//Sensors closeSurface,altS;
	//double senRead = closeSurface.ultrasonic_sensor_B();
	//double altRead = altS.altimeter();
	uint8_t extended_range = 2;
	double negExRangeVal = (altRead - extended_range), posExRangeVal = (altRead + extended_range);
	double scaledUread = senRead / 100;
	//Check if readings between altimeter and ultrasonic are similar by a difference of 2cm
	if (scaledUread != altRead && (altRead - negExRangeVal) < extended_range || (altRead + posExRangeVal) > extended_range){
		//if they are similar reading is verified
		//So we check to see if craft is close to surface
		if (altRead > (terrain_level)){
		}
	}
	else{
		//if they are not, analyse past altimeter readings from EEPROM to determine proper data source
		/*Data read;
				uint32_t source;
				 source = read.EEPROM_READ_WRITE(1,0,0);*/
	}
	return 1;
}

//Detect launch using acceleration and change in altitude
uint8_t AreaAnalysis::launch_detect(uint32_t current_altitude, double elapsed, double vel_change, double acc_change){
	//Function measures acceleration and altitude change. Each measurement has a weight to describe its reliability
	//Acceleration weight = 1 Altitude weight = 2
	//Minimum weight for launch trigger is 2
	uint8_t launch_certainty = 2, alt_weight = 2, acc_weight = 1, total_weight;
	uint8_t minimum_launch_alt, minimum_acc;
	if ((current_altitude - terrain_level) > minimum_launch_alt){ //Come back and adjust metrics
		total_weight += alt_weight;
	}
	//Change in acceleration = Delta V / Delta T
	//Compile two vel readings
	if (acc_change > minimum_acc){
		total_weight += acc_weight;
	}
	//define launch certainty based on weights
	if (total_weight >= launch_certainty){
		//haslaunched = 1;
		return 1;
	}
	else{
		//haslaunched = 0;
	}
	return 0;
}
