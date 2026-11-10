.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

.. _iot_Bluetooth_environmental_monitor:

Bluetooth-Umweltmonitor
=================================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/iot/10-iot_Bluetooth_environmental_monitor.mp4"  type="video/mp4">
      Ihr Browser unterstützt das Video-Tag nicht.
   </video>

Dieses Projekt nutzt eine Android-App, die mit dem MIT App Inventor erstellt wurde, um Umweltdaten von einem Arduino-Board zu empfangen und anzuzeigen. Das Arduino-Board sammelt Daten von einem DHT11-Sensor, um Temperatur und Luftfeuchtigkeit zu messen. Diese Daten werden dann über das JDY-31-Modul via Bluetooth übertragen. Die App zeigt die Daten auf dem Bildschirm an, sobald sie empfangen werden.

Die Android-Anwendung wird mit einer kostenlosen Webplattform namens |link_appinventor| erstellt. Das Projekt bietet eine hervorragende Gelegenheit, Erfahrungen in der Schnittstellenanbindung eines Arduino-Boards an ein Smartphone zu sammeln.

1. Den Schaltkreis aufbauen
-----------------------------

.. note:: 
   Das Kit kann verschiedene Versionen des DHT11-Moduls enthalten. Bitte bestätigen Sie die Verkabelungsmethode entsprechend dem Modul, das Sie haben.

.. csv-table:: 
   :header: "Modul", "Diagramm"
   :widths: 100, 250
   
   |dht11_module|, |dht11_module_circuit|
   |dht11_module_withLED|, |dht11_module_withLED_circuit|

.. |dht11_module| image:: img/10_dht11_module.png 
   :width: 100px

.. |dht11_module_circuit| image:: img/10-Wiring_Bluetooth_environmental_monitor.png
   :width: 360px

.. |dht11_module_withLED| image:: img/10_dht11_module_withLED.png
   :width: 150px

.. |dht11_module_withLED_circuit| image:: img/10-Wiring_Bluetooth_environmental_monitor_new.png
   :width: 360px

* :ref:`cpn_uno`
* :ref:`cpn_jdy31`
* :ref:`cpn_dht11`

2. Die Android-App erstellen
-----------------------------

Die Android-Anwendung wird mit einer kostenlosen Webanwendung namens |link_appinventor| entwickelt. 
Der MIT App Inventor ist ein ausgezeichneter Einstiegspunkt für die Android-Entwicklung, da er intuitive Drag-and-Drop-Funktionen für die Erstellung einfacher Anwendungen bietet.

Jetzt geht's los.

#. Besuchen Sie |link_appinventor_login| und klicken Sie auf "Online-Tool", um sich anzumelden. Sie benötigen ein Google-Konto, um sich beim MIT App Inventor zu registrieren.

   .. image:: img/new/09-ai_signup_shadow.png
       :width: 90%
       :align: center

#. Nach der Anmeldung navigieren Sie zu **Projects** -> **Import project (.aia) from my computer**. Laden Sie anschließend die Datei ``Bluetooth_controlled_lock.aia`` hoch, die im Verzeichnis ``ultimate-sensor-kit\iot_project\bluetooth\05-Bluetooth_environmental_monitor`` zu finden ist.

   Sie können die Datei auch direkt hier herunterladen: :download:`Bluetooth_Environmental_Monitor.aia</_static/other/Bluetooth_Environmental_Monitor.aia>`

   .. image:: img/new/09-ai_import_shadow.png
        :align: center

#. Nach dem Hochladen der ``.aia``-Datei wird die Anwendung im MIT App Inventor angezeigt. Es handelt sich hierbei um eine vorkonfigurierte Vorlage, die Sie nach einer Einarbeitungsphase im MIT App Inventor anpassen können.

#. Im MIT App Inventor gibt es zwei Hauptbereiche: den **Designer** und die **Blocks**. Sie können zwischen diesen beiden Bereichen in der oberen rechten Ecke der Seite wechseln.

   .. image:: img/new/09-ai_intro_1_shadow.png

#. Der **Designer** ermöglicht das Hinzufügen von Buttons, Texten, Bildschirmen und das Anpassen des Gesamtdesigns Ihrer Anwendung.

   .. image:: img/new/10-ai_intro_2_shadow.png
   
#. Als Nächstes gibt es den Bereich **Blocks**. Hier können Sie benutzerdefinierte Funktionen für Ihre App erstellen und so jedes Element der Benutzeroberfläche der App programmieren, um gewünschte Funktionen zu erreichen.

   .. image:: img/new/10-ai_intro_3_shadow.png

#. Um die Anwendung auf einem Smartphone zu installieren, navigieren Sie zum **Build**-Tab.

   .. image:: img/new/08-ai_intro_4_shadow.png

   * Sie können eine ``.apk``-Datei generieren. Wählen Sie diese Option, erscheint eine Seite, die Ihnen die Wahl lässt, entweder eine ``.apk``-Datei herunterzuladen oder einen QR-Code für die Installation zu scannen. Folgen Sie der Installationsanleitung, um die Installation der Anwendung abzuschließen.

     Sie können auch unsere bereits kompilierte APK hier herunterladen: :download:`Bluetooth_Environmental_Monitor.apk</_static/other/Bluetooth_Environmental_Monitor.apk>`

   * Wenn Sie die App im Google Play Store oder einem anderen App-Marktplatz veröffentlichen möchten, können Sie eine ``.aab``-Datei generieren.



3. Hochladen des Codes
-----------------------------

#. Öffnen Sie die Datei ``05-Bluetooth_environmental_monitor.ino`` im Pfad ``ultimate-sensor-kit\iot_project\bluetooth\05-Bluetooth_environmental_monitor`` oder kopieren Sie den Code in die **Arduino IDE**.

   .. note:: 
      Um die Bibliothek zu installieren, verwenden Sie den Arduino-Bibliotheksmanager und suchen Sie nach **"DHT sensor library"** und installieren Sie diese.

   .. raw:: html
       
       <iframe src=https://create.arduino.cc/editor/sunfounder01/97605897-2fae-4e4e-97f3-d254796636a1/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

#. Wählen Sie das korrekte Board und den Port aus und klicken Sie auf die Schaltfläche **Hochladen**.

#. Öffnen Sie den seriellen Monitor (Baudrate auf **9600** einstellen), um Debug-Nachrichten zu sehen.

4. Verbindung der App und des Bluetooth-Moduls
------------------------------------------------

Vergewissern Sie sich, dass die zuvor erstellte Anwendung auf Ihrem Smartphone installiert ist.

#. Aktivieren Sie zunächst **Bluetooth** auf Ihrem Smartphone.

   .. image:: img/new/09-app_1_shadow.png
      :width: 60%
      :align: center

#. Navigieren Sie zu den **Bluetooth-Einstellungen** auf Ihrem Smartphone und suchen Sie nach Namen wie **JDY-31-SPP**.

   .. image:: img/new/09-app_2_shadow.png
      :width: 60%
      :align: center

#. Nach dem Anklicken stimmen Sie der **Kopplungsanfrage** im aufspringenden Fenster zu. Falls ein Kopplungscode erforderlich ist, geben Sie "1234" ein.

   .. image:: img/new/09-app_3_shadow.png
      :width: 60%
      :align: center

#. Öffnen Sie nun die neu installierte App **Environmental Monitor**.

   .. image:: img/new/10-app_4_shadow.png
      :width: 25%
      :align: center

#. In der App klicken Sie auf die Schaltfläche **Connect**, um eine Verbindung zwischen der App und dem Bluetooth-Modul herzustellen.

   .. image:: img/new/10-app_5_shadow.png
      :width: 60%
      :align: center

#. Diese Seite zeigt eine Liste aller gekoppelten Bluetooth-Geräte an. Wählen Sie die Option ``xx.xx.xx.xx.xx.xx JDY-31-SPP`` aus der Liste. Der Name jedes Geräts steht neben seiner MAC-Adresse.

   .. image:: img/new/10-app_6_shadow.png
      :width: 60%
      :align: center

#. Wenn Sie auf der oben gezeigten Seite keine Geräte sehen, könnte das daran liegen, dass der App nicht erlaubt ist, nach nahegelegenen Geräten zu suchen. In diesem Fall müssen Sie die Einstellungen manuell anpassen.

   * Um zur **App-Info-Seite** zu gelangen, halten Sie das App-Symbol gedrückt und wählen Sie es aus. Alternativ können Sie auch eine andere Methode verwenden, um auf diese Seite zu gelangen.

   .. image:: img/new/10-app_8_shadow.png
         :width: 60%
         :align: center

   * Navigieren Sie zur Seite **Berechtigungen**.

   .. image:: img/new/08-app_9_shadow.png
         :width: 60%
         :align: center

   * Um der App die Suche nach nahegelegenen Geräten zu ermöglichen, gehen Sie zu **Nahegelegene Geräte** und wählen Sie **Immer**.

   .. image:: img/new/08-app_10_shadow.png
         :width: 60%
         :align: center

   * Starten Sie nun die App neu und wiederholen Sie die Schritte 5 und 6, um erfolgreich eine Bluetooth-Verbindung herzustellen.

#. Nach einer erfolgreichen Verbindung werden Sie zur Hauptseite weitergeleitet, auf der Temperatur und Luftfeuchtigkeit angezeigt werden.

   .. image:: img/new/10-app_7_shadow.png
      :width: 60%
      :align: center

5. Code-Erläuterung
-----------------------------------------------

1. Einrichtung der Bluetooth-Kommunikation und des DHT11-Sensors.

   .. code-block:: arduino

      #include <SoftwareSerial.h>
      const int bluetoothTx = 3;
      const int bluetoothRx = 4;
      SoftwareSerial bleSerial(bluetoothTx, bluetoothRx);

      #include <DHT.h>
      #define DHTPIN 2
      #define DHTTYPE DHT11
      DHT dht(DHTPIN, DHTTYPE);

   Der Code bindet die erforderlichen Bibliotheken ein und definiert die Pins für das Bluetooth-Modul sowie den DHT11-Sensor. Zudem werden Objekte für die Bluetooth-Kommunikation und den DHT11 deklariert.

2. Initialisierung in der Setup-Funktion.

   .. code-block:: arduino

      void setup() {
        Serial.begin(9600);
        bleSerial.begin(9600);
        dht.begin();
      }

   Dieser Abschnitt initialisiert die serielle Kommunikation für Debugging-Zwecke sowie das Bluetooth-Modul und den DHT-Sensor.

3. Datenerfassung und Übermittlung via Bluetooth.

   .. code-block:: arduino

      void loop() {

        delay(2000);
        float humidity = dht.readHumidity();
        float temperature = dht.readTemperature();

        // Check if any reads failed and exit early (to try again).
        if (isnan(humidity) || isnan(temperature)) {
          Serial.println(F("Failed to read from DHT sensor!"));
          return;
        }

        // For debug
        // Print the humidity and temperature to the serial monitor
        Serial.print(F("Humidity: "));
        Serial.print(humidity);
        Serial.print(F("%  Temperature: "));
        Serial.print(temperature);
        Serial.println(F("°C "));

        sensorData = String(temperature) + "," + String(humidity);  // Concatenate temperature and humidity values
        Serial.print("Data to send: ");
        Serial.println(sensorData);

        bleSerial.println(sensorData);  // Send temperature and humidity values to the Bluetooth module
      }

   Dieser Abschnitt liest alle 2 Sekunden Temperatur und Luftfeuchtigkeit vom DHT11-Sensor. Bei fehlerhaften Messungen wird eine Fehlermeldung ausgegeben. Ansonsten werden die Messdaten im seriellen Monitor angezeigt und in einem kommagetrennten Format via Bluetooth-Modul gesendet. Die App wertet die im Format "Temperatur,Luftfeuchtigkeit" empfangenen Daten aus und stellt sie in der Benutzeroberfläche dar.
