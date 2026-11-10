.. note::

    Hello, welcome to the SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasts Community on Facebook! Dive deeper into Raspberry Pi, Arduino, and ESP32 with fellow enthusiasts.

    **Why Join?**

    - **Expert Support**: Solve real-life coding problems and technical challenges with our community and team.
    - **Learn & Share**: Exchange tips, tutorials, and projects to enhance your skills.
    - **Exclusive Previews**: Get early access to new product announcements and sneak peeks.
    - **Festive Promotions and Giveaways**: Take part in giveaways and holiday promotions.

    👉 Ready to explore and create with us? Click [|link_sf_facebook|] and join today!

.. _c201_iot_Bluetooth_environmental_monitor:

10. Bluetooth Environmental Monitor
===================================

.. .. raw:: html

..    <video loop autoplay muted style = "max-width:100%">
..       <source src="../../_static/video/iot/10-iot_Bluetooth_environmental_monitor.mp4"  type="video/mp4">
..       Your browser does not support the video tag.
..    </video>

A DHT11 sensor measures the air, and the board pushes the two numbers to the phone every
two seconds. This is the **first project that sends data the other way round**: until now
the phone talked, the board listened. Here the board talks.


1. Build the Circuit
-----------------------------

.. note::

    The module draws a high current at start-up, so make sure the 9 V battery or an external power supply is plugged into the DC jack of the R4 Minima.


.. image:: ../img/10-Wiring_Bluetooth_environmental_monitor.png
   :width: 90%

* :ref:`cpn_uno`
* :ref:`cpn_espc201`
* :ref:`cpn_dht11`


2. Upload the Code
-----------------------------

#. Open the ``10-Bluetooth_environmental_monitor.ino`` file under the path of ``ultimate-sensor-kit\code\iot_project_espc201\bluetooth\10-Bluetooth_environmental_monitor``.

   .. note::

      Install the **DHT sensor library** (by Adafruit) and its dependency **Adafruit Unified
      Sensor** from the Library Manager.

#. Select **Arduino UNO R4 Minima** and the right port, then click **Upload**.

#. Open the Serial Monitor at **115200**. You should read:

   .. code-block:: text

      === ESPC2-01 Bluetooth (BLE) ===
      [OK] BLE is ready - scan for "SunFounder-C2" on your phone
      --------------------------------

      Humidity: 45.00%  Temperature: 27.00 C
      Data to send: 27.00,45.00

   If you read ``[!] no reply from the module``, the module is not answering on D0/D1 -
   check the four wires and the power supply.


#. This line is produced whether or not a phone is listening - useful, because it proves
   the sensor works before you go looking for a Bluetooth problem.

   .. code-block:: text

      Humidity: 45.00%  Temperature: 27.00 C
      Data to send: 27.00,45.00

3. Watch the Data in LightBlue
------------------------------

This time you do not write anything - you **subscribe**. Subscribing tells the phone to
keep a characteristic open and show whatever arrives.

#. Open LightBlue, tap **Scan** and connect to **SunFounder-C2**.

#. Expand the service **0xA002** and open the characteristic **C305**.

#. Tap **Subscribe**. Numbers start to appear by themselves, twice per second:

   .. image:: ../img/ble_lightblue_subs.png
      :width: 80%

   .. note::

      The format is ``temperature,humidity``. ``27.00,45.00`` means 27 degrees and 45 %
      humidity. A comma separates them so the receiving side can split the line into two
      numbers.

#. Cover the sensor with your hand - the humidity number climbs within a few seconds.

   .. note::

      If nothing arrives, check two things: that you opened **C305** (not C304), and that
      the Serial Monitor still shows ``Data to send:``. When the Serial Monitor is silent
      the problem is the sensor or its wiring, not Bluetooth.


4. Code explanation
-----------------------------

#. **Reading the sensor**

   .. code-block:: arduino

      float humidity = dht.readHumidity();
      float temperature = dht.readTemperature();

      if (isnan(humidity) || isnan(temperature)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
      }

   ``isnan`` means "is not a number". A DHT11 that is not wired properly returns exactly
   that, so the sketch stops before it sends an empty line to the phone.

#. **One line, two values**

   .. code-block:: arduino

      sensorData = String(temperature) + "," + String(humidity);
      bleSerial.println(sensorData);

   ``bleSerial.println`` writes the text and a line ending, exactly like ``Serial.println``.
   ``BLEStream`` splits it into 20-byte chunks and sends each one as a **notification on
   C305** - that is why the phone has to subscribe.

#. **The two-second rhythm**

   .. code-block:: arduino

      void loop() {
        delay(2000);
        ...
      }

   ``delay`` is allowed here because this sketch does nothing else. In the Wi-Fi projects
   we avoided it, because Blynk had to be served all the time; Bluetooth needs no such
   background work.

#. **Why the board can talk without being asked**

   A BLE notification only travels when the phone has subscribed to that characteristic.
   Nothing in the sketch checks "is anybody listening" - if nobody subscribed, the data
   simply goes nowhere. That is also why you see nothing in LightBlue until you tap
   **Subscribe**.

