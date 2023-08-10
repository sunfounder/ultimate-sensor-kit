/*
  The "doorbell" project is designed to play a melody on a passive buzzer 
  module when a button connected to the Arduino Uno board is pressed. The melody and 
  its durations are predefined.

  Board: Arduino Uno R4 (or R3)
  Component: Button Module and Passive Buzzer Module
*/

// Include the pitches.h for the musical note pitches.
#include "pitches.h"

// Define the pin numbers for the button and buzzer.
const int buttonPin = 7;
const int buzzerPin = 8;

// Define the melody sequence for doorbell.
int melody[] = {
  // Minuet in G - Petzold
  NOTE_D5, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5,
  NOTE_D5, NOTE_G4, NOTE_G4,
  NOTE_E5, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_FS5,
  NOTE_G5, NOTE_G4, NOTE_G4
};

// Define the durations for each note in the melody.
// note durations: 4 = quarter note, 8 = eighth note, etc, also called tempo:
int noteDurations[] = {
  4, 8, 8, 8, 8,
  4, 4, 4,
  4, 8, 8, 8, 8,
  4, 4, 4
};

void setup() {
  // Initialize the serial communication at 9600 baud.
  Serial.begin(9600);
  // Set the button pin as an input.
  pinMode(buttonPin, INPUT);
}

void loop() {
  // Read the state of the button.
  int buttonState = digitalRead(buttonPin);

  // Check if the button is pressed.
  if (buttonState == LOW) {
    Serial.println("Button pressed");  // Print a message indicating the button press.
    buzzer();                          // Play the buzzer melody.
  }
}

void buzzer() {

  // Calculate the number of notes in the melody.
  int size = sizeof(noteDurations) / sizeof(int);

  for (int thisNote = 0; thisNote < size; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];

    // Calculate the number of notes in the melody.
    tone(buzzerPin, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(buzzerPin);
  }
}
