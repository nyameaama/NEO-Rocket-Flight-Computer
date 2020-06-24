#include"AreaAnalysis.h"
 double *speed_of_increase = (double*)malloc(SAMPLE_SIZE);
 
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

//Detect Apogee using negative change in altitude
boolean AreaAnalysis::detectApogee(){
	//To detect apogee, we sample 3 altimeter readings, then values are compared to
	//see if they follow a direct negative trend. Ex:(98.5 -> 97.2 -> 95.6). If values 
	//follow a negative trend, apogee is met and function returns true else function returns 
	//false
	Sensors apog;
	//Get 3 readings
	double *readings = (double*)malloc(3);
	for(size_t i = 0; i < 3;i++){
		readings[i] = apog.altimeter();
	}
	//Analyse for constant negative change in altitude readings
	boolean change = true;
	for(size_t j = 0; j < 3;j++){
		if(j != 3){
			if(readings[j] < readings[j + 1]){
				change = false;
			}
		}else{
			break;
		}
	}
	free(readings);
	return change;
}

//Function gets altitude samples with time took place. time = millis() 
//which is the number of time passed after the program started
double *AreaAnalysis::getAltitudeVals(){
    double *values = (double*)malloc(SAMPLE_SIZE);
    for(size_t i = 0;i < SAMPLE_SIZE / 2;i+=2){
        values[i] = get.altimeter();
        values[i + 1] = millis();
    }
    return values;
}

//Function gets duration between two timestamps
double AreaAnalysis::timeBetweenReadings(double x,double y){
    return (y - x);
}

boolean AreaAnalysis::analyseAltDecceleration(){
     //To detect decceleration patterns from decceleration the distance between each
     //alt value is analysed to see if over the time the difference gets smaller
    double *alt_time_samples = getAltitudeVals();
    //New array to separate timestamps from vel values
    double *altOnly_samples = (double*)malloc(SAMPLE_SIZE); 
    uint8_t new_arr_index;
    for(size_t n = 0;n < SAMPLE_SIZE * 2;n+=2){
        altOnly_samples[new_arr_index] = alt_time_samples[n];
        new_arr_index++; 
    }
    //Find speed of increase between each pair of values
    //s = d /t --> speed_of_increase = difference / time_duration
    uint8_t SOI_index; 
    for(size_t i = 0;i < SAMPLE_SIZE;i++){
        //Get difference
        double diff = altOnly_samples[i + 1] - altOnly_samples[i];
        //Get time duration
        double duration = timeBetweenReadings(alt_time_samples[i + 1],alt_time_samples[i + 3]);
        //Compute speed of increase
        double S_O_I = diff / duration;//Samples per 
        speed_of_increase[SOI_index] = S_O_I;
        SOI_index++;
    }
    //Determine if speed of increase follws a descending trend
    boolean deccel = true;
    for(size_t j = 0;j < SAMPLE_SIZE;j++){
        if(j != SAMPLE_SIZE){
            if(speed_of_increase[j + 1] > speed_of_increase[j]){
                deccel = false;
            }
        }else{
            //Do nothing
        }
    }
    return deccel;
 }

 double AreaAnalysis::time_to_Apogee(){
    if(analyseAltDecceleration()){
        double time;
        double speed = speed_of_increase[SAMPLE_SIZE] - speed_of_increase[SAMPLE_SIZE - 1];
        double distance = speed_of_increase[SAMPLE_SIZE];
        time = distance / speed;
        return time;
    }else{
        return -1;
    }
}

void AreaAnalysis::BRICK_ALL_PROCESSES(){
	String ID = "E-BRICK",data = "PROCESS BRICK";
	RF_ASSIGN Eroutine;
	while(true){
		Eroutine.RF_SEND(ID,data);
	}
}

uint8_t AreaAnalysis::reOrient(){
	//Use of PID to reorient
	Gyro IMU;
	PROPORTIONAL_INTEGRAL_DERIVATIVE task;
	FinAxisAdjustment adjust;
	double kp,kd,ki;
	double reorientSetpoint;
	task.createPIDinstance("REORIENT",kp,ki,kd);
	double rFin = task.PID_MAIN("REORIENT",IMU.AccGyroVals(2),reorientSetpoint);
	//Move fins
	adjust.FIN_ADJUST(rFin,IMU.AccGyroVals(3));
	return;
}
