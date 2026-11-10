.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

.. _cpn_gas:

Gas-/Rauch-Sensormodul (MQ2)
=====================================

.. image:: img/02_mq2_gas_module.png
    :width: 350
    :align: center

Einleitung
---------------------------
Der MQ-2-Sensor ist ein vielseitiger Gassensor, der eine breite Palette von Gasen wie Alkohol, Kohlenmonoxid, Wasserstoff, Isobuten, Flüssiggas, Methan, Propan und Rauch erkennen kann. Aufgrund seiner kostengünstigen und benutzerfreundlichen Eigenschaften ist er besonders bei Einsteigern beliebt.

Funktionsprinzip
---------------------------
Der MQ-2-Sensor basiert auf dem Prinzip der Widerstandsänderung in Gegenwart verschiedener Gase. Wenn das Zielgas mit dem erhitzten MOS-Material (Metalloxid-Halbleiter) in Kontakt kommt, finden Oxidations- oder Reduktionsreaktionen statt, die den Widerstand des MOS-Materials verändern. Es ist bemerkenswert, dass der MQ-2-Sensor mehrere Gase erkennen kann, jedoch nicht in der Lage ist, zwischen ihnen zu unterscheiden. Dies ist eine übliche Eigenschaft der meisten Gassensoren.

Der Sensor verfügt über ein integriertes Potentiometer, das es ermöglicht, die digitale Ausgangsschwelle (D0) einzustellen. Überschreitet die Gaskonzentration in der Luft einen bestimmten Schwellenwert, ändert sich der Widerstand des Sensors. Diese Widerstandsänderung wird dann in ein elektrisches Signal umgewandelt, das von einem Arduino-Board ausgelesen werden kann.

Anwendungsbeispiele
---------------------------

**Benötigte Hardware-Komponenten**

- Arduino Uno R4 oder R3 Board * 1
- Gas-Sensormodul (MQ2) * 1
- Jumperkabel

**Schaltungsaufbau**

.. image:: img/02_mq2_sensor_circuit.png
    :width: 520
    :align: center

.. raw:: html
    
    <br/><br/>   

Programmcode
^^^^^^^^^^^^^^^^^^^^
.. raw:: html

    <iframe src=https://create.arduino.cc/editor/sunfounder01/1de900bf-d3bf-411a-8f6b-23e53b704bf5/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/02-component_gas.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>
   <br/><br/>   

Code-Erläuterung
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

1. Die erste Codezeile ist eine konstante Ganzzahldeklaration für den Sensorpin des Gassensors. Wir verwenden den analogen Pin A0, um die Ausgabe des Gassensors auszulesen.

   .. code-block:: arduino
   
      const int sensorPin = A0;

2. In der ``setup()``-Funktion initialisieren wir unsere serielle Kommunikation mit einer Baudrate von 9600. Dies ist notwendig, um die Messwerte des Gassensors im seriellen Monitor anzuzeigen.

   .. code-block:: arduino
   
      void setup() {
        Serial.begin(9600);  // Start serial communication at 9600 baud rate
      }

3. In der ``loop()``-Funktion lesen wir kontinuierlich den Analogwert des Gassensors aus und zeigen ihn im seriellen Monitor an. Wir verwenden die Funktion ``analogRead()`` zum Auslesen des Analogwerts. Anschließend warten wir 50 Millisekunden bis zur nächsten Messung. Diese Verzögerung gibt dem seriellen Monitor etwas Zeit zur Datenverarbeitung.

   .. code-block:: arduino
   
      void loop() {
        Serial.print("Analog output: ");
        Serial.println(analogRead(sensorPin));  // Read the analog value of the gas sensor and print it to the serial monitor
        delay(50);                             // Wait for 50 milliseconds
      }

.. note:: 

  Der MQ2 ist ein heizgetriebener Sensor, der normalerweise vor der Verwendung eine Vorheizphase benötigt. Während dieser Vorheizphase sind die Sensormesswerte in der Regel hoch und nehmen allmählich ab, bis sie sich stabilisieren.

Weitere Ideen
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- Hinzufügen eines visuellen oder akustischen Warnsystems (mittels LEDs oder eines Buzzers), das auslöst, wenn die Gaskonzentration bestimmte Schwellenwerte überschreitet.


Weitere Projekte
---------------------------
* :ref:`fun_gas_leak_alarm`
