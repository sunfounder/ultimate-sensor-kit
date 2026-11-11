.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

.. _c201_connect_blynk:

1.3 Die R4-Platine mit Blynk verbinden
====================================

#. Schließen Sie das ESPC2-01-Modul an den Arduino Uno R4 Minima an.

   .. note::

      Das Modul zieht beim Start einen hohen Strom. Stecken Sie deshalb die 9-V-Batterie
      bzw. das externe Netzteil in die Hohlbuchse des R4 Minima.

   .. image:: ../img/wiring_r4_espc201.png
      :width: 80%

#. Öffnen Sie die Datei ``00-Blynk_quick_start.ino`` unter dem Pfad ``ultimate-sensor-kit\code\iot_project_espc201\wifi\00-Blynk_quick_start``.

#. Ersetzen Sie die folgenden drei Zeilen durch die Angaben, die Sie auf der Seite
   **Device** Ihres Kontos kopiert haben. Sie legen fest, zu welchem Blynk-Konto die
   Platine gehört.

   .. code-block:: arduino

      #define BLYNK_TEMPLATE_ID   "TMPLxxxxxx"
      #define BLYNK_TEMPLATE_NAME "Ultimate Sensor Kit"
      #define BLYNK_AUTH_TOKEN    "YourAuthToken"

   .. image:: ../img/blynk_copy_token.png
      :width: 80%

#. Tragen Sie den Namen und das Passwort Ihres WLAN-Netzes in ``ssid`` und ``password``
   ein.

   .. code-block:: arduino

      char ssid[] = "your_ssid";
      char pass[] = "your_password";

#. Laden Sie den Sketch hoch, öffnen Sie den Seriellen Monitor und stellen Sie die
   Baudrate auf **115200**. Sobald die Platine die Blynk-Cloud erreicht hat, erscheint
   dort ``Ready``.

   .. image:: ../img/blynk_connect_network.png
      :width: 80%

   .. note::

      Erscheint ``ESP is not responding``, prüfen Sie Folgendes:

      * Das externe Netzteil ist angeschlossen;
      * das Modul sitzt fest im Adapter und IO9 bleibt unbeschaltet;
      * drücken Sie die Reset-Taste auf der R4-Platine.

      Manchmal klappt es erst beim zweiten oder dritten Versuch.

#. Der Gerätestatus in der Blynk.Console wechselt von **offline** auf **online**.

   .. image:: ../img/blynk_online.png
      :width: 70%

Damit ist die Platine verbunden. Das nächste Kapitel beginnt mit dem ersten Projekt.
