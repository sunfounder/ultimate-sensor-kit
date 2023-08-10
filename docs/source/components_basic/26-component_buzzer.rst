.. _cpn_buzzer:

Passive Buzzer Module
==========================

.. image:: img/26_passive_buzzer_module.png
    :width: 400
    :align: center

Introduction
---------------------------
A passive buzzer is a device that generates sound when an electrical signal is applied to it. It is called passive because it does not have an internal oscillator to generate sound on its own. Instead, it relies on an external signal from a microcontroller like Arduino to produce sound. The passive buzzer module is a small electronic component that contains a passive buzzer and some additional circuitry that makes it easier to use with Arduino.

Principle
---------------------------
The working principle of the passive buzzer module is based on the piezoelectric effect. When an electrical signal is applied to the buzzer, it causes a piezoelectric crystal inside the buzzer to vibrate at a specific frequency. This vibration produces sound waves that we can hear. The frequency of the sound produced by the buzzer depends on the frequency of the electrical signal applied to it. By changing the frequency of the signal, we can change the pitch of the sound produced by the buzzer.

Usage
---------------------------

**Hardware components**

- Arduino Uno R4 or R3 board * 1
- Passive Buzzer Module * 1
- Jumper Wires


**Circuit Assembly**

.. image:: img/26_passive_buzzer_module_circuit.png
    :width: 400
    :align: center

.. raw:: html
    
    <br/><br/>   

Code
^^^^^^^^^^^^^^^^^^^^

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/5b24a3d9-8688-4dc2-ad3a-cce82f6bd3a7/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/26-component_buzzer.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>
   <br/><br/>  

Code explanation
^^^^^^^^^^^^^^^^^^^^

1. Including the pitches library:
   This library provides the frequency values for various musical notes, allowing you to use musical notation in your code.

   .. code-block:: arduino
       
      #include "pitches.h"

2. Defining constants and arrays:

   * ``buzzerPin`` is the digital pin on the Arduino where the buzzer is connected.

   * ``melody[]`` is an array that stores the sequence of notes to be played.

   * ``noteDurations[]`` is an array that stores the duration of each note in the melody.

   .. code-block:: arduino
   
      const int buzzerPin = 8;
      int melody[] = {
        NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
      };
      int noteDurations[] = {
        4, 8, 8, 4, 4, 4, 4, 4
      };

3. Playing the melody:

   * The ``for`` loop iterates over each note in the melody.

   * The ``tone()`` function plays a note on the buzzer for a specific duration.

   * A delay is added between notes to distinguish them.

   * The ``noTone()`` function stops the sound.



   .. code-block:: arduino
   
      void setup() {
        for (int thisNote = 0; thisNote < 8; thisNote++) {
          int noteDuration = 1000 / noteDurations[thisNote];
          tone(buzzerPin, melody[thisNote], noteDuration);
          int pauseBetweenNotes = noteDuration * 1.30;
          delay(pauseBetweenNotes);
          noTone(buzzerPin);
        }
      }

4. Empty loop function:
   Since the melody is played only once in the setup, there's no code in the loop function.


Additional Ideas
^^^^^^^^^^^^^^^^^^^^

- Modify the melody: You can experiment by changing the notes and durations in the ``melody[]`` and ``noteDurations[]`` arrays to create your own tunes. If you are interested, there is a repository (|link_arduino-songs|) on GitHub that provides Arduino code for playing different songs. Although their approach may be different from this project, you can refer to their notes and durations.
- Add a button: Integrate a push-button to the circuit and modify the code to play the melody when the button is pressed.

More Projects
---------------------------
* :ref:`fun_doorbell`
* :ref:`fun_gas_leak_alarm`
