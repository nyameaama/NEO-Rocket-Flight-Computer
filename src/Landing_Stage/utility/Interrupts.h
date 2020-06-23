#ifndef INTERRUPT
#define INTERRUPT

#include"../Trigger Systems/AreaAnalysis.h"
#include"../Trigger Systems/Misc/LED_Buzzer.h"
#include"../RF Comm/Transmit/DataHandling/Assign.h"


class INTERRUPT_ROUTINE {
    public:
        void BUTTON_INTERRUPT();

        void RF_COMS_INTERRUPT();
};

#endif