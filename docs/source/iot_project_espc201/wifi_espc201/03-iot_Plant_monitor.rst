.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

.. _c201_iot_Plant_monitor:

3. Pflanzenüberwachung mit Blynk
========================================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../../_static/video/iot/03-iot_Plant_monitor.mp4"  type="video/mp4">
      Ihr Browser unterstützt das Video-Tag nicht.
   </video>

Dieses Projekt überwacht eine Pflanze: aktuelle Temperatur, Luftfeuchtigkeit,
Lichtintensität und Bodenfeuchte. Die Werte erscheinen in Blynk, zusammen mit einem
Hinweis zur Bodenfeuchte.

1. Schaltung aufbauen
-----------------------------

.. note::

   Das Modul zieht beim Start einen hohen Strom. Stecken Sie deshalb die 9-V-Batterie
   bzw. das externe Netzteil in die Hohlbuchse des R4 Minima.

   **Das Kit kann verschiedene Versionen des DHT11-Moduls enthalten. Prüfen Sie die
   Verdrahtung anhand Ihres Moduls.**


.. image:: ../img/03-Wiring_Plant_monitor_c201.png
   :width: 80%

.. image:: ../img/03-Wiring_Plant_monitor_new_c201.png
   :width: 80%


* :ref:`cpn_uno`
* :ref:`cpn_espc201`
* :ref:`cpn_dht11`
* :ref:`cpn_soil`


2. Blynk einrichten
-----------------------------

.. note::

    Template und Gerät wurden einmalig in :ref:`c201_iot_blynk_start` angelegt. Jedes
    Projekt fügt seine Datastreams dem **selben** Template hinzu, deshalb belegt jedes
    Projekt einen eigenen Bereich der virtuellen Pins. Dieses Projekt nutzt **V3** bis
    **V6**.

**Was dieses Projekt in die Cloud sendet**

Vier Werte, und der Typ ist jeweils wichtig - er bestimmt, wie Blynk den Wert anzeigen
kann:

* ``temperature`` - eine Dezimalzahl, also **Double**.
* ``humidity`` - eine Dezimalzahl, also **Double**.
* ``soil_moisture`` - ein Wort wie ``dry`` / ``wet``, also **String**.
* ``led_status`` - Helligkeit 0..255 für die Lampe im Dashboard, also **Integer**. Der
  Sketch sendet immer 255, nur die Farbe ändert sich.

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

   * **DATASTREAM NAME**: ``temperature``
   * **DISPLAY NAME**: ``Temperature``
   * **VIRTUAL PIN**: ``V3``
   * **DATA TYPE**: **Integer**
   * **MIN** ``-100``, **MAX** ``100``

   .. image:: ../img/blynk_plant_data_tem.png
      :width: 80%

#. Setzen Sie das Feld **UNITS** auf ``Celsius``.

   .. image:: ../img/blynk_plant_data_unit.png
      :width: 80%

#. Legen Sie die anderen drei Datastreams genauso an, mit diesen Werten:

   .. list-table::
      :header-rows: 1
      :widths: 12 26 14 20 28

      * - Pin
        - Name
        - Typ
        - Min / Max
        - Einheit
      * - V4
        - ``humidity``
        - Double
        - 0 / 100
        - Percent
      * - V5
        - ``soil_moisture``
        - String
        - -
        - -
      * - V6
        - ``led_status``
        - Integer
        - 0 / 255
        - -

   .. image:: ../img/blynk_plant_datastreams.png
      :width: 80%

**Web-Dashboard anlegen**

#. Klicken Sie auf **Dashboard** und dann auf **Add Widget**.

   .. image:: ../img/blynk_dashboard.png
      :width: 80%

#. Ziehen Sie ein **Gauge**-Widget auf das Dashboard.

   .. image:: ../img/blynk_dashboard_gauge.png
      :width: 80%

#. Klicken Sie auf die drei Punkte in der Ecke des **Gauge** und wählen Sie **Settings**.

   * Stellen Sie **Datastream** auf ``Temperature (V3)``.

   .. image:: ../img/blynk_plant_gauge_set.png
      :width: 80%

#. Ziehen Sie die übrigen Widgets genauso auf das Dashboard - ein weiteres **Gauge**, ein
   **Label** und eine **LED** - und verbinden Sie sie:

   .. list-table::
      :header-rows: 1
      :widths: 26 40 34

      * - Widget
        - Datastream
        - Was es zeigt
      * - Gauge
        - ``Humidity (V4)``
        - wie feucht die Luft ist
      * - Label
        - ``Soil Moisture (V5)``
        - ``dry`` oder ``wet``
      * - LED
        - ``Led Status (V6)``
        - eine Statuslampe im Dashboard: grün, wenn die Bodenfeuchte passt, rot, wenn
          nicht

   .. image:: ../img/blynk_plant_widgets.png
      :width: 80%

   .. note::

      Das **LED**-Widget ist eine **Lampe im Dashboard**. Der Sketch schreibt immer ``255``
      für volle Helligkeit und ändert nur die Farbe: grün, wenn die Bodenfeuchte im
      richtigen Bereich liegt, rot bei zu nass oder zu trocken. So erkennen Sie den
      Zustand der Pflanze aus der Entfernung.

#. Klicken Sie auf **Save**.

   .. image:: ../img/blynk_save.png
      :width: 40%


3. Code ausführen
-----------------------------

#. Öffnen Sie die Datei ``03-Plant_monitor.ino`` unter dem Pfad ``ultimate-sensor-kit\code\iot_project_espc201\wifi\03-Plant_monitor`` oder kopieren Sie den Code in die **Arduino IDE**.

#. Die drei Blynk-Zeilen wurden in :ref:`c201_iot_blynk_start` kopiert. Jedes Projekt
   dieses Kits nutzt dasselbe Gerät, sie müssen also nie geändert werden -
   projektspezifisch sind nur die WLAN-Angaben unten.

   .. code-block:: arduino

      #define BLYNK_TEMPLATE_ID   "TMPLxxxxxx"
      #define BLYNK_TEMPLATE_NAME "Ultimate Sensor Kit"
      #define BLYNK_AUTH_TOKEN    "YourAuthToken"

#. Tragen Sie außerdem ``ssid`` und ``password`` Ihres WLAN-Netzes ein.

   .. code-block:: arduino

    char ssid[] = "your_ssid";
    char pass[] = "your_password";

#. Wählen Sie die richtige Platine und den richtigen Port und klicken Sie auf **Upload**.

#. Öffnen Sie den Seriellen Monitor mit **115200** und warten Sie, bis eine Meldung wie
   eine erfolgreiche Verbindung erscheint.

   .. image:: ../img/blynk_plant_serial.png
      :width: 80%

#. Dieselben Werte sehen Sie auch im Blynk-Dashboard.

   .. image:: ../img/blynk_plant_dashboard.png
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
   an D0/D1, also an ``Serial1``, einer Hardware-Schnittstelle; 115200 funktioniert dort
   ohne Bitfehler.

   .. code-block:: arduino

      #define EspSerial Serial1
      #define ESP8266_BAUD 115200
      ESP8266 wifi(&EspSerial);

   Die Funktion ``espModuleInit()`` wartet, bis das Modul fertig gestartet ist, und
   schaltet dann mit ``ATE0`` das Echo ab. Ohne sie mischen sich Startprotokoll und
   zurückgespiegelte Befehle in die Antworten, und Blynk kann sie nicht lesen.

#. **Der DHT11-Sensor**

   .. code-block:: arduino

      #include <DHT.h>
      #define DHTPIN 8
      #define DHTTYPE DHT11
      DHT dht(DHTPIN, DHTTYPE);

      float temperature;
      float humidity;

   Ein DHT11 liefert ganze Grad und ganze Prozent, ein ``float`` ist also mehr
   Genauigkeit, als der Sensor wirklich hat - dafür bleibt der Code einfach und passt
   später auch für einen DHT22.

#. **Der Bodenfeuchtesensor und die zwei Schwellen**

   .. code-block:: arduino

      #define wetSoil 320
      #define drySoil 400

      const int moistureSensorPin = A0;
      int moisture;
      String soilStatus;

   Die Sonde liefert einen Analogwert zwischen 0 und 1023, und **je feuchter der Boden,
   desto kleiner die Zahl**. Deshalb bedeutet "unter ``wetSoil``" hier "zu nass".

   .. note::

      Messen Sie die beiden Zahlen selbst. Stecken Sie die Sonde in ein Glas Wasser und
      lesen Sie den Wert ab: das ist ungefähr Ihr ``wetSoil``. Dann messen Sie in trockener
      Erde: das ist ``drySoil``. Die Vorgaben 320 / 400 passen nur zur Erde des
      Entwicklers.

#. **setup()**

   .. code-block:: arduino

      void setup() {
        Serial.begin(115200);
        EspSerial.begin(ESP8266_BAUD);
        delay(10);

        espModuleInit();
        Blynk.config(wifi, BLYNK_AUTH_TOKEN);
        Blynk.connectWiFi(ssid, pass);

        timer.setInterval(5000L, myTimerEvent);

        dht.begin();
      }

   ``timer.setInterval(5000L, myTimerEvent)`` misst alle fünf Sekunden. Ein DHT11 kann
   ohnehin nicht schneller als einmal pro Sekunde messen, und Pflanzen ändern sich nicht
   schneller.

#. **loop()**

   .. code-block:: arduino

      void loop() {
        Blynk.run();
        timer.run();
      }

   ``Blynk.run()`` hält die Verbindung am Leben, ``timer.run()`` löst die Messung aus.
   Nichts darf hier blockieren, sonst trennt die Cloud das Gerät.

#. **sendData() - messen, bewerten, melden**

   .. code-block:: arduino

      void sendData() {
        humidity = dht.readHumidity();
        temperature = dht.readTemperature();

        if (isnan(humidity) || isnan(temperature)) {
          Serial.println(F("Failed to read from DHT sensor!"));
          return;                                  // diesen Durchlauf überspringen
        }

        moisture = analogRead(moistureSensorPin);

        String color;
        if (moisture < wetSoil) {
          soilStatus = "Soil is too wet";
          color = "#D3435C";
        } else if (moisture >= wetSoil && moisture < drySoil) {
          soilStatus = "Soil moisture is perfect";
          color = "#00FF00";
        } else {
          soilStatus = "Soil is too dry - time to water!";
          color = "#D3435C";
        }

        Blynk.virtualWrite(V3, temperature);
        Blynk.virtualWrite(V4, humidity);
        Blynk.virtualWrite(V5, soilStatus);
        Blynk.virtualWrite(V6, 255);
        Blynk.setProperty(V6, "color", color);
      }

   * Das ``return`` bei einer fehlgeschlagenen DHT-Messung lässt im Dashboard den letzten
     guten Wert stehen, statt ihn mit ``nan`` zu überschreiben.
   * ``Blynk.virtualWrite(V3, ...)`` und die anderen schieben die vier Werte in die
     Datastreams.
   * ``Blynk.virtualWrite(V6, 255)`` schaltet die **LED im Dashboard** voll ein;
     ``Blynk.setProperty(V6, "color", color)`` färbt sie dann grün oder rot. Die echte LED
     mit der Bezeichnung **L** auf der Platine wird von diesem Projekt nicht genutzt.

#. **printData()**

   .. code-block:: arduino

      void printData() {
        Serial.print(F("Humidity: "));
        Serial.print(humidity);
        Serial.print(F("%  Temperature: "));
        Serial.print(temperature);
        Serial.println(F("°C "));
        Serial.print("(");
        Serial.print(moisture);
        Serial.print(") ");
        Serial.println(soilStatus);
      }

   Dieselben Zahlen, aber im Seriellen Monitor. Wenn am Handy etwas falsch aussieht,
   prüfen Sie hier, ob der Sensor oder die Cloud die Ursache ist.
