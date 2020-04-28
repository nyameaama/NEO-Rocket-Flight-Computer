#include "TVC.h"

uint16_t Tools::HCF(uint32_t x, uint32_t y){
	//Function to compute the Highest Common Factor between two numbers
	uint16_t HCF;
	for (size_t i = 1; i <= x && i <= y; i++){
		if (x % i == 0 && y % i == 0){
			HCF = i;
		}
	}
	return HCF;
}

uint8_t Tools::greater(uint32_t x, uint32_t y){
	//Function to compare two uint32_tegers and determine which is greater
	uint32_t greater = x;
	if (y > x){
		greater = y;
	}
	return greater;
}

uint8_t Tools::length(uint8_t arr[]){
	//Function to find length of an array
	uint8_t count;
	for (size_t i = 0; i < arr[i]; i++){
		arr[i];
		count++;
	}
	return count;
}

/*-------------------------EXPERIMENTAL PROCESS-------------------------*/
uint8_t *Control::Equation_of_Line(uint32_t ROT, uint32_t MOV){
	//Finding equation of line (y = mx + c)
	//Finding M (y = (M)x + c)
	uint8_t pouint32_tx1, pouint32_tx2, pouint32_ty1, pouint32_ty2; // Temporary bug - Initial x pouint32_ts are not always (0,0) uint32_troduce array element to store last vector position to use for initial x pouint32_ts
	uint8_t slope1, slope2;
	//std::vector<uint32_t> vals;
	static uint8_t vals[128]; //Array to store (m) and (c) values
	pouint32_tx2 = ROT;
	pouint32_ty2 = (90 - ROT);
	slope1 = pouint32_ty2 - pouint32_ty1;
	slope2 = pouint32_tx2 - pouint32_tx1;
	uint8_t hcf = HCF(slope1, slope2);
	slope1 = slope1 / hcf;
	slope2 = slope2 / hcf;
	if (slope1 <= 1 || slope2 <= 1){
	}
	else{
		vals[0] = slope1;
		vals[1] = slope2;
	}
	/*vals.insert(vals.begin(),slope1);
 			vals.insert((vals.begin()+1),slope2); 
 			if(slope1 <= 1 || slope2 <= 1){
 				 vals.clear();
 				 vals.insert(vals.begin(),greater(slope1,slope2));
 			}*/

	//Finding C (y = mx + (C))
	uint8_t c = pouint32_ty2 - ((slope1 / slope2) * pouint32_tx2);
	if (c == 0){
		vals[length(vals)] = 0;
	}
	else{
		vals[length(vals)] = c;
	}

	return vals;
}
void Control::ExpVectorM(uint8_t ROT, uint8_t MOV){
	uint8_t Mval1, Cval;
	uint8_t xvalue, yvalue;
	//values[0] = M values[1] = c
	uint8_t *values = Equation_of_Line(ROT, MOV);
	//Parse
	//Get M value or fraction
	if (values[0] > 0 || values[1] > 0){
		//Get fraction
		Mval1 = values[0] / values[1];
	}
	else{
		//Get value
		Mval1 = greater(values[0], values[1]);
	}
	//Get C value
	Cval = values[3];
	//Execute
	//Calculate number of loops needed to move uint32_to final position
	uint8_t loops;
	/////////////////////
	for (uint8_t i = 0; i < loops; i++){
		yvalue = i; //Come Back to this(logical issue with y = ()x + ()
		xvalue = (Mval1 * i) + Cval;
		//multithreadServo(xvalue,yvalue);
	}
}
/*---------------------------------------------------------------------*/

uint8_t *Control::thrustVector(uint8_t M_1, uint8_t M_2){
	//M_1 and M_2 values will be in the range of 0 - 90
	//but servo moves from 0 - 180 so numbers will have to
	//be scaled
	//Vertical Moving Motor
	uint8_t servoLoc[2];
	uint8_t M1temp1, M1_reading;
	M1temp1 = M_1 * 180;
	M1_reading = M1temp1 / 90;
	servoLoc[0] = M1_reading;
	//Horizontal Moving Motor
	uint8_t M2temp1, M2_reading;
	M2temp1 = M_2 * 180;
	M2_reading = M2temp1 / 90;
	servoLoc[1] = M2_reading;
	//Multithread servo move process
	return servoLoc;
}

void Control::Motor1_Move(uint8_t val){
	M1.write(M1_reading);
}
void Control::Motor2_Move(uint8_t val){
	M2.write(M2_reading);
}
void Control::multithreadServo(uint8_t x,uint8_t y){
	//Thread Controller to control Threads		
	ThreadController control = ThreadController();
	//Servo #1 thread
	Thread servo1 = Thread();
	//Servo #2 thread
	Thread servo2 = Thread();
	//Configure Servo #1 thread
	//Interval set to 10ms
	//servo1.onRun(Motor1_Move);
	servo1.setInterval(10);
	//Configure Servo #2 thread
	//Interval set to 10ms
	//servo2.onRun(Motor2_Move);
	servo2.setInterval(10);
	//Add both threads to thread controller
	control.add(&servo1);
	control.add(&servo2);
	//Thread controller will run both threads based on interval
	control.run();
 }