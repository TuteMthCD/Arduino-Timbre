#include <Wire.h>  // Incluye la librería Wire
#include <RTClib.h> // Incluye la librería RTClib
RTC_DS1307 RTC; // Crea el objeto RTC

void init_rtc (void) {
  Serial.print("\nInit RTC");
 
  Wire.begin(); // Establece la velocidad de datos del bus I2C
  RTC.begin(); // Establece la velocidad de datos del RTC
  
}
void set_rtcFecha(int year, int month, int day, int hour, int minute, int second) {
  RTC.adjust(DateTime(year, month, day, hour, minute, second));
}

String timeNowHours(void) {
  DateTime now = RTC.now(); // Obtiene la fecha y hora del RTC

  String aux = "";
  aux = now.hour();
  aux += ":" ;
  aux += now.minute();
  aux += ":";
  aux += now.second();
  return (aux);

}

String timeNowDate(void) {
  DateTime now = RTC.now(); // Obtiene la fecha y hora del RTC

  String aux = "";
  aux = now.year();
  aux += "/";
  aux += now.month();
  aux += "/";
  aux += now.day();
  return (aux);

}
