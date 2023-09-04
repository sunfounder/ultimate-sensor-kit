.. _iot_Bluetooth_piano:

Bluetooth-Klavier
=============================

.. raw:: html

   <video controls style = "max-width:100%">
      <source src="../_static/video/iot/11-iot_Bluetooth_piano.mp4"  type="video/mp4">
      Ihr Browser unterstützt das Video-Tag nicht.
   </video>
   <br/><br/>

Dieses Projekt nutzt eine mit dem MIT App Inventor erstellte Android-App, um eine einfache "Klavier"-Funktion mittels eines JDY-31 Bluetooth-Moduls und eines passiven Summer-Moduls zu ermöglichen. Das Bluetooth-Klavier-Projekt erlaubt den Nutzern, verschiedene Musiknoten auf einem passiven Summer-Modul mithilfe eines JDY-31 Bluetooth-Moduls zu spielen. Durch das Senden spezifischer Notenanweisungen via Bluetooth an den Arduino können Nutzer die entsprechenden Töne auf dem Summer erzeugen.

Die Android-Anwendung wird mithilfe einer kostenlosen, webbasierten Plattform namens |link_appinventor| erstellt. Das Projekt bietet eine hervorragende Möglichkeit, Erfahrung im Umgang mit der Schnittstelle zwischen einem Arduino und einem Smartphone zu sammeln.


1. Schaltung aufbauen
-----------------------------

.. image:: img/11-Wiring_Bluetooth_piano.png
    :width: 75%

* :ref:`cpn_uno`
* :ref:`cpn_jdy31`
* :ref:`cpn_buzzer`


2. Android-App erstellen
-----------------------------

Die Android-Anwendung wird mit einer kostenlosen Webanwendung namens |link_appinventor| entwickelt. 
Der MIT App Inventor dient als ausgezeichneter Einstieg in die Android-Entwicklung, dank seiner intuitiven Drag-and-Drop-Funktionen zur Erstellung einfacher Anwendungen.

Jetzt geht's los.

#. Rufen Sie |link_appinventor_login| auf und klicken Sie auf "Online-Tool", um sich anzumelden. Sie benötigen ein Google-Konto, um sich beim MIT App Inventor zu registrieren.

   .. image:: img/new/09-ai_signup_shadow.png
       :width: 90%
       :align: center

#. Nach dem Login navigieren Sie zu **Projects** -> **Import project (.aia) from my computer**. Laden Sie anschließend die Datei ``piano.aia`` hoch, die sich im Pfad ``ultimate-sensor-kit\iot_project\bluetooth\06-Bluetooth_piano`` befindet.

   Direkter Download hier möglich: :download:`piano.aia</_static/other/piano.aia>`

   .. image:: img/new/09-ai_import_shadow.png
        :align: center

#. Nach dem Hochladen der ``.aia``-Datei erscheint die Anwendung in der Software des MIT App Inventors. Dies ist eine vorkonfigurierte Vorlage, die Sie nach dem Kennenlernen des MIT App Inventors modifizieren können.

#. Im MIT App Inventor gibt es zwei Hauptbereiche: den **Designer** und die **Blocks**. Sie können in der oberen rechten Ecke der Seite zwischen diesen beiden Bereichen wechseln.

   .. image:: img/new/09-ai_intro_1_shadow.png

#. Der **Designer** ermöglicht das Hinzufügen von Buttons, Texten, Bildschirmen und die Anpassung des Gesamtdesigns Ihrer Anwendung.

   .. image:: img/new/11-ai_intro_2_shadow.png
   
#. Als Nächstes gibt es den Bereich **Blocks**. In diesem Abschnitt können Sie individuelle Funktionen für Ihre App programmieren und so jedes Element in der GUI der App nach Ihren Wünschen gestalten.

   .. image:: img/new/11-ai_intro_3_shadow.png

#. Um die Anwendung auf einem Smartphone zu installieren, navigieren Sie zum **Build**-Tab.

   .. image:: img/new/08-ai_intro_4_shadow.png

   * Sie können eine ``.apk``-Datei generieren. Nach der Auswahl dieser Option erscheint eine Seite, auf der Sie wählen können, ob Sie eine ``.apk``-Datei herunterladen oder einen QR-Code zum Installieren scannen möchten. Folgen Sie dem Installationsleitfaden, um die Installation der Anwendung abzuschließen. 

     Unsere vorab kompilierte APK können Sie auch hier herunterladen: :download:`piano.apk</_static/other/piano.apk>`

   * Falls Sie diese App im Google Play Store oder einem anderen App-Marktplatz veröffentlichen möchten, können Sie eine ``.aab``-Datei generieren.



3. Den Code hochladen
-----------------------------

#. Öffnen Sie die Datei ``06-Bluetooth_piano.ino`` unter dem Pfad ``ultimate-sensor-kit\iot_project\bluetooth\06-Bluetooth_piano`` oder kopieren Sie diesen Code in die **Arduino IDE**.

   .. raw:: html
       
       <iframe src=https://create.arduino.cc/editor/sunfounder01/a9d0b7bf-0927-4a10-88b9-bbc4a9abc5c8/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

#. Nach der Auswahl des richtigen Boards und Ports, klicken Sie auf die **Hochladen**-Schaltfläche.

#. Öffnen Sie den seriellen Monitor (Baudrate auf **9600** einstellen), um Debug-Nachrichten anzuzeigen.


4. App und Bluetooth-Modul verbinden
-----------------------------------------------

Stellen Sie sicher, dass die zuvor erstellte Anwendung auf Ihrem Smartphone installiert ist.

#. Aktivieren Sie zunächst **Bluetooth** auf Ihrem Smartphone.

   .. image:: img/new/09-app_1_shadow.png
      :width: 60%
      :align: center

#. Navigieren Sie zu den **Bluetooth-Einstellungen** auf Ihrem Smartphone und suchen Sie nach Namen wie **JDY-31-SPP**.

   .. image:: img/new/09-app_2_shadow.png
      :width: 60%
      :align: center

#. Klicken Sie darauf und bestätigen Sie die **Kopplungsanfrage** im aufpoppenden Fenster. Falls ein Kopplungscode erforderlich ist, geben Sie "1234" ein.

   .. image:: img/new/09-app_3_shadow.png
      :width: 60%
      :align: center

#. Öffnen Sie nun die neu installierte **Piano**-App.

   .. image:: img/new/11-app_4_shadow.png
      :width: 25%
      :align: center

#. In der App klicken Sie auf die **Verbinden**-Schaltfläche, um eine Verbindung zwischen der App und dem Bluetooth-Modul herzustellen.

   .. image:: img/new/11-app_5_shadow.png
      :width: 85%
      :align: center

#. Diese Seite zeigt eine Liste aller gekoppelten Bluetooth-Geräte an. Wählen Sie die Option ``xx.xx.xx.xx.xx.xx JDY-31-SPP`` aus der Liste aus. Der Name jedes Geräts ist neben seiner MAC-Adresse aufgeführt.

   .. image:: img/new/11-app_6_shadow.png
      :width: 60%
      :align: center

#. Falls Sie auf der oben gezeigten Seite keine Geräte sehen, könnte dies daran liegen, dass der App die Berechtigung zur Suche nach nahegelegenen Geräten fehlt. In diesem Fall müssen Sie die Einstellungen manuell anpassen.

   * Um zur **App-Info**-Seite zu gelangen, halten Sie das App-Symbol gedrückt und wählen Sie es aus. Alternativ können Sie auch eine andere Methode verwenden, um diese Seite zu erreichen.

   .. image:: img/new/11-app_8_shadow.png
         :width: 60%
         :align: center

   * Navigieren Sie zur **Berechtigungen**-Seite.

   .. image:: img/new/08-app_9_shadow.png
         :width: 60%
         :align: center

   * Um der App das Scannen nach nahegelegenen Geräten zu ermöglichen, gehen Sie zu **Nahegelegene Geräte** und wählen **Immer** aus.

   .. image:: img/new/08-app_10_shadow.png
         :width: 60%
         :align: center

   * Starten Sie nun die App neu und wiederholen Sie die Schritte 5 und 6, um erfolgreich eine Bluetooth-Verbindung herzustellen.

#. Nach einer erfolgreichen Verbindung können Sie in der App auf die Tasten klicken, um verschiedene Noten zu spielen, und sogar einige einfache Lieder ausführen.

   .. image:: img/new/11-app_7_shadow.png
      :width: 85%
      :align: center

5. Code-Erklärung
-----------------------------------------------

1. **Bibliotheken und Pins einrichten**

   .. code-block:: arduino
   
      #include "pitches.h"
      #include <SoftwareSerial.h>
      const int bluetoothTx = 3;
      const int bluetoothRx = 4;
      SoftwareSerial bleSerial(bluetoothTx, bluetoothRx);
      const int buzzerPin = 2;

   - ``pitches.h``: Diese Datei enthält die Frequenzwerte für musikalische Noten.

   .. raw:: html

      <br/>

2. **Variablendeklaration zur Speicherung von Bluetooth-Daten**

   .. code-block:: arduino
   
      char character;
      String noteType;

   - ``character``: Speichert einzelne Zeichen, die über Bluetooth empfangen werden.
   - ``noteType``: Fasst die Zeichen zusammen, um die vollständige Notenanweisung zu bilden.

   .. raw:: html

      <br/>

3. **Setup-Funktion - Initialisierung der seriellen Kommunikation**

   .. code-block:: arduino
   
      void setup() {
        Serial.begin(9600);
        bleSerial.begin(9600);
      }

   - Initialisiert die serielle Kommunikation mit einer Baudrate von 9600.
   - Die Standard-``Serial`` dient zur Fehlersuche, während ``bleSerial`` speziell für die Bluetooth-Kommunikation vorgesehen ist.

4. **Hauptschleife - Lesen von Bluetooth-Daten und Abspielen entsprechender Noten**

   .. code-block:: arduino
   
      void loop() {
        while (bleSerial.available() > 0) {
          character = bleSerial.read();
          noteType = noteType + character;
          if (character == '*') {
            noteType = noteType.substring(0, noteType.length() - 1);
            Serial.println(noteType);
            if (noteType == "NOTE_C4") {
              tone(buzzerPin, NOTE_C4);
            } // ... weitere Noten werden ähnlich überprüft ...
            noteType = "";
            delay(200);
            noTone(buzzerPin);
          }
        }
      }

   - Liest Zeichen von Bluetooth und bildet den ``noteType``.
   - Wenn ein Sternchen ('*') erkannt wird, signalisiert dies das Ende der Notenanweisung. Die Note wird dann abgespielt, kurz verzögert und dann gestoppt.

