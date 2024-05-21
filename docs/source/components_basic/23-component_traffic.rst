.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

.. _cpn_traffic:

Ampel-Modul
==========================

.. image:: img/23_traffic_light.png
    :width: 400
    :align: center

Einführung
---------------------------
Das Ampel-Modul ist ein kleines Gerät, das rote, gelbe und grüne Lichter anzeigen kann, genau wie eine echte Ampel. Es eignet sich zur Erstellung eines Modells eines Ampelsystems oder zum Erlernen der Steuerung von LEDs mit Arduino. Es zeichnet sich durch seine kompakte Bauform, einfache Verkabelung, zielgerichtete Anwendung und individuelle Installationsmöglichkeiten aus. Über den PWM-Pin lässt sich die Helligkeit der LED steuern.

Funktionsprinzip
---------------------------
Das Ampel-Modul kann auf zwei Hauptarten gesteuert werden. Die einfachere Methode verwendet digitale Eingänge vom Arduino, bei denen ein HIGH- oder LOW-Signal die entsprechende LED direkt ein- oder ausschaltet. Alternativ kann PWM (Pulsweitenmodulation) verwendet werden, insbesondere wenn die Helligkeit der LED variiert werden soll. PWM ist eine Technik, bei der der Tastgrad eines digitalen Signals verändert wird, um die Helligkeit der LED zu modulieren. Der Tastgrad gibt den prozentualen Anteil der Zeit an, während der ein Signal in einem bestimmten Zeitraum aktiv ist. Ein Tastgrad von 50% bedeutet beispielsweise, dass das Signal für die Hälfte der Zeit aktiv und für den Rest inaktiv ist.

Anwendungsbeispiele
---------------------------

**Hardware-Komponenten**

- Arduino Uno R4 oder R3 Board * 1
- Ampel-Modul * 1
- Jumperkabel


**Schaltungsaufbau**

.. image:: img/23_traffic_light_circuit.png
    :width: 600
    :align: center

.. raw:: html
    
    <br/><br/>   

Programmcode
^^^^^^^^^^^^^^^^^^^^

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/fb0a9599-5e59-458c-893b-97551f62aea8/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/23-component_traffic.mp4"  type="video/mp4">
      Ihr Browser unterstützt das Video-Tag nicht.
   </video>
   <br/><br/>   

Code-Erklärung
^^^^^^^^^^^^^^^^^^^^

1. Bevor wir mit den Operationen beginnen, definieren wir Konstanten für die Pins, an denen die LEDs angeschlossen sind. Dies macht unseren Code leichter lesbar und modifizierbar.

  .. code-block:: arduino

     const int rledPin = 9;  //rot
     const int yledPin = 8;  //gelb
     const int gledPin = 7;  //grün

2. Hier legen wir die Pin-Modi für unsere LED-Pins fest. Alle sind auf ``OUTPUT`` gesetzt, da wir vorhaben, Spannung an sie zu senden.

  .. code-block:: arduino

     void setup() {
       pinMode(rledPin, OUTPUT);
       pinMode(yledPin, OUTPUT);
       pinMode(gledPin, OUTPUT);
     }

3. Hier wird die Logik für unseren Ampelzyklus implementiert. Die Abfolge der Operationen lautet:

    * Die grüne LED für 5 Sekunden einschalten.
    * Die gelbe LED dreimal blinken lassen (jedes Blinken dauert 0,5 Sekunden).
    * Die rote LED für 5 Sekunden einschalten.
    
  .. code-block:: arduino

     void loop() {
       digitalWrite(gledPin, HIGH);
       delay(5000);
       digitalWrite(gledPin, LOW);
       
       digitalWrite(yledPin, HIGH);
       delay(500);
       digitalWrite(yledPin, LOW);
       delay(500);
       digitalWrite(yledPin, HIGH);
       delay(500);
       digitalWrite(yledPin, LOW);
       delay(500);
       digitalWrite(yledPin, HIGH);
       delay(500);
       digitalWrite(yledPin, LOW);
       delay(500);
       
       digitalWrite(rledPin, HIGH);
       delay(5000);
       digitalWrite(rledPin, LOW);
     }

Weitere Ideen
^^^^^^^^^^^^^^^^^^^^

- Integrieren Sie einen Summer, um akustische Signale beim Wechsel von Grün auf Rot zu geben, was für sehbehinderte Personen hilfreich ist.

Weitere Projekte
---------------------------
* :ref:`fun_touch_toggle_light`
* :ref:`iot_Remote_relay_controller`
* :ref:`iot_Bluetooth_voice_control_relay`
* :ref:`iot_Bluetooth_traffic_light`
