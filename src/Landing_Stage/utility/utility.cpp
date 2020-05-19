#include"utility.h"

//This functions finds the next divisible number
uint16_t  Utility::divisibleBY(uint32_t x){
	uint8_t flag = 0;
	uint16_t ar[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	for (size_t i : ar){
		if (x % ar[i] == 0){
			flag = i;
		}
	}
	return ar[flag];
}
//This function converts decimal degrees to radians
double Utility::deg2rad(double deg){
	return (deg * pi / 180);
}
//This function converts radians to decimal degrees
double Utility::rad2deg(double rad){
	return (rad * 180 / pi);
}
//Calculates cosine rule
double Utility::cosine_rule(double lengthA, double lengthB, double lengthC){
	double val;
	val = pow(lengthB, 2) + pow(lengthC, 2);
	val = val - pow(lengthA, 2);
	val = val / (2 * lengthB * lengthC);
	val = acos(val) * 180.0 / pi;
	return val;
}
//1D array Length Function
uint8_t Utility::ODlength(double arr[]){
	uint8_t count;
	for (size_t i = 0; i < arr[i]; i++){
		arr[i];
		count++;
	}
	return count;
}
//2D array Length Function
uint32_t Utility::TDlength(double arr[][2]){
	//String str = String(arr);
}
//Convert 2D array to 1D array
double *Utility::arrayConversion2D_1D(double array[][2]){
	uint16_t n = 64;
	double a[n][n], b[n * n];
	uint16_t *c = (uint16_t *)malloc(n * n);
	uint16_t i, j, k = 0, l = 0;
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			b[k] = a[i][j];
			k++;
		}
	}
	free(c);
	return b;
}

uint16_t Utility::HCF(uint32_t x, uint32_t y){
	//Function to compute the Highest Common Factor between two numbers
	uint16_t HCF;
	for (size_t i = 1; i <= x && i <= y; i++){
		if (x % i == 0 && y % i == 0){
			HCF = i;
		}
	}
	return HCF;
}

uint8_t Utility::greater(uint32_t x, uint32_t y){
	//Function to compare two uint32_tegers and determine which is greater
	uint32_t greater = x;
	if (y > x){
		greater = y;
	}
	return greater;
}
