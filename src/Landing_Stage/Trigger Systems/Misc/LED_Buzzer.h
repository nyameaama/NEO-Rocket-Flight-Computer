#ifndef LEDBUZZER
#define LEDBUZZER

#include"pitches.h"
#include"../../utility/utility.h"
#include<Arduino.h>
#include"../AreaAnalysis.h"

#define LED_PIN 0
#define BUTTON_PIN 0
#define IGNITE_PIN 0

class LED_BUZZER {
    private:
        // notes in the melody:
        int melody[];
        // note durations: 4 = quarter note, 8 = eighth note, etc.:
        int noteDurations[];

        Utility com;

    private:
        template <typename type>
        void playCombination(type x);

    public:
        //Constructor
        LED_BUZZER();

        //Function to play tone
        void playTone();

        //Function to blink LED
        void blink(uint8_t x);

        boolean buttonPressed();

        void igniteMotor();


};

#endif