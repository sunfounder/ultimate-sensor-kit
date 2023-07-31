/*
  This Arduino code operates a remote relay using the Blynk app. The relay is 
  controlled via a virtual switch in the Blynk app. 
  When the switch on the app is turned on, it sets the digital pin connected 
  to the relay to HIGH and when it's turned off, it sets the digital pin to LOW. 

  Board: Arduino Uno R4(or R3) and ESP01
  Component: One Channel Relay Module
  Library: https://github.com/blynkkk/blynk-library 
*/

// Template ID, Device Name and Auth Token are provided by the Blynk Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPLxxxxxxxx"
#define BLYNK_TEMPLATE_NAME "remote relay"
#define BLYNK_AUTH_TOKEN "xxxxxxxxxx"

#define BLYNK_PRINT Serial  // Enables debug prints on Serial Monitor

// Include necessary libraries for ESP8266 and Blynk
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>


// Define WiFi credentials
char ssid[] = "your_ssid";
char pass[] = "your_password";  // Set password to "" for open networks.

// Software Serial on Uno
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(2, 3);  // RX, TX
#define ESP8266_BAUD 115200      // Set the ESP8266 baud rate
ESP8266 wifi(&EspSerial);

// Define the Relay pin and related variables
const int RelayPin = 6;
int switchStatus = 0;

// Create Blynk Timer object
BlynkTimer timer;

void setup() {
  // Set RelayPin as an output pin
  pinMode(RelayPin, OUTPUT);

  Serial.begin(115200);           // Start serial communication at 115200 baud rate for debugging
  EspSerial.begin(ESP8266_BAUD);  // Set ESP8266 baud rate
  delay(10);

  // Configure Blynk and connect to WiFi
  Blynk.config(wifi, BLYNK_AUTH_TOKEN);
  Blynk.connectWiFi(ssid, pass);

  // timer.setInterval(1000L, myTimerEvent);  // Setup a function to be called every second
}

void loop() {
  Blynk.run();  // Run Blynk
  timer.run();  // Run BlynkTimer
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED() {
  Blynk.syncVirtual(V0); // updates Virtual Pin V0 to the latest stored value on the server.
}

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0) {
  switchStatus = param.asInt();  // Set incoming value from pin V0 to a variable

  if (switchStatus == 1) {
    Serial.println("The switch on Blynk has been turned on.");
    digitalWrite(RelayPin, HIGH);
  } else {
    Serial.println("The switch on Blynk has been turned off.");
    digitalWrite(RelayPin, LOW);
  }
}
