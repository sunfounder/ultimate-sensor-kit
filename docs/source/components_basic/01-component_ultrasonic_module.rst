.. _cpn_ultrasonic:

Ultraschall-Sensormodul (HC-SR04)
=================================

.. image:: img/01_ultrasonic.png
    :width: 400
    :align: center

Einleitung
---------------------------
Das Ultraschall-Sensormodul (HC-SR04) ist ein Sensor, der mithilfe von Ultraschallwellen Entfernungen zwischen 2 cm und 4 Metern messen kann. Es wird häufig in Robotik- und Automatisierungsprojekten eingesetzt, um Objekte zu erkennen und Entfernungen zu messen. Das Modul besteht aus einem Ultraschall-Sender und -Empfänger, die gemeinsam Ultraschallwellen senden und empfangen.

.. _cpn_ultrasonic_principle:

Funktionsprinzip
---------------------------
Das Modul umfasst Ultraschallsender, Empfänger und Steuerschaltung. Die grundlegenden Prinzipien sind wie folgt:

#. Ein IO-Flipflop verarbeitet ein High-Level-Signal von mindestens 10us.

#. Das Modul sendet automatisch acht 40-kHz-Signale aus und prüft, ob ein Pulssignal zurückkehrt.

#. Wenn das Signal zurückkehrt und das High-Level passiert, beträgt die Ausgabe-IO-Dauer die Zeit vom Senden der Ultraschallwelle bis zu ihrer Rückkehr. Hier gilt: Testentfernung = (High-Level-Zeit x Schallgeschwindigkeit (340 m/s) / 2.

Das Timing-Diagramm ist unten dargestellt.

.. image:: img/01_ultrasonic_principle.png

Es genügt, einen kurzen 10us-Impuls für den Trigger-Eingang zu liefern, um die Entfernungsmessung zu starten. Das Modul sendet dann eine 8-Zyklus-Serie von Ultraschallwellen mit 40 kHz aus und erhebt sein Echo. Die Entfernung kann durch das Zeitintervall zwischen dem Senden des Trigger-Signals und dem Empfang des Echo-Signals berechnet werden.

.. note::
    Es wird empfohlen, einen Messzyklus von mehr als 60 ms zu verwenden, um Signalüberlappungen zwischen Trigger- und Echo-Signal zu vermeiden.

Formel: 
    - us / 58 = Zentimeter 
    - us / 148 = Zoll
    - Entfernung = High-Level-Zeit \* Schallgeschwindigkeit (340m/s) / 2; 


Anwendungsbeispiele
---------------------------

**Benötigte Hardware-Komponenten**

- Arduino Uno R4 oder R3-Board * 1
- Ultraschall-Sensormodul * 1
- Jumperkabel

**Schaltungsaufbau**

.. image:: img/01-ultrasonic_circuit.png
    :width: 400
    :align: center

.. raw:: html
    
    <br/><br/>   

Programmcode
^^^^^^^^^^^^^^^^^^^^

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/80624dbe-89ff-4c5b-9ca9-fb5053a0edbb/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/01-component_ultrasonic_module.mp4"  type="video/mp4">
      Ihr Browser unterstützt das Video-Tag nicht.
   </video>
   <br/> <br/> 



Programmcode Erklärung
^^^^^^^^^^^^^^^^^^^^^^^^

1. Pin-Deklaration:

   Beginnen Sie mit der Definition der Pins für den Ultraschallsensor. ``echoPin`` und ``trigPin`` werden als Ganzzahlen deklariert und ihre Werte entsprechen den physischen Anschlüssen auf dem Arduino-Board.

   .. code-block:: arduino

      const int echoPin = 3;
      const int trigPin = 4;

2. ``setup()`` Funktion:

   Die ``setup()`` Funktion initialisiert die serielle Kommunikation, setzt die Pin-Modi und gibt eine Meldung aus, um anzuzeigen, dass der Ultraschallsensor bereit ist.

   .. code-block:: arduino

      void setup() {
        Serial.begin(9600);
        pinMode(echoPin, INPUT);
        pinMode(trigPin, OUTPUT);
        Serial.println("Ultrasonic sensor:");
      }

3. ``loop()`` Funktion:

   Die ``loop()`` Funktion liest die Entfernung vom Sensor und zeigt sie auf dem seriellen Monitor an. Anschließend erfolgt eine Verzögerung von 400 Millisekunden, bevor der Vorgang wiederholt wird.

   .. code-block:: arduino

      void loop() {
        float distance = readDistance();
        Serial.print(distance);
        Serial.println(" cm");
        delay(400);
      }

4. ``readDistance()`` Funktion:

   Die ``readDistance()`` Funktion aktiviert den Ultraschallsensor und berechnet die Entfernung anhand der Zeit, die das Signal für den Hin- und Rückweg benötigt.

   .. code-block:: arduino

      float readDistance() {
        digitalWrite(trigPin, LOW);   // Set trig pin to low to ensure a clean pulse
        delayMicroseconds(2);         // Delay for 2 microseconds
        digitalWrite(trigPin, HIGH);  // Send a 10 microsecond pulse by setting trig pin to high
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);  // Set trig pin back to low
        float distance = pulseIn(echoPin, HIGH) / 58.00;  // Formula: (340m/s * 1us) / 2
        return distance;
      }


Zusätzliche Ideen
^^^^^^^^^^^^^^^^

- Anzeige der Entfernung auf einem LCD-Bildschirm statt auf dem seriellen Monitor
- Hinzufügen von LEDs, die leuchten, wenn ein Objekt innerhalb einer bestimmten Entfernung ist

Weitere Projekte
---------------------------
* :ref:`fun_smart_trashcan`



