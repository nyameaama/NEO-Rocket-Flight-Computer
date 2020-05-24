#include"LRM.h"

//FileSystem vars;
File DataFILE;

//Estimated Flight Time in miiliseconds
double estimatedFlight_time;
double Volume_Capacity = 8192;

double *LogRateManagement::compileFileSizes(){
    double *temp = (double*)malloc(10);
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

double LogRateManagement::getDiskUsed(){
    double *temp = compileFileSizes();
    uint32_t fileSizeTotal = total(temp);
    return fileSizeTotal;
}

double LogRateManagement::getRemainingCapacity(){
    double remainingCapacity = Volume_Capacity - getDiskUsed();
    return remainingCapacity;
}

double LogRateManagement::getLogRate(){
    uint32_t DataLogRate,Activity;
    //Activity = vars.Activity;
    uint32_t fileSizeTotal = getDiskUsed();
    double remainingCapacity = getRemainingCapacity();
    //Find Rate of data logging by dividing amount of logs done over flight duration
    uint32_t flightDuration = millis() / 1000; //secs
    DataLogRate = fileSizeTotal / flightDuration;   //logs/sec
    return DataLogRate;
}

uint16_t LogRateManagement::total(double *arr){
    uint16_t total;
    for (size_t i = 0; i < 10; i++){
        total += arr[i];
    }
    return total;
}

template <typename DataType>
boolean LogRateManagement::logMain(DataType x){
    auto dataSize = sizeof(x);
    double d = (Volume_Capacity / dataSize);
    double s = getLogRate();
    double forecastStorageCutTime = d / s;
    double flightTimeRemaining = estimatedFlight_time - millis();
    boolean acceptData = (forecastStorageCutTime > flightTimeRemaining) ? true : false;
    return acceptData;
}