.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

.. _cpn_flame:

Flammen-Sensormodul
==========================

.. image:: img/03_flame_module.jpg
    :width: 400
    :align: center

Einleitung
---------------------------
Das Flammen-Sensormodul ist in der Lage, die Anwesenheit von Feuer oder Flammen zu detektieren. Es erkennt Brände hauptsächlich durch die Erfassung der von Flammen oder Feuer emittierten Infrarotstrahlung. Es wird weitgehend in Brandmeldesystemen in Privathaushalten und in der Industrie verwendet.

Funktionsprinzip
---------------------------
Das Flammen-Sensormodul arbeitet auf Basis der Infrarotdetektion. Der Sensor besitzt einen IR-Empfänger, der die von den Flammen emittierte Infrarotstrahlung erkennt. Wenn Feuer brennt, emittiert es eine geringe Menge an infrarotem Licht, das von der Fotodiode (IR-Empfänger) auf dem Sensor empfangen wird. Mittels eines Operationsverstärkers wird dann die Spannungsänderung am IR-Empfänger überprüft, sodass bei erkanntem Feuer der Ausgangspin (DO) 0V (LOW) liefert und bei Nichterkennung 5V (HIGH).

Anwendungsbeispiele
---------------------------

**Benötigte Hardware-Komponenten**

- Arduino Uno R4 oder R3 Board * 1
- Flammen-Sensormodul * 1
- Jumperkabel

**Schaltungsaufbau**

.. image:: img/03_flame_module_circuit.png
    :width: 400
    :align: center

.. raw:: html
    
    <br/><br/>   

Programmcode
^^^^^^^^^^^^^^^^^^^^

.. raw:: html

   <iframe src=https://create.arduino.cc/editor/sunfounder01/7529b311-3763-4b62-aa1c-a63e41871856/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/03-component_flame.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>
   <br/><br/>  

Code-Erläuterung
^^^^^^^^^^^^^^^^^^^^

1. Die erste Codezeile definiert eine Konstante für den Pin des Flammen-Sensors. Hier verwenden wir den digitalen Pin 7, um die Ausgabe vom Flammen-Sensor zu lesen.

   .. code-block:: arduino
   
      const int sensorPin = 7;

2. Die ``setup()`` Funktion initialisiert den Pin des Flammen-Sensors als Eingang und den eingebauten LED-Pin als Ausgang. Zudem wird die serielle Kommunikation mit einer Baudrate von 9600 für die Ausgabe von Nachrichten im seriellen Monitor gestartet.

   .. code-block:: arduino
   
      void setup() {
        pinMode(sensorPin, INPUT);     // Set the flame sensor pin as input
        pinMode(LED_BUILTIN, OUTPUT);  // Set the built-in LED pin as output
        Serial.begin(9600);            // Initialize the serial monitor at a baud rate of 9600
      }

3. In der ``loop()`` Funktion wird kontinuierlich der Status des Flammen-Sensors überprüft. Erkennt der Sensor eine Flamme, wird die integrierte LED eingeschaltet und eine Nachricht im seriellen Monitor ausgegeben. Wird keine Flamme erkannt, wird die LED ausgeschaltet und eine andere Nachricht ausgegeben. Der Vorgang wiederholt sich alle 100 Millisekunden.

   .. code-block:: arduino
   
      void loop() {
        // Check if the sensor is detecting a fire
        if (digitalRead(sensorPin) == 0) {
          digitalWrite(LED_BUILTIN, HIGH);  // Turn on the built-in LED
          Serial.println("** Fire detected!!! **");
        } else {
          digitalWrite(LED_BUILTIN, LOW);  // Turn off the built-in LED
          Serial.println("No Fire detected");
        }
        delay(100);
      }

Weitere Ideen
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- Den Code so modifizieren, dass ein Summer oder Alarm ausgelöst wird, wenn eine Flamme erkannt wird.

- Zusätzlich zum Flammen-Sensor einen Rauchsensor integrieren, um die Branderkennung zu verbessern.

- Den **analogen Ausgang** anstelle des einfachen digitalen HIGH/LOW verwenden. Dazu den **AO** Pin verwenden.

Weitere Projekte
---------------------------
* :ref:`iot_Flame`
