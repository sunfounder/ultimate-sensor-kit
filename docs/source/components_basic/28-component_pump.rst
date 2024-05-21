.. note::

    Hello, welcome to the SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasts Community on Facebook! Dive deeper into Raspberry Pi, Arduino, and ESP32 with fellow enthusiasts.

    **Why Join?**

    - **Expert Support**: Solve post-sale issues and technical challenges with help from our community and team.
    - **Learn & Share**: Exchange tips and tutorials to enhance your skills.
    - **Exclusive Previews**: Get early access to new product announcements and sneak peeks.
    - **Special Discounts**: Enjoy exclusive discounts on our newest products.
    - **Festive Promotions and Giveaways**: Take part in giveaways and holiday promotions.

    👉 Ready to explore and create with us? Click [|link_sf_facebook|] and join today!

.. _cpn_pump:

Centrifugal Pump
==========================

.. image:: img/28_pump.png
    :width: 400
    :align: center

.. raw:: html
    
    <br/>
    
Introduction
---------------------------
A centrifugal pump is a device that can move liquids from one place to another by using a rotating impeller. It can be used to pump water, oil, chemicals, etc. A centrifugal pump has two main parts: a motor and a pump. The motor provides power to the pump and the pump converts the rotational energy into pressure and flow.


Principle
---------------------------

A centrifugal pump operates by using a spinning impeller which increases the velocity of the fluid, drawing it into the pump through an inlet pipe. As the liquid exits the impeller's outer edge, centrifugal force pushes it out through an outlet pipe, resulting in increased pressure. The faster the impeller spins, the higher the pressure and flow of the liquid.


Usage
---------------------------

**Hardware components**

- Arduino Uno R4 or R3 board * 1
- Centrifugal Pump * 1
- Jumper Wires


**Circuit Assembly**

.. image:: img/28_pump_circuit.png
    :width: 600
    :align: center

.. raw:: html
    
    <br/><br/>   

Code
^^^^^^^^^^^^^^^^^^^^

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/4c1aa3f1-7b17-4906-90e3-eb1e092fae09/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/28-component_pump.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>
   <br/><br/>  

Code explanation
^^^^^^^^^^^^^^^^^^^^

1. Two pins are defined for controlling the motor, specifically ``motorB_1A`` and ``motorB_2A``. These pins will connect to the L9110 motor control board to control the direction and speed of the motor.
  
   .. code-block:: arduino
   
      const int motorB_1A = 9;
      const int motorB_2A = 10;

2. Configuring the pins and controlling the motor:

   - The ``setup()`` function initializes the pins as ``OUTPUT`` which means they can send signals to the motor control board.

   - The ``analogWrite()`` function is used to set the motor speed. Here, setting one pin to ``HIGH`` and the other to ``LOW`` makes the pump spin in one direction. After a 5-second delay, both pins are set to 0, turning off the motor.
   
   .. code-block:: arduino
   
      void setup() {
         pinMode(motorB_1A, OUTPUT);  // set pump pin 1 as output
         pinMode(motorB_2A, OUTPUT);  // set pump pin 2 as output
         analogWrite(motorB_1A, HIGH); 
         analogWrite(motorB_2A, LOW);
         delay(5000);// wait for 5 seconds
         analogWrite(motorB_1A, 0);  // turn off the pump
         analogWrite(motorB_2A, 0);
      }


Additional Ideas
^^^^^^^^^^^^^^^^^^^^

- Reverse the pump's direction by switching the ``HIGH`` and ``LOW`` values between the pins.

- Implement a system where the pump toggles its state (on/off) using a button press.

- Implement a potentiometer to control the speed of the pump using PWM.

- Include sensors to automate the pump's operation based on certain conditions, e.g., turning the pump on/off depending on water level in a tank.

More Projects
---------------------------
* :ref:`fun_soap_dispenser`
* :ref:`iot_Auto_watering_system`

