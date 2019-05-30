#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);                              //Webserver Object
#define ssid      "Fibertel WiFi528 2.4GHz"
#define password  "jm_23242526"

void init_Web(void);
void login(void);

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
        init_Web();
}

void init_Web(void){
        server.on("/", login);                              //funtion with call to login in the index
        server.begin();                                     //Start the server
        Serial.print("\nServer listening in: ");
        Serial.print(WiFi.localIP());
}

void login(void) {
        server.send(200, "text/html", "hola" );
}

void relog_Server(void) {
        server.handleClient();
}
