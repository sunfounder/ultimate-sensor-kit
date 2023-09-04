.. _cpn_pump:

Kreiselpumpe
==========================

.. image:: img/28_pump.png
    :width: 400
    :align: center

.. raw:: html
    
    <br/>
    
Einleitung
---------------------------
Eine Kreiselpumpe ist ein Gerät, das Flüssigkeiten mittels eines rotierenden Laufrads von einem Ort zum anderen befördern kann. Sie kann zum Pumpen von Wasser, Öl, Chemikalien usw. verwendet werden. Eine Kreiselpumpe besteht aus zwei Hauptkomponenten: einem Motor und einer Pumpe. Der Motor versorgt die Pumpe mit Energie, und die Pumpe wandelt die Rotationsenergie in Druck und Durchfluss um.


Funktionsprinzip
---------------------------
Die Kreiselpumpe funktioniert mit einem sich drehenden Laufrad, das die Geschwindigkeit der Flüssigkeit erhöht und sie durch ein Einlassrohr in die Pumpe zieht. Sobald die Flüssigkeit den äußeren Rand des Laufrads verlässt, wird sie durch die Zentrifugalkraft durch ein Auslassrohr gedrückt, was zu einem erhöhten Druck führt. Je schneller das Laufrad rotiert, desto höher sind der Druck und der Durchfluss der Flüssigkeit.


Anwendungsbeispiele
---------------------------

**Hardware-Komponenten**

- Arduino Uno R4 oder R3 Board * 1
- Kreiselpumpe * 1
- Jumperkabel


**Schaltungsaufbau**

.. image:: img/28_pump_circuit.png
    :width: 600
    :align: center

.. raw:: html
    
    <br/><br/>   

Programmcode
^^^^^^^^^^^^^^^^^^^^

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/4c1aa3f1-7b17-4906-90e3-eb1e092fae09/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/28-component_pump.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>
   <br/><br/>  

Code-Erklärung
^^^^^^^^^^^^^^^^^^^^

1. Zwei Pins werden für die Motorsteuerung definiert, konkret ``motorB_1A`` und ``motorB_2A``. Diese Pins verbinden sich mit der L9110 Motorsteuerplatine, um die Richtung und Geschwindigkeit des Motors zu steuern.

   .. code-block:: arduino

      const int motorB_1A = 9;
      const int motorB_2A = 10;

2. Konfiguration der Pins und Steuerung des Motors:

   - Die ``setup()``-Funktion initialisiert die Pins als ``OUTPUT``, sodass sie Signale an die Motorsteuerplatine senden können.

   - Die Funktion ``analogWrite()`` wird verwendet, um die Motorgeschwindigkeit einzustellen. Hier bewirkt das Setzen eines Pins auf ``HIGH`` und des anderen auf ``LOW``, dass sich die Pumpe in eine Richtung dreht. Nach einer Verzögerung von 5 Sekunden werden beide Pins auf 0 gesetzt, um den Motor auszuschalten.
   
   .. code-block:: arduino

      void setup() {
         pinMode(motorB_1A, OUTPUT);  // Pin 1 der Pumpe als Ausgang definieren
         pinMode(motorB_2A, OUTPUT);  // Pin 2 der Pumpe als Ausgang definieren
         analogWrite(motorB_1A, HIGH); 
         analogWrite(motorB_2A, LOW);
         delay(5000);  // 5 Sekunden warten
         analogWrite(motorB_1A, 0);  // Pumpe ausschalten
         analogWrite(motorB_2A, 0);
      }


Weitere Ideen
^^^^^^^^^^^^^^^^^^^^

- Ändern der Pumpenrichtung durch Vertauschen der ``HIGH`` und ``LOW`` Werte zwischen den Pins.

- Implementieren Sie ein System, bei dem der Pumpenzustand (an/aus) durch einen Tastendruck umgeschaltet wird.

- Verwenden Sie ein Potenziometer, um die Geschwindigkeit der Pumpe mittels PWM zu steuern.

- Integrieren Sie Sensoren, um den Pumpenbetrieb automatisch auf der Grundlage bestimmter Bedingungen zu steuern, z. B. das Ein- und Ausschalten der Pumpe je nach Wasserstand in einem Tank.

Weitere Projekte
---------------------------
* :ref:`fun_soap_dispenser`
* :ref:`iot_Auto_watering_system`

