#include "WiFi.h"

void setup(){
  Serial.begin(115200);
  Serial.println();
  Serial.print("ESP32 Board MAC Address:  ");
  Serial.println(WiFi.macAddress());
}

void loop(){
  // Nothing to do here
}
