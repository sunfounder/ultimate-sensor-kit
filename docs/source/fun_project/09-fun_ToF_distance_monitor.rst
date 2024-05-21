.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

.. _fun_tof_distance_monitor:

ToF Entfernungsmonitor
==========================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/fun/09-fun_ToF_distance_monitor.mp4"  type="video/mp4">
      Ihr Browser unterstützt das Video-Tag nicht.
   </video>

Dieses Projekt ist darauf ausgelegt, die Entfernung zu einem Objekt mit Hilfe des VL53L0X Time-of-Flight (ToF) Micro-LIDAR Entfernungssensors zu messen und anzuzeigen. Die gemessene Entfernung in Millimetern wird auf einem OLED-Display dargestellt und zusätzlich auf dem seriellen Monitor ausgegeben. Der VL53L0X kann einen Bereich von etwa 50mm bis 1200mm abdecken.

1. Schaltungsaufbau
-----------------------------

.. image:: img/09-fun_ToF_distance_monitor_circuit.png
    :width: 90%

* :ref:`cpn_uno`
* :ref:`cpn_VL53L0X`
* :ref:`cpn_olde`


2. Programmcode
-----------------------------

#. Öffnen Sie die Datei ``09-ToF_distance_monitor.ino`` im Verzeichnis ``ultimate-sensor-kit\fun_project\09-ToF_distance_monitor`` oder kopieren Sie diesen Code in die **Arduino IDE**.

   .. note:: 
      Verwenden Sie den Arduino-Bibliotheksmanager und suchen Sie nach **"Adafruit_VL53L0X"** und installieren Sie diese.

   .. raw:: html
       
       <iframe src=https://create.arduino.cc/editor/sunfounder01/8077aa45-8e0c-4c13-9211-b23926b79462/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


3. Code-Erläuterung
-----------------------------

Das Projekt nutzt den VL53L0X Time-of-Flight-Sensor, um Entfernungen durch Messung der Zeit, die das Licht benötigt, um zu einem Objekt und zurück zum Sensor zu gelangen, zu ermitteln. Das OLED-Display zeigt dann die gemessene Entfernung in Millimetern an. Über die serielle Kommunikation werden ebenfalls die Messwerte ausgegeben, was das Monitoring und Debugging erleichtert. Sowohl das OLED-Display als auch der VL53L0X-Sensor kommunizieren mit dem Arduino über das I2C-Protokoll.

#. Einbinden der notwendigen Bibliotheken und Initialisieren der Komponenten

   .. note:: 
      Verwenden Sie den Arduino-Bibliotheksmanager und suchen Sie nach **"Adafruit_VL53L0X"** und installieren Sie diese.

   .. code-block:: arduino

      #include <Wire.h>
      #include "Adafruit_VL53L0X.h"
      #include <SPI.h>
      #include <Adafruit_GFX.h>
      #include <Adafruit_SSD1306.h>
   
      // Initialize the OLED display module with a resolution of 128x64
      Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire, -1);
      
      // Initialize the VL53L0X distance sensor
      Adafruit_VL53L0X lox = Adafruit_VL53L0X();
   
   - Die erforderlichen Bibliotheken für die Handhabung der I2C-Kommunikation, des Abstandssensors, des SPI-Protokolls und des OLED-Displays sind enthalten.
   - Das OLED-Display und der VL53L0X-Abstandssensor werden initialisiert.
#. Initialisierung der seriellen Kommunikation und Vorbereitung des Displays sowie des VL53L0X-Entfernungssensors.

   .. code-block:: arduino

      void setup() {
        Serial.begin(9600);
      
        // Start the OLED display with I2C address 0x3C
        display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
        display.display();
        delay(1000);
      
        // Begin I2C communication
        Wire.begin();
   
        // Start the VL53L0X distance sensor, halt if initialization fails
        if (!lox.begin()) {
          Serial.println(F("Failed to boot VL53L0X"));
          while (1)
            ;
        }
      
        // Set OLED display text size and color
        display.setTextSize(3);
        display.setTextColor(WHITE);
      }

   

   - Starte die serielle Kommunikation mit einer Baudrate von 9600.
   - Initialisiere das OLED-Display mit seiner I2C-Adresse.
   - Beginne die I2C-Kommunikation.
   - Überprüfe, ob der VL53L0X-Distanzsensor ordnungsgemäß initialisiert ist. Wenn nicht, wird eine Fehlermeldung angezeigt und der Arduino tritt in eine Endlosschleife ein.
   - Setze Textgröße und Farbe für das OLED-Display.

#. Hauptprogrammschleife zur Entfernungsvermessung und Anzeige des Ergebnisses

   .. code-block:: arduino

      void loop() {
        VL53L0X_RangingMeasurementData_t measure;
      
        lox.rangingTest(&measure, false);  // pass in 'true' to get debug data printout
      
        // If there are no phase failures, display the measured distance
        if (measure.RangeStatus != 4) {
          display.clearDisplay();
          display.setCursor(12, 22);
          display.print(measure.RangeMilliMeter);
          display.print("mm");
          display.display();
          Serial.println();
          delay(50);
        } else {
          display.display();
          display.clearDisplay();
          return;
        }
      }

   - Erstelle eine Variable, um die Messdaten zu speichern.
   - Führe eine Messung mit dem VL53L0X-Sensor durch.
   - Überprüfe, ob die Messung gültig ist (d.h. keine Phasenausfälle vorliegen).
   - Wenn die Messung gültig ist, lösche den OLED-Bildschirm, setze die Cursorposition und zeige den gemessenen Abstand an.
   - Andernfalls aktualisiere das Display und lösche es für die nächste Lesung.