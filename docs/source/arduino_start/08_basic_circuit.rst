.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

Wie man den Schaltkreis baut
============================

Viele Dinge, die Sie täglich verwenden, werden von Strom betrieben, beispielsweise die Lichter in Ihrem Haus und der Computer, auf dem Sie gerade lesen.

Um Elektrizität zu nutzen, müssen Sie einen elektrischen Schaltkreis aufbauen. Ein Schaltkreis ist im Grunde ein Pfad, durch den Strom fließt. Er besteht aus elektrischen Geräten und Komponenten, die auf bestimmte Weise verbunden sind, wie Widerstände, Kondensatoren, Stromversorgungen und Schalter.

.. image:: img/circuit.png
    :align: center
    :width: 250

.. raw:: html
    
    <br/>

Ein Schaltkreis ist ein geschlossener Pfad, in dem Elektronen sich bewegen, um einen elektrischen Strom zu erzeugen. Damit Strom fließen kann, muss ein leitender Pfad zwischen dem positiven und dem negativen Anschluss der Stromversorgung existieren, was man als geschlossenen Schaltkreis bezeichnet (wenn er unterbrochen ist, nennt man das einen offenen Schaltkreis).

Das Arduino-Board verfügt über einige Stromausgangspins (positiv) und einige Erdungspins (negativ).
Sie können diese Pins als positive und negative Seiten der Stromversorgung verwenden, indem Sie die Stromquelle an das Board anschließen.

.. image:: img/arduinoPN.jpg
    :align: center
    :width: 65%

Mit Elektrizität können Sie Licht, Ton und Bewegung erzeugen.
Sie können eine LED zum Leuchten bringen, indem Sie den langen Pin an den positiven und den kurzen Pin an den negativen Anschluss anschließen.
Ohne einen 220* Widerstand im Schaltkreis würde die LED sehr schnell kaputtgehen, daher muss dieser zur Schutz hinzugefügt werden.

Der von ihnen gebildete Schaltkreis ist unten abgebildet.

.. image:: img/sp221014_181625.png
    :align: center
    :width: 65%

.. raw:: html
    
    <br/>

Sie fragen sich vielleicht: Wie baue ich diesen Schaltkreis? Halte ich die Drähte mit der Hand oder klebe ich die Pins und Drähte fest?

In dieser Situation sind lötfreie Steckbretter Ihre besten Helfer.

.. _bc_bb:

Hallo, Steckbrett!
------------------

Ein Steckbrett ist eine rechteckige Kunststoffplatte mit vielen kleinen Löchern.
Diese Löcher ermöglichen es uns, elektronische Komponenten einfach einzufügen und elektronische Schaltkreise aufzubauen.
Da Steckbretter elektronische Komponenten nicht dauerhaft befestigen, können wir einen Schaltkreis leicht reparieren oder von vorn beginnen, wenn etwas schief geht.

.. note::
    Für die Verwendung von Steckbrettern sind keine speziellen Werkzeuge erforderlich. Viele elektronische Bauteile sind jedoch sehr klein, und eine Pinzette kann uns helfen, kleine Teile besser aufzunehmen.

Im Internet finden wir viele Informationen über Steckbretter.

* `Wie benutzt man ein Steckbrett - Science Buddies <https://www.sciencebuddies.org/science-fair-projects/references/how-to-use-a-breadboard#pth-smd>`_

* `Was ist ein STECKBRETT? - Makezine <https://cdn.makezine.com/uploads/2012/10/breadboardworkshop.pdf>`_

Hier sind einige Dinge, die Sie über Steckbretter wissen sollten.

#. Jede halbe Reihengruppe (wie z.B. Spalte A-E in Reihe 1 oder Spalte F-J in Reihe 3) ist verbunden. Fließt also ein elektrisches Signal bei A1 hinein, kann es bei B1, C1, D1, E1 herausfließen, aber nicht bei F1 oder A2.

#. In den meisten Fällen werden beide Seiten des Steckbretts als Stromschienen verwendet, und die Löcher in jeder Spalte (etwa 50 Löcher) sind miteinander verbunden. In der Regel werden positive Stromversorgungen mit den Löchern in der Nähe des roten Drahts und negative mit den Löchern in der Nähe des blauen Drahts verbunden.

#. In einem Schaltkreis fließt der Strom nach Durchlaufen der Last vom positiven zum negativen Pol. In diesem Fall könnte ein Kurzschluss auftreten.



**Lassen Sie uns der Stromrichtung folgen, um den Schaltkreis aufzubauen!**

.. image:: img/sp221014_182229.png
    :align: center
    :width: 60%

.. raw:: html
    
    <br/>

1. In diesem Schaltkreis verwenden wir den 5V-Pin des Boards, um die LED zu versorgen. Verwenden Sie ein Männchen-zu-Männchen (M2M) Verbindungskabel, um ihn an die rote Stromschiene anzuschließen.

#. Um die LED zu schützen, muss der Strom durch einen 220 Ohm Widerstand fließen. Verbinden Sie ein Ende (egal welches) des Widerstands mit der roten Stromschiene und das andere Ende mit der freien Reihe des Steckbretts.

   .. note::
        Der Farbring des 220 Ohm Widerstands ist rot, rot, schwarz, schwarz und braun.

#. Wenn Sie die LED aufnehmen, sehen Sie, dass einer ihrer Anschlüsse länger ist als der andere. Verbinden Sie den längeren Anschluss mit derselben Reihe wie der Widerstand und den kürzeren Anschluss mit der anderen Reihe.

   .. note::
        Der längere Anschluss ist die Anode, die die positive Seite des Schaltkreises repräsentiert; der kürzere Anschluss ist die Kathode, die die negative Seite darstellt. 

        Die Anode muss über einen Widerstand mit dem GPIO-Pin verbunden werden; die Kathode muss mit dem GND-Pin verbunden werden.

#. Verwenden Sie ein Männchen-zu-Männchen (M2M) Verbindungskabel, um den kurzen LED-Pin mit der negativen Stromschiene des Steckbretts zu verbinden.
#. Verbinden Sie den GND-Pin des Boards mit der negativen Stromschiene mittels eines Verbindungskabels.

Achtung vor Kurzschlüssen
--------------------------

Kurzschlüsse können auftreten, wenn zwei Komponenten, die nicht verbunden sein sollten, "versehentlich" miteinander verbunden werden. 
Dieses Kit enthält Widerstände, Transistoren, Kondensatoren, LEDs usw. mit langen Metallanschlüssen, die aneinanderstoßen und einen Kurzschluss verursachen können. Manche Schaltkreise funktionieren einfach nicht richtig, wenn ein Kurzschluss auftritt. Gelegentlich kann ein Kurzschluss Komponenten dauerhaft beschädigen, insbesondere zwischen der Stromversorgung und der Erdungsschiene, wodurch der Schaltkreis sehr heiß wird, das Plastik auf dem Steckbrett schmilzt und sogar die Komponenten verbrennt!

Daher stellen Sie immer sicher, dass die Pins aller Elektronikteile auf dem Steckbrett sich nicht berühren.


Schaltkreisrichtung
-------------------------------
Schaltkreise haben eine Orientierung, die bei bestimmten elektronischen Komponenten eine wichtige Rolle spielt. Es gibt Bauteile mit Polarität, d.h., sie müssen entsprechend ihrer positiven und negativen Pole korrekt angeschlossen werden. Falsch orientierte Schaltkreise funktionieren nicht ordnungsgemäß.

.. image:: img/sp221014_182229.png
    :align: center
    :width: 60%

.. raw:: html
    
    <br/>

Wenn Sie die LED in diesem einfachen Schaltkreis, den wir zuvor aufgebaut haben, umkehren, werden Sie feststellen, dass sie nicht mehr funktioniert.

Im Gegensatz dazu haben manche Bauteile keine Richtung, wie die Widerstände in diesem Schaltkreis. Daher können Sie versuchen, diese umzukehren, ohne die normale Funktion der LEDs zu beeinträchtigen.

Die meisten Komponenten und Module, die mit Bezeichnungen wie "+", "-", "GND", "VCC" gekennzeichnet sind oder Anschlusspins unterschiedlicher Länge haben, müssen auf eine bestimmte Weise an den Schaltkreis angeschlossen werden.


Schutz des Schaltkreises
-------------------------------------

Stromstärke ist die Geschwindigkeit, mit der Elektronen an einem Punkt im vollständigen elektrischen Schaltkreis vorbeifließen. Im Grundprinzip gilt: Stromstärke = Fluss. Die Einheit Ampere (AM-pir), kurz Amp, ist die international anerkannte Einheit zur Messung der Stromstärke. Sie gibt die Menge der Elektronen (manchmal als "elektrische Ladung" bezeichnet) an, die an einem Punkt im Schaltkreis innerhalb einer bestimmten Zeit vorbeifließen.

Die treibende Kraft (Spannung) hinter dem Stromfluss wird als Spannung bezeichnet und in Volt (V) gemessen.

Der Widerstand (R) ist die Eigenschaft des Materials, die den Stromfluss einschränkt, und wird in Ohm (Ω) gemessen.

Gemäß dem Ohmschen Gesetz (solange die Temperatur konstant bleibt) sind Stromstärke, Spannung und Widerstand proportional.
Die Stromstärke eines Schaltkreises ist proportional zu seiner Spannung und umgekehrt proportional zu seinem Widerstand.

Daher gilt: Stromstärke (I) = Spannung (V) / Widerstand (R).

* `Ohmsches Gesetz – Wikipedia <https://de.wikipedia.org/wiki/Ohmsches_Gesetz>`_

Zum Ohmschen Gesetz können wir ein einfaches Experiment durchführen.

.. image:: img/sp221014_183107.png

Wenn Sie das Drahtverbindung von 5V auf 3,3V ändern, wird die LED schwächer.
Wechseln Sie den Widerstand von 220 Ohm auf 1000 Ohm (Farbring: braun, schwarz, schwarz, braun und braun), werden Sie feststellen, dass die LED schwächer wird als zuvor. Je größer der Widerstand, desto schwächer die LED.

Die meisten vorgefertigten Module benötigen nur Zugang zur richtigen Spannung (meistens 3,3V oder 5V), wie beispielsweise Ultraschallmodule.

In Ihren selbstgebauten Schaltkreisen müssen Sie jedoch auf die Versorgungsspannung und den Widerstandseinsatz für elektrische Bauteile achten.

Als Beispiel verbrauchen LEDs in der Regel 20mA Strom und haben einen Spannungsabfall von etwa 1,8V. Gemäß dem Ohmschen Gesetz benötigen wir bei einer 5V-Stromversorgung mindestens einen 160-Ohm-Widerstand ((5-1,8)/20mA), um die LED nicht zu zerstören.




Schaltkreissteuerung mit Arduino
--------------------------------

Nachdem wir nun ein grundlegendes Verständnis für die Arduino-Programmierung und elektronische Schaltkreise haben, wird es Zeit, sich der wichtigsten Frage zu widmen: Wie steuert man Schaltkreise mit Arduino?

Vereinfacht ausgedrückt, steuert Arduino einen Schaltkreis, indem es den Pegel der Pins auf dem Board ändert. Beispielsweise wird beim Steuern einer integrierten LED ein High- oder Low-Level-Signal an Pin 13 gesendet.

Jetzt versuchen wir, das Arduino-Board so zu programmieren, dass die LED auf dem Steckbrett blinkt. Bauen Sie den Schaltkreis so, dass die LED an Pin 9 angeschlossen ist.

.. image:: img/wiring_led.png
    :width: 400
    :align: center

Laden Sie anschließend diesen Sketch auf das Arduino-Entwicklungsboard hoch.

.. code-block:: C

    int ledPin = 9;
    int delayTime = 500;

    void setup() {
        pinMode(ledPin,OUTPUT);
    }

    void loop() {
        digitalWrite(ledPin,HIGH);
        delay(delayTime);
        digitalWrite(ledPin,LOW);
        delay(delayTime);
    }

Dieser Sketch ähnelt stark dem, den wir verwendet haben, um das Blinken der integrierten LED zu steuern. Der Unterschied ist, dass der Wert von ``ledPin`` diesmal auf 9 geändert wurde.
Das liegt daran, dass wir dieses Mal versuchen, den Pegel von Pin 9 zu steuern.

Jetzt sehen Sie die LED auf dem Steckbrett blinken.


