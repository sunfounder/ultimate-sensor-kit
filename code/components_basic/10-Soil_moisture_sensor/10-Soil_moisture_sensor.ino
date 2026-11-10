/*
  This program reads the analog input from a capacitive soil moisture sensor 
  connected to pin A0 and prints the value to the serial monitor. 
  The smaller the value, the higher the soil moisture level. 

  Board: Arduino Uno R4 (or R3)
  Component: Capacitive soil moisture sensor
*/

// Define the sensor pin
const int sensorPin = A0;

void setup() {
  Serial.begin(9600);// Initialize serial communication at 9600 baud rate
}

void loop() {
  Serial.println(analogRead(sensorPin)); // The smaller the value, the higher the soil moisture level
  delay(500);// Wait for 500 milliseconds before taking the next reading
}
