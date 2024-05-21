.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

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

