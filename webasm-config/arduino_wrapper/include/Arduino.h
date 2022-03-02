#ifndef Arduino_h
#define Arduino_h

#include "serial.h"
#include <string>

static serial Serial = serial();

#define LED_BUILTIN 13

#define OUTPUT 0
#define INPUT 1
#define HIGH 1
#define LOW 0


void pinMode(int pin, int mode);

void digitalWrite(int pin, int val);

void delay(int ms);

/*JS integration*/
std::string _getArduinoState(int index);
#endif