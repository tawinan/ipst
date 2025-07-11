#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h> // Needed for esp_now_recv_info_t

// Define a data structure that matches the sender's structure
typedef struct struct_message {
    int id;
    float temp_aht;
    float humidity;
    float temp_bmp;
    float pressure;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// Callback function that will be executed when data is received
void OnDataRecv(const esp_now_recv_info * info, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.println("--------------------------------");
  Serial.print("Data received from board with ID: ");
  Serial.println(myData.id);
  Serial.print("From MAC Address: ");
  for (int i = 0; i < 6; i++) {
    Serial.print(info->src_addr[i], HEX);
    if (i < 5) Serial.print(":");
  }
  Serial.println();
  
  Serial.print("AHT20 Temp: ");
  Serial.println(myData.temp_aht);
  Serial.print("AHT20 Humidity: ");
  Serial.println(myData.humidity);
  Serial.print("BMP280 Temp: ");
  Serial.println(myData.temp_bmp);
  Serial.print("BMP280 Pressure: ");
  Serial.println(myData.pressure);
  Serial.println();
}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
  // Leave blank. All the action happens in the callback function.
}
