/*
  This code reads the analog values from two joystick axes (X and Y) connected to 
  analog pins A0 and A1, respectively, and prints them to the serial monitor.

  Board: Arduino Uno R4 (or R3)
  Component: Josick moudule
*/

const int xPin = A0;  //the VRX attach to
const int yPin = A1;  //the VRY attach to

void setup() {
  Serial.begin(9600);  // Begin serial communication with a baud rate of 9600
}

void loop() {
  Serial.print("X: ");
  Serial.print(analogRead(xPin));  // print the value of VRX
  Serial.print(" | Y: ");
  Serial.println(analogRead(yPin));  // print the value of VRX
  delay(50);
}
