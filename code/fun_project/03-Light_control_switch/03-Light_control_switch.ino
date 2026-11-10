/*
  This Arduino code reads the value from a photoresistance sensor module and controls 
  a relay module based on the sensor's value. If the sensorValue equals 1, the relay 
  module is switched ON (RelayPin is set HIGH); if the sensorValue does not equal 1 , 
  the relay module is switched OFF (RelayPin is set LOW).

  Board: Arduino Uno R4 (or R3)
  Component: Photoresistance Sensor Module and relay Module
*/

// Define the pin number for the relay module
const int RelayPin = 6;
// Define the pin numbers for the photoresistance sensor module
const int sensorPin = 7;

void setup() {
  // Set RelayPin as an output pin
  pinMode(RelayPin, OUTPUT);

  // Start the Serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Read the value from the photoresistance sensor module
  const int sensorValue = digitalRead(sensorPin);

  // If the light level is lower than the threshold (sensor value equals 1),
  // switch the relay module ON. The threshold can be adjusted with the module's potentiometer.
  if (sensorValue == 1) {
    digitalWrite(RelayPin, HIGH);
  } else
  // If the light level is higher than the threshold (sensor value equal 0),
  // switch the relay module OFF.
  {
    digitalWrite(RelayPin, LOW);
  }
}
