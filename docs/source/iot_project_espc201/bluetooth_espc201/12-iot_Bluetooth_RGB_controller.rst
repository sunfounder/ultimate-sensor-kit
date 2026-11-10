.. note::

    Hello, welcome to the SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasts Community on Facebook! Dive deeper into Raspberry Pi, Arduino, and ESP32 with fellow enthusiasts.

    **Why Join?**

    - **Expert Support**: Solve real-life coding problems and technical challenges with our community and team.
    - **Learn & Share**: Exchange tips, tutorials, and projects to enhance your skills.
    - **Exclusive Previews**: Get early access to new product announcements and sneak peeks.
    - **Festive Promotions and Giveaways**: Take part in giveaways and holiday promotions.

    👉 Ready to explore and create with us? Click [|link_sf_facebook|] and join today!

.. _c201_iot_Bluetooth_RGB_controller:

12. Bluetooth RGB Controller
============================

.. .. raw:: html

..    <video loop autoplay muted style = "max-width:100%">
..       <source src="../../_static/video/iot/09-iot_Bluetooth_RGB_controller.mp4"  type="video/mp4">
..       Your browser does not support the video tag.
..    </video>

One message carries three numbers: how much red, how much green, how much blue. Send
``R255G128B0`` and the LED turns orange.

This is the first **structured** message in the Bluetooth part - the sketch has to split it
into three parts before it can use it, a small job you will meet everywhere.


1. Build the Circuit
-----------------------------

.. note::

    The module draws a high current at start-up, so make sure the 9 V battery or an external power supply is plugged into the DC jack of the R4 Minima.


.. image:: ../img/09-Wiring_Bluetooth_rgb_controller.png
   :width: 90%

* :ref:`cpn_uno`
* :ref:`cpn_espc201`
* :ref:`cpn_rgb`


2. Upload the Code
-----------------------------

#. Open the ``12-Bluetooth_RGB_controller.ino`` file under the path of ``ultimate-sensor-kit\code\iot_project_espc201\bluetooth\12-Bluetooth_RGB_controller``.

#. Select **Arduino UNO R4 Minima** and the right port, then click **Upload**.

#. Open the Serial Monitor at **115200**. You should read:

   .. code-block:: text

      === ESPC2-01 Bluetooth (BLE) ===
      [OK] BLE is ready - scan for "SunFounder-C2" on your phone
      --------------------------------

   If you read ``[!] no reply from the module``, the module is not answering on D0/D1 -
   check the four wires and the power supply.


3. Change the Colour from the Phone
-----------------------------------

#. Open LightBlue, tap **Scan** and connect to **SunFounder-C2**.

#. Expand the service **0xA002** and open the characteristic **C304**. Then tap **Write new value**.

   .. image:: ../img/ble_lightblue_write.png
      :width: 80%

#. Set the format in the top right corner to **UTF-8 String** and type ``R255G128B0``. The picture shows the field just before sending:

   .. image:: ../img/ble_lightblue_rgb.png
      :width: 80%

#. Send it. The LED turns orange and the Serial Monitor prints ``colour: R255G128B0``.

   .. note::

      The sketch does not react to every single character. A BLE write can be split into
      several pieces on its way, so the sketch waits until the message is complete - a
      ``#`` at the end, or **120 ms** of silence - and only then sets the colour. If it
      acted on each piece, the LED would flash through the wrong colours on every send.

#. Try a few more - the field stays open, so you can send again right away:

   .. list-table::
      :header-rows: 1
      :widths: 30 70

      * - Send this
        - What happens
      * - ``R255G0B0``
        - red
      * - ``R0G255B0``
        - green
      * - ``R0G0B255``
        - blue
      * - ``R255G255B255``
        - white, all three channels at full
      * - ``R0G0B0``
        - off

   .. note::

      The numbers are **0 to 255**, not percentages. ``R128G0B0`` is a darker red than
      ``R255G0B0``, because the pin is switched on for only half of the time.

      The whole message has to stay under **12 characters**, which is why there are no
      separators.


4. Code explanation
-----------------------------

#. **Three pins, one colour**

   .. code-block:: arduino

      const int redPin = 9;
      const int greenPin = 10;
      const int bluePin = 11;

   ``analogWrite(pin, 0..255)`` uses PWM, so the LED can show many colours - not just the
   three primary ones.

#. **Splitting the message**

   .. code-block:: arduino

      if (r_char == 'R') { currentColor = 'R'; redTempValue = ""; }
      else if (r_char == 'G') { currentColor = 'G'; greenTempValue = ""; }
      else if (r_char == 'B') { currentColor = 'B'; blueTempValue = ""; }

      if (currentColor == 'R' && r_char != 'R') redTempValue += r_char;

   The letter **R**, **G** or **B** marks where a number starts. Every character after a
   marker is added to that colour until the next marker arrives. That is why the order
   ``R...G...B...`` matters and why no brackets are needed.

#. **From text to number**

   .. code-block:: arduino

      analogWrite(redPin,   redTempValue.toInt());
      analogWrite(greenPin, greenTempValue.toInt());
      analogWrite(bluePin,  blueTempValue.toInt());

   ``toInt()`` converts the text ``"255"`` into the number 255. Forgetting it is a classic
   mistake - ``analogWrite`` would then act on garbage.

#. **The 12 character limit**

   .. code-block:: arduino

      #define max_char 12

   One BLE write carries at most 20 bytes and this sketch keeps a little headroom.
   ``R255G255B255`` is 12 characters - the longest useful message.
