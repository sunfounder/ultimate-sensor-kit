.. _iot_Bluetooth_traffic_light:

Bluetooth-Ampel
=============================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/iot/16-iot_Bluetooth_traffic_light.mp4"  type="video/mp4">
      Ihr Browser unterstützt das Video-Tag nicht.
   </video>

Dieses Projekt dient der Steuerung einer Verkehrsampel (rote, gelbe, grüne LEDs) über Bluetooth-Kommunikation. Der Nutzer kann einen Buchstaben ('R', 'Y' oder 'G') von einem Bluetooth-Gerät senden. Bei Empfang eines dieser Zeichen leuchtet die entsprechende LED auf, während die beiden anderen LEDs ausgeschaltet bleiben.

1. Schaltung aufbauen
-----------------------------

.. image:: img/16-Wiring_Bluetooth_traffic_light.png
    :width: 80%

* :ref:`cpn_uno`
* :ref:`cpn_jdy31`
* :ref:`cpn_traffic`

2. Code hochladen
-----------------------------

#. Öffnen Sie die Datei ``02-Bluetooth_traffic_light.ino`` im Pfad ``ultimate-sensor-kit\iot_project\bluetooth\02-Bluetooth_traffic_light`` oder kopieren Sie diesen Code in die **Arduino IDE**.

   .. raw:: html
       
       <iframe src=https://create.arduino.cc/editor/sunfounder01/e004fd36-1294-453e-b6fd-2bc7fc9410e8/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

#. Wählen Sie das korrekte Board und den entsprechenden Port aus, und klicken Sie auf den **Hochladen**-Button.

#. Öffnen Sie den Seriellen Monitor (Baudrate auf **9600** einstellen), um Debug-Meldungen anzuzeigen.

3. App und Bluetooth-Modul verbinden
-----------------------------------------------

Zur Kommunikation können wir die App "Serial Bluetooth Terminal" verwenden, um Nachrichten vom Bluetooth-Modul an den Arduino zu senden.

a. **Serial Bluetooth Terminal installieren**

   Laden und installieren Sie |link_serial_bluetooth_terminal| über den Google Play Store.

b. **Bluetooth verbinden**

   Aktivieren Sie zuerst **Bluetooth** auf Ihrem Smartphone.

      .. image:: img/new/09-app_1_shadow.png
         :width: 60%
         :align: center
   
   Navigieren Sie zu den **Bluetooth-Einstellungen** auf Ihrem Smartphone und suchen Sie nach Namen wie **JDY-31-SPP**.
   
      .. image:: img/new/09-app_2_shadow.png
         :width: 60%
         :align: center
   
   Nach dem Anklicken stimmen Sie der **Kopplungsanfrage** im Pop-up-Fenster zu. Falls nach einem Kopplungscode gefragt wird, geben Sie "1234" ein.

      .. image:: img/new/09-app_3_shadow.png
         :width: 60%
         :align: center

c. **Mit dem Bluetooth-Modul kommunizieren**

   Öffnen Sie das Serial Bluetooth Terminal und verbinden Sie sich mit "JDY-31-SPP".

   .. image:: img/new/00-bluetooth_serial_4_shadow.png 

d. **Befehle senden**

   Verwenden Sie die Serial Bluetooth Terminal App, um Befehle über Bluetooth an den Arduino zu senden. Senden Sie R, um das rote Licht einzuschalten, Y für gelb und G für grün.

   .. image:: img/new/16-R_shadow.png 
      :width: 85%
      :align: center

   .. image:: img/new/16-Y_shadow.png 
      :width: 85%
      :align: center

   .. image:: img/new/16-G_shadow.png 
      :width: 85%
      :align: center

4. Code-Erklärung
-----------------------------------------------

#. Initialisierung und Bluetooth-Konfiguration

   .. code-block:: arduino

      // Set up Bluetooth module communication
      #include <SoftwareSerial.h>
      const int bluetoothTx = 3;
      const int bluetoothRx = 4;
      SoftwareSerial bleSerial(bluetoothTx, bluetoothRx);

   Zunächst binden wir die SoftwareSerial-Bibliothek ein, um die Bluetooth-Kommunikation zu erleichtern. Danach definieren wir die TX- und RX-Pins des Bluetooth-Moduls und ordnen sie den Pins 3 und 4 am Arduino zu. Abschließend initialisieren wir das ``bleSerial``-Objekt für die Bluetooth-Kommunikation.

#. Definition der LED-Pins

   .. code-block:: arduino

      // Pin numbers for each LED
      const int rledPin = 10;  //red
      const int yledPin = 11;  //yellow
      const int gledPin = 12;  //green

   Hier legen wir fest, an welchen Arduino-Pins unsere LEDs angeschlossen sind. Die rote LED ist am Pin 10, die gelbe am 11 und die grüne am 12 angeschlossen.

#. Funktion setup()

   .. code-block:: arduino

      void setup() {
         pinMode(rledPin, OUTPUT);
         pinMode(yledPin, OUTPUT);
         pinMode(gledPin, OUTPUT);

         Serial.begin(9600);
         bleSerial.begin(9600);
      }

   In der Funktion ``setup()`` setzen wir die LED-Pins als ``OUTPUT``. Des Weiteren starten wir die serielle Kommunikation sowohl für das Bluetooth-Modul als auch für die Standard-Serielle-Schnittstelle (verbunden mit dem Computer) mit einer Baudrate von 9600.

#. Hauptloop() für die Bluetooth-Kommunikation

   .. code-block:: arduino

      void loop() {
         while (bleSerial.available() > 0) {
            character = bleSerial.read();
            Serial.println(character);

            if (character == 'R') {
               toggleLights(rledPin);
            } else if (character == 'Y') {
               toggleLights(yledPin);
            } else if (character == 'G') {
               toggleLights(gledPin);
            }
         }
      }

   In unserer Haupt-Schleife ``loop()`` prüfen wir fortlaufend, ob Daten vom Bluetooth-Modul verfügbar sind. Falls Daten empfangen werden, lesen wir das Zeichen aus und zeigen es im seriellen Monitor an. Je nach empfangenem Zeichen (R, Y oder G) schalten wir die jeweilige LED mit der Funktion ``toggleLights()`` um.

#. Funktion zum Umschalten der Lichter

   .. code-block:: arduino

      void toggleLights(int targetLight) {
         digitalWrite(rledPin, LOW);
         digitalWrite(yledPin, LOW);
         digitalWrite(gledPin, LOW);

         digitalWrite(targetLight, HIGH);
      }

   Diese Funktion, ``toggleLights()``, schaltet zuerst alle LEDs aus. Nachdem sichergestellt ist, dass alle LEDs ausgeschaltet sind, wird die spezifizierte Ziel-LED eingeschaltet. Dadurch wird gewährleistet, dass jeweils nur eine LED aktiv ist.
