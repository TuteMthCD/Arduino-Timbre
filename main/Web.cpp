#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "SdCar.h"

ESP8266WebServer Server(80);                              //Webserver Object
#define ssid      "EEST1VL"
#define password  "exo-2011"

void init_Web(void);
bool login(void);
void data(void);
void home(void);

void hora(void);
void horaxml(void);

void init_Server(void){
        Serial.print("\nInit WEB and WiFi");

        WiFi.mode(WIFI_STA);                         //Wifi mode Station
        WiFi.begin(ssid, password);

        //  WiFi.mode(WIFI_AP);
        //  WiFi.softAP("ESP_AA", "12345");

        while (WiFi.status() != WL_CONNECTED) {
                delay(500);
                Serial.print(".");
        }
        init_SD();
        init_Web();
}

void init_Web(void){
        Server.on("/", login);                //funtion with call to login in the index
        Server.on("/data",data);
        Server.on("/home",home);
        Server.on("/hora",hora);
        Server.on("/obtenerXML",horaxml);

        Server.begin();                               //Start the server
        Serial.print("\nServer listening in: ");
        Serial.print(WiFi.localIP());
}

void relog_Server(void) {
        Server.handleClient();
        hola = millis();
}

bool login(void) {
        Server.send(200, "text/html", FileSD("index.html") );
}

void data(void){
        if (Server.hasArg("USER") && Server.hasArg("PASS")) {
                if(Server.arg("USER")== "admin" && Server.arg("PASS")== "admin") {
                        Serial.print("\n-- Username="+ Server.arg("USER") + " Password="+Server.arg("PASS"));

                        Server.sendHeader("Location", "/home");
                        Server.sendHeader("Cache-Control", "no-cache");
                        Server.sendHeader("Set-Cookie", "SESION=1");
                        Server.send(301);
                }else {
                        Server.sendHeader("Location", "/");
                        Server.sendHeader("Cache-Control", "no-cache");
                        Server.sendHeader("Set-Cookie", "SESION=0");
                        Server.send(301);
                }
        }
}

void home(void){
        if(login()) {
                Server.send(200, "text/plain", "BIEN SOS UN WN" );
        }
}

void horaxml(void){
        Server.send(200, "text/plain",FileSD("home.html"));
}
