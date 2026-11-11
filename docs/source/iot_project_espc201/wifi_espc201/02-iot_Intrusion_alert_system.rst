.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

.. _c201_iot_Intrusion_alert_system:

2. Einbruchwarnsystem mit Blynk
========================================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../../_static/video/iot/02-iot_Intrusion_alert_system.mp4
       "  type="video/mp4">
      Ihr Browser unterstützt das Video-Tag nicht.
   </video>

Dieses Projekt zeigt ein einfaches Einbruchwarnsystem mit einem passiven Infrarotsensor
(PIR, HC-SR501). Schalten Sie das System in der Blynk-App auf **Away**, überwacht der
PIR-Sensor den Raum. Jede erkannte Bewegung löst eine Benachrichtigung in der App aus und
warnt Sie so vor einem möglichen Einbruch.

1. Schaltung aufbauen
-----------------------------

.. note::

    Das Modul zieht beim Start einen hohen Strom. Stecken Sie deshalb die 9-V-Batterie
    bzw. das externe Netzteil in die Hohlbuchse des R4 Minima.


.. image:: ../img/02-Wiring_intrusion_alert_system_c201.png
   :width: 80%


* :ref:`cpn_uno`
* :ref:`cpn_espc201`
* :ref:`cpn_pir_motion`


2. Blynk einrichten
-----------------------------

.. note::

    Template und Gerät wurden einmalig in :ref:`c201_iot_blynk_start` angelegt. Jedes
    Projekt fügt seine Datastreams dem **selben** Template hinzu, deshalb belegt jedes
    Projekt einen eigenen Bereich der virtuellen Pins. Dieses Projekt nutzt **V1** und
    **V2**. Am Token des Geräts ändert das nichts, der Sketch läuft unverändert weiter.

**Zwei Dinge gehen in die Cloud, eines davon braucht zwei Datastreams.**

* ``away_mode`` - der Schalter, den Sie beim Verlassen des Hauses umlegen.
* ``current_status`` - eine Textzeile, die die Platine zurückschreibt, damit Sie sehen,
  was gerade passiert.

**Datastreams anlegen**

#. Öffnen Sie **Developer Zone** -> **My Templates** und klicken Sie auf **Ultimate
   Sensor Kit**.

   .. image:: ../img/blynk_template.png
      :width: 80%

#. Klicken Sie auf **Edit**, um das Template zu öffnen.

   .. image:: ../img/blynk_edit.png
      :width: 80%

#. Klicken Sie auf **Datastreams** und dann auf **Create New**.

   .. image:: ../img/blynk_new_data.png
      :width: 80%

#. Legen Sie den ersten Datastream an:

   * **DATASTREAM NAME**: ``away_mode``
   * **DISPLAY NAME**: ``Away Mode``
   * **VIRTUAL PIN**: ``V1``
   * **DATA TYPE**: **Integer**
   * **MIN** ``0``, **MAX** ``1``

   .. note::

      Ein Integer mit dem Bereich 0..1 ist die übliche Art, einen Schalter abzubilden:
      ``1`` heißt Alarmanlage scharf, ``0`` heißt aus.

   .. image:: ../img/blynk_intrusion_dataset.png
      :width: 80%

#. Klicken Sie erneut auf **Create New** für den zweiten Datastream:

   * **DATASTREAM NAME**: ``current_status``
   * **DISPLAY NAME**: ``Current Status``
   * **VIRTUAL PIN**: ``V2``
   * **DATA TYPE**: **String**

   .. note::

      Ein **String** nimmt Text auf. Die Platine sendet Zeilen wie ``Detecting signs of
      intrusion...`` oder ``Somebody in your house!``, die ein Label-Widget direkt anzeigen
      kann.

   .. image:: ../img/blynk_intrusion_v2set.png
      :width: 80%

#. In der Liste stehen jetzt beide Datastreams.

   .. image:: ../img/blynk_intrusion_2data.png
      :width: 80%

**Event anlegen**

Ein Event macht aus einem Sensorwert eine Benachrichtigung auf dem Handy. Ohne Event
ändert der Alarm nur ein Label - und das bemerkt niemand.

#. Öffnen Sie **Events & notifications** und klicken Sie auf **Create Event**.

   .. image:: ../img/blynk_intrusion_new_events.png
      :width: 80%

#. Setzen Sie den **EVENT CODE** auf ``intrusion_detected``.

   .. note::

      Schreiben Sie ihn genau so. Der Sketch ruft ``Blynk.logEvent("intrusion_detected")``
      auf, jede andere Schreibweise bewirkt stillschweigend nichts.

   .. image:: ../img/blynk_intrusion_event_code.png
      :width: 80%

#. Schalten Sie die Benachrichtigung ein und wählen Sie, wohin sie gehen soll.

   .. image:: ../img/blynk_intrusion_event_noti.png
      :width: 80%

**Web-Dashboard anlegen**

Das Dashboard ist der Teil, den Sie ansehen. Zwei Widgets genügen hier.

#. Klicken Sie auf **Dashboard** und dann auf **Add Widget**.

   .. image:: ../img/blynk_dashboard.png
      :width: 80%

#. Ziehen Sie ein **Label**-Widget auf das Dashboard.

   .. image:: ../img/blynk_dashboard_label.png
      :width: 80%

#. Fügen Sie ein **Switch**-Widget hinzu.

   .. image:: ../img/blynk_intrusion_switch.png
      :width: 80%

#. Klicken Sie auf die drei Punkte in der Ecke des **Label** und wählen Sie **Settings**.

   * Stellen Sie **Datastream** auf ``Current Status (V2)``.

   .. image:: ../img/blynk_intrusion_label_set.png
      :width: 80%

#. Machen Sie dasselbe für den **Switch**.

   * Stellen Sie **Datastream** auf ``Away Mode (V1)``, **ON LABEL** auf ``away home``
     und **OFF LABEL** auf ``at home``.

   .. image:: ../img/blynk_intrusion_switch_set.png
      :width: 80%

#. Klicken Sie auf **Save**.

   .. image:: ../img/blynk_save.png
      :width: 40%


3. Code ausführen
-----------------------------

#. Öffnen Sie die Datei ``02-Intrusion_alert_system.ino`` unter dem Pfad ``ultimate-sensor-kit\code\iot_project_espc201\wifi\02-Intrusion_alert_system`` oder kopieren Sie den Code in die **Arduino IDE**.

#. Die drei Blynk-Zeilen sind die aus dem Einsteigerkapitel. Lassen Sie sie unverändert -
   das Gerät existiert bereits, nur die WLAN-Angaben unterscheiden sich zwischen den
   Projekten.

   .. code-block:: arduino

      #define BLYNK_TEMPLATE_ID   "TMPLxxxxxx"
      #define BLYNK_TEMPLATE_NAME "Ultimate Sensor Kit"
      #define BLYNK_AUTH_TOKEN    "YourAuthToken"

#. Tragen Sie den Namen und das Passwort Ihres eigenen WLAN-Netzes ein.

   .. code-block:: arduino

      char ssid[] = "your_ssid";
      char pass[] = "your_password";

#. Wählen Sie **Arduino UNO R4 Minima** und den richtigen Port und klicken Sie auf
   **Upload**.

#. Öffnen Sie den Seriellen Monitor mit **115200**. Sobald die Platine die Cloud erreicht,
   endet die Ausgabe mit ``Ready``. Jedes Umlegen des Schalters in der App erzeugt hier
   eine Zeile - daran erkennen Sie, dass beide miteinander sprechen.

   .. image:: ../img/blynk_flame_serial.png
      :width: 80%

#. Stellen Sie den Schalter jetzt auf **away home** und winken Sie vor dem PIR-Sensor. Das
   Label auf dem Dashboard wechselt auf ``Somebody in your house! Please check!`` und Ihr
   Handy zeigt eine Benachrichtigung.

   .. image:: ../img/blynk_intrusion_dashboard.png
      :width: 80%

#. Wenn Sie Blynk auf dem Handy nutzen möchten, sehen Sie in :ref:`blynk_mobile` nach.

4. Code-Erklärung
-----------------------------

#. **Blynk-Konto und Bibliotheken**

   Die ersten drei Zeilen sagen, zu welchem Blynk-Gerät diese Platine gehört. Sie stammen
   von der Geräteseite und sind in jedem Projekt des Kits gleich.

   .. code-block:: arduino

      #define BLYNK_TEMPLATE_ID   "TMPL2Ms3WVki8"
      #define BLYNK_TEMPLATE_NAME "Ultimate Sensor Kit"
      #define BLYNK_AUTH_TOKEN    "lHSd4Q5pXP7YKUovVfPZYZqC0UHVORY6"

      #define BLYNK_PRINT Serial   // Blynk-Protokoll im Seriellen Monitor

      #include <ESP8266_Lib.h>               // sendet die AT-Befehle
      #include <BlynkSimpleShieldEsp8266.h>  // Blynk darauf

#. **Die serielle Schnittstelle zum Modul**

   Das ESPC2-01 führt Ihren Sketch nicht aus - es arbeitet als Modem, das AT-Befehle
   beantwortet. Auf dem R4 liegt es an D0/D1, also an ``Serial1``, einer Hardware-
   Schnittstelle; 115200 funktioniert dort ohne Bitfehler.

   .. code-block:: arduino

      #define EspSerial Serial1
      #define ESP8266_BAUD 115200
      ESP8266 wifi(&EspSerial);

#. **PIR-Pin und die beiden Zustandsvariablen**

   .. code-block:: arduino

      const int sensorPin = 8;   // PIR-Ausgang: HIGH = Bewegung, LOW = ruhig

      int state = 0;           // letzter gelesener Pegel
      int awayHomeMode = 0;    // 1 = Schalter in der App ist an, Anlage ist scharf

      BlynkTimer timer;

   ``state`` ermöglicht den nächsten Abschnitt: der Vergleich des neuen Wertes mit dem
   alten zeigt den Moment, in dem jemand vorbeigeht - statt hundertmal "da ist eine
   Person". ``awayHomeMode`` beantwortet die Frage "bin ich zu Hause oder nicht"; der Alarm
   reagiert nur bei ``1``.

#. **espModuleInit() - das Modul zuerst aufwecken**

   Das Modul braucht etwa eine Sekunde zum Starten und gibt sein Startprotokoll über
   genau die Leitung aus, die der Sketch gleich benutzt. Zu frühe Befehle vermischen sich
   mit diesem Protokoll. Die Funktion wartet auf das Wort ``ready`` und sendet dann
   ``ATE0``.

   .. code-block:: arduino

      void espModuleInit() {
        unsigned long t0 = millis();
        String buf;
        while (millis() - t0 < 5000) {
          while (EspSerial.available()) {
            buf += (char)EspSerial.read();
            if (buf.indexOf("ready") >= 0) t0 = millis() - 5000;   // Schleife verlassen
          }
        }
        while (EspSerial.available()) EspSerial.read();
        EspSerial.print("ATE0\r\n");   // Echo aus
        delay(300);
        while (EspSerial.available()) EspSerial.read();
      }

   ``ATE0`` schaltet das Echo ab. Mit Echo beginnt jede Antwort mit dem gerade gesendeten
   Befehl, und Blynk liest diese Zeile als Müll.

#. **setup()**

   .. code-block:: arduino

      void setup() {
        pinMode(sensorPin, INPUT);

        Serial.begin(115200);
        EspSerial.begin(ESP8266_BAUD);
        delay(10);

        espModuleInit();
        Blynk.config(wifi, BLYNK_AUTH_TOKEN);
        Blynk.connectWiFi(ssid, pass);

        timer.setInterval(1000L, myTimerEvent);
      }

   ``timer.setInterval(1000L, myTimerEvent)`` ruft die Funktion einmal pro Sekunde auf.
   Ändern Sie die Zahl, um den Sensor häufiger oder seltener zu prüfen.

#. **loop()**

   .. code-block:: arduino

      void loop() {
        Blynk.run();
        timer.run();
      }

   ``Blynk.run()`` hält die Verbindung am Leben, ``timer.run()`` löst die geplante
   Funktion aus. Nichts darf hier blockieren, sonst trennt die Cloud das Gerät.

#. **BLYNK_CONNECTED() und BLYNK_WRITE(V1)**

   .. code-block:: arduino

      BLYNK_CONNECTED() {
        Blynk.syncVirtual(V1);
      }

      BLYNK_WRITE(V1) {
        awayHomeMode = param.asInt();
        ...
      }

   ``BLYNK_CONNECTED()`` läuft bei jeder Verbindung zum Server - auch nach einem
   Stromausfall. ``Blynk.syncVirtual(V1)`` fragt die aktuelle Schalterstellung ab, damit
   eine um Mitternacht neu gestartete Platine immer noch weiß, dass Sie das Haus verlassen
   haben.

   ``BLYNK_WRITE(V1)`` läuft, sobald der Schalter in der App bewegt wird.
   ``param.asInt()`` ist der neue Wert, ``1`` oder ``0``, und die Antwort geht direkt zurück
   an das Label auf Datastream **V2**.

#. **sendData() - auf die Flanke reagieren, nicht auf den Pegel**

   .. code-block:: arduino

      void sendData() {
        int now = digitalRead(sensorPin);
        bool rising = (now == HIGH && state == LOW);
        state = now;

        if (awayHomeMode == 1 && rising && millis() - lastAlert > 5000) {
          lastAlert = millis();
          Blynk.virtualWrite(V2, "Somebody in your house! Please check!");
          Blynk.logEvent("intrusion_detected");
        }
      }

   * ``rising`` ist nur beim Übergang von ``LOW`` auf ``HIGH`` wahr - also in dem Moment,
     in dem der Sensor anspricht. Ohne diese Prüfung würde der Sketch jede Sekunde eine
     Nachricht senden, solange jemand dort steht, und das Blynk-Kontingent in Minuten
     aufbrauchen.
   * ``millis() - lastAlert > 5000`` hält zwei Meldungen mindestens fünf Sekunden
     auseinander.
   * ``Blynk.virtualWrite(V2, ...)`` schreibt den Text, den das Label anzeigt.
   * ``Blynk.logEvent("intrusion_detected")`` sendet das Event, das die Benachrichtigung
     auslöst. Der Name muss Zeichen für Zeichen dem angelegten **EVENT CODE** entsprechen.
