/*************************************************************
  WARNING!
    It's very tricky to get it working. Please read this article:
    http://help.blynk.cc/hardware-and-libraries/arduino/esp8266-with-at-firmware

 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID   "TMPLxxxxxx"   // optional: connecting only needs the token
#define BLYNK_TEMPLATE_NAME "Ultimate Sensor Kit"
#define BLYNK_AUTH_TOKEN    "YourAuthToken"


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "your_ssid";
char pass[] = "your_password";

// Hardware Serial on Mega, Leonardo, Micro...
// #define EspSerial Serial1

// or Software Serial on Uno, Nano...
// ==== ESPC2-01 (ESP32-C2): use hardware serial D0/D1 ====
#define EspSerial Serial1

// Your ESP8266 baud rate:
#define ESP8266_BAUD 115200

ESP8266 wifi(&EspSerial);

// ---- ESPC2-01 power-up: wait for the module to boot, then turn echo off ----
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
  EspSerial.print("ATE0\r\n");     // echo off, otherwise the reply mixes in the command text
  delay(300);
  while (EspSerial.available()) EspSerial.read();
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  espModuleInit();

  Blynk.begin(auth, wifi, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, wifi, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, wifi, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
