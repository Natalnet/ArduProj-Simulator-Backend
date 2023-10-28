#include "Arduino.h"
#include "JsIntegration.hpp"

#include <chrono>
#include <thread>
#include <vector>
#include <iostream>

static uint8_t pin_mode[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static std::vector<uint8_t> pin_values = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
/*state keeps the arduino state in string format so it is easier to use on js side*/
static std::string state;

void pinMode(int pin, PinMode mode){
    pin_mode[pin] = mode;
}

void digitalWrite(int pin, int val){
    if(pin_mode[pin] == PinMode::OUTPUT){
        pin_values[pin] = val;
    }
}

DigitalState fromInt(int value){
    if (value == 1)
        return DigitalState::HIGH;
    return DigitalState::LOW;
}

DigitalState digitalRead(int pin){
    if(pin_mode[pin] == PinMode::INPUT){
        pin_values[pin] = js_digitalRead(0, pin);
        return fromInt(pin_values[pin]);
    }
    //poderia disparar uma exception aqui
    return fromInt(pin_values[pin]);
}

void delay(int ms){
    js_notifyUpdate();
    js_sleepAsync(ms);
}


std::string _getArduinoState(int index){
    state = "[";
    for(int i=0; i<pin_values.size(); i++ ){
        state += std::to_string(pin_values[i]) + ",";
    }
    state.pop_back();//remove last ','
    state += "]";
    /*
    std::cout<<"Value of state "<<state<<" size "<<state.size()<<std::endl;
    std::cout<<" size pin values "<<pin_values.size()<<std::endl;
    std::cout<<" size pin_mode values "<<sizeof(pin_mode)<<std::endl;
    */
    return state;
}



/*recebe um vetor de valores com os estados no mesmo formato do getState*/
void _updateArduinoState(int index, std::string pinValues){

    std::cout<<"values gotten from js "<<index<<" "<<pinValues<<std::endl;

}

