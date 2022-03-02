#include "serial.h"
#include <iostream>

void serial::begin(int baud){
    m_baud = baud;
}

void serial::print(std::string str){
    std::cout<<str;
    //__console_log(str.c_str(), str.size());
}

void serial::println(std::string str){
    std::cout<<str<<std::endl;
    //__console_log(str.c_str(), str.size());
}