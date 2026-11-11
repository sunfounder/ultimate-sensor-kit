.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

.. _c201_iot_Bluetooth_lcd:

8. Bluetooth-LCD
================

Tippen Sie ein Wort auf dem Handy, und es erscheint auf dem LCD - ohne Kabel, ohne WLAN,
ohne Internet.

Die Platine ist das gleiche **SunFounder-C2**-Modul aus dem vorigen Kapitel, nur anders
genutzt: Das Handy schreibt Text in die Characteristic **C304**, und der Sketch liest ihn.


1. Schaltung aufbauen
-----------------------------

.. note::

    Das Modul zieht beim Start einen hohen Strom. Stecken Sie deshalb die 9-V-Batterie
    bzw. das externe Netzteil in die Hohlbuchse des R4 Minima.


.. image:: ../img/15-Wiring_Bluetooth_LCD.png
   :width: 100%

* :ref:`cpn_uno`
* :ref:`cpn_espc201`
* :ref:`cpn_i2c_lcd1602`


2. Code hochladen
-----------------------------

#. Öffnen Sie die Datei ``08-Bluetooth_lcd.ino`` unter dem Pfad ``ultimate-sensor-kit\code\iot_project_espc201\bluetooth\08-Bluetooth_lcd`` oder kopieren Sie den Code in die **Arduino IDE**.

   .. note::

      Der Sketch braucht die Bibliothek **LiquidCrystal I2C**. Öffnen Sie den
      Bibliotheksverwalter, suchen Sie ``LiquidCrystal I2C`` und installieren Sie sie.

#. Wählen Sie **Arduino UNO R4 Minima** und den richtigen Port und klicken Sie auf
   **Upload**.

#. Öffnen Sie den Seriellen Monitor mit **115200**. Sie sollten lesen:

   .. code-block:: text

      === ESPC2-01 Bluetooth (BLE) ===
      [OK] BLE is ready - scan for "SunFounder-C2" on your phone
      --------------------------------

   Steht dort ``[!] no reply from the module``, antwortet das Modul nicht auf D0/D1 -
   prüfen Sie die vier Drähte und das Netzteil.


3. Text mit LightBlue senden
------------------------------

Nutzen Sie dieselbe **LightBlue**-App wie im Einsteigerkapitel.

#. Öffnen Sie LightBlue, tippen Sie auf **Scan** und verbinden Sie sich mit
   **SunFounder-C2**.

#. Klappen Sie den Dienst **0xA002** auf und öffnen Sie die Characteristic **C304**.
   Tippen Sie dann auf **Write new value**.

   .. image:: ../img/ble_lightblue_write.png
      :width: 80%

#. Stellen Sie das Format oben rechts auf **UTF-8 String** und tippen Sie ein kurzes
   Wort - zum Beispiel ``hello``. Das Bild zeigt das Feld kurz vor dem Senden:

   .. image:: ../img/ble_lightblue_hello.png
      :width: 80%

#. Senden Sie es. Das Wort erscheint auf dem **LCD** und im Seriellen Monitor.

   .. note::

      Halten Sie den Text kurz: Das LCD hat 16 Spalten und 2 Zeilen, alles nach den ersten
      16 Zeichen rutscht in die zweite Zeile. Ein längerer Text wird einfach abgeschnitten.

#. Für die andere Richtung - von der Platine zum Handy - abonnieren Sie **C305** und
   tippen Sie dann im Seriellen Monitor. Es ist dasselbe Characteristic-Paar wie im
   Einsteigerkapitel, nur steuert diesmal eine Seite ein LCD.


4. Code-Erklärung
-----------------------------

#. **Das LCD am I2C-Bus**

   .. code-block:: arduino

      #include <LiquidCrystal_I2C.h>
      LiquidCrystal_I2C lcd(0x27, 16, 2);

   ``0x27`` ist die I2C-Adresse des Displays, ``16`` die Anzahl der Spalten und ``2`` die
   Anzahl der Zeilen. Die meisten dieser Module antworten auf ``0x27``, einige auf
   ``0x3F``.

#. **Bluetooth in einer Zeile**

   .. code-block:: arduino

      #include "SunFounder_BLE.h"
      BLEStream bleSerial;

   ``BLEStream`` verbirgt alle AT-Befehle. ``bleSerial.begin()`` schaltet Bluetooth ein,
   setzt den Namen **SunFounder-C2** und beginnt zu werben; danach verhält sich das Objekt
   wie ein normaler serieller Port - ``available()``, ``read()``, ``write()``.

   .. note::

      Das Modul spricht über D0/D1 (``Serial1``) mit **115200** mit der Platine. Das ist
      eine Hardware-Schnittstelle, es geht also kein Bit verloren, während das LCD
      aktualisiert wird.

#. **setup()**

   .. code-block:: arduino

      void setup() {
        lcd.init();
        lcd.clear();
        lcd.backlight();

        Serial.begin(115200);
        bleSerial.begin();
        bleSerial.setTimeout(50);
      }

   ``lcd.backlight()`` ist wichtig: Ohne sie arbeitet das Display, bleibt aber dunkel. Das
   kurze ``setTimeout(50)`` verhindert, dass ``readString()`` eine ganze Sekunde auf
   Zeichen wartet, die nie kommen.

#. **loop() - Handy zum LCD**

   .. code-block:: arduino

      if (bleSerial.available()) {
        data += bleSerial.readString();
        while (data.endsWith("\r") || data.endsWith("\n")) {
          data.remove(data.length() - 1);
        }
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(data);
      }

   Das Handy hängt an den getippten Text oft einen Zeilenumbruch an. Nur diese Zeichen
   werden entfernt - nie ein echtes Zeichen - und dann wird der Text auf dem Display
   ausgegeben.

#. **loop() - Platine zum Handy**

   .. code-block:: arduino

      if (Serial.available()) {
        bleSerial.write(Serial.read());
      }

   Alles, was Sie im Seriellen Monitor tippen, wird an **C305** weitergegeben. Abonnieren
   Sie diese Characteristic in LightBlue, erscheinen die Zeichen dort Byte für Byte.
