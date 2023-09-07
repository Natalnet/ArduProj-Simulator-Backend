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
  console.log('Calling self.notifyUpdate ' + self.notifyUpdate); //defined in worker or in global self
  self.notifyUpdate();
});

EM_JS(void, _notifyFinished, (), {
  console.log('Notify finished called');
  console.log('Calling self.notifyFinished ' + self.notifyFinished); //defined in worker or in global self
  self.notifyFinished();
});

std::string getArduinoState(int index){
    return _getArduinoState(index);
}

void stopLoop(){
    stop = true;
}

bool shouldStop(){
    return stop;
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
    function("stopLoop", &stopLoop);
}



