#ifndef Arduino_h
#define Arduino_h

#include "serial.h"
#include <string>

static serial Serial = serial();

#define LED_BUILTIN 13

enum PinMode{
    INPUT, OUTPUT
};

enum DigitalState{
    HIGH, LOW
};

void digitalWrite(int pin, int val);

void pinMode(int pin, PinMode mode);

DigitalState digitalRead(int pin);

void delay(int ms);

/*JS integration*/
std::string _getArduinoState(int index);
void _updateArduinoState(int index, std::string pinValues);
#endif