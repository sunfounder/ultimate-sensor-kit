.. _cpn_joystick:

ジョイスティックモジュール
==========================

.. image:: img/19_joystick.png
    :width: 400
    :align: center

概要
---------------------------
ジョイスティックモジュールは、ノブの動きを水平（X軸）および垂直（Y軸）の二方向で測定する装置です。ゲームやロボット、カメラなど、多種多様なアプリケーションでの操作に使用できます。

原理
---------------------------
ジョイスティックは、通常10キロオームの2つのポテンショメータに基づいて動作します。X軸とY軸の方向で抵抗が変わると、Arduinoはこれをx座標とy座標として解釈するための異なる電圧を受け取ります。プロセッサには、ジョイスティックのアナログ値をデジタル値に変換し、必要な処理を行うためのADCユニットが必要です。

Arduinoボードには10ビットのADCチャネルが6つあります。Arduinoの基準電圧（5V）が1024セグメントに分かれます。ジョイスティックがx軸に沿って動くと、ADCの値は0から1023まで上がり、値512が中央になります。以下の画像は、ジョイスティックの位置に基づいたADCのおおよその値を示しています。

.. image:: img/19_joystick_xy.png
    :width: 400
    :align: center

使い方
---------------------------

**使用する電子部品**

- Arduino Uno R4またはR3ボード * 1
- ジョイスティックモジュール * 1
- ジャンパーワイヤー

**回路組み立て**

.. image:: img/19_joystick_module_circuit.png
    :width: 600
    :align: center

.. raw:: html
    
    <br/><br/>   

コード
^^^^^^^^^^^^^^^^^^^^

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/3233bdfb-21b1-4358-a8cb-a0b2badeb173/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/19-component_joystick.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>
   <br/><br/>  

コードの説明
^^^^^^^^^^^^^^^^^^^^

#. ジョイスティックのピン設定。ここでは、ジョイスティックのX軸とY軸が接続されているアナログピンを定義します。

   .. code-block:: arduino

      const int xPin = A0;
      const int yPin = A1;

#. ``setup()`` 関数内での初期化。このセクションでは、シリアル通信を設定し、Arduinoとシリアルモニター間でメッセージの送受信を可能にします。

   .. code-block:: arduino

      void setup() {
        Serial.begin(9600);
      }

#. ``loop()`` 関数内でのジョイスティック値の読み取り。Arduinoは継続的にジョイスティックからX値とY値を読み取り、それらをシリアルモニターに出力します。各出力の後に短い遅延があり、これにより読み取りがより読みやすく、シリアルモニターが圧倒されないようにしています。

   .. code-block:: arduino
       
      void loop() {
        Serial.print("X: ");
        Serial.print(analogRead(xPin));
        Serial.print(" | Y: ");
        Serial.println(analogRead(yPin));
        delay(50);
      }

さらに多くのプロジェクト
^^^^^^^^^^^^^^^^^^^^^^^

- ジョイスティックの値を用いてサーボモーターを制御し、ジョイスティックの動きに応じて動かします。

