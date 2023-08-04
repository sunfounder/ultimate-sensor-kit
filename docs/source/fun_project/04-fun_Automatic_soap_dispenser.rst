.. _fun_soap_dispenser:

Automatic soap dispenser
==========================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="/_static/video/fun/04-fun_Automatic_soap_dispenser.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>

The Automatic Soap Dispenser project uses an Arduino Uno board along with an infrared obstacle avoidance sensor and a water pump. The sensor detects the presence of an object such as a hand, which activates the water pump to dispense soap.


1. Build the Cirduit
-----------------------------

.. image:: img/04-fun_Automatic_soap_dispenser_circuit.png
    :width: 90%

* :ref:`cpn_uno`
* :ref:`cpn_ir_obstacle`
* :ref:`cpn_pump`


2. Code
-----------------------------

#. Open the ``04-Automatic_soap_dispenser.ino`` file under the path of ``iot-sensor-kit\fun_project\04-Automatic_soap_dispenser``, or copy this code into **Arduino IDE**.

   .. raw:: html
       
       <iframe src=https://create.arduino.cc/editor/sunfounder01/0ee4125a-39fe-4493-bbe6-8bef68721896/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


3. Code explanation
-----------------------------

The main idea behind this project is to create a hands-free soap dispensing system. The infrared obstacle avoidance sensor detects when an object (like a hand) is close. Upon detecting an object, the sensor sends a signal to the Arduino, which in turn triggers the water pump to dispense soap. The pump stays active for a brief period, dispensing soap, then turns off.

#. **Defining the pins for the sensor and the pump**

   In this code snippet, we define the Arduino pins that connect to the sensor and pump. We define pin 7 as the sensor pin and we will use the variable ``sensorValue`` to store the data read from this sensor. For the water pump, we use two pins, 9 and 10.
   
   .. code-block:: arduino
   
      const int sensorPin = 7;
      int sensorValue;
      const int pump1A = 9;
      const int pump1B = 10;

#. **Setting up the sensor and pump**

   In the ``setup()`` function, we define the modes for the pins we're using. The sensor pin is set to ``INPUT`` as it will be used to receive data from the sensor. The pump pins are set to ``OUTPUT`` as they will send commands to the pump. We ensure that the pin ``pump1B`` starts in a ``LOW`` state (off), and we start the serial communication with a baud rate of 9600.

   .. code-block:: arduino
   
      void setup() {
        pinMode(sensorPin, INPUT);
        pinMode(pump1A, OUTPUT);    
        pinMode(pump1B, OUTPUT);    
        digitalWrite(pump1B, LOW);  
        Serial.begin(9600);
      }

#. **Continuously checking the sensor and controlling the pump**

   In the ``loop()`` function, the Arduino constantly reads the value from the sensor using ``digitalRead()`` and assigns it to ``sensorValue()``. It then prints this value to the serial monitor for debugging purposes. If the sensor detects an object, ``sensorValue()`` will be 0. When this happens, ``pump1A`` is set to ``HIGH``, activating the pump, and a delay of 700 milliseconds allows the pump to dispense soap. The pump is then deactivated by setting ``pump1A`` to ``LOW``, and a 1-second delay gives the user time to move their hand away before the cycle repeats.

   .. code-block:: arduino
   
      void loop() {
        sensorValue = digitalRead(sensorPin);
        Serial.println(sensorValue);
        if (sensorValue == 0) {  
          digitalWrite(pump1A, HIGH);
          delay(700);
          digitalWrite(pump1A, LOW);
          delay(1000);
        }
      }
