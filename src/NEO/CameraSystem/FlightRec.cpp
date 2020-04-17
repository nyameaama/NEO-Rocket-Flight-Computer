#include "FlightRec.h"

FlightRec::FlightRec(){
    ArduCAM myCAM1(OV3640, CS1);
    uint8_t vid, pid;
   
    Wire.begin();
    Serial.begin(115200);
    Serial.println(F("ArduCAM Start!"));
    // set the CS output:
    pinMode(CS1, OUTPUT);
    digitalWrite(CS1, HIGH);
    // initialize SPI:
    SPI.begin();
    //Reset the CPLD
    myCAM1.write_reg(0x07, 0x80);
    delay(100);
    myCAM1.write_reg(0x07, 0x00);
    delay(100);
    SPI_BUS_CHECK(myCAM1);
    myCAM1.OV3640_set_JPEG_size(OV3640_640x480);
}
void FlightRec::SPI_BUS_CHECK(ArduCAM myCAM1){
    //Check if the 4 ArduCAM Mini 2MP Cameras' SPI bus is OK
     uint8_t temp;
    while (1){
        myCAM1.write_reg(ARDUCHIP_TEST1, 0x55);
        temp = myCAM1.read_reg(ARDUCHIP_TEST1);
        if (temp != 0x55){
            //SPI1 interface Error!
            //Serial.println(F("SPI1 interface Error!"));
        }
        else{
            //SPI1 interface OK
            CAM1_EXIST = true;
            //Serial.println(F("SPI1 interface OK."));
        }
        if (!(CAM1_EXIST)){
            delay(1000);
            continue;
        }
        else{
            break;
        }    
    }
}
byte FlightRec::camCapture(ArduCAM myCAM){
    uint32_t length = 0;
    //Flush the FIFO
    myCAM.flush_fifo();
    //Clear the capture done flag
    myCAM.clear_fifo_flag();
    //Start capture
    myCAM.start_capture();
    //Serial.println("start Capture");
    while (!myCAM.get_bit(ARDUCHIP_TRIG, CAP_DONE_MASK));
    //Serial.println(F("Capture Done."));
    //Get fifo length
    length = myCAM.read_fifo_length();
    //Serial.print(F("The fifo length is :"));
    //Serial.println(length, DEC);
    if (length >= MAX_FIFO_SIZE){ //384K
        //Serial.println(F("Over size."));
        return;
    }
    if (length == 0){ //0KB
        //Serial.println(F("Size is 0."));
        return;
    }
    SavetoSD(length,myCAM);
    
}

uint8_t FlightRec::SavetoSD(uint32_t length,ArduCAM myCAM){
    //Construct a file name 
    static int k = 0;   
    static int i = 0;
    bool is_header = false;
    uint8_t temp = 0, temp_last = 0;
    char str[8];
    byte buf[256];
    File outFile;
    //Open the new file
    outFile = SD.open(ConstructFileName(k,str), O_WRITE | O_CREAT | O_TRUNC);
    if (!outFile){
        Serial.println(F("File open faild"));
        return;
    }
    myCAM.CS_LOW();
    myCAM.set_fifo_burst();
    while (length--){
        temp_last = temp;
        temp = SPI.transfer(0x00);
        //Read JPEG data from FIFO
        if ((temp == 0xD9) && (temp_last == 0xFF)){          //If find the end ,break while,
            buf[i++] = temp; //save the last  0XD9
                             //Write the remain bytes in the buffer
            myCAM.CS_HIGH();
            outFile.write(buf, i);
            //Close the file
            outFile.close();
            Serial.println(F("Image save OK."));
            is_header = false;
            i = 0;
        }
        if (is_header == true){
            //Write image data to buffer if not full
            if (i < 256)
                buf[i++] = temp;
            else{
                //Write 256 bytes image data to file
                myCAM.CS_HIGH();
                outFile.write(buf, 256);
                i = 0;
                buf[i++] = temp;
                myCAM.CS_LOW();
                myCAM.set_fifo_burst();
            }
        }
        else if ((temp == 0xD8) & (temp_last == 0xFF)){
            is_header = true;
            buf[i++] = temp_last;
            buf[i++] = temp;
        }
    }
}

 char *FlightRec::ConstructFileName(int k,char str[28]){
     k = k + 1;
    itoa(k, str, 10);
    strcat(str, ".jpg");
    return str;
 }