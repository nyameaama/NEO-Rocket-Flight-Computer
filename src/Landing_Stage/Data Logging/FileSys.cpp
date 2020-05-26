#include "FileSys.h"

FileSystem::FileSystem()
{
    if (!SD.begin(PIN_OUTPUT)){
        ErrorDump dp;
        dp.ERROR_DUMP("503");
    }
    //PIDS
    PrIDS[0] = "velocity_log";
    PrIDS[1] = "6C298Y3";
    PrIDS[2] = "altitude_log";
    PrIDS[3] = "67U34PO";
    PrIDS[4] = "pitch_log";
    PrIDS[5] = "376FG0T";
    PrIDS[6] = "yaw_log";
    PrIDS[7] = "7GN31Q0";
    PrIDS[8] = "ACTIVITY_LOG";
    PrIDS[9] = "SYS347P";
    PrIDS[10] = "ERROR_LOG";
    PrIDS[11] = "SYS412Y";
}

FileSystem::~FileSystem(){
    free(PrIDS);
}

template <typename FC>
boolean FileSystem::compare(FC x, FC y){
    return (x != y) ? false : true;
}


double FileSystem::TimeHelper(double x){
    double num;
    double temp = round(x);
    num = x - temp;
    if (num < 0){
        -(num);
        num = 0.10 - num;
    }
    else{
    }
    return num;
}

//Function computes and returns time
String *FileSystem::GET_TIME(){
    time_t timer;
    String *data = (String *)malloc(4);
    //auto current_time;
    auto current_time = time(&timer); //get current time; same as: timer = time(NULL)
    double days_since = current_time / 86400;
    double num = TimeHelper(days_since);
    double hour = num * 24;
    data[0] = String(hour);
    double min = TimeHelper(hour);
    min = min * 60;
    data[1] = String(min);
    double sec = min * 60;
    data[2] = String(sec);
    String time = String(hour) + ":" + String(min) + ":" + String(sec);
    data[3] = time;
    return data;
}

//Function writes/appends to file
uint8_t FileSystem::WRITE_TO_FILE(String x, String tag){
    DataFILE = SD.open(tag, O_RDWR);
    uint32_t temp;
    if (DataFILE){
        Serial.println(x);
        //After data is placed in file,new file breakpoint is updated
        unsigned long pos = DataFILE.position();
        DataFILE.seek(1);
        String content = (String)DataFILE.read();
        uint32_t count = content.toInt();
        count = pos;
        temp = count;
        Serial.print(String(count));
    }
    else{
        return 0;
    }
    // close the file:
    DataFILE.close();
    return temp;
}
//Function converts int to string
String FileSystem::toString(uint32_t num){
    String temp;
    temp = String(num);
    return temp;
}

String FileSystem::formatToData(String PID, String data){
    String *func = GET_TIME();
    String Ctime = func[3];
    String p = "Process";
    String pTemp = p + ":" + PID;
    String l = "log";
    String lTemp = l + ":" + data;
    String t = "Time";
    String tTemp = t + ":" + Ctime;
    String final = pTemp + "     " + lTemp + "     " + tTemp;
    return final;
}

//Function checks if PID belongs to a sys call
uint8_t FileSystem::parse(String x){
    uint8_t count;
    String *temp = (String *)malloc(3);
    temp[0] = "S";
    temp[1] = "Y";
    temp[2] = "S";
    for (size_t i = 0; i < 3; i++){
        if (compare<String>(String(x[i]), temp[i]) == 1){
            count++;
        }
    }
    free(temp);
    if (count == 3){
        return 1;
    }
    return 0;
}

//Function verifies PID
uint8_t *FileSystem::confirmPID(String x){
    //Confirm PID
    uint8_t *retArr = (uint8_t *)malloc(2);
    boolean confirm = false;
    uint8_t index;
    for (size_t i = 1; i < 10; i += 2){
        if (compare<String>(x, PrIDS[i]) == true){
            confirm = true;
            retArr[0] = 1;
            index = i;
            retArr[1] = index;
        }
    }
    return retArr;
}

//Function performs checks on every request to make sure full duration
// flight data logging is successful
uint8_t FileSystem::fileHandler(String PID){
    //Log request
    ACTIVITY_LOG();
    //Check if Sys call
    if (parse(PID) == 1){
        return 1;
    }
    //PrID Check
    uint8_t *confirm = confirmPID(PID);
    uint8_t index = confirm[1];
    String type = ".txt";
    if (confirm[0] == FALSE){
        ErrorDump dump;
        return dump.ERROR_DUMP("503");
    }
    else{
        //Check if any file is active and close it

        //Check if file exists from PID tag and open
        if (SD.exists(PID[index - 1] + type)){
            DataFILE = SD.open(PID[index - 1] + type, FILE_WRITE);
            DataFILE.close();
        }
        else{
            //Create file and add breakpoint
            DataFILE = SD.open(PID[index - 1] + type, FILE_WRITE);
            uint16_t breakPoint = 1; //The point/position in which the last character exists in the file
            WRITE_TO_FILE(String(breakPoint), String(PID[index - 1]));
            DataFILE.close();
            fileHandler(PID);
        }
        return 1;
    }
}

//Function handles scheduling and validation on request side
uint8_t FileSystem::FILE_LOG(String x,String PID){
    uint8_t *PID_vals = confirmPID(PID);
     //if log main returns true data can be written to file
    LogRateManagement proc;
    if(/*proc.logMain(x.toInt())*/1){
        String data = formatToData(PID, x);
        WRITE_TO_FILE(data, PrIDS[PID_vals[1] - 1]);
        return 1;
    }else{
        return 0;
    }
}

//Function logs file read/write activity
void FileSystem::ACTIVITY_LOG(){
    String PID = "SYS347P";
    String tag = "ACTIVITY_LOG";
    if (fileHandler(PID)){
        String time;
        String data = formatToData(PID, tag);
        Activity = WRITE_TO_FILE(data, tag);
    }
}

uint8_t FileSystem::FOREIGN_READ(String PID,String searchParam){
     fileHandler(PID);

 }

 uint8_t FileSystem::FOREIGN_LOG(String PID,double x){
     //Make request to file handler
    if (fileHandler(PID) == 1){
        String strVal = toString(x);
        FILE_LOG(strVal, PID);
        return 1;
    }
    else{
        return 0;
    }
 }

 