#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include <Adafruit_BMP280.h>

// I2C pins for ESP32-C3 Supermini
#define I2C_SDA 8
#define I2C_SCL 9

Adafruit_AHTX0 aht;
Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(10); // wait for serial port to connect.
  }

  Serial.println("AHT20 & BMP280 Sensor Test");

  // Initialize I2C
  Wire.begin(I2C_SDA, I2C_SCL);

  // Initialize AHT20
  if (!aht.begin()) {
    Serial.println("Could not find AHT20 sensor! Check wiring.");
    while (1) delay(10);
  }
  Serial.println("AHT20 Found!");

  // Initialize BMP280
  // Note: The BMP280 address may be 0x76 or 0x77. The library defaults to 0x77.
  // If your sensor is not found, try bmp.begin(0x76)
  if (!bmp.begin()) { 
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or I2C address!"));
    while (1) delay(10);
  }
  Serial.println("BMP280 Found!");

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void loop() {
  sensors_event_t humidity, temp_aht;
  aht.getEvent(&humidity, &temp_aht); // populate temp and humidity objects with fresh data

  Serial.print("AHT20 - ");
  Serial.print("Temperature: ");
  Serial.print(temp_aht.temperature);
  Serial.print(" *C\t");
  Serial.print("Humidity: ");
  Serial.print(humidity.relative_humidity);
  Serial.println(" %");

  Serial.print("BMP280 - ");
  Serial.print("Temperature: ");
  Serial.print(bmp.readTemperature());
  Serial.print(" *C\t");
  Serial.print("Pressure: ");
  Serial.print(bmp.readPressure() / 100.0F); // hPa
  Serial.println(" hPa");

  Serial.println("");
  delay(2000);
}