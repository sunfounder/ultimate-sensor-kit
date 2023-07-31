/*
  This Arduino code is designed to control an automatic watering system with a soil moisture 
  sensor. The system uses a Blynk app for user interaction. It sends soil moisture data to 
  the Blynk app and receives the watering threshold and automatic mode status from it. 
  If the soil moisture drops below the threshold and automatic mode is on, the system 
  activates the water pump.

  Board: Arduino Uno R4 (or R3)
  Component: Capacitive soil moisture sensor and water pump
*/

// Template ID, Device Name and Auth Token are provided by the Blynk Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPLxxxxxxx"
#define BLYNK_TEMPLATE_NAME "Auto water"
#define BLYNK_AUTH_TOKEN "xxxxxxxxxx"

//Set debug prints on Serial Monitor
#define BLYNK_PRINT Serial

#include <ESP8266_Lib.h>               // Library for ESP8266
#include <BlynkSimpleShieldEsp8266.h>  // Library for Blynk

// Your WiFi credentials.
char ssid[] = "your_ssid";
char pass[] = "your_password";  // Set password to "" for open networks.

// Software Serial on Uno
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(2, 3);  // RX, TX
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

void setup() {
  pinMode(pump1A, OUTPUT);    // set pump1A as output
  pinMode(pump1B, OUTPUT);    // set pump1B as output
  digitalWrite(pump1B, LOW);  // Keep pump1B low

  Serial.begin(115200);           // Start serial communication at 115200 baud rate for debugging
  EspSerial.begin(ESP8266_BAUD);  // Set ESP8266 baud rate
  delay(10);

  // Configure Blynk and connect to WiFi
  Blynk.config(wifi, BLYNK_AUTH_TOKEN);
  Blynk.connectWiFi(ssid, pass);

  // Configure timer events
  timer.setInterval(10000L, updateDataTimer);  // Update sensor data every 10 seconds
  timer.setInterval(35000L, autoWaterTimer);   // Check watering conditions every 35 seconds
}

void loop() {
  Blynk.run();
  timer.run();  // Run BlynkTimer
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED() {
  Blynk.syncVirtual(V1);  // Sync water threshold
  Blynk.syncVirtual(V2);  // Sync auto mode status
}

// This function is called every time the Virtual Pin 1 state changes
BLYNK_WRITE(V1) {
  waterThreshold = param.asInt();  // Update watering threshold
  Serial.print("Received threshold.   waterThreshold:");
  Serial.println(waterThreshold);
}

// This function is called every time the Virtual Pin 2 state changes
BLYNK_WRITE(V2) {
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
  Blynk.virtualWrite(V0, moisturePercentage * 100);
}

// Function to control automatic watering based on soil moisture and user settings
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