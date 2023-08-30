.. _cpn_VL53L0X:

飛行時間（ToF）マイクロLiDAR距離センサ（VL53L0X）
===============================================================

.. image:: img/20_VL53L0X_module.png
    :width: 350
    :align: center

概要
---------------------------

VL53L0Xモジュールは、レーザー技術を用いて最大2メートルまでの距離を精度よく測定できる飛行時間（ToF）測距センサです。このモジュールは、統合されたレーザー発生器、検出器、マイクロコントローラを搭載した多機能センサモジュールです。プルアップ抵抗やコンデンサなど、必要なコンポーネントがすべて搭載されています。対応可能な測定距離は約50〜1200mmです。

原理
---------------------------
VL53L0Xモジュールは、飛行時間（ToF）原理に基づいて動作します。レーザーパルスを送出し、反射して戻ってくるまでの時間を測定します。この時間は、センサと物体との距離に比例します。モジュールは単一光子雪崩ダイオード（SPAD）アレイを用いて、物体から反射された光を検出します。SPADアレイは、一つの光子さえも検出する能力があります。さらに、このモジュールにはデータ処理を行う統合マイクロコントローラが搭載されています。

使い方
---------------------------

**使用する電子部品**

- Arduino Uno R4またはR3ボード * 1
- 飛行時間マイクロLiDAR距離センサ * 1
- ジャンパーワイヤー


**回路組み立て**

.. image:: img/20_VL53L0X_module_circuit.png
    :width: 550
    :align: center

.. raw:: html
    
    <br/><br/>   

コード
^^^^^^^^^^^^^^^^^^^^

.. note:: 
   ライブラリのインストールには、Arduinoライブラリマネージャで **「Adafruit_VL53L0X」** を検索してインストールします。

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/d1f540b1-8a29-40cd-ba12-84c34f0ab4a3/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/20-component_VL53L0X.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>
   <br/><br/>  

コードの説明
^^^^^^^^^^^^^^^^^^^^

#. 必要なライブラリを含むとセンサオブジェクトを初期化。最初に、VL53L0Xセンサ用のライブラリを含み、Adafruit_VL53L0Xクラスのインスタンスを作成します。

   .. note:: 
      ライブラリのインストールには、Arduinoライブラリマネージャで **「Adafruit_VL53L0X」** を検索してインストールします。

   .. code-block:: arduino

      #include <Adafruit_VL53L0X.h>
      Adafruit_VL53L0X lox = Adafruit_VL53L0X();

#. ``setup()`` 関数での初期化。ここでは、シリアル通信を設定し、距離センサを初期化します。センサの初期化ができない場合、プログラムは停止します。

   .. code-block:: arduino

      void setup() {
        Serial.begin(115200);
        while (!Serial) {
          delay(1);
        }
        Serial.println("Adafruit VL53L0X test");
        if (!lox.begin()) {
          Serial.println(F("Failed to boot VL53L0X"));
          while (1)
            ;
        }
        Serial.println(F("VL53L0X API Simple Ranging example\n\n"));
      }

#. ``loop()`` 関数での測定値の取得と表示。Arduinoは、 ``rangingTest()`` メソッドを使用して、距離の測定を継続的に行います。測定が有効な場合、その値がシリアルモニタに表示されます。

   .. code-block:: arduino
       
      void loop() {
        VL53L0X_RangingMeasurementData_t measure;
        Serial.print("Reading a measurement... ");
        lox.rangingTest(&measure, false);
        if (measure.RangeStatus != 4) {
          Serial.print("Distance (mm): ");
          Serial.println(measure.RangeMilliMeter);
        } else {
          Serial.println(" out of range ");
        }
        delay(100);
      }

追加のアイディア
^^^^^^^^^^^^^^^^^^^^

- センサをディスプレイ（例：OLED）と連携させて、距離測定値を表示する。
- 物体が特定の範囲内に入ったときに、他のコンポーネント（LEDやブザーなど）を作動させる。

さらなるプロジェクト
---------------------------
* :ref:`fun_tof_distance_monitor`
