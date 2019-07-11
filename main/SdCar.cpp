#include "SdCar.h"
#include <SPI.h>
#include <SD.h>

#define Pin_CS 15

void init_SD(void){
        Serial.println("\ninit SD");
        if (!SD.begin(Pin_CS)) {
                Serial.println("init failed");
        } else Serial.println("init correct");
}
String FileSD(const char* name ) {
        File archivo;
        archivo = SD.open(name);
        if (archivo) {
                //Serial.print("\n");
                //Serial.println(name);

                String Sd_Read= "";
                while (archivo.available()) {
                        char aux = archivo.read();
                        Sd_Read += aux;
                }
                archivo.close();
                //Serial.println(Sd_Read);
                return Sd_Read;
        }
}
