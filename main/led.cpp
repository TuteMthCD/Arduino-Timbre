#include <Arduino.h>

//SD1 RED   GPIO8
//CMD GREEN GPIO11
//SD0 BLUE  GPIO7

void init_led (void){
        pinMode(8, OUTPUT);
        pinMode(11, OUTPUT);
        pinMode(7, OUTPUT);
        Serial.print("\nInit RGB LED");
}

void color_led(unsigned char R, unsigned char G,unsigned char B){
        digitalWrite(8,G);
        digitalWrite(11,R);
        digitalWrite(7,B);
}
