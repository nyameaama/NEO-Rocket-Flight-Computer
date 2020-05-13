#include "command.h"

//Finds the length of a string
uint8_t Command_Word_Break::string_len(char x[64]){
    uint8_t count;
    for (size_t i = 0; i < x[i]; i++){
        x[i];
        count++;
    }
    return count;
}

//Verify that string is apart of availabe commands
char Command_Word_Break::verify(char x[]){
    //char ERROR[] = "error";
    char availableC[128] = "Fatslu"; // Characters at index 0 and 2 of root command strings
    uint8_t itr;
    for (size_t i = 0; i < string_len(availableC); i++){
        if (x[0] == availableC[i]){
            itr++;
        }
    }
    for (size_t j = 0; j < string_len(availableC); j++){
        if (x[2] == availableC[j]){
            itr++;
        }
    }
    if (itr < 2){
        ErrorDump fr;
        return fr.ERROR_DUMP("404");
    }
    else{
        return 1;
    }
}
//Parse string command
uint8_t Command_Word_Break::parse_comm(char stringV[]){
    //char ERROR[] = "error";
    uint8_t count, count2 = 0;
    char subroot[32];
    char space[] = " -";
    //Call function to verify that string is apart of availabe commands
    if (verify(stringV) != 1){
    }
    else{
        //Break down command string (From ex:(Fdata -add) --> (-add))
        for (size_t k = 0; k < string_len(stringV); k++){
            count++;
            if (stringV[k] == space[0] && k != 0){
                break;
            }
        }

        //Parse rest of string
        if (stringV[count + 1] == space[1]){
            for (size_t k = (count + 2); k < string_len(stringV); k++){
                subroot[count2] = stringV[k];
                count2++;
            }
        }

        //char func  = subrootAnalyzer(subroot);
        return 1;
    }
}
//Analyzes subroot to corresponding function
char Command_Word_Break::subrootAnalyzer(char y[]){
}

void Command_Word_Break::SDisplay(char x){
    Serial.println(x);
}
//Display Integers
void Command_Word_Break::IDisplay(uint8_t x){
   Serial.println(x);
}
char *Command_Word_Break::prompt(){
    char comm_byte;
    char comm_str[32];
     //Call prompt
  //Read characters from Serial Monitor
  uint8_t comm_index;
  while(comm_byte != '\n'){
    if (Serial.available() > 0) {  
        comm_byte = Serial.read();// get the character
    }
    if (comm_byte != '\n') {
      // a character of the string was received
      comm_str[comm_index] = comm_byte;
      comm_index++;
    }
    else{
      
    }
  }                   
    return comm_str;
}
//Flight Data Functions
double *SYS_FUNCTIONS::COMPILED_FLIGHT_DATA(){
    //Display Altitude
    //IDisplay(xF_Altitude);
    //Display Coordinates
    for (size_t i = 0; i < 2; i++){
        //IDisplay(xF_FCoordinates[i]);
    }
}
double SYS_FUNCTIONS::GET_LATITUDE(double *xF_FCoordinates){
    return xF_FCoordinates[0];
}
double SYS_FUNCTIONS::GET_LONGITUDE(double *xF_FCoordinates){
    return xF_FCoordinates[1];
}
uint8_t SYS_FUNCTIONS::ADD_COORDINATES(double x, double y, double *xF_FCoordinates){
    //xF_FCoordinates[2]
    for (size_t i = 0; i < 2; i++){
        if (xF_FCoordinates[i] != NULL){
        }
    }
    xF_FCoordinates[0] = x;
    xF_FCoordinates[1] = y;
    return 1;
}
uint8_t SYS_FUNCTIONS::ADD_ALTITUDE(double newAlt, double *xF_altitude){
    //xF_altitude
    double *nAlt = &newAlt;
    if (xF_altitude > 0){
    }
    else{
        xF_altitude = nAlt;
    }
    return 1;
}
void SYS_FUNCTIONS::CLEAR_F_DATA(double *xF_FCoordinates, double *xF_altitude){
    //Clear Flight Data sets all data values to NULL
    //Altitude
    //xF_Altitude = NULL;
    //Coordinates
    for (size_t i = 0; i < 2; i++){
        xF_FCoordinates[i] = NULL;
    }
}
//Testing Functions
String *SYS_FUNCTIONS::TEST_SYS(){
    uint8_t BASE_SIZE = 7;
    String *state = (String*)malloc(BASE_SIZE);
    Inspect sysFuncs;
    state = sysFuncs.InspectMain();
    realloc(state,state[0].toInt());
    return state;
}

//Launch Functions
uint8_t SYS_FUNCTIONS::LAUNCH_DATA(){

}
