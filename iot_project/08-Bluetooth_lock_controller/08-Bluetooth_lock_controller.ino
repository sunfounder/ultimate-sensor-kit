/*
  The code controls a servo motor based on the message received from a JDY-31 Bluetooth module. 
  The servo motor moves to a "locked" position when the message is 1 and an "unlocked" position 
  when the message is 0. 

  Board: Arduino Uno R4 or R3
  Component:  JDY-31 Bluetooth Module
*/


#include <SoftwareSerial.h>
#include <Servo.h>

// Set up Bluetooth module communication
const int bluetoothTx = 3;                           // bluetooth tx to 3 pin
const int bluetoothRx = 4;                           // bluetooth rx to 4 pin
SoftwareSerial bleSerial(bluetoothTx, bluetoothRx);  //Rx,Tx

// Define servo-related constants
const int servoPin = 9;
const int lockAngle = 180;
const int unlockAngle = 90;
// Create a servo object
Servo myservo;

void setup() {
  myservo.attach(servoPin);

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  bleSerial.begin(9600);
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