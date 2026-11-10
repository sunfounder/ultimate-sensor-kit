.. note::

    こんにちは、SunFounderのRaspberry Pi & Arduino & ESP32愛好家コミュニティへようこそ！Facebook上でRaspberry Pi、Arduino、ESP32についてもっと深く掘り下げ、他の愛好家と交流しましょう。

    **参加する理由は？**

    - **エキスパートサポート**：コミュニティやチームの助けを借りて、販売後の問題や技術的な課題を解決します。
    - **学び＆共有**：ヒントやチュートリアルを交換してスキルを向上させましょう。
    - **独占的なプレビュー**：新製品の発表や先行プレビューに早期アクセスしましょう。
    - **特別割引**：最新製品の独占割引をお楽しみください。
    - **祭りのプロモーションとギフト**：ギフトや祝日のプロモーションに参加しましょう。

    👉 私たちと一緒に探索し、創造する準備はできていますか？[|link_sf_facebook|]をクリックして今すぐ参加しましょう！

.. _cpn_button:

ボタンモジュール
==========================

.. image:: img/06_button.png
    :width: 350
    :align: center

.. _btn_intro:

概要
---------------------------
ボタンモジュールは、ボタンの状態を検出する電子デバイスです。通常はスイッチとして使用され、回路を接続または遮断します。ボタンは、ドアベル、デスクランプ、リモートコントロール、エレベーター、火災報知器など、多様なシナリオで活用されています。

原理
---------------------------
ボタンモジュールはスイッチの原理で動作します。スイッチとは、回路を開閉するための電子部品です。

以下はボタンの内部構造です。右下の記号は、回路図でボタンを表す際に一般的に使用されます。

.. image:: img/06_button_2.png
    :width: 400
    :align: center

ボタンが押されると、1番ピンと2番ピン、3番ピンと4番ピンが接続され、回路が閉じます。

.. image:: img/06_button_3.png
    :width: 700
    :align: center

使い方
---------------------------

**使用する電子部品**

- Arduino Uno R4またはR3ボード * 1
- ボタンモジュール * 1
- ジャンパーワイヤー

**回路の組み立て**

.. image:: img/06_button_circuit.png
    :width: 400
    :align: center

.. raw:: html
    
    <br/><br/>   

コード
^^^^^^^^^^^^^^^^^^^^

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/d6586fb8-fd37-46d2-ba1f-c94ef3582fe8/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/06-component_button.mp4"  type="video/mp4">
      お使いのブラウザはビデオタグをサポートしていません。
   </video>
   <br/><br/>  


コードの説明
^^^^^^^^^^^^^^^^^^^^

1. **初期設定**: このコードの部分では、まず ``sensorPin`` を定数型の整数として宣言し、Arduinoボード上でボタンに接続するピン番号を割り当てます。 ``setup()`` 関数は、 ``sensorPin`` のモードを ``INPUT`` として設定します。これは、このピンを通してボタンからデータを受け取ることを意味します。 ``Serial.begin()`` 関数は、ボーレートが9600でシリアル通信を開始します。

   .. code-block:: arduino

      const int sensorPin = 7;

      void setup() {
        pinMode(sensorPin, INPUT);
        Serial.begin(9600);
      }

2. **メインループ**: ``loop()`` 関数は、プログラムの主要なロジックを含んでいます。この関数は連続してボタンの状態を読み取り、その値を50ミリ秒ごとにシリアルモニターに出力します。 ``digitalRead()`` 関数はボタンの状態を読み取り、 ``Serial.println()`` 関数はその値をシリアルモニターに出力します。 ``delay()`` 関数は、次の読み取り前に実行を50ミリ秒間一時停止します。ボタンは押されると低レベルを、放されると高レベルを出力します。

   .. code-block:: arduino

      void loop() {
        Serial.println(digitalRead(sensorPin));
        delay(50);
      }


追加のアイデア
^^^^^^^^^^^^^^^^^^^^

- if文を用いてボタンでプログラム内で異なる結果を制御する。
- ボタンでLEDをオン/オフ切り替えるようにする。

他のプロジェクト
---------------------------
* :ref:`fun_doorbell`
