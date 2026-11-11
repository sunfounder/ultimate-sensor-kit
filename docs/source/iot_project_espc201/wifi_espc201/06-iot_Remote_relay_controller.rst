.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

.. _c201_iot_Remote_relay_controller:

6. Funk-Relaissteuerung mit Blynk
===============================================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../../_static/video/iot/06-iot_Remote_relay_controller.mp4"  type="video/mp4">
      Ihr Browser unterstützt das Video-Tag nicht.
   </video>

Dieses Projekt baut eine Fernsteuerung für ein Relais, bedient über einen virtuellen
Schalter in der Blynk-App. Ist der Schalter an, setzt die Platine den Digitalpin des
Relais auf HIGH, ist er aus, auf LOW. So lässt sich das Relais aus der Ferne schalten -
im Grunde ein Schalter mit großer Reichweite.

1. Schaltung aufbauen
-----------------------------

.. warning ::

    Das folgende Beispiel schaltet mit dem Relais ein LED-Modul. **In echten Anwendungen
    können Sie damit auch andere Geräte schalten, aber der Umgang mit hoher
    Wechselspannung verlangt äußerste Vorsicht. Fehlerhafte Verwendung kann zu schweren
    Verletzungen bis zum Tod führen. Das Beispiel richtet sich deshalb an Personen, die
    mit hoher Wechselspannung vertraut sind. Sicherheit steht immer an erster Stelle.**

.. note::

    Das Modul zieht beim Start einen hohen Strom. Stecken Sie deshalb die 9-V-Batterie
    bzw. das externe Netzteil in die Hohlbuchse des R4 Minima.


.. image:: ../img/06-Wiring_Remote_relay_controller_c201.png
   :width: 80%


* :ref:`cpn_uno`
* :ref:`cpn_espc201`
* :ref:`cpn_relay`
* :ref:`cpn_traffic`


2. Blynk einrichten
-----------------------------

.. note::

    Template und Gerät wurden einmalig in :ref:`c201_iot_blynk_start` angelegt. Jedes
    Projekt fügt seine Datastreams dem **selben** Template hinzu, deshalb belegt jedes
    Projekt einen eigenen Bereich der virtuellen Pins. Dieses Projekt nutzt **V7**.

**Was dieses Projekt in die Cloud sendet**

Eine Ganzzahl, ``relay_status``. Sie ist kein Messwert: Sie spiegelt den Zustand des
Relais, damit App und Platine immer dieselbe Meinung haben, ob es an ist.

**Datastream anlegen**

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

#. Füllen Sie das Formular aus:

   * **DATASTREAM NAME**: ``relay_status``
   * **DISPLAY NAME**: ``Relay Status``
   * **VIRTUAL PIN**: ``V7``
   * **DATA TYPE**: **Integer**
   * **MIN** ``0``, **MAX** ``1``

   .. image:: ../img/blynk_relay_data.png
      :width: 80%

**Web-Dashboard anlegen**

#. Klicken Sie auf **Dashboard** und dann auf **Add Widget**.

   .. image:: ../img/blynk_dashboard.png
      :width: 80%

#. Ziehen Sie ein **Switch**-Widget auf das Dashboard.

   .. image:: ../img/blynk_dashboard_switch.png
      :width: 80%

#. Klicken Sie auf die drei Punkte in der Ecke des **Switch** und wählen Sie **Settings**.

   * Stellen Sie **Datastream** auf ``Relay Status (V7)``.

   .. note::

      Ein **Switch** zeigt und setzt den Wert zugleich. Ein Tippen sendet ``1`` oder ``0``
      an die Platine; die Platine schaltet das Relais und schreibt denselben Wert zurück,
      der Schalter gerät also nie aus dem Tritt - auch wenn Sie zweimal schnell tippen.

   .. image:: ../img/blynk_relay_widget.png
      :width: 80%

#. Klicken Sie auf **Save**.

   .. image:: ../img/blynk_save.png
      :width: 40%


3. Code ausführen
-----------------------------

#. Öffnen Sie die Datei ``06-Remote_relay_controller.ino`` unter dem Pfad ``ultimate-sensor-kit\code\iot_project_espc201\wifi\06-Remote_relay_controller`` oder kopieren Sie den Code in die **Arduino IDE**.

#. Die drei Blynk-Zeilen wurden im Einsteigerkapitel kopiert. Jedes Projekt dieses Kits
   nutzt dasselbe Gerät, sie müssen also nie geändert werden - projektspezifisch sind nur
   die WLAN-Angaben unten.

   .. code-block:: arduino

      #define BLYNK_TEMPLATE_ID   "TMPLxxxxxx"
      #define BLYNK_TEMPLATE_NAME "Ultimate Sensor Kit"
      #define BLYNK_AUTH_TOKEN    "YourAuthToken"

#. Tragen Sie Namen und Passwort Ihres eigenen WLAN-Netzes ein.

   .. code-block:: arduino

      char ssid[] = "your_ssid";
      char pass[] = "your_password";

#. Wählen Sie **Arduino UNO R4 Minima** und den richtigen Port und klicken Sie auf
   **Upload**.

#. Öffnen Sie den Seriellen Monitor mit **115200**. Sobald die Platine die Cloud erreicht,
   endet die Ausgabe mit ``Ready``, und jedes Umlegen des Schalters erzeugt hier eine
   Zeile:

   .. code-block:: text

      [28358] Ready (ping: 285ms).
      The switch on Blynk has been turned on.
      The switch on Blynk has been turned off.

   Dieses Echo ist der schnellste Beweis, dass App und Platine wirklich miteinander
   sprechen.

   .. image:: ../img/blynk_relay_serial.png
      :width: 80%

#. Tippen Sie auf den Schalter: Das Relais klickt. Noch einmal: Es klickt zurück.

   .. note::

      Das Relais behält seine Stellung nach einem Stromausfall. Beim Verbinden fragt die
      Platine den Server nach dem letzten Wert (``Blynk.syncVirtual(V7)``), das Relais
      kehrt also in den Zustand zurück, in dem Sie es verlassen haben, statt immer
      ausgeschaltet zu starten.

   .. image:: ../img/blynk_relay_dashbaord.png
      :width: 80%


4. Code-Erklärung
-----------------------------

#. **Blynk-Konto und Bibliotheken**

   Die ersten drei Zeilen sagen, zu welchem Blynk-Gerät diese Platine gehört. Sie stammen
   von der Geräteseite und sind in jedem Projekt dieses Kits gleich.

   .. code-block:: arduino

      #define BLYNK_TEMPLATE_ID   "TMPL2Ms3WVki8"
      #define BLYNK_TEMPLATE_NAME "Ultimate Sensor Kit"
      #define BLYNK_AUTH_TOKEN    "lHSd4Q5pXP7YKUovVfPZYZqC0UHVORY6"

      #define BLYNK_PRINT Serial   // Blynk-Protokoll im Seriellen Monitor

      #include <ESP8266_Lib.h>               // sendet die AT-Befehle
      #include <BlynkSimpleShieldEsp8266.h>  // Blynk darauf

#. **Die serielle Schnittstelle zum Modul**

   Das ESPC2-01 arbeitet als Modem: Der Sketch sendet ihm AT-Befehle. Auf dem R4 hängt es
   an D0/D1, also an ``Serial1``, einer Hardware-Schnittstelle; 115200 funktioniert ohne
   Bitfehler.

   .. code-block:: arduino

      #define EspSerial Serial1
      #define ESP8266_BAUD 115200
      ESP8266 wifi(&EspSerial);

   Die Funktion ``espModuleInit()`` wartet, bis das Modul fertig gestartet ist, und
   schaltet dann mit ``ATE0`` das Echo ab. Ohne sie mischen sich Startprotokoll und
   zurückgespiegelte Befehle in die Antworten, und Blynk kann sie nicht lesen.

#. **Der Relais-Pin**

   .. code-block:: arduino

      const int RelayPin = 6;
      int switchStatus = 0;

   ``RelayPin`` ist der Pin, der das Relaismodul treibt - hier D6. ``switchStatus``
   speichert einfach den letzten Wert, den die App gesendet hat, damit der Code an einer
   Stelle "an" von "aus" unterscheiden kann.

   .. note::

      Manche Relaismodule schalten umgekehrt und ziehen an, wenn der Pin **LOW** ist.
      Klickt Ihr Relais entgegengesetzt zum Schalter in der App, tauschen Sie in der
      Funktion unten ``HIGH`` und ``LOW`` - sonst ändert sich nichts.

#. **setup()**

   .. code-block:: arduino

      void setup() {
        pinMode(RelayPin, OUTPUT);
        digitalWrite(RelayPin, LOW);

        Serial.begin(115200);
        EspSerial.begin(ESP8266_BAUD);
        delay(10);

        espModuleInit();
        Blynk.config(wifi, BLYNK_AUTH_TOKEN);
        Blynk.connectWiFi(ssid, pass);
      }

   ``digitalWrite(RelayPin, LOW)`` direkt nach ``pinMode`` ist wichtig: Ein Pin, der
   gerade Ausgang geworden ist, könnte kurz HIGH sein und das Relais bei jedem Einschalten
   klicken lassen.

#. **loop()**

   .. code-block:: arduino

      void loop() {
        Blynk.run();
        timer.run();
      }

   ``Blynk.run()`` hält die Verbindung am Leben. Dieses Projekt hat nichts zu messen, die
   Schleife tut also nichts weiter - sie muss trotzdem so schnell wie möglich laufen.

#. **BLYNK_CONNECTED() - den letzten Zustand wiederherstellen**

   .. code-block:: arduino

      BLYNK_CONNECTED() {
        Blynk.syncVirtual(V7);
      }

   Das läuft bei jeder Verbindung zum Server, auch nach einem Stromausfall.
   ``Blynk.syncVirtual(V7)`` fragt den gespeicherten Wert des Schalters ab, und der Server
   antwortet mit einem Aufruf von ``BLYNK_WRITE(V7)`` - das Relais landet also in dem
   Zustand, in dem Sie es verlassen haben.

#. **BLYNK_WRITE(V7) - der Schalter erledigt die Arbeit**

   .. code-block:: arduino

      BLYNK_WRITE(V7) {
        switchStatus = param.asInt();

        if (switchStatus == 1) {
          Serial.println("The switch on Blynk has been turned on.");
          digitalWrite(RelayPin, HIGH);
        } else {
          Serial.println("The switch on Blynk has been turned off.");
          digitalWrite(RelayPin, LOW);
        }
      }

   * ``BLYNK_WRITE(V7)`` läuft von selbst, sobald sich Datastream **V7** ändert - Sie
     rufen die Funktion nie aus ``loop()`` auf.
   * ``param.asInt()`` ist der neue Wert: ``1`` bei Schalter an, ``0`` bei aus.
   * Die ``Serial.println``-Zeilen sind nur für Sie; damit können Sie den Schalter im
     Seriellen Monitor mitverfolgen.
