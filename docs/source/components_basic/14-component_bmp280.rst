.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

.. _cpn_bmp280:

Temperatur-, Feuchtigkeits- & Drucksensor (BMP280)
===============================================================

.. image:: img/14_gy_bme280_3.3_module.png
    :width: 300
    :align: center

Einleitung
---------------------------
Das GY-BMP280-3.3 Präzisionsmodul für die atmosphärische Druckmessung ist ein Gerät, das in der Lage ist, Luftdruck und Temperatur mit hoher Genauigkeit zu erfassen. Es eignet sich hervorragend zur Überwachung von Wetterbedingungen oder für Projekte, die Daten zur Höhe oder zum barometrischen Druck nutzen.

Funktionsprinzip
---------------------------
Das GY-BMP280-3.3 Modul arbeitet mit einem BMP280-Sensor von Bosch, der sowohl den Druck als auch die Temperatur messen kann. Innerhalb einer abgedichteten Metallkammer befinden sich ein piezoresistiver Drucksensor und ein Thermistor. Der piezoresistive Sensor ändert seinen Widerstand je nach dem auf die Kammer ausgeübten Druck, während der Thermistor seinen Widerstand in Abhängigkeit von der Innentemperatur der Kammer ändert. Das Modul beinhaltet einen integrierten Schaltkreis, der diese Widerstandswerte in digitale Signale umwandelt und diese über die I2C- oder SPI-Schnittstelle an den Arduino weiterleitet.

Anwendungsbeispiele
---------------------------

**Hardware-Komponenten**

- Arduino Uno R4 oder R3 Platine * 1
- Temperatur-, Feuchtigkeits- & Drucksensor (GY-BMP280-3.3) * 1
- Jumperkabel

**Schaltungsaufbau**

.. image:: img/14_gy_bme280_3.3_module_circuit.png
    :width: 550
    :align: center

.. raw:: html
    
    <br/><br/>   

Programmcode
^^^^^^^^^^^^^^^^^^^^

.. note::
   Um die Bibliothek zu installieren, verwenden Sie den Arduino-Bibliotheksmanager und suchen Sie nach **"Adafruit BMP280"**, um es zu installieren.

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/e1f581e4-76c8-48a0-b1cc-d15604267183/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/14-component_bmp280.mp4"  type="video/mp4">
      Ihr Browser unterstützt das Video-Tag nicht.
   </video>
   <br/><br/>  

Code-Erläuterung
^^^^^^^^^^^^^^^^^^^^

1. Einbindung der Bibliotheken und Initialisierung. Die erforderlichen Bibliotheken werden eingebunden und der BMP280-Sensor wird für die Kommunikation über die I2C-Schnittstelle initialisiert.

   .. note::
      Zur Installation der Bibliothek nutzen Sie den Arduino-Bibliotheksmanager und suchen nach **"Adafruit BMP280"** und installieren Sie es.

   - Adafruit BMP280 Bibliothek: Diese Bibliothek bietet eine benutzerfreundliche Schnittstelle für den BMP280-Sensor und ermöglicht es dem Benutzer, Temperatur, Druck und Höhe auszulesen. 

   - Wire.h: Wird für die I2C-Kommunikation verwendet.

   .. raw:: html
    
    <br/>

   .. code-block:: arduino
    
      #include <Wire.h>
      #include <Adafruit_BMP280.h>
      #define BMP280_ADDRESS 0x76
      Adafruit_BMP280 bmp;  // use I2C interface

2. Die Funktion ``setup()`` initialisiert die serielle Kommunikation, prüft den BMP280-Sensor und konfiguriert ihn mit den Standard-Einstellungen.

   .. code-block:: arduino

      void setup() {
        Serial.begin(9600);
        while (!Serial) delay(100);
        Serial.println(F("BMP280 test"));
        unsigned status;
        status = bmp.begin(BMP280_ADDRESS);
        // ... (rest of the setup code)

3. Die Funktion ``loop()`` liest kontinuierlich Daten für Temperatur, Druck und Höhe vom BMP280-Sensor und gibt diese auf dem Serial Monitor aus.

   .. code-block:: arduino

      void loop() {
        // ... (read and print temperature, pressure, and altitude data)
        delay(2000);  // 2-second delay between readings.
      }

Weitere Ideen
^^^^^^^^^^^^^^^^^^^^

- Integrieren Sie ein LCD-Displaymodul, um die Messwerte zusätzlich oder alternativ auf dem Serial Monitor anzuzeigen.
- Legen Sie Schwellenwerte für Temperatur und Druck fest. Verwenden Sie einen Summer oder eine LED, um bei Überschreitung dieser Grenzwerte zu alarmieren.

Weitere Projekte
---------------------------
* :ref:`iot_weather_monitor`
