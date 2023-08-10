.. _fun_potentiometer_scale_value:

Potentiometer scale value
==========================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/fun/10-fun-Potentiometer_scale_value.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>

This project is designed to read the value from a potentiometer and display the read value on an LCD 1620 with an I2C interface. The value is also sent to the serial monitor for real-time viewing. A unique feature of this project is the visual representation of the potentiometer's value on the LCD, displaying a bar that varies in length corresponding to the value.


1. Build the Cirduit
-----------------------------

.. image:: img/10-fun-Potentiometer_scale_value_circuit.png
    :width: 100%

* :ref:`cpn_uno`
* :ref:`cpn_potentiometer`
* :ref:`cpn_i2c_lcd1602`


2. Code
-----------------------------

#. Open the ``10-Potentiometer_scale_value.ino`` file under the path of ``ultimate-sensor-kit\fun_project\10-Potentiometer_scale_value``, or copy this code into **Arduino IDE**.

   .. raw:: html
       
       <iframe src=https://create.arduino.cc/editor/sunfounder01/8adabab1-9d8b-4b84-9007-18f86eda247a/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


3. Code explanation
-----------------------------

The project functions by continually reading the value from a connected potentiometer. This value is then mapped to a smaller scale (0-16) and represented both numerically and visually on the LCD. By checking the difference between consecutive readings, the code ensures that only significant changes are reflected on the display, thereby reducing jitter. Reducing jitter helps avoid undesirable visual effects resulting from frequent refreshing of the LCD screen.

1. **Library Inclusion and Initialization**:

   .. code-block:: arduino
   
      #include <Wire.h>
      #include <LiquidCrystal_I2C.h>
      LiquidCrystal_I2C lcd(0x27, 16, 2);

   Here, the required libraries (``Wire`` for I2C communication and ``LiquidCrystal_I2C`` for the LCD) are included. An LCD object is created with the I2C address ``0x27`` and is defined to have ``16`` columns and ``2`` rows.

2. **Variable Declaration**:

   .. code-block:: arduino
   
      int lastRead = 0;     // Previous potentiometer value
      int currentRead = 0;  // Current potentiometer value

   ``lastRead`` stores the previously read potentiometer value. ``currentRead`` will store the current reading from the potentiometer.

3. **setup() Function**:

   .. code-block:: arduino
   
      void setup() {
        lcd.init();          // Initialize the LCD
        lcd.backlight();     // Turn on the LCD backlight
        Serial.begin(9600);  // Start serial communication at 9600 baud rate
      }

   The LCD is initialized, its backlight is turned on, and serial communication is started at a baud rate of ``9600``.

4. **Main Loop**:

   .. code-block:: arduino
   
      void loop() {
        int currentRead = analogRead(A0);
        int barLength = map(currentRead, 0, 1023, 0, 16);
        if (abs(lastRead - currentRead) > 2) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Value:");
          lcd.setCursor(7, 0);
          lcd.print(currentRead);
          Serial.println(currentRead);
          for (int i = 0; i < barLength; i++) {
            lcd.setCursor(i, 1);
            lcd.print(char(255));
          }
        }
        lastRead = currentRead;
        delay(200);
      }

   * The potentiometer value is read and mapped to a bar length (0-16).
   * If the difference between the last and current reading is more than ``2``, the LCD is updated.
   * The value is printed on the first row and a bar (based on the mapped value) on the second row.
   * The value is also sent to the serial monitor.
   * Before the next iteration, ``lastRead`` is updated, and a delay of ``200ms`` is introduced for stability.
