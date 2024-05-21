.. note::

    こんにちは、SunFounderのRaspberry Pi & Arduino & ESP32愛好家コミュニティへようこそ！Facebook上でRaspberry Pi、Arduino、ESP32についてもっと深く掘り下げ、他の愛好家と交流しましょう。

    **参加する理由は？**

    - **エキスパートサポート**：コミュニティやチームの助けを借りて、販売後の問題や技術的な課題を解決します。
    - **学び＆共有**：ヒントやチュートリアルを交換してスキルを向上させましょう。
    - **独占的なプレビュー**：新製品の発表や先行プレビューに早期アクセスしましょう。
    - **特別割引**：最新製品の独占割引をお楽しみください。
    - **祭りのプロモーションとギフト**：ギフトや祝日のプロモーションに参加しましょう。

    👉 私たちと一緒に探索し、創造する準備はできていますか？[|link_sf_facebook|]をクリックして今すぐ参加しましょう！

.. _cpn_rgb:

RGB モジュール
==========================

.. image:: img/24_rgb_module.png
    :width: 350
    :align: center

概要
---------------------------
このRGBフルカラーLEDモジュールは、赤、緑、青の光を混合することで多彩な色を発生させます。各色はPWM（パルス幅変調）を使用して調整されます。このモジュールは、カラフルな照明効果を作成したり、ArduinoでPWMを使用する方法を学ぶためにも利用できます。

原理
---------------------------
RGBモジュールは、可変PWM電圧入力付きのR、G、Bピンを使って全色LEDを制御します。  
LEDからの色は組み合わせることができ、例えば青と緑を混合するとシアンに、赤と緑を混合すると黄色になります。これを「加法混色法」と呼びます。

* `加法混色 - Wikipedia <https://ja.wikipedia.org/wiki/加法混色>`_

.. image:: img/24_rgb_module_2.png
    :width: 200
    :align: center

この方法に基づいて、三原色をさまざまな比率で混合することで、任意の可視光の色を生成することができます。例えば、赤を多くして緑を少なくすると、オレンジ色が生じます。
PWMはデューティサイクルを変更することで、LEDの明るさを調整する技術です。

使い方
---------------------------

**使用する電子部品**

- Arduino Uno R4またはR3ボード * 1
- RGB モジュール * 1
- ジャンパーワイヤ

**回路組立**

.. image:: img/24_rgb_module_circuit.png
    :width: 400
    :align: center

.. raw:: html
    
    <br/><br/>   

コード
^^^^^^^^^^^^^^^^^^^^

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/ac279eab-cbc6-4c51-a8b5-4d1b9048ec92/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/24-component_rgb.mp4"  type="video/mp4">
      お使いのブラウザはビデオタグをサポートしていません。
   </video>
   <br/><br/>  

コードの説明
^^^^^^^^^^^^^^^^^^^^

1. コードの最初の部分で、RGB LEDモジュールの各色チャネルに接続されているピンを宣言および初期化します。

   .. code-block:: arduino
       
      const int rledPin = 9;  // pin connected to the red color channel
      const int gledPin = 10;   // pin connected to the green color channel
      const int bledPin = 11;  // pin connected to the blue color channel

2. ``setup()`` 関数では、これらのピンをOUTPUTとして初期化します。これは、これらのピンからRGB LEDモジュールへ信号を送り出すという意味です。

   .. code-block:: arduino
   
      void setup() {
        pinMode(rledPin, OUTPUT);
        pinMode(gledPin, OUTPUT);
        pinMode(bledPin, OUTPUT);
      }

3. ``loop()`` 関数内で、 ``setColor()`` 関数が異なるパラメータで呼び出され、様々な色を表示します。各色を設定した後で、 ``delay()`` 関数を使用して1000ミリ秒（または1秒）次の色に移る前に一時停止します。

   .. code-block:: arduino
   
      void loop() {
        setColor(255, 0, 0);  // Set RGB LED color to red
        delay(1000);
        setColor(0, 255, 0);  // Set RGB LED color to green
        delay(1000);
        // The rest of the color sequence...
      }

4. ``setColor()`` 関数は、 ``analogWrite()`` 関数を使用してRGB LEDモジュールの各色チャネルの明るさを調整します。この関数はPWMを用いて、変動する電圧出力を模倣します。デューティサイクル（信号がHIGHである固定期間内の時間の割合）を制御することで、各色チャネルの明るさをコントロールし、多様な色の混合が可能になります。

   .. code-block:: arduino

      void setColor(int R, int G, int B) {
        analogWrite(rledPin, R);  // Use PWM to control the brightness of the red color channel
        analogWrite(gledPin, G);  // Use PWM to control the brightness of the green color channel
        analogWrite(bledPin, B);  // Use PWM to control the brightness of the blue color channel
      }

追加アイデア
^^^^^^^^^^^^^^^^^^^^

- 他の色を表示してみてください。
- RGB LEDをセンサーと組み合わせて、センサーの値に基づいて色を変更してみてください。

さらに多くのプロジェクト
---------------------------
* :ref:`fun_gas_leak_alarm`
* :ref:`fun_light_control_switch`
* :ref:`fun_motion_triggered_relay`
* :ref:`iot_Bluetooth_RGB_controller`
* :ref:`iot_Bluetooth_remote_relay`
