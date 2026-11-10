.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

.. _cpn_button:

Tastenmodul
==========================

.. image:: img/06_button.png
    :width: 350
    :align: center

.. _btn_intro:

Einführung
---------------------------
Das Tastenmodul ist ein elektronisches Gerät zur Erfassung des Zustands einer Taste. Üblicherweise werden sie als Schalter zum Verbinden oder Unterbrechen von Schaltkreisen eingesetzt. Tasten finden in vielen Anwendungsbereichen Verwendung, etwa bei Türklingeln, Schreibtischlampen, Fernbedienungen, Aufzügen, Brandmeldern usw.

Funktionsprinzip
---------------------------
Das Tastenmodul funktioniert nach dem Prinzip eines Schalters. Ein Schalter ist ein elektrisches Bauteil, das dazu dient, einen Stromkreis zu öffnen oder zu schließen.

Die nachfolgende Abbildung zeigt den internen Aufbau einer Taste. Das Symbol rechts unten wird meist verwendet, um eine Taste in Schaltungen darzustellen.

.. image:: img/06_button_2.png
    :width: 400
    :align: center

Da der Pin 1 mit dem Pin 2 und der Pin 3 mit dem Pin 4 verbunden ist, schließt das Drücken der Taste alle 4 Pins und somit den Stromkreis.

.. image:: img/06_button_3.png
    :width: 700
    :align: center

Anwendungsbeispiele
---------------------------

**Benötigte Hardware-Komponenten**

- Arduino Uno R4 oder R3 Platine * 1
- Tastenmodul * 1
- Jumperkabel

**Schaltungsaufbau**

.. image:: img/06_button_circuit.png
    :width: 400
    :align: center

.. raw:: html
    
    <br/><br/>   

Programmcode
^^^^^^^^^^^^^^^^^^^^

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/d6586fb8-fd37-46d2-ba1f-c94ef3582fe8/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/06-component_button.mp4"  type="video/mp4">
      Ihr Browser unterstützt das Video-Tag nicht.
   </video>
   <br/><br/>  

Code-Erklärung
^^^^^^^^^^^^^^^^^^^^

1. **Einrichtung**: Im ersten Abschnitt des Codes deklarieren wir zunächst ``sensorPin`` als eine Konstante vom Typ Integer und weisen ihr die Pin-Nummer zu, an die wir unsere Taste am Arduino-Board anschließen werden. Die Funktion ``setup()`` setzt den Modus von ``sensorPin`` auf ``INPUT``, was bedeutet, dass wir Daten von der Taste über diesen Pin empfangen werden. Die Funktion ``Serial.begin()`` initiiert die serielle Kommunikation mit einer Baudrate von 9600.

   .. code-block:: arduino

      const int sensorPin = 7;

      void setup() {
        pinMode(sensorPin, INPUT);
        Serial.begin(9600);
      }

2. **Die Schleife**: Die Funktion ``loop()`` enthält die Hauptlogik des Programms. Sie liest kontinuierlich den Zustand der Taste aus und gibt ihn alle 50 Millisekunden im seriellen Monitor aus. Die Funktion ``digitalRead()`` liest den Zustand der Taste, und die Funktion ``Serial.println()`` gibt diesen Wert im seriellen Monitor aus. Die Funktion ``delay()`` pausiert dann die Ausführung für 50 Millisekunden, bevor die nächste Messung erfolgt. Die Taste gibt ein niedriges Signal aus, wenn sie gedrückt wird, und ein hohes, wenn sie losgelassen wird.

   .. code-block:: arduino
    
      void loop() {
        Serial.println(digitalRead(sensorPin));
        delay(50);
      }

Weitere Ideen
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- Verwenden Sie die Taste in Kombination mit if-Anweisungen, um unterschiedliche Szenarien in einem Programm zu steuern.
- Lassen Sie die Taste eine LED ein- und ausschalten, anstatt nur Ausgaben im seriellen Monitor zu erzeugen.

Weitere Projekte
---------------------------
* :ref:`fun_doorbell`
