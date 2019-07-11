#include "Web.h"

void setup() {
  Serial.begin(115200);
  init_Server();
}

void loop() {
  relog_Server();
}
