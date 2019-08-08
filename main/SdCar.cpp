#include "SdCar.h"
#include <SPI.h>
#include <SD.h>

#define Pin_CS 15

void init_SD(void) {
        Serial.print("\ninit SD");
        if (!SD.begin(Pin_CS)) {
                Serial.print("-init failed");
        } else Serial.print("-init correct");
}
String FileSD(const char* name) {
        File archivo;
        archivo = SD.open(name, FILE_READ);

        if (archivo) {
                //Serial.print("\n");
                //Serial.println(name);
                String Sd_Read = "";
                while (archivo.available()) {
                        char aux = archivo.read();
                        Sd_Read += aux;
                }
                archivo.close();
                //Serial.println(Sd_Read);
                return Sd_Read;
        }


}

void XML::read(const char* name){
        inStr=FileSD(name);
}

String XML::readParam(String needParam){
        if (inStr.indexOf("<" + needParam + ">") > 0) {
                int CountChar = needParam.length();
                int indexStart = inStr.indexOf("<" + needParam + ">");
                int indexStop = inStr.indexOf("</" + needParam + ">");
                return inStr.substring(indexStart + CountChar + 2, indexStop);
        }
        return "not found";
}

void XML::writeParam(String needParam,String writeParam){
        if (inStr.indexOf("<" + needParam + ">") > 0) {
                int CountCharTotal = inStr.length();
                int CountChar = needParam.length();
                int indexStart = inStr.indexOf("<" + needParam + ">");
                int indexStop = inStr.indexOf("</" + needParam + ">");

                inStr = inStr.substring(0,indexStart + CountChar + 2) + writeParam + inStr.substring(indexStop,CountCharTotal);
        }
}
String XML::returnStr(void){
        return (inStr);
}
