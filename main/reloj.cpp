#include <Wire.h>  // Incluye la librería Wire
#include <RTClib.h> // Incluye la librería RTClib
RTC_DS1307 RTC; // Crea el objeto RTC

void set_rtcFecha(int year, int month, int day, int hour, int minute, int second) {
        RTC.adjust(DateTime(year, month, day, hour, minute, second));
}

String timeNowHours(void) {
        DateTime now = RTC.now(); // Obtiene la fecha y hora del RTC

        String aux = "";
        if(now.hour() < 10) {
                aux += "0";
                aux+=now.hour();
        }else aux+=now.hour();
        aux +=":";

        if(now.minute() < 10) {
                aux += "0";
                aux+=now.minute();
        }else aux+=now.minute();
        aux +=":";

        if(now.second() < 10) {
                aux += "0";
                aux+=now.second();
        }else aux+=now.second();

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
void init_rtc (void) {
        Wire.begin(); // Establece la velocidad de datos del bus I2C
        RTC.begin(); // Establece la velocidad de datos del RTC

        //RTC.adjust(DateTime(__DATE__, __TIME__));

        Serial.print("\nInit RTC");
        Serial.print(" "+timeNowDate()+" "+timeNowHours());
}
