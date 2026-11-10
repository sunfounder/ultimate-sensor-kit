.. note::

    Hello, welcome to the SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasts Community on Facebook! Dive deeper into Raspberry Pi, Arduino, and ESP32 with fellow enthusiasts.

    **Why Join?**

    - **Expert Support**: Solve real-life coding problems and technical challenges with our community and team.
    - **Learn & Share**: Exchange tips, tutorials, and projects to enhance your skills.
    - **Exclusive Previews**: Get early access to new product announcements and sneak peeks.
    - **Festive Promotions and Giveaways**: Take part in giveaways and holiday promotions.

    👉 Ready to explore and create with us? Click [|link_sf_facebook|] and join today!


.. _c201_connect_blynk:

1.3 Connecting the R4 board to Blynk
====================================

#. Connect the ESPC2-01 module to the Arduino Uno R4 Minima.

   .. note::

      The module draws a high current at start-up, so make sure the 9V battery or an external power supply is plugged into the DC jack of the R4 Minima.

   .. image:: ../img/wiring_r4_espc201.png
      :width: 80%

#. Open the ``00-Blynk_quick_start.ino`` file under the path of ``ultimate-sensor-kit\code\iot_project_espc201\wifi\00-Blynk_quick_start``.


#. Replace the following three lines with the ones you copied from your account's
   **Device** page. They tell the board which Blynk account it belongs to.

   .. code-block:: arduino

      #define BLYNK_TEMPLATE_ID   "TMPLxxxxxx"
      #define BLYNK_TEMPLATE_NAME "Ultimate Sensor Kit"
      #define BLYNK_AUTH_TOKEN    "YourAuthToken"

   .. image:: ../img/blynk_copy_token.png
      :width: 80%

#. Fill in the ``ssid`` and ``password`` of the Wi-Fi network you are using.

   .. code-block:: arduino

      char ssid[] = "your_ssid";
      char pass[] = "your_password";

#. Upload the code, open the Serial Monitor and set the baud rate to **115200**. When
   the board has reached the Blynk cloud the monitor shows ``Ready``.

   .. image:: ../img/blynk_connect_network.png
      :width: 80%

   .. note::

      If ``ESP is not responding`` appears, check the following:

      * The external power supply is connected;
      * The module sits firmly in the adapter and IO9 is left floating;
      * Press the reset button on the R4 board.

      It may take two or three tries.

#. The device status in the Blynk.Console changes from **offline** to **online**.

   .. image:: ../img/blynk_online.png
      :width: 70%

Now the board is connected. The next chapter starts with the first project.
