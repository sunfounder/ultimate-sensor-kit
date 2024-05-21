.. note::

    Hello, welcome to the SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasts Community on Facebook! Dive deeper into Raspberry Pi, Arduino, and ESP32 with fellow enthusiasts.

    **Why Join?**

    - **Expert Support**: Solve post-sale issues and technical challenges with help from our community and team.
    - **Learn & Share**: Exchange tips and tutorials to enhance your skills.
    - **Exclusive Previews**: Get early access to new product announcements and sneak peeks.
    - **Special Discounts**: Enjoy exclusive discounts on our newest products.
    - **Festive Promotions and Giveaways**: Take part in giveaways and holiday promotions.

    👉 Ready to explore and create with us? Click [|link_sf_facebook|] and join today!

.. _cpn_gas:

Gas/Smoke Sensor Module (MQ2) 
=====================================

.. image:: img/02_mq2_gas_module.png
    :width: 350
    :align: center

Introduction
---------------------------
The MQ-2 sensor is a versatile gas sensor capable of detecting a wide range of gases including alcohol, carbon monoxide, hydrogen, isobutene, liquefied petroleum gas, methane, propane, and smoke. It is popular among beginners due to its low cost and easy-to-use features.

Principle
---------------------------
The MQ-2 sensor works on the principle of resistance changes in the presence of different gases. When the target gas comes in contact with the heated MOS(Metal Oxide Semiconductor) material, it undergoes oxidation or reduction reactions that change the resistance of the MOS material. It is noteworthy that the MQ2 gas sensor is capable of detecting multiple gases, but lacks the ability to differentiate between them. This is a common characteristic of most gas sensors. 

The sensor has a built-in potentiometer that allows you to adjust the sensor digital output (D0) threshold. When the concentration of gas in the air exceeds a certain threshold value, the resistance of the sensor changes. This change in resistance is then converted into an electrical signal that can be read by an Arduino board.

Usage
---------------------------

**Hardware components**

- Arduino Uno R4 or R3 board * 1
- Gas Sensor Module(MQ2) * 1
- Jumper Wires

**Circuit Assembly**

.. image:: img/02_mq2_sensor_circuit.png
    :width: 520
    :align: center

.. raw:: html
    
    <br/><br/>   

Code
^^^^^^^^^^^^^^^^^^^^
.. raw:: html

    <iframe src=https://create.arduino.cc/editor/sunfounder01/1de900bf-d3bf-411a-8f6b-23e53b704bf5/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/02-component_gas.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>
   <br/><br/>  

Code explanation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

1. The first line of code is a constant integer declaration for the gas sensor pin. We use the analog pin A0 to read the output from the gas sensor.

   .. code-block:: arduino
   
      const int sensorPin = A0;

2. The ``setup()`` function is where we initialize our serial communication at a baud rate of 9600. This is necessary to print the readings from the gas sensor to the serial monitor.

   .. code-block:: arduino
   
      void setup() {
        Serial.begin(9600);  // Start serial communication at 9600 baud rate
      }

3. The ``loop()`` function is where we continuously read the analog value from the gas sensor and print it to the serial monitor. We use the ``analogRead()`` function to read the analog value from the sensor. We then wait for 50 milliseconds before the next reading. This delay gives some breathing space for the serial monitor to process the data.

   .. code-block:: arduino
   
      void loop() {
        Serial.print("Analog output: ");
        Serial.println(analogRead(sensorPin));  // Read the analog value of the gas sensor and print it to the serial monitor
        delay(50);                             // Wait for 50 milliseconds
      }

.. note:: 

  MQ2 is a heating-driven sensor that usually requires preheating before use. During the preheating period, the sensor typically reads high and gradually decreases until it stabilizes.

Additional Ideas
^^^^^^^^^^^^^^^^

-  add a visual or auditory warning system (using LEDs or a buzzer) that triggers when gas concentrations exceed certain thresholds.


More Projects
---------------------------
* :ref:`fun_gas_leak_alarm`



