#include "Web.h"

void setup() {
  Serial.begin(115200);
  //pinMode(12,OUTPUT);
  //pinMode(11,OUTPUT);

  //digitalWrite(12,HIGH);
  //digitalWrite(11,LOW);

  init_Server();
}

void loop() {
  relog_Server();
}
