#include "WiFi.h"

void setup(){
  Serial.begin(115200);
  Serial.println();

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Setup done");
  Serial.print("ESP32 Board MAC Address:  ");
  Serial.println(WiFi.macAddress());
}

void loop(){
  // Nothing to do here
}
