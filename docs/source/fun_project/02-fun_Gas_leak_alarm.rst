.. _fun_gas_leak_alarm:

Gasleck-Alarm
==========================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/fun/02-fun_Gas_leak_alarm.mp4"  type="video/mp4">
      Ihr Browser unterstützt das Video-Tag nicht.
   </video>

Dieses Projekt dreht sich um die Simulation eines Gaslecks mittels eines Arduino Uno Boards. Durch die Integration eines MQ-2 Gassensors und einer RGB-LED erfasst die Demonstration fortlaufend die Gaskonzentration. Überschreitet diese einen voreingestellten Grenzwert, wird ein Alarm (Summer) ausgelöst und die RGB-LED leuchtet rot auf. Bleibt die Konzentration unter dem Grenzwert, bleibt der Alarm inaktiv und die LED zeigt Grün. Es ist wichtig zu betonen, dass diese Demonstration rein illustrativ ist und echte Gasleck-Detektionssysteme nicht ersetzen sollte.

1. Schaltungsaufbau
-----------------------------

.. image:: img/02-fun_Gas_leak_alarm_circuit.png
    :width: 90%

* :ref:`cpn_uno`
* :ref:`cpn_gas`
* :ref:`cpn_rgb`
* :ref:`cpn_buzzer`

2. Code
-----------------------------

#. Öffnen Sie die Datei ``02-Gas_leak_alarm.ino`` im Verzeichnis ``ultimate-sensor-kit\fun_project\02-Gas_leak_alarm`` oder kopieren Sie den Code in die **Arduino IDE**.

   .. raw:: html
       
       <iframe src=https://create.arduino.cc/editor/sunfounder01/a8ac24b4-bbab-4d9d-b0ed-a890b764d52d/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


3. Code-Erklärung
-----------------------------

Das Kernprinzip des Projekts besteht darin, kontinuierlich die Gaskonzentration zu überwachen. Wenn die gemessene Konzentration einen bestimmten Schwellenwert überschreitet, wird der Alarm ausgelöst und die LED wechselt zu Rot. Dies dient als simulierter Warnmechanismus für potenziell gefährliche Zustände. Fällt die Konzentration unter den Schwellenwert, wird der Alarm deaktiviert und die LED wechselt zu Grün, was auf eine sichere Umgebung hinweist.

1. Konstanten und Variablen definieren

   Diese Zeilen deklarieren und initialisieren die Pinnummern für verschiedene Komponenten. Der ``sensorPin`` gibt den analogen Pin an, an dem der MQ-2-Gassensor angeschlossen ist. ``sensorValue`` ist eine Ganzzahl, die den analogen Ausgang des Sensors speichert. Der ``buzzerPin`` kennzeichnet den digitalen Pin für den Summer. Schließlich sind ``RPin`` und ``GPin`` die Pins für die roten und grünen Kanäle der RGB-LED.

   .. code-block:: arduino
   
      // Define the pin numbers for the Gas Sensor
      const int sensorPin = A0;
      int sensorValue;
   
      // Define the pin number for the buzzer
      const int buzzerPin = 9;
   
      // Define pin numbers for the RGB LED
      const int RPin = 5;  // R channel of RGB LED
      const int GPin = 6;  // G channel of RGB LED
   
2. Initialisierung in ``setup()``

   Die Funktion ``setup()`` initialisiert die benötigten Einstellungen. Die serielle Kommunikation beginnt mit einer Baudrate von 9600, was die Anzeige der Sensorwerte im Serial Monitor ermöglicht. Die Pins für Summer und RGB-LED werden als ``OUTPUT`` festgelegt, um Signale an externe Komponenten zu senden.

   .. code-block:: arduino
   
      void setup() {
        Serial.begin(9600);  // Start serial communication at 9600 baud rate
   
        // Initialize the buzzer and RGB LED pins as output
        pinMode(buzzerPin, OUTPUT);
        pinMode(RPin, OUTPUT);
        pinMode(GPin, OUTPUT);
      }
   
3. Hauptprogrammschleife: Sensorauslesen und Alarm auslösen

   Die Funktion ``loop()`` liest kontinuierlich den Ausgang des Gassensors aus. Der Wert wird dann im Serial Monitor zur Beobachtung angezeigt. Je nach Sensorwert können zwei Szenarien eintreten:
   
   - Überschreitet der Wert 300, wird der Summer mittels ``tone()`` aktiviert und die RGB-LED leuchtet rot.
   - Liegt der Wert unter 300, wird der Summer mit ``noTone()`` stummgeschaltet und die LED leuchtet grün.
   
   Zuletzt wird eine Verzögerung von 50 Millisekunden eingeführt, bevor die nächste Iteration der Schleife beginnt, um die Auslesefrequenz zu regulieren und die CPU-Last zu verringern.

   .. code-block:: arduino
   
      void loop() {
        // Read the analog value of the gas sensor
        sensorValue = analogRead(sensorPin);
   
        // Print the sensor value to the serial monitor
        Serial.print("Analog output: ");
        Serial.println(sensorValue);
   
        // If the sensor value exceeds the threshold, trigger the alarm and make the RGB LED red
        if (sensorValue > 300) {
          tone(buzzerPin, 500, 300);
          digitalWrite(GPin, LOW);
          digitalWrite(RPin, HIGH);
        } else {
          // If the sensor value is below the threshold, turn off the alarm and make the RGB LED green
          noTone(buzzerPin);
          digitalWrite(RPin, LOW);
          digitalWrite(GPin, HIGH);
        }
   
        // Wait for 50 milliseconds before the next loop iteration
        delay(50);
      }
   
