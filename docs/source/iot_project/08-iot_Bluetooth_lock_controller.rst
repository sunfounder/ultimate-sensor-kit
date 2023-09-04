.. _iot_Bluetooth_lock_controller:

Bluetooth-Schlosssteuerung
=============================

.. raw:: html

   <video loop autoplay muted style="max-width:100%">
      <source src="../_static/video/iot/08-iot_Bluetooth_lock_controller.mp4" type="video/mp4">
      Ihr Browser unterstützt das Video-Tag nicht.
   </video>

Dieses Projekt nutzt eine mit dem MIT App Inventor erstellte Android-App, um über Bluetooth einen Servomotor aus der Ferne zu steuern und so einen Verriegelungsmechanismus zu simulieren. Benutzer können über die App spezifische Nachrichten senden, um den Servo entweder in die "verriegelte" oder "entriegelte" Position zu bewegen.

Das System verwendet ein JDY-31 Bluetooth-Modul, um diese Nachrichten zu empfangen und gibt entsprechende Anweisungen an ein Arduino Uno Board, um den Winkel des Servomotors anzupassen. Bei Empfang der Nachricht '1' bewegt sich der Servo in die "verriegelte" Position und bei Empfang der Nachricht '0' in die "entriegelte" Position.

Diese Android-Anwendung wird mithilfe einer ergänzenden webbasierten Plattform namens |link_appinventor| erstellt. Das Projekt bietet eine hervorragende Gelegenheit, die Schnittstelle zwischen einem Arduino und einem Smartphone kennen zu lernen.


1. Schaltungsaufbau
-----------------------------

.. image:: img/08-Wiring_Bluetooth_lock_controller.png
    :width: 90%

* :ref:`cpn_uno`
* :ref:`cpn_jdy31`
* :ref:`cpn_servo`


2. Erstellung der Android-App
-----------------------------

Die Android-Anwendung wird mit einer kostenlosen Webanwendung namens |link_appinventor| entwickelt. 
Der MIT App Inventor eignet sich hervorragend als Einstiegspunkt für die Android-Entwicklung dank seiner intuitiven Drag-and-Drop-Funktionen, mit denen einfache Anwendungen erstellt werden können.

Lassen Sie uns beginnen.

#. Besuchen Sie |link_appinventor_login| und klicken Sie auf "Online-Tool" zum Einloggen. Zum Registrieren bei MIT App Inventor benötigen Sie ein Google-Konto.

   .. image:: img/new/09-ai_signup_shadow.png
       :width: 90%
       :align: center

#. Nach dem Einloggen navigieren Sie zu **Projects** -> **Import project (.aia) from my computer**. Laden Sie anschließend die Datei ``Bluetooth_controlled_lock.aia`` aus dem Pfad ``ultimate-sensor-kit\iot_project\bluetooth\03-Bluetooth_lock_controller`` hoch.

   Sie können es auch direkt hier herunterladen: :download:`Bluetooth_controlled_lock.aia</_static/other/Bluetooth_controlled_lock.aia>`

   .. image:: img/new/09-ai_import_shadow.png
        :align: center

#. Nach dem Hochladen der ``.aia``-Datei wird die Anwendung in der MIT App Inventor Software angezeigt. Dies ist eine vorkonfigurierte Vorlage. Sie können diese Vorlage nach dem Vertrautmachen mit dem MIT App Inventor über die folgenden Schritte anpassen.

#. Im MIT App Inventor gibt es zwei Hauptbereiche: den **Designer** und die **Blocks**. Sie können in der oberen rechten Ecke der Seite zwischen diesen beiden Bereichen wechseln.

   .. image:: img/new/09-ai_intro_1_shadow.png

#. Mit dem **Designer** können Sie Schaltflächen, Texte, Bildschirme hinzufügen und das gesamte Aussehen Ihrer Anwendung ändern.

   .. image:: img/new/08-ai_intro_2_shadow.png
   
#. Weiter gibt es den Bereich **Blocks**. Dieser Bereich ermöglicht es Ihnen, benutzerdefinierte Funktionen für Ihre App zu erstellen, sodass Sie jedes Element auf der GUI der App programmieren können, um gewünschte Funktionen zu erreichen.

   .. image:: img/new/08-ai_intro_3_shadow.png

#. Um die Anwendung auf einem Smartphone zu installieren, gehen Sie zum Tab **Build**.

   .. image:: img/new/08-ai_intro_4_shadow.png

   * Sie können eine ``.apk``-Datei generieren. Nach Auswahl dieser Option erscheint eine Seite, auf der Sie zwischen dem Herunterladen einer ``.apk``-Datei oder dem Scannen eines QR-Codes zur Installation wählen können. Befolgen Sie die Installationsanleitung, um die Anwendungsinstallation abzuschließen. 

     Sie können auch unsere vorab kompilierte APK hier herunterladen: :download:`Bluetooth_controlled_lock.apk</_static/other/Bluetooth_controlled_lock.apk>`

   * Falls Sie die App im Google Play Store oder einem anderen App-Marktplatz veröffentlichen möchten, können Sie eine ``.aab``-Datei generieren.


3. Code hochladen
-----------------------------

#. Öffnen Sie die Datei ``03-Bluetooth_lock_controller.ino`` unter dem Pfad ``ultimate-sensor-kit\iot_project\bluetooth\03-Bluetooth_lock_controller`` oder kopieren Sie diesen Code in die **Arduino IDE**.

   .. raw:: html
       
       <iframe src=https://create.arduino.cc/editor/sunfounder01/b7d14207-953c-479c-89a8-b4a6d8c64e61/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

#. Wählen Sie das richtige Board und den richtigen Port aus und klicken Sie auf den **Hochladen**-Button.

#. Öffnen Sie den Seriellen Monitor (Baudrate auf **9600** einstellen), um Debug-Nachrichten anzuzeigen. 


4. Verbindung von App und Bluetooth-Modul
--------------------------------------------------

Vergewissern Sie sich, dass die zuvor erstellte Anwendung auf Ihrem Smartphone installiert ist.

#. Aktivieren Sie zuerst **Bluetooth** auf Ihrem Smartphone.

   .. image:: img/new/09-app_1_shadow.png
      :width: 60%
      :align: center

#. Navigieren Sie zu den **Bluetooth-Einstellungen** auf Ihrem Smartphone und suchen Sie nach Bezeichnungen wie **JDY-31-SPP**.

   .. image:: img/new/09-app_2_shadow.png
      :width: 60%
      :align: center

#. Nach dem Anklicken stimmen Sie der **Kopplungsanfrage** im Popup-Fenster zu. Falls ein Kopplungscode erforderlich ist, geben Sie bitte "1234" ein.

   .. image:: img/new/09-app_3_shadow.png
      :width: 60%
      :align: center

#. Öffnen Sie nun die neu installierte **Control_RGB_LED**-App.

   .. image:: img/new/08-app_4_shadow.png
      :width: 25%
      :align: center

#. In der App klicken Sie auf das **Schloss-Symbol**, um eine Verbindung zwischen der App und dem Bluetooth-Modul herzustellen.

   .. image:: img/new/08-app_5_shadow.png
      :width: 60%
      :align: center

#. Diese Seite zeigt eine Liste aller gekoppelten Bluetooth-Geräte an. Wählen Sie die Option ``xx.xx.xx.xx.xx.xx JDY-31-SPP`` aus der Liste. Der Name jedes Geräts wird neben seiner MAC-Adresse aufgeführt.

   .. image:: img/new/08-app_6_shadow.png
      :width: 60%
      :align: center

#. Falls Sie auf der oben dargestellten Seite keine Geräte sehen, könnte dies daran liegen, dass dieser App die Berechtigung zur Suche nach nahegelegenen Geräten fehlt. In einem solchen Fall müssen Sie die Einstellungen manuell anpassen.

   * Um zur **App-Infoseite** zu gelangen, halten Sie das App-Symbol gedrückt und wählen es aus. Oder nutzen Sie eine andere Methode, um auf diese Seite zu gelangen, falls Ihnen eine bekannt ist.

   .. image:: img/new/08-app_8_shadow.png
         :width: 60%
         :align: center

   * Navigieren Sie zur Seite **Berechtigungen**.

   .. image:: img/new/08-app_9_shadow.png
         :width: 60%
         :align: center

   * Um der App das Scannen von nahegelegenen Geräten zu ermöglichen, gehen Sie zu **Nahegelegene Geräte** und wählen **Immer**.

   .. image:: img/new/08-app_10_shadow.png
         :width: 60%
         :align: center

   * Starten Sie nun die App neu und wiederholen Sie die Schritte 5 und 6, um eine erfolgreiche Verbindung zu Bluetooth herzustellen.

#. Nach einer erfolgreichen Verbindung werden Sie zur Hauptseite weitergeleitet, auf der "connected" angezeigt wird. Nun können Sie entweder auf "Unlock" oder "Lock" klicken, um den Verriegelungsmechanismus zu steuern.

   .. image:: img/new/08-app_7_shadow.png
      :width: 60%
      :align: center

5. Code-Erklärung
--------------------------------------------------

#. Kommunikationspins definieren und SoftwareSerial-Bibliothek initialisieren

   .. code-block:: arduino

      const int bluetoothTx = 3;  
      const int bluetoothRx = 4;  
      SoftwareSerial bleSerial(bluetoothTx, bluetoothRx);  

   Im obigen Code werden die Sendepins (Tx) und Empfangspins (Rx), die vom JDY-31 Bluetooth-Modul zur Kommunikation genutzt werden, definiert. Anschließend wird die SoftwareSerial-Bibliothek initialisiert, die es dem Bluetooth-Modul ermöglicht, mit dem Arduino-Board zu kommunizieren.

#. Servo-relevante Konstanten definieren und Servo-Objekt erstellen

   .. code-block:: arduino

      const int servoPin = 9;
      const int lockAngle = 180;
      const int unlockAngle = 90;
      Servo myservo;

   Hier werden der dem Servo zugeordnete Pin sowie die Winkel für die "verriegelte" und "entriegelte" Position definiert. Ein Servo-Objekt ``myservo`` wird ebenfalls für die Steuerung des Servomotors erstellt.

#. Servo und serielle Kommunikation initialisieren

   .. code-block:: arduino

      void setup() {
        myservo.attach(servoPin);
        Serial.begin(9600);
        bleSerial.begin(9600);
      }

#. Servo-Steuerung basierend auf Eingaben des Bluetooth-Moduls

   .. code-block:: arduino

      void loop() {
        if (bleSerial.available() > 0) {
          char message = bleSerial.read(); 
          if (message == '1') {  
            myservo.write(lockAngle);
            Serial.println("Locked");
          }
          else if (message == '0') {  
            myservo.write(unlockAngle);
            Serial.println("Unlocked");
          }
        }
      }

   Die ``loop()``-Funktion wird fortlaufend ausgeführt. Sie liest eingehende Nachrichten vom Bluetooth-Modul. Wenn die Nachricht '1' lautet, wird der Servo in die "verriegelte" Position bewegt. Bei der Nachricht '0' wird der Servo in die "entriegelte" Position bewegt. Der aktuelle Status ("Verriegelt" oder "Entriegelt") wird im seriellen Monitor ausgegeben.

