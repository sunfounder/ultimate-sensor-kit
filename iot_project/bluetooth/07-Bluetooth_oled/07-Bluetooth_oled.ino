/*
  The code initializes and sets up communication with a JDY-31 Bluetooth module and an OLED display 
  that connect to an Arduino Uno R4 (or R3) board. The Arduino waits for messages from the Bluetooth module 
  and displays them on the OLED screen. Each message from the Bluetooth module should end with a '#' character 
  to denote the end of the message.

  Board: Arduino Uno R4 (or R3)
  Component:  JDY-31 Bluetooth Module and OLED Module
  Library: https://github.com/adafruit/Adafruit_SSD1306 (Adafruit SSD1306 by Adafruit)  
           https://github.com/adafruit/Adafruit-GFX-Library (Adafruit GFX Library by Adafruit) 
*/

// Set up Bluetooth module communication
#include <SoftwareSerial.h>
const int bluetoothTx = 3;                           // bluetooth tx to 3 pin
const int bluetoothRx = 4;                           // bluetooth rx to 4 pin
SoftwareSerial bleSerial(bluetoothTx, bluetoothRx);  // Declare SoftwareSerial object for Bluetooth communication

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
  Serial.begin(9600);
  bleSerial.begin(9600);

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

void loop() {
  // If there's data available from Bluetooth serial
  while (bleSerial.available() > 0) {
    character = bleSerial.read();   // Read a character
    message = message + character;  // Append character to message string

    // Check if the end of the message (denoted by '#') is received
    if (character == '#') {
      message = message.substring(0, message.length() - 1);// Remove '#' from the end

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

      message = "";  // Clear message for next reception
      delay(200);    // Wait for a short duration
    }
  }
}
