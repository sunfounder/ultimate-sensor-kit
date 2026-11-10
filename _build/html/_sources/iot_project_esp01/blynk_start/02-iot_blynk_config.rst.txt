.. note::

    Hello, welcome to the SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasts Community on Facebook! Dive deeper into Raspberry Pi, Arduino, and ESP32 with fellow enthusiasts.

    **Why Join?**

    - **Expert Support**: Solve post-sale issues and technical challenges with help from our community and team.
    - **Learn & Share**: Exchange tips and tutorials to enhance your skills.
    - **Exclusive Previews**: Enjoy exclusive access to new product announcements and sneak peeks.
    - **Special Discounts**: Enjoy discounts on our newest products.
    - **Festive Promotions and Giveaways**: Take part in giveaways and holiday promotions.

    👉 Ready to explore and create with us? Click [|link_sf_facebook|] and join today!



1.1 Configuring the Blynk
==============================

In this chapter we create a Blynk account, a template and a device, and then copy the
three lines that go at the top of every project sketch.

.. note::

    The Blynk.Console interface is updated from time to time. The screenshots below
    were taken in 2026. If a button has moved, look for the **field name** (such as
    `AUTH TOKEN`) instead of the exact button position.

1. Create an account
--------------------

#. Go to `BLYNK <https://blynk.io/>`_ and click **Sign Up** in the upper right corner.

   .. image:: img/blynk26_01_signup.png
      :width: 80%
      :align: center

   .. raw:: html

      <br/>

#. Enter your email address, tick the agreement box and click **Sign Up**.

   .. image:: img/blynk26_02_email.png
      :width: 80%
      :align: center

   .. raw:: html

      <br/>

#. Open the activation link in your mailbox, then create a password.

   .. image:: img/blynk26_03_password.png
      :width: 55%
      :align: center

   .. raw:: html

      <br/>

2. Enable Developer Mode
------------------------

Blynk has to know that you are the person **building** the device and not the end
user. Only a user in **Developer Mode** can create templates, dashboards and devices,
which is everything this kit needs.

#. Click **My Profile** in the upper right corner of the Blynk.Console.

#. Make sure the **Developer Mode** switch is set to **ON**.

   The first account of an organization is a developer by default, but on some
   accounts the switch has to be turned on by hand.

.. note::

   If the sidebar has no **Developer Zone** and no **+ New Template** button, the
   **Developer Mode** switch is still off. Turn it on and the menu items appear -
   no need to sign out or create another account.

.. tip::

   **Developer Mode** is a setting of your account, not a paid feature. The free plan
   already allows it. What the free plan limits is the number of devices and the
   number of messages per day, so for a classroom it is usually enough to create one
   template and reuse it for every board.

3. Create a template
--------------------

#. After signing in you will see the **Blynk.Console**. Open **Developer Zone** in the
   left sidebar, then **My Templates**, and click **+ New Template**.

   .. image:: img/blynk26_04_console.png
      :width: 85%
      :align: center

   .. image:: img/blynk26_05_templates.png
      :width: 85%
      :align: center

   .. raw:: html

      <br/>

#. Fill in the template form:

   * **NAME**: `Ultimate Sensor`
   * **HARDWARE**: **ESP32**
   * **CONNECTION TYPE**: **WiFi**

   .. image:: img/blynk26_06_template_form.png
      :width: 60%
      :align: center

   .. note::

      **HARDWARE** is only a label that Blynk uses to suggest example code. Both
      **ESP32** and **ESP8266** work with the projects in this kit; the screenshot
      above uses **ESP32**.

   Click **Done** when finished.

   .. raw:: html

      <br/>

4. Create a device
------------------

A template on its own has **no** auth token - a device has. Every device you create
gets its own token.

#. In the left sidebar click **Devices**, then **+ New Device**.

   .. image:: img/blynk26_07_devices.png
      :width: 85%
      :align: center

   .. raw:: html

      <br/>

#. Choose **Create New**.

   .. image:: img/blynk26_08_new_device.png
      :width: 85%
      :align: center

   .. raw:: html

      <br/>

#. Select the template you just created, give the device a name, and click **Create**.

   .. image:: img/blynk26_09_device_form.png
      :width: 70%
      :align: center

   .. raw:: html

      <br/>

#. A **New Device Created!** window pops up with the three lines you need.

   .. image:: img/blynk26_10_token.png
      :width: 85%
      :align: center

   .. note::

      If you close that window, the same information is always available in
      **Devices** -> your device -> **Developer Tools**.

   .. raw:: html

      <br/>

5. Put them at the top of the sketch
------------------------------------

.. code-block:: cpp

    #define BLYNK_TEMPLATE_ID   "TMPL..."
    #define BLYNK_TEMPLATE_NAME "Ultimate Sensor"
    #define BLYNK_AUTH_TOKEN    "..."

.. warning::

    Copy them **exactly**. A single wrong character and the board will never connect.

6. Install the Blynk library
----------------------------

#. In the Arduino IDE open **Library Manager**, search for `blynk` and install
   **Blynk 1.4.0**.

   .. image:: img/blynk26_11_library.png
      :width: 80%
      :align: center

.. important::

    The sketches in this kit use `BlynkSimpleShieldEsp8266`, which needs a **second**
    library called **BlynkESP8266** (it provides `ESP8266_Lib.h`). It is **not** in
    Library Manager and has to be installed manually:

    1. Open https://github.com/vshymanskyy/BlynkESP8266
    2. Click **Code -> Download ZIP**
    3. In the Arduino IDE choose **Sketch -> Include Library -> Add .ZIP Library**
    4. Restart the IDE

    See :doc:`03-iot_add_lib` for more details.

