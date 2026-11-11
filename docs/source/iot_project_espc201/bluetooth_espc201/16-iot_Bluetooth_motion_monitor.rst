.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

.. _c201_iot_Bluetooth_motion_monitor:

16. Bluetooth-Bewegungsmonitor
=================================

Dieses letzte Projekt spricht als einziges **in beide Richtungen gleichzeitig**.

* Die Platine schickt die Neigung eines **MPU6050** ans Handy - eine Notification auf
  **C305**, zweimal pro Sekunde.
* Das Handy kann diese Übertragung **anhalten und fortsetzen**, indem es ``P`` oder ``S``
  in **C304** schreibt.

Jedes andere Kapitel nutzte nur eine Richtung. Hier sehen Sie beide und erkennen den
Unterschied der zwei Characteristics deutlich: Die eine trägt Daten **zu** Ihnen, die
andere trägt Ihren Befehl **zurück**.


1. Schaltung aufbauen
-----------------------------

.. note::

    Das Modul zieht beim Start einen hohen Strom. Stecken Sie deshalb die 9-V-Batterie
    bzw. das externe Netzteil in die Hohlbuchse des R4 Minima.


.. image:: ../img/16-Wiring_Bluetooth_motion_monitor.png
   :width: 80%

* :ref:`cpn_uno`
* :ref:`cpn_espc201`
* :ref:`cpn_mpu6050`


2. Code hochladen
-----------------------------

#. Öffnen Sie die Datei ``16-Bluetooth_motion_monitor.ino`` unter dem Pfad ``ultimate-sensor-kit\code\iot_project_espc201\bluetooth\16-Bluetooth_motion_monitor``.

   .. note::

      Installieren Sie **Adafruit MPU6050** und **Adafruit Unified Sensor** aus dem
      Bibliotheksverwalter.

#. Wählen Sie **Arduino UNO R4 Minima** und den richtigen Port und klicken Sie auf
   **Upload**.

#. Öffnen Sie den Seriellen Monitor mit **115200**. Sie sollten lesen:

   .. code-block:: text

      === ESPC2-01 Bluetooth (BLE) ===
      [OK] BLE is ready - scan for "SunFounder-C2" on your phone
      --------------------------------
      [OK] MPU6050 is ready
      Keep the board flat and still - measuring the zero point ...
      zero: X=-1.0 Y=-3.0
      Send S on C304 to start, P to pause

   Steht dort ``[!] no MPU6050 found``, antwortet der Sensor nicht auf A4/A5 - prüfen Sie
   SDA, SCL, VCC und GND, bevor Sie weitermachen.

   .. note::

      **Lassen Sie die Platine beim Einschalten flach und ruhig liegen.** Der Sketch nimmt
      in der ersten Sekunde zehn Messungen und speichert diese Lage als Nullpunkt, damit
      eine flach liegende Platine ``X:0.0 Y:0.0`` zeigt statt der wenigen Grad, die jeder
      Sensor von sich aus hat. Die beiden Zahlen in der Zeile ``zero:`` sind das, was er
      gemessen hat.


3. Gleichzeitig beobachten und steuern
------------------------------

#. Öffnen Sie LightBlue, tippen Sie auf **Scan** und verbinden Sie sich mit
   **SunFounder-C2**.

#. Klappen Sie den Dienst **0xA002** auf, öffnen Sie die Characteristic **C305** und
   tippen Sie auf **Subscribe**. Die Zeilen kommen zweimal pro Sekunde:

   .. image:: ../img/ble_lightblue_subs.png
      :width: 80%

   .. code-block:: text

      X:1.2 Y:-0.4
      X:8.7 Y:-3.1

   **Die Zahlen sind Grad.** ``0`` heißt flach, ``90`` heißt hochkant, und das Vorzeichen
   zeigt, in welche Richtung es kippt.

   .. list-table::
      :header-rows: 1
      :widths: 18 82

      * - Wert
        - Was er ist
      * - ``X``
        - Neigung **um die X-Achse** - die Platine kippt nach links oder rechts
      * - ``Y``
        - Neigung **um die Y-Achse** - die Platine kippt nach vorn oder hinten

   .. note::

      In der Nähe der Senkrechten beeinflussen sich beide Zahlen etwas - kippen Sie auf
      ``Y:80``, beginnt auch ``X`` zu wandern. So wird diese Art Winkel berechnet, es ist
      kein Verkabelungsfehler.

#. Gehen Sie nun zurück zur Dienstliste und öffnen Sie **C304**. Schreiben Sie ``P`` -
   die Übertragung stoppt sofort und der Serielle Monitor schreibt ``Streaming paused``.

   .. image:: ../img/ble_lightblue_write.png
      :width: 80%

   .. note::

      Das ist der interessante Teil: **Das Abonnement auf C305 bleibt offen**, aber es
      kommt nichts mehr an, weil die Platine aufgehört hat zu senden. Daten fließen nur,
      wenn der Sketch sie sendet.

#. Schreiben Sie ``S``, um wieder zu starten - die Zeilen kommen zurück.


4. Code-Erklärung
-----------------------------

#. **Zwei Richtungen in einer Schleife**

   .. code-block:: arduino

      while (bleSerial.available() > 0) {          // Handy -> Platine
        char c = (char)bleSerial.read();
        if (c == 'S') streaming = true;
        else if (c == 'P') streaming = false;
      }

      if (streaming && millis() - lastSend > interval) {   // Platine -> Handy
        bleSerial.println(line);
      }

   Der erste Block **liest**, der zweite **schreibt**. Beide laufen in derselben
   ``loop()``, keiner blockiert den anderen - deshalb fließt der Datenstrom weiter,
   während das Handy jederzeit einen Befehl senden kann.

#. **Neigung statt roher Beschleunigung**

   .. code-block:: arduino

      float tiltX = atan2(ay, az) * 180.0 / PI;
      float tiltY = atan2(-ax, sqrt(ay * ay + az * az)) * 180.0 / PI;

   Der Sensor liefert Beschleunigung in ``m/s^2``, was schwer zu lesen ist. ``atan2`` macht
   daraus einen Winkel in Grad: ``0`` flach, ``90`` hochkant.

#. **Der Nullpunkt**

   .. code-block:: arduino

      float sumX = 0, sumY = 0;
      for (int i = 0; i < 10; i++) {
        float tx, ty;
        readTilt(tx, ty);
        sumX += tx;
        sumY += ty;
        delay(50);
      }
      zeroX = sumX / 10.0;
      zeroY = sumY / 10.0;

   Zehn Messungen werden gemittelt, weil eine einzelne um ein bis zwei Grad springt. Dieser
   Mittelwert wird von jeder späteren Messung abgezogen:

   .. code-block:: arduino

      float x = tiltX - zeroX;
      float y = tiltY - zeroY;

   Ohne diesen Schritt zeigt eine flach liegende Platine ``X:-1.0 Y:-3.0`` und ein
   Lernender denkt, etwas sei kaputt. Mit ihm heißt ``0.0`` wirklich flach - so macht es
   auch ein echtes Produkt, meist mit einer Taste zum erneuten Nullstellen.

#. **Eine halbe Sekunde zwischen den Zeilen**

   .. code-block:: arduino

      const unsigned long interval = 500;
      if (streaming && millis() - lastSend > interval) { ... }

   BLE kann keinen endlosen Strom tragen; eine Zeile alle 500 ms ist auf dem Bildschirm
   flüssig und lässt dem Modul trotzdem Zeit für den Befehlskanal. Bei jedem Schleifen-
   durchlauf zu senden würde den Puffer fluten und ``P`` verspätet ankommen.
