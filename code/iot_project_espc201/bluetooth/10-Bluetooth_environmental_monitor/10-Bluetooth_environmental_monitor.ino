#include "SunFounder_BLE.h"
/*
  The code initializes and reads data from a DHT11 temperature and humidity sensor. 
  It then displays the readings on the serial monitor and sends them via a ESPC2-01 (ESP32-C2) 
  Bluetooth module in a comma-separated format.
  
  Board: Arduino Uno R4 or R3
  Component:  ESPC2-01 (ESP32-C2) BLE module and DHT11 module
  Library: https://github.com/adafruit/DHT-sensor-library  (DHT sensor library by Adafruit)
*/

// Set up Bluetooth module communication
// ==== ESPC2-01 (ESP32-C2) BLE: uses hardware Serial1 (D0/D1) ====
BLEStream bleSerial;

// Set up DHT11 module
#include <DHT.h>
#define DHTPIN 2           // Define the pin used to connect the sensor
#define DHTTYPE DHT11      // Define the sensor type
DHT dht(DHTPIN, DHTTYPE);  // Create a DHT object

String sensorData;  // To store concatenated temperature and humidity values

void setup() {
  
  Serial.begin(115200);

  // Start the module BEFORE printing: on the R4 the USB port needs about a second
  // after a reset, so a line printed immediately would never reach the monitor.
  bleSerial.begin();

  Serial.println();
  Serial.println("=== ESPC2-01 Bluetooth (BLE) ===");
  
  
  Serial.println("--------------------------------");
     // Initialize serial communication for debugging
  bleSerial.report();  // Initialize serial communication for Bluetooth module

  dht.begin();  // Initialize the DHT sensor
}

void loop() {
  delay(2000);  // Wait for 2 seconds

  float humidity = dht.readHumidity();        // Read humidity from DHT sensor
  float temperature = dht.readTemperature();  // Read temperature from DHT sensor

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Print the humidity and temperature to the serial monitor
  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(temperature);
  Serial.println(F("°C "));

  sensorData = String(temperature) + "," + String(humidity);  // Concatenate temperature and humidity values
  Serial.print("Data to send: ");
  Serial.println(sensorData);

  bleSerial.println(sensorData);  // Send temperature and humidity values to the Bluetooth module
}
