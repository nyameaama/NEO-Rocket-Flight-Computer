#include"LandingLegs.h"

uint8_t currentServosPos;

LLDeploy::LLDeploy(){
    //Attaching Servos to pins
    uint8_t num;
    l1.attach(num);
    l2.attach(num);
    l3.attach(num);
    l4.attach(num);
}

boolean LLDeploy::LLtrigger(){
    //Function returns bool. If craft is above landing leg deploy margin,
    //function returns false meaning that landing legs should be in retracted
    //position but if function returns true craft is below margin, landing
    //legs should be deployed.
    boolean trigger = true;
    uint8_t *ulSensor = (uint8_t*)malloc(2);
    ulSensor[0] = TRIG_PIN;
    ulSensor[1] = ECHO_PIN;
    uint16_t groundLevel;
    uint16_t ground_margin = groundLevel + 10;
    uint16_t ultrasonics = ul.ultrasonic_sensor_calib( ulSensor[0],ulSensor[1]);
    if(ultrasonics < ground_margin){
        trigger = true;
        free(ulSensor);
    }else if(ultrasonics > ground_margin){
        trigger = false;
    }
    free(ulSensor);
    return trigger;
}

uint8_t LLDeploy::deploy(){
    boolean trig = LLtrigger();
    if(trig == true){
        uint8_t iter = currentServosPos;
        while(iter != DEPLOYED_POSITION){
            sequentialMove(iter);
            iter++;
        }
        currentServosPos = iter;
    }else {
        return 0;
    }
}

uint8_t LLDeploy::retract(){
    boolean trigger = LLtrigger();
    if(trigger == false){
        uint8_t count = currentServosPos;
        while(count != RETRACTED_POSITION){
            sequentialMove(count);
            count--;
        }
        currentServosPos = count;
    }else {
        return 0;
    }
}

uint8_t LLDeploy::sequentialMove(uint8_t iter){
    uint8_t DELAY_TIME;
    l1.write(iter);
    delay(DELAY_TIME);
    l2.write(iter);
    delay(DELAY_TIME);
    l3.write(iter);
    delay(DELAY_TIME);
    l4.write(iter);
    delay(DELAY_TIME);
    return 1;
}

uint8_t* LLDeploy::compilePos(){
    uint8_t *positions = (uint8_t*)malloc(4);
    for(int i = 0; i < 4;i++){
        positions[i] = currentServosPos;
    }
    return positions;
}

boolean LLDeploy::verifyStatus(uint8_t x){
    uint8_t *pos = compilePos();
    boolean flag = true;
    if(x == DEPLOYED_POSITION){
        for(size_t i = 0;i < 4;i++){
            if(pos[i] != DEPLOYED_POSITION){
                flag = false;
            }
        }
        free(pos);
        return flag;
    }
    if(x == RETRACTED_POSITION){
        for(size_t i = 0;i < 4;i++){
            if(pos[i] != RETRACTED_POSITION){
                flag = false;
            }
        }
        free(pos);
        return flag;
    }
}

uint8_t LLDeploy::LL_controller(){
    if(LLtrigger() == true){
        deploy();
        if(verifyStatus(DEPLOYED_POSITION) == true){
            return 1;
        }else{

        }
    }else if(LLtrigger() == false){
        retract();
        if(verifyStatus(RETRACTED_POSITION) == true){
            return 1;
        }else{

        }
    }    
}