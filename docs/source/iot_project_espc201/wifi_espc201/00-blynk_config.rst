.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

1.1 Blynk einrichten
==========================

In diesem Kapitel legen wir ein Blynk-Konto, ein Template und ein Gerät an und kopieren
die drei Zeilen, die in jedem Projektsketch ganz oben stehen. Das passiert **einmal** -
alle Projekte dieses Kits verwenden dasselbe Template und dasselbe Gerät.

.. note::

    Die Oberfläche der Blynk.Console wird von Zeit zu Zeit überarbeitet. Die Screenshots
    unten stammen aus dem Jahr 2026. Wenn eine Schaltfläche woanders liegt, orientieren
    Sie sich am **Feldnamen** (zum Beispiel ``AUTH TOKEN``) statt an der genauen Position.

1. Konto anlegen
--------------------

#. Rufen Sie `BLYNK <https://blynk.io/>`_ auf und klicken Sie oben rechts auf **Sign Up**.

   .. image:: ../img/blynk26_01_signup.png
      :width: 80%

#. Geben Sie Ihre E-Mail-Adresse ein, setzen Sie das Häkchen für die Bedingungen und
   klicken Sie auf **Sign Up**.

   .. image:: ../img/blynk26_02_email.png
      :width: 60%

#. Sie werden gebeten, Ihr Postfach zu prüfen. Öffnen Sie den Aktivierungslink in der
   Mail und legen Sie anschließend ein Passwort fest.

   .. image:: ../img/blynk26_03_password.png
      :width: 60%

2. Template anlegen
--------------------

Ein **Template** ist der Bauplan: Es legt fest, welche Daten das Projekt sendet und wie
das Dashboard aussieht. Sie legen es einmal an und ergänzen es nach und nach, während Sie
die Projekte durcharbeiten.

#. Öffnen Sie in der linken Seitenleiste **Developer Zone**, dann **My Templates** und
   klicken Sie auf **+ New Template**.

   .. image:: ../img/blynk_new_template.png
      :width: 80%

#. Richten Sie das Template ein.

   .. image:: ../img/blynk_config_template.png
      :width: 80%

#. Füllen Sie das Formular aus:

   * **NAME**: ``Ultimate Sensor Kit``
   * **HARDWARE**: **ESP32**
   * **CONNECTION TYPE**: **WiFi**

   .. image:: ../img/blynk_template_set.png
      :width: 80%

#. Klicken Sie auf **Done** / **Save**, um das Template zu speichern.

   .. image:: ../img/blynk_save.png
      :width: 40%

Zu diesem Zeitpunkt ist das Template **leer** - keine Datastreams, keine Events, kein
Dashboard. Das ist beabsichtigt: Sie kommen erst in den einzelnen Projekten dazu, wenn
bekannt ist, welche Daten das Projekt braucht.

Da alle Projekte dasselbe Template nutzen, bekommt jedes Projekt **eigene virtuelle Pins**,
damit sie sich nicht gegenseitig überschreiben:

.. list-table::
   :header-rows: 1
   :widths: 40 30 30

   * - Projekt
     - Virtuelle Pins
     - Wofür
   * - Flammenwarnsystem
     - V0
     - Wert des Flammensensors
   * - Einbruchwarnsystem
     - V1 - V2
     - Abwesenheitsmodus, Statustext
   * - Pflanzenüberwachung
     - V3 - V6
     - Temperatur, Luftfeuchte, Bodenfeuchte, LED
   * - Funk-Relaissteuerung
     - V7
     - Zustand des Relais
   * - Automatische Bewässerung
     - V8 - V10
     - Bodenfeuchte, Schwellwert, Automatikmodus

Sie müssen sich die Nummern nicht merken - jede Projektseite nennt die Pins, die sie
verwendet.

.. note::

   Jeder Datastream hat **zwei Namen**, und Blynk verwendet sie für unterschiedliche
   Dinge:

   * **DATASTREAM NAME** - der technische Name, zum Beispiel ``away_mode``. Diesen sehen
     die API und MQTT; er wird klein und mit Unterstrichen geschrieben.
   * **DISPLAY NAME** - der Name, den Widgets und Dashboards anzeigen, zum Beispiel
     ``Away Mode``. Blynk erzeugt ihn automatisch, indem jeder Wortanfang groß
     geschrieben und jeder Unterstrich durch ein Leerzeichen ersetzt wird.

   Deshalb steht auf einem Widget ``Away Mode (V1)``, obwohl der Datastream
   ``away_mode`` heißt. Die Projektseiten nennen das Widget beim Anzeigenamen, weil
   genau dieser Text auf dem Bildschirm steht.

3. Gerät anlegen
------------------

Ein Template allein hat **keinen** Auth-Token - den hat ein Gerät. Das Gerät ist die
eigentliche Platine, und es übernimmt das Template.

#. Klicken Sie in der linken Seitenleiste auf **Devices**, dann auf **+ New Device**.

   .. image:: ../img/blynk_new_device.png
      :width: 80%

#. Wählen Sie **From template**.

   .. image:: ../img/blynk_new_device_tem.png
      :width: 80%

#. Wählen Sie das Template **Ultimate Sensor Kit**, geben Sie dem Gerät einen Namen und
   klicken Sie auf **Create**.

   .. image:: ../img/blynk_device_name.png
      :width: 80%

#. Ein Fenster **New Device Created!** erscheint mit den drei Zeilen, die Sie brauchen.

   .. image:: ../img/blynk_token.png
      :width: 80%

#. Kopieren Sie sie **exakt** - ein falsches Zeichen und die Platine verbindet sich nie.

   .. code-block:: cpp

      #define BLYNK_TEMPLATE_ID   "TMPL..."
      #define BLYNK_TEMPLATE_NAME "Ultimate Sensor Kit"
      #define BLYNK_AUTH_TOKEN    "..."

   .. note::

      * Wenn Sie das Fenster schließen, finden Sie dieselben Angaben unter **Devices** ->
        Ihr Gerät.
      * Der Token gehört zum **Gerät**, nicht zum Template. Weitere Datastreams im
        Template ändern den Token nicht, die Sketche laufen also weiter.

Template und Gerät sind fertig. Im nächsten Kapitel installieren Sie die beiden
Bibliotheken, die die Sketche benötigen.
