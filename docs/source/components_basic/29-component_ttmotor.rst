.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

.. _cpn_ttmotor:

TT Motor
==========================

.. image:: img/29_tt_motor.jpg
    :width: 400
    :align: center

.. raw:: html
    
    <br/>

Einführung
---------------------------
Ein TT-Motor ist eine Art von Gleichstrommotor, an den ein Getriebe angekoppelt ist. Dieses Getriebe reduziert die Geschwindigkeit des Motors und erhöht sein Drehmoment. TT-Motoren werden häufig in Anwendungen wie Antriebsrädern, Propellern, Ventilatoren und ähnlichem eingesetzt. Ein TT-Motor verfügt über zwei Kabel: ein positives und ein negatives. Das positive Kabel ist in der Regel rot und das negative Kabel in der Regel schwarz.

Im Produkt wird ein TT-Gleichstromgetriebemotor mit einem Übersetzungsverhältnis von 1:48 verwendet. Er ist mit 2 x 200 mm Kabeln mit 0,1"-Steckverbindern ausgestattet, die in ein Steckbrett passen. Ideal zum Einstecken in ein Steckbrett oder eine Anschlussleiste.

Sie können diese Motoren mit 3 ~ 6VDC betreiben, allerdings werden sie bei höheren Spannungen natürlich schneller laufen.


Funktionsprinzip
---------------------------
Ein TT-Motor funktioniert, indem er elektrische Energie in mechanische Energie umwandelt. Wenn eine Spannung an die Kabel des Motors angelegt wird, entsteht ein Magnetfeld, das den Motor zum Drehen bringt. Die Geschwindigkeit und die Drehrichtung des Motors hängen von der Spannung und der Polarität der Stromquelle ab. Je höher die Spannung, desto schneller dreht der Motor. Umkehren der Polarität bewirkt, dass der Motor in die entgegengesetzte Richtung dreht.


Anwendungsbeispiele
---------------------------

**Hardware-Komponenten**

- Arduino Uno R4 oder R3 Board * 1
- TT Motor * 1
- Jumperkabel


**Schaltungsaufbau**

.. image:: img/29_tt_motor_circuit.png
    :width: 400
    :align: center

.. raw:: html
    
    <br/><br/>   

Programmcode
^^^^^^^^^^^^^^^^^^^^

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/045d66e3-280d-4ef8-aa96-a1770ade414f/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/29-component_ttmotor.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>
   <br/><br/>  

Code-Erklärung
^^^^^^^^^^^^^^^^^^^^

1. Der erste Teil des Codes definiert die Steuerpins des Motors. Diese sind mit der L9110-Motorsteuerplatine verbunden.

   .. code-block:: arduino
   
      // Motorpins definieren
      const int motorB_1A = 9;
      const int motorB_2A = 10;

2. Die ``setup()``-Funktion initialisiert die Motorsteuerpins als Ausgang mit der Funktion ``pinMode()``. Anschließend wird mit ``analogWrite()`` die Geschwindigkeit des Motors eingestellt. Der an ``analogWrite()`` übergebene Wert kann zwischen 0 (aus) und 255 (volle Geschwindigkeit) variieren. Danach wird die Funktion ``delay()`` verwendet, um den Code für 5000 Millisekunden (oder 5 Sekunden) anzuhalten, wonach die Motorgeschwindigkeit auf 0 (aus) gesetzt wird.

   .. code-block:: arduino
   
      void setup() {
        pinMode(motorB_1A, OUTPUT);  // set motor pin 1 as output
        pinMode(motorB_2A, OUTPUT);  // set motor pin 2 as output
   
        analogWrite(motorB_1A, 255);  // set motor speed (0-255)
        analogWrite(motorB_2A, 0);
   
        delay(5000);
   
        analogWrite(motorB_1A, 0);  
        analogWrite(motorB_2A, 0);
      }

Weitere Ideen
^^^^^^^^^^^^^^^^^^^^

- Geschwindigkeitssteuerung des Motors mit einem Potentiometer: Anstatt die Motorgeschwindigkeit fest vorzugeben, könnten Sie ein Potentiometer verwenden, um die Geschwindigkeit des Motors dynamisch zu steuern.

