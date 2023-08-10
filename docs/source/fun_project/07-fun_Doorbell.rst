.. _fun_doorbell:

Doorbell
==========================

.. raw:: html

   <video controls autoplay style = "max-width:100%">
      <source src="../_static/video/fun/07-fun_Doorbell.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>

The "doorbell" project aims to simulate the function of a doorbell. When a button is pressed, the Arduino plays a predefined melody using a passive buzzer module.


1. Build the Cirduit
-----------------------------

.. image:: img/07-fun_Doorbell_circuit.png
    :width: 70%

* :ref:`cpn_uno`
* :ref:`cpn_button`
* :ref:`cpn_buzzer`


2. Code
-----------------------------

#. Open the ``07-Doorbell.ino`` file under the path of ``iot-sensor-kit\fun_project\07-Doorbell``, or copy this code into **Arduino IDE**.

   .. raw:: html
       
       <iframe src=https://create.arduino.cc/editor/sunfounder01/a6511078-ed6f-49d0-a4a5-2cafc3d63e4e/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


3. Code explanation
-----------------------------

The main idea behind this project is to use the Arduino Uno board to detect a button press and, in response, play a melody on the passive buzzer. The melody consists of a sequence of notes (defined by their pitches) and their durations.

#. Setting up necessary libraries and global variables

   .. code-block:: arduino
   
      #include "pitches.h"  // This library provides the frequency values for musical notes.
   
      const int buttonPin = 7;  // Button connected to digital pin 7
      const int buzzerPin = 8;  // Buzzer connected to digital pin 8
   
      // Arrays to define the melody and the corresponding note durations
      int melody[] = {...};
      int noteDurations[] = {...};

   This segment includes the necessary library for musical notes and sets up the pins for our components. Additionally, the melody and its durations are defined in arrays.

#. Initializing the button and starting serial communication

   .. code-block:: arduino
   
      void setup() {
        Serial.begin(9600);           // Start serial communication at 9600 baud rate
        pinMode(buttonPin, INPUT);    // Set the button pin as an input
      }

   In the ``setup()`` function, we start serial communication and configure the buttonPin to act as an input.

#. Monitoring the button press to play the melody

   .. code-block:: arduino
   
      void loop() {
        int buttonState = digitalRead(buttonPin);  // Read the state of the button
   
        if (buttonState == LOW) {                  // Check if the button is pressed
          Serial.println("Button pressed");        // Send a message to serial monitor
          buzzer();                                // Play the buzzer melody
        }
      }

   Here, we continuously check the state of the button in the loop. If pressed, a message is sent to the serial monitor, and the ``buzzer()`` function (which plays the melody) is called.

#. The ``buzzer()`` function to play the melody

   .. code-block:: arduino
      
      void buzzer() {
        int size = sizeof(noteDurations) / sizeof(int);   // Calculate the number of notes
   
        for (int thisNote = 0; thisNote < size; thisNote++) {
          int noteDuration = 1000 / noteDurations[thisNote];   // Calculate note's play duration
          tone(buzzerPin, melody[thisNote], noteDuration);    // Play the note on the buzzer
   
          int pauseBetweenNotes = noteDuration * 1.30;        // Calculate pause between notes
          delay(pauseBetweenNotes);                           // Introduce the pause
          noTone(buzzerPin);                                  // Stop playing the note
        }
      }

   In the ``buzzer()`` function, the melody's notes are played sequentially. The ``tone()`` function generates a tone on the buzzer for a specified duration. After playing each note, there's a brief pause before playing the next note.




