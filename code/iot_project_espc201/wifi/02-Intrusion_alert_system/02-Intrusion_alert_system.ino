/*
  Intrusion Alert System

  A PIR sensor watches the room. While the switch in the Blynk app is on ("away" mode),
  any movement is reported to the cloud and your phone gets a notification.

  Board:     Arduino Uno R4 Minima
  Module:    ESPC2-01 (ESP32-C2) with ESP-AT firmware, on D0/D1
  Component: PIR motion sensor (HC-SR501)
  Library:   https://github.com/blynkkk/blynk-library
*/

// The three lines below come from the Blynk device page.
// They are exactly the same in every project of this kit.
#define BLYNK_TEMPLATE_ID   "TMPLxxxxxx"
#define BLYNK_TEMPLATE_NAME "Ultimate Sensor Kit"
#define BLYNK_AUTH_TOKEN    "YourAuthToken"

#define BLYNK_PRINT Serial   // show Blynk's own log on the Serial Monitor

#include <ESP8266_Lib.h>               // driver that sends AT commands to the module
#include <BlynkSimpleShieldEsp8266.h>  // Blynk running on top of that driver

// Your Wi-Fi network. Use "" as the password for an open network.
char ssid[] = "your_ssid";
char pass[] = "your_password";

// The module is a modem: the sketch talks to it over a serial port.
// On the R4 that is Serial1 (D0/D1), a real hardware port - no bit errors at 115200.
#define EspSerial Serial1
#define ESP8266_BAUD 115200
ESP8266 wifi(&EspSerial);

const int sensorPin = 8;   // PIR output: HIGH = movement, LOW = quiet

int state = 0;           // last reading of the PIR pin
int awayHomeMode = 0;    // 1 = the switch in the app is on, so the alarm is armed

BlynkTimer timer;        // runs a function on a schedule, without blocking the loop

// The module needs about a second to boot and prints its start-up log on the same wire.
// If the sketch sends AT commands too early, that log mixes with the replies and Blynk
// cannot read them. So wait for the word "ready", then switch the echo off.
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
  EspSerial.print("ATE0\r\n");     // echo off, otherwise every reply starts with the command
  delay(300);
  while (EspSerial.available()) EspSerial.read();
}

void setup() {
  pinMode(sensorPin, INPUT);

  Serial.begin(115200);           // Serial Monitor
  EspSerial.begin(ESP8266_BAUD);  // module
  delay(10);

  espModuleInit();                                  // let the module finish booting
  Blynk.config(wifi, BLYNK_AUTH_TOKEN);             // remember the token
  Blynk.connectWiFi(ssid, pass);                    // then go online

  timer.setInterval(1000L, myTimerEvent);           // check the sensor once per second
}

void loop() {
  Blynk.run();   // keeps the connection alive
  timer.run();   // fires myTimerEvent() when it is due
}

// Called every time the board connects - including after a power cut.
// It asks the server for the current switch position, so the board remembers that you
// are away even if it restarted.
BLYNK_CONNECTED() {
  Blynk.syncVirtual(V1);
}

// Called every time the switch in the app changes (V1 = away_mode).
BLYNK_WRITE(V1) {
  awayHomeMode = param.asInt();

  if (awayHomeMode == 1) {
    Serial.println("The switch on Blynk has been turned on.");
    Blynk.virtualWrite(V2, "Detecting signs of intrusion...");
  } else {
    Serial.println("The switch on Blynk has been turned off.");
    Blynk.virtualWrite(V2, "Away home mode close");
  }
}

void myTimerEvent() {
  sendData();   // about once per second; Blynk allows at most 10 values per second
}

unsigned long lastAlert = 0;

void sendData() {
  int now = digitalRead(sensorPin);

  // Print only when the level changes, so the monitor stays readable.
  if (now != state) {
    Serial.print("pin 8 -> ");
    Serial.print(now);
    Serial.print("   (Away mode = ");
    Serial.print(awayHomeMode);
    Serial.println(")");
  }

  // Report on the edge LOW -> HIGH only. Reporting while the pin simply stays HIGH
  // would send one message every second and use up the Blynk quota within minutes.
  bool rising = (now == HIGH && state == LOW);
  state = now;

  if (awayHomeMode == 1 && rising && millis() - lastAlert > 5000) {
    lastAlert = millis();
    Serial.println("Somebody here!");
    Blynk.virtualWrite(V2, "Somebody in your house! Please check!");
    Blynk.logEvent("intrusion_detected");
  }
}
