#include <esp_now.h>
#include <WiFi.h>

// REPLACE WITH THE MAC ADDRESS OF YOUR RECEIVER(S)
// You can add up to 20 receivers
uint8_t broadcastAddress1[] = {0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX}; // Receiver 1
uint8_t broadcastAddress2[] = {0xYY, 0xYY, 0xYY, 0xYY, 0xYY, 0xYY}; // Receiver 2
// Add more broadcastAddressX[] for more receivers

// Define the button pin
const int buttonPin = 0; // GPIO0 - Be careful, this is also a boot pin!

// Define a data structure
typedef struct struct_message {
    int id; // ID of the sender board (e.g., 1 for this sender)
    bool buttonState; // true if button pressed
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
  // Add more peerInfoX and esp_now_add_peer for more receivers
}
 
void loop() {
  // Set a unique ID for this sender board
  myData.id = 1; 

  // Read the state of the button
  // The button is connected to INPUT_PULLUP, so LOW means pressed
  if (digitalRead(buttonPin) == LOW) {
    // Debounce delay
    delay(50);
    if (digitalRead(buttonPin) == LOW) { // Confirm button press
      myData.buttonState = true; // Button is pressed
      // Send message via ESP-NOW to all registered peers
      esp_err_t result = esp_now_send(0, (uint8_t *) &myData, sizeof(myData));
       
      if (result == ESP_OK) {
        Serial.println("Sent button pressed signal to all receivers");
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
