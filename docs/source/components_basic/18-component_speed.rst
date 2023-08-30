.. _cpn_speed:

赤外線速度センサモジュール（LM393）
=====================================

.. image:: img/18_LM393_module.png
    :width: 300
    :align: center

概要
---------------------------
LM393モジュールは、赤外線（IR）トランスミッターと受信機を備えたIRカウンタです。これらのセンサーの間に何らかの障害物が置かれると、マイクロコントローラに信号が送られます。このモジュールは、モーターの速度検出、パルスカウント、位置制限など、マイクロコントローラと連携して使用することができます。

原理
---------------------------
LM393モジュールは、H2010フォトセルを1つ備えています。このフォトセルは、フォトトランジスタと赤外線発光ダイオードが一体になっていて、幅10cmの黒いプラスチックハウジングに収められています。

.. image:: img/18_LM393_module_2.png
    :width: 200
    :align: center

動作時には、赤外線発光ダイオードが連続して赤外線（目に見えない光）を発生させ、この光を受けた場合、感光性トライオードが導通します。

.. image:: img/18_LM393_module_3.png
    :width: 900
    :align: center

使い方
---------------------------

**使用する電子部品**

- Arduino Uno R4 または R3 ボード * 1
- 赤外線速度センサモジュール * 1
- ジャンパーワイヤー

**回路の組み立て**

.. image:: img/18_LM393_module_circuit.png
    :width: 100%
    :align: center

.. raw:: html
    
    <br/><br/>   

コード
^^^^^^^^^^^^^^^^^^^^

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/abcd3502-1ea8-49e5-8254-5652448f06b1/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/18-component_speed.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>
   <br/><br/>  

コードの説明
^^^^^^^^^^^^^^^^^^^^

#. ピンの設定と変数の初期化。ここでは、モーターと速度センサーのピンを定義し、モーターの速度を測定および計算するために使用する変数も初期化します。

   .. code-block:: arduino

      // Define the sensor and motor pins
      const int sensorPin = 11;
      const int motorB_1A = 9;
      const int motorB_2A = 10;
      
      // Define variables for measuring speed
      unsigned long start_time = 0;
      unsigned long end_time = 0;
      int steps = 0;
      float steps_old = 0;
      float temp = 0;
      float rps = 0;

#. ``setup()`` 関数内での初期設定。ここではシリアル通信を設定し、ピンのモードを設定し、初期のモーター速度も設定します。

   .. code-block:: arduino

      void setup() {
        Serial.begin(9600);
        pinMode(sensorPin, INPUT);
        pinMode(motorB_1A, OUTPUT);
        pinMode(motorB_2A, OUTPUT);
        analogWrite(motorB_1A, 160);
        analogWrite(motorB_2A, 0);
      }

#. ``loop()`` 関数内でモーターの速度を測定します。この部分では、1秒間におけるモーターのステップを測定します。それらのステップは、回転数（rps）を計算するために使用され、シリアルモニターに出力されます。

   .. code-block:: arduino

      void loop() {
        start_time = millis();
        end_time = start_time + 1000;
        while (millis() < end_time) {
          if (digitalRead(sensorPin)) {
            steps = steps + 1;
            while (digitalRead(sensorPin))
              ;
          }
        }
        temp = steps - steps_old;
        steps_old = steps;
        rps = (temp / 20);
        Serial.print("rps:");
        Serial.println(rps);
      }

追加のアイデア
^^^^^^^^^^^^^^^^^^^^

- rpsをLCDスクリーンに表示して、よりユーザーフレンドリーなインターフェースを提供する。

