.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

.. _fun_potentiometer_scale_value:

Potentiometer-Skalenwert
==========================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/fun/10-fun-Potentiometer_scale_value.mp4"  type="video/mp4">
      Ihr Browser unterstützt das Video-Tag nicht.
   </video>

Dieses Projekt wurde entwickelt, um den Wert eines Potentiometers auszulesen und diesen Wert auf einem LCD 1620 mit einer I2C-Schnittstelle anzuzeigen. Der Wert wird auch an den seriellen Monitor gesendet, um ihn in Echtzeit anzusehen. Ein besonderes Merkmal dieses Projekts ist die visuelle Darstellung des Potentiometerwerts auf dem LCD, die einen Balken anzeigt, dessen Länge dem Wert entspricht.

1. Schalten Sie die Schaltung
-----------------------------

.. image:: img/10-fun-Potentiometer_scale_value_circuit.png
    :width: 100%

* :ref:`cpn_uno`
* :ref:`cpn_potentiometer`
* :ref:`cpn_i2c_lcd1602`


2. Code
-----------------------------

#. Öffnen Sie die Datei ``10-Potentiometer_scale_value.ino`` unter dem Pfad ``ultimate-sensor-kit\fun_project\10-Potentiometer_scale_value``, oder kopieren Sie diesen Code in die **Arduino IDE**.

   .. raw:: html
       
       <iframe src=https://create.arduino.cc/editor/sunfounder01/8adabab1-9d8b-4b84-9007-18f86eda247a/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


3. Code-Erklärung
-----------------------------

Das Projekt funktioniert, indem es kontinuierlich den Wert von einem angeschlossenen Potentiometer liest. Dieser Wert wird dann auf eine kleinere Skala (0-16) abgebildet und sowohl numerisch als auch visuell auf dem LCD dargestellt. Durch Überprüfung des Unterschieds zwischen aufeinanderfolgenden Messwerten stellt der Code sicher, dass nur signifikante Änderungen auf dem Display widergespiegelt werden, wodurch das Flackern reduziert wird. Dies hilft, unerwünschte visuelle Effekte durch häufiges Aktualisieren des LCD-Bildschirms zu vermeiden.

1. **Bibliothek einbinden und initialisieren**:

   .. code-block:: arduino
   
      #include <Wire.h>
      #include <LiquidCrystal_I2C.h>
      LiquidCrystal_I2C lcd(0x27, 16, 2);

   Hier werden die benötigten Bibliotheken (``Wire`` für die I2C-Kommunikation und ``LiquidCrystal_I2C`` für das LCD) eingebunden. Ein LCD-Objekt wird mit der I2C-Adresse ``0x27`` erstellt und ist definiert mit ``16`` Spalten und ``2`` Zeilen.

2. **Variablendeklaration**:

   .. code-block:: arduino
   
      int lastRead = 0;     // Previous potentiometer value
      int currentRead = 0;  // Current potentiometer value

   ``lastRead`` speichert den zuletzt gelesenen Potentiometerwert. ``currentRead`` speichert den aktuellen Wert des Potentiometers.

3. **setup() Funktion**:

   .. code-block:: arduino
   
      void setup() {
        lcd.init();          // Initialize the LCD
        lcd.backlight();     // Turn on the LCD backlight
        Serial.begin(9600);  // Start serial communication at 9600 baud rate
      }

   Das LCD wird initialisiert, seine Hintergrundbeleuchtung eingeschaltet und die serielle Kommunikation mit einer Baudrate von ``9600`` gestartet.

4. **Hauptloop**:

   .. code-block:: arduino
   
      void loop() {
        int currentRead = analogRead(A0);
        int barLength = map(currentRead, 0, 1023, 0, 16);
        if (abs(lastRead - currentRead) > 2) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Wert:");
          lcd.setCursor(7, 0);
          lcd.print(currentRead);
          Serial.println(currentRead);
          for (int i = 0; i < barLength; i++) {
            lcd.setCursor(i, 1);
            lcd.print(char(255));
          }
        }
        lastRead = currentRead;
        delay(200);
      }

   * Der Potentiometerwert wird gelesen und auf eine Balkenlänge (0-16) abgebildet.
   * Wenn der Unterschied zwischen dem letzten und dem aktuellen Wert größer als ``2`` ist, wird das LCD aktualisiert.
   * Der Wert wird in der ersten Zeile und ein Balken (basierend auf dem abgebildeten Wert) in der zweiten Zeile angezeigt.
   * Der Wert wird auch an den seriellen Monitor gesendet.
   * Vor der nächsten Iteration wird ``lastRead`` aktualisiert, und es wird eine Verzögerung von ``200ms`` für die Stabilität eingeführt.

