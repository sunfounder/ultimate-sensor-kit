.. note::

    こんにちは、SunFounderのRaspberry Pi & Arduino & ESP32愛好家コミュニティへようこそ！Facebook上でRaspberry Pi、Arduino、ESP32についてもっと深く掘り下げ、他の愛好家と交流しましょう。

    **参加する理由は？**

    - **エキスパートサポート**：コミュニティやチームの助けを借りて、販売後の問題や技術的な課題を解決します。
    - **学び＆共有**：ヒントやチュートリアルを交換してスキルを向上させましょう。
    - **独占的なプレビュー**：新製品の発表や先行プレビューに早期アクセスしましょう。
    - **特別割引**：最新製品の独占割引をお楽しみください。
    - **祭りのプロモーションとギフト**：ギフトや祝日のプロモーションに参加しましょう。

    👉 私たちと一緒に探索し、創造する準備はできていますか？[|link_sf_facebook|]をクリックして今すぐ参加しましょう！

.. _fun_motion_triggered_relay:

動作検出によるリレー制御
==========================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/fun/05-fun_Motion_triggered_relay.mp4"  type="video/mp4">
      お使いのブラウザはビデオタグをサポートしていません。
   </video>

このArduinoプロジェクトは、パッシブ赤外線（PIR）センサーを使用してリレーで操作する照明を制御することを目的としています。PIRセンサーが動きを検出すると、リレーが活性化し、照明が点灯します。照明は最後に検出された動きから5秒間点灯したままです。

.. warning ::
    このデモンストレーションでは、RGB LEDモジュールを制御するためにリレーを使用しています。しかし、現実のシナリオではこれが最も実用的な方法であるとは限りません。
    
    **実際の用途でリレーを他の機器に接続することはできますが、高電圧ACに対する極度の注意が必要です。不適切または誤った使用は重傷や死亡につながる可能性があります。したがって、高電圧ACに精通している方を対象としています。安全を最優先にしてください。**


1. 回路の作成
-----------------------------

.. image:: img/05-fun_Motion_triggered_relay_circuit.png
    :width: 90%

* :ref:`cpn_uno`
* :ref:`cpn_pir_motion`
* :ref:`cpn_relay`
* :ref:`cpn_rgb`


2. コード
-----------------------------

#. ``05-Motion_triggered_relay.ino`` ファイルを ``ultimate-sensor-kit\fun_project\05-Motion_triggered_relay`` のパスから開くか、このコードを **Arduino IDE** にコピーペーストしてください。

   .. raw:: html
       
       <iframe src=https://create.arduino.cc/editor/sunfounder01/147bb59d-8127-46e3-b276-a721bcff08df/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


3. コードの説明
-----------------------------

このプロジェクトは、PIR動作センサーの動きを検出する能力を中心に展開されています。動きが検出されると、Arduinoに信号が送られ、これがリレーモジュールをトリガーし、照明が活性化します。照明は、最後に検出された動き後、指定された期間（この場合は5秒）点灯したままとなります。

1. **初期設定と変数の宣言**

   この部分では、コード全体で使用される定数と変数を定義しています。リレーとPIRのピン、動きの遅延定数を設定し、最後に検出された動作の時間と動作検出のフラグを追跡する変数も用意しています。

   .. code-block:: arduino
   
      const int relayPin = 9;
      const int pirPin = 8;
      const unsigned long MOTION_DELAY = 5000;
      unsigned long lastMotionTime = 0;
      bool motionDetected = false;

2. **setup()関数内のピン設定**

   ``setup()`` 関数で、リレーとPIRセンサーのピンモードを設定します。また、最初はリレーをオフにしています。

   .. code-block:: arduino
   
      void setup() {
        pinMode(relayPin, OUTPUT);
        pinMode(pirPin, INPUT);
        digitalWrite(relayPin, LOW);
      }

3. **loop()関数における主要なロジック**

   ``loop()`` 関数は主要なロジックを含んでいます。PIRセンサーが動きを検出すると、 ``HIGH`` 信号を送り、リレーをオンにし、 ``lastMotionTime`` を更新します。特定の遅延（この場合は5秒）で動きがない場合、リレーはオフになります。

   このアプローチにより、動きが断続的または短時間であっても、最後に検出された動きから少なくとも5秒間ライトが点灯し、一貫した照明時間を提供します。
   
   .. code-block:: arduino
   
      void loop() {
        if (digitalRead(pirPin) == HIGH) {
          lastMotionTime = millis();
          digitalWrite(relayPin, HIGH);
          motionDetected = true;
        }
        if (motionDetected && (millis() - lastMotionTime >= MOTION_DELAY)) {
          digitalWrite(relayPin, LOW);
          motionDetected = false;
        }
      }
