.. note::

    こんにちは、SunFounderのRaspberry Pi & Arduino & ESP32愛好家コミュニティへようこそ！Facebook上でRaspberry Pi、Arduino、ESP32についてもっと深く掘り下げ、他の愛好家と交流しましょう。

    **参加する理由は？**

    - **エキスパートサポート**：コミュニティやチームの助けを借りて、販売後の問題や技術的な課題を解決します。
    - **学び＆共有**：ヒントやチュートリアルを交換してスキルを向上させましょう。
    - **独占的なプレビュー**：新製品の発表や先行プレビューに早期アクセスしましょう。
    - **特別割引**：最新製品の独占割引をお楽しみください。
    - **祭りのプロモーションとギフト**：ギフトや祝日のプロモーションに参加しましょう。

    👉 私たちと一緒に探索し、創造する準備はできていますか？[|link_sf_facebook|]をクリックして今すぐ参加しましょう！

.. _cpn_raindrop:

雨滴検出モジュール
==========================

.. image:: img/11_raindrop_detection_module.jpg
    :width: 300
    :align: center

概要
---------------------------

雨滴センサー、または雨滴検出センサーは、雨が降っているか、そしてその降雨量を検出するために使用されます。このセンサーは、自動車の自動ワイパーシステム、スマート照明システム、およびサンルーフシステムで広く活用されています。

原理
---------------------------

雨滴センサーは基本的に、ニッケルが線形にコーティングされた基板です。このセンサーは、抵抗の原理に基づいて動作します。基板上に雨滴がない場合、抵抗は高く、V=IRに従って高い電圧が得られます。雨滴が存在すると、水は電気の導体であり、水の存在によりニッケルの線が並列に接続されるため、抵抗が減少し、それに伴い電圧も低下します。降雨が激しいほど、抵抗は低くなります。

使い方
---------------------------

**使用する電子部品**

- Arduino Uno R4またはR3ボード * 1
- 雨滴検出モジュール * 1
- ジャンパーワイヤー


**回路組み立て**

.. image:: img/11_raindrop_detection_module_circuit.png
    :width: 400
    :align: center

.. raw:: html
    
    <br/><br/>   

コード
^^^^^^^^^^^^^^^^^^^^

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/5dbd8745-a9a9-4b19-b245-02c073d89ce8/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/11-component_raindrop.mp4"  type="video/mp4">
      お使いのブラウザはビデオタグをサポートしていません。
   </video>
   <br/><br/>  

コードの説明
^^^^^^^^^^^^^^^^^^^^

1. センサーピンの定義
ここでは、 ``sensorPin`` という名前の定数整数を定義し、値7を割り当てます。これは、Arduinoボードのデジタルピンに雨滴検出センサーが接続される場所に対応しています。

.. code-block:: arduino

    const int sensorPin = 7;

2. ピンモードの設定とシリアル通信の初期化
``setup()`` 関数では、二つの主要な手順を実施します。まず、 ``pinMode()``  で ``sensorPin`` を入力モードに設定し、雨滴センサーからデジタル値を読むことができるようにします。次に、9600のボーレートでシリアル通信を開始します。

.. code-block:: arduino

    void setup() {
      pinMode(sensorPin, INPUT);
      Serial.begin(9600);
    }

3. デジタル値の読み取りとシリアルモニタへの送信
``loop()`` 関数で、 ``digitalRead()`` を用いて雨滴センサーからデジタル値を読み取ります。この値（HIGH または LOW）はシリアルモニターに出力されます。その後、次回の読み取りまで50ミリ秒待機します。

.. code-block:: arduino

    void loop() {
      Serial.println(digitalRead(sensorPin));
      delay(50);
    }

追加のアイディア
^^^^^^^^^^^^^^^^^^^^

- 雨が検出された際に点灯するLEDインジケーターを追加する。
- Arduinoにブザーを接続し、雨を検出したときに警告音を鳴らす。これはピクニックや屋外活動などのイベントにおける早期警告システムとして使用できる。
