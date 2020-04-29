#include"LED_Buzzer.h"

LED_BUZZER::LED_BUZZER(){
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