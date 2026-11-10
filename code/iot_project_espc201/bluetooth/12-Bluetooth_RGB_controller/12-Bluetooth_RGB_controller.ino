#include "SunFounder_BLE.h"
/*
  Bluetooth RGB Controller

  The phone sends one message with three numbers, for example R255G128B0,
  and the RGB LED shows that colour.

  A BLE write can arrive in several pieces, so the sketch collects the characters
  until the message is complete (a '#' at the end, or 120 ms of silence) and only
  then parses it. Applying a half-received message is what makes the colours jump.

  Board:     Arduino Uno R4 Minima
  Module:    ESPC2-01 (ESP32-C2) with ESP-AT firmware, on D0/D1
  Component: RGB LED (R = D9, G = D10, B = D11)
*/

// The RGB LED is common cathode: a higher number means more of that colour.
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

BLEStream bleSerial;

String message = "";
unsigned long lastByte = 0;

// Read the number that follows a marker: extract("R255G128B0", 'G') returns 128.
// It returns -1 when the marker is not in the message at all.
int extract(const String& m, char marker) {
  int at = m.indexOf(marker);
  if (at < 0) return -1;

  int value = 0;
  bool found = false;
  for (int i = at + 1; i < (int)m.length(); i++) {
    char c = m[i];
    if (c >= '0' && c <= '9') {
      value = value * 10 + (c - '0');
      found = true;
      if (value > 999) break;
    } else {
      break;
    }
  }
  return found ? value : -1;
}

void applyMessage() {
  if (message.length() == 0) return;

  int r = extract(message, 'R');
  int g = extract(message, 'G');
  int b = extract(message, 'B');

  if (r >= 0) analogWrite(redPin,   constrain(r, 0, 255));
  if (g >= 0) analogWrite(greenPin, constrain(g, 0, 255));
  if (b >= 0) analogWrite(bluePin,  constrain(b, 0, 255));

  Serial.print("colour: ");
  Serial.println(message);

  message = "";
}

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);

  Serial.begin(115200);

  // The module takes a few seconds to start. Do that BEFORE printing anything:
  // on the R4 the USB port needs about a second after a reset, so a line printed
  // immediately would be lost before the Serial Monitor can show it.
  bleSerial.begin();

  Serial.println();
  Serial.println("=== ESPC2-01 Bluetooth (BLE) ===");
  bleSerial.report();
  Serial.println("--------------------------------");
  Serial.println("Send R255G128B0 on C304");
}

void loop() {
  while (bleSerial.available() > 0) {
    char c = (char)bleSerial.read();
    lastByte = millis();

    if (c == '#' || c == '\r' || c == '\n') {
      applyMessage();          // an explicit end marker
      continue;
    }
    if (message.length() < 20) message += c;
  }

  // no '#' came, so treat a short silence as the end of the message
  if (message.length() > 0 && millis() - lastByte > 120) {
    applyMessage();
  }
}
