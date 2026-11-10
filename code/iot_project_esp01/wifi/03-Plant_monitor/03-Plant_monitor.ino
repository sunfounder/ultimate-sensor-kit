/*
  This Arduino code is designed to monitor plant health by measuring soil moisture, 
  temperature, and humidity using an ESP01 board, DHT sensor, and a soil moisture sensor. 
  The data is sent to the Blynk app via WiFi for remote monitoring. 

  Board: Arduino Uno R4(or R3) and ESP01
  Component: DHT sensor (DHT11) and Soil Moisture Sensor
  Library: https://github.com/blynkkk/blynk-library 
           https://github.com/adafruit/DHT-sensor-library  (DHT sensor library by Adafruit)
*/

// Template ID, Device Name and Auth Token are provided by the Blynk Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPLxxxxxxxxx"
#define BLYNK_TEMPLATE_NAME "Plant Monitor"
#define BLYNK_AUTH_TOKEN "xxxxxxxxxxxx"

//Set debug prints on Serial Monitor
#define BLYNK_PRINT Serial

#include <ESP8266_Lib.h>               // Library for ESP8266
#include <BlynkSimpleShieldEsp8266.h>  // Library for Blynk

// Your WiFi credentials.
char ssid[] = "your_ssid";
char pass[] = "your_password";  // Set password to "" for open networks.

// Software Serial on Uno
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(2, 3);  // RX, TX
#define ESP8266_BAUD 115200        // Set the ESP8266 baud rate
ESP8266 wifi(&EspSerial);

// Configure DHT
#include <DHT.h>
#define DHTPIN 8           // Define the pin used to connect the sensor
#define DHTTYPE DHT11      // Define the sensor type
DHT dht(DHTPIN, DHTTYPE);  // Create a DHT object
float temperature;
float humidity;

// Configure soil moisture sensor
/* Change these values based on your observations */
#define wetSoil 320  // Define max value we consider soil 'wet'
#define drySoil 400  // Define min value we consider soil 'dry'
const int moistureSensorPin = A0;
int moisture;
String soilStatus;

BlynkTimer timer;

void setup() {

  Serial.begin(115200);           // Start serial communication at 115200 baud rate for debugging
  EspSerial.begin(ESP8266_BAUD);  // Set ESP8266 baud rate
  delay(10);

  // Configure Blynk and connect to WiFi
  Blynk.config(wifi, BLYNK_AUTH_TOKEN);
  Blynk.connectWiFi(ssid, pass);

  // Configure timer event every 5 seconds
  timer.setInterval(5000L, myTimerEvent);

  // Initialize DHT sensor
  dht.begin();
}

void loop() {
  Blynk.run();
  timer.run();  // Run BlynkTimer
}

void myTimerEvent() {
  // Please don't send more that 10 values per second.
  sendData();  // Call function to send sensor data to Blynk app
}

// Function to send sensor data to Blynk app
void sendData() {

  // Read temperature and humidity from DHT sensor
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {  // If reading fails, print an error message and stop sending data
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  moisture = analogRead(moistureSensorPin);  // Read soil moisture

  // Determine soil status based on moisture level
  String color;
  if (moisture < wetSoil) {
    soilStatus = "Soil is too wet";
    color = "#D3435C";
  } else if (moisture >= wetSoil && moisture < drySoil) {
    soilStatus = "Soil moisture is perfect";
    color = "#00FF00";
  } else {
    soilStatus = "Soil is too dry - time to water!";
    color = "#D3435C";
  }

  printData();

  // Send data to Blynk app
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V2, soilStatus);
  Blynk.virtualWrite(V3, 255);            // set blynk LED brightness
  Blynk.setProperty(V3, "color", color);  // set blynk LED color
}

// Function to print sensor data to serial monitor
void printData() {
  Serial.println("----------------------data----------------------");
  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(temperature);
  Serial.println(F("°C "));
  Serial.print("(");
  Serial.print(moisture);
  Serial.print(") ");
  Serial.println(soilStatus);
}
