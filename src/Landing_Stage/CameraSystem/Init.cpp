#include"Init.h"

void Init::Init_YUV422(){
  WriteOV7670(0x12, 0x00);//COM7
  WriteOV7670(0x8C, 0x00);//RGB444
  WriteOV7670(0x04, 0x00);//COM1
  WriteOV7670(0x40, 0xC0);//COM15
  WriteOV7670(0x14, 0x1A);//COM9
  WriteOV7670(0x3D, 0x40);//COM13
  }

void Init::Init_QVGA(){
  WriteOV7670(0x0C, 0x04);//COM3 - Enable Scaling
  WriteOV7670(0x3E, 0x19);//COM14
  WriteOV7670(0x72, 0x11);//
  WriteOV7670(0x73, 0xF1);//
  WriteOV7670(0x17, 0x16);//HSTART
  WriteOV7670(0x18, 0x04);//HSTOP
  WriteOV7670(0x32, 0xA4);//HREF
  WriteOV7670(0x19, 0x02);//VSTART
  WriteOV7670(0x1A, 0x7A);//VSTOP
  WriteOV7670(0x03, 0x0A);//VREF
}

void Init::Init_OV7670(){
  //Reset All Register Values
  WriteOV7670(0x12,0x80);
  delay(100);
  WriteOV7670(0x3A, 0x04); //TSLB
 
  WriteOV7670(0x13, 0xC0); //COM8
  WriteOV7670(0x00, 0x00); //GAIN
  WriteOV7670(0x10, 0x00); //AECH
  WriteOV7670(0x0D, 0x40); //COM4
  WriteOV7670(0x14, 0x18); //COM9
  WriteOV7670(0x24, 0x95); //AEW
  WriteOV7670(0x25, 0x33); //AEB
  WriteOV7670(0x13, 0xC5); //COM8
  WriteOV7670(0x6A, 0x40); //GGAIN
  WriteOV7670(0x01, 0x40); //BLUE
  WriteOV7670(0x02, 0x60); //RED
  WriteOV7670(0x13, 0xC7); //COM8
  WriteOV7670(0x41, 0x08); //COM16
  WriteOV7670(0x15, 0x20); //COM10 - PCLK does not toggle on HBLANK
  }

void Init::WriteOV7670(byte regID, byte regVal){
  // Slave 7-bit address is 0x21.
  // R/W bit set automatically by Wire functions
  // dont write 0x42 or 0x43 for slave address
  Wire.beginTransmission(0x21);
  // Reset all register values
  Wire.write(regID);  
  Wire.write(regVal);
  Wire.endTransmission();
  delay(1);
  
  }

void Init::ReadOV7670(byte regID){
  // Reading from a register is done in two steps
  // Step 1: Write register address to the slave 
  // from which data is to be read. 
  Wire.beginTransmission(0x21); // 7-bit Slave address
  Wire.write(regID);  // reading from register 0x11
  Wire.endTransmission();

  // Step 2: Read 1 byte from Slave
  Wire.requestFrom(0x21, 1);
  Serial.print("Read request Status:");
  Serial.println(Wire.available());
  Serial.print(regID,HEX);
  Serial.print(":");
  Serial.println(Wire.read(),HEX);
  }

