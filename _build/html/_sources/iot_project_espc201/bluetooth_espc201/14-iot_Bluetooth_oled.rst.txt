.. note::

    Hello, welcome to the SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasts Community on Facebook! Dive deeper into Raspberry Pi, Arduino, and ESP32 with fellow enthusiasts.

    **Why Join?**

    - **Expert Support**: Solve real-life coding problems and technical challenges with our community and team.
    - **Learn & Share**: Exchange tips, tutorials, and projects to enhance your skills.
    - **Exclusive Previews**: Get early access to new product announcements and sneak peeks.
    - **Festive Promotions and Giveaways**: Take part in giveaways and holiday promotions.

    👉 Ready to explore and create with us? Click [|link_sf_facebook|] and join today!

.. _c201_iot_Bluetooth_oled:

14. Bluetooth OLED
==================

.. .. raw:: html

..    <video loop autoplay muted style = "max-width:100%">
..       <source src="../../_static/video/iot/12-iot_Bluetooth_oled.mp4"  type="video/mp4">
..       Your browser does not support the video tag.
..    </video>

Type on the phone, read it on a 128 x 64 OLED display. This project is close to the LCD
one, but the display is smaller and the sketch has to guess when a sentence is finished -
the phone sends characters one after another, not as one block.


1. Build the Circuit
-----------------------------

.. note::

    The module draws a high current at start-up, so make sure the 9 V battery or an external power supply is plugged into the DC jack of the R4 Minima.


.. image:: ../img/12-Wiring_oled.png
   :width: 90%

* :ref:`cpn_uno`
* :ref:`cpn_espc201`
* :ref:`cpn_olde`


2. Upload the Code
-----------------------------

#. Open the ``14-Bluetooth_oled.ino`` file under the path of ``ultimate-sensor-kit\code\iot_project_espc201\bluetooth\14-Bluetooth_oled``.

   .. note::

      Install **Adafruit SSD1306** and **Adafruit GFX Library** from the Library Manager.

#. Select **Arduino UNO R4 Minima** and the right port, then click **Upload**.

#. Open the Serial Monitor at **115200**. You should read:

   .. code-block:: text

      === ESPC2-01 Bluetooth (BLE) ===
      [OK] BLE is ready - scan for "SunFounder-C2" on your phone
      --------------------------------

   If you read ``[!] no reply from the module``, the module is not answering on D0/D1 -
   check the four wires and the power supply.

3. Send Text from the Phone
------------------------------

#. Open LightBlue, tap **Scan** and connect to **SunFounder-C2**.

#. Expand the service **0xA002** and open the characteristic **C304**. Then tap **Write new value**.

   .. image:: ../img/ble_lightblue_write.png
      :width: 80%

#. Set the format in the top right corner to **UTF-8 String** and type ``Hello``. The picture shows the field just before sending:

   .. image:: ../img/ble_lightblue_hello.png
      :width: 80%

#. Send it. The word appears on the OLED and in the Serial Monitor.

#. Send another word - it replaces the first one, the display does not scroll.

   .. note::

      Two rules decide when the message is complete: either you end it with ``#``, or you
      simply stop typing. The sketch waits **120 ms** of silence and then treats what it
      has as one message.

      The display is 21 characters wide and 4 lines high. Longer text is cut off.


4. Code explanation
-----------------------------

#. **The display**

   .. code-block:: arduino

      display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 0);
      display.print(message);
      display.display();

   ``0x3C`` is the I2C address of the module. Nothing shows up until ``display.display()``
   is called - the sketch writes into a buffer first and pushes the buffer to the screen
   in one go.

#. **Deciding when the text is finished**

   .. code-block:: arduino

      if (c == '#' || c == '\r' || c == '\n') {
        showMessage();
        continue;
      }
      message += c;
      lastByte = millis();

   A ``#`` finishes the message at once. A line ending does the same, because some apps
   add one automatically.

#. **The 120 ms rule**

   .. code-block:: arduino

      if (message.length() > 0 && millis() - lastByte > 120) {
        showMessage();
      }

   BLE sends the characters of one write in a burst, with almost no gap. When the burst
   stops, 120 ms pass and the sketch shows what it has. This makes typing on the phone
   feel natural without pressing anything.

#. **Clearing afterwards**

   .. code-block:: arduino

      message = "";

   Without this the next word would be appended to the old one and the display would grow
   longer and longer until it is cut off.
