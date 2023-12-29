.. _cpn_dht11:

Temperatur- und Feuchtigkeitssensor-Modul (DHT11)
==================================================

.. image:: img/12_dht11_module.png
    :width: 400
    :align: center

Einführung
---------------------------
Der digitale Temperatur- und Feuchtigkeitssensor DHT11 ist ein kombinierter Sensor, der kalibrierte digitale Signalausgaben für Temperatur und Feuchtigkeit liefert. Die Verbindung aus spezieller digitaler Modultechnologie und Temperatur- sowie Feuchtigkeitssensorik sorgt für hohe Zuverlässigkeit und langfristige Stabilität des Produkts. 

Der Sensor setzt sich aus einer resistiven Feuchtigkeitsmesskomponente und einer NTC-Temperaturmesseinheit zusammen, die mit einem leistungsfähigen 8-Bit-Mikrocontroller verbunden sind.

Funktionsprinzip
---------------------------
Der Sensor hat lediglich drei benutzbare Anschlüsse: VCC, GND und DATA. Der Kommunikationsprozess beginnt mit Startsignalen, die die DATA-Leitung an den DHT11 sendet. Nach dem Empfang der Signale sendet der DHT11 ein Antwortsignal zurück. Anschließend empfängt der Host das Antwortsignal und beginnt mit dem Empfang der 40-Bit-Temperatur- und Feuchtigkeitsdaten (8-Bit Feuchtigkeit Ganzzahl + 8-Bit Feuchtigkeit Dezimal + 8-Bit Temperatur Ganzzahl + 8-Bit Temperatur Dezimal + 8-Bit Prüfsumme).

.. image:: img/12_dht11_module_2.png
    :width: 300
    :align: center

.. raw:: html
    
    <br/><br/>   

Anwendungsbeispiele
---------------------------

**Benötigte Hardware-Komponenten**

- Arduino Uno R4 oder R3 Platine * 1
- Temperatur- und Feuchtigkeitssensor-Modul (DHT11) * 1
- Jumperkabel


**Schaltungsaufbau**

.. image:: img/12_dht11_module_circuit.png
    :width: 400
    :align: center

.. raw:: html
    
    <br/><br/>   

Code
^^^^^^^^^^^^^^^^^^^^

.. note:: 
   Zur Installation der Bibliothek nutzen Sie den Arduino Library Manager und suchen Sie nach **"DHT sensor library"** und installieren Sie diese. 

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/34796700-4b94-4796-815a-314a25f60638/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/12-component_dht11.mp4"  type="video/mp4">
      Ihr Browser unterstützt das Video-Tag nicht.
   </video>
   <br/><br/>  

Code-Erklärung
^^^^^^^^^^^^^^^^^^^^

1. Einbindung der erforderlichen Bibliotheken und Definition der Konstanten.
   Dieser Codeabschnitt enthält die DHT-Sensorbibliothek und definiert die verwendete Pinnummer und den Sensortyp für dieses Projekt.

   .. note:: 
      Zur Installation der Bibliothek nutzen Sie den Arduino Library Manager und suchen Sie nach **"DHT sensor library"** und installieren Sie diese. 

   .. code-block:: arduino
    
      #include <DHT.h>
      #define DHTPIN 2       // Define the pin used to connect the sensor
      #define DHTTYPE DHT11  // Define the sensor type

2. Erstellung eines DHT-Objekts.
   Hier erstellen wir ein DHT-Objekt mit der definierten Pinnummer und dem definierten Sensortyp.

   .. code-block:: arduino

      DHT dht(DHTPIN, DHTTYPE);  // Create a DHT object

3. Initialisierungsfunktion.
   Diese Funktion wird einmalig beim Start des Arduino ausgeführt. Hier initialisieren wir die serielle Kommunikation und den DHT-Sensor.

   .. code-block:: arduino

      void setup() {
        Serial.begin(9600);
        Serial.println(F("DHT11 test!"));
        dht.begin();  // Initialize the DHT sensor
      }

4. Hauptloop.
   Die ``loop()``-Funktion läuft kontinuierlich nach der Setup-Funktion. Hier lesen wir die Feuchtigkeits- und Temperaturwerte aus, berechnen den Hitzeindex und geben diese Werte an den seriellen Monitor weiter. Sollte der Sensorauslesevorgang fehlschlagen (NaN zurückgeben), wird eine Fehlermeldung ausgegeben.

   .. note::
    
      Der |link_heat_index| ist ein Maß für das gefühlte Außentemperatur, das durch Kombination von Lufttemperatur und Luftfeuchtigkeit ermittelt wird. 

   .. code-block:: arduino

      void loop() {
        delay(2000);
        float h = dht.readHumidity();
        float t = dht.readTemperature();
        float f = dht.readTemperature(true);
        if (isnan(h) || isnan(t) || isnan(f)) {
          Serial.println(F("Failed to read from DHT sensor!"));
          return;
        }
        float hif = dht.computeHeatIndex(f, h);
        float hic = dht.computeHeatIndex(t, h, false);
        Serial.print(F("Humidity: "));
        Serial.print(h);
        Serial.print(F("%  Temperature: "));
        Serial.print(t);
        Serial.print(F("°C "));
        Serial.print(f);
        Serial.print(F("°F  Heat index: "));
        Serial.print(hic);
        Serial.print(F("°C "));
        Serial.print(hif);
        Serial.println(F("°F"));
      }

Weitere Ideen
^^^^^^^^^^^^^^^^^^^^

- Anzeige der Messwerte auf einem LCD- oder OLED-Display

Weitere Projekte
---------------------------
* :ref:`iot_Plant_monitor`
* :ref:`iot_Bluetooth_environmental_monitor`

