.. _cpn_i2c_lcd1602:

I2C LCD 1602
==========================

.. image:: img/21_i2c_lcd.png
    :width: 600
    :align: center

Introduction
---------------------------
An I2C LCD1602 is a device that can display text and characters on a 16x2 (16 columns and 2 rows) liquid crystal display (LCD) using the I2C protocol. You can use an I2C LCD1602 to show information from your Arduino projects, such as sensor readings, messages, menus, etc. The I2C module has a built-in PCF8574 I2C chip that converts I2C serial data to parallel data for the LCD display.        

* |link_PCF8574_Datasheet|



Principle
---------------------------
An I2C LCD1602 consists of a normal LCD1602 and an I2C module that is attached to the back of the LCD. The I2C module is a chip that can expand the I/O ports of the Arduino using the I2C protocol. The I2C protocol is a serial communication protocol that uses two wires: SDA (serial data) and SCL (serial clock). The I2C protocol allows multiple devices to communicate with each other using only two wires and unique addresses.

The I2C module converts the signals from the Arduino into commands for the LCD. The LCD has 16x2 cells that can display characters or symbols. Each cell consists of 5x8 dots that can be turned on or off by applying voltage. The LCD can display different characters or symbols by turning on or off different combinations of dots.

.. image:: img/21_ic2_lcd_2.png
    :width: 500
    :align: center

.. raw:: html
    
    <br/><br/> 

**I2C Address**

The default address is basically 0x27, in a few cases it may be 0x3F.

Taking the default address of 0x27 as an example, the device address can be modified by shorting the A0/A1/A2 pads; in the default state, A0/A1/A2 is 1, and if the pad is shorted, A0/A1/A2 is 0.

.. image:: img/21_i2c_address.jpg
    :width: 600
    :align: center

.. raw:: html
    
    <br/>

**Backlight/Contrast**

Backlight can be enabled by jumper cap, unplugg the jumper cap to disable the backlight. The blue potentiometer on the back is used to adjust the contrast (the ratio of brightness between the brightest white and the darkest black).

.. image:: img/21_back_lcd1602.jpg
    :width: 600
    :align: center

.. raw:: html
    
    <br/> 

* **Shorting Cap**: Backlight can be enabled by this cap，unplugg this cap to disable the backlight.
* **Potentiometer**: It is used to adjust the contrast (the clarity of the displayed text), which is increased in the clockwise direction and decreased in the counterclockwise direction.

.. note::
    After wiring the LCD, you should turn on the Arduino and adjust the contrast by rotating the potentiometer on the I2C module until the first row of rectangles appear to ensure proper LCD operation.

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/21-component_i2c_lcd1602-2.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>
   <br/><br/>  

Usage
---------------------------

**Hardware components**

- Arduino Uno R4 or R3 board * 1
- I2C LCD1602 * 1
- Jumper Wires


**Circuit Assembly**

.. image:: img/21_I2C_lcd_circuit.png
    :width: 100%
    :align: center

.. raw:: html
    
    <br/><br/>  


Code
^^^^^^^^^^^^^^^^^^^^

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/b19d0aac-7dbd-460c-9634-31dd1c0310f9/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/21-component_i2c_lcd1602.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>
   <br/><br/>  

Code explanation
^^^^^^^^^^^^^^^^^^^^

1. Library Inclusion and LCD Initialization:
   The LiquidCrystal I2C library is included to provide functions and methods for LCD interfacing. Following that, an LCD object is created using the LiquidCrystal_I2C class, specifying the I2C address, number of columns, and number of rows.

   .. note:: 
      To install library, use the Arduino Library Manager and search for **"LiquidCrystal I2C"** and install the library.  

   .. code-block:: arduino

      #include <LiquidCrystal_I2C.h>
      LiquidCrystal_I2C lcd(0x27, 16, 2);

2. Setup Function:
   The ``setup()`` function is executed once when the Arduino starts. In this function, the LCD is initialized, cleared, and the backlight is turned on. Then, two messages are displayed on the LCD.

   .. code-block:: arduino

      void setup() {
        lcd.init();       // initialize the LCD
        lcd.clear();      // clear the LCD display
        lcd.backlight();  // Make sure backlight is on
      
        // Print a message on both lines of the LCD.
        lcd.setCursor(2, 0);  //Set cursor to character 2 on line 0
        lcd.print("Hello world!");
      
        lcd.setCursor(2, 1);  //Move cursor to character 2 on line 1
        lcd.print("LCD Tutorial");
      }


Additional Ideas
^^^^^^^^^^^^^^^^^^^^

- Integrate a temperature sensor and display the current room temperature on the LCD.



