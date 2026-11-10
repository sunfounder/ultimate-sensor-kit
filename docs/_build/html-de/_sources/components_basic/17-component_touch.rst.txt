
.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

.. _cpn_touch:

Berührungs-Sensormodul
==========================

.. image:: img/17_touch_sensor_moudle.png
    :width: 200
    :align: center

Einführung
---------------------------
Der Berührungsschalter (auch Touch-Button oder Touch-Schalter genannt) findet breite Anwendung in verschiedenen Geräten, wie beispielsweise berührungsempfindlichen Lampen. Er übernimmt dieselben Funktionen wie ein herkömmlicher Knopf, verleiht dem Produkt jedoch ein sauberes, modernes Erscheinungsbild.

Funktionsprinzip
---------------------------
Das Modul basiert auf einem Berührungssensor-IC (TTP223B) und fungiert als kapazitiver Touch-Schalter. Im Ruhezustand gibt das Modul ein niedriges Signal bei geringem Stromverbrauch aus. Bei Berührung wechselt das Ausgangssignal auf ein hohes Niveau und kehrt nach Loslassen des Fingers wieder auf ein niedriges Niveau zurück.

Funktionsweise des kapazitiven Touch-Schalters:

Der kapazitive Touch-Schalter besteht aus verschiedenen Schichten – einer oberen Isolierschicht, gefolgt von der Berührungsplatte, einer weiteren Isolierschicht und schließlich einer Erdungsplatte.

.. image:: img/17_touch_sensor_moudle_principle.jpeg
    :width: 400
    :align: center

In der Praxis kann ein kapazitiver Sensor auf einer doppelseitigen Leiterplatte realisiert werden, wobei eine Seite als Sensorfläche und die gegenüberliegende Seite als Erdungsplatte dient. Bei angelegter Spannung laden sich beide Platten auf. Im Gleichgewicht entspricht die Spannung der Platten der des Stromnetzes.

Der Detektorschaltkreis beinhaltet einen Oszillator, dessen Frequenz von der Kapazität der Sensorfläche abhängt. Nähert sich ein Finger der Sensorfläche, verändert die zusätzliche Kapazität die Frequenz des internen Oszillators. Der Detektorschaltkreis überwacht in festgelegten Intervallen die Oszillatorfrequenz und löst bei Überschreiten eines bestimmten Schwellenwerts ein Tastendruckereignis aus.

Anwendungsbeispiele
---------------------------

**Hardware-Komponenten**

- Arduino Uno R4 oder R3 Board * 1
- Berührungs-Sensormodul * 1
- Jumperkabel


**Schaltungsaufbau**

.. image:: img/17_touch_sensor_moudle_circuit.png
    :width: 400
    :align: center

.. raw:: html
    
    <br/><br/>   

Programmcode
^^^^^^^^^^^^^^^^^^^^

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/3a0a411f-7bdc-43f0-82e9-5978e4167dd7/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/17-component_touch.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>
   <br/><br/>  

Code-Erklärung
^^^^^^^^^^^^^^^^^^^^

#. Definition der benötigten Variablen. Zunächst wird die Pinnummer definiert, an die der Berührungssensor angeschlossen ist.

   .. code-block:: arduino

      const int sensorPin = 7;

#. Initialisierung in der ``setup()``-Funktion. Hier legen wir fest, dass der Sensor-Pin für den Eingang und die integrierte LED für den Ausgang genutzt werden. Zudem wird die serielle Kommunikation gestartet, um Nachrichten an den seriellen Monitor zu senden.

   .. code-block:: arduino

      void setup() {
        pinMode(sensorPin, INPUT);
        pinMode(LED_BUILTIN, OUTPUT);
        Serial.begin(9600);
      }

#. Kontinuierlich überprüft das Arduino, ob der Berührungssensor aktiviert ist. Bei Berührung leuchtet die LED auf und eine Meldung "Touch detected!" wird ausgegeben. Ist keine Berührung vorhanden, wird die LED ausgeschaltet und die Meldung "No touch detected..." erscheint. Eine Verzögerung verhindert, dass der Sensor zu schnell abgefragt wird.

   .. code-block:: arduino

      void loop() {
        if (digitalRead(sensorPin) == 1) {
          digitalWrite(LED_BUILTIN, HIGH);
          Serial.println("Touch detected!");
        } else {
          digitalWrite(LED_BUILTIN, LOW);
          Serial.println("No touch detected...");
        }
        delay(100);
      }

Weitere Ideen
^^^^^^^^^^^^^^^^^^^^

- Verwendung unterschiedlicher LED-Farben zur Anzeige einer Berührung
- Der Berührungssensor könnte auch zur Steuerung komplexerer Elemente wie einem Motor oder einem Relais verwendet werden.

Weitere Projekte
---------------------------
* :ref:`fun_touch_toggle_light`

