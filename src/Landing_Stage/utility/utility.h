#ifndef Utility_F
#define Utility_F

#include<stddef.h>
#include<stdint.h>
#include"math.h"
#include<Arduino.h>

#define pi 3.14159265358979
//Utility Functions

class Utility {
    public:
        double copyELements(double array[1024][2],double arr[][2],uint8_t arrlength);

        double arrayConversion1D_2D(double array[64]);

        //This functions finds the next divisible number
		uint16_t divisibleBY(uint32_t x);

        //This function converts decimal degrees to radians       
		double deg2rad(double deg);

        //This function converts radians to decimal degrees 
		double rad2deg(double rad);

         //Calculates cosine rule
		double cosine_rule(double lengthA,double lengthB,double lengthC);

        //1D array Length Function
		uint8_t ODlength(double arr[]);

        //2D array Length Function
		uint32_t TDlength(double arr[][2]);

        //Convert 2D array to 1D array    
        double *arrayConversion2D_1D(double array[][2]);

        //Function to compute the Highest Common Factor between two numbers
 		uint16_t HCF(uint32_t x,uint32_t y);

        //Function to compare two uint32_tegers and determine which is greater
        uint8_t greater(uint32_t x,uint32_t y);

    
};

#endif