
.. note::

    Hello, welcome to the SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasts Community on Facebook! Dive deeper into Raspberry Pi, Arduino, and ESP32 with fellow enthusiasts.

    **Why Join?**

    - **Expert Support**: Solve post-sale issues and technical challenges with help from our community and team.
    - **Learn & Share**: Exchange tips and tutorials to enhance your skills.
    - **Exclusive Previews**: Get early access to new product announcements and sneak peeks.
    - **Special Discounts**: Enjoy exclusive discounts on our newest products.
    - **Festive Promotions and Giveaways**: Take part in giveaways and holiday promotions.

    👉 Ready to explore and create with us? Click [|link_sf_facebook|] and join today!

.. _c201_iot_Remote_relay_controller:

6. Remote Relay Controller with Blynk
===============================================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../../_static/video/iot/06-iot_Remote_relay_controller.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>

This project aims to create a remote relay controller that can be operated through a virtual switch in the Blynk app. When the switch is turned on, it sets the digital pin connected to the relay to HIGH, and when it's turned off, it sets the digital pin to LOW. This allows for easy control of the relay from a distance, effectively creating a remote switch.

1. Build the Circuit
-----------------------------

.. warning ::
    The following example demonstrates using a relay to control an LED module. 
    **While you can connect the relay to other appliances in actual applications, extreme caution is required when dealing with HIGH AC voltage. Improper or incorrect use can lead to severe injury or even death. Therefore, it is intended for people who are familiar with and knowledgeable about HIGH AC voltage. Always prioritize safety.**

.. note::

    The module draws a high current at start-up, so make sure the 9 V battery or an external power supply is plugged into the DC jack of the R4 Minima.


.. image:: ../img/06-Wiring_Remote_relay_controller_c201.png
   :width: 80%


* :ref:`cpn_uno`
* :ref:`cpn_espc201`
* :ref:`cpn_relay`
* :ref:`cpn_traffic`


2. Configure Blynk
-----------------------------

.. note::

    The template and the device were created once in :ref:`c201_iot_blynk_start`.
    Every project adds its datastreams to that **same** template, so each project
    occupies its own range of virtual pins. This project uses **V7**.

**What this project sends to the cloud**

One integer, ``relay_status``. It is not a sensor reading: it mirrors the state of the
relay, so the app and the board always agree on whether the relay is on.

**Add the datastream**

#. Open **Developer Zone** -> **My Templates**, click **Ultimate Sensor Kit**.

   .. image:: ../img/blynk_template.png
      :width: 80%

#. Click **Edit** to open the template.

   .. image:: ../img/blynk_edit.png
      :width: 80%

#. Click **Datastreams**, then **Create New**.

   .. image:: ../img/blynk_new_data.png
      :width: 80%

#. Fill in the form:

   * **DATASTREAM NAME**: ``relay_status``
   * **DISPLAY NAME**: ``Relay Status``
   * **VIRTUAL PIN**: ``V7``
   * **DATA TYPE**: **Integer**
   * **MIN** ``0``, **MAX** ``1``

   .. image:: ../img/blynk_relay_data.png
      :width: 80%

**Add the web dashboard**

#. Click **Dashboard**, then **Add Widget**.

   .. image:: ../img/blynk_dashboard.png
      :width: 80%

#. Drag a **Switch** widget onto the dashboard.

   .. image:: ../img/blynk_dashboard_switch.png
      :width: 80%

#. Click the three dots in the corner of the **Switch** and choose **Settings**. 

   * Set **Datastream** to ``Relay Status (V7)``.

   .. note::

      A **Switch** both shows and sets the value. Tapping it sends ``1`` or ``0`` to the
      board; the board switches the relay and writes the same value back, so the switch
      never gets out of step - even if you tap it twice quickly.

   .. image:: ../img/blynk_relay_widget.png
      :width: 80%

   
#. Click **Save**.

   .. image:: ../img/blynk_save.png
      :width: 40%


3. Run the Code
-----------------------------

#. Open the ``06-Remote_relay_controller.ino`` file under the path of ``ultimate-sensor-kit\code\iot_project_espc201\wifi\06-Remote_relay_controller``, or copy this code into **Arduino IDE**.

#. The three Blynk lines were copied in the Get Started chapter. Every project of this
   kit uses the same device, so they never have to be changed - only the Wi-Fi settings
   below are project specific.

   .. code-block:: arduino

      #define BLYNK_TEMPLATE_ID   "TMPLxxxxxx"
      #define BLYNK_TEMPLATE_NAME "Ultimate Sensor Kit"
      #define BLYNK_AUTH_TOKEN    "YourAuthToken"

#. Type the name and the password of your own Wi-Fi network.

   .. code-block:: arduino

      char ssid[] = "your_ssid";
      char pass[] = "your_password";

#. Select **Arduino UNO R4 Minima** and the right port, then click **Upload**.

#. Open the Serial Monitor at **115200**. When the board reaches the cloud the log ends
   with ``Ready``, and every time you move the switch in the app a line appears here:

   .. code-block:: text

      [28358] Ready (ping: 285ms).
      The switch on Blynk has been turned on.
      The switch on Blynk has been turned off.

   That echo is the quickest way to see that the app and the board are really talking.

   .. image:: ../img/blynk_relay_serial.png
      :width: 80%

#. Tap the switch: the relay clicks. Tap it again: it clicks back.

   .. note::

      The relay keeps its position after a power cut. When the board reconnects it asks the
      server for the last value (``Blynk.syncVirtual(V7)``), so the relay returns to the
      state you left it in instead of always starting switched off.

   .. image:: ../img/blynk_relay_dashbaord.png
      :width: 80%


4. Code explanation
-----------------------------

#. **Blynk account and libraries**

   The first three lines say which Blynk device this board belongs to. They come from the
   device page and are identical in every project of this kit.

   .. code-block:: arduino

      #define BLYNK_TEMPLATE_ID   "TMPL2Ms3WVki8"
      #define BLYNK_TEMPLATE_NAME "Ultimate Sensor Kit"
      #define BLYNK_AUTH_TOKEN    "lHSd4Q5pXP7YKUovVfPZYZqC0UHVORY6"

      #define BLYNK_PRINT Serial   // show Blynk's own log on the Serial Monitor

      #include <ESP8266_Lib.h>               // sends the AT commands
      #include <BlynkSimpleShieldEsp8266.h>  // Blynk on top of them

#. **The serial port that talks to the module**

   The ESPC2-01 works as a modem: the sketch sends it AT commands. On the R4 it is wired
   to D0/D1, which is ``Serial1``, a hardware port, so 115200 works without bit errors.

   .. code-block:: arduino

      #define EspSerial Serial1
      #define ESP8266_BAUD 115200
      ESP8266 wifi(&EspSerial);

   The function ``espModuleInit()`` waits for the module to finish booting and then sends
   ``ATE0`` to switch the echo off. Without it, the module's start-up log and the echoed
   commands get mixed into the replies and Blynk cannot read them.

#. **The relay pin**

   .. code-block:: arduino

      const int RelayPin = 6;
      int switchStatus = 0;

   ``RelayPin`` is the pin that drives the relay module - D6 here. ``switchStatus`` simply
   keeps the last value the app sent, so the code can tell "on" from "off" in one place.

   .. note::

      Some relay modules switch the other way round and close when the pin is **LOW**.
      If your relay clicks the opposite way to the switch in the app, swap ``HIGH`` and
      ``LOW`` in the function below - nothing else changes.

#. **setup()**

   .. code-block:: arduino

      void setup() {
        pinMode(RelayPin, OUTPUT);
        digitalWrite(RelayPin, LOW);

        Serial.begin(115200);
        EspSerial.begin(ESP8266_BAUD);
        delay(10);

        espModuleInit();
        Blynk.config(wifi, BLYNK_AUTH_TOKEN);
        Blynk.connectWiFi(ssid, pass);
      }

   ``digitalWrite(RelayPin, LOW)`` right after ``pinMode`` matters: a pin that has just
   become an output could otherwise start HIGH for a moment and make the relay click at
   every power-up.

#. **loop()**

   .. code-block:: arduino

      void loop() {
        Blynk.run();
        timer.run();
      }

   ``Blynk.run()`` keeps the connection alive. This project has nothing to measure, so the
   loop does no other work - but it still has to run as fast as possible.

#. **BLYNK_CONNECTED() - restore the last state**

   .. code-block:: arduino

      BLYNK_CONNECTED() {
        Blynk.syncVirtual(V7);
      }

   This runs every time the board reaches the server, including after a power cut.
   ``Blynk.syncVirtual(V7)`` asks for the stored value of the switch, and the server answers
   by calling ``BLYNK_WRITE(V7)`` - so the relay ends up in the state you left it in.

#. **BLYNK_WRITE(V7) - the switch does the work**

   .. code-block:: arduino

      BLYNK_WRITE(V7) {
        switchStatus = param.asInt();

        if (switchStatus == 1) {
          Serial.println("The switch on Blynk has been turned on.");
          digitalWrite(RelayPin, HIGH);
        } else {
          Serial.println("The switch on Blynk has been turned off.");
          digitalWrite(RelayPin, LOW);
        }
      }

   * ``BLYNK_WRITE(V7)`` runs by itself whenever datastream **V7** changes - you never call
     it from ``loop()``.
   * ``param.asInt()`` is the new value: ``1`` when the switch is on, ``0`` when it is off.
   * The ``Serial.println`` lines are only there for you; they let you watch the switch from
     the Serial Monitor.
