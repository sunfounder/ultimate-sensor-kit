.. _cpn_speed:

Infrared Speed Sensor Module (LM393)
=====================================

.. image:: img/18_LM393_module.png
    :width: 300
    :align: center

Introduction
---------------------------
The LM393 module is an IR counter that has an IR transmitter and receiver. If any obstacle is placed between these sensors, a signal is sent to the microcontroller. The module can be used in association with a microcontroller for motor speed detection, pulse count, position limit, etc.


Principle
---------------------------
The LM393 module has 1 H2010 photocell, which consists of a phototransistor and an infrared light emitter packaged in a 10 cm wide black plastic housing.

.. image:: img/18_LM393_module_2.png
    :width: 200
    :align: center

When operating, the infrared light-emitting diode continuously emits infrared light (invisible light), and the photosensitive triode will conduct if it receives it.

.. image:: img/18_LM393_module_3.png
    :width: 900
    :align: center


Usage
---------------------------

**Hardware components**

- Arduino Uno R4 or R3 board * 1
- Infrared Speed Sensor Module * 1
- Jumper Wires


**Circuit Assembly**

.. image:: img/18_LM393_module_circuit.png
    :width: 600
    :align: center

.. raw:: html
    
    <br/><br/>   

Code
^^^^^^^^^^^^^^^^^^^^

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/abcd3502-1ea8-49e5-8254-5652448f06b1/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/18-component_speed.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>
   <br/><br/>  

Code explanation
^^^^^^^^^^^^^^^^^^^^

#. Setting up the pins and initializing variables. Here, we define the pins for the motor and the speed sensor. We also initialize variables that will be used to measure and calculate the speed of the motor.

   .. code-block:: arduino

      // Define the sensor and motor pins
      const int sensorPin = 11;
      const int motorB_1A = 9;
      const int motorB_2A = 10;
      
      // Define variables for measuring speed
      unsigned long start_time = 0;
      unsigned long end_time = 0;
      int steps = 0;
      float steps_old = 0;
      float temp = 0;
      float rps = 0;

#. Initialization in the ``setup()`` function. This section sets up the serial communication, configures the pins' modes, and sets the initial motor speed.

   .. code-block:: arduino

      void setup() {
        Serial.begin(9600);
        pinMode(sensorPin, INPUT);
        pinMode(motorB_1A, OUTPUT);
        pinMode(motorB_2A, OUTPUT);
        analogWrite(motorB_1A, 160);
        analogWrite(motorB_2A, 0);
      }

#. Measuring the motor's speed in the ``loop()`` function. In this segment, the motor's steps are measured for a duration of 1 second. These steps are then used to calculate the revolutions per second (rps), which is then printed to the serial monitor.

   ``millis()`` returns the number of milliseconds passed since the Arduino board began running the current program. 

   .. code-block:: arduino

      void loop() {
        start_time = millis();
        end_time = start_time + 1000;
        while (millis() < end_time) {
          if (digitalRead(sensorPin)) {
            steps = steps + 1;
            while (digitalRead(sensorPin))
              ;
          }
        }
        temp = steps - steps_old;
        steps_old = steps;
        rps = (temp / 20);
        Serial.print("rps:");
        Serial.println(rps);
      }

Additional Ideas
^^^^^^^^^^^^^^^^^^^^

- Display the rps on an LCD screen for a more user-friendly interface.

