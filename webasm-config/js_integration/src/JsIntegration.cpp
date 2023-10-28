#include "Arduino.h"
#include <emscripten/bind.h>



/*
this will put -s EXPORTED_FUNCTIONS='["__console_log"]' automatically on compilation
*/
/*Should print the string received*/
/*EM_JS(void, __console_log, (const char*, int size), {
    implementation comes from frontend
})

int _getArduinoState (int index){
    const char* state = getArduinoState(index);
    buffer myBuffer;
    myBuffer.pointer = state; 
    myBuffer.size = strlen(state);
    return myBuffer.size;
}
*/
#include <emscripten.h>
#include <iostream>

using namespace emscripten;

static bool stop = false;

EM_JS(void, _notifyUpdate, (), {
  console.log('Notify update called');
  self.notifyUpdate();
});

EM_JS(void, _notifyFinished, (), {
  console.log('Notify finished called');
  self.notifyFinished();
});

EM_JS(char*, _getPinValues, (), {
    var str = self.getPinValues();
    var strLength = lengthBytesUTF8(str) + 1;
    var buffer = _malloc(strLength);
    stringToUTF8(str, buffer, strLength);
    return buffer; 
});

EM_JS(int, _digitalRead, (int index, int pin), {
    var pinVal = self.digitalRead(index, pin);
    return pinVal; 
});

std::string getArduinoState(int index){
    return _getArduinoState(index);
}

void updateArduinoState(int index, std::string pinValues){
    return _updateArduinoState(index, pinValues);
}


void stopLoop(){
    stop = true;
}

bool shouldStop(){
    return stop;
}

std::string js_getAllPinValues(int index){
    return std::string(_getPinValues());
}

int js_digitalRead(int index, int pin){
    return _digitalRead(index, pin);
}

void js_sleepAsync(int ms){
    emscripten_sleep(ms);
    std::cout << "sleep break" << std::endl;
}

void js_notifyUpdate(){
    _notifyUpdate();
}

void js_notifyFinished(){
    _notifyFinished();
}


EMSCRIPTEN_BINDINGS(module) {
    function("getArduinoState", &getArduinoState);
    function("updateArduinoState", &updateArduinoState);
    function("stopLoop", &stopLoop);
}



