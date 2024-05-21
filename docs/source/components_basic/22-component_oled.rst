.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

.. _cpn_olde:

OLED-Display-Modul
==========================

.. image:: img/22_OLED.png
   :width: 300
   :align: center

Einführung
---------------------------
Ein OLED-Display-Modul (Organic Light-Emitting Diode) ermöglicht die Darstellung von Text, Grafiken und Bildern auf einem dünnen, flexiblen Bildschirm. Es nutzt organische Materialien, die Licht aussenden, wenn elektrischer Strom angelegt wird.

Ein wesentlicher Vorteil von OLED-Displays besteht darin, dass sie ihr eigenes Licht erzeugen und keine zusätzliche Hintergrundbeleuchtung benötigen. Dies führt oft zu besserem Kontrast, höherer Helligkeit und besseren Betrachtungswinkeln im Vergleich zu LCD-Displays.

Ein weiteres Highlight von OLED-Displays sind die tiefen Schwarzwerte. Da jedes Pixel sein eigenes Licht emittiert, kann zur Darstellung der Farbe Schwarz das entsprechende Pixel einfach ausgeschaltet werden.

OLED-Displays zeichnen sich zudem durch einen geringeren Stromverbrauch aus, da nur leuchtende Pixel Strom verbrauchen. Daher sind sie besonders beliebt in batteriebetriebenen Geräten wie Smartwatches, Gesundheitstrackern und anderen Wearables.

Funktionsprinzip
---------------------------
Ein OLED-Display-Modul besteht aus einem OLED-Panel und einem auf der Rückseite montierten OLED-Treiber-Chip. Das Panel besteht aus zahlreichen winzigen Pixeln, die unterschiedliche Farben erzeugen können. Jedes Pixel setzt sich aus mehreren Schichten organischer Materialien zwischen zwei Elektroden (Anode und Kathode) zusammen. Fließt Strom durch die Elektroden, senden die organischen Materialien Licht unterschiedlicher Wellenlängen aus, je nach ihrer Zusammensetzung.

Der OLED-Treiber-Chip steuert die Pixel des OLED-Panels über das serielle Kommunikationsprotokoll I2C (Inter-Integrated Circuit). 

Mit speziellen Bibliotheken wie der Adafruit SSD1306 lässt sich das OLED-Display-Modul über den Arduino ansteuern, um beispielsweise Helligkeitsstufen einzustellen oder Text und Grafiken darzustellen.

Anwendungsbeispiele
---------------------------

**Hardware-Komponenten**

- Arduino Uno R4 oder R3 Board * 1
- OLED-Display-Modul * 1
- Jumperkabel

**Schaltungsaufbau**

.. image:: img/22_OLED_circuit.png
    :width: 600
    :align: center

.. raw:: html
    
    <br/><br/>   

Code
^^^^^^^^^^^^^^^^^^^^

.. note:: 
   Zur Installation der Bibliothek verwenden Sie den Arduino-Bibliotheksmanager und suchen nach **"Adafruit SSD1306"** sowie **"Adafruit GFX"** und installieren diese.

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/fee9cc72-22bb-408c-81cf-fb4589121276/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/22-component_oled.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>
   <br/><br/>  

Code-Erläuterung
^^^^^^^^^^^^^^^^^^^^

1. **Einbindung der Bibliotheken und initiale Definitionen**:
   Die notwendigen Bibliotheken für die Kommunikation mit dem OLED-Display werden eingebunden. Anschließend erfolgen die Definitionen für die Abmessungen und die I2C-Adresse des OLEDs.

   - **Adafruit SSD1306**: Diese Bibliothek ist darauf ausgelegt, die Kommunikation mit dem SSD1306 OLED-Display zu erleichtern. Sie stellt Methoden zur Initialisierung des Displays, zur Steuerung seiner Einstellungen und zur Anzeige von Inhalten bereit.
   
   - **Adafruit GFX Library**: Dies ist eine Kerngrafikbibliothek, die es ermöglicht, Text anzuzeigen, Farben zu erzeugen, Formen zu zeichnen usw., auf verschiedenen Bildschirmen, einschließlich OLEDs.

   .. Hinweis:: 
      Um die Bibliothek zu installieren, verwenden Sie den Arduino-Bibliotheksmanager und suchen nach **"Adafruit SSD1306"** und **"Adafruit GFX"**, um sie zu installieren.

   .. code-block:: arduino
    
      #include <SPI.h>
      #include <Wire.h>
      #include <Adafruit_GFX.h>
      #include <Adafruit_SSD1306.h>

      #define SCREEN_WIDTH 128  // OLED display width, in pixels
      #define SCREEN_HEIGHT 64  // OLED display height, in pixels

      #define OLED_RESET -1
      #define SCREEN_ADDRESS 0x3C

2. **Bitmap-Daten**:
   Bitmap-Daten für die Anzeige eines benutzerdefinierten Symbols auf dem OLED-Bildschirm. Diese Daten repräsentieren ein Bild in einem Format, das das OLED interpretieren kann.

   Sie können dieses Online-Tool namens |link_image2cpp| verwenden, um Ihr Bild in ein Array umzuwandeln.

   Das Schlüsselwort ``PROGMEM`` gibt an, dass das Array im Programmspeicher des Arduino-Mikrocontrollers gespeichert ist. Die Speicherung von Daten im Programmspeicher (PROGMEM) anstelle von RAM kann bei großen Datenmengen nützlich sein, da sie sonst zu viel Platz im RAM beanspruchen würden.

   .. code-block:: arduino

      static const unsigned char PROGMEM sunfounderIcon[] = {...};

3. **Setup-Funktion (Initialisierung und Anzeige)**:
   Die ``setup()``-Funktion initialisiert das OLED und zeigt eine Reihe von Mustern, Texten und Animationen an.

   .. code-block:: arduino

      void setup() {
         ...  // Serial initialization and OLED object initialization
         ...  // Displaying various text, numbers, and animations
      }



Weitere Ideen
^^^^^^^^^^^^^^^^^^^^

- Verwenden Sie Tasten, um die angezeigten Nachrichten zu ändern oder zwischen verschiedenen Mustern und Animationen umzuschalten.

- Zeigen Sie Sensormessungen (wie Temperatur oder Luftfeuchtigkeit) in Echtzeit auf dem OLED an.

Weitere Projekte
---------------------------
* :ref:`fun_heartrate_monitor`
* :ref:`fun_tof_distance_monitor`
* :ref:`iot_Bluetooth_oled`
