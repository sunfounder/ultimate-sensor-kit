#include "SunFounder_BLE.h"
/*
  Bluetooth Motion Monitor

  The board reads an MPU6050 and streams the two tilt angles to the phone.
  The phone can stop and restart the stream, so this project talks in BOTH directions:
    phone -> board : write S (start) or P (pause) to C304
    board -> phone : notification on C305, one line every half second

  At power-up the sketch measures the zero point, so a board lying flat shows 0.0 / 0.0.

  Board:     Arduino Uno R4 Minima
  Module:    ESPC2-01 (ESP32-C2) with ESP-AT firmware, on D0/D1
  Component: MPU6050 (I2C, SDA = A4, SCL = A5)
  Library:   Adafruit MPU6050 + Adafruit Unified Sensor
*/

#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

BLEStream bleSerial;
Adafruit_MPU6050 mpu;

bool streaming = true;          // the phone can pause the stream with P
unsigned long lastSend = 0;
const unsigned long interval = 500;   // one line every half second

// The angles the board has when it lies flat. Measured once in setup() and
// subtracted from every reading, so "flat" really means 0.0.
float zeroX = 0;
float zeroY = 0;

// One reading, already converted from acceleration to degrees.
void readTilt(float &tiltX, float &tiltY) {
  sensors_event_t a, g, t;
  mpu.getEvent(&a, &g, &t);

  float ax = a.acceleration.x;
  float ay = a.acceleration.y;
  float az = a.acceleration.z;

  tiltX = atan2(ay, az) * 180.0 / PI;
  tiltY = atan2(-ax, sqrt(ay * ay + az * az)) * 180.0 / PI;
}

void setup() {
  Serial.begin(115200);

  // Start the module BEFORE printing: on the R4 the USB port needs about a second
  // after a reset, so a line printed immediately would never reach the monitor.
  bleSerial.begin();

  Serial.println();
  Serial.println("=== ESPC2-01 Bluetooth (BLE) ===");
  bleSerial.report();
  Serial.println("--------------------------------");

  Wire.begin();                       // SDA = A4, SCL = A5 on the R4
  if (!mpu.begin()) {
    Serial.println("[!] no MPU6050 found - check SDA, SCL, VCC and GND");
    while (1) delay(10);
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  Serial.println("[OK] MPU6050 is ready");

  // ---- zero point: the board must lie flat and stay still for a moment ----
  Serial.println("Keep the board flat and still - measuring the zero point ...");
  delay(1000);

  float sumX = 0, sumY = 0;
  for (int i = 0; i < 10; i++) {
    float tx, ty;
    readTilt(tx, ty);
    sumX += tx;
    sumY += ty;
    delay(50);
  }
  zeroX = sumX / 10.0;
  zeroY = sumY / 10.0;

  Serial.print("zero: X=");
  Serial.print(zeroX, 1);
  Serial.print(" Y=");
  Serial.println(zeroY, 1);
  Serial.println("Send S on C304 to start, P to pause");
}

void loop() {
  // ---- phone -> board: S starts the stream, P pauses it ----
  while (bleSerial.available() > 0) {
    char c = (char)bleSerial.read();
    if (c == 'S') {
      streaming = true;
      Serial.println("Streaming started");
    } else if (c == 'P') {
      streaming = false;
      Serial.println("Streaming paused");
    }
  }

  // ---- board -> phone: one line every half second ----
  if (streaming && millis() - lastSend > interval) {
    lastSend = millis();

    float tiltX, tiltY;
    readTilt(tiltX, tiltY);

    float x = tiltX - zeroX;        // 0.0 when the board lies flat
    float y = tiltY - zeroY;

    String line = "X:" + String(x, 1) + " Y:" + String(y, 1);
    bleSerial.println(line);     // goes out on C305
    Serial.println(line);
  }
}
