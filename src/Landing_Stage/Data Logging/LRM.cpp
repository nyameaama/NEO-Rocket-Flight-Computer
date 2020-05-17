#include"LRM.h"

FileSystem vars;

double *LogRateManagement::volume_size_used(){
    double *temp = (double *)malloc(10);
    uint8_t count;
    DataFILE.rewindDirectory();
    while (true){
        DataFILE.openNextFile();
        if (DataFILE.isDirectory()){
            DataFILE.openNextFile();
        }
        else{
            temp[count] = DataFILE.size();
            count++;
        }
    }
    return temp;
}

 double LogRateManagement::getLogRate(){
    uint32_t remainingCapacity,DataLogRate,Activity;
    remainingCapacity = vars.remainingCapacity;
    DataLogRate = vars.DataLogRate;
    Activity = vars.Activity;
    double *temp = volume_size_used();
    uint32_t Volume_Capacity = 8192;
    uint32_t fileSizeTotal = total(temp);
    remainingCapacity = Volume_Capacity - fileSizeTotal;
    //Find Rate of data logging by dividing amount of logs done over flight duration
    uint32_t flightDuration = millis() / 1000; //secs
    DataLogRate = Activity / flightDuration;   //logs/sec
 }

 uint16_t LogRateManagement::total(double *arr){
    uint16_t total;
    for (size_t i = 0; i < 10; i++){
        total += arr[i];
    }
    return total;
}

double LogRateManagement::logMain(){
    uint32_t Time_on_Capacity = vars.remainingCapacity / vars.DataLogRate;
    uint32_t Time_Needed;

}