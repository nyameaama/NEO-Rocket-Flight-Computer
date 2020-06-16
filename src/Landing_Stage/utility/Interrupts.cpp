#include"Interrupts.h"

void INTERRUPT_ROUTINE::BUTTON_INTERRUPT(){
    LED_BUZZER trig;
    while(trig.buttonPressed()){
    delayMicroseconds(5000000);
    if(!trig.buttonPressed()){
      //Do nothing
    }else{
      AreaAnalysis routine;
      routine.BRICK_ALL_PROCESSES();
    }
  }
  //While loop terminated which means button wasnt held for > 5 secs
}

 void INTERRUPT_ROUTINE::RF_COMS_INTERRUPT(){
     
 }