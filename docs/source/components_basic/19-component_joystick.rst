.. _cpn_joystick:

Joystick-Modul
==========================

.. image:: img/19_joystick.png
    :width: 400
    :align: center

Einführung
---------------------------
Ein Joystick-Modul ist ein Gerät, das die Bewegungen eines Knüppels in zwei Richtungen messen kann: horizontal (X-Achse) und vertikal (Y-Achse). Es eignet sich zur Steuerung verschiedenster Anwendungen wie Spiele, Roboter, Kameras und mehr.

Funktionsprinzip
---------------------------
Ein Joystick funktioniert auf Basis der Widerstandsänderung zweier Potentiometer (üblicherweise 10 Kiloohm). Durch Veränderung des Widerstands in X- und Y-Richtung empfängt das Arduino Board variierende Spannungen, die als X- und Y-Koordinaten interpretiert werden. Der Prozessor benötigt eine ADC-Einheit, um die analogen Werte des Joysticks in digitale Werte umzuwandeln und die erforderliche Verarbeitung durchzuführen.

Arduino-Boards verfügen über sechs 10-Bit-ADC-Kanäle, was bedeutet, dass die Referenzspannung (5 Volt) des Arduino in 1024 Segmente unterteilt ist. Bewegt sich der Joystick entlang der X-Achse, steigt der ADC-Wert von 0 auf 1023, wobei der Mittelwert bei 512 liegt. Das untenstehende Bild zeigt den ungefähren ADC-Wert in Abhängigkeit von der Position des Joysticks.

.. image:: img/19_joystick_xy.png
    :width: 400
    :align: center

Anwendungsbeispiele
---------------------------

**Hardware-Komponenten**

- Arduino Uno R4 oder R3 Board * 1
- Joystick-Modul * 1
- Jumperkabel

**Schaltungsaufbau**

.. image:: img/19_joystick_module_circuit.png
    :width: 600
    :align: center

.. raw:: html
    
    <br/><br/>   

Programmcode
^^^^^^^^^^^^^^^^^^^^

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/3233bdfb-21b1-4358-a8cb-a0b2badeb173/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/19-component_joystick.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>
   <br/><br/>  

Code-Erklärung
^^^^^^^^^^^^^^^^^^^^

#. Festlegung der Anschlüsse für den Joystick. Hier definieren wir, an welche analogen Pins die X- und Y-Achsen des Joysticks angeschlossen sind.

   .. code-block:: arduino

      const int xPin = A0;
      const int yPin = A1;

#. Initialisierung in der ``setup()``-Funktion. In diesem Abschnitt wird die serielle Kommunikation eingerichtet, die es uns ermöglicht, Nachrichten von und zum Arduino über den seriellen Monitor zu senden und zu empfangen.

   .. code-block:: arduino

      void setup() {
        Serial.begin(9600);
      }

#. Auslesen der Joystick-Werte in der ``loop()``-Funktion. Kontinuierlich liest das Arduino die X- und Y-Werte vom Joystick aus und gibt sie auf dem seriellen Monitor aus. Zwischen den einzelnen Ausgaben gibt es eine kurze Verzögerung, um die Lesungen besser lesbar zu machen und den seriellen Monitor nicht zu überlasten.

   .. code-block:: arduino
       
      void loop() {
        Serial.print("X: ");
        Serial.print(analogRead(xPin));
        Serial.print(" | Y: ");
        Serial.println(analogRead(yPin));
        delay(50);
      }

Weitere Ideen
^^^^^^^^^^^^^^^^^^^^

- Die Joystick-Werte zur Steuerung eines Servomotors verwenden, der auf die Bewegungen des Joysticks reagiert.

