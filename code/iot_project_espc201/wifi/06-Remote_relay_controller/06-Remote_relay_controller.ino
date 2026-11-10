/*
  Remote Relay Controller with Blynk

  A switch in the Blynk app drives a relay on the board. Flip the switch on your phone
  and the relay clicks - from anywhere there is internet.

  Board:     Arduino Uno R4 Minima
  Module:    ESPC2-01 (ESP32-C2) with ESP-AT firmware, on D0/D1
  Component: one-channel relay module
  Library:   https://github.com/blynkkk/blynk-library
*/

// The three lines below come from the Blynk device page.
// They are exactly the same in every project of this kit.
#define BLYNK_TEMPLATE_ID   "TMPLxxxxxx"
#define BLYNK_TEMPLATE_NAME "Ultimate Sensor Kit"
#define BLYNK_AUTH_TOKEN "lHSd4Q5pXP7YKUovVfPZYZqC0UHVORY6"

#define BLYNK_PRINT Serial   // show Blynk's own log on the Serial Monitor

#include <ESP8266_Lib.h>               // sends the AT commands
#include <BlynkSimpleShieldEsp8266.h>  // Blynk on top of them

// Your Wi-Fi network. Use "" as the password for an open network.
char ssid[] = "MakerStarsHall";
char pass[] = "sunfounder";

// The module works as a modem: the sketch talks to it over a serial port.
// On the R4 that is Serial1 (D0/D1), a real hardware port - no bit errors at 115200.
#define EspSerial Serial1
#define ESP8266_BAUD 115200
ESP8266 wifi(&EspSerial);

// The relay module is on D6. HIGH turns it on; if your module switches the other way
// round (some are active LOW), swap HIGH and LOW in BLYNK_WRITE below.
const int RelayPin = 6;
int switchStatus = 0;   // last value sent by the switch in the app

BlynkTimer timer;

// The module needs about a second to boot and prints its start-up log on the same wire.
// Wait for "ready", then switch the echo off so the replies stay readable.
void espModuleInit() {
  unsigned long t0 = millis();
  String buf;
  while (millis() - t0 < 5000) {
    while (EspSerial.available() && buf.length() < 512) {
      buf += (char)EspSerial.read();
      if (buf.indexOf("ready") >= 0) t0 = millis() - 5000;   // leave the loop
    }
  }
  while (EspSerial.available()) EspSerial.read();
  EspSerial.print("ATE0\r\n");     // echo off, otherwise the reply mixes in the command
  delay(300);
  while (EspSerial.available()) EspSerial.read();
}

void setup() {
  pinMode(RelayPin, OUTPUT);      // the relay starts switched off
  digitalWrite(RelayPin, LOW);

  Serial.begin(115200);           // Serial Monitor
  EspSerial.begin(ESP8266_BAUD);  // module
  delay(10);

  espModuleInit();                        // let the module finish booting
  Blynk.config(wifi, BLYNK_AUTH_TOKEN);   // remember the token
  Blynk.connectWiFi(ssid, pass);          // then go online
}

void loop() {
  Blynk.run();   // keeps the connection alive
  timer.run();   // reserved for future use
}

// Called every time the board connects - including after a power cut.
// It asks the server for the current switch position, so the relay comes back in the
// state you left it, even if the board restarted.
BLYNK_CONNECTED() {
  Blynk.syncVirtual(V7);
}

// Called every time the switch in the app changes (V7 = relay_status).
// 1 = switch on, 0 = switch off.
BLYNK_WRITE(V7) {
  switchStatus = param.asInt();

  if (switchStatus == 1) {
    Serial.println("The switch on Blynk has been turned on.");
    digitalWrite(RelayPin, HIGH);
  } else {
    Serial.println("The switch on Blynk has been turned off.");
    digitalWrite(RelayPin, LOW);
  }
}
