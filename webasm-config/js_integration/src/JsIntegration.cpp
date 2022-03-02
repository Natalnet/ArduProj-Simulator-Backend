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

using namespace emscripten;

EM_JS(void, _notifyUpdate, (), {
  console.log('Notify update called');
  console.log('Calling self.notifyUpdate ' + self.notifyUpdate); //defined in worker or in global self
  self.notifyUpdate();
});

std::string getArduinoState(int index){
    return _getArduinoState(index);
}

void js_sleepAsync(int ms){
    emscripten_sleep(ms);
}

void js_notifiUpdate(){
    _notifyUpdate();
}


EMSCRIPTEN_BINDINGS(module) {
    function("getArduinoState", &getArduinoState);
}



