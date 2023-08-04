.. _cpn_bmp280:

Temperature, Humidity & Pressure Sensor (BMP280)
==========================

.. image:: img/14_gy_bme280_3.3_module.png
    :width: 300
    :align: center

Introduction
---------------------------
A GY-BMP280-3.3 high precision atmospheric pressure sensor module is a device that can measure the air pressure and temperature with high accuracy. It can help you monitor the weather conditions and create projects that use altitude or barometric pressure data.

Principle
---------------------------
A GY-BMP280-3.3 high precision atmospheric pressure sensor module works by using a BMP280 sensor from Bosch that can measure both pressure and temperature. The BMP280 sensor has a piezoresistive pressure sensor and a thermistor inside a sealed metal chamber. The piezoresistive sensor changes its resistance according to the pressure applied to the chamber. The thermistor changes its resistance according to the temperature inside the chamber. The module has an integrated circuit that converts the resistance values into digital signals and sends them to the Arduino through either I2C or SPI interface. 


Usage
---------------------------

**Hardware components**

- Arduino Uno R4 or R3 board * 1
- Temperature, Humidity & Pressure Sensor(GY-BMP280-3.3) * 1
- Jumper Wires


**Circuit Assembly**

.. image:: img/14_gy_bme280_3.3_module_circuit.png
    :width: 550
    :align: center

.. raw:: html
    
    <br/><br/>   

Code
^^^^^^^^^^^^^^^^^^^^

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/e1f581e4-76c8-48a0-b1cc-d15604267183/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/14-component_bmp280.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>
   <br/><br/>  

Code explanation
^^^^^^^^^^^^^^^^^^^^

1. Including Libraries and Initialization. Necessary libraries are included and the BMP280 sensor is initialized for communication using the I2C interface.

   .. note:: 
      To install, use the Arduino Library Manager and search for **"Adafruit BMP280"** and install the library. 

   - Adafruit BMP280 Library: This library provides an easy-to-use interface for the BMP280 sensor, allowing the user to read temperature, pressure, and altitude. 
   - Wire.h: Used for I2C communication.

   .. raw:: html
    
    <br/>

   .. code-block:: arduino
    
      #include <Wire.h>
      #include <Adafruit_BMP280.h>
      #define BMP280_ADDRESS 0x76
      Adafruit_BMP280 bmp;  // use I2C interface


2. The ``setup()`` function initializes the Serial communication, checks for the BMP280 sensor, and sets up the sensor with default settings.

   .. code-block:: arduino

      void setup() {
        Serial.begin(9600);
        while (!Serial) delay(100);
        Serial.println(F("BMP280 test"));
        unsigned status;
        status = bmp.begin(BMP280_ADDRESS);
        // ... (rest of the setup code)

3. The ``loop()`` function reads data from the BMP280 sensor for temperature, pressure, and altitude. This data is printed to the Serial Monitor.

   .. code-block:: arduino

      void loop() {
        // ... (read and print temperature, pressure, and altitude data)
        delay(2000);  // 2-second delay between readings.
      }


Additional Ideas
^^^^^^^^^^^^^^^^^^^^

- Integrate an LCD display module to show the readings instead of or in addition to the Serial Monitor.
- Set threshold values for temperature and pressure. Use a buzzer or LED to alert when these thresholds are exceeded.

More Projects
---------------------------
* :ref:`iot_Weather_monitor`
