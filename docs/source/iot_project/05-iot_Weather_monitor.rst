.. _iot_Wetterüberwachung:

Wetterüberwachung mit ThingSpeak
====================================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/iot/05-iot_Weather_monitor.mp4"  type="video/mp4">
      Ihr Browser unterstützt das Video-Tag nicht.
   </video>

Dieses Projekt erfasst Temperatur- und Druckdaten mithilfe eines Atmosphärendrucksensors. Die gesammelten Daten werden in regelmäßigen Abständen über ein ESP8266-Modul und ein WLAN-Netzwerk an die ThingSpeak-Cloud-Plattform übertragen.


1. Schaltung aufbauen
-----------------------------

.. note::

    Das ESP8266-Modul benötigt einen hohen Stromfluss, um eine stabile Betriebsumgebung zu gewährleisten. Stellen Sie daher sicher, dass die 9-V-Batterie angeschlossen ist.

.. image:: img/05-Wiring_Weather_monitor.png
    :width: 90%

* :ref:`cpn_uno`
* :ref:`cpn_esp8266`
* :ref:`cpn_bmp280`


2. ThingSpeak konfigurieren
-----------------------------

|link_thingspeak| ™ ist eine IoT-Analyseplattform, die die Aggregation, Visualisierung und Analyse von Live-Datenströmen in der Cloud ermöglicht. ThingSpeak bietet sofortige Visualisierungen von Daten, die von Ihren Geräten an ThingSpeak gesendet werden. Mit der Möglichkeit, MATLAB®-Code in ThingSpeak auszuführen, können Sie eine Echtzeitanalyse und -verarbeitung der eingehenden Daten durchführen. ThingSpeak wird häufig für Prototypen und Machbarkeitsnachweise von IoT-Systemen mit Analyseanforderungen eingesetzt.

.. image:: https://thingspeak.com/assets/Signup_TSP_ML_image-3d581d644f5eb1ff9f4999fc55ad04e2530ee7f54be98323d7bb453032353750.svg
    :width: 80%
    :align: center

.. raw:: html
    
    <br/>  

**2.1 ThingSpeak-Konto erstellen**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Als Erstes müssen Sie ein Konto bei ThingSpeak erstellen. Da es eine Zusammenarbeit mit MATLAB gibt, können Sie sich mit Ihren MathWorks-Anmeldedaten bei |link_thingspeak| anmelden.

Wenn Sie noch keine haben, müssen Sie ein Konto bei MathWorks erstellen und sich bei der ThingSpeak-Anwendung anmelden.

.. image:: img/new/05-thingspeak_signup_shadow.png
    :width: 50%
    :align: center

**2.2 Einen Kanal erstellen**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Nach der Anmeldung erstellen Sie einen neuen Kanal zur Datenspeicherung, indem Sie zu "Channels" > "My Channels" gehen und auf "New Channel" klicken.

.. image:: img/new/05-thingspeak_channel_1_shadow.png
    :width: 95%
    :align: center

Für dieses Projekt müssen wir einen Kanal namens "**Weather Monitor**" mit zwei Feldern erstellen: **Field 1** für "**Temperature**" und **Field 2** für "**Atmospheric Pressure**".

.. image:: img/new/05-thingspeak_channel_2_shadow.png
    :width: 95%
    :align: center

.. raw:: html
    
    <br/>  


3. Den Code ausführen
-----------------------------

#. Öffnen Sie die Datei ``05-Weather_monitor.ino`` im Verzeichnispfad ``ultimate-sensor-kit\iot_project\wifi\05-Weather_monitor`` oder kopieren Sie diesen Code in die **Arduino IDE**.

   .. note:: 
      Um die Bibliothek zu installieren, nutzen Sie den Arduino-Bibliotheksmanager und suchen Sie nach **"Adafruit BMP280"**, um sie zu installieren.

   .. raw:: html
       
       <iframe src=https://create.arduino.cc/editor/sunfounder01/195c180e-72fa-4bea-9370-7c75920c7933/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

#. Sie müssen die ``mySSID`` und ``myPWD`` des von Ihnen verwendeten WLANs eingeben.

   .. code-block:: arduino

    String mySSID = "Ihre_SSID";     // WiFi SSID
    String myPWD = "Ihr_Passwort";  // WiFi-Passwort

#. Außerdem müssen Sie die ``myAPI`` mit Ihrem ThingSpeak Channel-API-Schlüssel anpassen.

   .. code-block:: arduino
    
      String myAPI = "xxxxxxxxxxxx";  // API-Schlüssel

   .. image:: img/new/05-thingspeak_api_shadow.png
       :width: 80%
       :align: center
  
   Hier finden Sie **Ihren einzigartigen API-Schlüssel, den Sie geheim halten müssen**.

#. Nach der Auswahl des korrekten Boards und Ports klicken Sie auf die Schaltfläche **Hochladen**.

#. Öffnen Sie das serielle Monitor (Baudrate auf **9600** einstellen) und warten Sie auf eine Meldung wie eine erfolgreiche Verbindung.

   .. image:: img/new/05-ready_1_shadow.png
          :width: 95%

   .. image:: img/new/05-ready_2_shadow.png
          :width: 95%



4. Code-Erklärung
-----------------------------

Das im Kit enthaltene ESP8266-Modul ist bereits ab Werk mit einer AT-Firmware vorprogrammiert. Dadurch lässt sich das ESP8266-Modul über AT-Befehle steuern. In diesem Projekt verwenden wir die Software-Seriell-Kommunikation, um die Kommunikation zwischen dem Arduino Uno Board und dem ESP8266-Modul zu ermöglichen. Das Arduino Uno Board sendet AT-Befehle an das ESP8266-Modul, um eine Netzwerkverbindung herzustellen und Anfragen zu senden. Weitere Informationen finden Sie unter |link_esp8266_at|.

Das Uno-Board liest Sensordaten und sendet AT-Befehle an das ESP8266-Modul. Das ESP8266-Modul verbindet sich mit einem Netzwerk und sendet Anfragen an die ThingSpeak-Server.

1. **Einrichtung & Globale Variablen**:

   Dieser Abschnitt stellt die Kommunikation mit dem ESP8266-Modul her und deklariert notwendige globale Variablen.

   .. code-block:: arduino

      #include <SoftwareSerial.h>
      SoftwareSerial espSerial(2, 3);
      #define DEBUG true
      String mySSID = "Ihre_SSID";
      String myPWD = "Ihr_Passwort";
      String myAPI = "xxxxxxxxxxxx";
      String myHOST = "api.thingspeak.com";
      String myPORT = "80";
      unsigned long lastConnectionTime = 0;
      const unsigned long postingInterval = 20000L;

2. **BMP280 Sensor-Konfiguration**:

   Dieses Code-Segment konfiguriert den BMP280-Sensor für die Datenerfassung.

   .. code-block:: arduino

      #include <Wire.h>
      #include <Adafruit_BMP280.h>
      #define BMP280_ADDRESS 0x76
      Adafruit_BMP280 bmp;
      unsigned bmpStatus;
      float pressure;
      float temperature;

3. **Initialisierung (Setup-Funktion)**:

   Die Funktion ``setup()`` initialisiert die serielle Kommunikation, verbindet das ESP8266-Modul mit dem WLAN und initialisiert den BMP280-Sensor.

   .. code-block:: arduino

      void setup() {
        Serial.begin(9600);
        espSerial.begin(115200);
      
        // Initialize the ESP8266 module
        sendATCommand("AT+RST", 1000, DEBUG);                                         //Reset the ESP8266 module
        sendATCommand("AT+CWMODE=1", 1000, DEBUG);                                    //Set the ESP mode as station mode
        sendATCommand("AT+CWJAP=\"" + mySSID + "\",\"" + myPWD + "\"", 1000, DEBUG);  //Connect to WiFi network
      
        // Initialize the bmp280 sensor
        bmpStatus = bmp.begin(BMP280_ADDRESS);
        if (!bmpStatus) {
          Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                           "try a different address!"));
          while (1) delay(10);  // Stop code execution if the sensor is not found.
        }
      
        /* Default settings from datasheet. */
        bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                        Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                        Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                        Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                        Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
      }

4. **loop()-Funktion**:

   Die Haupt-Schleife prüft, ob seit der letzten Datenübertragung 20 Sekunden vergangen sind. Ist dies der Fall, werden die Daten gesendet. Sie können den Wert der Variable ``postingInterval`` anpassen, um das Intervall der Datenübertragung zu ändern.

   .. code-block:: arduino

      void loop() {
        // Datenübertragung gemäß dem eingestellten Zeitintervall.
        if (millis() - lastConnectionTime > postingInterval) {
          sendData();
        }
      }

5. **Datenübertragung**:

   Diese Funktion liest die Temperatur und den Druck, konstruiert die GET-Anfrage und sendet die Daten an ThingSpeak.

   Wir haben eine GET-Anfrage in Form von ``GET /update?api_key=xxxxxx&field1=xx&field2=xxxxxx`` erstellt und drei Parameter an den ThingSpeak-Server gesendet.

     - ``api_key``: API-Schlüssel für Authentifizierung und Zugriffskontrolle
     - ``field1``: ein Parameter namens "field1" zur Aufzeichnung der Temperatur
     - ``field2``: ein Parameter namens "field2" zur Aufzeichnung des Luftdrucks

   .. code-block:: arduino

      void sendData() {
        // Read the temperature and pressure from the BMP280 sensor
        pressure = bmp.readPressure();
        temperature = bmp.readTemperature();
      
        // If the data is invalid, print an error message and stop sending it
        if (isnan(pressure) || isnan(temperature)) {
          Serial.println("Failed to read from BMP sensor!");
          return;
        }
      
        // Construct the GET request for ThingSpeak
        String sendData = "GET /update?api_key=" + myAPI;
        sendData += "&field1=" + String(temperature);
        sendData += "&field2=" + String(pressure);
      
        // Send the GET request to ThingSpeak via the ESP8266
        sendATCommand("AT+CIPMUX=1", 1000, DEBUG);  //Allow multiple connections
        sendATCommand("AT+CIPSTART=0,\"TCP\",\"" + myHOST + "\"," + myPORT, 1000, DEBUG);  // Start a TCP connection to ThingSpeak
        sendATCommand("AT+CIPSEND=0," + String(sendData.length() + 4), 1000, DEBUG);       // Send the GET request
        espSerial.find(">");    // Wait for the ">" character from the ESP8266
        espSerial.println(sendData);    // Send the GET request
        Serial.println(sendData);
      
        // Print the values
        Serial.println("Value to be sent: ");
        printBMP();  // Call the printBMP function to print the temperature and pressure
      
        sendATCommand("AT+CIPCLOSE=0", 1000, DEBUG);  // Close the TCP connection
        lastConnectionTime = millis();          // Update the last connection time
      }


6. **Hilfsfunktionen**:

   Diese Funktionen unterstützen beim Senden von AT-Befehlen an das ESP8266-Modul und beim Anzeigen der Messwerte des BMP280-Sensors.

   .. code-block:: arduino

      void sendATCommand(String command, const int timeout, boolean debug) {
         ... // (refer to the provided code for the full sendATCommand function)
      }

      void printBMP() {
         ... // (refer to the provided code for the full printBMP function)
      }


**Referenz**

* |link_esp8266_at|