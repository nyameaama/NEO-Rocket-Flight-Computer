# FILE FUNCTIONS DESCRIPTIONS

## File System 

### Log rate Management
* Log Rate Management is a method that is aimed to maximise SD memory in flight regardless of Storage size. Log rate management
records the number of file write entries made by flight systems such as data logging (which logs fligh altitude, speed, pitch, yaw), variables stored on SD as well as Real-Time Camera Data Storage. It then computes the rate of write entries into the SD (logs/sec) and computes the time remaining based on the rate of entries. Taking into account the fixed SD size predefined (ex: 4GB), the number of entries per sec that would  be needed to maximise SD flight memory would be calculated. Then in order to enforce this, data log calls by system functions would either be accepted or denied based on the current system log rate.

This method prioritizes critical data such as variables needed by other system methods and data size is also taken into account.

## EEPROM

On board EEPROM Storage is used as a safety system for SD data logging in case of SD overflow. Flight data during flight will be stored in EEPROM storage consisting of 1024 bytes. A partition is applied for flight setup data and onboard flight data (100B - 800B - 124B) and System Management(Variables). Flight Data consists of (Alt readings,Vel readings,Pitch and yaw readings, **** readings) taken at 15 second intervals.
