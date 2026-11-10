#include "SunFounder_BLE.h"
/*
  The code controls a servo motor based on the message received from a ESPC2-01 (ESP32-C2) BLE module. 
  The servo motor moves to a "locked" position when the message is 1 and an "unlocked" position 
  when the message is 0. 

  Board: Arduino Uno R4 or R3
  Component:  ESPC2-01 (ESP32-C2) BLE module and servo motor(SG90)
*/


#include <Servo.h>

// Set up Bluetooth module communication
// ==== ESPC2-01 (ESP32-C2) BLE: uses hardware Serial1 (D0/D1) ====
BLEStream bleSerial;

// Define servo-related constants
const int servoPin = 9;
const int lockAngle = 180;
const int unlockAngle = 90;
// Create a servo object
Servo myservo;

void setup() {
  myservo.attach(servoPin);

  // initialize serial communication at 9600 bits per second:
  
  Serial.begin(115200);

  // The module takes a few seconds to start. Do that BEFORE printing anything:
  // on the R4 the USB port needs about a second after a reset, so a line printed
  // immediately would be lost before the Serial Monitor can show it.
  bleSerial.begin();

  Serial.println();
  Serial.println("=== ESPC2-01 Bluetooth (BLE) ===");
  bleSerial.report();
  Serial.println("--------------------------------");
}

void loop() {
  // Read incoming message from serial input
  if (bleSerial.available() > 0) {
    char message = bleSerial.read();  // Read the message from Bluetooth serial
    // Serial.println(message);  //for debug

    if (message == '1') {  // If the incoming message is '1', moves to a "locked" position
      myservo.write(lockAngle);
      Serial.println("Locked");
    }
    else if (message == '0') {  // If the incoming message is '0', moves to a "unlocked" position
      myservo.write(unlockAngle);
      Serial.println("Unlocked");
    }
  }
}