.. note::

    こんにちは、SunFounderのRaspberry Pi & Arduino & ESP32愛好家コミュニティへようこそ！Facebook上でRaspberry Pi、Arduino、ESP32についてもっと深く掘り下げ、他の愛好家と交流しましょう。

    **参加する理由は？**

    - **エキスパートサポート**：コミュニティやチームの助けを借りて、販売後の問題や技術的な課題を解決します。
    - **学び＆共有**：ヒントやチュートリアルを交換してスキルを向上させましょう。
    - **独占的なプレビュー**：新製品の発表や先行プレビューに早期アクセスしましょう。
    - **特別割引**：最新製品の独占割引をお楽しみください。
    - **祭りのプロモーションとギフト**：ギフトや祝日のプロモーションに参加しましょう。

    👉 私たちと一緒に探索し、創造する準備はできていますか？[|link_sf_facebook|]をクリックして今すぐ参加しましょう！

.. _cpn_traffic:

信号機モジュール
==========================

.. image:: img/23_traffic_light.png
    :width: 400
    :align: center

概要
---------------------------
この信号機モジュールは、実際の信号機と同様に、赤・黄・緑の3色の光を表示する小型デバイスです。交通信号システムの模型を作成したり、ArduinoでLEDを制御する方法を学習するために使用できます。このモジュールの特長は、そのコンパクトなサイズ、簡単な配線、特定の用途に合わせたカスタムインストールが可能である点です。PWMピンに接続してLEDの明るさを制御することもできます。

原理
---------------------------
信号機モジュールは主に2つの方法で制御できます。一つはArduinoからのデジタル入力を使用する単純な方法で、HIGHまたはLOWの信号で対応するLEDを直接点灯または消灯します。もう一つは、特にLEDの明るさを可変にしたい場合に使用されるPWM（パルス幅変調）です。PWMは、デジタル信号のデューティサイクルを変更してLEDの明るさを調整する技術です。デューティサイクルとは、特定の期間に信号がオンになっている割合を示します。例えば、50%のデューティサイクルは、その期間の半分で信号がアクティブで、残りの半分で非アクティブであることを意味します。

使い方
---------------------------

**使用する電子部品**

- Arduino Uno R4またはR3ボード * 1
- 信号機モジュール * 1
- ジャンパーワイヤー


**回路組み立て**

.. image:: img/23_traffic_light_circuit.png
    :width: 600
    :align: center

.. raw:: html
    
    <br/><br/>   

コード
^^^^^^^^^^^^^^^^^^^^

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/fb0a9599-5e59-458c-893b-97551f62aea8/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/23-component_traffic.mp4"  type="video/mp4">
      お使いのブラウザはビデオタグをサポートしていません。
   </video>
   <br/><br/>  

コード説明
^^^^^^^^^^^^^^^^^^^^

1. まず最初に、LEDが接続されているピンに対応する定数を定義します。これにより、コードが読みやすく、修正も容易になります。

  .. code-block:: arduino

     const int rledPin = 9;  //red
     const int yledPin = 8;  //yellow
     const int gledPin = 7;  //green

2. 次に、LEDピンのモードを指定します。すべて ``OUTPUT`` に設定されていますが、これはLEDに電圧を供給する intention です。

  .. code-block:: arduino

     void setup() {
       pinMode(rledPin, OUTPUT);
       pinMode(yledPin, OUTPUT);
       pinMode(gledPin, OUTPUT);
     }

3. ここでは、信号機の動作サイクルのロジックが実装されています。具体的な手順は以下の通りです。

    * 緑のLEDを5秒間点灯。
    * 黄色のLEDを三回点滅（各点滅は0.5秒）。
    * 赤のLEDを5秒間点灯。

  .. code-block:: arduino

     void loop() {
       digitalWrite(gledPin, HIGH);
       delay(5000);
       digitalWrite(gledPin, LOW);
       
       digitalWrite(yledPin, HIGH);
       delay(500);
       digitalWrite(yledPin, LOW);
       delay(500);
       digitalWrite(yledPin, HIGH);
       delay(500);
       digitalWrite(yledPin, LOW);
       delay(500);
       digitalWrite(yledPin, HIGH);
       delay(500);
       digitalWrite(yledPin, LOW);
       delay(500);
       
       digitalWrite(rledPin, HIGH);
       delay(5000);
       digitalWrite(rledPin, LOW);
     }

追加のアイデア
^^^^^^^^^^^^^^^^^^^^

- ブザーを組み込み、緑から赤への切り替わり時に音声で警告を出すことで、視覚障害者の方々にも配慮する。

さらに多くのプロジェクト
---------------------------
* :ref:`fun_touch_toggle_light`
* :ref:`iot_Remote_relay_controller`
* :ref:`iot_Bluetooth_voice_control_relay`
* :ref:`iot_Bluetooth_traffic_light`

