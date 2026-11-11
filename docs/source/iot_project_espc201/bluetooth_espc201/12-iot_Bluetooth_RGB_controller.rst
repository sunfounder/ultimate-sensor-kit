.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

.. _c201_iot_Bluetooth_RGB_controller:

12. Bluetooth-RGB-Steuerung
============================

Eine Nachricht trägt drei Zahlen: wie viel Rot, wie viel Grün, wie viel Blau. Senden Sie
``R255G128B0``, und die LED wird orange.

Das ist die erste **strukturierte** Nachricht im Bluetooth-Teil - der Sketch muss sie in
drei Teile zerlegen, bevor er etwas damit anfangen kann.


1. Schaltung aufbauen
-----------------------------

.. note::

    Das Modul zieht beim Start einen hohen Strom. Stecken Sie deshalb die 9-V-Batterie
    bzw. das externe Netzteil in die Hohlbuchse des R4 Minima.


.. image:: ../img/09-Wiring_Bluetooth_rgb_controller.png
   :width: 80%

* :ref:`cpn_uno`
* :ref:`cpn_espc201`
* :ref:`cpn_rgb`


2. Code hochladen
-----------------------------

#. Öffnen Sie die Datei ``12-Bluetooth_RGB_controller.ino`` unter dem Pfad ``ultimate-sensor-kit\code\iot_project_espc201\bluetooth\12-Bluetooth_RGB_controller``.

#. Wählen Sie **Arduino UNO R4 Minima** und den richtigen Port und klicken Sie auf
   **Upload**.

#. Öffnen Sie den Seriellen Monitor mit **115200**. Jede Nachricht wird einmal
   ausgegeben, sobald sie vollständig ist - Sie sehen also genau, was die Platine
   verstanden hat:

   .. code-block:: text

      colour: R255G128B0


3. Die Farbe vom Handy ändern
------------------------------

#. Öffnen Sie LightBlue, tippen Sie auf **Scan** und verbinden Sie sich mit
   **SunFounder-C2**.

#. Klappen Sie den Dienst **0xA002** auf und öffnen Sie die Characteristic **C304**. Die
   Schaltfläche, die Sie brauchen, liegt im roten Rahmen.

   .. image:: ../img/ble_lightblue_write.png
      :width: 80%

#. Tippen Sie auf **Write new value**, stellen Sie das Format oben rechts auf
   **UTF-8 String** und geben Sie ``R255G128B0`` ein. Das Bild zeigt das Feld kurz vor dem
   Senden:

   .. image:: ../img/ble_lightblue_rgb.png
      :width: 80%

#. Senden Sie es. Die LED wird orange und der Serielle Monitor schreibt
   ``colour: R255G128B0``.

   .. note::

      Der Sketch reagiert nicht auf jedes einzelne Zeichen. Eine BLE-Nachricht kann
      unterwegs in mehrere Stücke zerlegt werden, deshalb wartet der Sketch, bis die
      Nachricht vollständig ist - ein ``#`` am Ende oder **120 ms** Ruhe - und setzt erst
      dann die Farbe. Würde er auf jedes Stück reagieren, blitzte die LED bei jedem Senden
      durch falsche Farben.

#. Probieren Sie ein paar weitere - das Feld bleibt offen, Sie können sofort erneut
   senden:

   .. list-table::
      :header-rows: 1
      :widths: 30 70

      * - Senden Sie
        - Was passiert
      * - ``R255G0B0``
        - rot
      * - ``R0G255B0``
        - grün
      * - ``R0G0B255``
        - blau
      * - ``R255G255B255``
        - weiß, alle drei Kanäle voll
      * - ``R0G0B0``
        - aus

   .. note::

      Die Zahlen gehen von **0 bis 255**, nicht in Prozent. ``R128G0B0`` ist ein dunkleres
      Rot als ``R255G0B0``, weil der Pin nur die halbe Zeit eingeschaltet ist.

      Die ganze Nachricht muss unter **20 Zeichen** bleiben, deshalb gibt es keine
      Trennzeichen.


4. Code-Erklärung
-----------------------------

#. **Drei Pins, eine Farbe**

   .. code-block:: arduino

      const int redPin = 9;
      const int greenPin = 10;
      const int bluePin = 11;

   ``analogWrite(pin, 0..255)`` nutzt PWM, die LED kann also viele Farben zeigen - nicht
   nur die drei Grundfarben.

#. **Die Nachricht zerlegen**

   .. code-block:: arduino

      int extract(const String& m, char marker) {
        int at = m.indexOf(marker);
        if (at < 0) return -1;
        ...
      }

   ``extract`` sucht den Buchstaben **R**, **G** oder **B** und liest die Ziffern
   dahinter, bis ein anderes Zeichen kommt. ``extract("R255G128B0", 'G')`` liefert also
   ``128``. Deshalb ist die Reihenfolge ``R...G...B...`` wichtig - Klammern braucht es
   nicht.

#. **Von Text zu Zahl**

   .. code-block:: arduino

      if (r >= 0) analogWrite(redPin,   constrain(r, 0, 255));
      if (g >= 0) analogWrite(greenPin, constrain(g, 0, 255));
      if (b >= 0) analogWrite(bluePin,  constrain(b, 0, 255));

   ``constrain`` begrenzt den Wert auf 0..255. Fehlt ein Buchstabe, bleibt ``-1`` und die
   zugehörige Farbe wird nicht verändert.

#. **Warten, bis die Nachricht fertig ist**

   .. code-block:: arduino

      if (c == '#' || c == '\r' || c == '\n') {
        applyMessage();
        continue;
      }
      if (message.length() < 20) message += c;

      // keine Raute gekommen: kurze Ruhe gilt als Ende
      if (message.length() > 0 && millis() - lastByte > 120) {
        applyMessage();
      }

   Zeichen werden gesammelt, nicht sofort ausgewertet. Erst ein ``#`` oder 120 ms Ruhe
   beenden die Nachricht - dann wird die Farbe gesetzt und der Puffer geleert.
