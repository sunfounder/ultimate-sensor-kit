.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

.. _cpn_relay:

5V-Relaismodul
==========================

.. image:: img/25_relay_module.png
    :width: 400
    :align: center

Einleitung
---------------------------
5V-Relaismodule sind Geräte, die Hochspannungs- oder Hochstromgeräte mit einem 5V-Signal vom Arduino ein- und ausschalten können. Sie eignen sich zur Steuerung von Geräten wie Lampen, Lüftern, Motoren oder Magnetventilen. Ein 5V-Relais verfügt über drei Hochspannungsanschlüsse (NC, C und NO), die an das zu steuernde Gerät angeschlossen werden. Auf der anderen Seite befinden sich drei Niederspannungsanschlüsse (Ground, Vcc und Signal), die mit dem Arduino verbunden werden.

Funktionsprinzip
---------------------------
Ein Relais ist ein Bauelement, das zur Herstellung einer Verbindung zwischen zwei oder mehr Punkten oder Geräten in Reaktion auf ein eingegebenes Signal verwendet wird. Mit anderen Worten, Relais bieten eine Isolation zwischen dem Controller und den angeschlossenen Geräten, die entweder mit Wechsel- oder Gleichstrom arbeiten können. Da sie Signale von einem Mikrocontroller erhalten, der mit Gleichstrom arbeitet, ist ein Relais erforderlich, um die Lücke zu überbrücken. Relais sind besonders nützlich, wenn man mit einem kleinen elektrischen Signal eine große Menge an Strom oder Spannung steuern möchte.

Ein Relais besteht aus fünf Hauptkomponenten:

.. image:: img/25_relay_2.jpeg
    :width: 500
    :align: center

Elektromagnet - Er besteht aus einem Eisenkern, um den eine Drahtspule gewickelt ist. Wird Strom durch ihn geleitet, wird er magnetisch.

Anker - Der bewegliche magnetische Streifen wird als Anker bezeichnet. Wenn Strom durch die Spule fließt, wird ein Magnetfeld erzeugt, das dazu dient, die Kontakte entweder zu schließen oder zu öffnen. Der Anker kann sowohl mit Gleich- als auch mit Wechselstrom bewegt werden.

Feder - Wenn kein Strom durch die Spule des Elektromagneten fließt, zieht die Feder den Anker zurück, sodass der Stromkreis unterbrochen wird.

Elektrische Kontakte - Es gibt zwei Kontaktstellen:

* Normalerweise offen - geschlossen, wenn das Relais aktiviert ist, und offen, wenn es inaktiv ist.
* Normalerweise geschlossen - offen, wenn das Relais aktiviert ist, und geschlossen, wenn es inaktiv ist.

Gehäuse - Dies ist typischerweise aus Kunststoff gefertigt und bietet strukturelle Unterstützung und Schutz für das Relais.

Die Funktionsweise eines Relais ist einfach. Sobald Strom zugeführt wird, beginnt der Strom durch die Steuerspule zu fließen, und der Elektromagnet wird aktiviert. Dann wird der Anker zum Elektromagneten gezogen, und die Kontakte schließen sich. Dadurch wird der Lastkreis eingeschaltet. Um den Kreislauf zu unterbrechen, wird der Anker durch die Kraft der Feder zurückgezogen. Auf diese Weise kann das Ein- und Ausschalten des Relais den Zustand einer Last steuern.

Anwendungsbeispiele
---------------------------

**Hardwarekomponenten**

- Arduino Uno R4 oder R3 Board * 1
- 5V-Relaismodul * 1
- Jumperkabel

**Schaltungsaufbau**

.. image:: img/25_relay_module_circuit.png
    :width: 100%
    :align: center

.. raw:: html
    
    <br/><br/>   

.. warning ::
    Das folgende Beispiel zeigt die Verwendung eines Relais zur Steuerung eines LED-Moduls. 
    **Obwohl das Relais in realen Anwendungen auch für andere Geräte verwendet werden kann, ist bei der Arbeit mit HOHER Wechselspannung äußerste Vorsicht geboten. Unsachgemäßer oder fehlerhafter Gebrauch kann zu schweren Verletzungen oder sogar zum Tod führen. Daher ist es für Personen gedacht, die sich mit HOHER Wechselspannung auskennen. Sicherheit hat immer Vorrang.**

Programmcode
^^^^^^^^^^^^^^^^^^^^

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/d3f6723d-bd49-4461-96de-84293f2e6d10/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/25-component_relay.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>
   <br/><br/>  

Code-Erklärung
^^^^^^^^^^^^^^^^^^^^

#. Einrichten des Relais-Pins:

   - Das Relaismodul ist an Pin 6 des Arduino angeschlossen. Dieser Pin wird im Code als ``relayPin`` bezeichnet.

   .. code-block:: arduino
    
      const int relayPin = 6;

#. Konfigurieren des Relais-Pins als Ausgang:

   - In der ``setup()`` Funktion wird der Relais-Pin als OUTPUT festgelegt, um Signale (entweder HIGH oder LOW) an diesen Pin zu senden.

   .. code-block:: arduino

      void setup() {
        pinMode(relayPin, OUTPUT);
      }

#. Ein- und Ausschalten des Relais:

   - In der ``loop()`` Funktion wird das Relais zunächst auf den OFF-Zustand gesetzt (``digitalWrite(relayPin, LOW)``) und bleibt 3 Sekunden in diesem Zustand (``delay(3000)``).
   - Anschließend wird das Relais auf den ON-Zustand gesetzt (``digitalWrite(relayPin, HIGH)``) und bleibt ebenfalls 3 Sekunden in diesem Zustand.
   - Dieser Zyklus wiederholt sich unendlich.

   .. code-block:: arduino

      void loop() {
        digitalWrite(relayPin, LOW);
        delay(3000);

        digitalWrite(relayPin, HIGH);
        delay(3000);
      }

Weitere Ideen
^^^^^^^^^^^^^^^^^^^^

- Einführung eines physischen Schalters zur manuellen Steuerung des Relaiszustands.

- Integration von Sensoren (wie Temperatur- oder Lichtsensor) zur Auslösung des Relais abhängig von den Umgebungsbedingungen.

Weitere Projekte
---------------------------
* :ref:`fun_light_control_switch`
* :ref:`fun_motion_triggered_relay`
* :ref:`iot_Remote_relay_controller`
* :ref:`iot_Bluetooth_remote_relay`
* :ref:`iot_Bluetooth_voice_control_relay`
