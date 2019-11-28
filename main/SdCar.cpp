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
        //SD.remove("config.xml");
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
void writeSD(String name,String text){
        File archivo;

        //SD.remove("config.xml");

        archivo = SD.open(name, FILE_WRITE);

        if (archivo) {
                archivo.seek(0);
                for(unsigned int i=0; i<text.length(); i++) archivo.print(" ");
                archivo.seek(0);
                archivo.print(text);
                archivo.close();
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

void XML::writeParam(String parametro,String writeParam){
        if (inStr.indexOf("<" + parametro + ">") > 0) {
                int CountCharTotal = inStr.length();
                int CountChar = parametro.length();
                int indexStart = inStr.indexOf("<" + parametro + ">");
                int indexStop = inStr.indexOf("</" + parametro + ">");

                inStr = inStr.substring(0,indexStart + CountChar + 2) + writeParam + inStr.substring(indexStop,CountCharTotal);
        }
}

String XML::needParam(String parametro, String str){
        if (inStr.indexOf("<" + parametro + ">") > 0) {
                int indexStart = str.indexOf("<" + parametro + ">");
                int indexStop = str.indexOf("</" + parametro + ">");

                str = str.substring(indexStart + parametro.length() + 2,indexStop);
                return(str);
        }else return "not found";
}

String XML::returnStr(void){
        return (inStr);
}
void XML::needDatas(void){
        String datalist = needParam("datalist",inStr);
        String box[CantBox];

        for(char i=0; i < CantBox; i++ ) {
                box[i] = needParam("box",datalist);
                int boxEnd=datalist.indexOf("</box>")+6;
                datalist = datalist.substring(boxEnd,datalist.length());
        }


        for(char i=0; i<CantBox; i++) {
                Timbres[i].time= needParam("time", box[i]);

                if(needParam("outA",box[i])=="Y") {
                        Timbres[i].outA=1;
                }else Timbres[i].outA=0;

                if(needParam("outB",box[i])=="Y") {
                        Timbres[i].outB=1;
                }else Timbres[i].outB=0;


                Serial.println(Timbres[i].time);
                //Serial.println(Timbres[i].outA);
                //Serial.println(Timbres[i].outB);

                //__asm__ ("nop\n\t");
                //__asm__ ("nop\n\t");
                //__asm__ ("nop\n\t");
        }
}
