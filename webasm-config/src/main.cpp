//esse código sempre existe

//linka com o setup / loop vindo do usuário
extern void setup(); 
extern void loop();

int main(){

    setup();

    while(true)
        loop();

    return 0;
}