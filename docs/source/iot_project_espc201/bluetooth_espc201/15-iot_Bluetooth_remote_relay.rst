.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

.. _c201_iot_Bluetooth_remote_relay:

15. Bluetooth-Relais
====================

Ein Relais ist ein Schalter, der von einem Elektromagneten bewegt wird - ein kleines
Signal steuert also eine viel größere Last. Senden Sie ``1``, zieht das Relais an, bei
``0`` fällt es ab.


1. Schaltung aufbauen
-----------------------------

.. warning::

    Das Relais in diesem Kit schaltet nur kleine Gleichstromlasten. **Schließen Sie
    niemals Netzspannung an**, solange Sie lernen - 230 V können tödlich sein, und hier
    wird sie nicht gebraucht.

.. note::

    Das Modul zieht beim Start einen hohen Strom. Stecken Sie deshalb die 9-V-Batterie
    bzw. das externe Netzteil in die Hohlbuchse des R4 Minima.


.. image:: ../img/13-Wiring_Bluetooth_remote_relay.png
   :width: 80%

* :ref:`cpn_uno`
* :ref:`cpn_espc201`
* :ref:`cpn_relay`


2. Code hochladen
-----------------------------

#. Öffnen Sie die Datei ``15-Bluetooth_remote_relay.ino`` unter dem Pfad ``ultimate-sensor-kit\code\iot_project_espc201\bluetooth\15-Bluetooth_remote_relay``.

#. Wählen Sie **Arduino UNO R4 Minima** und den richtigen Port und klicken Sie auf
   **Upload**.

#. Öffnen Sie den Seriellen Monitor mit **115200**. Er antwortet auf jeden Befehl mit
   ``On`` oder ``Off``:

   .. code-block:: text

      On
      Off


3. Vom Handy schalten
------------------------------

#. Öffnen Sie LightBlue, tippen Sie auf **Scan** und verbinden Sie sich mit
   **SunFounder-C2**, dann Dienst **0xA002** und Characteristic **C304**. Die
   Schaltfläche liegt im roten Rahmen.

   .. image:: ../img/ble_lightblue_write.png
      :width: 80%

#. Tippen Sie auf **Write new value**, stellen Sie das Format oben rechts auf
   **UTF-8 String** und geben Sie ``1`` ein. Das Bild zeigt das Feld kurz vor dem Senden:

   .. image:: ../img/ble_lightblue_1.png
      :width: 80%

#. Senden Sie es. Das Relais klickt, seine Kontroll-LED leuchtet und der Monitor schreibt
   ``On``.

#. Geben Sie ``0`` im selben Feld ein und senden Sie - das Relais fällt wieder ab und der
   Monitor schreibt ``Off``. Das Bild zeigt das Feld erneut:

   .. image:: ../img/ble_lightblue_0.png
      :width: 80%

   .. note::

      Manche Relaismodule arbeiten umgekehrt: Sie schalten ein, wenn der Pin **LOW** ist.
      Klickt Ihr Relais entgegengesetzt zum Schalter, tauschen Sie im Sketch ``HIGH`` und
      ``LOW``.


4. Code-Erklärung
-----------------------------

#. **Ein Pin, ein Schalter**

   .. code-block:: arduino

      const int relayPin = 8;

      pinMode(relayPin, OUTPUT);
      digitalWrite(relayPin, LOW);

   Das ``LOW`` in ``setup()`` ist wichtig: Ein Pin, der gerade Ausgang geworden ist, kann
   kurz HIGH sein und das Relais bei jedem Neustart klicken lassen.

#. **Die Befehlsprüfung**

   .. code-block:: arduino

      if (message == '1') {
        digitalWrite(relayPin, HIGH);
        Serial.println("On");
      } else if (message == '0') {
        digitalWrite(relayPin, LOW);
        Serial.println("Off");
      }

   Gleiche Form wie beim Schloss: Der Zustand kommt vom Handy, alles außer ``1`` und ``0``
   wird ignoriert.

#. **Warum das Relais nicht direkt vom Handy geschaltet wird**

   Das Handy spricht mit dem Modul, das Modul spricht über zwei Drähte mit der Platine,
   und die Platine schaltet das Relais. Jede Stufe gibt nur einen kurzen Befehl weiter -
   deshalb genügt ein einziges Zeichen, obwohl drei Geräte beteiligt sind.
