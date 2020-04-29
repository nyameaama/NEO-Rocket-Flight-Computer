#ifndef LEDBUZZER
#define LEDBUZZER

#include"pitches.h"
#include<Arduino.h>

class LED_BUZZER {
    private:
        // notes in the melody:
        int melody[];
        // note durations: 4 = quarter note, 8 = eighth note, etc.:
        int noteDurations[];

    public:
        //Constructor
        LED_BUZZER();

        //Function to play tone
        void playTone();

};

#endif