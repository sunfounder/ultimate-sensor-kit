.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

.. _c201_install_libs:

1.2 Bibliotheken installieren
=============================

Die Sketche brauchen **zwei** Bibliotheken. Eine kommt aus dem Bibliotheksverwalter der
Arduino IDE, die andere muss von Hand heruntergeladen und hinzugefügt werden.

**Blynk-Bibliothek installieren**

#. Öffnen Sie in der Arduino IDE den **Bibliotheksverwalter**, suchen Sie nach ``blynk``
   und klicken Sie auf **INSTALLIEREN**.

   .. image:: ../img/blynk26_11_library.png
      :width: 80%

#. Der Installer fragt zusätzlich nach **BlynkNcpDriver** - wählen Sie **ALLE
   installieren**.

   .. image:: ../img/blynk_lib_blynk.png
      :width: 60%

.. note::

   Die Bibliothek heißt **BlynkESP8266** und definiert ``ESP8266 wifi;`` - diese Namen sind
   historisch, sie stammen von dem Modul, für das Blynk vor Jahren geschrieben wurde. Mit
   dem ESPC2-01 funktionieren sie genauso, denn auch dieses Modul antwortet auf die
   AT-Befehle.

**BlynkESP8266-Bibliothek installieren**

Diese Bibliothek ist nicht im Bibliotheksverwalter enthalten und muss von GitHub
heruntergeladen werden.

#. Laden Sie `BlynkESP8266 <https://github.com/vshymanskyy/BlynkESP8266/archive/refs/heads/master.zip>`_
   herunter.

#. Wählen Sie in der Arduino IDE **Sketch -> Bibliothek einbinden -> .ZIP-Bibliothek
   hinzufügen...**

   .. image:: ../img/blynk_add_zip_lib.png
      :width: 80%

#. Wählen Sie die heruntergeladene ZIP-Datei aus - sie muss vorher nicht entpackt werden.

   .. image:: ../img/blynk_choose_zip.png
      :width: 80%

#. Starten Sie die Arduino IDE neu, nachdem die Bibliothek hinzugefügt wurde.

.. note::

    Diese Bibliothek nutzt das alte 1.0-Layout, deshalb meldet die IDE unter Umständen,
    dass sie keine Versionsnummer lesen kann. Die Warnung können Sie ignorieren - die
    Sketche lassen sich problemlos kompilieren und hochladen.
