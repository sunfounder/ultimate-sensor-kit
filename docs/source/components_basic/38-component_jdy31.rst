.. _cpn_jdy31:

JDY-31 Bluetooth-Modul
=====================================

.. image:: img/38_JDY31_1.jpg
    :align: center

.. warning::
  Dieses Modul **unterstützt keine Verbindungen mit Apple-Geräten**, daher sind für Tutorials mit diesem Modul ein Android-Smartphone oder -Tablet erforderlich.

Das JDY-31 Bluetooth-Modul dient als pin-kompatibler Ersatz für das HC-06 Bluetooth-Modul. Es ist unkomplizierter und einfacher in der Anwendung als das HC-06 und oft zu einem etwas geringeren Preis erhältlich.

Das JDY-31 Bluetooth-Modul basiert auf dem Bluetooth 3.0 SPP-Design und unterstützt die Datenübertragung unter Windows, Linux und Android. Die Betriebsfrequenz des JDY-31 Bluetooth-Moduls beträgt 2,4 GHz mit der Modulationsart GFSK. Die maximale Sendeleistung beträgt 8 dB, und die maximale Übertragungsentfernung liegt bei 30 Metern. Über AT-Befehle können Benutzer den Gerätenamen, die Baudrate und weitere Einstellungen ändern.

Pins des JDY-31 und ihre Funktionen:

.. image:: img/38_JDY31_2.jpg
    :align: center

.. list-table:: JDY-31 Pins
   :widths: 25 25 100
   :header-rows: 1

   * - Pin	
     - Bezeichnung	
     - Beschreibung
   * - 1	
     - STATE
     - Statuspin für die Verbindung (niedriges Niveau bei fehlender Verbindung, hohes Niveau nach Verbindung)
   * - 2	
     - RXD	
     - Empfängerpin, dieser Pin muss mit dem TX-Pin des nächsten Geräts verbunden sein.
   * - 3	
     - TXD
     - Senderpin, dieser Pin muss mit dem RX-Pin des nächsten Geräts verbunden sein.
   * - 4		
     - GND
     - Masse (GND)
   * - 5	
     - VCC
     - Stromversorgung (1,8-3,6V, empfohlen 3,3V)
   * - 6	
     - EN
     - Aktiviert oder deaktiviert das Modul. Wird dieser Pin auf hohem Niveau gehalten, ist das Modul aktiv und beginnt mit der Datenübertragung.

Patch-Anwendung: Für allgemeine Anwendungen müssen nur die Pins VCC, GND, RXD und TXD verbunden werden. Um die Verbindung aktiv zu trennen, senden Sie im Verbindungsstatus den Befehl AT+DISC.

AT-Befehlssatz
---------------------------

+------------+---------------------------------------------+-------------+
|   Befehl   |                   Funktion                  |   Standard  |
+============+=============================================+=============+
| AT+VERSION | Versionsnummer                              | JDY-31-V1.2 |
+------------+---------------------------------------------+-------------+
| AT+RESET   | Soft-Reset                                  |             |
+------------+---------------------------------------------+-------------+
| AT+DISC    | Trennen (gültig bei bestehender Verbindung) |             |
+------------+---------------------------------------------+-------------+
| AT+LADDR   | MAC-Adresse des Moduls abfragen             |             |
+------------+---------------------------------------------+-------------+
| AT+PIN     | Verbindungspasswort setzen oder abfragen    | 1234        |
+------------+---------------------------------------------+-------------+
| AT+BAUD    | Baudrate setzen oder abfragen               | 9600        |
+------------+---------------------------------------------+-------------+
| AT+NAME    | Sendenamen setzen oder abfragen             | JDY-31-SPP  |
+------------+---------------------------------------------+-------------+
| AT+DEFAULT | Werkseinstellungen wiederherstellen         |             |
+------------+---------------------------------------------+-------------+
| AT+ENLOG   | Statusausgabe der seriellen Schnittstelle   | 1           |
+------------+---------------------------------------------+-------------+

Weitere Projekte
---------------------------

* :ref:`iot_Bluetooth_start`
* :ref:`iot_Bluetooth_lcd`
* :ref:`iot_Bluetooth_traffic_light`
* :ref:`iot_Bluetooth_lock_controller`
* :ref:`iot_Bluetooth_RGB_controller`
* :ref:`iot_Bluetooth_environmental_monitor`
* :ref:`iot_Bluetooth_piano`
* :ref:`iot_Bluetooth_oled`
* :ref:`iot_Bluetooth_remote_relay`
* :ref:`iot_Bluetooth_voice_control_relay`

