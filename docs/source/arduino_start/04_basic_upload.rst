So laden Sie eine Skizze auf das Board hoch
===========================================

In diesem Abschnitt erfahren Sie, wie Sie die zuvor erstellte Skizze auf das Arduino-Board hochladen und auf was Sie achten sollten.

**1. Wählen Sie Board und Port aus**

Arduino-Entwicklungsboards werden in der Regel mit einem USB-Kabel geliefert. Verbinden Sie das Board damit mit Ihrem Computer.

Wählen Sie im Arduino IDE das korrekte **Board** und den korrekten **Port** aus. Normalerweise erkennen Computer Arduino-Boards automatisch und weisen ihnen einen Port zu, den Sie hier auswählen können.

    .. image:: img/board_port.png
        :width: 90%

Sollte Ihr Board bereits angeschlossen, aber nicht erkannt sein, überprüfen Sie, ob das **installiert**-Logo im Abschnitt **Arduino AVR Boards** des **Board-Verwaltung** erscheint. Falls nicht, scrollen Sie ein wenig nach unten und klicken auf **Installieren**.

    .. image:: img/upload1.png
        :width: 90%

Speziell für UNO R4, suchen Sie im **Board-Verwaltung** nach **"UNO R4"** und prüfen, ob die zugehörige Bibliothek installiert ist.

    .. image:: img/install_uno_r4_lib.png
        :width: 90%

Ein Neustart der Arduino IDE und das erneute Anschließen des Arduino-Boards beheben die meisten Probleme. Alternativ können Sie auch **Werkzeuge** -> **Board** oder **Port** anklicken, um sie auszuwählen.

**2. Überprüfen Sie die Skizze**

Nachdem Sie auf die Schaltfläche Überprüfen geklickt haben, wird die Skizze kompiliert, um mögliche Fehler zu identifizieren.

    .. image:: img/sp221014_174532.png
        :width: 90%

Sie können damit Fehler finden, falls Sie Zeichen gelöscht oder Buchstaben versehentlich eingetippt haben. Anhand der Nachrichtenzeile sehen Sie, wo und welche Art von Fehlern aufgetreten sind.

    .. image:: img/sp221014_175307.png
        :width: 90%

Wenn keine Fehler vorliegen, wird eine Meldung wie die folgende angezeigt.

    .. image:: img/sp221014_175512.png
        :width: 90%

**3. Skizze hochladen**

Nach Abschluss der oben genannten Schritte klicken Sie auf die Schaltfläche **Hochladen**, um die Skizze auf das Board zu übertragen.

    .. image:: img/sp221014_175614.png
        :width: 90%

Bei Erfolg erscheint die folgende Aufforderung.

    .. image:: img/sp221014_175654.png
        :width: 90%

Gleichzeitig blinkt die LED auf dem Board.

.. image:: img/1_led.jpg
    :width: 400
    :align: center

.. raw:: html
    
    <br/>

Das Arduino-Board führt die Skizze automatisch aus, sobald die Stromversorgung nach dem Hochladen der Skizze hergestellt ist. Das laufende Programm kann durch Hochladen einer neuen Skizze überschrieben werden.

