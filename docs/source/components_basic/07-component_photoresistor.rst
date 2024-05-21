.. note::

    Hello, welcome to the SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasts Community on Facebook! Dive deeper into Raspberry Pi, Arduino, and ESP32 with fellow enthusiasts.

    **Why Join?**

    - **Expert Support**: Solve post-sale issues and technical challenges with help from our community and team.
    - **Learn & Share**: Exchange tips and tutorials to enhance your skills.
    - **Exclusive Previews**: Get early access to new product announcements and sneak peeks.
    - **Special Discounts**: Enjoy exclusive discounts on our newest products.
    - **Festive Promotions and Giveaways**: Take part in giveaways and holiday promotions.

    👉 Ready to explore and create with us? Click [|link_sf_facebook|] and join today!

.. _cpn_photoresistor:

Photoresistor Module
==========================

.. image:: img/07_photoresistor_module.png
    :width: 400
    :align: center

Introduction
---------------------------
A photoresistor module is a device that can detect the intensity of light in the environment. It can be used for various purposes, such as adjusting the brightness of a device, detecting day and night, or activating a light switch.

An important component of the photoresistor module is the photoresistor. A photoresistor is a light-controlled variable resistor. The resistance of a photoresistor decreases with increasing incident light intensity; in other words, it exhibits photo conductivity.

A photoresistor can be applied in light-sensitive detector circuits and light-activated and dark-activated switching circuits acting as a resistance semiconductor. In the dark, a photoresistor can have a resistance as high as several megaohms (MΩ), while in the light, a photoresistor can have a resistance as low as a few hundred ohms.

Here is the electronic symbol of photoresistor.

.. image:: img/07_photoresistor_symbol_2.png
    :width: 200
    :align: center

Principle
---------------------------
The photoresistor module works on the principle of changing resistance in response to different light intensities. The sensor has a built-in potentiometer that adjusts the sensor's digital output (D0) threshold. When the intensity of light exceeds a certain threshold, the resistance of the sensor changes. This change in resistance is then converted to an electrical signal that can be read by the Arduino board.


Usage
---------------------------

**Hardware components**

- Arduino Uno R4 or R3 board * 1
- Photoresistor Module * 1
- Jumper Wires

**Circuit Assembly**

.. image:: img/07_photoresistor_module_circuit.png
    :width: 400
    :align: center

.. raw:: html
    
    <br/><br/>   

Code
^^^^^^^^^^^^^^^^^^^^

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/72eab12e-5539-46a5-9205-3fede2a236fc/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/07-component_photoresistor.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>
   <br/><br/>  

Code explanation
^^^^^^^^^^^^^^^^^^^^

#. This line of code defines the pin number to which the photoresistance sensor is connected on the Arduino board.

   .. code-block:: arduino

      const int sensorPin = 7;

#. The ``setup()`` function is a special function in Arduino that is executed only once when the Arduino is powered on or reset. In this project, the sensorPin is set as INPUT because we are reading values from it. The Serial.begin(9600) command initiates serial communication at a baud rate of 9600.

   .. code-block:: arduino

      void setup() {
        pinMode(sensorPin, INPUT);  
        Serial.begin(9600);         
      }

#. The ``loop()`` function is the main function where the program runs repeatedly. In this function, the digitalRead function reads the digital value from the photoresistor sensor and prints it to the serial monitor using Serial.println. The ``delay(50)`` command makes the program wait for 50 milliseconds before taking the next reading.

   .. code-block:: arduino

      void loop() {
        Serial.println(digitalRead(sensorPin));  
        delay(50);
      }


Additional Ideas
^^^^^^^^^^^^^^^^^^^^

- Use the sensor to turn on/off an LED or relay. 
- Plot the **analog output** instead of just digital HIGH/LOW. Use **AO** pin.


More Projects
---------------------------
* :ref:`fun_light_control_switch`

