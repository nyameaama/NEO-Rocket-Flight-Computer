#ifndef LEDBUZZER
#define LEDBUZZER

#include"pitches.h"
#include<Arduino.h>

#define LED_PIN 0

class LED_BUZZER {
    private:
        // notes in the melody:
        int melody[];
        // note durations: 4 = quarter note, 8 = eighth note, etc.:
        int noteDurations[];

    private:
            

    public:
        //Constructor
        LED_BUZZER();

        //Function to play tone
        void playTone();

        //Function to blink LED
        void blink();


};

#endif