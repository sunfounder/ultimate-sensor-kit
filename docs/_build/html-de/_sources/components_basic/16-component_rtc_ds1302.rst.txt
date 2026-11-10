.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

.. _cpn_rtc_ds1302:

Echtzeituhr-Modul (DS1302)
=====================================

.. image:: img/16_DS1302_module.png
    :width: 400
    :align: center

Einleitung
---------------------------
Das DS1302 Echtzeituhr-Modul ist ein Gerät zur präzisen Zeit- und Datumsverwaltung. Es eignet sich hervorragend für Projekte, die genaue Zeitangaben und Planungen erfordern, oder um eine digitale Uhr mit Arduino zu realisieren.

Funktionsweise
---------------------------
DS1302 ist ein von DALLAS in den USA eingeführter Uhrenbaustein mit Trickle-Ladung. Er verfügt über eine integrierte Echtzeituhr und einen 31-Byte-Statischen RAM. Der Baustein kommuniziert mit dem Mikrocontroller (MCU) über einfache serielle Schnittstellen. Er stellt Informationen zu Sekunde, Minute, Stunde, Tag, Woche, Monat und Jahr bereit. Zudem passt der DS1302 die Anzahl der Tage pro Monat sowie Schaltjahre automatisch an. Ob das 24-Stunden- oder das 12-Stunden-System verwendet wird, lässt sich über eine AM/PM-Auswahl festlegen. Die Kommunikation mit dem MCU erfolgt synchron über nur drei Anschlusskabel: Reset (RST), I/O-Daten (SDA) und serielle Uhr (SCL).

Anwendungsbeispiele
---------------------------

**Hardware-Komponenten**

- Arduino Uno R4 oder R3 Platine * 1
- Echtzeituhr-Modul (DS1302) * 1
- Jumperkabel


**Schaltungsaufbau**

.. image:: img/16_DS1302_module_circuit.png
    :width: 400
    :align: center

.. raw:: html
    
    <br/><br/>   

Programmcode
^^^^^^^^^^^^^^^^^^^^

.. note:: 
   Um die Bibliothek zu installieren, nutzen Sie den Arduino-Bibliotheksmanager und suchen Sie nach **"Rtc by Makuna"**, um sie zu installieren.

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/f923ec19-a2f0-4d74-b68b-826da12a17f3/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/16-component_rtc_ds1302.mp4"  type="video/mp4">
      Ihr Browser unterstützt das Video-Tag nicht.
   </video>
   <br/><br/>  

Code-Erklärung
^^^^^^^^^^^^^^^^^^^^

#. Initialisierung und Einbindung der Bibliotheken

   .. note:: 
      Um die Bibliothek zu installieren, nutzen Sie den Arduino-Bibliotheksmanager und suchen Sie nach **"Rtc by Makuna"**, um sie zu installieren. 

   Hier werden die erforderlichen Bibliotheken für das DS1302 RTC-Modul eingebunden.

   .. code-block:: arduino

      #include <ThreeWire.h>
      #include <RtcDS1302.h>

#. Pin-Definitionen und Erstellung der RTC-Instanz

   Die Pins für die Kommunikation werden definiert und eine Instanz des RTC wird erstellt.

   .. code-block:: arduino

      const int IO = 4;    // DAT
      const int SCLK = 5;  // CLK
      const int CE = 2;    // RST

      ThreeWire myWire(4, 5, 2);  // IO, SCLK, CE
      RtcDS1302<ThreeWire> Rtc(myWire);

#. ``setup()`` Funktion

   Diese Funktion initialisiert die serielle Kommunikation und nimmt die Grundkonfiguration des RTC-Moduls vor. Es werden diverse Prüfungen durchgeführt, um sicherzustellen, dass die RTC korrekt arbeitet.

   .. code-block:: arduino

      void setup() {
        Serial.begin(9600);
      
        Serial.print("compiled: ");
        Serial.print(__DATE__);
        Serial.println(__TIME__);
      
        Rtc.Begin();
      
        RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
        printDateTime(compiled);
        Serial.println();
      
        if (!Rtc.IsDateTimeValid()) {
          // Common Causes:
          //    1) first time you ran and the device wasn't running yet
          //    2) the battery on the device is low or even missing
      
          Serial.println("RTC lost confidence in the DateTime!");
          Rtc.SetDateTime(compiled);
        }
      
        if (Rtc.GetIsWriteProtected()) {
          Serial.println("RTC was write protected, enabling writing now");
          Rtc.SetIsWriteProtected(false);
        }
      
        if (!Rtc.GetIsRunning()) {
          Serial.println("RTC was not actively running, starting now");
          Rtc.SetIsRunning(true);
        }
      
        RtcDateTime now = Rtc.GetDateTime();
        if (now < compiled) {
          Serial.println("RTC is older than compile time!  (Updating DateTime)");
          Rtc.SetDateTime(compiled);
        } else if (now > compiled) {
          Serial.println("RTC is newer than compile time. (this is expected)");
        } else if (now == compiled) {
          Serial.println("RTC is the same as compile time! (not expected but all is fine)");
        }
      }

#. ``loop()`` Funktion

   Diese Funktion liest regelmäßig das aktuelle Datum und die aktuelle Uhrzeit vom RTC aus und gibt sie im seriellen Monitor aus. Sie prüft auch, ob die RTC weiterhin eine gültige Zeit und ein gültiges Datum beibehält.

   .. code-block:: arduino

      void loop() {
        RtcDateTime now = Rtc.GetDateTime();
      
        printDateTime(now);
        Serial.println();
      
        if (!now.IsValid()) {
          // Common Causes:
          //    1) the battery on the device is low or even missing and the power line was disconnected
          Serial.println("RTC lost confidence in the DateTime!");
        }
      
        delay(5000);  // five seconds
      }

#. Datum- und Zeitdruckfunktion

   Eine Hilfsfunktion, die ein ``RtcDateTime``-Objekt nimmt und das formatierte Datum und die Uhrzeit im seriellen Monitor ausgibt.

   .. code-block:: arduino

      void printDateTime(const RtcDateTime& dt) {
        char datestring[20];
      
        snprintf_P(datestring,
                   countof(datestring),
                   PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
                   dt.Month(),
                   dt.Day(),
                   dt.Year(),
                   dt.Hour(),
                   dt.Minute(),
                   dt.Second());
        Serial.print(datestring);
      }

Weitere Ideen
^^^^^^^^^^^^^^^^^^^^

- Anzeige der Uhrzeit auf einem LCD oder im seriellen Monitor
- Planung von Ereignissen/Weckern zu bestimmten Zeiten

