.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

.. _cpn_rgb:

RGB-Modul
==========================

.. image:: img/24_rgb_module.png
    :width: 350
    :align: center

Einführung
---------------------------
Das RGB-Vollfarb-LED-Modul erzeugt durch die Mischung von rotem, grünem und blauem Licht ein Spektrum an Farben. Jede Farbe wird mittels PWM (Pulsweitenmodulation) eingestellt. Das Modul kann für bunte Lichteffekte verwendet oder zum Erlernen der PWM-Steuerung mit Arduino genutzt werden.

Funktionsprinzip
---------------------------
Das RGB-Modul funktioniert mit einer Vollfarb-LED, die über R-, G- und B-Anschlüsse mit einstellbarer PWM-Spannungseingabe verfügt. Die Farben der LED können miteinander kombiniert werden. Zum Beispiel erzeugt die Mischung von blauem und grünem Licht Zyan, die Mischung von rotem und grünem Licht Gelb. Dies wird als "additive Farbmischung" bezeichnet.

* `Additive Farbe - Wikipedia <https://de.wikipedia.org/wiki/Additive_Farbmischung>`_

.. image:: img/24_rgb_module_2.png
    :width: 200
    :align: center

Durch diese Methode können wir die drei Grundfarben in verschiedenen Verhältnissen mischen, um sichtbares Licht jeder gewünschten Farbe zu erzeugen. Beispielsweise kann Orange durch mehr Rot und weniger Grün erzeugt werden. Durch Anpassung der Stärke der Grundfarben (Rot, Blau, Grün) mittels PWM kann eine vollständige Farbmischung erreicht werden.

Anwendungsbeispiele
---------------------------

**Hardware-Komponenten**

- Arduino Uno R4 oder R3 Board * 1
- RGB-Modul * 1
- Jumperkabel


**Schaltungsaufbau**

.. image:: img/24_rgb_module_circuit.png
    :width: 400
    :align: center

.. raw:: html
    
    <br/><br/>   

Programmcode
^^^^^^^^^^^^^^^^^^^^

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/ac279eab-cbc6-4c51-a8b5-4d1b9048ec92/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/24-component_rgb.mp4"  type="video/mp4">
      Ihr Browser unterstützt das Video-Tag nicht.
   </video>
   <br/><br/>  

Code-Erklärung
^^^^^^^^^^^^^^^^^^^^

1. Im ersten Codeabschnitt werden die Pins deklariert und initialisiert, an die die Farbkanäle der RGB-LED angeschlossen sind.

   .. code-block:: arduino
       
      const int rledPin = 9;  // pin connected to the red color channel
      const int gledPin = 10;   // pin connected to the green color channel
      const int bledPin = 11;  // pin connected to the blue color channel

2. Die Funktion ``setup()`` initialisiert diese Pins als OUTPUT, da wir Signale von diesen Pins zum RGB-LED-Modul senden.

   .. code-block:: arduino
   
      void setup() {
        pinMode(rledPin, OUTPUT);
        pinMode(gledPin, OUTPUT);
        pinMode(bledPin, OUTPUT);
      }

3. In der Funktion ``loop()`` wird die Funktion ``setColor()`` mit verschiedenen Parametern aufgerufen, um verschiedene Farben anzuzeigen. Die Funktion ``delay()`` wird nach dem Einstellen jeder Farbe verwendet, um für 1000 Millisekunden (oder 1 Sekunde) zu pausieren, bevor zur nächsten Farbe übergegangen wird.

   .. code-block:: arduino
   
      void loop() {
        setColor(255, 0, 0);  // Set RGB LED color to red
        delay(1000);
        setColor(0, 255, 0);  // Set RGB LED color to green
        delay(1000);
        // The rest of the color sequence...
      }

4. Die Funktion ``setColor()`` verwendet die Funktion ``analogWrite()``, um die Helligkeit der einzelnen Farbkanäle im RGB-LED-Modul zu steuern. Mit der Funktion ``analogWrite()`` und PWM können verschiedene Spannungsausgänge simuliert werden. Durch Steuerung des PWM-Tastverhältnisses kann die Helligkeit jedes Farbkanals kontrolliert und so die Mischung verschiedener Farben ermöglicht werden.

   .. code-block:: arduino

      void setColor(int R, int G, int B) {
        analogWrite(rledPin, R);  // Use PWM to control the brightness of the red color channel
        analogWrite(gledPin, G);  // Use PWM to control the brightness of the green color channel
        analogWrite(bledPin, B);  // Use PWM to control the brightness of the blue color channel
      }


Weitere Ideen
^^^^^^^^^^^^^^^^^^^^

- Versuchen Sie, andere Farben anzuzeigen.
- Integrieren Sie die RGB-LED mit Sensoren und zeigen Sie verschiedene Farben basierend auf dem Sensorwert an.

Weitere Projekte
---------------------------
* :ref:`fun_gas_leak_alarm`
* :ref:`fun_light_control_switch`
* :ref:`fun_motion_triggered_relay`
* :ref:`iot_Bluetooth_RGB_controller`
* :ref:`iot_Bluetooth_remote_relay`

