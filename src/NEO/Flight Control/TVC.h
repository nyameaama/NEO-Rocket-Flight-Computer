#include<stdint.h>
#include<stddef.h>
#include<Arduino.h>
#include<Servo.h>
#include<Thread.h>
#include<ThreadController.h>

class Tools {
 	public:
        //Function to compute the Highest Common Factor between two numbers
 		uint16_t HCF(uint32_t x,uint32_t y);

        //Function to compare two uint32_tegers and determine which is greater
                uint8_t greater(uint32_t x,uint32_t y);

        //Function to find length of an array
                uint8_t length(uint8_t arr[]);

};

class Control : public Tools {
 	private:
 	        uint8_t inputL1;
 		uint8_t inputL2;
                uint8_t currentM1; // Current degrees for motor M1 and M2
                uint8_t currentM2; 
                Servo M1,M2;
                uint8_t M2_reading,M1_reading;
        private:


 	public:
                uint8_t *Equation_of_Line(uint32_t ROT,uint32_t MOV);

                void ExpVectorM(uint8_t ROT,uint8_t MOV);

                uint8_t *thrustVector(uint8_t M_1,uint8_t M_2);

                void Motor1_Move(uint8_t val);

                void Motor2_Move(uint8_t val);
                
                void multithreadServo(uint8_t x,uint8_t y);

};        
