.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

.. _cpn_pir_motion:

PIR-Bewegungsmelder-Modul (HC-SR501)
=====================================

.. image:: img/13_pir_module.png
    :width: 300
    :align: center

Einleitung
---------------------------
Der Passive Infrarot (PIR) Bewegungsmelder ist ein Sensor zur Erfassung von Bewegungen. Er findet häufig Einsatz in Sicherheitssystemen und automatischen Beleuchtungsanlagen. Der Sensor besitzt zwei Schlitze, die Infrarotstrahlung erkennen. Passiert ein Objekt, etwa eine Person, den Erfassungsbereich des Sensors, so registriert dieser eine Veränderung der Infrarotstrahlung und löst ein Ausgangssignal aus.

Funktionsprinzip
---------------------------
Der PIR-Sensor ist in zwei Schlitze unterteilt, die mit einem Differenzverstärker verbunden sind. Wenn ein stationäres Objekt vor dem Sensor ist, empfangen beide Schlitze dieselbe Menge an Strahlung, und der Ausgang bleibt neutral. Bewegt sich jedoch ein Objekt vor dem Sensor, nimmt einer der Schlitze mehr Strahlung auf als der andere, was zu Schwankungen im Ausgangssignal führt. Diese Veränderung der Ausgangsspannung ist ein Indikator für erkannte Bewegung.

.. image:: img/13_pir_working_principle.jpg
    :width: 500
    :align: center

Nach der Verkabelung des Sensormoduls erfolgt eine einminütige Initialisierung. Während dieser Zeit kann das Modul 0 bis 3-mal in Abständen ein Signal ausgeben. Danach geht das Modul in den Standby-Modus. Um Fehlbedienungen durch störende Signale zu vermeiden, sollte der Sensor von Lichtquellen und anderen Störeinflüssen ferngehalten werden. Am besten wird der Sensor in einer windgeschützten Umgebung eingesetzt, da auch Wind die Sensorik beeinträchtigen kann.

.. image:: img/13_pir_module_back.png
    :width: 350
    :align: center

.. raw:: html
    
    <br/><br/> 

Reichweiteneinstellung
^^^^^^^^^^^^^^^^^^^^^^^^
Durch Drehen des Potentiometers für die Reichweiteneinstellung im Uhrzeigersinn wird die Erfassungsreichweite erhöht, mit einem Maximalbereich von etwa 0-7 Metern. Dreht man es gegen den Uhrzeigersinn, verringert sich die Reichweite auf etwa 0-3 Meter.

Verzögerungseinstellung
^^^^^^^^^^^^^^^^^^^^^^^^
Dreht man das Potentiometer für die Verzögerungseinstellung im Uhrzeigersinn, erhöht sich die Verzögerungszeit. Die maximale Verzögerungszeit kann bis zu 300 Sekunden betragen. In entgegengesetzter Richtung verringert sich die Verzögerung auf ein Minimum von 5 Sekunden.

Zwei Trigger-Modi
^^^^^^^^^^^^^^^^^^^^^^^^
Durch Verwendung einer Jumperkappe können verschiedene Modi ausgewählt werden.

* H: Wiederholbarer Trigger-Modus. Nach der Erfassung einer Bewegung gibt das Modul ein hohes Signal aus. Während der anschließenden Verzögerungszeit bleibt das Ausgangssignal bei erneuter Bewegungserkennung hoch.
* L: Nicht wiederholbarer Trigger-Modus. Nach der Erfassung einer Bewegung gibt das Modul ein hohes Signal aus, das nach Ablauf der Verzögerungszeit automatisch auf ein niedriges Niveau zurückfällt.

Anwendungsbeispiele
---------------------------

**Hardware-Komponenten**

- Arduino Uno R4 oder R3 Platine * 1
- PIR-Bewegungsmelder-Modul * 1
- Jumperkabel


**Schaltungsaufbau**

.. note::
    Die Pin-Markierungen sind durch die Fresnel-Linse verdeckt. Zum Ansehen kann diese geöffnet werden.

.. image:: img/13_pir_module_circuit.png
    :width: 400
    :align: center

.. raw:: html
    
    <br/><br/>   

Programmcode 
^^^^^^^^^^^^^^^^^^^^

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/4a9b7041-dac5-4d8a-8941-fa0d2d6313d8/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/13-component_pir_motion.mp4"  type="video/mp4">
      Ihr Browser unterstützt das Video-Tag nicht.
   </video>
   <br/><br/>  

Code-Erklärung
^^^^^^^^^^^^^^^^^^^^

1. Einrichten des PIR-Sensor-Pins. Der Pin für den PIR-Sensor wird als Pin 2 definiert.

   .. code-block:: arduino

      const int pirPin = 2;
      int state = 0;

2. Initialisierung des PIR-Sensors. In der ``setup()`` Funktion wird der Pin des PIR-Sensors als Eingang definiert. Dadurch kann der Arduino den Status des PIR-Sensors lesen.

   .. code-block:: arduino

      void setup() {
        pinMode(pirPin, INPUT);
        Serial.begin(9600);
      }

3. Auslesen des PIR-Sensors und Anzeige der Ergebnisse. In der ``loop()`` Funktion wird der Status des PIR-Sensors kontinuierlich ausgelesen. 

   .. code-block:: arduino

      void loop() {
        state = digitalRead(pirPin);
        if (state == HIGH) {
          Serial.println("Somebody here!");
        } else {
          Serial.println("Monitoring...");
          delay(100);
        }
      }

   Wenn der Status ``HIGH`` ist, also eine Bewegung erkannt wird, erscheint die Meldung "Somebody here!" im seriellen Monitor. Andernfalls wird "Monitoring..." angezeigt.

Weitere Ideen
^^^^^^^^^^^^^^^^^^^^

- Einbindung einer LED, die bei erkannter Bewegung aufleuchtet oder blinkt. Dies bietet eine visuelle Rückmeldung zusätzlich zur Nachricht im seriellen Monitor.
- Integration eines Summers, der bei Bewegungserkennung einen Alarmton ausgibt.

Weitere Projekte
---------------------------
* :ref:`fun_motion_triggered_relay`
* :ref:`iot_Intrusion_alert_system`

