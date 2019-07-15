#include "SdCar.h"
#include <SPI.h>
#include <SD.h>

#define Pin_CS 15

void init_SD(void) {
  Serial.println("\ninit SD");
  if (!SD.begin(Pin_CS)) {
    Serial.println("init failed");
  } else Serial.println("init correct");
}
String FileSD(const char* name) {
  File archivo;


  /*archivo = SD.open("config_xml", FILE_WRITE);

  if (archivo) {

    archivo.println("Ponele");
    archivo.close();

    Serial.println("Ponele otra vez");
  }*/



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

String readXML(String inStr, String needParam)
{
  if (inStr.indexOf("<" + needParam + ">") > 0) {
    int CountChar = needParam.length();
    int indexStart = inStr.indexOf("<" + needParam + ">");
    int indexStop = inStr.indexOf("</" + needParam + ">");
    return inStr.substring(indexStart + CountChar + 2, indexStop);
  }
  return "not found";
}


String writeXML(String inStr, String needParam)
{
  if (inStr.indexOf("<" + needParam + ">") > 0) {
    int CountChar = needParam.length();
    int indexStart = inStr.indexOf("<" + needParam + ">");



    int indexStop = inStr.indexOf("</" + needParam + ">");
    return inStr.substring(indexStart + CountChar + 2, indexStop);
  }
  return "not found";
}
