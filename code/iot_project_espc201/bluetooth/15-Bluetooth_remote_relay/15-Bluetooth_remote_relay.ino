#include "SunFounder_BLE.h"
/*
  This code interface with the ESPC2-01 (ESP32-C2) BLE module using the Arduino Uno. It listens 
  for incoming messages from the Bluetooth module and toggles a relay module connected to 
  pin 8 based on the received message. If the message is '1', the relay is turned on; if 
  the message is '0', the relay is turned off.

  Board: Arduino Uno R4 or R3
  Component:  ESPC2-01 (ESP32-C2) BLE module and relay module
*/


// Set up Bluetooth module communication
// ==== ESPC2-01 (ESP32-C2) BLE: uses hardware Serial1 (D0/D1) ====
BLEStream bleSerial;

// Define relay control pin
const int relayPin = 8;

void setup() {
  
  Serial.begin(115200);

  // The module takes a few seconds to start. Do that BEFORE printing anything:
  // on the R4 the USB port needs about a second after a reset, so a line printed
  // immediately would be lost before the Serial Monitor can show it.
  bleSerial.begin();

  Serial.println();
  Serial.println("=== ESPC2-01 Bluetooth (BLE) ===");
  bleSerial.report();
  Serial.println("--------------------------------");
  // Set relayPin as an output pin
  pinMode(relayPin, OUTPUT);
}

void loop() {
  // Read incoming message from serial input
  if (bleSerial.available() > 0) {
    char message = bleSerial.read();  // Read the message from Bluetooth serial
    // Serial.println(message);  //for debug

    // Toggle the relay based on the received message
    if (message == '1') {
      digitalWrite(relayPin, HIGH);
      Serial.println("On");
    } else if (message == '0') {
      digitalWrite(relayPin, LOW);
      Serial.println("Off");
    }
  }
}
