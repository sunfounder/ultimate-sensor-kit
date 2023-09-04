
.. _iot_Bluetooth_environmental_monitor:

Bluetooth Environmental Monitor
=================================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/iot/10-iot_Bluetooth_environmental_monitor.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>


This project uses an Android app created with MIT App Inventor to receive and display environmental data from an Arduino board. The Arduino board fetches data from a DHT11 sensor to measure temperature and humidity. Once the data is collected, it's transmitted over Bluetooth using the JDY-31 module.APP will display the data on the screen once it receives it.

The Android application will be constructed utilizing a complimentary web-based platform known as |link_appinventor|. The project presents an excellent opportunity to gain familiarity with the interfacing of an Arduino with a smartphone. 


1. Build the Cirduit
-----------------------------

.. image:: img/10-Wiring_Bluetooth_environmental_monitor.png
    :width: 75%

* :ref:`cpn_uno`
* :ref:`cpn_jdy31`
* :ref:`cpn_dht11`


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

#. After logging in, navigate to **Projects** -> **Import project (.aia) from my computer**. Subsequently, upload the ``Bluetooth_controlled_lock.aia`` file located in the path ``ultimate-sensor-kit\iot_project\bluetooth\05-Bluetooth_environmental_monitor``.

   You can also directly download here: :download:`Bluetooth_Environmental_Monitor.aia</_static/other/Bluetooth_Environmental_Monitor.aia>`

   .. image:: img/new/09-ai_import_shadow.png
        :align: center

#. Upon uploading the ``.aia`` file, you will see the application on the MIT App Inventor software. This is a pre-configured template. You can modify this template after you have familiarized yourself with MIT App Inventor through the following steps.

#. In MIT App Inventor, you have 2 primary sections: the **Designer** and the **Blocks**. You can switch between these two sections in the upper right corner of the page.

   .. image:: img/new/09-ai_intro_1_shadow.png

#. The **Designer** allows you to add buttons, text, screens, and modify the overall aesthetic of your application.

   .. image:: img/new/10-ai_intro_2_shadow.png
   
#. Next, there's the **Blocks** section. This section lets you craft custom functionalities for your app, allowing you to program each component on the app's GUI to achieve desired features.

   .. image:: img/new/10-ai_intro_3_shadow.png

#. To install the application on a smartphone, navigate to the **Build** tab.

   .. image:: img/new/08-ai_intro_4_shadow.png

   * You can generate a ``.apk`` file. After selecting this option, a page will appear allowing you to choose between downloading a ``.apk`` file or scanning a QR code for installation. Follow the installation guide to complete the application installation. 

     You also download our pre-compiled APK here: :download:`Bluetooth_Environmental_Monitor.apk</_static/other/Bluetooth_Environmental_Monitor.apk>`

   * If you wish to upload this app to Google Play or another app marketplace, you can generate a ``.aab`` file.


3. Upload the Code
-----------------------------

#. Open the ``05-Bluetooth_environmental_monitor.ino`` file under the path of ``ultimate-sensor-kit\iot_project\bluetooth\05-Bluetooth_environmental_monitor``, or copy this code into **Arduino IDE**.
   
   .. note:: 
      To install the library, use the Arduino Library Manager and search for **"DHT sensor library"** and install it. 

   .. raw:: html
       
       <iframe src=https://create.arduino.cc/editor/sunfounder01/97605897-2fae-4e4e-97f3-d254796636a1/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

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

#. Now open the newly installed **Environmental Monitor** APP.

   .. image:: img/new/10-app_4_shadow.png
      :width: 25%
      :align: center

#. In the APP, click on **Connect** button to establish a connection between the APP and Bluetooth module.

   .. image:: img/new/10-app_5_shadow.png
      :width: 60%
      :align: center

#. This page displays a list of all paired Bluetooth devices. Choose the ``xx.xx.xx.xx.xx.xx JDY-31-SPP`` option from the list. The name of each device is listed next to its MAC address.

   .. image:: img/new/10-app_6_shadow.png
      :width: 60%
      :align: center

#. If you don't see any devices on the page shown above, it could be because this app is not authorized to scan for nearby devices. In such a case, you will need to adjust the settings manually.

   * To access the **APP Info** page, long-press the app icon and select it. Alternatively, if you have another method to reach this page, use that instead.

   .. image:: img/new/10-app_8_shadow.png
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

#. After a successful connection, you will be redirected to the main page where it will display temperature and humidity.

   .. image:: img/new/10-app_7_shadow.png
      :width: 60%
      :align: center

5. Code explanation
-----------------------------------------------

1. Setting up Bluetooth communication and DHT11 sensor.

   .. code-block:: arduino

      #include <SoftwareSerial.h>
      const int bluetoothTx = 3;
      const int bluetoothRx = 4;
      SoftwareSerial bleSerial(bluetoothTx, bluetoothRx);

      #include <DHT.h>
      #define DHTPIN 2
      #define DHTTYPE DHT11
      DHT dht(DHTPIN, DHTTYPE);

   The code includes necessary libraries and defines pins for the Bluetooth module and DHT11 sensor. It also declares objects for Bluetooth communication and DHT11.

2. Initialization in setup function.

   .. code-block:: arduino

      void setup() {
        Serial.begin(9600);
        bleSerial.begin(9600);
        dht.begin();
      }

   This segment initializes serial communication for debugging, Bluetooth module, and the DHT sensor.

3. Reading data and sending via Bluetooth.

   .. code-block:: arduino

      void loop() {

        delay(2000);
        float humidity = dht.readHumidity();
        float temperature = dht.readTemperature();

        // Check if any reads failed and exit early (to try again).
        if (isnan(humidity) || isnan(temperature)) {
          Serial.println(F("Failed to read from DHT sensor!"));
          return;
        }

        // For debug
        // Print the humidity and temperature to the serial monitor
        Serial.print(F("Humidity: "));
        Serial.print(humidity);
        Serial.print(F("%  Temperature: "));
        Serial.print(temperature);
        Serial.println(F("°C "));

        sensorData = String(temperature) + "," + String(humidity);  // Concatenate temperature and humidity values
        Serial.print("Data to send: ");
        Serial.println(sensorData);

        bleSerial.println(sensorData);  // Send temperature and humidity values to the Bluetooth module
      }

   This segment reads temperature and humidity from the DHT11 sensor every 2 seconds. If the reading fails, it prints an error message. Otherwise, it prints the readings to the Serial Monitor and sends them via the Bluetooth module in a comma-separated format. When the app receives data in the format of "temperature,humidity", it will parse the information and present it on the user interface.