.. _fun_light_control_switch:

Light control switch
==========================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/fun/03-fun_Light_control_switch.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>

This project is a light control switch system. The main idea is to use a photoresistance sensor module to detect the ambient light level and, based on this detection, control a relay module. If the ambient light is below a certain threshold, the relay is switched on. Conversely, if the ambient light is above the threshold, the relay is switched off.

.. warning ::
    As a demonstration, we are using a relay to control an RGB LED module. However, in real-life scenarios, this may not be the most practical approach.
    
    **While you can connect the relay to other appliances in actual applications, extreme caution is required when dealing with HIGH AC voltage. Improper or incorrect use can lead to severe injury or even death. Therefore, it is intended for people who are familiar with and knowledgeable about HIGH AC voltage. Always prioritize safety.**


1. Build the Cirduit
-----------------------------

.. image:: img/03-fun_Light_control_switch_circuit.png
    :width: 90%

* :ref:`cpn_uno`
* :ref:`cpn_photoresistor`
* :ref:`cpn_relay`
* :ref:`cpn_rgb`


2. Code
-----------------------------

#. Open the ``03-fun_Light_control_switch.ino`` file under the path of ``ultimate-sensor-kit\fun_project\03-fun_Light_control_switch``, or copy this code into **Arduino IDE**.

   .. raw:: html
       
       <iframe src=https://create.arduino.cc/editor/sunfounder01/ffe65b97-0ce0-4f27-841e-92b792233dd4/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


3. Code explanation
-----------------------------

The primary principle behind this project is the use of a photoresistance sensor to detect ambient light levels. Photoresistors change their resistance based on the light falling on them. This property is utilized in the sensor module to give a digital output. When the light is below the set threshold, the sensor sends a HIGH signal to the Arduino. This signal is then used to activate a relay, which can control other devices.

.. note::
    The photoresistance sensor has a potentiometer (a small adjustable knob) that sets the threshold for when it outputs HIGH vs. LOW. This threshold might need to be adjusted based on the desired light levels for switching.

1. **Setting up constants and defining pins**

   Here, we are defining the pins we will use for the relay and the sensor. We use the ``const`` keyword because these pin numbers won't change throughout the program.

   .. code-block:: arduino
   
      const int RelayPin = 6;
      const int sensorPin = 7;
   

2. **Initialization in the setup() function**

   The ``setup()`` function is executed once when the program starts. Here, we declare the ``RelayPin`` as an output since we will be sending signals to control the relay. We also start Serial communication at 9600 baud for debugging purposes.

   .. code-block:: arduino
   
      void setup() {
        // Set RelayPin as an output pin
        pinMode(RelayPin, OUTPUT);
        // Start the Serial communication for debugging
        Serial.begin(9600);
      }
   


3. **Reading Sensor and Controlling Relay**

   The ``loop()`` function is where the main logic resides. It repeatedly checks the value from the photoresistance sensor. If the sensor reads a value of 1 (indicative of light level below the threshold), the relay is turned on by setting ``RelayPin`` to HIGH. Otherwise, the relay is turned off by setting ``RelayPin`` to LOW.

   .. code-block:: arduino
   
      void loop() {
        // Read the value from the photoresistance sensor module
        const int sensorValue = digitalRead(sensorPin);
        // If the light level is lower than the threshold (sensor value equals 1),
        // switch the relay module ON.
        if (sensorValue == 1) {
          digitalWrite(RelayPin, HIGH);
        } else
        // If the light level is higher than the threshold (sensor value equal 0),
        // switch the relay module OFF.
        {
          digitalWrite(RelayPin, LOW);
        }
      }
   

