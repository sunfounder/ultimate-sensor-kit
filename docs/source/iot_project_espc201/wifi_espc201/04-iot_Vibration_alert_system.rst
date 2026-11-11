.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

.. _c201_iot_Vibration_alert_system:

4. Vibrationswarnsystem mit IFTTT
========================================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../../_static/video/iot/04-iot_Vibration_alert_system.mp4"  type="video/mp4">
      Ihr Browser unterstützt das Video-Tag nicht.
   </video>

Auf dem Tisch steht ein Vibrationsschalter (SW-420). Wird an den Tisch gestoßen, meldet
die Platine das an IFTTT, und IFTTT schickt Ihnen eine E-Mail.

Dieses Projekt nutzt **kein Blynk**. Es sendet eine einfache HTTP-Anfrage direkt an IFTTT,
Sie sehen also, was das Modul mit einem AT-Befehl wie ``AT+CIPSEND`` wirklich tut -
dasselbe, was Ihr Browser beim Öffnen einer Webseite macht.

Damit Ihr Postfach ruhig bleibt, liegen zwei Warnungen immer mindestens **zwei Minuten**
auseinander.


1. Schaltung aufbauen
-----------------------------

.. note::

    Das Modul zieht beim Start einen hohen Strom. Stecken Sie deshalb die 9-V-Batterie
    bzw. das externe Netzteil in die Hohlbuchse des R4 Minima.


   .. image:: ../img/04-Wiring_Vibration_alert_system_c201.png
      :width: 80%


* :ref:`cpn_uno`
* :ref:`cpn_espc201`
* :ref:`cpn_vibration`


2. IFTTT einrichten
-----------------------------

|link_ifttt| ist ein kostenloser Dienst, der Apps mit einer einfachen Regel verbindet:

> **Wenn dies passiert, dann passiert das.**

Hier brauchen wir zwei Teile:

* **If This** - jemand rüttelt am Sensor. IFTTT gibt uns eine private Webadresse, die
  die Platine aufrufen kann.
* **Then That** - eine E-Mail senden. Das ist die Aktion.


   .. image:: ../img/04-ifttt_intro.png
      :width: 80%


**2.1 Bei IFTTT anmelden**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#. Öffnen Sie https://ifttt.com im Browser und klicken Sie auf **Start building**.
   Füllen Sie das Formular aus, um ein Konto anzulegen.

   .. image:: ../img/04-ifttt_signup.png
      :width: 80%

#. Klicken Sie auf **start building**.

   .. image:: ../img/ifttt_start_building.png
      :width: 80%

#. Wählen Sie den Modus **Classic**.

   .. image:: ../img/ifttt_choose_classic.png
      :width: 80%


**2.2 If This - der Auslöser**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#. Klicken Sie neben **If This** auf **Add**.

   .. image:: ../img/04-ifttt_create_applet_2_shadow.png
      :width: 80%

#. Suchen Sie nach **webhook** und klicken Sie auf **Webhooks**.

   .. image:: ../img/04-ifttt_create_applet_3_shadow.png
      :width: 80%

#. Klicken Sie auf **Receive a web request**. Diesen Dienst ruft die Platine auf.

   .. image:: ../img/04-ifttt_create_applet_4_shadow.png
      :width: 80%

#. Setzen Sie den **Event Name** auf **vibration_detected** und klicken Sie auf
   **Create trigger**.

   .. note::

      Dieser Name wird Teil der Adresse, er muss also mit der ``URL`` im Sketch
      übereinstimmen. Verwenden Sie hier einen anderen Namen, ändern Sie ihn dort ebenfalls.

   .. image:: ../img/04-ifttt_create_applet_5_shadow.png
      :width: 80%


**2.3 Then That - die Aktion**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#. Klicken Sie neben **Then That** auf **Add**, um eine Aktion hinzuzufügen.

   .. image:: ../img/04-ifttt_create_applet_6_shadow.png
      :width: 80%

#. Suchen Sie nach **email** und klicken Sie auf **Email**.

   .. image:: ../img/04-ifttt_create_applet_7_shadow.png
      :width: 80%

#. Klicken Sie auf **Send me an email**.

   .. image:: ../img/04-ifttt_create_applet_8_shadow.png
      :width: 80%

#. Schreiben Sie Betreff und Text der E-Mail.

   Zum Beispiel:

   * **Subject**: ``Detected vibration!!!``
   * **Body**: ``Detected vibration, please confirm the situation promptly! {{OccurredAt}}``

   ``{{OccurredAt}}`` ersetzt IFTTT durch den genauen Zeitpunkt des Ereignisses -
   praktisch, wenn Sie die Mail am nächsten Morgen lesen.

   .. image:: ../img/04-ifttt_create_applet_9_shadow.png
      :width: 80%

#. Schließen Sie den Assistenten über die folgenden Bildschirme ab.

   .. image:: ../img/04-ifttt_create_applet_10_shadow.png
      :width: 80%

   .. image:: ../img/04-ifttt_create_applet_11_shadow.png
      :width: 80%


3. Code ausführen
-----------------------------

#. Öffnen Sie die Datei ``04-Vibration_alert_system.ino`` unter dem Pfad ``ultimate-sensor-kit\code\iot_project_espc201\wifi\04-Vibration_alert_system`` oder kopieren Sie den Code in die **Arduino IDE**.

#. Tragen Sie Namen und Passwort Ihres WLAN-Netzes ein.

   .. code-block:: arduino

      String mySSID = "your_ssid";
      String myPWD  = "your_password";

#. Öffnen Sie in IFTTT die Seite **My Applets** und klicken Sie auf das eben erstellte
   Applet.

   .. image:: ../img/04_ifttt_my_applets.png
      :width: 80%

#. Kopieren Sie Ihre Webhook-URL.

   .. image:: ../img/04_ifttt_webhook_url.png
      :width: 60%

#. Fügen Sie die **ganze** Adresse, die IFTTT zeigt, in ``URL`` ein - **mit https://**,
   genau so, wie Sie sie kopiert haben.

   .. code-block:: arduino

      String URL = "https://maker.ifttt.com/trigger/vibration_detected/with/key/xxxxxxxxxxxxxxxxxx";

   Sie müssen nichts abschneiden. Der Sketch behält vor dem Senden nur den Teil nach dem
   Hostnamen, weil das Modul einfaches TCP auf Port 80 spricht.

#. Wählen Sie **Arduino UNO R4 Minima** und den richtigen Port und klicken Sie auf
   **Upload**.

#. Öffnen Sie den Seriellen Monitor mit **115200**. Nach wenigen Sekunden sollten Sie
   lesen:

   .. code-block:: text

      === Vibration Alert System (IFTTT) ===
      module is ready
      joining Wi-Fi ... connected
      Detecting...

   Steht dort ``FAILED (check ssid and password)``, kann die Platine Ihr Netz nicht
   betreten - prüfen Sie WLAN-Name und Passwort, und denken Sie daran, dass das ESPC2-01
   nur **2,4 GHz** kann.

   .. image:: ../img/04-ready_shadow.png
      :width: 80%

#. Klopfen Sie an den Sensor. Der Monitor antwortet mit

   .. code-block:: text

      Detected vibration!!!
        > AT+CIPMUX=0
        > AT+CIPSTART="TCP","maker.ifttt.com",80
        > AT+CIPSEND=118
        request sent to IFTTT

   und innerhalb weniger Sekunden kommt eine E-Mail an.

   .. note::

      Klopfen Sie zweimal hintereinander: Beim zweiten Mal steht nur ``An alert was sent
      recently, so this one is skipped.`` Das ist die Zwei-Minuten-Regel bei der Arbeit,
      kein Fehler.


4. Code-Erklärung
-----------------------------

#. **Die serielle Schnittstelle zum Modul**

   Das ESPC2-01 führt diesen Sketch nicht aus - es arbeitet als Modem. Die Platine sendet
   ihm AT-Befehle auf D0/D1, also über ``Serial1``, eine Hardware-Schnittstelle; 115200
   funktioniert dort ohne Bitfehler.

   .. code-block:: arduino

      #define EspSerial Serial1

#. **Was Sie eintragen müssen**

   .. code-block:: arduino

      String mySSID = "your_ssid";
      String myPWD  = "your_password";
      String myHOST = "maker.ifttt.com";
      String myPORT = "80";

      String URL = "https://maker.ifttt.com/trigger/vibration_detected/with/key/xxxxxxxxxx";

   Sie kopieren die Adresse so, wie IFTTT sie zeigt - **mit https://** -, und der Sketch
   wandelt sie um:

   .. code-block:: arduino

      String urlPath() {
        String u = URL;
        u.replace("https://", "");
        u.replace("http://", "");
        int slash = u.indexOf('/');
        return (slash >= 0) ? u.substring(slash) : "/";
      }

   ``myHOST`` und ``myPORT`` ändern sich nie: IFTTT antwortet immer auf Port 80 von
   ``maker.ifttt.com``. Nur der Pfad ist persönlich, denn er trägt Ihren Key.

   .. note::

      Warum nicht ``https://`` direkt ans Modul geben? HTTPS bedeutet TLS: Das Modul müsste
      eine gesicherte Verbindung mit Zertifikaten aufbauen, was eine viel längere
      AT-Sequenz wäre. IFTTT nimmt dieselbe Anfrage auch auf einfachem **Port 80** an,
      der kurze Weg genügt hier also.

#. **Vibrations-Pin und die Zwei-Minuten-Regel**

   .. code-block:: arduino

      unsigned long lastAlertTime = 0;
      const unsigned long postingInterval = 120000L;   // 2 Minuten

      const int sensorPin = 7;

   Der SW-420 liefert einen einfachen Pegel: Er geht **während des Rüttelns auf HIGH**.
   Ohne die Zwei-Minuten-Regel würde ein einziger Stoß Dutzende Mails auslösen.

#. **espModuleInit() - das Modul zuerst aufwecken**

   Das Modul braucht etwa eine Sekunde zum Starten und gibt sein Startprotokoll über
   dieselbe Leitung aus. Diese Funktion wartet auf das Wort ``ready`` und sendet dann
   ``ATE0``, damit in den Antworten nicht mehr der gerade gesendete Befehl mitläuft.

   .. code-block:: arduino

      void espModuleInit() {
        unsigned long t0 = millis();
        String buf;
        while (millis() - t0 < 5000) {
          while (EspSerial.available() && buf.length() < 512) {
            buf += (char)EspSerial.read();
            if (buf.indexOf("ready") >= 0) t0 = millis() - 5000;
          }
          if (buf.indexOf("ready") >= 0) break;
        }
        while (EspSerial.available()) EspSerial.read();
        EspSerial.print("ATE0\r\n");
        delay(300);
        while (EspSerial.available()) EspSerial.read();
      }

   Die Prüfung ``buf.length() < 512`` ist wichtig: Ohne sie würde ein dauerhaft
   sprechendes Modul die innere Schleife endlos beschäftigen und der Sketch käme nie zu
   ``setup()``.

#. **at() - ein AT-Befehl mit Zeitlimit**

   .. code-block:: arduino

      String at(const String& cmd, unsigned long waitMs, const char* okMark, const char* errMark) {
        while (EspSerial.available()) EspSerial.read();
        EspSerial.print(cmd);
        EspSerial.print("\r\n");

        unsigned long t0 = millis();
        String r;
        while (millis() - t0 < waitMs) {
          while (EspSerial.available() && r.length() < 512) r += (char)EspSerial.read();
          if (okMark && r.indexOf(okMark) >= 0) break;
          if (errMark && r.indexOf(errMark) >= 0) break;
        }
        return r;
      }

   Jeder Befehl läuft durch diese eine Funktion: Sie sendet, sammelt die Antwort und hört
   auf, sobald die erwartete Antwort - oder ein Fehler - erscheint. Sie **kehrt immer
   zurück**, die Platine kann also nie auf ein fehlendes ``OK`` warten.

#. **setup() und loop()**

   .. code-block:: arduino

      void setup() {
        Serial.begin(115200);
        EspSerial.begin(115200);
        espModuleInit();
        Serial.println("module is ready");
        wifiOK = joinWiFi();
      }

      void loop() {
        if (!wifiOK && millis() - lastRetry > 30000) {
          lastRetry = millis();
          wifiOK = joinWiFi();
        }
        ...
        delay(500);
      }

   Ist das WLAN beim Start nicht da, gibt der Sketch nicht auf: Er versucht es alle 30
   Sekunden erneut. Deshalb können Sie die Platine starten, bevor der Router bereit ist.

#. **sendAlert() - eine HTTP-Anfrage**

   .. code-block:: arduino

      String req = "GET " + URL + " HTTP/1.1\r\n";
      req += "Host: maker.ifttt.com\r\n";
      req += "Connection: close\r\n\r\n";

      at("AT+CIPMUX=0", 1000, "OK", "ERROR");
      at("AT+CIPSTART=\"TCP\",\"" + myHOST + "\"," + myPORT, 5000, "OK", "ERROR");
      ...
      EspSerial.print("AT+CIPSEND=");
      EspSerial.print(req.length());
      ...
      EspSerial.print(req);

   Drei AT-Befehle erledigen die Arbeit:

   * ``AT+CIPMUX=0`` - eine Verbindung zur Zeit.
   * ``AT+CIPSTART`` - eine TCP-Verbindung zu ``maker.ifttt.com:80`` öffnen.
   * ``AT+CIPSEND=<Länge>`` - das Modul antwortet mit ``>``, und erst dann senden Sie den
     Text der Anfrage. Die Länge muss der genauen Zeichenzahl entsprechen, deshalb misst
     der Sketch ``req.length()`` statt zu raten.

   Die Anfrage selbst ist das, was auch Ihr Browser sendet: eine Zeile mit Methode und
   Pfad, ein Header, eine leere Zeile, sonst nichts. IFTTT löst das Applet aus, sobald es
   den Pfad liest.
