#include "SunFounder_BLE.h"
/*
  The code initializes and sets up communication with a ESPC2-01 (ESP32-C2) BLE module and an OLED display 
  that connect to an Arduino Uno R4 (or R3) board. The Arduino waits for messages from the Bluetooth module 
  and displays them on the OLED screen. Each message from the Bluetooth module should end with a '#' character 
  to denote the end of the message.

  Board: Arduino Uno R4 (or R3)
  Component:  ESPC2-01 (ESP32-C2) BLE module and OLED Module
  Library: https://github.com/adafruit/Adafruit_SSD1306 (Adafruit SSD1306 by Adafruit)  
           https://github.com/adafruit/Adafruit-GFX-Library (Adafruit GFX Library by Adafruit) 
*/

// Set up Bluetooth module communication
// ==== ESPC2-01 (ESP32-C2) BLE: uses hardware Serial1 (D0/D1) ====
BLEStream bleSerial;

// Libraries and dependencies for OLED display
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Set up OLED display
// Declaration for SSD1306 display connected using I2C
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET -1     // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

char character;  // Character received from Bluetooth serial
String message;  // Stores the complete message from Bluetooth

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
  // initialize the OLED object
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  // display "Waiting for connection" on OLED
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(32, 20);
  display.println("Waiting for");
  display.setCursor(32, 30);
  display.println("connection");
  display.display();
}

void showMessage() {
  if (message.length() == 0) return;

  // debug
  Serial.println();
  Serial.print("DEBUG:");
  Serial.println(message);

  // display to OLED
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 20);
  display.println(message);
  display.display();

  message = "";   // ready for the next message
}

void loop() {
  // A message ends when '#' arrives, or when the phone stops sending for 120 ms.
  static unsigned long lastByte = 0;

  while (bleSerial.available() > 0) {
    char c = (char)bleSerial.read();
    if (c == '#' || c == '\r' || c == '\n') {
      showMessage();
      lastByte = millis();
      continue;
    }
    message += c;
    lastByte = millis();
  }

  if (message.length() > 0 && millis() - lastByte > 120) {
    showMessage();
  }
}
