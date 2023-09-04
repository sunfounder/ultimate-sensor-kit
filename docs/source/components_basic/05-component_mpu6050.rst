.. _cpn_mpu6050:

Beschleunigungssensor & Gyroskop-Modul (MPU6050)
===============================================================

.. image:: img/05_mpu6050_1.png
    :width: 300
    :align: center

Einleitung
---------------------------
Der MPU-6050 ist ein 6-achsiger Bewegungssensor, der einen 3-achsigen Gyroskop und einen 3-achsigen Beschleunigungsmesser kombiniert. Er erfasst Veränderungen in Bewegung, Beschleunigung und Rotation. Häufig findet er Einsatz in Robotik, Game-Controllern und anderen elektronischen Geräten, die eine Bewegungserkennung benötigen. Aufgrund seiner hohen Genauigkeit und geringen Kosten ist er besonders bei der DIY-Community beliebt.

Funktionsprinzip
---------------------------
Ein MPU-6050 Sensor-Modul besteht aus einem 3-achsigen Beschleunigungsmesser und einem 3-achsigen Gyroskop.

Die drei Koordinatensysteme sind wie folgt definiert:

Legen Sie den MPU6050 flach auf den Tisch, sodass das Etikett nach oben zeigt und ein Punkt auf dieser Oberfläche in der oberen linken Ecke ist. Dann ist die aufrechte Richtung nach oben die Z-Achse des Chips. Die Richtung von links nach rechts wird als X-Achse betrachtet. Entsprechend ist die Richtung von hinten nach vorne als Y-Achse definiert.

.. image:: img/05_mpu_2.png
    :width: 300
    :align: center

3-achsiger Beschleunigungsmesser
^^^^^^^^^^^^^^^^^^^^
Der Beschleunigungsmesser funktioniert nach dem Prinzip des piezoelektrischen Effekts, der es bestimmten Materialien ermöglicht, bei mechanischer Belastung eine elektrische Ladung zu erzeugen.

Stellen Sie sich eine quaderförmige Box mit einer kleinen Kugel darin vor, wie im obigen Bild. Die Wände dieser Box bestehen aus piezoelektrischen Kristallen. Wenn Sie die Box neigen, bewegt sich die Kugel aufgrund der Schwerkraft in Richtung der Neigung. Die Wand, gegen die die Kugel stößt, erzeugt kleine piezoelektrische Ströme. Insgesamt gibt es drei gegenüberliegende Wandpaare in einem Quader, die jeweils einer Achse im 3D-Raum entsprechen: den X-, Y- und Z-Achsen. Abhängig von den Strömen, die von den piezoelektrischen Wänden erzeugt werden, können wir die Richtung und das Ausmaß der Neigung bestimmen.

.. image:: img/05_mpu_3.png
    :width: 800
    :align: center

Der MPU6050 kann zur Erfassung der Beschleunigung auf jeder Koordinatenachse verwendet werden (im stationären Zustand ist die Beschleunigung der Z-Achse 1 Gravitationseinheit, X und Y sind 0). Bei Neigung oder in einem zustandslosen/überlasteten Zustand ändert sich der entsprechende Wert.

Es gibt vier wählbare Messbereiche: +/-2g, +/-4g, +/-8g und +/-16g (standardmäßig 2g), die jeweils einer Präzision entsprechen. Die Werte reichen von -32768 bis 32767.

Die Beschleunigungsablesung wird durch Abbildung des Messbereichs auf den Lesebereich in einen Beschleunigungswert umgewandelt.

Beschleunigung = (Rohdaten der Beschleunigungsachsen / 65536 * voller Beschleunigungsbereich) g

Nehmen Sie die X-Achse als Beispiel, wenn die Rohdaten der Beschleunigungs-X-Achse 16384 betragen und der Bereich +/- 2g ausgewählt ist:

Beschleunigung entlang der X-Achse = (16384 / 65536 * 4) g = 1g

3-achsiger Gyroskop
^^^^^^^^^^^^^^^^^^^^
Gyroskope funktionieren nach dem Prinzip der Coriolis-Beschleunigung. Stellen Sie sich eine gabelähnliche Struktur vor, die sich ständig hin und her bewegt und durch piezoelektrische Kristalle an Ort und Stelle gehalten wird. Wenn Sie versuchen, diese Anordnung zu neigen, erfahren die Kristalle eine Kraft in Richtung der Neigung. Dies entsteht aufgrund der Trägheit der beweglichen Gabel. Die Kristalle erzeugen daraufhin einen Strom gemäß dem piezoelektrischen Effekt, der dann verstärkt wird.

.. image:: img/05_mpu_4.png
    :width: 800
    :align: center

Auch der Gyroskop hat vier Arten von Messbereichen: +/- 250, +/- 500, +/- 1000, +/- 2000. Die Berechnungsmethode und die Beschleunigung sind im Grunde konsistent.

Die Formel zur Umwandlung der Ablesung in die Winkelgeschwindigkeit lautet wie folgt:

Winkelgeschwindigkeit = (Rohdaten der Gyroskopachsen / 65536 * voller Gyroskopbereich) °/s

Nehmen Sie als Beispiel die X-Achse, wenn die Rohdaten der Beschleunigungs-X-Achse 16384 betragen und der Bereich + / - 250 ° / s beträgt:

Winkelgeschwindigkeit entlang der X-Achse = (16384 / 65536 * 500)°/s = 125°/s



Anwendungsbeispiele
---------------------------

**Benötigte Hardware-Komponenten**

- Arduino Uno R4 oder R3 Board * 1
- Beschleunigungssensor & Gyroskop Modul (MPU6050) * 1
- Jumperkabel

**Schaltkreismontage**

.. image:: img/05_mpu6050_circuit.png
    :width: 400
    :align: center

.. raw:: html
    
    <br/><br/>   

Programmcode
^^^^^^^^^^^^^^^^^^^^

.. note::
      Um die Bibliothek zu installieren, nutzen Sie den Arduino Bibliotheksmanager und suchen nach **"Adafruit MPU6050"**, um sie zu installieren.

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/e5160412-ce6c-4742-a0f3-0aa259bb9770/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/05-component_mpu6050.mp4"  type="video/mp4">
      Ihr Browser unterstützt das Video-Tag nicht.
   </video>
   <br/><br/>  

Code-Erklärung
^^^^^^^^^^^^^^^^^^^^

1. Der Code beginnt mit dem Einbinden der erforderlichen Bibliotheken und der Erstellung eines Objekts für den MPU6050-Sensor. Dieser Code verwendet die Adafruit_MPU6050-Bibliothek, die Adafruit_Sensor-Bibliothek und die Wire-Bibliothek. Die ``Adafruit_MPU6050``-Bibliothek dient der Kommunikation mit dem MPU6050-Sensor und der Abfrage von Beschleunigungs-, Rotations- und Temperaturdaten. Die ``Adafruit_Sensor``-Bibliothek bietet eine allgemeine Schnittstelle für verschiedene Sensortypen. Die ``Wire``-Bibliothek wird für die I2C-Kommunikation verwendet, die für die Kommunikation mit dem MPU6050-Sensor erforderlich ist.

   .. note::
       Um die Bibliothek zu installieren, nutzen Sie den Arduino Bibliotheksmanager und suchen nach **"Adafruit MPU6050"**, um sie zu installieren.

   .. code-block:: arduino
   
      #include <Adafruit_MPU6050.h>
      #include <Adafruit_Sensor.h>
      #include <Wire.h>
      Adafruit_MPU6050 mpu;
   
2. Die ``setup()``-Funktion initialisiert die serielle Kommunikation und prüft, ob der Sensor erkannt wird. Wenn der Sensor nicht gefunden wird, tritt das Arduino in eine Endlosschleife mit der Meldung "MPU6050-Chip nicht gefunden" ein. Wird er gefunden, werden der Beschleunigungsbereich, der Gyrobereich und die Filterbandbreite eingestellt, und eine Verzögerung wird für die Stabilität hinzugefügt.

   .. code-block:: arduino

      void setup(void) {
        // Initialize the serial communication
        Serial.begin(9600);
   
        // Check if the MPU6050 sensor is detected
        if (!mpu.begin()) {
          Serial.println("Failed to find MPU6050 chip");
          while (1) {
            delay(10);
          }
        }
        Serial.println("MPU6050 Found!");
   
        // set accelerometer range to +-8G
        mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
   
        // set gyro range to +- 500 deg/s
        mpu.setGyroRange(MPU6050_RANGE_500_DEG);
   
        // set filter bandwidth to 21 Hz
        mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
   
        // Add a delay for stability
        delay(100);
      }

3. In der ``loop()``-Funktion erstellt das Programm Events, um die Sensormesswerte zu speichern, und ruft dann diese Messwerte ab. Die Werte für Beschleunigung, Rotation und Temperatur werden dann auf dem seriellen Monitor ausgegeben.

   .. code-block:: arduino
   
      void loop() {
        // Get new sensor events with the readings
        sensors_event_t a, g, temp;
        mpu.getEvent(&a, &g, &temp);
   
        // Print out the acceleration, rotation, and temperature readings
        // ...
   
        // Add a delay to avoid flooding the serial monitor
        delay(1000);
      }

Weitere Ideen
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- Visualisiere Sensordaten in grafischer Form auf einem LCD oder OLED
