.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

.. _fun_motion_triggered_relay:

Bewegungsgesteuertes Relais
==================================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/fun/05-fun_Motion_triggered_relay.mp4"  type="video/mp4">
      Ihr Browser unterstützt das Video-Tag nicht.
   </video>

Dieses Arduino-Projekt hat zum Ziel, eine mit einem Relais gesteuerte Lampe mithilfe eines passiven Infrarot-(PIR)-Sensors zu steuern. Sobald der PIR-Sensor eine Bewegung erkennt, wird das Relais aktiviert und die Lampe eingeschaltet. Die Lampe bleibt für 5 Sekunden nach der zuletzt erkannten Bewegung eingeschaltet.

.. warning ::
    Zur Demonstration verwenden wir ein Relais zur Steuerung eines RGB-LED-Moduls. In realen Anwendungsfällen ist diese Herangehensweise jedoch eventuell nicht die praktikabelste.
    
    **Beim Anschluss des Relais an andere Geräte in realen Anwendungen ist äußerste Vorsicht im Umgang mit HOHER Wechselspannung geboten. Unfachgemäße oder falsche Handhabung kann zu schweren Verletzungen oder sogar zum Tod führen. Daher richtet sich dieses Projekt an Personen, die sich mit HOHER Wechselspannung auskennen. Sicherheit hat stets oberste Priorität.**


1. Schaltkreis aufbauen
-----------------------------

.. image:: img/05-fun_Motion_triggered_relay_circuit.png
    :width: 90%

* :ref:`cpn_uno`
* :ref:`cpn_pir_motion`
* :ref:`cpn_relay`
* :ref:`cpn_rgb`


2. Code
-----------------------------

#. Öffnen Sie die Datei ``05-Motion_triggered_relay.ino`` im Verzeichnis ``ultimate-sensor-kit\fun_project\05-Motion_triggered_relay`` oder kopieren Sie diesen Code in die **Arduino IDE**.

   .. raw:: html
       
       <iframe src=https://create.arduino.cc/editor/sunfounder01/147bb59d-8127-46e3-b276-a721bcff08df/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


3. Code-Erklärung
-----------------------------

Das Projekt basiert auf der Fähigkeit des PIR-Bewegungssensors, Bewegungen zu erkennen. Bei erkannter Bewegung sendet der Sensor ein Signal an den Arduino, der das Relais aktiviert, wodurch wiederum eine Lampe eingeschaltet wird. Die Lampe bleibt für eine festgelegte Zeit (in diesem Fall 5 Sekunden) nach der letzten erkannten Bewegung an, sodass der Bereich kurzzeitig beleuchtet bleibt, auch wenn keine Bewegung mehr erfolgt.

1. **Initiale Einrichtung und Variablendeklarationen**

   In diesem Abschnitt werden Konstanten und Variablen definiert, die im gesamten Code verwendet werden. Wir legen die Pins für das Relais und den PIR-Sensor sowie eine Zeitverzögerungskonstante für die Bewegung fest. Außerdem gibt es eine Variable zur Verfolgung des letzten Zeitpunkts einer erkannten Bewegung und ein Flag zur Überwachung, ob eine Bewegung erkannt wurde.

   .. code-block:: arduino
   
      // Define the pin number for the relay
      const int relayPin = 9;
   
      // Define the pin number for the PIR sensor
      const int pirPin = 8;
   
      // Motion delay threshold in milliseconds
      const unsigned long MOTION_DELAY = 5000;
   
      unsigned long lastMotionTime = 0;  // Timestamp of the last motion detection
      bool motionDetected = false;       // Flag to track if motion is detected
   
   

2. **Konfiguration der Pins in der setup() Funktion**

   In der ``setup()`` Funktion konfigurieren wir die Pinmodi für das Relais und den PIR-Sensor und initialisieren das Relais so, dass es zu Beginn ausgeschaltet ist.

   .. code-block:: arduino
   
      void setup() {
        pinMode(relayPin, OUTPUT);    // Set relayPin as an output pin
        pinMode(pirPin, INPUT);       // Set the PIR pin as an input
        digitalWrite(relayPin, LOW);  // Turn off the relay initially
      }

3. **Hauptlogik in der loop() Funktion**

   Die ``loop()`` Funktion enthält die Hauptlogik. Wenn der PIR-Sensor eine Bewegung erkennt, sendet er ein ``HIGH`` Signal, schaltet das Relais ein und aktualisiert die ``lastMotionTime``. Wenn innerhalb der festgelegten Verzögerung (in diesem Fall 5 Sekunden) keine Bewegung mehr erkannt wird, wird das Relais ausgeschaltet.
   
   Diese Methode gewährleistet, dass die Lampe auch bei sporadischen oder kurzen Bewegungen für mindestens 5 Sekunden nach der letzten erkannten Bewegung eingeschaltet bleibt und somit eine gleichmäßige Beleuchtungsdauer erreicht wird.

   .. code-block:: arduino
   
      void loop() {
        if (digitalRead(pirPin) == HIGH) {
          lastMotionTime = millis();     // Update the last motion time
          digitalWrite(relayPin, HIGH);  // Turn on the relay (and hence the light)
          motionDetected = true;
        }
   
        // If motion was detected earlier and 5 seconds have elapsed, turn off the relay
        if (motionDetected && (millis() - lastMotionTime >= MOTION_DELAY)) {
          digitalWrite(relayPin, LOW);  // Turn off the relay
          motionDetected = false;
        }
      }
   
