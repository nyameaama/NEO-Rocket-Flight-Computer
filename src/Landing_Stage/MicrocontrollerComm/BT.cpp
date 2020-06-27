#include "BT.h"
SoftwareSerial BTSerial(2, 3); // RX | TX

 unsigned int BT_Comm::crc32c_checksum(String data){
    const char *message = data.c_str();
    int i, j;
    unsigned int byte, crc, mask;
    static unsigned int table[256];

    /* Set up the table, if necessary. */

    if (table[1] == 0) {
        for (byte = 0; byte <= 255; byte++) {
            crc = byte;
            for (j = 7; j >= 0; j--) {    // Do eight times.
                mask = -(crc & 1);
                crc = (crc >> 1) ^ (0xEDB88320 & mask);
            }
            table[byte] = crc;
        }
   }

   /* Through with table setup, now calculate the CRC. */

   i = 0;
   crc = 0xFFFFFFFF;
   while ((byte = message[i]) != 0) {
      crc = (crc >> 8) ^ table[(crc ^ byte) & 0xFF];
      i = i + 1;
   }
   return ~crc;

}

String BT_Comm::compressStrings(String x, String y){
    //Separate strings with '_'
    return (x + '_') + y;
}

String *BT_Comm::decompressString(String x){
    String *newStr = (String*)malloc(2);
    String delimiter = "_";
    uint8_t pos = x.indexOf(delimiter);
    newStr[0] =  x.substring(0, pos);
    newStr[1] = x.substring(pos + 1,x.length());
    return newStr;
}

BT_Comm::BT_Comm(){
    //Set to HC-05 default baud rate, found using AT+UART.  It is usually 38400.
    BTSerial.begin(38400);
}

String * BT_Comm::request(){
    String *ProcessInf = (String*)malloc(2);
    String bdata;
    String *decomp;
    //Read from the Bluetooth module and send to the Arduino Serial Monitor
    if(BTSerial.available()){
        bdata = String(BTSerial.read());
        decomp = decompressString(bdata);
        ProcessInf[0] = decomp[0];
        ProcessInf[1] = decomp[1];
    }
    return ProcessInf;
}

uint8_t BT_Comm::send(String ID, String x){
    //Send to the Bluetooth module
  if (BTSerial.available()) {
    String comp = compressStrings(ID,x);
    BTSerial.write(comp.toInt());  //<-- Come back and test for type errors
  }
  return;
}
