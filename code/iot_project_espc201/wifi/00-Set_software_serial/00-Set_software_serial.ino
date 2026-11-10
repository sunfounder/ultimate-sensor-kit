/*
  00-Set_software_serial

  A plain bridge between the USB port and the ESPC2-01 module, so you can talk to the
  module with AT commands from the Serial Monitor.

  Board:   Arduino Uno R4 Minima
  Module:  ESPC2-01 (ESP32-C2) with ESP-AT firmware
  Wiring:  module TX0 -> D0, RX0 -> D1, 3V3 -> adapter 5V pin, GND -> GND, IO9 floating

  Serial Monitor: 115200, line ending "Both NL & CR".
  Try:  AT      AT+GMR      AT+CWMODE?      AT+BLEINIT?
*/

#define EspSerial Serial1

void setup() {
  Serial.begin(115200);
  EspSerial.begin(115200);

  // Print the start-up log of the module, so you can see that it is alive.
  unsigned long t0 = millis();
  bool heard = false;
  while (millis() - t0 < 3000) {
    while (EspSerial.available()) {
      Serial.write(EspSerial.read());
      heard = true;
    }
  }

  if (!heard) {
    Serial.println();
    Serial.println("[no reply from the module] check D0/D1, 3V3, GND and IO9");
  }
  Serial.println();
  Serial.println("[ready] type an AT command and press Enter");
}

void loop() {
  // module -> Serial Monitor
  while (EspSerial.available()) Serial.write(EspSerial.read());
  // Serial Monitor -> module
  while (Serial.available()) EspSerial.write(Serial.read());
}
