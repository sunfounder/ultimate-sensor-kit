.. _cpn_potentiometer:

Potentiometer-Modul
==========================

.. image:: img/08_potentiomete_module.png
    :width: 300
    :align: center

Einleitung
---------------------------
Das Potentiometer-Modul ist ein elektronisches Bauelement, dessen Widerstandswert sich je nach Stellung des Drehknopfs ändert. Es findet vielseitige Anwendungsbereiche, wie zum Beispiel die Lautstärkeregelung eines Lautsprechers, die Helligkeitssteuerung einer LED oder die Geschwindigkeitskontrolle eines Motors.

Funktionsprinzip
---------------------------
Ein Potentiometer ist ebenfalls ein Widerstandsbauelement mit drei Anschlüssen, dessen Widerstandswert gemäß einer bestimmten Regelung angepasst werden kann.

Potentiometer gibt es in verschiedenen Formen, Größen und Werten, aber sie haben alle folgende Eigenschaften gemeinsam:

- Sie verfügen über drei Anschlüsse.
- Sie haben einen Drehknopf, eine Schraube oder einen Schieber, um den Widerstand zwischen dem mittleren und einem der äußeren Anschlüsse zu variieren.
- Der Widerstand zwischen dem mittleren und einem der äußeren Anschlüsse variiert von 0 Ω bis zum maximalen Widerstand des Potentiometers, wenn der Drehknopf, die Schraube oder der Schieber bewegt wird.

Hier ist das Schaltungssymbol eines Potentiometers.

.. image:: img/08_potentiometer_symbol_2.png
    :width: 200
    :align: center

Die Funktionen des Potentiometers im Stromkreis sind wie folgt:

#. Als Spannungsteiler
    Das Potentiometer ist ein kontinuierlich einstellbarer Widerstand. Wenn man die Welle oder den Schiebegriff des Potentiometers verstellt, bewegt sich der gleitende Kontakt auf dem Widerstandselement. Dabei kann eine Spannung in Abhängigkeit von der am Potentiometer anliegenden Spannung und dem Drehwinkel oder dem Verfahrweg des beweglichen Armes abgegriffen werden.

#. Als Rheostat
    Wenn das Potentiometer als Rheostat eingesetzt wird, werden der mittlere Pin und einer der anderen beiden Pins im Stromkreis verbunden. So erhält man einen stufenlos und kontinuierlich veränderbaren Widerstandswert innerhalb des Verfahrwegs des gleitenden Kontakts.

#. Als Stromregler
    Wenn das Potentiometer als Stromregler fungiert, muss der gleitende Kontakt als einer der Ausgangsanschlüsse verbunden werden.

Anwendungsbeispiele
---------------------------

**Benötigte Hardware-Komponenten**

- Arduino Uno R4 oder R3 Board * 1
- Potentiometer-Modul * 1
- Jumper-Kabel

**Schaltungsaufbau**

.. image:: img/08_potentiometer_module_circuit.png
    :width: 400
    :align: center

.. raw:: html
    
    <br/><br/>   

Programmcode
^^^^^^^^^^^^^^^^^^^^

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/dd4ed045-ccca-48f2-a938-e90bb5257830/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/08-component_potentiometer.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>
   <br/><br/>  

Code-Erläuterung
^^^^^^^^^^^^^^^^^^^^

#. Diese Codezeile definiert die Pin-Nummer, an die das Potentiometer am Arduino-Board angeschlossen ist.

   .. code-block:: arduino

      const int sensorPin = A0;

#. Die ``setup()``-Funktion ist eine spezielle Funktion im Arduino-Umfeld, die nur einmal ausgeführt wird, wenn das Arduino-Board eingeschaltet oder zurückgesetzt wird. In diesem Projekt wird die serielle Kommunikation mit ``Serial.begin(9600)`` bei einer Baudrate von 9600 eingeleitet.

   .. code-block:: arduino

      void setup() {
        Serial.begin(9600);  
      }

#. Die ``loop()``-Funktion ist die Hauptfunktion, in der das Programm wiederholt ausgeführt wird. In dieser Funktion liest die ``analogRead()``-Funktion den Analogwert vom Potentiometer und gibt ihn mit ``Serial.println()`` im seriellen Monitor aus. Der Befehl ``delay(50)`` lässt das Programm für 50 Millisekunden pausieren, bevor der nächste Wert gelesen wird.

   .. code-block:: arduino

      void loop() {
        Serial.println(analogRead(sensorPin));  
        delay(50);
      }

Weitere Ideen
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- Steuerung der LED-Helligkeit: Der Analogwert des Potentiometers könnte verwendet werden, um die Helligkeit einer an einem PWM-fähigen Pin des Arduino angeschlossenen LED zu steuern.
   
- Steuerung der Position eines Servomotors: Durch die Zuordnung des Analogwerts zum Bereich der Position des Servomotors (in der Regel von 0 bis 180 Grad) könnte das Potentiometer als Controller für den Servomotor dienen.

Weitere Projekte
---------------------------
* :ref:`fun_potentiometer_scale_value`

