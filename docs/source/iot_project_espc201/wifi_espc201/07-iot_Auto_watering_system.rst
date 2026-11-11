.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

.. _c201_iot_Auto_watering_system:

7. Automatische Bewässerung mit Blynk
===================================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../../_static/video/iot/07-iot_Auto_watering_system.mp4"  type="video/mp4">
      Ihr Browser unterstützt das Video-Tag nicht.
   </video>

Eine Bodenfeuchtesonde steckt im Topf, eine kleine Pumpe steht in einem Glas Wasser. Die
Platine meldet, wie feucht die Erde ist, und - sobald Sie es erlauben - schaltet sie die
Pumpe selbst ein, bevor die Pflanze Durst bekommt.

Über das Handy beobachten Sie die Feuchte, ziehen einen Schieberegler, um zu bestimmen,
wie trocken die Erde werden darf, und entscheiden, ob das Kit selbst gießen darf.

1. Schaltung aufbauen
-----------------------------

.. note::

    Das Modul zieht beim Start einen hohen Strom. Stecken Sie deshalb die 9-V-Batterie
    bzw. das externe Netzteil in die Hohlbuchse des R4 Minima.


.. image:: ../img/07-Wiring_Auto_watering_c201.png
   :width: 80%


* :ref:`cpn_uno`
* :ref:`cpn_espc201`
* :ref:`cpn_soil`
* :ref:`cpn_pump`


2. Blynk einrichten
-----------------------------

.. note::

    Template und Gerät wurden einmalig in :ref:`c201_iot_blynk_start` angelegt. Jedes
    Projekt fügt seine Datastreams dem **selben** Template hinzu, deshalb belegt jedes
    Projekt einen eigenen Bereich der virtuellen Pins. Dieses Projekt nutzt **V8** bis
    **V10**.

**Was dieses Projekt in die Cloud sendet**

Drei Werte mit unterschiedlichen Aufgaben:

* ``moisture_percentage`` - schreibt die Platine, damit Sie die Bodenfeuchte sehen.
* ``water_threshold`` - schreiben Sie über den Schieberegler: die Schwelle, unterhalb
  derer die Pumpe läuft.
* ``auto_mode`` - ein Schalter, der entscheidet, ob die Platine die Pumpe selbst starten
  darf.

**Datastreams anlegen**

#. Öffnen Sie **Developer Zone** -> **My Templates** und klicken Sie auf **Ultimate
   Sensor Kit**.

   .. image:: ../img/blynk_template.png
      :width: 80%

#. Klicken Sie auf **Edit**, um das Template zu öffnen.

   .. image:: ../img/blynk_edit.png
      :width: 80%

#. Klicken Sie auf **Datastreams** und dann auf **Create New**.

#. Legen Sie den ersten Datastream an - einen **Virtual Pin**-Datastream. An ``V8`` ist
   nichts angeschlossen: Ein virtueller Pin existiert nur in der Cloud, er ist ein
   Briefkasten, den Platine und App gemeinsam nutzen.

   * **DATASTREAM NAME**: ``moisture_percentage``
   * **DISPLAY NAME**: ``Moisture Percentage``
   * **VIRTUAL PIN**: ``V8``
   * **DATA TYPE**: **Double**
   * **MIN** ``0``, **MAX** ``100``

   .. image:: ../img/blynk_water_data_mois.png
      :width: 80%

#. Setzen Sie das Feld **UNITS** auf ``Percentage``.

   .. image:: ../img/blynk_water_data_unit.png
      :width: 80%

#. Legen Sie die anderen **zwei** Virtual-Pin-Datastreams genauso an - klicken Sie
   zweimal weitere Male auf **Create New**:

   .. list-table::
      :header-rows: 1
      :widths: 10 26 24 14 16 10

      * - Pin
        - Datastream-Name
        - Anzeigename
        - Typ
        - Min / Max
        - Einheit
      * - V9
        - ``water_threshold``
        - ``Water Threshold``
        - **Double**
        - 0 / 100
        - Percent
      * - V10
        - ``auto_mode``
        - ``Auto Mode``
        - **Integer**
        - 0 / 1
        - None

   .. image:: ../img/blynk_water_datastreams.png
      :width: 80%

**Web-Dashboard anlegen**

#. Klicken Sie auf **Dashboard** und dann auf **Add Widget**.

   .. image:: ../img/blynk_dashboard.png
      :width: 80%

#. Ziehen Sie ein **Gauge**-Widget auf das Dashboard.

   .. image:: ../img/blynk_dashboard_gauge.png
      :width: 80%

#. Klicken Sie auf die drei Punkte in der Ecke des **Gauge** und wählen Sie **Settings**.

   * Stellen Sie **Datastream** auf ``Moisture Percentage (V8)``.

   .. image:: ../img/blynk_water_gauge_set.png
      :width: 80%

#. Ziehen Sie genauso einen **Slider** und einen **Switch** auf das Dashboard und
   verbinden Sie sie:

   .. list-table::
      :header-rows: 1
      :widths: 26 40 34

      * - Widget
        - Datastream
        - Wofür
      * - Slider
        - ``Water Threshold (V9)``
        - die Schwelle einstellen, ab der gegossen wird
      * - Switch
        - ``Auto Mode (V10)``
        - der Platine erlauben, die Pumpe selbst zu steuern

   .. image:: ../img/blynk_water_widgets.png
      :width: 80%

   .. note::

      Ist **auto_mode** aus, läuft die Pumpe nie, egal was der Slider sagt. Das ist die
      sichere Voreinstellung: Sie können die Werte eine Weile beobachten, bevor das Kit
      die Pflanze selbst gießt.

#. Klicken Sie auf **Save**.

   .. image:: ../img/blynk_save.png
      :width: 40%


3. Code ausführen
-----------------------------

#. Öffnen Sie die Datei ``07-Auto_watering_system.ino`` unter dem Pfad ``ultimate-sensor-kit\code\iot_project_espc201\wifi\07-Auto_watering_system`` oder kopieren Sie den Code in die **Arduino IDE**.

#. Die drei Blynk-Zeilen wurden im Einsteigerkapitel kopiert - lassen Sie sie unverändert.

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

#. Öffnen Sie den Seriellen Monitor mit **115200**. Alle 10 Sekunden meldet die Platine
   die Bodenfeuchte:

   .. code-block:: text

      -----------------------------
      Update soil moisture data ...
      sensorValue:453  moisturePercentage:32.16

   Die Zahl nach ``sensorValue`` ist der **Rohwert** der Sonde. Ignorieren Sie den
   Prozentwert vorerst - er ist noch nicht kalibriert.

#. Kalibrieren Sie die Sonde, denn jede Sonde und jede Erde ist anders:

   #. Halten Sie die Sonde **in die Luft** (trocken) und notieren Sie den
      ``sensorValue``, zum Beispiel ``535``.
   #. Stecken Sie die Sonde **in ein Glas Wasser** und notieren Sie den zweiten
      ``sensorValue``, zum Beispiel ``280``.
   #. Tragen Sie beide Zahlen im Sketch ein:

      .. code-block:: arduino

         const float moistureInAir = 535;     // Wert in trockener Luft
         const float moistureInWater = 280;   // Wert in Wasser

   #. Laden Sie erneut hoch. Jetzt bedeutet der Prozentwert wirklich etwas: 0 % ist so
      trocken wie die Luft, 100 % so nass wie das Wasser.

   .. note::

      Die Sonde liest **trocken höher und nass niedriger** - deshalb stehen die beiden
      Zahlen in dieser Reihenfolge in der Formel. Überspringen Sie die Kalibrierung, wird
      der Prozentwert trotzdem angezeigt, das Gauge kann aber bei feuchter Erde auf 0 %
      stehen oder bei trockener auf 100 %.

   .. image:: ../img/blynk_water_serial.png
      :width: 80%

#. Ziehen Sie im Dashboard den **Slider** über die aktuelle Feuchte (zum Beispiel 40)
   und schalten Sie **Auto Mode** ein. Innerhalb von 35 Sekunden startet die Pumpe, und
   das Gauge beginnt zu steigen.

   .. note::

      Die Pumpe läuft nur, wenn **Auto Mode** an ist. Mit ausgeschaltetem Schalter können
      Sie die Werte beliebig lange beobachten, die Pumpe bleibt still.

   .. image:: ../img/blynk_water_dashboard.png
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

#. **Die serielle Schnittstelle zum Modul**

   Das ESPC2-01 arbeitet als Modem: Der Sketch sendet ihm AT-Befehle auf D0/D1, also über
   ``Serial1``, eine Hardware-Schnittstelle. ``espModuleInit()`` wartet, bis das Modul
   gestartet ist, und sendet dann ``ATE0``, damit die Antworten nicht mehr den Befehl
   mitschleppen.

   .. code-block:: arduino

      #define EspSerial Serial1
      #define ESP8266_BAUD 115200
      ESP8266 wifi(&EspSerial);

#. **Die Pumpe**

   .. code-block:: arduino

      const int pump1A = 9;
      const int pump1B = 10;
      bool pumpStatus = 0;

   Die Pumpe läuft über einen **L9110**-Treiber. Gib ``1A`` HIGH, und die Pumpe dreht;
   ``1B`` bleibt LOW, es wird nur zum Umkehren eines Motors gebraucht. Ein Relais oder ein
   einfacher Transistor würden genauso funktionieren - ein Pin, an oder aus.

#. **Die Sonde und ihre zwei Kalibrierpunkte**

   .. code-block:: arduino

      const float moistureInAir = 535;
      const float moistureInWater = 280;
      const int sensorPin = A0;

   Die Sonde liefert eine Rohzahl, und - das ist der überraschende Teil - **je feuchter
   die Erde, desto kleiner die Zahl**. Der Sketch rechnet das in Prozent um:

   .. code-block:: arduino

      moisturePercentage = 1 - (sensorValue - moistureInWater) / (moistureInAir - moistureInWater);

   Mit den beiden Kalibrierwerten wird "in Wasser" zu ``1.0`` und "in Luft" zu ``0.0``,
   alles dazwischen proportional.

#. **Zwei Timer, zwei Aufgaben**

   .. code-block:: arduino

      timer.setInterval(10000L, updateDataTimer);   // alle 10 s melden
      timer.setInterval(35000L, autoWaterTimer);    // alle 35 s die Pumpe prüfen

   Messen ist billig, es passiert also oft. Eine Pumpe zu starten ist es nicht, deshalb
   wird langsamer geprüft - und ``delay()`` kommt nie zum Einsatz, die Blynk-Verbindung
   läuft also weiter.

#. **BLYNK_CONNECTED() und die beiden Writes**

   .. code-block:: arduino

      BLYNK_CONNECTED() {
        Blynk.syncVirtual(V9);
        Blynk.syncVirtual(V10);
      }

      BLYNK_WRITE(V9)  { waterThreshold = param.asInt(); }
      BLYNK_WRITE(V10) { autoMode       = param.asInt(); }

   ``BLYNK_CONNECTED()`` läuft bei jeder Verbindung, auch nach einem Stromausfall, und
   fragt den Server nach Slider und Schalter. Ohne sie würde eine neu gestartete Platine
   mit einer Schwelle von ``0`` gießen - also nie.

#. **sendData() meldet, autoWater() handelt**

   .. code-block:: arduino

      void sendData() {
        sensorValue = analogRead(sensorPin);
        moisturePercentage = 1 - (sensorValue - moistureInWater) / (moistureInAir - moistureInWater);
        Blynk.virtualWrite(V8, moisturePercentage * 100);
      }

      void autoWater() {
        if (autoMode == 1 && moisturePercentage * 100 < waterThreshold) {
          // Pumpe eine Weile laufen lassen
        }
      }

   ``sendData()`` liest nur und meldet - die Pumpe berührt sie nie. ``autoWater()`` ist die
   einzige Stelle, die sie startet, und dafür braucht sie **beide** Bedingungen:
   Automatikmodus an und die Erde trockener als Ihr Slider.
