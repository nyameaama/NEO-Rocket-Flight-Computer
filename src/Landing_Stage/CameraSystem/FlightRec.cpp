#include "FlightRec.h"

FlightRec::FlightRec(){
    noInterrupts(); //Disable all interrupts
    XCLK_SETUP();   //Setup 8MHz clock at pin 11
    OV7670_PINS();  // Setup Data-in and interrupt pins from camera
    delay(1000);
    TWI_SETUP();    // Setup SCL for 100KHz
    interrupts();
    Wire.begin();
    setup.Init_OV7670();
    setup.Init_QVGA();
    setup.Init_YUV422();
    setup.WriteOV7670(0x11, 0x1F); //Range 00-1F
    noInterrupts();
    Serial.begin(9600);
    pinMode(setup.CS_Pin, OUTPUT);
    SD.begin(setup.CS_Pin);
}

void FlightRec::XCLK_SETUP(void){
    // Nyame - > Set output pin
  pinMode(OUTPUT_PIN, OUTPUT); //Set pin 9 to output

  
  //Initialize timer 1
  
  //WGM13, WGM12, WGM11 & WGM10 bits SET- Fast PWM mode
  //COM1A0 SET- Toggle OC1A on compare match
  TCCR1A = (1 << COM1A0) | (1 << WGM11) | (1 << WGM10);
  //SET CS10 bit for clock select with no prescaling
  TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS10); 
  //Output Compare Register 1A(OCR1A) = 0
  //This will lead to a match on every clock cycle
  //Toggle OC1A output pin on every match instance
  //Therefore, the generated waveform will have half
  //the frequency of the driving clock i.e. 8Mhz
  //OC1A pin- PB1 (alternate functn) pin i.e. Arduino pin 9
  OCR1A = 0;

}

// Two Wire Interface Setup
// Sets the frequency of the SCL line
// Default is 100KHz so we won't use this function
void FlightRec::TWI_SETUP(void){
  //Set prescaler bits in TWI Status Register (TWSR) to 0
  TWSR &= ~3;
  //Set SCL frequency to 100KHz
  //SCLfreq = CPUfreq/(16 + 2(TWBR) - 4^(TWPS))
  //TWBR = 72, TWPS(prescaler) = 0
  TWBR = 72;

}

void FlightRec::OV7670_PINS(void){
  //Setup Data input pins and Interrupt pins
  //DDRC bits 3:0 = 0 =>  bits configured as Data Inputs
  //DDRC 3:0 - A3,A2,A1,A0
  DDRC &= ~15;//low d0-d3 camera
  
  //~(0b11111100) = 0b00000011
  //make DDRD 7:2 = 0 => Inputs
  //d7-d4 as data inputs, d3-INT1 is VSYNC and d2-INT0 is PCLK
  DDRD &= ~252;
}

void FlightRec::QVGA_Image(String title){
  int h,w;
  
  File dataFile = SD.open(title, FILE_WRITE);
  while (!(PIND & 8));//wait for high
  while ((PIND & 8));//wait for low

    h = 240;
  while (h--){
        w = 320;
       byte dataBuffer[320];
    while (w--){
      while ((PIND & 4));   //wait for low
        dataBuffer[319-w] = (PINC & 15) | (PIND & 240);
      while (!(PIND & 4));  //wait for high
      while ((PIND & 4));   //wait for low
      while (!(PIND & 4));  //wait for high
    }
    dataFile.write(dataBuffer,320);

    
  }

    dataFile.close();
    delay(100);
}

 void FlightRec::camCapture(String FileName){
     QVGA_Image(FileName);
 }
