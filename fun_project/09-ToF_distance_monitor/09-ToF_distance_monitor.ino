/*
  This code initializes and runs an Arduino Uno setup that interfaces with a VL53L0X Time of Flight 
  Micro-LIDAR Distance Sensor and an OLED display. It measures the distance in millimeters and displays 
  the distance on the OLED screen. The measurement values are also output on the serial monitor.
  Note: The VL53L0X can handle about 50 - 1200 mm of range distance.

  Board: Arduino Uno R4 (or R3)
  Component: Time of Flight Micro-LIDAR Distance Sensor (VL53L0X) and OLED Display Module
  Library: https://github.com/adafruit/Adafruit_VL53L0X  (Adafruit_VL53L0X by Adafruit)
           https://github.com/adafruit/Adafruit_SSD1306 (Adafruit SSD1306 by Adafruit)  
           https://github.com/adafruit/Adafruit-GFX-Library (Adafruit GFX Library by Adafruit) 
           
*/

#include <Wire.h>
#include "Adafruit_VL53L0X.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Initialize the OLED display module with a resolution of 128x64
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire, -1);

// Initialize the VL53L0X distance sensor
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  Serial.begin(9600);

  // Start the OLED display with I2C address 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(1000);

  // Begin I2C communication
  Wire.begin();

  // Start the VL53L0X distance sensor, halt if initialization fails
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while (1)
      ;
  }

  // Set OLED display text size and color
  display.setTextSize(3);
  display.setTextColor(WHITE);
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;

  lox.rangingTest(&measure, false);  // pass in 'true' to get debug data printout

  // If there are no phase failures, display the measured distance
  if (measure.RangeStatus != 4) {
    display.clearDisplay();
    display.setCursor(12, 22);
    display.print(measure.RangeMilliMeter);
    display.print("mm");
    display.display();
    Serial.println();
    delay(50);
  } else {
    display.display();
    display.clearDisplay();
    return;
  }
}