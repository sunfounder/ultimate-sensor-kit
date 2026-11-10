.. note::

    こんにちは、SunFounderのRaspberry Pi & Arduino & ESP32愛好家コミュニティへようこそ！Facebook上でRaspberry Pi、Arduino、ESP32についてもっと深く掘り下げ、他の愛好家と交流しましょう。

    **参加する理由は？**

    - **エキスパートサポート**：コミュニティやチームの助けを借りて、販売後の問題や技術的な課題を解決します。
    - **学び＆共有**：ヒントやチュートリアルを交換してスキルを向上させましょう。
    - **独占的なプレビュー**：新製品の発表や先行プレビューに早期アクセスしましょう。
    - **特別割引**：最新製品の独占割引をお楽しみください。
    - **祭りのプロモーションとギフト**：ギフトや祝日のプロモーションに参加しましょう。

    👉 私たちと一緒に探索し、創造する準備はできていますか？[|link_sf_facebook|]をクリックして今すぐ参加しましょう！

.. _cpn_ir_obstacle:

IR 赤外線障害物回避センサーモジュール
=====================================

.. image:: img/09_IR_obstacle_module.png
    :width: 400
    :align: center

概要
---------------------------
IR障害物センサーは、赤外線反射原理に基づいて障害物を検出します。障害物が存在しない場合、赤外線受信器は信号を受信しません。障害物が前方にあり、赤外線を遮断して反射する場合、赤外線受信器は信号を受信します。

原理
---------------------------
障害物回避センサーは、主に赤外線送信器、赤外線受信器、およびポテンショメータで構成されています。対象物の反射特性により、障害物が存在しない場合、放出された赤外線は距離に応じて減衰し、最終的に消失します。障害物がある場合、赤外線はそれに当たり、赤外線受信器に反射されます。その後、赤外線受信器はこの信号を検出し、前方に障害物があることを確認します。検出範囲は、内蔵されたポテンショメータで調整することができます。

.. image:: img/09_IR_obstacle_module_1.png
    :width: 600
    :align: center

使い方
---------------------------

**使用する電子部品**

- Arduino Uno R4またはR3ボード * 1
- IR 障害物回避センサーモジュール * 1
- ジャンパーワイヤ

**回路組み立て**

.. image:: img/09_IR_obstacle_module_circuit.png
    :width: 400
    :align: center

.. raw:: html
    
    <br/><br/>   

コード
^^^^^^^^^^^^^^^^^^^^

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/f0e8f3a8-c3a8-4ded-a8ec-67de5a4076f6/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/09-component_ir_obstacle.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>
   <br/><br/>  

コードの説明
^^^^^^^^^^^^^^^^^^^^

1. センサー接続用のピン番号を定義:

   .. code-block:: arduino

     const int sensorPin = 2;

   センサーの出力ピンをArduinoの2番ピンに接続します。

2. シリアル通信のセットアップとセンサーピンを入力として定義:

   .. code-block:: arduino

     void setup() {
       pinMode(sensorPin, INPUT);  
       Serial.begin(9600);
     }

   シリアルモニターに出力するため、9600ボーの通信速度でシリアル通信を初期化します。
   センサーピンを入力として設定し、入力信号を読み取ります。

3. センサー値を読み取り、シリアルモニターに出力:

   .. code-block:: arduino

     void loop() {
       Serial.println(digitalRead(sensorPin));
       delay(50); 
     }

   ``digitalRead()`` を用いてセンサーピンからデジタル値を連続して読み取り、 ``Serial.println()`` でシリアルモニターに出力します。
   見やすくするために、出力の間に50msの遅延を挿入します。

.. note::

   センサーが正常に動作していない場合、IR送信機と受信機を平行に調整します。さらに、内蔵されたポテンショメーターを使用して検出範囲を調整できます。

追加のアイデア
^^^^^^^^^^^^^^^^^^^^

- 障害物を検出したときにブザーを鳴らす

その他のプロジェクト
---------------------------
* :ref:`fun_soap_dispenser`
