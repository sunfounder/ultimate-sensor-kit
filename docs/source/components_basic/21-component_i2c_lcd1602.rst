.. _cpn_i2c_lcd1602:

I2C LCD 1602
==========================

.. image:: img/21_i2c_lcd.png
    :width: 600
    :align: center

はじめに
---------------------------
I2C LCD1602は、I2Cプロトコルを用いて16x2（16列と2行）の液晶ディスプレイ（LCD）にテキストやキャラクターを表示するデバイスです。Arduinoプロジェクトからの情報、例えばセンサーの読み取り値、メッセージ、メニューなどを表示するために使用できます。I2Cモジュールには、LCDディスプレイ用のパラレルデータにI2Cシリアルデータを変換するPCF8574 I2Cチップが内蔵されています。        

* |link_PCF8574_Datasheet|



原理
---------------------------
I2C LCD1602は、通常のLCD1602と、その背面に取り付けられたI2Cモジュールで構成されています。このI2Cモジュールは、ArduinoのI/OポートをI2Cプロトコルを使用して拡張するチップです。I2Cプロトコルは、SDA（シリアルデータ）とSCL（シリアルクロック）の2本のワイヤーを使用するシリアル通信プロトコルです。複数のデバイスがこの2本のワイヤーとユニークなアドレスを用いて通信できます。

I2Cモジュールは、Arduinoからの信号をLCDのコマンドに変換します。LCDには、16x2のセルがあり、それぞれのセルは5x8のドットで構成されています。これらのドットは、電圧をかけることでオンまたはオフにできます。LCDは、ドットの異なる組み合わせをオンまたはオフにすることで、さまざまなキャラクターやシンボルを表示できます。

.. image:: img/21_ic2_lcd_2.png
    :width: 500
    :align: center

.. raw:: html
    
    <br/><br/> 

**I2Cアドレス**

基本的にデフォルトアドレスは0x27で、一部の場合には0x3Fになることもあります。

デフォルトアドレスの0x27を例に取ると、A0/A1/A2パッドを短絡することでデバイスアドレスを変更できます。デフォルト状態では、A0/A1/A2は1ですが、パッドが短絡されると、A0/A1/A2は0になります。

.. image:: img/21_i2c_address.jpg
    :width: 600
    :align: center

.. raw:: html
    
    <br/>

**バックライト/コントラスト**

バックライトはジャンパーキャップで有効にでき、キャップを外すとバックライトが無効になります。背面の青いポテンショメーターは、コントラスト（最も明るい白と最も暗い黒との間の明るさの比率）を調整するために使用されます。

.. image:: img/21_back_lcd1602.jpg
    :width: 600
    :align: center

.. raw:: html
    
    <br/> 

* **ジャンパーキャップ**: このキャップによりバックライトを有効にでき、キャップを外すとバックライトが無効になります。
* **ポテンショメーター**: これは、表示されるテキストの鮮明度を調整するために使用されます。時計回りに回すと増加し、反時計回りに回すと減少します。

.. note::
    LCDの配線が完了したら、Arduinoをオンにして、I2Cモジュール上のポテンショメーターを回して、最初の行に四角が表示されるまでコントラストを調整し、LCDが正常に動作することを確認してください。

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/21-component_i2c_lcd1602-2.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>
   <br/><br/>  

使い方
---------------------------

**使用する電子部品**

- Arduino Uno R4またはR3ボード * 1
- I2C LCD1602 * 1
- ジャンパーワイヤー


**回路の組立て**

.. image:: img/21_I2C_lcd_circuit.png
    :width: 100%
    :align: center

.. raw:: html
    
    <br/><br/>  


コード
^^^^^^^^^^^^^^^^^^^^

.. note:: 
   ライブラリをインストールするには、Arduinoライブラリマネージャーで **"LiquidCrystal I2C"** と検索してインストールしてください。

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/b19d0aac-7dbd-460c-9634-31dd1c0310f9/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/21-component_i2c_lcd1602.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>
   <br/><br/>  

コードの説明
^^^^^^^^^^^^^^^^^^^^

1. ライブラリの取り込みとLCDの初期化:

   LiquidCrystal I2Cライブラリがインクルードされ、それに続いてLiquidCrystal_I2Cクラスを使用してLCDオブジェクトが作成されます。この際、I2Cアドレス、列数、行数が指定されます。

   .. note:: 
      ライブラリをインストールするには、Arduinoライブラリマネージャーで **"LiquidCrystal I2C"** と検索してインストールしてください。  

   .. code-block:: arduino

      #include <LiquidCrystal_I2C.h>
      LiquidCrystal_I2C lcd(0x27, 16, 2);

2. ``setup()`` 関数:

   ``setup()`` 関数はArduinoが起動すると一度だけ実行されます。この関数内で、LCDが初期化され、表示がクリアされ、バックライトがオンにされます。その後、LCDに2つのメッセージが表示されます。

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


追加のアイデア
^^^^^^^^^^^^^^^^^^^^

- 温度センサーを組み込み、LCDに現在の室温を表示する。


さらに多くのプロジェクト
---------------------------
* :ref:`fun_potentiometer_scale_value`
* :ref:`iot_Bluetooth_lcd`

