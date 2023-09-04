Struktur eines Arduino-Programms
================================

Schauen wir uns die neue Skizze an. Obwohl sie bereits einige Codezeilen enthält, handelt es sich tatsächlich um eine "leere" Skizze.
Das Hochladen dieser Skizze auf das Entwicklungsboard wird keine Auswirkung haben.

.. code-block:: arduino

    void setup() {
    // Hier kommt der Einrichtungscode hin, der einmal ausgeführt wird:

    }

    void loop() {
    // Hier kommt der Hauptcode hin, der wiederholt ausgeführt wird:

    }

Wenn wir ``setup()`` und ``loop()`` entfernen und die Skizze zu einer echten "leeren" Datei machen, werden Sie feststellen, dass sie die Überprüfung nicht besteht.
Sie sind das Äquivalent zum menschlichen Skelett und unverzichtbar.

Während der Skizzenerstellung wird ``setup()`` zuerst ausgeführt und der darin enthaltene Code (innerhalb von ``{}``) wird nach dem Einschalten oder Zurücksetzen des Boards genau einmal ausgeführt.
``loop()`` dient dazu, die Hauptfunktion zu schreiben, und der darin enthaltene Code wird in einer Schleife ausgeführt, nachdem ``setup()`` abgearbeitet ist.

Um ``setup()`` und ``loop()`` besser zu verstehen, verwenden wir vier Skizzen. Ihr Ziel ist es, die integrierte LED des Arduino blinken zu lassen. Führen Sie bitte jedes Experiment nacheinander aus und dokumentieren Sie die spezifischen Effekte.

* Skizze 1: Die integrierte LED blinkt kontinuierlich.

.. code-block:: arduino
    :emphasize-lines: 8,9,10,11

    void setup() {
        // Einrichtungscode, der einmal ausgeführt wird:
        pinMode(13, OUTPUT);
    }

    void loop() {
        // Hauptcode, der wiederholt ausgeführt wird:
        digitalWrite(13, HIGH);
        delay(500);
        digitalWrite(13, LOW);
        delay(500);
    }

* Skizze 2: Die integrierte LED blinkt nur einmal.

.. code-block:: arduino
    :emphasize-lines: 4,5,6,7

    void setup() {
        // Einrichtungscode, der einmal ausgeführt wird:
        pinMode(13, OUTPUT);
        digitalWrite(13, HIGH);
        delay(500);
        digitalWrite(13, LOW);
        delay(500);
    }

    void loop() {
        // Hauptcode, der wiederholt ausgeführt wird:
    }

* Skizze 3: Die integrierte LED blinkt einmal langsam und dann schnell.

.. code-block:: arduino
    :emphasize-lines: 4,5,6,7,12,13,14,15

    void setup() {
        // Einrichtungscode, der einmal ausgeführt wird:
        pinMode(13, OUTPUT);
        digitalWrite(13, HIGH);
        delay(1000);
        digitalWrite(13, LOW);
        delay(1000);
    }

    void loop() {
        // Hauptcode, der wiederholt ausgeführt wird:
        digitalWrite(13, HIGH);
        delay(200);
        digitalWrite(13, LOW);
        delay(200);
    }

* Skizze 4: Fehlermeldung.

.. code-block:: arduino
    :emphasize-lines: 6,7,8,9

    void setup() {
        // Einrichtungscode, der einmal ausgeführt wird:
        pinMode(13, OUTPUT);
    }

    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    delay(1000);

    void loop() {
        // Hauptcode, der wiederholt ausgeführt wird:
    }

Mit Hilfe dieser Skizzen können wir mehrere Eigenschaften von ``setup-loop`` zusammenfassen.

* ``loop()`` wird wiederholt ausgeführt, nachdem das Board eingeschaltet ist.
* ``setup()`` wird nur einmal ausgeführt, nachdem das Board eingeschaltet ist.
* Nach dem Einschalten des Boards wird zuerst ``setup()`` und dann ``loop()`` ausgeführt.
* Der Code muss innerhalb des ``{}``-Bereichs von ``setup()`` oder ``loop()`` geschrieben werden, außerhalb dieses Rahmens führt es zu einem Fehler.

.. note::  
    Anweisungen wie ``digitalWrite(13, HIGH)`` dienen zur Steuerung der integrierten LED. Ihre genaue Verwendung wird in späteren Kapiteln detailliert erläutert.

