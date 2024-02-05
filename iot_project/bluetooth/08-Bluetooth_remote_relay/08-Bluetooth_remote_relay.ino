/*
  This code interface with the JDY-31 Bluetooth Module using the Arduino Uno. It listens 
  for incoming messages from the Bluetooth module and toggles a relay module connected to 
  pin 8 based on the received message. If the message is '1', the relay is turned on; if 
  the message is '0', the relay is turned off.

  Board: Arduino Uno R4 or R3
  Component:  JDY-31 Bluetooth Module and relay module
*/

#include <SoftwareSerial.h>

// Set up Bluetooth module communication
const int bluetoothTx = 3;                           // bluetooth tx to 3 pin
const int bluetoothRx = 4;                           // bluetooth rx to 4 pin
SoftwareSerial bleSerial(bluetoothTx, bluetoothRx);  // Rx,Tx

// Define relay control pin
const int relayPin = 8;

void setup() {
  Serial.begin(9600);
  bleSerial.begin(9600);

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
