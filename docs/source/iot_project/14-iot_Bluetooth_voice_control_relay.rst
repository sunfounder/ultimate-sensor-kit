.. _iot_Bluetooth_Sprachsteuerungsrelais:

Bluetooth Sprachgesteuertes Relais
=================================

.. raw:: html

   <video controls style="max-width:100%">
      <source src="../_static/video/iot/14-iot_Bluetooth_voice_control_relay.mp4" type="video/mp4">
      Ihr Browser unterstützt das Video-Tag nicht.
   </video>

Dieses Projekt kombiniert eine Android-App, die mit dem MIT App Inventor entwickelt wurde, mit einem Arduino Uno Board. Die App bietet eine Spracheingabefunktion. Wenn die Spracheingabe des Benutzers das Wort "an" enthält, sendet die App eine "1"-Nachricht über Bluetooth an den Arduino, um das Relais einzuschalten. Enthält die Spracheingabe hingegen das Wort "aus", wird eine "0"-Nachricht gesendet, die den Arduino anweist, das Relais auszuschalten. Nach Erhalt dieser Nachrichten verarbeitet der Arduino sie entsprechend und schaltet das Relais ein oder aus.

Die Android-Anwendung wird mithilfe einer kostenlosen webbasierten Plattform namens |link_appinventor| erstellt. Dieses Projekt bietet eine hervorragende Möglichkeit, sich mit der Schnittstelle zwischen einem Arduino und einem Smartphone vertraut zu machen.

1. Schaltung aufbauen
-----------------------------

.. warning ::
    Im folgenden Beispiel wird gezeigt, wie ein Relais zur Steuerung eines Verkehrslichtmoduls verwendet wird.
    **Sie können das Relais in realen Anwendungen auch mit anderen Geräten verbinden. Dabei ist jedoch äußerste Vorsicht im Umgang mit HOHER Wechselspannung geboten. Unsachgemäße oder fehlerhafte Verwendung kann zu schweren Verletzungen oder gar zum Tod führen. Das Projekt ist daher nur für Personen geeignet, die sich mit HOHER Wechselspannung auskennen. Sicherheit hat immer Vorrang.**

.. image:: img/14-Wiring_Bluetooth_voice_control_relay.png
    :width: 75%

* :ref:`cpn_uno`
* :ref:`cpn_jdy31`
* :ref:`cpn_relay`
* :ref:`cpn_traffic`

2. Android-App erstellen
-----------------------------

Die Android-Anwendung wird mit einer kostenlosen Webanwendung namens |link_appinventor| entwickelt. 
Der MIT App Inventor dient als hervorragender Einstieg in die Android-Entwicklung dank seiner intuitiven Drag-and-Drop-Funktionen, die die Erstellung einfacher Anwendungen ermöglichen.

Jetzt geht's los.

#. Öffnen Sie |link_appinventor_login| und klicken Sie auf "Online-Tool", um sich anzumelden. Für die Registrierung bei MIT App Inventor benötigen Sie ein Google-Konto.

   .. image:: img/new/09-ai_signup_shadow.png
       :width: 90%
       :align: center

#. Nach dem Login navigieren Sie zu **Projects** -> **Import project (.aia) from my computer**. Laden Sie dann die ``VoiceControl.aia``-Datei hoch, die im Pfad ``ultimate-sensor-kit\iot_project\bluetooth\09-Bluetooth_voice_control_relay`` zu finden ist.

   Hier können Sie auch direkt herunterladen: :download:`VoiceControl.aia</_static/other/VoiceControl.aia>`

   .. image:: img/new/09-ai_import_shadow.png
        :align: center

#. Nach dem Hochladen der ``.aia``-Datei erscheint die Anwendung in der MIT App Inventor-Software. Dies ist eine vorkonfigurierte Vorlage, die Sie nach dem Kennenlernen des MIT App Inventors nach Ihren Wünschen anpassen können.

#. Im MIT App Inventor gibt es zwei Hauptbereiche: den **Designer** und die **Blocks**. Sie können oben rechts auf der Seite zwischen diesen beiden Bereichen wechseln.

   .. image:: img/new/09-ai_intro_1_shadow.png

#. Der **Designer** ermöglicht Ihnen, Schaltflächen, Text, Bildschirme und das allgemeine Erscheinungsbild Ihrer Anwendung zu gestalten.

   .. image:: img/new/14-ai_intro_2_shadow.png

#. Als nächstes kommt der Bereich **Blocks**. Hier können Sie individuelle Funktionen für Ihre App erstellen und jedes Element auf der Benutzeroberfläche der App programmieren, um die gewünschten Funktionen zu erreichen.

   .. image:: img/new/14-ai_intro_3_shadow.png

   In diesem Projekt verwenden wir Englisch als Beispiel für die Spracherkennung. Wenn Sie eine Erkennung in einer anderen Sprache wünschen, müssen Sie den unten stehenden Codeblock anpassen und die APK selbst kompilieren.

   Zunächst müssen Sie ``SpeechRecognizer1.Language`` auf den **Sprachcode** der gewünschten Sprache setzen. Sprachen werden durch einen Sprachcode mit einer optionalen Regionskennung angegeben, wie zum Beispiel ``en``, ``de`` oder ``ja``. Der Sprachcode kann unter |link_language_tag| gefunden werden.

   .. image:: img/new/14-ai_intro_3-1_shadow.png
      :width: 80%
      :align: center

   Danach müssen Sie die entsprechende Bedingung anpassen. Der durch den Pfeil im folgenden Bild gekennzeichnete Teil.

   .. image:: img/new/14-ai_intro_3-2_shadow.png
      :width: 80%
      :align: center

#. Um die Anwendung auf einem Smartphone zu installieren, wechseln Sie zur Registerkarte **Buildn**.

   .. image:: img/new/08-ai_intro_4_shadow.png

   * Sie können eine ``.apk``-Datei generieren. Nachdem Sie diese Option ausgewählt haben, erscheint eine Seite, auf der Sie zwischen dem Herunterladen einer ``.apk``-Datei oder dem Scannen eines QR-Codes für die Installation wählen können. Befolgen Sie die Installationsanleitung, um die Installation der Anwendung abzuschließen.

     Sie können auch unsere vorkompilierte APK hier herunterladen: :download:`VoiceControl.apk</_static/other/VoiceControl.apk>`

   * Wenn Sie diese App im Google Play Store oder einem anderen App-Marktplatz veröffentlichen möchten, können Sie eine ``.aab``-Datei generieren.


3. Den Code hochladen
-----------------------------

#. Öffnen Sie die Datei ``09-Bluetooth_voice_control_relay.ino`` im Verzeichnis ``ultimate-sensor-kit\iot_project\bluetooth\09-Bluetooth_voice_control_relay`` oder fügen Sie den Code in die **Arduino IDE** ein.

   .. raw:: html
       
       <iframe src=https://create.arduino.cc/editor/sunfounder01/ab5f8fca-dd25-4e32-bf61-d5dc109bb6cd/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

#. Wählen Sie das passende Board und den entsprechenden Port aus und klicken Sie anschließend auf die Schaltfläche **Hochladen**.

#. Öffnen Sie den Seriellen Monitor und setzen Sie die Baudrate auf **9600**, um Debug-Meldungen einzusehen.

4. Verbindung der App mit dem Bluetooth-Modul
-----------------------------------------------

Stellen Sie sicher, dass die zuvor erstellte App auf Ihrem Smartphone installiert ist.

#. Aktivieren Sie zunächst **Bluetooth** auf Ihrem Smartphone.

   .. image:: img/new/09-app_1_shadow.png
      :width: 60%
      :align: center

#. Navigieren Sie zu den **Bluetooth-Einstellungen** auf Ihrem Smartphone und suchen Sie nach Gerätenamen wie **JDY-31-SPP**.

   .. image:: img/new/09-app_2_shadow.png
      :width: 60%
      :align: center

#. Nach dem Anklicken bestätigen Sie die **Kopplungsanfrage** im aufpoppenden Fenster. Falls ein Kopplungscode erforderlich ist, geben Sie "1234" ein.

   .. image:: img/new/09-app_3_shadow.png
      :width: 60%
      :align: center

#. Öffnen Sie nun die frisch installierte **Voice-Controlled Relay**-App.

   .. image:: img/new/14-app_4_shadow.png
      :width: 25%
      :align: center

#. In der App klicken Sie auf die Schaltfläche **Connect**, um die Verbindung zwischen der App und dem Bluetooth-Modul herzustellen.

   .. image:: img/new/14-app_5_shadow.png
      :width: 60%
      :align: center

#. Diese Seite zeigt eine Liste aller gekoppelten Bluetooth-Geräte. Wählen Sie die Option ``xx.xx.xx.xx.xx.xx JDY-31-SPP`` aus der Liste. Der Gerätename wird neben der jeweiligen MAC-Adresse angezeigt.

   .. image:: img/new/14-app_6_shadow.png
      :width: 60%
      :align: center

#. Sollten keine Geräte angezeigt werden, könnte dies daran liegen, dass der App die nötigen Berechtigungen fehlen. In diesem Fall müssen Sie die Einstellungen manuell anpassen.

   * Um zur Seite **App-Informationen** zu gelangen, halten Sie das App-Symbol gedrückt und wählen es aus.

   .. image:: img/new/14-app_8_shadow.png
         :width: 60%
         :align: center

   * Navigieren Sie zur **Berechtigungsseite**.

   .. image:: img/new/08-app_9_shadow.png
         :width: 60%
         :align: center

   * Aktivieren Sie unter **Nahegelegene Geräte** die Option **Immer**, damit die App nach Geräten in der Umgebung suchen kann.

   .. image:: img/new/08-app_10_shadow.png
         :width: 60%
         :align: center

   * Starten Sie die App neu und wiederholen Sie die Schritte 5 und 6 für eine erfolgreiche Bluetooth-Verbindung.

#. Nach erfolgreicher Verbindung gelangen Sie zur Hauptseite. Dort können Sie das Relais über die Schaltflächen "ON" oder "OFF" steuern.

   .. image:: img/new/14-app_7_shadow.png
      :width: 60%
      :align: center

   Zwar können Sie das Relais auch mit kurzen Sprachbefehlen wie "on" oder "off" steuern, empfehlenswert sind jedoch vollständige Sätze wie "turn on the light", um Fehlinterpretationen zu vermeiden.

   Die Spracherkennung basiert auf Googles Spracherkennungsmotor. Daher könnte es notwendig sein, |link_speech_recognition| im Voraus zu installieren. Bei den meisten Android-Smartphones ist diese Funktion jedoch bereits vorinstalliert.

   .. image:: img/new/14-app_7-1_shadow.png
      :width: 60%
      :align: center

5. Code-Erläuterung
-----------------------------------------------

1. Kommunikation mit dem Bluetooth-Modul einrichten

   .. code-block:: arduino
   
      #include <SoftwareSerial.h>
      const int bluetoothTx = 3;                           // bluetooth tx to 3 pin
      const int bluetoothRx = 4;                           // bluetooth rx to 4 pin
      SoftwareSerial bleSerial(bluetoothTx, bluetoothRx);  // Declare SoftwareSerial object for Bluetooth communication
   
   Dieser Abschnitt initialisiert die Bluetooth-Kommunikation mit Hilfe der SoftwareSerial-Bibliothek. Diese Bibliothek ermöglicht dem Arduino, einen zusätzlichen seriellen Port zu nutzen. Der "TX"-Pin des Bluetooth-Moduls ist mit Pin 3 und der "RX"-Pin mit Pin 4 des Arduino verbunden.

2. Variablen und Steuer-Pin für das Relais definieren

   .. code-block:: arduino
   
      char character;  // Character received from Bluetooth serial
      String message;  // Stores the complete message from Bluetooth
      const int relayPin = 8;
   
   In diesem Abschnitt deklarieren wir Variablen, um einzelne Zeichen (``character``) und die komplette Nachricht (``message``) vom Bluetooth zu speichern. Der ``relayPin`` wird auf Pin 8 initialisiert, der zur Steuerung des Relais verwendet wird.

3. Serielle Kommunikation initialisieren und den Modus des Relais-Pins festlegen

   .. code-block:: arduino
   
      void setup() {
        Serial.begin(9600);
        bleSerial.begin(9600);
        pinMode(relayPin, OUTPUT);
      }
   
   In der ``setup()``-Funktion initialisieren wir den Standard-Seriell-Port und den Bluetooth-Seriell-Port mit einer Baudrate von 9600. Zudem setzen wir den ``relayPin`` als Ausgang.

4. Bluetooth-Nachrichten lesen und das Relais steuern

   .. code-block:: arduino
   
      void loop() {
        while (bleSerial.available() > 0) {
          character = bleSerial.read();
          message = message + character;
          if (character == '#') {
            message = message.substring(0, message.length() - 1);
            Serial.println();
            Serial.print("DEBUG:");
            Serial.println(message);
            if (message == "1") {
              digitalWrite(relayPin, HIGH);
              Serial.println("On");
            } else if (message == "0") {
              digitalWrite(relayPin, LOW);
              Serial.println("Off");
            }
            message = "";
            delay(200);
          }
        }
      }

   Die ``loop()``-Funktion überprüft kontinuierlich auf eingehende Nachrichten von Bluetooth. Bei Erhalt einer Nachricht wird jedes Zeichen zur ``message``-Zeichenfolge hinzugefügt. Sobald das Zeichen ``#`` erkannt wird, gilt die Nachricht als vollständig. Wir entfernen dann das ``#``, geben eine Debug-Nachricht aus und prüfen den Inhalt. Wenn dieser "1" lautet, wird das Relais eingeschaltet; bei "0" wird es ausgeschaltet. Anschließend wird die ``message``-Zeichenfolge geleert und kurz gewartet, bevor nach der nächsten Nachricht gesucht wird.
