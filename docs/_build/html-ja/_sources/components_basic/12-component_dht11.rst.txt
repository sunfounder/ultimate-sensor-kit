.. note::

    こんにちは、SunFounderのRaspberry Pi & Arduino & ESP32愛好家コミュニティへようこそ！Facebook上でRaspberry Pi、Arduino、ESP32についてもっと深く掘り下げ、他の愛好家と交流しましょう。

    **参加する理由は？**

    - **エキスパートサポート**：コミュニティやチームの助けを借りて、販売後の問題や技術的な課題を解決します。
    - **学び＆共有**：ヒントやチュートリアルを交換してスキルを向上させましょう。
    - **独占的なプレビュー**：新製品の発表や先行プレビューに早期アクセスしましょう。
    - **特別割引**：最新製品の独占割引をお楽しみください。
    - **祭りのプロモーションとギフト**：ギフトや祝日のプロモーションに参加しましょう。

    👉 私たちと一緒に探索し、創造する準備はできていますか？[|link_sf_facebook|]をクリックして今すぐ参加しましょう！

.. _cpn_dht11:

温度と湿度センサーモジュール（DHT11）
================================================

.. image:: img/12_dht11_module.png
    :width: 300
    :align: center

概要
---------------------------
デジタル温度湿度センサーDHT11は、温度と湿度の較正済みデジタル信号出力を有する複合センサーです。この製品は専用のデジタルモジュール技術と温湿度センシング技術を組み合わせており、高い信頼性と優れた長期安定性が保証されています。

このセンサーは、抵抗性湿度検知コンポーネントとNTC温度計測デバイスを内蔵し、高性能8ビットマイクロコントローラーと接続されています。

原理
---------------------------
利用可能なピンはVCC、GND、DATAの3つだけです。通信プロセスは、DATAラインからDHT11にスタート信号を送ることで始まり、DHT11はこの信号を受けて応答信号を返します。その後、ホストは応答信号を受け取り、40ビットの湿度と温度データ（8ビット湿度整数 + 8ビット湿度小数 + 8ビット温度整数 + 8ビット温度小数 + 8ビットチェックサム）を受け取ります。

.. image:: img/12_dht11_module_2.png
    :width: 300
    :align: center

.. raw:: html
    
    <br/><br/>   

使い方
---------------------------

**使用する電子部品**

- Arduino Uno R4またはR3ボード * 1
- 温度と湿度センサーモジュール（DHT11） * 1
- ジャンパーワイヤー


**回路の組み立て**

.. note:: 
   キットには異なるバージョンのDHT11モジュールが含まれている場合があります。お手持ちのモジュールに応じた配線方法を確認してください。

.. csv-table:: 
   :header: "モジュール", "図"
   :widths: 100, 250

   |dht11_module|, |dht11_module_circuit|
   |dht11_module_withLED|, |dht11_module_withLED_circuit|


.. |dht11_module| image:: img/12_dht11_module.png 
   :width: 100px

.. |dht11_module_circuit| image:: img/12_dht11_module_circuit.png
   :width: 360px

.. |dht11_module_withLED| image:: img/12_dht11_module_withLED.png
   :width: 150px

.. |dht11_module_withLED_circuit| image:: img/12_dht11_module_withLED_circuit.png
   :width: 360px  


コード
^^^^^^^^^^^^^^^^^^^^

.. note:: 
   ライブラリをインストールするには、Arduinoのライブラリマネージャーで **"DHT sensor library"** を検索してインストールしてください。

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/34796700-4b94-4796-815a-314a25f60638/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/12-component_dht11.mp4"  type="video/mp4">
      お使いのブラウザはビデオタグをサポートしていません。
   </video>
   <br/><br/>  


コードの説明
^^^^^^^^^^^^^^^^^^^^

#. 必要なライブラリと定数の定義。
   この部分ではDHTセンサーライブラリを含め、このプロジェクトで使用されるピン番号とセンサータイプを定義しています。

   .. note::
      ライブラリをインストールするには、Arduinoのライブラリマネージャーで **"DHT sensor library"** と検索してインストールしてください。

   .. code-block:: arduino
    
      #include <DHT.h>
      #define DHTPIN 2       // Define the pin used to connect the sensor
      #define DHTTYPE DHT11  // Define the sensor type

#. DHTオブジェクトの作成。
   ここで、定義したピン番号とセンサータイプを用いてDHTオブジェクトを作成します。

   .. code-block:: arduino

      DHT dht(DHTPIN, DHTTYPE);  // Create a DHT object

#. Arduinoが起動したときに一度だけ実行される関数。
   この関数でシリアル通信とDHTセンサーを初期化します。

   .. code-block:: arduino

      void setup() {
        Serial.begin(9600);
        Serial.println(F("DHT11 test!"));
        dht.begin();  // Initialize the DHT sensor
      }

#. メインループ。
   ``loop()`` 関数はsetup関数の後に繰り返し実行されます。ここでは、湿度と温度の値を読み取り、ヒートインデックスを計算し、これらの値をシリアルモニターに表示します。センサーの読み取りが失敗する（NaNを返す）場合、エラーメッセージが表示されます。

   .. note::
    
      |link_heat_index| は、気温と湿度を組み合わせて、外部の暑さを感じる度合いを測定する方法です。これは「体感気温」または「顕在温度」とも呼ばれます。

   .. code-block:: arduino

      void loop() {
        delay(2000);
        float h = dht.readHumidity();
        float t = dht.readTemperature();
        float f = dht.readTemperature(true);
        if (isnan(h) || isnan(t) || isnan(f)) {
          Serial.println(F("Failed to read from DHT sensor!"));
          return;
        }
        float hif = dht.computeHeatIndex(f, h);
        float hic = dht.computeHeatIndex(t, h, false);
        Serial.print(F("Humidity: "));
        Serial.print(h);
        Serial.print(F("%  Temperature: "));
        Serial.print(t);
        Serial.print(F("°C "));
        Serial.print(f);
        Serial.print(F("°F  Heat index: "));
        Serial.print(hic);
        Serial.print(F("°C "));
        Serial.print(hif);
        Serial.println(F("°F"));
      }

追加アイデア
^^^^^^^^^^^^^^^^^^^^

- LCDまたはOLEDディスプレイでの読み取り値の表示

その他のプロジェクト
---------------------------
* :ref:`iot_Plant_monitor`
* :ref:`iot_Bluetooth_environmental_monitor`

