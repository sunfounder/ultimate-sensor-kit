.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

.. _cpn_VL53L0X:

Time-of-Flight Mikro-LIDAR-Entfernungssensor (VL53L0X)
===============================================================

.. image:: img/20_VL53L0X_module.png
    :width: 350
    :align: center

Einführung
---------------------------

Der VL53L0X ist ein Time-of-Flight (ToF) Distanzmesssensor, der mithilfe von Lasertechnologie präzise Entfernungen bis zu 2 Metern messen kann. Das Modul ist ein Multisensor-System, das einen integrierten Laseremitter, Detektor und Mikrocontroller enthält. Es ist vollständig ausgestattet mit erforderlichen Komponenten wie Pull-up-Widerständen und Kondensatoren und bietet einen Messbereich von 50 - 1200 mm.

Funktionsprinzip
---------------------------

Das VL53L0X-Modul arbeitet auf dem Prinzip der Flugzeit (ToF). Es sendet einen Laserimpuls aus und misst die Zeit, die der Impuls benötigt, um zurückzukommen. Diese Zeit ist proportional zur Entfernung zwischen Sensor und Objekt. Das Modul nutzt ein SPAD-Array (Single-Photon-Avalanche-Diode) für die Detektion des reflektierten Lichts vom Objekt. Das SPAD-Array kann selbst einzelne Photonen detektieren. Ein integrierter Mikrocontroller verarbeitet die Daten des SPAD-Arrays und berechnet die Entfernung zum Objekt.

Anwendungsbeispiele 
---------------------------

**Hardwarekomponenten**

- Arduino Uno R4 oder R3 Board * 1
- Time-of-Flight Mikro-LIDAR-Entfernungssensor * 1
- Jumperkabel

**Schaltungsaufbau**

.. image:: img/20_VL53L0X_module_circuit.png
    :width: 550
    :align: center

.. raw:: html
    
    <br/><br/>   

Programmcode
^^^^^^^^^^^^^^^^^^^^

.. note:: 
   Für die Installation der Bibliothek verwenden Sie den Arduino-Bibliotheksmanager und suchen Sie nach **"Adafruit_VL53L0X"** und installieren Sie diese.

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/d1f540b1-8a29-40cd-ba12-84c34f0ab4a3/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/20-component_VL53L0X.mp4"  type="video/mp4">
      Ihr Browser unterstützt das Video-Tag nicht.
   </video>
   <br/><br/>  

Code-Erläuterung
^^^^^^^^^^^^^^^^^^^^

#. Einbindung der notwendigen Bibliothek und Initialisierung des Sensorobjekts. Wir beginnen mit der Einbindung der Bibliothek für den VL53L0X-Sensor und erstellen eine Instanz der Klasse Adafruit_VL53L0X.

   .. note:: 
      Verwenden Sie den Arduino-Bibliotheksmanager und suchen Sie nach **"Adafruit_VL53L0X"** und installieren Sie diese.

   .. code-block:: arduino

      #include <Adafruit_VL53L0X.h>
      Adafruit_VL53L0X lox = Adafruit_VL53L0X();

#. Initialisierung in der Funktion ``setup()``. Hier richten wir die serielle Kommunikation ein und initialisieren den Entfernungssensor. Kann der Sensor nicht initialisiert werden, hält das Programm an.

   .. code-block:: arduino

      void setup() {
        Serial.begin(115200);
        while (!Serial) {
          delay(1);
        }
        Serial.println("Adafruit VL53L0X test");
        if (!lox.begin()) {
          Serial.println(F("Failed to boot VL53L0X"));
          while (1)
            ;
        }
        Serial.println(F("VL53L0X API Simple Ranging example\n\n"));
      }

#. Erfassung und Anzeige der Messwerte in der Funktion ``loop()``. Kontinuierlich nimmt der Arduino eine Entfernungsmessung vor und zeigt diese, falls gültig, im seriellen Monitor an.

   .. code-block:: arduino
       
      void loop() {
        VL53L0X_RangingMeasurementData_t measure;
        Serial.print("Reading a measurement... ");
        lox.rangingTest(&measure, false);
        if (measure.RangeStatus != 4) {
          Serial.print("Distance (mm): ");
          Serial.println(measure.RangeMilliMeter);
        } else {
          Serial.println(" out of range ");
        }
        delay(100);
      }

Weitere Ideen
^^^^^^^^^^^^^^^^^^^^

- Integration des Sensors in eine Anzeige (wie ein OLED), um die Entfernungsdaten anzuzeigen.
- Verwenden der Entfernungsdaten, um andere Komponenten wie LEDs oder Summer auszulösen, wenn ein Objekt in einen bestimmten Bereich kommt.

Weitere Projekte
---------------------------
* :ref:`fun_tof_distance_monitor`
