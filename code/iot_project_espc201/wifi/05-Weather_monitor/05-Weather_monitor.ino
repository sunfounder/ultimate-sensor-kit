/*
  Weather Monitor with ThingSpeak

  A BMP280 sensor measures temperature and air pressure. Every 20 seconds the board
  sends both values to a ThingSpeak channel, where you can watch them as a graph from
  any browser.

  Board:     Arduino Uno R4 Minima
  Module:    ESPC2-01 (ESP32-C2) with ESP-AT firmware, on D0/D1
  Component: BMP280 pressure sensor (I2C, address 0x76 or 0x77)
  Library:   https://github.com/adafruit/Adafruit_BMP280_Library
*/

#define EspSerial Serial1
#define DEBUG true

// ---- what you have to fill in ----
String mySSID = "your_ssid";      // your Wi-Fi network
String myPWD = "your_password";  // its password
String myAPI  = "xxxxxxxxxxxxxxx"; // the Write API Key of your ThingSpeak channel
String myHOST = "api.thingspeak.com";
String myPORT = "80";

// ThingSpeak asks for at least 15 s between two updates on a free account.
unsigned long lastConnectionTime = 0;
const unsigned long postingInterval = 20000L;   // one update every 20 s

// ---- the BMP280 on I2C ----
#include <Wire.h>
#include <Adafruit_BMP280.h>
#define BMP280_ADDRESS 0x76
Adafruit_BMP280 bmp;
unsigned bmpStatus;
float pressure;
float temperature;

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
  delay(1000);                        // let the rest of the boot log come out
  while (EspSerial.available()) EspSerial.read();

  EspSerial.print("ATE0\r\n");      // echo off
  delay(500);
  while (EspSerial.available()) EspSerial.read();
}

// Send one AT command and collect the reply. Never blocks longer than waitMs,
// and never lets the reply grow without a limit.
String at(const String& cmd, unsigned long waitMs, const char* okMark, const char* errMark) {
  while (EspSerial.available()) EspSerial.read();
  EspSerial.print(cmd);
  EspSerial.print("\r\n");
  if (DEBUG) {
    Serial.print("  > ");
    Serial.println(cmd);
  }

  unsigned long t0 = millis();
  String r;
  while (millis() - t0 < waitMs) {
    while (EspSerial.available() && r.length() < 512) r += (char)EspSerial.read();
    if (okMark && r.indexOf(okMark) >= 0) break;
    if (errMark && r.indexOf(errMark) >= 0) break;
  }
  return r;
}

bool wifiOK = false;

bool joinWiFi() {
  at("AT+CWMODE=1", 1500, "OK", "ERROR");

  Serial.print("joining Wi-Fi ... ");
  String r = at("AT+CWJAP=\"" + mySSID + "\",\"" + myPWD + "\"", 20000,
               "WIFI GOT IP", "FAIL");
  bool ok = r.indexOf("WIFI GOT IP") >= 0;
  if (ok) {
    Serial.println("connected");
  } else {
    Serial.println("FAILED");
    r.replace("\r", "");
    r.replace("\n", " | ");
    Serial.print("  module said: ");
    Serial.println(r.length() ? r : "(nothing)");
  }
  return ok;
}

void setup() {
  Serial.begin(115200);
  delay(300);
  Serial.println();
  Serial.println("=== Weather Monitor (ThingSpeak) ===");

  EspSerial.begin(115200);
  espModuleInit();
  Serial.println("module is ready");

  wifiOK = joinWiFi();

  // The BMP280 answers on 0x76 or 0x77 depending on how its SDO pin is wired.
  if (!bmp.begin(BMP280_ADDRESS)) {
    if (!bmp.begin(0x77)) {
      Serial.println(F("Could not find a BMP280, check the wiring and the address"));
      while (1) delay(10);   // there is nothing to do without the sensor
    }
  }
  Serial.println("BMP280 is ready");

  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                  Adafruit_BMP280::SAMPLING_X2,
                  Adafruit_BMP280::SAMPLING_X16,
                  Adafruit_BMP280::FILTER_X16,
                  Adafruit_BMP280::STANDBY_MS_500);
}

void loop() {
  if (!wifiOK) return;   // nothing to send without a network

  if (millis() - lastConnectionTime > postingInterval) {
    sendData();
  }
}

void sendData() {
  pressure = bmp.readPressure();
  temperature = bmp.readTemperature();

  if (isnan(pressure) || isnan(temperature)) {
    Serial.println("Failed to read from the BMP280!");
    return;
  }

  // The request is short, so it fits in one line - ThingSpeak accepts a GET with the
  // values in the URL and answers with a single number.
  String req = "GET /update?api_key=" + myAPI;
  req += "&field1=" + String(temperature);
  req += "&field2=" + String(pressure);
  req += " HTTP/1.1\r\nHost: api.thingspeak.com\r\nConnection: close\r\n\r\n";

  at("AT+CIPMUX=0", 1000, "OK", "ERROR");

  String r = at("AT+CIPSTART=\"TCP\",\"" + myHOST + "\"," + myPORT, 5000, "OK", "ERROR");
  if (r.indexOf("OK") < 0 && r.indexOf("ALREADY") < 0) {
    Serial.println("  could not reach ThingSpeak, update dropped");
    return;
  }

  // Ask the module to accept exactly req.length() bytes, then wait for the ">" prompt.
  while (EspSerial.available()) EspSerial.read();
  EspSerial.print("AT+CIPSEND=");
  EspSerial.print(req.length());
  EspSerial.print("\r\n");

  bool prompt = false;
  unsigned long t0 = millis();
  while (millis() - t0 < 3000) {
    while (EspSerial.available()) {
      if (EspSerial.read() == '>') { prompt = true; break; }
    }
    if (prompt) break;
  }
  if (!prompt) {
    Serial.println("  no > prompt, update dropped");
    at("AT+CIPCLOSE", 1000, "OK", "ERROR");
    return;
  }

  EspSerial.print(req);
  Serial.println("  update sent to ThingSpeak");
  delay(1500);

  at("AT+CIPCLOSE", 1000, "OK", "ERROR");

  printBMP();
  lastConnectionTime = millis();
}

void printBMP() {
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" C.  Pressure: ");
  Serial.print(pressure);
  Serial.println(" Pa");
  Serial.println();
}
