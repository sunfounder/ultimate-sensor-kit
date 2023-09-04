
.. _iot_Bluetooth_oled:

Bluetooth OLED
=================================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/iot/12-iot_Bluetooth_oled.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>


This project uses an Android app created with MIT App Inventor to send messages over Bluetooth to an Arduino device. The Arduino, upon receiving the messages, displays them on an OLED screen. The Android app, designed with a user-friendly interface, allows users to input messages and send them with the press of a button. 

The Android application will be constructed utilizing a complimentary web-based platform known as |link_appinventor|. The project presents an excellent opportunity to gain familiarity with the interfacing of an Arduino with a smartphone. 


1. Build the Cirduit
-----------------------------

.. image:: img/12-Wiring_oled.png
    :width: 75%

* :ref:`cpn_uno`
* :ref:`cpn_jdy31`
* :ref:`cpn_olde`


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

#. After logging in, navigate to **Projects** -> **Import project (.aia) from my computer**. Subsequently, upload the ``oled.aia`` file located in the path ``ultimate-sensor-kit\iot_project\bluetooth\07-Bluetooth_oled``.

   You can also directly download here: :download:`oled.aia</_static/other/oled.aia>`

   .. image:: img/new/09-ai_import_shadow.png
        :align: center

#. Upon uploading the ``.aia`` file, you will see the application on the MIT App Inventor software. This is a pre-configured template. You can modify this template after you have familiarized yourself with MIT App Inventor through the following steps.

#. In MIT App Inventor, you have 2 primary sections: the **Designer** and the **Blocks**. You can switch between these two sections in the upper right corner of the page.

   .. image:: img/new/09-ai_intro_1_shadow.png

#. The **Designer** allows you to add buttons, text, screens, and modify the overall aesthetic of your application.

   .. image:: img/new/12-ai_intro_2_shadow.png
   
#. Next, there's the **Blocks** section. This section lets you craft custom functionalities for your app, allowing you to program each component on the app's GUI to achieve desired features.

   .. image:: img/new/12-ai_intro_3_shadow.png

#. To install the application on a smartphone, navigate to the **Build** tab.

   .. image:: img/new/08-ai_intro_4_shadow.png

   * You can generate a ``.apk`` file. After selecting this option, a page will appear allowing you to choose between downloading a ``.apk`` file or scanning a QR code for installation. Follow the installation guide to complete the application installation. 

     You also download our pre-compiled APK here: :download:`piano.apk</_static/other/piano.apk>`

   * If you wish to upload this app to Google Play or another app marketplace, you can generate a ``.aab`` file.


3. Upload the Code
-----------------------------

#. Open the ``07-Bluetooth_oled.ino`` file under the path of ``ultimate-sensor-kit\iot_project\bluetooth\07-Bluetooth_oled``, or copy this code into **Arduino IDE**.

   .. note:: 
      To install the library, use the Arduino Library Manager and search for **"Adafruit SSD1306"** and **"Adafruit GFX"** and install it. 

   .. raw:: html
       
       <iframe src=https://create.arduino.cc/editor/sunfounder01/aafe675c-be6c-49a0-8c73-596d8b85e3cc/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

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

#. Now open the newly installed **OLED** APP.

   .. image:: img/new/12-app_4_shadow.png
      :width: 25%
      :align: center

#. In the APP, click on **Connect** button to establish a connection between the APP and Bluetooth module.

   .. image:: img/new/12-app_5_shadow.png
      :width: 60%
      :align: center

#. This page displays a list of all paired Bluetooth devices. Choose the ``xx.xx.xx.xx.xx.xx JDY-31-SPP`` option from the list. The name of each device is listed next to its MAC address.

   .. image:: img/new/12-app_6_shadow.png
      :width: 60%
      :align: center

   After a successful connection, the OLED display will switch from showing "Waiting for connection" to displaying the MAC address of the connected device.

   .. image:: img/12-app_6-1.png
      :width: 70%
      :align: center

   .. raw:: html

      <br/>

#. If you don't see any devices on the page shown above, it could be because this app is not authorized to scan for nearby devices. In such a case, you will need to adjust the settings manually.

   * To access the **APP Info** page, long-press the app icon and select it. Alternatively, if you have another method to reach this page, use that instead.

   .. image:: img/new/12-app_8_shadow.png
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

#. After a successful connection, you will be redirected to the main page. Enter your desired message in the text box provided and click on the send button to display it on the OLED screen.

   .. image:: img/new/12-app_7_shadow.png
      :width: 60%
      :align: center

5. Code explanation
-----------------------------------------------

1. **Setting Up Bluetooth Communication**:
   
   This section includes the ``SoftwareSerial`` library and sets up the digital pins for Bluetooth communication. The standard ``Serial`` is for debugging while ``bleSerial`` is specifically for Bluetooth communication.

   .. code-block:: arduino

      #include <SoftwareSerial.h>
      const int bluetoothTx = 3;
      const int bluetoothRx = 4;
      SoftwareSerial bleSerial(bluetoothTx, bluetoothRx);

2. **Setting Up OLED Display**:

   The libraries and constants required to initialize and manage the OLED display are declared here.

   .. code-block:: arduino

      #include <SPI.h>
      #include <Wire.h>
      #include <Adafruit_GFX.h>
      #include <Adafruit_SSD1306.h>
      #define SCREEN_WIDTH 128
      #define SCREEN_HEIGHT 64
      #define OLED_RESET -1
      #define SCREEN_ADDRESS 0x3C
      Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

3. **Initialization**:
   
   In the ``setup()`` function, serial communications are initialized. The OLED display is started, and an initial message "Waiting for connection" is displayed.

   .. code-block:: arduino

      void setup() {
         Serial.begin(9600);
         bleSerial.begin(9600);
         if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
            Serial.println(F("SSD1306 allocation failed"));
            for (;;)
               ;
         }
         display.clearDisplay();
         display.setTextColor(WHITE);
         display.setTextSize(1);
         display.setCursor(32, 20);
         display.println("Waiting for");
         display.setCursor(32, 30);
         display.println("connection");
         display.display();
      }

4. **Main Loop**:
   
   Within the ``loop()``, the code constantly checks for incoming data from the Bluetooth module. Once a full message (ending with a '#', the APP will automatically add a '#' at the end of the message that the user send) is received, it's displayed on the OLED. Also, the received message is printed to the serial monitor for debugging purposes.

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
               display.clearDisplay();
               display.setTextColor(WHITE);
               display.setTextSize(1);
               display.setCursor(0, 20);
               display.println(message);
               display.display();
               message = "";
               delay(200);
            }
         }
      }