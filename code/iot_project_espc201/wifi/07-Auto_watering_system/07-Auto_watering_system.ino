/*
  This Arduino code is designed to control an automatic watering system with a soil moisture 
  sensor. The system uses a Blynk app for user interaction. It sends soil moisture data to 
  the Blynk app and receives the watering threshold and automatic mode status from it. 
  If the soil moisture drops below the threshold and automatic mode is on, the system 
  activates the water pump.

  Board: Arduino Uno R4 (or R3)
  Component: Capacitive soil moisture sensor and water pump
  Library: https://github.com/blynkkk/blynk-library
*/

// Template ID, Device Name and Auth Token are provided by the Blynk Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID   "TMPLxxxxxx"
#define BLYNK_TEMPLATE_NAME "Ultimate Sensor Kit"
#define BLYNK_AUTH_TOKEN    "YourAuthToken"

//Set debug prints on Serial Monitor
#define BLYNK_PRINT Serial

#include <ESP8266_Lib.h>               // Library for ESP8266
#include <BlynkSimpleShieldEsp8266.h>  // Library for Blynk

// Your WiFi credentials.
char ssid[] = "your_ssid";
char pass[] = "your_password";  // Set password to "" for open networks.

// Software Serial on Uno
// ==== ESPC2-01 (ESP32-C2): use hardware serial D0/D1 ====
#define EspSerial Serial1
#define ESP8266_BAUD 115200      // Set the ESP8266 baud rate
ESP8266 wifi(&EspSerial);

// Define pin configurations for the water pump
const int pump1A = 9;
const int pump1B = 10;
bool pumpStatus = 0;  // 0 indicates OFF, 1 indicates ON

// Define the soil moisture sensor
const float moistureInAir = 535;    // Measure by placing the sensor in air
const float moistureInWater = 280;  // Measure by immersing the sensor in water
const int sensorPin = A0;
int sensorValue = 0;  // Stores the raw sensor value

int autoMode = 0;
int waterThreshold = 0;        // The soil moisture percentage threshold to activate watering
float moisturePercentage = 0;  // The calculated soil moisture percentage

BlynkTimer timer;


// ---- ESPC2-01 power-up: wait for the module to boot, then turn echo off ----
void espModuleInit() {
  unsigned long t0 = millis();
  String buf;
  while (millis() - t0 < 5000) {
    while (EspSerial.available() && buf.length() < 512) {
      buf += (char)EspSerial.read();
      if (buf.indexOf("ready") >= 0) t0 = millis() - 5000;   // leave the loop
    }
  }
  while (EspSerial.available()) EspSerial.read();
  EspSerial.print("ATE0\r\n");     // echo off, otherwise the reply mixes in the command text
  delay(300);
  while (EspSerial.available()) EspSerial.read();
}

void setup() {
  pinMode(pump1A, OUTPUT);    // set pump1A as output
  pinMode(pump1B, OUTPUT);    // set pump1B as output
  digitalWrite(pump1B, LOW);  // Keep pump1B low

  Serial.begin(115200);           // Start serial communication at 115200 baud rate for debugging
  EspSerial.begin(ESP8266_BAUD);  // Set ESP8266 baud rate
  delay(10);

  // Configure Blynk and connect to WiFi
  espModuleInit();
  Blynk.config(wifi, BLYNK_AUTH_TOKEN);
  Blynk.connectWiFi(ssid, pass);

  // Configure timer events
  // Two timers: one reports the soil every 10 s, the other checks the pump every 35 s.
  timer.setInterval(35000L, autoWaterTimer);
}

void loop() {
  Blynk.run();
  timer.run();  // Run BlynkTimer
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED() {
  Blynk.syncVirtual(V9);  // Sync water threshold
  Blynk.syncVirtual(V10);  // Sync auto mode status
}

// This function is called every time the Virtual Pin 1 state changes
BLYNK_WRITE(V9) {
  waterThreshold = param.asInt();  // Update watering threshold
  Serial.print("Received threshold.   waterThreshold:");
  Serial.println(waterThreshold);
}

// This function is called every time the Virtual Pin 2 state changes
BLYNK_WRITE(V10) {
  autoMode = param.asInt();  // Update auto mode status

  if (autoMode == 1) {
    Serial.println("The switch on Blynk has been turned on.");
  } else {
    Serial.println("The switch on Blynk has been turned off.");
  }
}

void updateDataTimer() {
  sendData();
}

void autoWaterTimer() {
  autoWater();
}

// Function to send sensor data to Blynk app
void sendData() {
  // Calculate soil moisture percentage
  sensorValue = analogRead(sensorPin);
  moisturePercentage = 1 - (sensorValue - moistureInWater) / (moistureInAir - moistureInWater);

  Serial.println("-----------------------------");
  Serial.println("Update soil moisture data ...");
  Serial.print("sensorValue:");
  Serial.print(sensorValue);
  Serial.print("  moisturePercentage:");
  Serial.println(moisturePercentage * 100);

  // Send moisture percentage to Blynk app
  Blynk.virtualWrite(V8, moisturePercentage * 100);
}

// Runs every 35 s: if the automatic mode is on and the soil is drier than the slider,
// start the pump for a while.
void autoWater() {
  if (autoMode == 1 && moisturePercentage * 100 < waterThreshold) {

    if (!pumpStatus) {
      turnOnPump();
      Serial.println("-----------------------------");
      Serial.println("Watering...");

      // Turn off pump after 2 seconds
      timer.setTimeout(2000L, turnOffPump);
    }
  }
}

// Function to turn on the water pump
void turnOnPump() {
  digitalWrite(pump1A, HIGH);
  pumpStatus = 1;
}

// Function to turn off the water pump
void turnOffPump() {
  digitalWrite(pump1A, LOW);
  pumpStatus = 0;
}