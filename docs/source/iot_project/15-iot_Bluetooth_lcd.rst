.. _iot_Bluetooth_lcd:

Bluetooth LCD
=============================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/iot/15-iot_Bluetooth_lcd.mp4"  type="video/mp4">
      Ihr Browser unterstützt das Video-Tag nicht.
   </video>

Das Projekt empfängt Nachrichten über ein mit dem UNO-Board verbundenes Bluetooth-Modul und zeigt die empfangenen Nachrichten auf einem LCD-Bildschirm an.

1. Schaltung aufbauen
-----------------------------

.. image:: img/15-Wiring_Bluetooth_LCD.png
    :width: 90%

* :ref:`cpn_uno`
* :ref:`cpn_jdy31`
* :ref:`cpn_i2c_lcd1602`

2. Code hochladen
-----------------------------

#. Öffnen Sie die Datei ``01-Bluetooth_lcd.ino`` im Verzeichnis ``ultimate-sensor-kit\iot_project\bluetooth\01-Bluetooth_lcd``, oder kopieren Sie diesen Code in die **Arduino IDE**.

   .. note:: 
      Um die Bibliothek zu installieren, nutzen Sie den Arduino-Bibliotheksmanager und suchen nach **"LiquidCrystal I2C"**, um es zu installieren.

   .. raw:: html

       <iframe src=https://create.arduino.cc/editor/sunfounder01/9df5fa0e-9a98-40bb-9dd2-e22edb250bfa/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

#. Wählen Sie das korrekte Board und den passenden Port aus und klicken Sie dann auf den **Upload**-Button.

#. Öffnen Sie den Seriellen Monitor (Baudrate auf **9600** einstellen), um Debug-Nachrichten anzuzeigen.

3. App und Bluetooth-Modul verbinden
-----------------------------------------------

Eine App namens "Serial Bluetooth Terminal" ermöglicht es, Nachrichten vom Bluetooth-Modul zum Arduino zu senden.

a. **Serial Bluetooth Terminal installieren**

   Laden und installieren Sie |link_serial_bluetooth_terminal| aus dem Google Play Store.

b. **Bluetooth verbinden**

   Aktivieren Sie zuerst **Bluetooth** auf Ihrem Smartphone.

      .. image:: img/new/09-app_1_shadow.png
         :width: 60%
         :align: center

   Navigieren Sie zu den **Bluetooth-Einstellungen** auf Ihrem Smartphone und suchen Sie nach Namen wie **JDY-31-SPP**.

      .. image:: img/new/09-app_2_shadow.png
         :width: 60%
         :align: center

   Nach dem Anklicken bestätigen Sie die **Kopplungsanfrage** im Pop-up-Fenster. Falls ein Kopplungscode erforderlich ist, geben Sie "1234" ein.

      .. image:: img/new/09-app_3_shadow.png
         :width: 60%
         :align: center


c. **Kommunikation mit dem Bluetooth-Modul**

   Öffnen Sie das Serial Bluetooth Terminal und verbinden Sie es mit "JDY-31-SPP".

   .. image:: img/new/00-bluetooth_serial_4_shadow.png 

d. **Befehle senden**

   Verwenden Sie die Serial Bluetooth Terminal App, um Nachrichten über Bluetooth an den Arduino zu senden. Die über Bluetooth gesendete Nachricht wird auf dem LCD angezeigt.

   .. image:: img/new/15-lcd_shadow.png
      :width: 100%
      :align: center




4. Code-Erläuterung
-----------------------------------------------

.. note:: 
      Zur Bibliotheksinstallation nutzen Sie den Arduino-Bibliotheksmanager und suchen nach **"LiquidCrystal I2C"**, um die Bibliothek zu installieren.

#. Einrichtung des LCDs

   .. code-block:: arduino

      #include <LiquidCrystal_I2C.h>
      LiquidCrystal_I2C lcd(0x27, 16, 2);

   Dieses Code-Segment bindet die LiquidCrystal_I2C-Bibliothek ein und initialisiert das LCD-Modul mit der I2C-Adresse ``0x27``. Zudem wird festgelegt, dass das LCD ``16`` Spalten und ``2`` Zeilen hat.

#. Einrichtung der Bluetooth-Kommunikation

   .. code-block:: arduino

      #include <SoftwareSerial.h>
      const int bluetoothTx = 3;
      const int bluetoothRx = 4;
      SoftwareSerial bleSerial(bluetoothTx, bluetoothRx);

   Hier wird die SoftwareSerial-Bibliothek eingebunden, um die Kommunikation zwischen dem JDY-31 Bluetooth-Modul und dem Arduino über die Pins 3 (TX) und 4 (RX) zu ermöglichen.

#. Initialisierung

   .. code-block:: arduino

      void setup() {
         lcd.init();
         lcd.clear();
         lcd.backlight();

         Serial.begin(9600);
         bleSerial.begin(9600);
      }

   Die Funktion ``setup()`` initialisiert das LCD und entfernt etwaigen vorhandenen Inhalt. Auch wird die Hintergrundbeleuchtung des LCDs aktiviert. Die Kommunikation mit dem seriellen Monitor sowie dem Bluetooth-Modul wird bei einer Baudrate von ``9600`` gestartet.

#. Hauptprogrammschleife

   .. code-block:: arduino

      void loop() {
         String data;

         if (bleSerial.available()) {
            data += bleSerial.readString();
            data = data.substring(0, data.length() - 2);
            Serial.print(data);

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(data);
         }

         if (Serial.available()) {
            bleSerial.write(Serial.read());
         }
      }

   Dies ist die Hauptprogrammschleife des Arduino-Programms. Sie überprüft kontinuierlich den Eingang von Daten sowohl vom Bluetooth-Modul als auch vom seriellen Monitor. Bei Empfang von Daten über das Bluetooth-Gerät werden diese verarbeitet, auf dem seriellen Monitor angezeigt und auf dem LCD dargestellt. Wenn Daten im seriellen Monitor eingegeben werden, werden diese Daten an das Bluetooth-Modul gesendet.
