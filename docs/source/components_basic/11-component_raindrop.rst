.. note::

    Hello, welcome to the SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasts Community on Facebook! Dive deeper into Raspberry Pi, Arduino, and ESP32 with fellow enthusiasts.

    **Why Join?**

    - **Expert Support**: Solve post-sale issues and technical challenges with help from our community and team.
    - **Learn & Share**: Exchange tips and tutorials to enhance your skills.
    - **Exclusive Previews**: Get early access to new product announcements and sneak peeks.
    - **Special Discounts**: Enjoy exclusive discounts on our newest products.
    - **Festive Promotions and Giveaways**: Take part in giveaways and holiday promotions.

    👉 Ready to explore and create with us? Click [|link_sf_facebook|] and join today!

.. _cpn_raindrop:

Raindrop Detection Module
==========================

.. image:: img/11_raindrop_detection_module.jpg
    :width: 300
    :align: center

Introduction
---------------------------

A raindrop sensor, or raindrop detection sensor, is used to detect whether it is raining and also the rainfall. It is widely used in the automatic wiper system, smart lighting system and sunroof system of automobiles.

Principle
---------------------------

Raindrop sensor is basically a board on which nickel is coated in the form of lines. It works on the principal of resistance. When there is no rain drop on board. Resistance is high so we gets high voltage according to V=IR. When rain drop present it reduces the resistance because water is conductor of electricity and presence of water connects nickel lines in parallel so reduced resistance and reduced voltage drop across it. The more intense the rainfall the lower the resistance.

Module Schematic Diagram
---------------------------

.. image:: img/11_raindrop_detection_module_schematic.png
    :width: 100%
    :align: center

.. raw:: html

   <br/>

Usage
---------------------------

**Hardware components**

- Arduino Uno R4 or R3 board * 1
- Raindrop Detection Module * 1
- Jumper Wires


**Circuit Assembly**

.. image:: img/11_raindrop_detection_module_circuit.png
    :width: 400
    :align: center

.. raw:: html
    
    <br/><br/>   

Code
^^^^^^^^^^^^^^^^^^^^

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/5dbd8745-a9a9-4b19-b245-02c073d89ce8/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/11-component_raindrop.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>
   <br/><br/>  

Code explanation
^^^^^^^^^^^^^^^^^^^^

1. Defining sensor pin

   Here, a constant integer named ``sensorPin`` is defined and assigned the value 7. This corresponds to the digital pin on the Arduino board where the raindrops detection sensor is connected.
   
   .. code-block:: arduino
   
       const int sensorPin = 7;

2. Setting up the pin mode and initiating serial communication

   In the ``setup()`` function, two essential steps are performed. Firstly, ``pinMode()`` is used to set the ``sensorPin`` as an input, enabling us to read digital values from the raindrops sensor. Secondly, serial communication is initialized with a baud rate of 9600.
   
   .. code-block:: arduino
   
       void setup() {
         pinMode(sensorPin, INPUT);
         Serial.begin(9600);
       }

3. Reading the digital value and sending it to the serial monitor. 

   The ``loop()`` function reads the digital value from the raindrops sensor using ``digitalRead()``. This value (either HIGH or LOW) is printed to the Serial Monitor. The program then waits for 50 milliseconds before the next reading.
   
   .. code-block:: arduino
   
       void loop() {
         Serial.println(digitalRead(sensorPin));
         delay(50);
       }

Additional Ideas
^^^^^^^^^^^^^^^^^^^^

- Add an LED indicator that lights up when rain is detected
- Connect a buzzer to the Arduino to sound an alert when rain is detected, which can act as an early warning system for events like picnics or outdoor activities.


