.. _cpn_buzzer:

Passives Summermodul
==========================

.. image:: img/26_passive_buzzer_module.png
    :width: 400
    :align: center

Einleitung
---------------------------
Ein passiver Summer ist ein Bauelement, das Töne erzeugt, sobald ihm ein elektrisches Signal zugeführt wird. Es wird als passiv bezeichnet, da es keinen internen Oszillator besitzt, um eigenständig Töne zu generieren. Stattdessen benötigt es ein externes Signal von einem Mikrocontroller wie dem Arduino. Das passive Summermodul ist eine kompakte elektronische Komponente, die neben dem passiven Summer auch die nötige Schaltungstechnik enthält, um die Anwendung mit dem Arduino zu vereinfachen.

Funktionsprinzip
---------------------------
Das Arbeitsprinzip des passiven Summermoduls basiert auf dem piezoelektrischen Effekt. Sobald ein elektrisches Signal an den Summer angelegt wird, bringt es einen im Inneren befindlichen piezoelektrischen Kristall zum Schwingen. Diese Schwingungen erzeugen Schallwellen. Die Frequenz des erzeugten Tons hängt von der Frequenz des zugeführten elektrischen Signals ab. Durch Variation der Signal-Frequenz kann die Tonhöhe verändert werden.

Anwendungsbeispiele
---------------------------

**Hardware-Komponenten**

- Arduino Uno R4 oder R3 Board * 1
- Passives Summermodul * 1
- Jumperkabel

**Schaltungsaufbau**

.. image:: img/26_passive_buzzer_module_circuit.png
    :width: 80%
    :align: center

.. raw:: html
    
    <br/><br/>   

Code
^^^^^^^^^^^^^^^^^^^^

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/5b24a3d9-8688-4dc2-ad3a-cce82f6bd3a7/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/26-component_buzzer.mp4"  type="video/mp4">
      Ihr Browser unterstützt das Video-Tag nicht.
   </video>
   <br/><br/>  

Code-Erläuterung
^^^^^^^^^^^^^^^^^^^^

1. Einbindung der Tonhöhen-Bibliothek:
   Diese Bibliothek stellt die Frequenzwerte für verschiedene Musiknoten bereit.

   .. code-block:: arduino
       
      #include "pitches.h"

2. Definition von Konstanten und Arrays:

   * ``buzzerPin`` ist der digitale Pin am Arduino, an dem der Summer angeschlossen ist.
   
   * ``melody[]`` ist ein Array, das die Reihenfolge der zu spielenden Noten speichert.
   
   * ``noteDurations[]`` ist ein Array, das die Dauer jeder Note in der Melodie speichert.

   .. code-block:: arduino
   
      const int buzzerPin = 8;
      int melody[] = {
        NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
      };
      int noteDurations[] = {
        4, 8, 8, 4, 4, 4, 4, 4
      };

3. Melodiewiedergabe:

   * Die ``for``-Schleife geht jede Note der Melodie durch.
   
   * Die Funktion ``tone()`` spielt eine Note über den Summer für eine bestimmte Dauer ab.
   
   * Eine Verzögerung zwischen den Noten sorgt für eine klare Trennung.
   
   * Die Funktion ``noTone()`` beendet die Tonausgabe.

   .. code-block:: arduino
   
      void setup() {
        for (int thisNote = 0; thisNote < 8; thisNote++) {
          int noteDuration = 1000 / noteDurations[thisNote];
          tone(buzzerPin, melody[thisNote], noteDuration);
          int pauseBetweenNotes = noteDuration * 1.30;
          delay(pauseBetweenNotes);
          noTone(buzzerPin);
        }
      }

4. Leere Loop-Funktion:
   Da die Melodie nur einmal im Setup gespielt wird, ist die Loop-Funktion leer.

Weitere Ideen
^^^^^^^^^^^^^^^^^^^^

- Melodie ändern: Experimentieren Sie mit anderen Noten und Dauern in den Arrays ``melody[]`` und ``noteDurations[]``, um eigene Melodien zu erzeugen. Es gibt ein GitHub-Repository (|link_arduino-songs|), das Arduino-Codes für verschiedene Lieder bereitstellt. 
- Schalter integrieren: Fügen Sie einen Taster in die Schaltung ein und passen Sie den Code so an, dass die Melodie nur dann gespielt wird, wenn der Taster gedrückt wird.

Weitere Projekte
---------------------------
* :ref:`fun_doorbell`
* :ref:`fun_gas_leak_alarm`
* :ref:`iot_Bluetooth_piano`

