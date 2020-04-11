
#include"EEPROMStorage.h"

        uint8_t Data::EEPROM_READ_WRITE(uint8_t x,uint32_t y,uint16_t z,uint32_t eepromCycle,uint16_t addr){ //x = read/write, y = value, z = specific address(SA) if z != SA z = -1
            if(x == 0){
                //Write the value to the appropriate byte of the EEPROM.
                //http://electronics.scriblab.de/write-an-integer-to-the-arduino-eeprom/
                //"All you need to do is to do some bit-shifting magic and voilá you can decompose the uint32_t to its Byte components 
                //(taking the first and the last 8-Bits) and save it to actually 2 addresses."
                if(z > -1 && z < 1024){
                    byte two = (y & 0xFF);
                    byte one = ((y >> 8) & 0xFF);
                    EEPROM.update(addr, two);
                    EEPROM.update(addr + 1, one);
                    addr+=2;
                    eepromCycle+=2;
                    if(addr == EEPROM.length()) {                                   
                     addr = 0;
                    }
                    return 0;
                }else{
                    byte two = (y & 0xFF);
                    byte one = ((y >> 8) & 0xFF);
                    EEPROM.update(z, two);
                    EEPROM.update(z + 1, one);
                    eepromCycle+=2;
                    return 0; 
                }
            }
            else if(x == 1){
                //Read the value from the address specified in variable y
                long two = EEPROM.read(z);
                long one = EEPROM.read(z + 1);
                return ((two << 0) & 0xFFFFFF) + ((one << 8) & 0xFFFFFFFF);
            }
        }
        uint8_t Data::EEPROM_MANAGEMENT(uint32_t eepromCycle){
            uint16_t max_storage = 1024;
            uint32_t max_cycle_times = 100000;
            double percent_health;
            uint32_t total,x;
            //Calculate remaining EEPROM health
            total = max_storage * max_cycle_times;
            x = total - eepromCycle;
            percent_health = (x / total)*100;
            return percent_health;
        }
    
       void Data::Flight_Data_Save(uint16_t alt_address,uint16_t vel_address,uint16_t pitch_address,uint16_t yaw_address,uint16_t altimeter,uint8_t Airspeed,uint8_t pitch,uint8_t yaw,uint16_t eepromCycle,uint16_t addr) {
            //Data during flight | 100 - 900 Byte address
            //Sensors alt,airSp;
            //Gyro pitch,yaw;
            //Altitude
            Data inf;
            if(alt_address < 160){  //Alt = 100 - 260 
                inf.EEPROM_READ_WRITE(0,altimeter,alt_address,eepromCycle,addr);
                alt_address++;
            }
            //Velocity
            if(vel_address < 160){ //Vel = 260 - 420
                inf.EEPROM_READ_WRITE(0,Airspeed,vel_address,eepromCycle,addr);
                vel_address++;
            }
            //Pitch
            if(pitch_address < 160){ //Pitch = 420 - 580
                inf.EEPROM_READ_WRITE(0,pitch,pitch_address,eepromCycle,addr);
                pitch_address++;
            }
            //Roll
            if(yaw_address < 160){ //Yaw = 580 - 740
                inf.EEPROM_READ_WRITE(0,yaw,yaw_address,eepromCycle,addr);
                yaw_address++;
            }

        }

