#include"limCalcs.h"

//Functions to check if roll, pitch and yaw readings are in acceptable range
//Based on flight path, correct calibrated angle will change according to state in path so the standard (roll/pith/yaw) values 
//have to be dynamic


	//Check functions return 0 when readings are ideal and a non-zero error margin value when readings are off
	// If function returns negative value there is movement on negative axis(left)
	//If function returns positive value there is movement on the positive axis(right)
    //standardRollval = //0 degrees
    //standardPitchval = //87 degrees
	
	

		double RPY_CHECK::roll_range(double roll_val,uint8_t standardRollval) {
			double A_margin = 0.5;
			double readingError = 0;
			if(roll_val < (standardRollval - A_margin)) {
				readingError =  standardRollval - roll_val;   
			}
			if(roll_val > (standardRollval + A_margin)){
				readingError = roll_val - standardRollval;
			}
			return readingError;	 
		}
			
		double RPY_CHECK::pitch_range(double pitch_val,uint8_t standardPitchval) {
			double Acceptable_margin = 5.0;
			double readError = 0;
			if(pitch_val < (standardPitchval - Acceptable_margin)) {
				readError =  standardPitchval - pitch_val;   
			}
			return readError;	 
		}
			
		double RPY_CHECK::yaw_range(double yaw_val,uint8_t standardYawVal) {
			double AccMargin = 0.1;
			double readError = 0;
			if(yaw_val < (standardYawVal - AccMargin)) {
				readError =  standardYawVal - yaw_val;   
			}
			if(yaw_val > (standardYawVal + AccMargin)){
				readError = yaw_val - standardYawVal;
			}
			return readError;	 
		}		

//Function to correct rocket axis from variances in flight direction
		int *VectorCompute::translate_to_servo(double yawR,double pitchR) {
			//Translate gyro range to support servo range
			int ranges[2];
			int low = -90;
			int mid = 90;
			int translateY,translateP;
			//Yaw
			if(yawR < 0){
				translateY = -(low + -(yawR));
			}
			else if(yawR > 0){
				translateY = mid + yawR;
            }else{
                translateY = 90;
            }
			//Pitch
			if(pitchR < 0){
				translateP = -(low + -(pitchR));
			}
			else if(pitchR > 0){
				translateP = mid + pitchR;
			}else{
                translateP = 90;
			}
			ranges[0] = translateP;
			ranges[1] = translateY;
			return ranges;
		}	 

//---------EXPERIMENTAL-------------//

		//Creates altimeter and ultrasonic sensor readings relationship and determines if rocket is in safe alt range after 
		//launch or during landing
		uint8_t AreaAnalysis::closeSurfaceDetection(double senRead,double altRead){
			//Sensors closeSurface,altS;
			//double senRead = closeSurface.ultrasonic_sensor_B();
			//double altRead = altS.altimeter();
			uint8_t extended_range = 2;
			double negExRangeVal = (altRead - extended_range),posExRangeVal = (altRead + extended_range);
			double scaledUread = senRead / 100;
			//Check if readings between altimeter and ultrasonic are similar by a difference of 2cm
			if(scaledUread != altRead && (altRead - negExRangeVal) < extended_range || (altRead + posExRangeVal) > extended_range){
				//if they are similar reading is verified
				//So we check to see if rocket is close to surface
				if(altRead > (terrain_level)){

				}
				
			}else{
				//if they are not, analyse past altimeter readings from EEPROM to determine proper data source
				/*Data read;
				uint32_t source;
				 source = read.EEPROM_READ_WRITE(1,0,0);*/
			}
			return 1;
		}

		//Detect launch using acceleration and change in altitude 
		uint8_t  AreaAnalysis::launch_detect(uint32_t current_altitude,double elapsed,double vel_change,double acc_change){
			//Function measures acceleration and altitude change. Each measurement has a weight to describe its reliability
			//Acceleration weight = 1 Altitude weight = 2
			//Minimum weight for launch trigger is 2
			uint8_t launch_certainty = 2,alt_weight = 2,acc_weight = 1,total_weight;
			uint8_t minimum_launch_alt,minimum_acc;
			if((current_altitude - terrain_level) > minimum_launch_alt){ //Come back and adjust metrics
				total_weight += alt_weight;
			}
			//Change in acceleration = Delta V / Delta T
			//Compile two vel readings
			if(acc_change > minimum_acc){
				total_weight += acc_weight;
			}
			//define launch certainty based on weights
			if(total_weight >=
			 launch_certainty){
				//haslaunched = 1;
				return 1;
			}else{
				//haslaunched = 0;
			}
			return 0;
		}
