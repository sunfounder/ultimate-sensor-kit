.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

.. _config_esp8266:

1.1 Konfiguration des ESP8266
===============================

Das im Kit enthaltene ESP8266-Modul ist bereits mit der AT-Firmware vorinstalliert. Dennoch müssen Sie seine Konfiguration gemäß den folgenden Schritten anpassen.

1. Bauen Sie den Schaltkreis.

   .. image:: img/wiring_r4_configure.png
       :width: 800

2. Öffnen Sie die Datei ``00-Set_software_serial.ino`` unter dem Pfad ``ultimate-sensor-kit\iot_project\wifi\00-Set_software_serial``. Oder kopieren Sie diesen Code in die Arduino-IDE und laden Sie den Code hoch.

   Der Code etabliert eine softwaregesteuerte serielle Kommunikation mit Hilfe der SoftwareSerial-Bibliothek von Arduino. Dadurch kann das Arduino-Board mit dem ESP8266-Modul über die digitalen Pins 2 und 3 (als Rx und Tx) kommunizieren. Es prüft die Datenübertragung zwischen den beiden und leitet empfangene Nachrichten mit einer Baudrate von 115200 weiter. **Mit diesem Code können Sie den seriellen Monitor des Arduino verwenden, um AT-Firmware-Befehle an das ESP8266-Modul zu senden und dessen Antworten zu empfangen.**

   .. code-block:: Arduino

       #include <SoftwareSerial.h>
       SoftwareSerial espSerial(2, 3); //Rx,Tx

       void setup() {
           // Put your setup code here, to run once:
           Serial.begin(115200);
           espSerial.begin(115200);
       }

       void loop() {
           if (espSerial.available()) {
               Serial.write(espSerial.read());
           }
           if (Serial.available()) {
               espSerial.write(Serial.read());
           }
       }

3. Klicken Sie auf das Lupensymbol (Serial Monitor) in der oberen rechten Ecke und stellen Sie die Baudrate auf **115200** ein. (Sie könnten einige Informationen wie ich gedruckt haben oder auch nicht, das spielt keine Rolle, gehen Sie einfach zum nächsten Schritt über.)

   .. image:: img/esp01_configurie_1.png

   .. warning::

        * Sollte ``ready`` nicht erscheinen, können Sie versuchen, das ESP8266-Modul zurückzusetzen (RST an GND anschließen) und den Serial Monitor erneut zu öffnen.

        * Falls das Ergebnis ``OK`` lautet, müssen Sie möglicherweise die Firmware erneut brennen. Bitte beziehen Sie sich für Details auf :ref:`burn_firmware`. Sollten Sie immer noch Probleme haben, machen Sie bitte einen Screenshot des seriellen Monitors und senden Sie ihn an sevice@sunfounder.com. Wir werden Ihnen so schnell wie möglich weiterhelfen.

4. Klicken Sie auf **NEWLINE DROPDOWN BOX**, wählen Sie ``both NL & CR`` im Dropdown-Menü aus, geben Sie ``AT`` ein; wenn OK zurückgegeben wird, bedeutet dies, dass die Verbindung zwischen ESP8266 und R4-Board erfolgreich hergestellt wurde.

   .. image:: img/esp01_configurie_2.png

   .. image:: img/esp01_configurie_3.png

5. Geben Sie ``AT+CWMODE=3`` ein, um den Verwaltungsmodus auf **Station und AP**-Koexistenz zu ändern.

   .. image:: img/esp01_configurie_4.png

.. 6. Um später die Software-Seriell nutzen zu können, müssen Sie ``AT+UART=9600,8,1,0,0`` eingeben, um die Baudrate des ESP8266 auf 9600 zu ändern.

..    .. image:: img/esp01_configurie_5.png


**Referenzen**

* |link_esp8266_at|
