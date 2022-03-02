#ifndef JsIntegration_hpp
#define JsIntegration_hpp
#include <iostream>

std::string getArduinoState(int index);

void js_sleepAsync(int ms);

void js_notifiUpdate();

#endif //JsIntegration_hpp