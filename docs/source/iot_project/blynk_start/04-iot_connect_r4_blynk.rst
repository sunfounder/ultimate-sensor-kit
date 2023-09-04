.. _connect_blynk:

1.4 Verbindung des R4-Boards mit Blynk herstellen
-------------------------------------------------

#. Verbinden Sie das ESP8266-Modul und das R4-Board erneut. Hier wird die Software-Schnittstelle verwendet, sodass TX und RX jeweils mit den Pins 2 und 3 des R4-Boards verbunden sind.

  .. note::

       Das ESP8266-Modul benötigt einen hohen Strom, um eine stabile Betriebsumgebung zu gewährleisten. Stellen Sie daher sicher, dass die 9V-Batterie angeschlossen ist.

  .. image:: img/wiring_r4_quickstart.png

#. Öffnen Sie die Datei ``00-Blynk_quick_start.ino`` unter dem Pfad ``ultimate-sensor-kit\iot_project\wifi\00-Blynk_quick_start``. Oder kopieren Sie diesen Code in die **Arduino IDE**.

   .. raw:: html
       
       <iframe src=https://create.arduino.cc/editor/sunfounder01/421997b2-aaa7-45d7-926a-f0aec50db99a/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

#. Ersetzen Sie die folgenden drei Codezeilen, die Sie von der **Geräteinfo**-Seite Ihres Kontos kopieren können. Diese drei Zeilen ermöglichen es dem R4-Board, Ihr Blynk-Konto zu finden.

   .. code-block:: arduino

       #define BLYNK_TEMPLATE_ID "TMPLxxxxxx"
       #define BLYNK_DEVICE_NAME "Device"
       #define BLYNK_AUTH_TOKEN "YourAuthToken"
   
   .. image:: img/sp20220614174721.png

#. Geben Sie die ``ssid`` und das ``Passwort`` des verwendeten WLANs ein.

   .. code-block:: arduino

       char ssid[] = "ssid";
       char pass[] = "password";

#. Laden Sie den Code auf das R4-Board, öffnen Sie dann den seriellen Monitor und stellen Sie die Baudrate auf 115200 ein. Wenn das R4-Board erfolgreich mit Blynk kommuniziert, wird im seriellen Monitor das Zeichen ``ready`` angezeigt.

   .. image:: img/sp220607_170223.png

   .. note::
   
       Sollte die Meldung ``ESP is not responding`` erscheinen, befolgen Sie bitte diese Schritte:

       * Stellen Sie sicher, dass die 9V-Batterie angeschlossen ist.
       * Setzen Sie das ESP8266-Modul zurück, indem Sie den Pin RST für 1 Sekunde auf GND legen und dann wieder entfernen.
       * Drücken Sie die Reset-Taste auf dem R4-Board.

       Manchmal müssen Sie die obigen Schritte 3-5 Mal wiederholen. Bitte haben Sie Geduld.

#. Der Status von Blynk ändert sich von **offline** auf **online**.

    .. image:: img/sp220607_170326.png
