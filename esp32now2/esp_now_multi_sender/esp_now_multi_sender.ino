#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include <Adafruit_BMP280.h>

// REPLACE WITH THE MAC ADDRESS OF YOUR SINGLE RECEIVER
uint8_t broadcastAddress[] = {0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX};

// I2C pins for ESP32-C3 Supermini
#define I2C_SDA 8
#define I2C_SCL 9

Adafruit_AHTX0 aht;
Adafruit_BMP280 bmp;

// Define a data structure
typedef struct struct_message {
    int id; // Unique ID for each sender board
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

  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}
 
void loop() {
  // Set a unique ID for each sender board
  // CHANGE THIS FOR EACH SENDER (1, 2, 3, etc)
  myData.id = 1; 

  // Read sensor data
  sensors_event_t humidity_event, temp_aht_event;
  aht.getEvent(&humidity_event, &temp_aht_event);
  
  myData.temp_aht = temp_aht_event.temperature;
  myData.humidity = humidity_event.relative_humidity;
  myData.temp_bmp = bmp.readTemperature();
  myData.pressure = bmp.readPressure() / 100.0F;

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  } else {
    Serial.println("Error sending the data");
  }
  delay(5000);
}
