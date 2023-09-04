So erstellen, öffnen oder speichern Sie eine Skizze
====================================================

#. Wenn Sie die Arduino IDE zum ersten Mal öffnen oder eine neue Skizze erstellen, erscheint eine Seite wie diese. Hier erstellt die Arduino IDE automatisch eine neue Datei für Sie, die als "Skizze" bezeichnet wird.

   .. image:: img/sp221014_173458.png

   Diese Skizzendateien haben einen regulären temporären Namen, an dem Sie das Erstellungsdatum der Datei erkennen können. ``sketch_oct14a.ino`` steht für die erste Skizze vom 14. Oktober, und ``.ino`` ist das Dateiformat dieser Skizze.

#. Lassen Sie uns nun eine neue Skizze erstellen. Kopieren Sie den folgenden Code in die Arduino IDE, um den ursprünglichen Code zu ersetzen.

   .. image:: img/create1.png

   .. code-block:: Arduino

       void setup() {
           // put your setup code here, to run once:
           pinMode(13,OUTPUT); 
       }

       void loop() {
           // put your main code here, to run repeatedly:
           digitalWrite(13,HIGH);
           delay(500);
           digitalWrite(13,LOW);
           delay(500);
       }

#. Drücken Sie ``Strg+S`` oder klicken Sie auf **Datei** -> **Save**. Die Skizze wird standardmäßig unter ``C:\Users\{Ihr_Benutzername}\Documents\Arduino`` gespeichert. Sie können den Namen ändern oder einen neuen Speicherort wählen.

   .. image:: img/create2.png

#. Nach erfolgreichem Speichern wird der Name in der Arduino IDE aktualisiert.

   .. image:: img/create3.png

Bitte fahren Sie mit dem nächsten Abschnitt fort, um zu erfahren, wie Sie diese erstellte Skizze auf Ihr Arduino-Board hochladen können.

