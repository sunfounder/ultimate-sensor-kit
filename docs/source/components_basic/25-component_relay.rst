.. _cpn_relay:

5V Relay Module
==========================

.. image:: img/25_relay_module.png
    :width: 400
    :align: center

Introduction
---------------------------
5V relay modules are devices that can switch high voltage or high current devices on and off using a 5V signal from Arduino. They can be used to control devices such as lights, fans, motors, solenoids, etc. 5V relay has three high voltage terminals (NC, C, and NO) which connect to the device you want to control. The other side has three low voltage pins (Ground, Vcc, and Signal) which connect to the Arduino.


Principle
---------------------------
A relay is a device which is used to provide connection between two or more points or devices in response to the input signal applied. In other words, relays provide isolation between the controller and devices, which may operate on either AC or DC. However, they receive signals from a microcontroller which works on DC hence requiring a relay to bridge the gap. Relay is extremely useful when you need to control a large amount of current or voltage with small electrical signal.

There are 5 parts in every relay:

.. image:: img/25_relay_2.jpeg
    :width: 500
    :align: center

Electromagnet - It consists of an iron core wounded by coil of wires. When electricity is passed through, it becomes magnetic. Therefore, it is called electromagnet.

Armature - The movable magnetic strip is known as armature. When current flows through them, the coil gets energized thus producing a magnetic field which is used to make or break the normally open (N/O) or normally close (N/C) points. And the armature can be moved with direct current (DC) as well as alternating current (AC).

Spring - When no currents flow through the coil on the electromagnet, the spring pulls the armature away so the circuit cannot be completed.

Set of electrical contacts - There are two contact points:

* Normally open - connected when the relay is activated, and disconnected when it is inactive.
* Normally closed - not connected when the relay is activated, and connected when it is inactive.

Molded frame - This is typically made of plastic and provides structural support and protection for the relay.

The working principle of relay is simple. When power is supplied to the relay, currents start flowing through the control coil; as a result, the electromagnet starts energizing. Then the armature is attracted to the coil, pulling down the moving contact together thus connecting with the normally open contacts. So the circuit with the load is energized. Then breaking the circuit would be a similar case, as the moving contact will be pulled up to the normally closed contacts under the force of the spring. In this way, the switching on and off of the relay can control the state of a load circuit.

Usage
---------------------------

**Hardware components**

- Arduino Uno R4 or R3 board * 1
- 5V Relay Module * 1
- Jumper Wires

**Circuit Assembly**

.. image:: img/25_relay_module_circuit.png
    :width: 600
    :align: center

.. raw:: html
    
    <br/><br/>   

.. warning ::
    The following example demonstrates using a relay to control an LED module. 
    **While you can connect the relay to other appliances in actual applications, extreme caution is required when dealing with HIGH AC voltage. Improper or incorrect use can lead to severe injury or even death. Therefore, it is intended for people who are familiar with and knowledgeable about HIGH AC voltage. Always prioritize safety.**

Code
^^^^^^^^^^^^^^^^^^^^

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/d3f6723d-bd49-4461-96de-84293f2e6d10/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/25-component_relay.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>
   <br/><br/>  

Code explanation
^^^^^^^^^^^^^^^^^^^^

#. Setting up the relay pin:
   - The relay module is connected to pin 6 of the Arduino. This pin is defined as ``relayPin`` for ease of reference in the code.

   .. code-block:: arduino
    
      const int relayPin = 6;

#. Configuring the relay pin as an output:
   - In the ``setup()`` function, the relay pin is set as an OUTPUT using the ``pinMode()`` function. This means the Arduino will send signals (either HIGH or LOW) to this pin.

   .. code-block:: arduino

      void setup() {
        pinMode(relayPin, OUTPUT);
      }

#. Toggling the relay ON and OFF:
   - In the ``loop()`` function, the relay is first set to the OFF state using ``digitalWrite(relayPin, LOW)``. It remains in this state for 3 seconds (``delay(3000)``).
   - Then, the relay is set to the ON state using ``digitalWrite(relayPin, HIGH)``. Again, it remains in this state for 3 seconds.
   - This cycle repeats indefinitely.

   .. code-block:: arduino

      void loop() {
        digitalWrite(relayPin, LOW);
        delay(3000);

        digitalWrite(relayPin, HIGH);
        delay(3000);
      }

Additional Ideas
^^^^^^^^^^^^^^^^^^^^

- Introduce a physical button to manually control the relay's state.

- Integrate sensors (like a temperature or light sensor) to trigger the relay based on environmental conditions.

More Projects
---------------------------
* :ref:`fun_light_control_switch`
* :ref:`fun_motion_triggered_relay`
* :ref:`iot_Remote_relay_controller`
