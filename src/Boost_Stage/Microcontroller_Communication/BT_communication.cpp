#include "BT_communication.h"
SoftwareSerial BSerial(RXPIN, TXPIN);

 unsigned int MC_Communication::crc32c_checksum(unsigned char *message){
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

MC_Communication::MC_Communication(){
    //Set to HC-05 default baud rate, found using AT+UART.  It is usually 38400.
    BSerial.begin(38400);
}

String * MC_Communication::request(){
    String *ProcessInf = (String*)malloc(2);
    String bdata;
    String *decomp;
    //Read from the Bluetooth module and send to the Arduino Serial Monitor
    if(BSerial.available()){
        bdata = String(BSerial.read());
        decomp = decompString(bdata);
        ProcessInf[0] = decomp[0];
        ProcessInf[1] = decomp[1];
    }
    return ProcessInf;
}

uint8_t MC_Communication::send(String ID, String x){
    // Send to the Bluetooth module
  if (BSerial.available()) {
    String comp = compStrings(ID,x);
    BSerial.write(comp.toInt());  //<-- Come back and  for type
  }
}

String MC_Communication::compStrings(String x, String y){
    String compressed;
    uint8_t combinedLength = x.length() + y.length();
    //Separate string using "_" 
    for(size_t i = 0; i < combinedLength + 1;i++){
        if(i < (combinedLength + 1)/2){
            compressed[i] = x[i];
        }else if(i > (combinedLength + 1)/2){
            compressed[i] = y[i];
        }else{
            String temp = "0";
            //compressed[i] = temp;
        }
    }
    return compressed;
}

String MC_Communication::*decompString(String x){
    String *newStr = (String*)malloc(2);
    uint8_t combLength = x.length();
    String str1,str2;
    for(size_t i = 0;i < combLength;i++){
        str1 = x[i] + x[i];
        //if(x[i] == " "){
    
        //}
    }


}
