#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include <Adafruit_BMP280.h>

// REPLACE WITH THE MAC ADDRESS OF YOUR RECEIVERS
uint8_t broadcastAddress1[] = {0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX}; // Receiver 1
uint8_t broadcastAddress2[] = {0xYY, 0xYY, 0xYY, 0xYY, 0xYY, 0xYY}; // Receiver 2

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

// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status to: ");
  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
  Serial.print("\t");
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

  esp_now_register_send_cb(OnDataSent);
  
  // --- Register Peer 1 ---
  esp_now_peer_info_t peerInfo1;
  memcpy(peerInfo1.peer_addr, broadcastAddress1, 6);
  peerInfo1.channel = 0;  
  peerInfo1.encrypt = false;
  if (esp_now_add_peer(&peerInfo1) != ESP_OK){
    Serial.println("Failed to add peer 1");
    return;
  }

  // --- Register Peer 2 ---
  esp_now_peer_info_t peerInfo2;
  memcpy(peerInfo2.peer_addr, broadcastAddress2, 6);
  peerInfo2.channel = 0;  
  peerInfo2.encrypt = false;
  if (esp_now_add_peer(&peerInfo2) != ESP_OK){
    Serial.println("Failed to add peer 2");
    return;
  }
}
 
void loop() {
  // Read sensor data
  sensors_event_t humidity_event, temp_aht_event;
  aht.getEvent(&humidity_event, &temp_aht_event);
  
  myData.temp_aht = temp_aht_event.temperature;
  myData.humidity = humidity_event.relative_humidity;
  myData.temp_bmp = bmp.readTemperature();
  myData.pressure = bmp.readPressure() / 100.0F;

  // Send message to all registered peers
  // The first argument (0 or NULL) sends to all peers
  esp_err_t result = esp_now_send(0, (uint8_t *) &myData, sizeof(myData)); 
   
  if (result == ESP_OK) {
    Serial.println("Sent message to all peers");
  } else {
    Serial.println("Error sending the data");
  }
  delay(5000);
}
