.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

.. _c201_iot_Bluetooth_start:

Erste Schritte mit Bluetooth
=============================

Das ESPC2-01 bietet **WLAN und Bluetooth im selben Modul**, das Kit braucht also keinen
zweiten Bluetooth-Chip. Die Bluetooth-Projekte nutzen genau das Modul, das Sie schon
haben.

In den WLAN-Projekten sprach die Platine über die Cloud mit Blynk. Hier spricht das Handy
**direkt** mit dem Modul - ohne Router, ohne Internet, ohne Konto. Das macht Bluetooth für
eine Fernbedienung oder ein kleines Display so praktisch.

Am Ende dieses Kapitels haben Sie:

* das Modul, das sich als **SunFounder-C2** meldet,
* Text vom Handy, der auf der Platine ankommt, und
* Text von der Platine, der auf dem Handy erscheint.


1. Modul anschließen
---------------------

Schließen Sie das Modul am R4 Minima genauso an wie in den WLAN-Projekten:
**5V, GND, TX, RX** - vier Drähte, sonst nichts.

.. note::

    Das Modul zieht beim Start einen hohen Strom. Stecken Sie deshalb die 9-V-Batterie
    bzw. das externe Netzteil in die Hohlbuchse des R4 Minima.


.. image:: ../img/wiring_r4_espc201.png
   :width: 80%


2. Sketch hochladen
--------------------

#. Öffnen Sie ``00-Bluetooth_start.ino`` unter dem Pfad ``ultimate-sensor-kit\code\iot_project_espc201\bluetooth\00-Bluetooth_start``.

#. Wählen Sie **Arduino UNO R4 Minima** und den richtigen Port und klicken Sie auf
   **Upload**.

   Der Sketch macht drei Dinge:

   * Er bindet ``SunFounder_BLE.h`` ein, eine kleine Hülle um die Bluetooth-Befehle des
     Moduls - deshalb braucht der übrige Code nur ``bleSerial.print()`` und
     ``bleSerial.read()``;
   * beim Start schaltet die Hülle Bluetooth ein, setzt den Namen auf **SunFounder-C2**
     und beginnt zu werben, damit ein Handy es findet;
   * danach reicht der Sketch einfach Text in beide Richtungen durch.

   .. image:: ../img/ble_start_code.png
      :width: 80%

#. Öffnen Sie den Seriellen Monitor mit **115200**. Sie sollten lesen:

   .. code-block:: text

      === ESPC2-01 Bluetooth (BLE) ===
      [OK] BLE is ready - scan for "SunFounder-C2" on your phone
      --------------------------------
      Type here and press Enter: the text is sent to the phone (C305)

   .. image:: ../img/ble_start_serial.png
      :width: 80%

   Steht dort stattdessen ``[!] no reply from the module``, antwortet das Modul nicht auf
   D0/D1 - prüfen Sie die vier Drähte und das Netzteil und drücken Sie dann die
   Reset-Taste auf der Platine.


3. Modul mit dem Handy finden
----------------------------------

#. Installieren Sie **LightBlue** auf Ihrem Handy - die App ist für iOS und Android
   kostenlos. Jeder Bluetooth-Scanner funktioniert, die Bilder unten zeigen LightBlue.

   .. image:: ../img/ble_lightblue_app.png
      :width: 20%

#. Öffnen Sie LightBlue und tippen Sie auf **Scan**. Das Modul erscheint als
   **SunFounder-C2**.

   .. note::

      Der Name kommt aus dem Sketch. Ändern Sie ihn dort, erscheint der neue Name auf dem
      Handy - praktisch, wenn mehrere Kits im selben Raum stehen.

   .. warning::

      **Koppeln Sie das Modul nicht in den Bluetooth-Einstellungen des Handys.** Das ist
      BLE, es gibt nichts zu koppeln: LightBlue baut die Verbindung selbst auf. Wenn Sie
      **SunFounder-C2** unter *Einstellungen > Bluetooth* antippen, startet Android oder
      iOS den älteren Kopplungsvorgang und fragt nach einer PIN - und das Modul hat keine
      PIN, die Eingabe kann also nie passen.

      Falls Sie es schon versucht haben: Öffnen Sie *Einstellungen > Bluetooth*, wählen
      Sie **Gerät entfernen** (oder *Entkoppeln*), schalten Sie Bluetooth aus und wieder
      ein und verbinden Sie sich dann aus LightBlue.

   .. image:: ../img/ble_lightblue_scan.png
      :width: 80%

#. Tippen Sie auf **SunFounder-C2**, um sich zu verbinden. Die Dienstliste öffnet sich.

#. Klappen Sie den Dienst **0xA002** auf. Er enthält die Characteristics **C300** bis
   **C307**. Die drei aus diesem Kapitel sind:

   .. list-table::
      :header-rows: 1
      :widths: 17 26 57

      * - Characteristic
        - Richtung
        - Wofür
      * - **C304**
        - Handy -> Platine
        - hier schreibt das Handy Text, die Platine liest ihn
      * - **C305**
        - Platine -> Handy
        - hier schickt die Platine Text; das Handy muss vorher **Subscribe** wählen
      * - **C300**
        - Platine -> Handy
        - ein gespeicherter Wert, den das Handy jederzeit **Read** lesen kann

   .. image:: ../img/ble_lightblue_expand.png
      :width: 80%


4. Text vom Handy zur Platine senden
----------------------------------------

#. Öffnen Sie **0xC304** und tippen Sie auf **Write new value**.

   .. image:: ../img/ble_lightblue_write.png
      :width: 80%

#. Stellen Sie das Format oben rechts auf **UTF-8 String** und tippen Sie ein Wort, zum
   Beispiel ``hello``.

   .. note::

      Dieser Schritt wird leicht vergessen. Im voreingestellten Hex-Format empfängt die
      Platine die Zahlen ``68 65 6C 6C 6F`` statt des Wortes ``hello``.

   .. image:: ../img/ble_lightblue_hello.png
      :width: 80%

#. Sehen Sie in den Seriellen Monitor: Ihr Text erscheint dort, und die Platine schickt
   ihn direkt zurück - so sehen Sie, dass die Strecke in beide Richtungen funktioniert.

   .. image:: ../img/ble_lightblue_serial.png
      :width: 80%


5. Text von der Platine zum Handy senden
----------------------------------------

#. Öffnen Sie **0xC305** und tippen Sie auf **Subscribe**.

   **Subscribe** heißt "halte das offen und zeige alles, was ankommt". Ohne diesen
   Schritt verwirft das Handy stillschweigend alles, was die Platine sendet.

   .. image:: ../img/ble_lightblue_subs.png
      :width: 80%

#. Tippen Sie im Seriellen Monitor ein Wort und drücken Sie **Enter**. Der Sketch leitet
   es an C305 weiter, es erscheint also in LightBlue.

   .. image:: ../img/ble_ide_send.png
      :width: 80%

#. Sehen Sie in LightBlue Hex-Zahlen statt Ihres Textes, stellen Sie das Format oben
   rechts auf **UTF-8 String** - dieselbe Einstellung wie in Schritt 4.

   .. image:: ../img/ble_ide_receive.png
      :width: 80%


6. Was Sie gerade gelernt haben
------------------------

* **Write** (C304) - das Handy sendet Daten an die Platine.
* **Subscribe** (C305) - die Platine sendet Daten an das Handy, und das Handy hört zu.
* **Read** (C300) - das Handy fragt einen Wert ab, wann es will.

Die nächsten Kapitel nutzen genau diese drei, es ändern sich nur Text und Hardware: ein
LCD, das zeigt, was Sie tippen, ein Schloss, das aufgeht, eine RGB-Lampe, die die Farbe
wechselt.
