#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include <Adafruit_BMP280.h>

// Replace with your network credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// I2C pins for ESP32-C3 Supermini
#define I2C_SDA 8
#define I2C_SCL 9

WebServer server(80);
Adafruit_AHTX0 aht;
Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(115200);
  
  // Initialize I2C
  Wire.begin(I2C_SDA, I2C_SCL);

  // Initialize sensors
  if (!aht.begin()) {
    Serial.println("Could not find AHT20 sensor!");
    return;
  }
  if (!bmp.begin()) {
    Serial.println("Could not find BMP280 sensor!");
    return;
  }

  // Connect to WiFi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Define web server routes
  server.on("/", handleRoot);
  
  // Start server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  // Read sensor data
  sensors_event_t humidity, temp_aht;
  aht.getEvent(&humidity, &temp_aht);
  float bmp_temp = bmp.readTemperature();
  float bmp_pressure = bmp.readPressure() / 100.0F;

  // HTML web page
  String html = "<!DOCTYPE html><html><head><title>ESP32 Sensor Data</title>";
  html += "<meta http-equiv=\"refresh\" content=\"10\">"; // Auto-refresh every 10 seconds
  html += "<style>body { font-family: Arial, sans-serif; text-align: center; } ";
  html += "h1 { color: #003366; } .sensor-box { border: 1px solid #ccc; padding: 20px; margin: 20px auto; width: 300px; border-radius: 10px; } </style>";
  html += "</head><body>";
  html += "<h1>ESP32-C3 Sensor Monitor</h1>";
  
  html += "<div class=\"sensor-box\">";
  html += "<h2>AHT20 Sensor</h2>";
  html += "<p>Temperature: " + String(temp_aht.temperature) + " &deg;C</p>";
  html += "<p>Humidity: " + String(humidity.relative_humidity) + " %</p>";
  html += "</div>";

  html += "<div class=\"sensor-box\">";
  html += "<h2>BMP280 Sensor</h2>";
  html += "<p>Temperature: " + String(bmp_temp) + " &deg;C</p>";
  html += "<p>Pressure: " + String(bmp_pressure) + " hPa</p>";
  html += "</div>";
  
  html += "</body></html>";

  server.send(200, "text/html", html);
}