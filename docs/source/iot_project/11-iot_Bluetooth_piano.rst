
.. _iot_Bluetooth_piano:

Bluetooth Piano
=============================

.. raw:: html

   <video controls style = "max-width:100%">
      <source src="../_static/video/iot/11-iot_Bluetooth_piano.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>
   <br/><br/>

This project uses an Android app created with MIT App Inventor to enable a straightforward "piano" feature by utilizing a JDY-31 Bluetooth module and a Passive Buzzer Module. The Bluetooth piano project allows users to play different musical notes on a passive buzzer module using a JDY-31 Bluetooth module. By sending specific note instructions via Bluetooth to the Arduino, users can generate corresponding tones on the buzzer. 

The Android application will be constructed utilizing a complimentary web-based platform known as |link_appinventor|. The project presents an excellent opportunity to gain familiarity with the interfacing of an Arduino with a smartphone. 


1. Build the Cirduit
-----------------------------

.. image:: img/11-Wiring_Bluetooth_piano.png
    :width: 75%

* :ref:`cpn_uno`
* :ref:`cpn_jdy31`
* :ref:`cpn_buzzer`


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

#. After logging in, navigate to **Projects** -> **Import project (.aia) from my computer**. Subsequently, upload the ``piano.aia`` file located in the path ``ultimate-sensor-kit\iot_project\bluetooth\06-Bluetooth_piano``.

   You can also directly download here: :download:`piano.aia</_static/other/piano.aia>`

   .. image:: img/new/09-ai_import_shadow.png
        :align: center

#. Upon uploading the ``.aia`` file, you will see the application on the MIT App Inventor software. This is a pre-configured template. You can modify this template after you have familiarized yourself with MIT App Inventor through the following steps.

#. In MIT App Inventor, you have 2 primary sections: the **Designer** and the **Blocks**. You can switch between these two sections in the upper right corner of the page.

   .. image:: img/new/09-ai_intro_1_shadow.png

#. The **Designer** allows you to add buttons, text, screens, and modify the overall aesthetic of your application.

   .. image:: img/new/11-ai_intro_2_shadow.png
   
#. Next, there's the **Blocks** section. This section lets you craft custom functionalities for your app, allowing you to program each component on the app's GUI to achieve desired features.

   .. image:: img/new/11-ai_intro_3_shadow.png

#. To install the application on a smartphone, navigate to the **Build** tab.

   .. image:: img/new/08-ai_intro_4_shadow.png

   * You can generate a ``.apk`` file. After selecting this option, a page will appear allowing you to choose between downloading a ``.apk`` file or scanning a QR code for installation. Follow the installation guide to complete the application installation. 

     You also download our pre-compiled APK here: :download:`piano.apk</_static/other/piano.apk>`

   * If you wish to upload this app to Google Play or another app marketplace, you can generate a ``.aab`` file.


3. Upload the Code
-----------------------------

#. Open the ``06-Bluetooth_piano.ino`` file under the path of ``ultimate-sensor-kit\iot_project\bluetooth\06-Bluetooth_piano``, or copy this code into **Arduino IDE**.

   .. raw:: html
       
       <iframe src=https://create.arduino.cc/editor/sunfounder01/a9d0b7bf-0927-4a10-88b9-bbc4a9abc5c8/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

#. After selecting the correct board and port, click the **Upload** button.

#. Open the Serial monitor(set baudrate to **9600**) to view debug messages. 

4. App and Bluetooth moudule Connection
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

#. Now open the newly installed **Piano** APP.

   .. image:: img/new/11-app_4_shadow.png
      :width: 25%
      :align: center

#. In the APP, click on **Connect** button to establish a connection between the APP and Bluetooth module.

   .. image:: img/new/11-app_5_shadow.png
      :width: 85%
      :align: center

#. This page displays a list of all paired Bluetooth devices. Choose the ``xx.xx.xx.xx.xx.xx JDY-31-SPP`` option from the list. The name of each device is listed next to its MAC address.

   .. image:: img/new/11-app_6_shadow.png
      :width: 60%
      :align: center

#. If you don't see any devices on the page shown above, it could be because this app is not authorized to scan for nearby devices. In such a case, you will need to adjust the settings manually.

   * To access the **APP Info** page, long-press the app icon and select it. Alternatively, if you have another method to reach this page, use that instead.

   .. image:: img/new/11-app_8_shadow.png
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

#. After a successful connection, you can click on the buttons in the app to play different notes, and even perform some simple songs.

   .. image:: img/new/11-app_7_shadow.png
      :width: 85%
      :align: center

5. Code explanation
-----------------------------------------------

1. **Setting Up Libraries and Pins**

   .. code-block:: arduino
   
      #include "pitches.h"
      #include <SoftwareSerial.h>
      const int bluetoothTx = 3;
      const int bluetoothRx = 4;
      SoftwareSerial bleSerial(bluetoothTx, bluetoothRx);
      const int buzzerPin = 2;
   

   - ``pitches.h``: This file contains the frequency values for musical notes.

   .. raw:: html

      <br/>

2. **Variable Declarations for Storing Bluetooth Data**

   .. code-block:: arduino
   
      char character;
      String noteType;
   
   - ``character``: Stores individual characters received from Bluetooth.
   - ``noteType``: Aggregates the characters to form the full note instruction.

   .. raw:: html

      <br/>

3. **Setup Function - Initializing Serial Communications**

   .. code-block:: arduino
   
      void setup() {
        Serial.begin(9600);
        bleSerial.begin(9600);
      }
   
   - Initializes serial communication at a baud rate of 9600.
   - The standard ``Serial`` is for debugging while ``bleSerial`` is specifically for Bluetooth communication.

4. **Main Loop - Reading Bluetooth Data and Playing Corresponding Notes**

   .. code-block:: arduino
   
      void loop() {
        while (bleSerial.available() > 0) {
          character = bleSerial.read();
          noteType = noteType + character;
          if (character == '*') {
            noteType = noteType.substring(0, noteType.length() - 1);
            Serial.println(noteType);
            if (noteType == "NOTE_C4") {
              tone(buzzerPin, NOTE_C4);
            } // ... other notes check similarly ...
            noteType = "";
            delay(200);
            noTone(buzzerPin);
          }
        }
      }

   - Reads characters from Bluetooth and assembles the ``noteType``.
   - If an asterisk ('*') is detected, it indicates the end of the note instruction. The note is then played, followed by a short delay and then stopped.
