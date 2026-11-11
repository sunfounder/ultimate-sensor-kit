.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

.. _c201_iot_Flame:

1. Flammenwarnsystem mit Blynk
====================================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../../_static/video/iot/01-iot_Flame_alert_system.mp4"  type="video/mp4">
      Ihr Browser unterstützt das Video-Tag nicht.
   </video>

In diesem Kapitel bauen wir ein Flammenwarnsystem für zu Hause. Ein Flammensensor
erkennt ein mögliches Feuer, die Werte gehen an Blynk und Sie können Ihr Zuhause über das
Internet beobachten. Schlägt der Sensor an, schickt Blynk sofort eine E-Mail.


1. Schaltung aufbauen
-----------------------------

.. note::

    Das Modul zieht beim Start einen hohen Strom. Stecken Sie deshalb die 9-V-Batterie
    bzw. das externe Netzteil in die Hohlbuchse des R4 Minima.


.. image:: ../img/01-Wiring_flame_alert_system_c201.png
   :width: 80%

* :ref:`cpn_uno`
* :ref:`cpn_flame`
* :ref:`cpn_espc201`


2. Blynk einrichten
-----------------------------

.. note::

    Das **Template** und das **Gerät** wurden in :ref:`c201_iot_blynk_start` angelegt.
    Daten im Template hinzuzufügen ändert den Token des Geräts **nicht**, die drei Zeilen
    im Sketch bleiben also für jedes Projekt gleich.

**Datastream anlegen**

#. Öffnen Sie das Template **Ultimate Sensor Kit**, das Sie im Einsteigerkapitel
   erstellt haben.

   .. image:: ../img/blynk_template.png
      :width: 80%

#. Klicken Sie auf **Edit**, um das Template zu öffnen.

   .. image:: ../img/blynk_edit.png
      :width: 80%

#. Klicken Sie auf **Datastreams** und dann auf **Create New**.

   .. image:: ../img/blynk_new_data.png
      :width: 80%

#. Füllen Sie das Formular so aus:

   * **DATASTREAM NAME**: ``flame_sensor_value``
   * **DISPLAY NAME**: ``Flame Sensor Value``
   * **VIRTUAL PIN**: ``V0``
   * **DATA TYPE**: **Integer**
   * **MIN** ``0``, **MAX** ``1``

   .. image:: ../img/blynk_flame_datastream.png
      :width: 80%

**Event anlegen**

Das Event ist das, was später die Benachrichtigung auf dem Handy auslöst.

#. Wechseln Sie zu **Events & notifications** und klicken Sie auf **Create Event**.

   .. image:: ../img/blynk_new_event.png
      :width: 80%

#. Setzen Sie den **EVENT CODE** auf ``flame_detected``.

   .. note::

      Schreiben Sie ihn genau so. Der Sketch ruft ``Blynk.logEvent("flame_detected")``
      auf, und jede andere Schreibweise bedeutet, dass die Benachrichtigung nie ankommt.

   .. image:: ../img/blynk_flame_event.png
      :width: 80%

#. Schalten Sie die Benachrichtigung ein und wählen Sie, wohin sie gehen soll.

   .. image:: ../img/blynk_flame_event_notify.png
      :width: 80%

**Web-Dashboard anlegen**

#. Klicken Sie auf **Dashboard** und dann auf **Add Widget**.

   .. image:: ../img/blynk_dashboard.png
      :width: 80%

#. Ziehen Sie ein **Label**-Widget auf das Dashboard.

   .. image:: ../img/blynk_dashboard_label.png
      :width: 80%

#. Klicken Sie auf die drei Punkte in der Ecke des Widgets und wählen Sie **Settings**.

   .. image:: ../img/blynk_label_setting.png
      :width: 80%

#. Stellen Sie **Datastream** auf ``Flame Sensor Value (V0)``.

   .. image:: ../img/blynk_flame_label.png
      :width: 80%

#. Klicken Sie auf **Save**.

   .. image:: ../img/blynk_save.png
      :width: 40%


3. Code ausführen
-----------------------------

#. Öffnen Sie die Datei ``01-Flame_alert_system.ino`` unter dem Pfad ``ultimate-sensor-kit\code\iot_project_espc201\wifi\01-Flame_alert_system`` oder kopieren Sie den Code in die **Arduino IDE**.

#. Die drei Blynk-Zeilen wurden in :ref:`c201_iot_blynk_start` kopiert. Jedes Projekt
   dieses Kits nutzt dasselbe Gerät, sie müssen also nie geändert werden - projektspezifisch
   sind nur die WLAN-Angaben unten.

   .. code-block:: arduino

      #define BLYNK_TEMPLATE_ID   "TMPLxxxxxx"
      #define BLYNK_TEMPLATE_NAME "Ultimate Sensor Kit"
      #define BLYNK_AUTH_TOKEN    "YourAuthToken"

#. Tragen Sie außerdem ``ssid`` und ``password`` Ihres WLAN-Netzes ein.

   .. code-block:: arduino

    char ssid[] = "your_ssid";
    char pass[] = "your_password";

#. Wählen Sie die richtige Platine und den richtigen Port und klicken Sie auf **Upload**.
   Öffnen Sie den Seriellen Monitor mit **115200 Baud** und warten Sie, bis eine Meldung
   wie eine erfolgreiche Verbindung erscheint.

   .. image:: ../img/blynk_flame_serial.png
      :width: 80%

#. Nun zeigt Blynk den Wert des Flammensensors. Im Label-Widget sehen Sie den gelesenen
   Wert. Steht dort **1**, ist der Hintergrund des Labels grün. Steht dort **0**, wird der
   Hintergrund rot und Blynk schickt Ihnen eine Warnmail.

   .. image:: ../img/blynk_flame_dashboard.png
      :width: 70%

#. Wenn Sie Blynk auch auf dem Handy nutzen möchten, sehen Sie in :ref:`blynk_mobile` nach.


4. Code-Erklärung
-----------------------------

1. **Blynk-Konto und Bibliotheken**

   Die ersten drei Zeilen sagen der Platine, zu welchem Blynk-Gerät sie gehört. Sie
   wurden im Einsteigerkapitel kopiert und sind in jedem Projekt dieses Kits gleich.

   .. code-block:: arduino

      #define BLYNK_TEMPLATE_ID   "TMPL2Ms3WVki8"
      #define BLYNK_TEMPLATE_NAME "Ultimate Sensor Kit"
      #define BLYNK_AUTH_TOKEN    "lHSd4Q5pXP7YKUovVfPZYZqC0UHVORY6"

      #define BLYNK_PRINT Serial             // Debug-Ausgabe im Seriellen Monitor

      #include <ESP8266_Lib.h>               // AT-Befehlstreiber für das Modul
      #include <BlynkSimpleShieldEsp8266.h>  // Blynk auf diesem Treiber

2. **Die serielle Schnittstelle zum Modul**

   Das ESPC2-01 führt Ihren Sketch nicht aus - es arbeitet als Modem, das AT-Befehle
   empfängt. Auf dem R4 hängt es an D0/D1, also an ``Serial1``, einer Hardware-Schnittstelle;
   bei 115200 Baud gibt es daher keine Bitfehler.

   .. code-block:: arduino

      #define EspSerial Serial1
      #define ESP8266_BAUD 115200
      ESP8266 wifi(&EspSerial);

3. **WLAN-Zugang, Sensorpin und Timer**

   .. code-block:: arduino

      char ssid[] = "MakerStarsHall";
      char pass[] = "sunfounder";

      const int sensorPin = 8;
      BlynkTimer timer;

   Das Flammenmodul gibt einen einfachen digitalen Pegel aus, Pin 8 wird deshalb mit
   ``digitalRead()`` gelesen. ``BlynkTimer`` ist ein Software-Timer aus der Blynk-Bibliothek:
   er ruft eine Funktion nach Zeitplan auf, ohne ``delay()``, das die Verbindung einfrieren
   würde.

4. **espModuleInit() - das Modul zuerst aufwecken**

   Das Modul braucht etwa eine Sekunde zum Starten und gibt sein Startprotokoll über
   dieselbe Leitung aus. Schickt der Sketch zu früh AT-Befehle, mischen sich die Antworten
   mit diesem Protokoll und Blynk kann sie nicht lesen. Diese Funktion wartet auf das Wort
   ``ready`` und schaltet dann mit ``ATE0`` das Echo ab.

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

   ``ATE0`` ist nicht optional: Mit eingeschaltetem Echo beginnt jede Antwort mit dem
   gerade gesendeten Befehl, der Blynk-Parser sieht also eine Zeile Müll vor der
   eigentlichen Antwort.

5. **setup()**

   .. code-block:: arduino

      void setup() {
        pinMode(sensorPin, INPUT);

        Serial.begin(115200);           // Serieller Monitor
        EspSerial.begin(ESP8266_BAUD);  // Modul
        delay(1000);

        timer.setInterval(1000L, myTimerEvent);   // einmal pro Sekunde

        espModuleInit();
        Blynk.config(wifi, BLYNK_AUTH_TOKEN);
        Blynk.connectWiFi(ssid, pass);
      }

   * ``timer.setInterval(1000L, myTimerEvent)`` ruft die Funktion alle 1000 ms auf. Ändern
     Sie die Zahl, um schneller oder langsamer zu melden.
   * ``Blynk.config()`` merkt sich den Token, ``Blynk.connectWiFi()`` bringt das Modul
     anschließend online. Man könnte auch eine Zeile ``Blynk.begin(...)`` verwenden, mit
     zwei Schritten kann das Modul aber erst fertig starten.

6. **loop()**

   .. code-block:: arduino

      void loop() {
        Blynk.run();
        timer.run();
      }

   ``Blynk.run()`` hält die Verbindung am Leben, ``timer.run()`` löst die geplante
   Funktion aus. Nichts in der Schleife darf blockieren, sonst trennt die Plattform das
   Gerät.

7. **sendData() - Pin lesen und melden**

   .. code-block:: arduino

      void sendData() {
        int data = digitalRead(sensorPin);
        Blynk.virtualWrite(V0, data);
        Serial.print("flame:");
        Serial.println(data);
        if (data == 0) {
          Blynk.logEvent("flame_detected");
        }
      }

   * ``Blynk.virtualWrite(V0, data)`` schiebt den Wert in den Datastream **V0**, den das
     Label auf dem Dashboard anzeigt.
   * Das Flammenmodul ist **active low**: Es liefert ``0``, wenn eine Flamme nah ist, und
     ``1``, wenn die Luft klar ist. Deshalb prüft der Sketch ``data == 0``.
   * ``Blynk.logEvent("flame_detected")`` sendet das Event, das die Benachrichtigung
     auslöst. Die Zeichenkette muss Zeichen für Zeichen dem **EVENT CODE** entsprechen, den
     Sie vorher angelegt haben.
