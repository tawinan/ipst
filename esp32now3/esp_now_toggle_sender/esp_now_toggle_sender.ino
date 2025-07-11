#include <esp_now.h>
#include <WiFi.h>

// REPLACE WITH THE MAC ADDRESS OF YOUR SINGLE RECEIVER
uint8_t broadcastAddress[] = {0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX};

// Define the button pin
const int buttonPin = 0; // GPIO0 - Be careful, this is also a boot pin!

// Define a data structure
typedef struct struct_message {
    int id; // Unique ID for each sender board
    bool buttonState; // true if button pressed
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
  
  // Initialize the button pin as an input with internal pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);

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

  // Read the state of the button
  // The button is connected to INPUT_PULLUP, so LOW means pressed
  if (digitalRead(buttonPin) == LOW) {
    // Debounce delay
    delay(50);
    if (digitalRead(buttonPin) == LOW) { // Confirm button press
      myData.buttonState = true; // Button is pressed
      // Send message via ESP-NOW
      esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
       
      if (result == ESP_OK) {
        Serial.println("Sent button pressed signal");
      } else {
        Serial.println("Error sending the data");
      }
      // Wait for button release to avoid multiple sends for one press
      while(digitalRead(buttonPin) == LOW) {
        delay(10);
      }
    }
  }
  delay(100); // Small delay to prevent constant checking
}
