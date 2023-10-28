#include "JsIntegration.hpp"
//esse código sempre existe

//linka com o setup / loop vindo do usuário
extern void setup(); 
extern void loop();


int main(){

    setup();

    while(!shouldStop()){
        loop();
        js_notifyUpdate();
        std::cout<<js_getAllPinValues(0)<<std::endl;
    }

    js_notifyFinished();

    return 0;
}