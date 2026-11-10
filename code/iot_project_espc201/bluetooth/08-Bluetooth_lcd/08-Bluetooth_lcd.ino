#include "SunFounder_BLE.h"
/*
  The code is designed for an Arduino Uno R4 (or R3) to interface with a ESPC2-01 (ESP32-C2) BLE module and an LCD module. The Arduino listens for incoming data from the Bluetooth module, 
  and upon receiving, displays the data on both the LCD and the serial monitor. It also 
  forwards any data received from the serial monitor to the Bluetooth module.

  Board: Arduino Uno R4 (or R3)
  Component: ESPC2-01 (ESP32-C2) BLE module and LCD Module
  Library: https://www.arduino.cc/reference/en/libraries/liquidcrystal-i2c/ (LiquidCrystal I2C by Frank de Brabander)  
*/

// Set up LCD Module
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);  // initialize the Liquid Crystal Display object with the I2C address 0x27, 16 columns and 2 rows

// Set up Bluetooth module communication
// ==== ESPC2-01 (ESP32-C2) BLE: uses hardware Serial1 (D0/D1) ====
BLEStream bleSerial;

void setup() {
  lcd.init();       // initialize the LCD
  lcd.clear();      // clear the LCD display
  lcd.backlight();  // Make sure backlight is on

  
  Serial.begin(115200);

  // The module takes a few seconds to start. Do that BEFORE printing anything:
  // on the R4 the USB port needs about a second after a reset, so a line printed
  // immediately would be lost before the Serial Monitor can show it.
  bleSerial.begin();

  Serial.println();
  Serial.println("=== ESPC2-01 Bluetooth (BLE) ===");
  bleSerial.report();
  Serial.println("--------------------------------");
  bleSerial.setTimeout(50);   // do not let readString() block for a full second
}

void loop() {
  String data;

  // Check if there's any data from the Bluetooth module
  if (bleSerial.available()) {

    data += bleSerial.readString();               // Read incoming string from Bluetooth
    // the phone app may add \r\n at the end: strip line endings only, never characters
    while (data.endsWith("\r") || data.endsWith("\n")) {
      data.remove(data.length() - 1);
    }
    Serial.print(data);                           // Display data on serial monitor

    lcd.clear();          // Clear previous message on LCD
    lcd.setCursor(0, 0);  // Set cursor to beginning of LCD
    lcd.print(data);      // Display the received data on LCD
  }

  // Check if there's any data from the Serial monitor (PC)
  if (Serial.available()) {
    bleSerial.write(Serial.read());  // Forward the received byte to Bluetooth module
  }
}
