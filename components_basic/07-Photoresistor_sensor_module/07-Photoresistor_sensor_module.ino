/*
  This code reads the digital value from a photoresistor sensor connected to 
  pin 7 and prints it to the serial monitor every 50 milliseconds.
  When the light intensity exceeds the threshold, a low level is output; 
  conversely, when the light intensity is below the threshold, a high level is output.

  Board: Arduino Uno R4 (or R3)
  Component: Photoresistance Sensor Module
*/

// Define the pin numbers for the photoresistance sensor module
const int sensorPin = 7;

void setup() {
  pinMode(sensorPin, INPUT);  // Set sensorPin as input
  Serial.begin(9600);         // Start serial communication at 9600 baud rate
}

void loop() {
  Serial.println(digitalRead(sensorPin));  // Read the digital value from the sensor and print it to the serial monitor
  delay(50);
}
