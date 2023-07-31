/*
  This code reads the digital value from a Button module connected to 
  pin 7 and prints it to the serial monitor every 50 milliseconds.
  When the button is pressed, it outputs a low level and remains high when released.

  Board: Arduino Uno R4 (or R3)
  Component: Button module
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
