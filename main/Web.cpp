#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "SdCar.h"
#include "reloj.h"
#include "led.h"


ESP8266WebServer Server(80);                              //Webserver Object
#define ssid      "Fibertel WiFi528 2.4GHz"
#define password  "jm_23242526"
//#define ssid      "EEST1VL"
//#define password  "exo-2011"

void init_Web(void);
bool login(void);
void data(void);
void home(void);

void response(void);

void init_pins(void);
void relojclip(void); // funcion de comparacion de los relojes

void init_Server(void) {
        Serial.print("\nInit WEB and WiFi");

        //WiFi.mode(WIFI_AP);
        //WiFi.softAP("ESP_AA", "12345");

        WiFi.mode(WIFI_STA);                   //Wifi mode Station
        WiFi.begin(ssid, password);



        while (WiFi.status() != WL_CONNECTED) {
                delay(500);
                Serial.print(".");
        }
        init_SD();
        init_rtc();
        init_pins();
//        init_led();

//        color_led(1,0,0);
        init_Web();
        //set_rtcFecha(2019, 8, 8, 15, 22, 0);
}

void init_Web(void) {

        Server.on("/", login);          //funtion with call to login in the index
        Server.on("/data", data);
        Server.on("/home", home);
        Server.on("/response", response);

        Server.begin();                         //Start the server
        Serial.print("\nServer listening in: ");
        Serial.print(WiFi.localIP());
}

void relog_Server(void) {
        relojclip();
        Server.handleClient();
}

bool login(void) {
        Server.send(200, "text/html", FileSD("index.html") );
}

void data(void) {
        if (Server.hasArg("USER") && Server.hasArg("PASS")) {
                if (Server.arg("USER") == "admin" && Server.arg("PASS") == "admin") {
                        Serial.print("\n-- Username=" + Server.arg("USER") + " Password=" + Server.arg("PASS"));

                        Server.sendHeader("Location", "/home");
                        Server.sendHeader("Cache-Control", "no-cache");
                        Server.sendHeader("Set-Cookie", "SESION=1");
                        Server.send(301);
                } else {
                        Server.sendHeader("Location", "/");
                        Server.sendHeader("Cache-Control", "no-cache");
                        Server.sendHeader("Set-Cookie", "SESION=0");
                        Server.send(301);
                }
        }
        if(Server.hasArg("datos")) {
                //Serial.print(Server.arg("datos"));
                String aux = Server.arg("datos");

                writeSD("config.xml",aux);

                XML XML;
                XML.read("config.xml");

                XML.needDatas();

                Server.sendHeader("Location", "/home");
                Server.sendHeader("Cache-Control", "no-cache");
                Server.send(301);
        }
}

void home(void) {
        Server.send(200, "text/html", FileSD("home.html"));
}

void response(void) {
        XML XML;
        XML.read("config.xml");
        XML.writeParam("time", timeNowHours());

        Server.send(200, "text/xml",XML.returnStr());
}

#define CantBox 10

#define pinOutA 10
#define pinOutB 11

void init_pins(void){
        pinMode(pinOutA,OUTPUT);
        //pinMode(pinOutB,OUTPUT);


        digitalWrite(pinOutA,LOW);
        //digitalWrite(pinOutB,LOW);

        Serial.print("\ninit pins configurados");
}
void relojclip(void){
        static char aux = 0;
        static unsigned long before= 0, soundtime=millis()+500;
        static char outVarA=0,outVarB=0;

        if(millis()>before) {
                String time = timeNowHours();
                for(char i=0; i<CantBox; i++) {
                        if(Timbres[i].time == time) {
                                if(Timbres[i].outA) outVarA=1;
                                if(Timbres[i].outB) outVarB=1;
                                soundtime=millis()+500;
                        }
                }
                before=millis()+1000;
        }

        if (outVarA) {
                if(millis()>soundtime) {
                        digitalWrite(pinOutA,LOW);
                }else digitalWrite(pinOutA,HIGH);
        }
        if (outVarB) {
                if(millis()>soundtime) {
                        digitalWrite(pinOutB,LOW);
                }else digitalWrite(pinOutB,HIGH);
        }

}
