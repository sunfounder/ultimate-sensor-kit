.. _cpn_fotowiderstand:

Fotowiderstands-Modul
==========================

.. image:: img/07_photoresistor_module.png
    :width: 400
    :align: center

Einleitung
---------------------------
Ein Fotowiderstands-Modul ist ein Gerät zur Messung der Lichtintensität in der Umgebung. Es kann für verschiedene Zwecke eingesetzt werden, wie etwa zur Anpassung der Helligkeit eines Geräts, zur Erkennung von Tag und Nacht oder zur Aktivierung eines Lichtschalters.

Ein wesentlicher Bestandteil des Fotowiderstands-Moduls ist der Fotowiderstand selbst. Ein Fotowiderstand ist ein lichtgesteuerter variabler Widerstand. Mit steigender Lichteinstrahlung verringert sich der Widerstand des Fotowiderstands; er zeigt also eine Foto-Leitfähigkeit.

Der Fotowiderstand kann in lichtempfindlichen Detektorschaltungen sowie in licht- und dunkelaktivierten Schaltkreisen als Halbleiterwiderstand eingesetzt werden. Im Dunkeln kann der Widerstand eines Fotowiderstands mehrere Megaohm (MΩ) betragen, während er im Hellen auf nur wenige hundert Ohm sinken kann.

Hier ist das elektronische Symbol für den Fotowiderstand:

.. image:: img/07_photoresistor_symbol_2.png
    :width: 200
    :align: center

Funktionsprinzip
---------------------------
Das Fotowiderstands-Modul arbeitet nach dem Prinzip der Widerstandsveränderung in Abhängigkeit von unterschiedlichen Lichtintensitäten. Der Sensor verfügt über ein integriertes Potentiometer, das den digitalen Ausgang (D0) des Sensors anpasst. Überschreitet die Lichtintensität einen bestimmten Schwellenwert, ändert sich der Widerstand des Sensors. Diese Widerstandsänderung wird dann in ein elektrisches Signal umgewandelt, das vom Arduino-Board ausgelesen werden kann.

Anwendungsbeispiele 
---------------------------

**Benötigte Hardware-Komponenten**

- Arduino Uno R4 oder R3 Board * 1
- Fotowiderstands-Modul * 1
- Jumperkabel

**Schaltungsaufbau**

.. image:: img/07_photoresistor_module_circuit.png
    :width: 400
    :align: center

.. raw:: html
    
    <br/><br/>   

Programmcode
^^^^^^^^^^^^^^^^^^^^

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/72eab12e-5539-46a5-9205-3fede2a236fc/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/07-component_photoresistor.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>
   <br/><br/>  

Code-Erklärung
^^^^^^^^^^^^^^^^^^^^

1. Diese Codezeile definiert die Pin-Nummer, an die der Fotowiderstandssensor auf dem Arduino-Board angeschlossen ist.

   .. code-block:: arduino

      const int sensorPin = 7;

2. Die Funktion ``setup()`` wird nur einmal ausgeführt, wenn das Arduino-Board eingeschaltet oder zurückgesetzt wird. In diesem Projekt wird der sensorPin als INPUT festgelegt, da wir von ihm Werte ablesen. Der Befehl Serial.begin(9600) initiiert die serielle Kommunikation mit einer Baudrate von 9600.

   .. code-block:: arduino

      void setup() {
        pinMode(sensorPin, INPUT);  
        Serial.begin(9600);         
      }

3. Die Funktion ``loop()`` ist die Hauptfunktion, in der das Programm fortlaufend abläuft. In dieser Funktion liest die Funktion digitalRead den digitalen Wert vom Fotowiderstandssensor und gibt ihn mit Serial.println auf dem seriellen Monitor aus. Der Befehl ``delay(50)`` sorgt für eine Wartezeit von 50 Millisekunden vor der nächsten Messung.

   .. code-block:: arduino

      void loop() {
        Serial.println(digitalRead(sensorPin));  
        delay(50);
      }

Weitere Ideen
^^^^^^^^^^^^^^^^^^^^

- Verwenden Sie den Sensor, um eine LED oder ein Relais ein- und auszuschalten.
- Plotten Sie den **analogen Ausgang** anstelle von einfachem digitalen HIGH/LOW. Verwenden Sie dafür den **AO**-Pin.

Weitere Projekte
---------------------------
* :ref:`fun_light_control_switch`

