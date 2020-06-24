#include"LED_Buzzer.h"

uint8_t blinkCombinations[3][5] = { {1,0,1,0,1,},
                                    {1,0,0,0,1},
                                    {0,0,1,0,0}};

LED_BUZZER::LED_BUZZER(){
  //LED
    pinMode(8, OUTPUT);
    pinMode(13,OUTPUT);
    melody[0] = NOTE_C4;
    melody[1] = NOTE_G3;
    melody[2] = NOTE_G3;
    melody[3] = NOTE_A3;
    melody[4] = NOTE_G3;
    melody[5] = 0;
    melody[6] = NOTE_B3;
    melody[7] = NOTE_C4;
    noteDurations[0] = 4;
    noteDurations[1] = 8; 
    noteDurations[1] = 8; 
    noteDurations[1] = 4; 
    noteDurations[1] = 4;
    noteDurations[1] = 4;
    noteDurations[1] = 4;
    noteDurations[1] = 4;
    //Button
    //initialize the pushbutton pin as an input:
    pinMode(BUTTON_PIN, INPUT);
    //Electric Ignitor
    pinMode(IGNITE_PIN,OUTPUT);
}

void LED_BUZZER::playTone(){
    // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

void LED_BUZZER::blink(uint8_t x){
  for(size_t i = 0; i < 3;i++){
    if(x == i){
      for(size_t j = 0; j < 5;j++){
        playCombination(blinkCombinations[i][j]);
      }
      break;
    }
  }
}

template <typename type>
void LED_BUZZER::playCombination(type x){
  uint8_t low = 0, high = 0;
  if(x == low){
    digitalWrite(8,LOW);
    digitalWrite(13,LOW);
  }else if(x == high){
    digitalWrite(8,HIGH);
    digitalWrite(13,HIGH);
  }
}

boolean LED_BUZZER::buttonPressed(){
   // read the state of the pushbutton value:
  uint8_t buttonState = digitalRead(BUTTON_PIN);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    return true;
  } else {
    return false;
  }
}
