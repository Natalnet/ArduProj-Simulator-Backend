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

void pinMode(int pin, int mode){
    pin_mode[pin] = mode;
}

void digitalWrite(int pin, int val){
    if(pin_mode[pin] == OUTPUT && val != pin_values[pin]){
        pin_values[pin] = val;
        js_notifiUpdate();
    }
}

void delay(int ms){
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
void updateAruinoState(std::string state){

}

