#ifndef serial_h
#define serial_h

#include <string>
/**
 * Wrapper to arduino serial class
*/
class serial{
    private:
        int m_baud;
    public:
        void begin(int baudRate);
        void print(std::string string);
        void println(std::string string);
};

#endif //serial_h