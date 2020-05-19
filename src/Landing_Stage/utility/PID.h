#ifndef PID
#define PID

#include<Arduino.h>
#include"ErrorDump.h"

//Different instances of PID computation will be called from this class so each unique process will
//need to have constants stored so individual processes can be continued after end of class call

class PROPORTIONAL_INTEGRAL_DERIVATIVE {
    private:
        uint8_t dt;

    private:
        void updateConstants(String Process);

        double getProportional();

        double getIntegral();

        double getDerivative();

        boolean compare(String x, String y);

        boolean checkforInstance(String tag);

    public:
        //
        double PID_MAIN(String Process,double rocketPos,double setpoint);

        void createPIDinstance(String tag,double kp,double ki,double kd);

};



#endif