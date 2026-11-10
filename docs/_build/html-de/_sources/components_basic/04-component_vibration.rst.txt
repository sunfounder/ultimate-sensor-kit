.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

.. _cpn_vibration:

Vibrationssensor-Modul (SW-420)
=====================================

.. image:: img/04_sw420_vibration_module.png
    :width: 400
    :align: center

Einführung
---------------------------
Das SW-420 Vibrationssensor-Modul ist in der Lage, Vibrationen oder Erschütterungen auf einer Oberfläche zu erfassen. Es kann für verschiedene Zwecke eingesetzt werden, wie z.B. zur Erkennung von Türklopfen, Maschinenfehlern, Autounfällen oder Alarmanlagen. Das Modul arbeitet mit einer Spannung von 3,3 V bis 5 V und verfügt über drei Peripheriegeräte: zwei LEDs, eine für den Betriebsstatus und die andere für den Sensorausgang, sowie ein Potentiometer zur Feineinstellung des Ansprechpunktes für Vibrationen.

Funktionsprinzip
---------------------------
Das SW-420 Vibrationssensor-Modul setzt sich aus einem SW-420 Vibrationsschalter und einem LM393 Spannungsvergleicher zusammen. Der SW-420 Vibrationsschalter enthält eine Feder und einen Stab innerhalb eines Rohres. Bei Vibrationen kommt die Feder mit dem Stab in Kontakt und schließt den Stromkreis. Der im Modul integrierte Vibrationssensor erfasst diese Schwingungen und wandelt sie in elektrische Signale um. Der LM393 Vergleicherchip vergleicht diese Signale dann mit einer Referenzspannung, die am Potentiometer eingestellt wird. Überschreitet die Amplitude des Signals diese Referenzspannung, gibt der Vergleicher ein hohes Signal (1) aus, andernfalls ein niedriges (0).

Anwendungsbeispiele
---------------------------

**Benötigte Hardware-Komponenten**

- Arduino Uno R4 oder R3 Board * 1
- Vibrationssensor-Modul (SW-420) * 1
- Jumperkabel

**Schaltungsaufbau**

.. image:: img/04_vibration_module_circuit.png
    :width: 400
    :align: center

.. raw:: html
    
    <br/><br/>   

Programmcode
^^^^^^^^^^^^^^^^^^^^

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/690d9d6c-1049-48cd-99af-7bc6cd9c1ae4/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/04-component_vibration.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>
   <br/><br/>  

Code-Erklärung
^^^^^^^^^^^^^^^^^^^^

1. Die erste Zeile des Codes deklariert einen konstanten Integer für den Vibrationssensor-Anschluss. Der digitale Pin 7 wird verwendet, um die Ausgabe des Vibrationssensors zu lesen.

   .. code-block:: arduino
   
      const int sensorPin = 7;

2. In der ``setup()``-Funktion initialisieren wir die serielle Kommunikation mit einer Baudrate von 9600, um die Messwerte des Vibrationssensors im seriellen Monitor anzuzeigen. Außerdem wird der Vibrationssensor-Anschluss als Eingang definiert.

   .. code-block:: arduino
   
      void setup() {
        Serial.begin(9600);         // Start serial communication at 9600 baud rate
        pinMode(sensorPin, INPUT);  // Set the sensorPin as an input pin
      }

3. In der ``loop()``-Funktion prüfen wir kontinuierlich, ob vom Sensor Vibrationen erkannt werden. Bei Erkennung einer Vibration wird "Detected vibration..." im seriellen Monitor ausgegeben. Wird keine Vibration erkannt, wird "..." ausgegeben. Die Schleife wiederholt sich alle 100 Millisekunden.

   .. code-block:: arduino
   
      void loop() {
        if (digitalRead(sensorPin)) {               // Check if there is any vibration detected by the sensor
          Serial.println("Detected vibration...");  // Print "Detected vibration..." if vibration detected
        } 
        else {
          Serial.println("...");  // Print "..." otherwise
        }
        // Add a delay to avoid flooding the serial monitor
        delay(100);
      }

Weitere Ideen
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- Anschluss einer LED, die bei erkannter Vibration leuchtet
- Auslösen eines Alarms oder Buzzers bei Vibrationserkennung

Weitere Projekte
---------------------------
* :ref:`iot_Intrusion_alert_system`
