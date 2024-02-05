
.. _iot_Bluetooth_traffic_light:

Bluetooth Traffic Light
=============================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/iot/16-iot_Bluetooth_traffic_light.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>

This project is designed to control a traffic light (Red, Yellow, Green LEDs) using Bluetooth communication. The user can send a character ('R', 'Y', or 'G') from a Bluetooth device. When the Arduino receives one of these characters, it lights up the corresponding LED, while ensuring the other two LEDs are turned off.


1. Build the Circuit
-----------------------------

.. image:: img/16-Wiring_Bluetooth_traffic_light.png
    :width: 80%

* :ref:`cpn_uno`
* :ref:`cpn_jdy31`
* :ref:`cpn_traffic`

2. Upload the Code
-----------------------------

#. Open the ``02-Bluetooth_traffic_light.ino`` file under the path of ``ultimate-sensor-kit\iot_project\bluetooth\02-Bluetooth_traffic_light``, or copy this code into **Arduino IDE**.

   .. raw:: html
       
       <iframe src=https://create.arduino.cc/editor/sunfounder01/e004fd36-1294-453e-b6fd-2bc7fc9410e8/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

#. After selecting the correct board and port, click the **Upload** button.

#. Open the Serial monitor(set baudrate to **9600**) to view debug messages. 

3. App and Bluetooth module Connection
-----------------------------------------------
We can use an app called "Serial Bluetooth Terminal" to send messages from the Bluetooth module to Arduino.

a. **Install Serial Bluetooth Terminal**

   Go to Google Play to download and install |link_serial_bluetooth_terminal| .


b. **Connect Bluetooth**

   Initially, turn on **Bluetooth** on your smartphone.
   
      .. image:: img/new/09-app_1_shadow.png
         :width: 60%
         :align: center
   
   Navigate to the **Bluetooth settings** on your smartphone and look for names like **JDY-31-SPP**.
   
      .. image:: img/new/09-app_2_shadow.png
         :width: 60%
         :align: center
   
   After clicking it, agree to the **Pair** request in the pop-up window. If prompted for a pairing code, please enter "1234".
   
      .. image:: img/new/09-app_3_shadow.png
         :width: 60%
         :align: center
   

c. **Communicate with Bluetooth module**

   Open the Serial Bluetooth Terminal. Connect to "JDY-31-SPP".

   .. image:: img/new/00-bluetooth_serial_4_shadow.png 

d. **Send command**

   Use the Serial Bluetooth Terminal app to send commands to Arduino via Bluetooth. Send R to turn on the red light, Y for yellow, and G for green.

   .. image:: img/new/16-R_shadow.png 
      :width: 85%
      :align: center

   .. image:: img/new/16-Y_shadow.png 
      :width: 85%
      :align: center

   .. image:: img/new/16-G_shadow.png 
      :width: 85%
      :align: center


4. Code explanation
-----------------------------------------------

#. Initialization and Bluetooth setup

   .. code-block:: arduino

      // Set up Bluetooth module communication
      #include <SoftwareSerial.h>
      const int bluetoothTx = 3;
      const int bluetoothRx = 4;
      SoftwareSerial bleSerial(bluetoothTx, bluetoothRx);
   
   We begin by including the SoftwareSerial library to help us with Bluetooth communication. The Bluetooth module's TX and RX pins are then defined and associated with pins 3 and 4 on the Arduino. Finally, we initialize the ``bleSerial`` object for Bluetooth communication.

#. LED Pin Definitions

   .. code-block:: arduino

      // Pin numbers for each LED
      const int rledPin = 10;  //red
      const int yledPin = 11;  //yellow
      const int gledPin = 12;  //green

   Here, we're defining which Arduino pins our LEDs are connected to. The red LED is on pin 10, yellow on 11, and green on 12.

#. setup() Function

   .. code-block:: arduino

      void setup() {
         pinMode(rledPin, OUTPUT);
         pinMode(yledPin, OUTPUT);
         pinMode(gledPin, OUTPUT);

         Serial.begin(9600);
         bleSerial.begin(9600);
      }

   In the ``setup()`` function, we set the LED pins as ``OUTPUT``. We also start serial communication for both the Bluetooth module and the default serial (connected to the computer) at a baud rate of 9600.

#. Main loop() for Bluetooth Communication

   .. code-block:: arduino

      void loop() {
         while (bleSerial.available() > 0) {
            character = bleSerial.read();
            Serial.println(character);

            if (character == 'R') {
               toggleLights(rledPin);
            } else if (character == 'Y') {
               toggleLights(yledPin);
            } else if (character == 'G') {
               toggleLights(gledPin);
            }
         }
      }

   Inside our main ``loop()``, we continuously check if data is available from the Bluetooth module. If we receive data, we read the character and display it in the serial monitor. Depending on the character received (R, Y, or G), we toggle the respective LED using the ``toggleLights()`` function.

#. Toggle Lights Function

   .. code-block:: arduino

      void toggleLights(int targetLight) {
         digitalWrite(rledPin, LOW);
         digitalWrite(yledPin, LOW);
         digitalWrite(gledPin, LOW);

         digitalWrite(targetLight, HIGH);
      }

   This function, ``toggleLights()``, turns off all the LEDs first. After ensuring they are all off, it turns on the specified target LED. This ensures that only one LED is on at a time.