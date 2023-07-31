/*
  This Arduino code is designed to control an RGB LED connected to an Arduino Uno via a 
  JDY-31 Bluetooth module. The program receives RGB color values via Bluetooth as characters 
  from a serial port and sets the color of the LED accordingly. The color values are 
  identified by the characters 'R', 'G', and 'B', followed by the color intensity value. 
  After processing the data, it resets the buffer for the next input.

  Board: Arduino Uno R4 (or R3)
  Component:  JDY-31 Bluetooth Module
*/

// Set up Bluetooth module communication
#include <SoftwareSerial.h>
SoftwareSerial bleSerial(3, 4);  //Rx,Tx

// Define and initialize message handling variables
#define max_char 12
char message[max_char];  // Buffer for incoming messages
char r_char;             // Character read from serial input
byte currentIndex = 0;   // Current index in the message buffer

// Define the RGB LED pins
const int redPin = 10;
const int greenPin = 9;
const int bluePin = 11;

// Initialize the RGB color values
int redValue = 0;
int greenValue = 255;
int blueValue = 0;

// Temporary color values as Strings for conversion
String redTempValue;
String greenTempValue;
String blueTempValue;

int flag = 0;       // Flag to indicate if a new instruction has been received
char currentColor;  // Current color being read (R, G, or B)

void setup() {
  // Set the RGB LED pins as output
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  bleSerial.begin(9600);
}

void loop() {
  // Read incoming message from serial input
  while (bleSerial.available() > 0) {
    flag = 0;   // Reset the flag indicating a new instruction has been received

    //the message can have up to 12 characters
    if (currentIndex < (max_char - 1)) {
      r_char = bleSerial.read();       // Read a character from the serial input
      message[currentIndex] = r_char;  // Store the character in the message array

      // Determine which color value is being read based on the character received
      if (r_char == 'R') {
        currentColor = 'R';
        redTempValue = "";
      } else if (r_char == 'G') {
        currentColor = 'G';
        greenTempValue = "";
      } else if (r_char == 'B') {
        currentColor = 'B';
        blueTempValue = "";
      }

      // Add character to the appropriate color value string
      if (currentColor == 'R' && r_char != 'R') {
        redTempValue += r_char;
      } else if (currentColor == 'G' && r_char != 'G') {
        greenTempValue += r_char;
      } else if (currentColor == 'B' && r_char != 'B') {
        blueTempValue += r_char;
      }

      currentIndex++;                // Increment currentIndex for the next character
      message[currentIndex] = '\0';  // End the string
    }
  }

  // If a complete message has been read, update the RGB LED color
  if (flag == 0) {
    Serial.println(message); // for debug

    // Update LED color
    analogWrite(redPin, redTempValue.toInt());
    analogWrite(greenPin, greenTempValue.toInt());
    analogWrite(bluePin, blueTempValue.toInt());

    flag = 1;  // Set the flag indicating that the message has been processed

    // Reset message buffer for the next incoming message
    for (int i = 0; i < 12; i++) {
      message[i] = '\0';
    }

    // Reset currentIndex for the next message
    currentIndex = 0;
  }
}