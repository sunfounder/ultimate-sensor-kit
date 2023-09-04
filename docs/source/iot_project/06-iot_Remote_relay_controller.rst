.. _iot_Remote_relay_controller:

Ferngesteuerter Relais-Controller mit Blynk
============================================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/iot/06-iot_Remote_relay_controller.mp4"  type="video/mp4">
      Ihr Browser unterstützt das Video-Tag nicht.
   </video>

Dieses Projekt zielt darauf ab, einen ferngesteuerten Relais-Controller zu entwickeln, der über einen virtuellen Schalter in der Blynk-App bedient werden kann. Wenn der Schalter eingeschaltet wird, wird der mit dem Relais verbundene digitale Pin auf HIGH gesetzt. Wird der Schalter ausgeschaltet, wird der Pin auf LOW gesetzt. Dies ermöglicht eine einfache Fernsteuerung des Relais und fungiert effektiv als Fernschalter.

1. Schaltkreis aufbauen
-----------------------------

.. warning ::
    Das folgende Beispiel zeigt, wie ein Relais zur Steuerung eines LED-Moduls verwendet wird.
    **Obwohl Sie das Relais in realen Anwendungen auch an andere Geräte anschließen können, ist bei der Arbeit mit HOCHSPANNUNG-Wechselstrom äußerste Vorsicht geboten. Unsachgemäße oder fehlerhafte Verwendung kann zu schweren Verletzungen oder sogar zum Tod führen. Dies ist daher nur für Personen gedacht, die mit HOCHSPANNUNG vertraut sind und darüber Bescheid wissen. Sicherheit hat immer Vorrang.**

.. note::

    Das ESP8266-Modul benötigt einen hohen Strom, um eine stabile Betriebsumgebung zu gewährleisten. Stellen Sie daher sicher, dass die 9V-Batterie angeschlossen ist.

.. image:: img/06-Wiring_Remote_relay_controller.png
    :width: 100%


* :ref:`cpn_uno`
* :ref:`cpn_esp8266`
* :ref:`cpn_relay`
* :ref:`cpn_traffic`


2. Blynk konfigurieren
-----------------------------

.. note::
    Wenn Sie noch nicht mit Blynk vertraut sind, wird dringend empfohlen, zunächst diese beiden Tutorials zu lesen. :ref:`iot_blynk_start` ist ein Einsteigerleitfaden für Blynk, der auch die Konfiguration des ESP8266 und die Registrierung bei Blynk umfasst. Und :ref:`iot_Flame` ist ein einfaches Beispiel, jedoch werden die Schritte darin ausführlicher beschrieben.

**2.1 Vorlage erstellen**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Zuerst müssen wir eine Vorlage in Blynk erstellen. Erstellen Sie eine **"Ferngesteuertes Relais"**-Vorlage.

**2.2 Datenströme**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Erstellen Sie **Datastreams** vom Typ **Virtual Pin** auf der **Datastreams**-Seite, um Daten vom esp8266 und uno r4 Board zu empfangen.

* Erstellen Sie den virtuellen Pin V0 gemäß dem folgenden Diagramm:

  Benennen Sie den **Virtual Pin V0** in **Switch status** um. Setzen Sie den **DATA TYPE** auf **Integer** und MIN und MAX auf **0** und **1**. Setzen Sie die **UNITS** auf **None**.

  .. image:: img/new/06-datastream_1_shadow.png
      :width: 90%

.. raw:: html
    
    <br/> 


**2.3 Web-Dashboard**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Das **Web-Dashboard** muss ebenfalls konfiguriert werden, um mit dem ferngesteuerten Relais zu interagieren.

Konfigurieren Sie das Web-Dashboard entsprechend dem folgenden Diagramm. Stellen Sie sicher, dass jedes Widget an seinen entsprechenden virtuellen Pin gebunden ist.

.. image:: img/new/06-web_dashboard_1_shadow.png
    :width: 65%
    :align: center

.. raw:: html



3. Den Code ausführen
-----------------------------

#. Öffnen Sie die Datei ``06-Remote_relay_controller.ino`` unter dem Pfad ``ultimate-sensor-kit\iot_project\wifi\06-Remote_relay_controller``, oder kopieren Sie diesen Code in die **Arduino IDE**.

   .. raw:: html
       
       <iframe src=https://create.arduino.cc/editor/sunfounder01/33324acd-40b6-470f-99f4-d86f4d0fb2f8/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

#. Legen Sie ein Blynk-Gerät mit der Vorlage "Ferngesteuertes Relais" an. Ersetzen Sie dann die Werte für ``BLYNK_TEMPLATE_ID``, ``BLYNK_TEMPLATE_NAME`` und ``BLYNK_AUTH_TOKEN`` durch Ihre eigenen.

   .. code-block:: arduino
    
      #define BLYNK_TEMPLATE_ID "TMPxxxxxxx"
      #define BLYNK_TEMPLATE_NAME "Remote relay"
      #define BLYNK_AUTH_TOKEN "xxxxxxxxxxxxx"

#. Geben Sie auch die ``ssid`` und das ``Passwort`` des verwendeten WLANs ein.

   .. code-block:: arduino

    char ssid[] = "Ihre_ssid";
    char pass[] = "Ihr_Passwort";

#. Nach Auswahl des korrekten Boards und Ports klicken Sie auf die Schaltfläche **Hochladen**.

#. Öffnen Sie den seriellen Monitor (Baudrate auf 115200 einstellen) und warten Sie auf eine Meldung, die eine erfolgreiche Verbindung anzeigt.

   .. image:: img/new/02-ready_1_shadow.png
    :width: 80%
    :align: center

   .. note::

       Sollte die Meldung ``ESP is not responding`` erscheinen, befolgen Sie diese Schritte.

       * Stellen Sie sicher, dass die 9V-Batterie angeschlossen ist.
       * Setzen Sie das ESP8266-Modul zurück, indem Sie den Pin RST für 1 Sekunde mit GND verbinden, dann ziehen Sie den Stecker.
       * Drücken Sie die Reset-Taste auf dem R4-Board.

       Manchmal müssen Sie die oben genannten Schritte 3-5 Mal wiederholen. Bitte haben Sie Geduld.



4. Code-Erklärung
-----------------------------

1. Einrichten der Blynk-Zugangsdaten:

   Dieser Abschnitt enthält spezifische Einstellungen für die Blynk-App, wie zum Beispiel die Template-ID, den Gerätenamen und den Authentifizierungstoken.

   .. code-block:: arduino

      #define BLYNK_TEMPLATE_ID "TMPLxxxxxxxx"
      #define BLYNK_TEMPLATE_NAME "Remote relay"
      #define BLYNK_AUTH_TOKEN "xxxxxxxxxxx"

2. Einbindung der erforderlichen Bibliotheken:

   Hier binden wir die für das Projekt erforderlichen Bibliotheken ein. Diese ermöglichen die Kommunikation unseres Arduino über WiFi und die Interaktion mit der Blynk-App.
   
   .. code-block:: arduino

      #define BLYNK_PRINT Serial
      #include <ESP8266_Lib.h>
      #include <BlynkSimpleShieldEsp8266.h>
      #include <SoftwareSerial.h>

3. Konfiguration von WiFi und seriellen Einstellungen:

   Die SSID und das Passwort für das WiFi werden festgelegt. Darüber hinaus werden die Pins für die Software-Serienkommunikation mit dem ESP01 definiert. ``ESP8266_BAUD`` legt die Baudrate für das ESP8266-Modul fest.
   
   .. code-block:: arduino

      char ssid[] = "Ihre_ssid";
      char pass[] = "Ihr_Passwort";
      SoftwareSerial EspSerial(2, 3);  // RX, TX
      #define ESP8266_BAUD 115200
      ESP8266 wifi(&EspSerial);

4. Definition des Relais-Pins:

   Wir definieren den digitalen Pin des Arduino, der zur Steuerung des Relais dient. Zudem initialisieren wir eine Variable ``switchStatus``, um den Zustand unseres virtuellen Schalters in der Blynk-App zu speichern.
   
   .. code-block:: arduino

      const int RelayPin = 6;
      int switchStatus = 0;

5. Die Funktion setup():

   In dieser Funktion initialisieren wir den Relais-Pin als Ausgang, starten die serielle Kommunikation für Debugging-Zwecke und stellen die Verbindung zu Blynk mit den angegebenen WiFi-Zugangsdaten her.
   
   .. code-block:: arduino

      void setup() {
        pinMode(RelayPin, OUTPUT);
        Serial.begin(115200);
        EspSerial.begin(ESP8266_BAUD);
        delay(10);
        Blynk.config(wifi, BLYNK_AUTH_TOKEN);
        Blynk.connectWiFi(ssid, pass);
      }

6. Die Funktion loop():

   Sie führt kontinuierlich zwei essenzielle Funktionen aus, um die Verbindung zu Blynk aufrechtzuerhalten und Ereignisse (wie Änderungen an virtuellen Pins) zu verarbeiten.
   
   .. code-block:: arduino

      void loop() {
        Blynk.run();
        timer.run();
      }

7. Steuerung des virtuellen Pins in Blynk:

   Hier lesen wir den Status des virtuellen Pins V0 aus der Blynk-App aus und steuern das Relais entsprechend. Ist der Schalter in der App aktiviert (d.h., V0 ist 1), wird der Relais-Pin auf HIGH gesetzt; ist er deaktiviert, wird er auf LOW gesetzt.

   - Jedes Mal, wenn der Wert eines virtuellen Pins auf dem BLYNK-Server ändert, wird ``BLYNK_WRITE()`` ausgelöst. Weitere Details unter |link_blynk_write|.

   .. raw:: html
    
    <br/> 
   
   .. code-block:: arduino

      // This function is called every time the Virtual Pin 0 state changes
      BLYNK_WRITE(V0) {
        switchStatus = param.asInt();  // Set incoming value from pin V0 to a variable
      
        if (switchStatus == 1) {
          Serial.println("The switch on Blynk has been turned on.");
          digitalWrite(RelayPin, HIGH);
        } else {
          Serial.println("The switch on Blynk has been turned off.");
          digitalWrite(RelayPin, LOW);
        }
      }
