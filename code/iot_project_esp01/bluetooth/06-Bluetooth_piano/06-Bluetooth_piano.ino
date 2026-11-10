/*
  The Arduino program enables a straightforward "piano" feature by utilizing a JDY-31 Bluetooth module 
  and a Passive Buzzer Module. The program listens for specific note instructions sent via Bluetooth. 
  When a note  instruction (like "NOTE_C4*") is received, it plays the corresponding tone on the buzzer. 
  Each note instruction ends with an asterisk ('*').

  Board: Arduino Uno R4 (or R3)
  Component:  JDY-31 Bluetooth module and passive buzzer module
*/

// Include the pitches.h for the musical note pitches.
#include "pitches.h"

// Set up Bluetooth module communication
#include <SoftwareSerial.h>
const int bluetoothTx = 3;                           // bluetooth tx to 3 pin
const int bluetoothRx = 4;                           // bluetooth rx to 4 pin
SoftwareSerial bleSerial(bluetoothTx, bluetoothRx);  // Declare SoftwareSerial object for Bluetooth communication

// Define pin connected to the buzzer
const int buzzerPin = 2;

char character;   // Variable to store individual characters from serial input
String noteType;  // String to store the note type received via Bluetooth

void setup() {
  Serial.begin(9600);     // Initialize serial communication for debugging
  bleSerial.begin(9600);  // Initialize serial communication for Bluetooth module
}

void loop() {
  // Read and process incoming messages from Bluetooth
  while (bleSerial.available() > 0) {
    character = bleSerial.read();
    noteType = noteType + character;

    // Check if the end of the message (denoted by '*') is received
    if (character == '*') {
      noteType = noteType.substring(0, noteType.length() - 1);  // Delete last char *
      Serial.println(noteType);

      // Play the corresponding tone based on the received note type
      if (noteType == "NOTE_C4") {
        tone(buzzerPin, NOTE_C4);
      } else if (noteType == "NOTE_D4") {
        tone(buzzerPin, NOTE_D4);
      } else if (noteType == "NOTE_E4") {
        tone(buzzerPin, NOTE_E4);
      } else if (noteType == "NOTE_F4") {
        tone(buzzerPin, NOTE_F4);
      } else if (noteType == "NOTE_G4") {
        tone(buzzerPin, NOTE_G4);
      } else if (noteType == "NOTE_A4") {
        tone(buzzerPin, NOTE_A4);
      } else if (noteType == "NOTE_B4") {
        tone(buzzerPin, NOTE_B4);
      } else if (noteType == "NOTE_C5") {
        tone(buzzerPin, NOTE_C5);
      }

      noteType = "";      // Reset the note type string for the next message
      delay(200);         // Wait for a short duration
      noTone(buzzerPin);  // Stop playing the tone
    }
  }
}
