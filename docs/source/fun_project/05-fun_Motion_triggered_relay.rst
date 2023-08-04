.. _fun_motion_triggered_relay:

Motion triggered relay
==========================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/fun/05-fun_Motion_triggered_relay.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>

This Arduino project aims to control a relay-operated light using a passive infrared (PIR) sensor. When the PIR sensor detects motion, the relay is activated, turning the light on. The light remains on for 5 seconds after the last detected motion.

.. warning ::
    As a demonstration, we are using a relay to control an RGB LED module. However, in real-life scenarios, this may not be the most practical approach.
    
    **While you can connect the relay to other appliances in actual applications, extreme caution is required when dealing with HIGH AC voltage. Improper or incorrect use can lead to severe injury or even death. Therefore, it is intended for people who are familiar with and knowledgeable about HIGH AC voltage. Always prioritize safety.**


1. Build the Cirduit
-----------------------------

.. image:: img/05-fun_Motion_triggered_relay_circuit.png
    :width: 90%

* :ref:`cpn_uno`
* :ref:`cpn_pir_motion`
* :ref:`cpn_relay`
* :ref:`cpn_rgb`


2. Code
-----------------------------

#. Open the ``05-Motion_triggered_relay.ino`` file under the path of ``iot-sensor-kit\fun_project\05-Motion_triggered_relay``, or copy this code into **Arduino IDE**.

   .. raw:: html
       
       <iframe src=https://create.arduino.cc/editor/sunfounder01/0e371717-97dc-43ad-bdc2-e468589da2a0/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


3. Code explanation
-----------------------------

The project revolves around the PIR motion sensor's capability to detect motion. When motion is detected, a signal is sent to the Arduino, triggering the relay module, which in turn activates a light. The light stays on for a specified duration (in this case, 5 seconds) after the last detected motion, ensuring the area remains illuminated for a short period even if motion ceases.

1. **Initial setup and variable declarations**

   This segment defines constants and variables that will be used throughout the code. We set up the relay and PIR pins and a delay constant for motion. We also have a variable to keep track of the last detected motion time and a flag to monitor if motion is detected.

   .. code-block:: arduino
   
      // Define the pin number for the relay
      const int relayPin = 9;
   
      // Define the pin number for the PIR sensor
      const int pirPin = 8;
   
      // Motion delay threshold in milliseconds
      const unsigned long MOTION_DELAY = 5000;
   
      unsigned long lastMotionTime = 0;  // Timestamp of the last motion detection
      bool motionDetected = false;       // Flag to track if motion is detected
   
   

2. **Configuration of pins in setup() function**

   In the ``setup()`` function, we configure the pin modes for both the relay and PIR sensor. We also initialize the relay to be off at the start.

   .. code-block:: arduino
   
      void setup() {
        pinMode(relayPin, OUTPUT);    // Set relayPin as an output pin
        pinMode(pirPin, INPUT);       // Set the PIR pin as an input
        digitalWrite(relayPin, LOW);  // Turn off the relay initially
      }

3. **Main logic in loop() function**

   The ``loop()`` function contains the primary logic. When the PIR sensor detects motion, it sends a ``HIGH`` signal, turning on the relay and updating the ``lastMotionTime``. If there's no motion for the specified delay (5 seconds in this case), the relay is turned off.
   
   This approach ensures that even if motion is sporadic or brief, the light remains on for at least 5 seconds after the last detected motion, providing a consistent illumination duration.

   .. code-block:: arduino
   
      void loop() {
        if (digitalRead(pirPin) == HIGH) {
          lastMotionTime = millis();     // Update the last motion time
          digitalWrite(relayPin, HIGH);  // Turn on the relay (and hence the light)
          motionDetected = true;
        }
   
        // If motion was detected earlier and 5 seconds have elapsed, turn off the relay
        if (motionDetected && (millis() - lastMotionTime >= MOTION_DELAY)) {
          digitalWrite(relayPin, LOW);  // Turn off the relay
          motionDetected = false;
        }
      }
   
   
   