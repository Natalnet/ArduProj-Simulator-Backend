#ifndef JsIntegration_hpp
#define JsIntegration_hpp
#include <iostream>

std::string getArduinoState(int index);

void updateArduinoState(int index, std::string pinValues);

void js_sleepAsync(int ms);

void js_notifyUpdate();

void js_notifyFinished();

int js_digitalRead(int index, int pin);

std::string js_getAllPinValues(int index);

bool shouldStop();

void stopLoop();


#endif //JsIntegration_hpp