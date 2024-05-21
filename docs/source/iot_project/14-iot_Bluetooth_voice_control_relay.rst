
.. note::

    Hello, welcome to the SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasts Community on Facebook! Dive deeper into Raspberry Pi, Arduino, and ESP32 with fellow enthusiasts.

    **Why Join?**

    - **Expert Support**: Solve post-sale issues and technical challenges with help from our community and team.
    - **Learn & Share**: Exchange tips and tutorials to enhance your skills.
    - **Exclusive Previews**: Get early access to new product announcements and sneak peeks.
    - **Special Discounts**: Enjoy exclusive discounts on our newest products.
    - **Festive Promotions and Giveaways**: Take part in giveaways and holiday promotions.

    👉 Ready to explore and create with us? Click [|link_sf_facebook|] and join today!

.. _iot_Bluetooth_voice_control_relay:

Bluetooth Voice-control Relay
=================================

.. raw:: html

   <video controls style = "max-width:100%">
      <source src="../_static/video/iot/14-iot_Bluetooth_voice_control_relay.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>


This project integrates an Android app, developed using MIT App Inventor, with an Arduino Uno board. The app offers a voice input feature. When the user's voice input contains the word "on", the app sends a "1" message via Bluetooth to the Arduino, instructing it to turn the relay on. Similarly, if the voice input contains the word "off", the app sends a "0" message, signaling the Arduino to turn the relay off. Once the Arduino receives these messages, it processes them and turns the relay on or off accordingly. 

The Android application will be constructed utilizing a complimentary web-based platform known as |link_appinventor|. The project presents an excellent opportunity to gain familiarity with the interfacing of an Arduino with a smartphone. 


1. Build the Circuit
-----------------------------

.. warning ::
    The following example demonstrates using a relay to control an traffic light module. 
    **While you can connect the relay to other appliances in actual applications, extreme caution is required when dealing with HIGH AC voltage. Improper or incorrect use can lead to severe injury or even death. Therefore, it is intended for people who are familiar with and knowledgeable about HIGH AC voltage. Always prioritize safety.**

.. image:: img/14-Wiring_Bluetooth_voice_control_relay.png
    :width: 75%

* :ref:`cpn_uno`
* :ref:`cpn_jdy31`
* :ref:`cpn_relay`
* :ref:`cpn_traffic`


2. Create the Android App
-----------------------------

The Android application will be developed using a free web application known as |link_appinventor|. 
MIT App Inventor serves as an excellent starting point for Android development, owing to its intuitive drag-and-drop 
features allowing for the creation of simplistic applications.

Now, let's begin.

#. Go to |link_appinventor_login|, and click "online tool" to login. You will require a Google account to register with MIT App Inventor.

   .. image:: img/new/09-ai_signup_shadow.png
       :width: 90%
       :align: center

#. After logging in, navigate to **Projects** -> **Import project (.aia) from my computer**. Subsequently, upload the ``VoiceControl.aia`` file located in the path ``ultimate-sensor-kit\iot_project\bluetooth\09-Bluetooth_voice_control_relay``.

   You can also directly download here: :download:`VoiceControl.aia</_static/other/VoiceControl.aia>`

   .. image:: img/new/09-ai_import_shadow.png
        :align: center

#. Upon uploading the ``.aia`` file, you will see the application on the MIT App Inventor software. This is a pre-configured template. You can modify this template after you have familiarized yourself with MIT App Inventor through the following steps.

#. In MIT App Inventor, you have 2 primary sections: the **Designer** and the **Blocks**. You can switch between these two sections in the upper right corner of the page.

   .. image:: img/new/09-ai_intro_1_shadow.png

#. The **Designer** allows you to add buttons, text, screens, and modify the overall aesthetic of your application.

   .. image:: img/new/14-ai_intro_2_shadow.png
   
#. Next, there's the **Blocks** section. This section lets you craft custom functionalities for your app, allowing you to program each component on the app's GUI to achieve desired features.

   .. image:: img/new/14-ai_intro_3_shadow.png

   In this project, we take English recognition as an example. If you want to apply recognition of other languages, you need to modify the code block below and then compile the APK by yourself.

   Firstly, you need to set ``SpeechRecognizer1.Language`` to the **language tag** of the language you want to recognize. Language is specified using a language tag with an optional region suffix, such as ``en``, ``de`` or ``ja``. The language tag can be found at |link_language_tag|.

   .. image:: img/new/14-ai_intro_3-1_shadow.png
      :width: 80%
      :align: center

   Then, you need to modify the corresponding judgment condition. The part indicated by the arrow in the following figure.

   .. image:: img/new/14-ai_intro_3-2_shadow.png
      :width: 80%
      :align: center 

#. To install the application on a smartphone, navigate to the **Build** tab.

   .. image:: img/new/08-ai_intro_4_shadow.png

   * You can generate a ``.apk`` file. After selecting this option, a page will appear allowing you to choose between downloading a ``.apk`` file or scanning a QR code for installation. Follow the installation guide to complete the application installation. 

     You also download our pre-compiled APK here: :download:`VoiceControl.apk</_static/other/VoiceControl.apk>`

   * If you wish to upload this app to Google Play or another app marketplace, you can generate a ``.aab`` file.


3. Upload the Code
-----------------------------

#. Open the ``09-Bluetooth_voice_control_relay.ino`` file under the path of ``ultimate-sensor-kit\iot_project\bluetooth\09-Bluetooth_voice_control_relay``, or copy this code into **Arduino IDE**.

   .. raw:: html
       
       <iframe src=https://create.arduino.cc/editor/sunfounder01/ab5f8fca-dd25-4e32-bf61-d5dc109bb6cd/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

#. After selecting the correct board and port, click the **Upload** button.

#. Open the Serial monitor(set baudrate to **9600**) to view debug messages. 

4. App and Bluetooth module Connection
-----------------------------------------------

Ensure that the application created earlier is installed on your smartphone.

#. Initially, turn on **Bluetooth** on your smartphone.

   .. image:: img/new/09-app_1_shadow.png
      :width: 60%
      :align: center

#. Navigate to the **Bluetooth settings** on your smartphone and look for names like **JDY-31-SPP**.

   .. image:: img/new/09-app_2_shadow.png
      :width: 60%
      :align: center

#. After clicking it, agree to the **Pair** request in the pop-up window. If prompted for a pairing code, please enter "1234".

   .. image:: img/new/09-app_3_shadow.png
      :width: 60%
      :align: center

#. Now open the newly installed **Voice-Controlled Relay** APP.

   .. image:: img/new/14-app_4_shadow.png
      :width: 25%
      :align: center

#. In the APP, click on **Connect** button to establish a connection between the APP and Bluetooth module.

   .. image:: img/new/14-app_5_shadow.png
      :width: 60%
      :align: center

#. This page displays a list of all paired Bluetooth devices. Choose the ``xx.xx.xx.xx.xx.xx JDY-31-SPP`` option from the list. The name of each device is listed next to its MAC address.

   .. image:: img/new/14-app_6_shadow.png
      :width: 60%
      :align: center

#. If you don't see any devices on the page shown above, it could be because this app is not authorized to scan for nearby devices. In such a case, you will need to adjust the settings manually.

   * To access the **APP Info** page, long-press the app icon and select it. Alternatively, if you have another method to reach this page, use that instead.

   .. image:: img/new/14-app_8_shadow.png
         :width: 60%
         :align: center

   * Navigate to the **Permissions** page.

   .. image:: img/new/08-app_9_shadow.png
         :width: 60%
         :align: center

   * To enable the APP to scan for nearby devices, go to **Nearby devices** and select **Always**.

   .. image:: img/new/08-app_10_shadow.png
         :width: 60%
         :align: center

   * Now, restart the APP and repeat steps 5 and 6 to successfully connect to Bluetooth.

#. After a successful connection, you will be redirected to the main page. Click the "ON" or "OFF" button to turn on or off the relay.

   .. image:: img/new/14-app_7_shadow.png
      :width: 60%
      :align: center

   Although the relay can be controlled by voice input commands containing "on" or "off", it is recommended to use longer or complete sentences such as "turn on" or "turn on the light" to avoid recognition errors caused by short voice inputs. 
   
   Speech recognition function relies on Google's speech recognition engine, so you may need to install |link_speech_recognition| in advance (most Android phones come with this feature pre-installed).

   .. image:: img/new/14-app_7-1_shadow.png
      :width: 60%
      :align: center

5. Code explanation
-----------------------------------------------

1. Set up Bluetooth module communication

   .. code-block:: arduino
   
      #include <SoftwareSerial.h>
      const int bluetoothTx = 3;                           // bluetooth tx to 3 pin
      const int bluetoothRx = 4;                           // bluetooth rx to 4 pin
      SoftwareSerial bleSerial(bluetoothTx, bluetoothRx);  // Declare SoftwareSerial object for Bluetooth communication
   
   This section initializes the Bluetooth communication using the SoftwareSerial library. This library allows the Arduino to have an additional serial port. The Bluetooth module's "TX" pin is connected to the Arduino's pin 3 and the "RX" pin is connected to pin 4.

2. Define variables and relay control pin

   .. code-block:: arduino
   
      char character;  // Character received from Bluetooth serial
      String message;  // Stores the complete message from Bluetooth
      const int relayPin = 8;
   
   Here, we declare variables to store individual characters received from Bluetooth (``character``) and the complete message (``message``). The ``relayPin`` is initialized to pin 8, which will be used to control the relay.

3. Initialize serial communication and set relay pin mode

   .. code-block:: arduino
   
      void setup() {
        Serial.begin(9600);
        bleSerial.begin(9600);
        pinMode(relayPin, OUTPUT);
      }

   In the ``setup()`` function, we initialize the standard serial port and the Bluetooth serial port with a baud rate of 9600. We also set the ``relayPin`` as an output pin.

4. Read Bluetooth messages and control the relay

   .. code-block:: arduino
   
      void loop() {
        while (bleSerial.available() > 0) {
          character = bleSerial.read();
          message = message + character;
          if (character == '#') {
            message = message.substring(0, message.length() - 1);
            Serial.println();
            Serial.print("DEBUG:");
            Serial.println(message);
            if (message == "1") {
              digitalWrite(relayPin, HIGH);
              Serial.println("On");
            } else if (message == "0") {
              digitalWrite(relayPin, LOW);
              Serial.println("Off");
            }
            message = "";
            delay(200);
          }
        }
      }


   The ``loop()`` function continuously checks for incoming messages from Bluetooth. When a message is received, each character is appended to the ``message`` string. Once the ``#`` character is detected, the message is considered complete. We then remove the ``#``, print a debug message, and check the content. If it's "1", the relay is turned on; if "0", it's turned off. The ``message`` string is then cleared, and we wait briefly before checking for the next message.