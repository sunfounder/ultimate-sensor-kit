#include "SunFounder_BLE.h"
/*
  00-Bluetooth_start

  Turns the ESPC2-01 into a BLE serial port, so the Serial Monitor and the
  phone can talk to each other.

  Wiring:
      module TX0 -> D0      module RX0 -> D1
      module 3V3 -> 3V3     module GND -> GND
      module IO9 -> not connected

  Serial Monitor: 115200
*/

BLEStream bleSerial;   // BLE serial, uses Serial1 (D0/D1) internally

void report() {
  // ask the module for its state and show the answer
  while (Serial1.available()) Serial1.read();
  Serial1.print("AT+BLEINIT?\r\n");
  unsigned long t0 = millis();
  String r;
  while (millis() - t0 < 700) {
    while (Serial1.available()) r += (char)Serial1.read();
  }
  if (r.indexOf("+BLEINIT:2") >= 0) {
    Serial.println("[OK] BLE is ready - scan for \"SunFounder-C2\" on your phone");
  } else {
    Serial.print("[!] no reply from the module, got: ");
    Serial.println(r);
  }
}

void setup() {
  Serial.begin(115200);

  // The module takes a few seconds to start. Do that BEFORE printing anything:
  // on the R4 the USB port needs about a second after a reset, so a line printed
  // immediately would be lost before the Serial Monitor can show it.
  bleSerial.begin();

  Serial.println();
  Serial.println("=== ESPC2-01 Bluetooth (BLE) ===");
  report();
  Serial.println("--------------------------------");
  Serial.println("Type here and press Enter: the text is sent to the phone (C305)");
}

unsigned long lastReport = 0;

void loop() {
  // phone -> Serial Monitor
  if (bleSerial.available()) {
    Serial.write(bleSerial.read());
  }
  // Serial Monitor -> phone
  if (Serial.available()) {
    bleSerial.write(Serial.read());
    lastReport = millis();          // do not report while typing
  }
  // keep the student informed every 10 s
  if (millis() - lastReport > 10000 && !Serial.available()) {
    lastReport = millis();
    report();
  }
}
