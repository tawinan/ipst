#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h> // Needed for esp_now_recv_info_t

// Define the LED pin
const int ledPin = 0; // GPIO0 - Be careful, this is also a boot pin!

// Define a data structure that matches the sender's structure
typedef struct struct_message {
    int id; // Unique ID for each sender board
    bool buttonState; // true if button pressed
} struct_message;

// Create a struct_message called myData
struct_message myData;

// Keep track of the LED state
bool ledState = true; // Start with LED ON (HIGH)

// Callback function that will be executed when data is received
void OnDataRecv(const esp_now_recv_info * info, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.println("--------------------------------");
  Serial.print("Data received from Sender ID: ");
  Serial.println(myData.id);
  Serial.print("From MAC Address: ");
  for (int i = 0; i < 6; i++) {
    Serial.print(info->src_addr[i], HEX);
    if (i < 5) Serial.print(":");
  }
  Serial.println();
  
  if (myData.buttonState == true) { // Only act on button press signal
    ledState = !ledState; // Toggle the LED state
    digitalWrite(ledPin, ledState ? HIGH : LOW);
    Serial.print("LED State: ");
    Serial.println(ledState ? "ON" : "OFF");
  }
  Serial.println();
}
 
void setup() {
  Serial.begin(115200);
  
  // Initialize LED pin as an output and set initial state to ON
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH); // LED starts ON

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
