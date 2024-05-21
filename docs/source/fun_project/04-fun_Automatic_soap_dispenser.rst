.. note::

    こんにちは、SunFounderのRaspberry Pi & Arduino & ESP32愛好家コミュニティへようこそ！Facebook上でRaspberry Pi、Arduino、ESP32についてもっと深く掘り下げ、他の愛好家と交流しましょう。

    **参加する理由は？**

    - **エキスパートサポート**：コミュニティやチームの助けを借りて、販売後の問題や技術的な課題を解決します。
    - **学び＆共有**：ヒントやチュートリアルを交換してスキルを向上させましょう。
    - **独占的なプレビュー**：新製品の発表や先行プレビューに早期アクセスしましょう。
    - **特別割引**：最新製品の独占割引をお楽しみください。
    - **祭りのプロモーションとギフト**：ギフトや祝日のプロモーションに参加しましょう。

    👉 私たちと一緒に探索し、創造する準備はできていますか？[|link_sf_facebook|]をクリックして今すぐ参加しましょう！

.. _fun_soap_dispenser:

自動石鹸ディスペンサー
==========================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/fun/04-fun_Automatic_soap_dispenser.mp4"  type="video/mp4">
      お使いのブラウザはビデオタグをサポートしていません。
   </video>

この自動石鹸ディスペンサープロジェクトは、Arduino Unoボードと赤外線障害物回避センサー、水ポンプを使用しています。このセンサーは手などの物体の存在を検出し、その結果を基に水ポンプが石鹸を供給します。

1. 回路の作成
-----------------------------

.. image:: img/04-fun_Automatic_soap_dispenser_circuit.png
    :width: 90%

* :ref:`cpn_uno`
* :ref:`cpn_ir_obstacle`
* :ref:`cpn_pump`


2. コード
-----------------------------

#. ``ultimate-sensor-kit\fun_project\04-Automatic_soap_dispenser`` のパス下にある ``04-Automatic_soap_dispenser.ino`` ファイルを開くか、このコードを **Arduino IDE** にコピーしてください。

   .. raw:: html
       
       <iframe src=https://create.arduino.cc/editor/sunfounder01/0ee4125a-39fe-4493-bbe6-8bef68721896/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


3. コードの解説
-----------------------------

このプロジェクトの主旨は、手を使わずに石鹸を供給するシステムを作成することです。赤外線障害物回避センサーが物体（手など）が近づいているのを検出すると、その情報をArduinoに送信します。それによって水ポンプが活性化し、短い期間石鹸を供給した後、停止します。

#. **センサーとポンプのピンの定義**

   このコードスニペットでは、センサーとポンプに接続するArduinoのピンを定義しています。7番ピンをセンサーピンとして、 ``sensorValue`` 変数でこのセンサーから読み取るデータを保持します。水ポンプには、9番と10番の2つのピンを使用します。

   .. code-block:: arduino
   
      const int sensorPin = 7;
      int sensorValue;
      const int pump1A = 9;
      const int pump1B = 10;

#. **センサーとポンプの設定**

   ``setup()`` 関数では、使用するピンのモードを定義しています。センサーピンは ``INPUT`` として設定され、センサーからのデータを受信します。ポンプのピンは ``OUTPUT`` として設定され、ポンプに命令を送ります。 ``pump1B`` ピンが ``LOW`` （オフ）状態から始まるようにし、9600のボーレートでシリアル通信を開始します。

   .. code-block:: arduino
   
      void setup() {
        pinMode(sensorPin, INPUT);
        pinMode(pump1A, OUTPUT);    
        pinMode(pump1B, OUTPUT);    
        digitalWrite(pump1B, LOW);  
        Serial.begin(9600);
      }

#. **センサーの状態を常に確認し、ポンプを制御する**

   ``loop()`` 関数では、Arduinoが常にセンサーからの値を ``digitalRead()`` で読み取り、 ``sensorValue()`` に割り当てます。その値をデバッグのためにシリアルモニターに出力します。センサーが物体を検出すると、 ``sensorValue()`` は0になります。このとき、 ``pump1A`` を ``HIGH`` に設定してポンプを活性化し、700ミリ秒の遅延で石鹸を供給します。その後、 ``pump1A`` を ``LOW`` に設定してポンプを停止し、1秒の遅延でユーザーが手を動かせる時間を確保します。

   .. code-block:: arduino
   
      void loop() {
        sensorValue = digitalRead(sensorPin);
        Serial.println(sensorValue);
        if (sensorValue == 0) {  
          digitalWrite(pump1A, HIGH);
          delay(700);
          digitalWrite(pump1A, LOW);
          delay(1000);
        }
      }
