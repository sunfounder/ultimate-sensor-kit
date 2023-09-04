Skizzen-Schreibregeln
================================

Wenn du einen Freund bittest, das Licht für dich einzuschalten, kannst du einfach sagen: "Schalte das Licht ein" oder "Mach Licht, Kumpel." Dabei spielt der Tonfall keine Rolle.

Wenn du jedoch möchtest, dass ein Arduino-Board etwas für dich tut, musst du die Programmschreibregeln von Arduino befolgen.

Dieses Kapitel enthält die grundlegenden Regeln der Arduino-Sprache und hilft dir zu verstehen, wie du natürliche Sprache in Code übersetzen kannst.

Natürlich erfordert dieser Prozess eine gewisse Eingewöhnungszeit und ist gerade für Anfänger am fehleranfälligsten. Wenn du also oft Fehler machst, ist das kein Problem, versuche es einfach noch ein paar Mal.


Semikolon ``;``
---------------

Genau wie im Briefverkehr, wo am Ende jedes Satzes ein Punkt steht, verlangt die Arduino-Sprache, dass du ``;`` verwendest, um das Board über das Ende eines Befehls zu informieren.

Nehmen wir das bekannte Beispiel der "an Bord befindlichen LED-Blinkanzeige". Ein fehlerfreies Skript könnte so aussehen:

Beispiel:

.. code-block:: arduino

    void setup() {
        // Füge hier deinen Setup-Code ein, der einmal ausgeführt wird:
        pinMode(13, OUTPUT); 
    }

    void loop() {
        // Füge hier deinen Hauptcode ein, der wiederholt ausgeführt wird:
        digitalWrite(13, HIGH);
        delay(500);
        digitalWrite(13, LOW);
        delay(500);
    }

Als nächstes betrachten wir die folgenden beiden Skizzen und überlegen, ob sie vom Arduino korrekt erkannt werden, bevor wir sie ausführen.

Skizze A:

.. code-block:: arduino
    :emphasize-lines: 8,9,10,11

    void setup() {
        // Füge hier deinen Setup-Code ein, der einmal ausgeführt wird:
        pinMode(13, OUTPUT); 
    }

    void loop() {
        // Füge hier deinen Hauptcode ein, der wiederholt ausgeführt wird:
        digitalWrite(13, HIGH)
        delay(500)
        digitalWrite(13, LOW)
        delay(500)
    }

Skizze B:

.. code-block:: arduino
    :emphasize-lines: 8,9,10,11,12,13,14,15,16

    void setup() {
        // Füge hier deinen Setup-Code ein, der einmal ausgeführt wird:
        pinMode(13, OUTPUT);
    }
    
    void loop() {
        // Füge hier deinen Hauptcode ein, der wiederholt ausgeführt wird:
        digitalWrite(13,
    HIGH);  delay
        (500
        );
        digitalWrite(13,
        
        LOW);
                delay(500)
        ;
    }

Das Ergebnis ist, dass **Skizze A** einen Fehler meldet und **Skizze B** ausgeführt wird.

* Die Fehler in **Skizze A** sind fehlende ``;`` und obwohl die Skizze normal aussieht, kann sie von Arduino nicht gelesen werden.
* **Skizze B** mag unleserlich erscheinen, aber Einrückungen, Zeilenumbrüche und Leerzeichen in den Anweisungen sind für den Arduino-Compiler irrelevant. Daher sieht die Skizze für ihn genauso aus wie im Beispiel.

Bitte schreibe deinen Code jedoch nicht wie in **Skizze B**, da es in der Regel Menschen sind, die den Code schreiben und lesen. Erschwere dir also nicht unnötig die Arbeit.


Geschweifte Klammern ``{}``
---------------------------

Geschweifte Klammern ``{}`` sind ein Hauptbestandteil der Arduino-Programmiersprache und müssen immer paarweise vorkommen.
Eine gängige Programmierrichtlinie besteht darin, direkt nach dem Tippen der öffnenden geschweiften Klammer auch die schließende geschweifte Klammer einzufügen und den Cursor dann zwischen die Klammern zu setzen, um die Anweisung einzufügen.


Kommentare ``//``
------------------

Kommentare sind die Teile einer Skizze, die der Compiler ignoriert. Sie dienen in der Regel dazu, anderen zu erklären, wie das Programm funktioniert.

Schreibt man zwei aufeinanderfolgende Schrägstriche in einer Codezeile, wird alles bis zum Ende der Zeile vom Compiler ignoriert.

Wenn wir eine neue Skizze erstellen, enthält sie bereits zwei Kommentare. Entfernen wir diese, hat dies keinen Einfluss auf die Funktionsweise der Skizze.

.. code-block:: arduino
    :emphasize-lines: 2,7

    void setup() {
        // Setze hier deinen Initialisierungscode ein, der einmal ausgeführt wird:

    }

    void loop() {
        // Setze hier deinen Hauptcode ein, der ständig wiederholt wird:

    }

Kommentare sind in der Programmierung sehr nützlich, und einige gängige Anwendungsbeispiele sind nachfolgend aufgelistet.

* Anwendungsfall A: Erkläre dir oder anderen, was dieser Codeabschnitt macht.

.. code-block:: arduino

    void setup() {
        pinMode(13, OUTPUT); // Setze Pin 13 in den Ausgabemodus, er steuert die onboard LED
    }

    void loop() {
        digitalWrite(13, HIGH); // Aktiviere die onboard LED durch Setzen von Pin 13 auf HIGH
        delay(500); // Halte den Status für 500 ms
        digitalWrite(13, LOW); // Schalte die onboard LED aus
        delay(500); // Halte den Status für 500 ms
    }

* Anwendungsfall B: Temporäres Deaktivieren von Anweisungen (ohne sie zu löschen), um sie bei Bedarf wieder zu aktivieren, ohne sie neu schreiben zu müssen. Dies ist beim Debuggen von Code und bei der Fehlersuche sehr hilfreich.

.. code-block:: arduino
    :emphasize-lines: 3,4,5,6

    void setup() {
        pinMode(13, OUTPUT);
        // digitalWrite(13, HIGH);
        // delay(1000);
        // digitalWrite(13, LOW);
        // delay(1000);
    }

    void loop() {
        digitalWrite(13, HIGH);
        delay(200);
        digitalWrite(13, LOW);
        delay(200);
    }    

.. note:: 
    Verwenden Sie die Tastenkombination ``Strg+/``, um Ihren Code schnell zu kommentieren oder zu dekommentieren.

Kommentar ``/**/``
------------------

Gleichwertig zu ``//`` für Kommentare. Diese Art von Kommentar kann über mehrere Zeilen gehen. Sobald der Compiler ``/*`` liest, ignoriert er alles, was darauf folgt, bis er ``*/`` trifft.



Example 1:

.. code-block:: arduino
    :emphasize-lines: 1,8,9,10,11

    /* Blink */

    void setup() {
        pinMode(13,OUTPUT); 
    }

    void loop() {
        /*
        The following code will blink the onboard LED
        You can modify the number in delay() to change the blinking frequency
        */
        digitalWrite(13,HIGH); 
        delay(500); 
        digitalWrite(13,LOW); 
        delay(500);
    }


``#define``
--------------

Dies ist ein nützliches Werkzeug in C++.

.. code-block:: arduino

    #define identifier Token-String

Der Compiler ersetzt beim Lesen automatisch den ``identifier`` durch den ``Token-String``, was meist zur Definition von Konstanten verwendet wird.

Hier ein Beispiel für eine Skizze, die `#define` verwendet, um die Lesbarkeit des Codes zu erhöhen.

.. code-block:: arduino
    :emphasize-lines: 1,2

    #define ONBOARD_LED 13
    #define VERZOEGERUNGSZEIT 500

    void setup() {
        pinMode(ONBOARD_LED, OUTPUT); 
    }

    void loop() {
        digitalWrite(ONBOARD_LED, HIGH); 
        delay(VERZOEGERUNGSZEIT); 
        digitalWrite(ONBOARD_LED, LOW); 
        delay(VERZOEGERUNGSZEIT);
    }

Aus Sicht des Compilers sieht der Code eigentlich so aus:

.. code-block:: arduino

    void setup() {
        pinMode(13, OUTPUT); 
    }

    void loop() {
        digitalWrite(13, HIGH); 
        delay(500); 
        digitalWrite(13, LOW); 
        delay(500);
    }

Wie man sehen kann, wird der ``Bezeichner`` ersetzt und existiert nicht im Programm. Daher gibt es einige Vorsichtsmaßnahmen bei der Verwendung.

1. Ein ``Token-String`` kann nur manuell geändert und nicht durch Rechenoperationen im Programm in andere Werte umgewandelt werden.

2. Vermeiden Sie die Verwendung von Symbolen wie ``;``. Zum Beispiel:

.. code-block:: arduino
    :emphasize-lines: 1

    #define ONBOARD_LED 13;

    void setup() {
        pinMode(ONBOARD_LED, OUTPUT); 
    }

    void loop() {
        digitalWrite(ONBOARD_LED, HIGH); 
    }

Der Compiler wird es wie folgt interpretieren, was zu einem Fehler führen wird:

.. code-block:: arduino
    :emphasize-lines: 2,6

    void setup() {
        pinMode(13;, OUTPUT); 
    }

    void loop() {
        digitalWrite(13;, HIGH); 
    }

.. note:: 
    Eine Namenskonvention für ``#define`` ist es, den ``identifier`` zu groß zu schreiben, um Verwechslungen mit Variablen zu vermeiden.
