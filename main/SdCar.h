#include <Arduino.h>

void init_SD(void);
String FileSD(const char*);

class XML {
private:
        String inStr;
public:
        void read(const char*);
        String readParam(String);
        void writeParam(String, String);
        String returnStr(void);
};
