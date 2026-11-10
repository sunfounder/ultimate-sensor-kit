#include "SunFounder_BLE.h"
/*
  The code initializes a Bluetooth module for communication and sets up 
  three LEDs (red, yellow, and green). It reads characters from the Bluetooth 
  connection, and based on the received character ('R', 'Y', or 'G'), it 
  toggles the respective LED (turning all other LEDs off).

  Board: Arduino Uno R4 (or R3)
  Component: ESPC2-01 (ESP32-C2) BLE module and Traffic Light Module
*/

// Set up Bluetooth module communication
// ==== ESPC2-01 (ESP32-C2) BLE: uses hardware Serial1 (D0/D1) ====
BLEStream bleSerial;

// Pin numbers for each LED
const int rledPin = 10;  //red
const int yledPin = 11;  //yellow
const int gledPin = 12;  //green

char character;  // Character received from Bluetooth communication

void setup() {
  // Set LED pins as output
  pinMode(rledPin, OUTPUT);
  pinMode(yledPin, OUTPUT);
  pinMode(gledPin, OUTPUT);

  
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
  // Check if there are data available from the Bluetooth module
  while (bleSerial.available() > 0) {

    character = bleSerial.read();  // Read the incoming character
    Serial.println(character);     // Print the received character to the serial monitor

    // Toggle respective LED based on received character
    if (character == 'R') {
      toggleLights(rledPin);
    } else if (character == 'Y') {
      toggleLights(yledPin);
    } else if (character == 'G') {
      toggleLights(gledPin);
    }
  }
}

// Function to turn off all LEDs and turn on the specified LED
void toggleLights(int targetLight) {
  digitalWrite(rledPin, LOW);  // Turn off Red LED
  digitalWrite(yledPin, LOW);  // Turn off Yellow LED
  digitalWrite(gledPin, LOW);  // Turn off Green LED

  digitalWrite(targetLight, HIGH);  // Turn on the target LED
}
