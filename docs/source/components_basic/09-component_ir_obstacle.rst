.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

.. _cpn_ir_obstacle:

IR-Hindernisvermeidungssensor-Modul
===================================

.. image:: img/09_IR_obstacle_module.png
    :width: 400
    :align: center

Einleitung
------------
Ein IR-Hindernisvermeidungssensor funktioniert nach dem Prinzip der Infrarotreflexion, um Hindernisse zu detektieren. Wenn kein Objekt im Weg ist, empfängt der Infrarotempfänger keine Signale. Befindet sich jedoch ein Hindernis im Weg, das das Infrarotlicht reflektiert, dann nimmt der Infrarotempfänger Signale auf.

Funktionsweise
----------------
Ein Hindernisvermeidungssensor setzt sich in der Regel aus einem Infrarotsender, einem Infrarotempfänger und einem Potentiometer zusammen. Je nach Reflektionseigenschaften des Objekts schwächt der ausgesendete Infrarotstrahl mit zunehmender Entfernung ab und verschwindet letztlich. Trifft der Strahl auf ein Hindernis, wird er zurück zum Infrarotempfänger reflektiert. Dieser erkennt das Signal und signalisiert ein Hindernis im Pfad. Die Erfassungsreichweite kann über das integrierte Potentiometer justiert werden.

.. image:: img/09_IR_obstacle_module_1.png
    :width: 600
    :align: center

Anwendungsbeispiele
--------------------

**Benötigte Hardware-Komponenten**

- Arduino Uno R4 oder R3 Board * 1
- IR-Hindernisvermeidungssensor-Modul * 1
- Verbindungskabel

**Schaltungsaufbau**

.. image:: img/09_IR_obstacle_module_circuit.png
    :width: 400
    :align: center

.. raw:: html
    
    <br/><br/>   

Programmcode
^^^^^^^^^^^^^^^^

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/f0e8f3a8-c3a8-4ded-a8ec-67de5a4076f6/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/09-component_ir_obstacle.mp4"  type="video/mp4">
      Ihr Browser unterstützt das Video-Tag nicht.
   </video>
   <br/><br/>  

Code-Erläuterung
^^^^^^^^^^^^^^^^^^^^^^^^^^

1. Sensoranschlusspin festlegen:

   .. code-block:: arduino

     const int sensorPin = 2;

   Schließen Sie den Ausgangspin des Sensors an den Arduino-Pin 2 an.

2. Serielle Kommunikation initialisieren und Sensorpin als Eingang definieren:

   .. code-block:: arduino

     void setup() {
       pinMode(sensorPin, INPUT);  
       Serial.begin(9600);
     }

   Initialisieren Sie die serielle Kommunikation mit einer Baudrate von 9600 für die Ausgabe auf dem seriellen Monitor.
   Setzen Sie den Sensorpin als Eingang, um das Signal einzulesen.

3. Sensorwert auslesen und im seriellen Monitor anzeigen:

   .. code-block:: arduino

     void loop() {
       Serial.println(digitalRead(sensorPin));
       delay(50); 
     }
   
   Lesen Sie kontinuierlich den digitalen Wert vom Sensorpin mit ``digitalRead()`` und geben Sie diesen Wert mit ``Serial.println()`` im seriellen Monitor aus.
   Fügen Sie eine 50-ms-Pause zwischen den Ausgaben ein, um die Ansicht zu verbessern.

.. note::

   Sollte der Sensor nicht wie erwartet arbeiten, justieren Sie den Infrarotsender und -empfänger so, dass sie parallel zueinander stehen. Zusätzlich können Sie die Erfassungsreichweite mittels des eingebauten Potentiometers anpassen.

Weitere Ideen
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- Integrieren Sie einen Summer, der bei Hinderniserkennung einen Ton ausgibt

Weitere Projekte
-----------------------
* :ref:`fun_soap_dispenser`

