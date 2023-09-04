Variable
========

Eine Variable ist eines der mächtigsten und wichtigsten Werkzeuge in einem Programm. Sie ermöglicht es uns, Daten in unseren Programmen zu speichern und abzurufen.

Das folgende Skizzen-File verwendet Variablen. Es speichert die Pin-Nummern der integrierten LED in der Variable ``ledPin`` und die Zahl "500" in der Variable ``delayTime``.

.. code-block:: arduino
    :emphasize-lines: 1,2

    int ledPin = 13;
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

Ist das eine Wiederholung von dem, was ``#define`` macht? Die Antwort ist NEIN.

* Die Rolle von ``#define`` ist es lediglich, Text einfach und direkt zu ersetzen; es wird vom Compiler nicht als Bestandteil des Programms angesehen.
* Eine ``Variable`` hingegen existiert im Programm und wird zum Speichern und Abrufen von Werten verwendet. Sie kann ihren Wert im Programm auch ändern, was ``#define`` nicht kann.

Im folgenden Skizzen-File addiert sich die Variable selbst, sodass die integrierte LED nach jedem Blinken länger blinkt.

.. code-block:: arduino

    int ledPin = 13;
    int delayTime = 500;

    void setup() {
        pinMode(ledPin,OUTPUT); 
    }

    void loop() {
        digitalWrite(ledPin,HIGH); 
        delay(delayTime); 
        digitalWrite(ledPin,LOW); 
        delay(delayTime);
        delayTime = delayTime + 200; // Jede Ausführung erhöht den Wert um 200
    }

Variable deklarieren
-------------------

Eine Variable zu deklarieren bedeutet, eine Variable zu erstellen.

Für die Deklaration einer Variable benötigen Sie zwei Dinge: den Datentyp und den Variablennamen. Der Datentyp muss vom Variablennamen durch ein Leerzeichen getrennt und die Variablendeklaration durch ein ``;`` beendet werden.

Nehmen wir diese Variable als Beispiel.

.. code-block:: arduino

    int delayTime;

**Datentyp**

Hier ist ``int`` ein Datentyp namens Integer, der zur Speicherung von Ganzzahlen von -32768 bis 32766 verwendet werden kann. Er kann nicht zur Speicherung von Dezimalzahlen verwendet werden.

Neben Ganzzahlen können Variablen auch andere Arten von Daten speichern. Die Arduino-Sprache (die, wie man sich erinnern sollte, C++ ist) bietet eingebaute Unterstützung für einige davon (hier sind nur die am häufigsten verwendeten und nützlichsten aufgelistet):

* ``float``: Speichert eine Dezimalzahl, z.B. 3,1415926.
* ``byte``: Kann Zahlen von 0 bis 255 halten.
* ``boolean``: Nimmt nur zwei mögliche Werte an, ``True`` oder ``False``, obwohl es im Speicher ein Byte belegt.
* ``char``: Speichert eine Zahl von -127 bis 127. Da es als ``char`` markiert ist, versucht der Compiler, es einem Zeichen aus der |link_ascii| zuzuordnen.
* ``string``: Kann eine Zeichenfolge speichern, z.B. ``Halloween``.

**Variablenname**

Sie können der Variable jeden beliebigen Namen geben, z.B. ``i``, ``apple``, ``Bruce``, ``R2D2``, ``Sectumsempra``, aber es gibt einige Grundregeln.

1. Beschreiben Sie den Verwendungszweck. Hier habe ich die Variable delayTime genannt, damit man leicht versteht, wofür sie dient. Wenn ich sie ``barryAllen`` nenne, verwirrt das die Person, die den Code betrachtet.

2. Verwenden Sie eine gängige Benennung. Wie ich es getan habe, können Sie CamelCase verwenden, wobei das T in ``delayTime`` groß geschrieben ist, sodass man leicht erkennen kann, dass die Variable aus zwei Wörtern besteht. Alternativ können Sie UnderScoreCase verwenden, um die Variable als ``delay_time`` zu schreiben. Das beeinflusst nicht die Ausführung des Programms, erleichtert aber dem Programmierer das Lesen des Codes, wenn Sie die von Ihnen bevorzugte Benennung verwenden.

3. Verwenden Sie keine Schlüsselwörter. Ähnlich wie bei der Eingabe von "int" wird die Arduino-IDE es farblich hervorheben, um Sie daran zu erinnern, dass es ein Wort mit einer speziellen Bedeutung ist und nicht als Variablenname verwendet werden kann. Ändern Sie den Namen der Variable, wenn sie farblich hervorgehoben ist.

4. Spezielle Symbole sind nicht erlaubt. Zum Beispiel Leerzeichen, #, $, /, +, % usw. Die Kombination aus englischen Buchstaben (Groß- und Kleinschreibung), Unterstrichen und Zahlen (aber Zahlen können nicht als erstes Zeichen eines Variablennamens verwendet werden) ist ausreichend vielfältig.

**Einen Wert einer Variable zuweisen**

Nachdem wir die Variable deklariert haben, ist es an der Zeit, die Daten zu speichern. Wir verwenden den Zuweisungsoperator (d.h. ``=``), um den Wert in die Variable zu setzen.

Wir können der Variable Werte zuweisen, sobald wir sie deklariert haben.

.. code-block:: arduino

    int delayTime = 500;

Es ist auch möglich, ihr später einen neuen Wert zuzuweisen.

.. code-block:: arduino

    int delayTime; // kein Wert
    delayTime = 500; // Wert ist 500
    delayTime = delayTime + 200; // Wert ist 700
