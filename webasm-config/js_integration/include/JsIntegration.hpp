#ifndef JsIntegration_hpp
#define JsIntegration_hpp
#include <iostream>

std::string getArduinoState(int index);

void js_sleepAsync(int ms);

void js_notifyUpdate();

void js_notifyFinished();

bool shouldStop();

void stopLoop();

#endif //JsIntegration_hpp