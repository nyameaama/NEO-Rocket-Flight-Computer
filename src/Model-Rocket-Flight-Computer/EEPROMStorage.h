#include<EEPROM.h>
#include<Arduino.h>
//Flight data during flight will be stored in EEPROM storage consisting of 1024 bytes. 
//Apply a partition for flight setup data and onboard flight data (100B - 800B - 124B) and EEPROM management
//Flight Data consists of (Alt readings,Vel readings,Pitch and yaw readings, **** readings) taken at 15 second intervals

class Data {
    public:
        uint8_t EEPROM_READ_WRITE(uint8_t x,uint32_t y,uint16_t z,uint32_t eepromCycle,uint16_t addr);

        uint8_t EEPROM_MANAGEMENT(uint32_t eepromCycle);

        void Flight_Data_Save(uint16_t alt_address,uint16_t vel_address,uint16_t pitch_address,uint16_t yaw_address,uint16_t altimeter,uint8_t Airspeed,uint8_t pitch,uint8_t yaw,uint16_t eepromCycle,uint16_t addr);
   
};
        