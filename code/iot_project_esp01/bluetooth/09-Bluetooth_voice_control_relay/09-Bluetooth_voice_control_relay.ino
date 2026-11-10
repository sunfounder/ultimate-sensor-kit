/*
  The code establishes a Bluetooth serial communication using a JDY-31 Bluetooth Module 
  that connect to an Arduino Uno board. It listens for incoming messages via Bluetooth, 
  and when a complete message ending with a '#' character is received, it toggles a relay 
  module connected to pin 8 based on the content of the message. If the message is "1", 
  the relay is turned on; if the message is "0", the relay is turned off. 
  Additionally, debug messages are printed to the standard serial port.

  Board: Arduino Uno R4 (or R3)
  Component:  JDY-31 Bluetooth Module and relay module
*/

// Set up Bluetooth module communication
#include <SoftwareSerial.h>
const int bluetoothTx = 3;                           // bluetooth tx to 3 pin
const int bluetoothRx = 4;                           // bluetooth rx to 4 pin
SoftwareSerial bleSerial(bluetoothTx, bluetoothRx);  // Declare SoftwareSerial object for Bluetooth communication

char character;  // Character received from Bluetooth serial
String message;  // Stores the complete message from Bluetooth

// Define relay control pin
const int relayPin = 8;

void setup() {
  Serial.begin(9600);
  bleSerial.begin(9600);

  // Set relayPin as an output pin
  pinMode(relayPin, OUTPUT);
}

void loop() {
  // If there's data available from Bluetooth serial
  while (bleSerial.available() > 0) {
    character = bleSerial.read();   // Read a character
    message = message + character;  // Append character to message string

    // Check if the end of the message (denoted by '#') is received
    if (character == '#') {
      message = message.substring(0, message.length() - 1);  // Remove '#' from the end

      // debug
      Serial.println();
      Serial.print("DEBUG:");
      Serial.println(message);

      // Toggle the relay based on the received message
      if (message == "1") {
        digitalWrite(relayPin, HIGH);
        Serial.println("On");
      } else if (message == "0") {
        digitalWrite(relayPin, LOW);
        Serial.println("Off");
      }

      message = "";  // Clear message for next reception
      delay(200);    // Wait for a short duration
    }
  }
}
