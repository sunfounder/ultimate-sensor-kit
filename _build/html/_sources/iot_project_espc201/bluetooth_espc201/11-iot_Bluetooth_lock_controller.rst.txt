.. note::

    Hello, welcome to the SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasts Community on Facebook! Dive deeper into Raspberry Pi, Arduino, and ESP32 with fellow enthusiasts.

    **Why Join?**

    - **Expert Support**: Solve real-life coding problems and technical challenges with our community and team.
    - **Learn & Share**: Exchange tips, tutorials, and projects to enhance your skills.
    - **Exclusive Previews**: Get early access to new product announcements and sneak peeks.
    - **Festive Promotions and Giveaways**: Take part in giveaways and holiday promotions.

    👉 Ready to explore and create with us? Click [|link_sf_facebook|] and join today!

.. _c201_iot_Bluetooth_lock_controller:

11. Bluetooth Lock Controller
=============================

.. .. raw:: html

..    <video loop autoplay muted style = "max-width:100%">
..       <source src="../../_static/video/iot/08-iot_Bluetooth_lock_controller.mp4"  type="video/mp4">
..       Your browser does not support the video tag.
..    </video>

A servo motor stands in for the bolt of a lock. One character from the phone turns it:
``1`` locks, ``0`` unlocks.

Two states are enough for a lock, so the sketch needs no message terminator - every single
character that arrives is a complete command.


1. Build the Circuit
-----------------------------

.. note::

    The module draws a high current at start-up, so make sure the 9 V battery or an external power supply is plugged into the DC jack of the R4 Minima. A servo has its own current spike - never feed it from the 5 V pin of the board.


.. image:: ../img/08-Wiring_Bluetooth_lock_controller.png
   :width: 90%

* :ref:`cpn_uno`
* :ref:`cpn_espc201`
* :ref:`cpn_servo`


2. Upload the Code
-----------------------------

#. Open the ``11-Bluetooth_lock_controller.ino`` file under the path of ``ultimate-sensor-kit\code\iot_project_espc201\bluetooth\11-Bluetooth_lock_controller``.


#. Select **Arduino UNO R4 Minima** and the right port, then click **Upload**.

#. The Serial Monitor at **115200** shows the two Bluetooth lines, and then one line for
   every command you send:

   .. code-block:: text

      === ESPC2-01 Bluetooth (BLE) ===
      [OK] BLE is ready - scan for "SunFounder-C2" on your phone
      --------------------------------
      Locked
      Unlocked


3. Lock and Unlock from the Phone
---------------------------------

#. Open LightBlue, tap **Scan** and connect to **SunFounder-C2**.

#. Expand the service **0xA002** and open the characteristic **C304**. Then tap **Write new value**.

   .. image:: ../img/ble_lightblue_write.png
      :width: 80%

#. Set the format in the top right corner to **UTF-8 String** and type ``1``. The picture shows the field just before sending:

   .. image:: ../img/ble_lightblue_1.png
      :width: 80%

#. Send it. The servo turns to the locked position and the Serial Monitor prints
   ``Locked``.

#. Type ``0`` in the same field and send it - the servo swings back and the monitor
   prints ``Unlocked``. The picture shows the field again:

   .. image:: ../img/ble_lightblue_0.png
      :width: 80%

   .. note::

      The servo angles are ``lockAngle`` and ``unlockAngle`` at the top of the sketch.
      If your lock mechanism moves the wrong way, swap the two numbers instead of turning
      the horn by hand - that is easier to undo.


4. Code explanation
-----------------------------

#. **The servo**

   .. code-block:: arduino

      #include <Servo.h>
      Servo myservo;

      const int lockAngle = 0;
      const int unlockAngle = 90;

   ``myservo.write(angle)`` moves the horn to a position between 0 and 180 degrees and
   holds it there. It does not spin continuously - which is exactly what a lock bolt needs.

#. **Waiting for one character**

   .. code-block:: arduino

      if (bleSerial.available() > 0) {
        char message = bleSerial.read();

        if (message == '1') {
          myservo.write(lockAngle);
          Serial.println("Locked");
        } else if (message == '0') {
          myservo.write(unlockAngle);
          Serial.println("Unlocked");
        }
      }

   ``bleSerial.read()`` returns **one** character, which is why the phone must send ``1``
   and not ``Lock``. Anything that is not ``1`` or ``0`` is ignored without complaint.

   .. note::

      ``'1'`` with single quotes is a character; ``"1"`` with double quotes is a text of
      one character and the comparison would not compile.

#. **Why no terminator is needed**

   Every command here is exactly one character long, so the sketch cannot get out of step.
   In the piano and OLED projects the messages are longer, and there a terminator is
   required - look for ``*`` and ``#`` in the next chapters.
