#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include <Adafruit_BMP280.h>

// REPLACE WITH THE MAC ADDRESS OF YOUR RECEIVER(S)
// You can add up to 20 receivers
uint8_t broadcastAddress1[] = {0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX};
// uint8_t broadcastAddress2[] = {0xYY, 0xYY, 0xYY, 0xYY, 0xYY, 0xYY};

// I2C pins for ESP32-C3 Supermini
#define I2C_SDA 8
#define I2C_SCL 9

Adafruit_AHTX0 aht;
Adafruit_BMP280 bmp;

// Define a data structure
typedef struct struct_message {
    float temp_aht;
    float humidity;
    float temp_bmp;
    float pressure;
} struct_message;

// Create a struct_message called myData
struct_message myData;

esp_now_peer_info_t peerInfo;

// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {
  Serial.begin(115200);
  
  // Initialize I2C and Sensors
  Wire.begin(I2C_SDA, I2C_SCL);
  if (!aht.begin() || !bmp.begin()) {
    Serial.println("Sensor error!");
    return;
  }

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer(s)
  memcpy(peerInfo.peer_addr, broadcastAddress1, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  // To add more peers, repeat the memcpy, and esp_now_add_peer block
}
 
void loop() {
  // Read sensor data
  sensors_event_t humidity_event, temp_aht_event;
  aht.getEvent(&humidity_event, &temp_aht_event);
  
  myData.temp_aht = temp_aht_event.temperature;
  myData.humidity = humidity_event.relative_humidity;
  myData.temp_bmp = bmp.readTemperature();
  myData.pressure = bmp.readPressure() / 100.0F;

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(0, (uint8_t *) &myData, sizeof(myData)); // 0 means send to all peers
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  } else {
    Serial.println("Error sending the data");
  }
  delay(5000);
}
