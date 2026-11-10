.. note::

    Hello, welcome to the SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasts Community on Facebook! Dive deeper into Raspberry Pi, Arduino, and ESP32 with fellow enthusiasts.

    **Why Join?**

    - **Expert Support**: Solve real-life coding problems and technical challenges with our community and team.
    - **Learn & Share**: Exchange tips, tutorials, and projects to enhance your skills.
    - **Exclusive Previews**: Get early access to new product announcements and sneak peeks.
    - **Festive Promotions and Giveaways**: Take part in giveaways and holiday promotions.

    👉 Ready to explore and create with us? Click [|link_sf_facebook|] and join today!


.. _c201_install_libs:

1.2 Install Libraries
=====================

The sketches need **two** libraries. One comes from the Arduino Library Manager, the
other one has to be downloaded and added by hand.

**Install the Blynk library**

#. In the Arduino IDE open **Library Manager**, search for ``blynk`` and click
   **INSTALL**.

   .. image:: ../img/blynk26_11_library.png
      :width: 80%

#. The installer also asks for **BlynkNcpDriver** - choose **INSTALL ALL**.

   .. image:: ../img/blynk_lib_blynk.png
      :width: 60%

.. note::

   The library is called **BlynkESP8266** and defines ``ESP8266 wifi;`` - those names are
   historical, they come from the module Blynk was written for years ago. They work
   exactly the same with the ESPC2-01, which also answers the AT commands.

**Install the BlynkESP8266 library**

This one is not in the Library Manager, so it has to be downloaded from GitHub.

#. Download `BlynkESP8266 <https://github.com/vshymanskyy/BlynkESP8266/archive/refs/heads/master.zip>`_.

#. In the Arduino IDE choose **Sketch -> Include Library -> Add .ZIP Library...**

   .. image:: ../img/blynk_add_zip_lib.png
      :width: 80%

#. Select the downloaded zip file - there is no need to unzip it first.

   .. image:: ../img/blynk_choose_zip.png
      :width: 80%

#. Restart the Arduino IDE after the library has been added.

.. note::

    This library uses the old 1.0 layout, so the IDE may report that it cannot read a
    version number. The warning can be ignored - the sketches compile and upload without
    problems.

