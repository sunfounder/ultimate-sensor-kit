.. note::

    こんにちは、SunFounderのRaspberry Pi & Arduino & ESP32愛好家コミュニティへようこそ！Facebook上でRaspberry Pi、Arduino、ESP32についてもっと深く掘り下げ、他の愛好家と交流しましょう。

    **参加する理由は？**

    - **エキスパートサポート**：コミュニティやチームの助けを借りて、販売後の問題や技術的な課題を解決します。
    - **学び＆共有**：ヒントやチュートリアルを交換してスキルを向上させましょう。
    - **独占的なプレビュー**：新製品の発表や先行プレビューに早期アクセスしましょう。
    - **特別割引**：最新製品の独占割引をお楽しみください。
    - **祭りのプロモーションとギフト**：ギフトや祝日のプロモーションに参加しましょう。

    👉 私たちと一緒に探索し、創造する準備はできていますか？[|link_sf_facebook|]をクリックして今すぐ参加しましょう！

.. _cpn_touch:

タッチセンサモジュール
==========================

.. image:: img/17_touch_sensor_moudle.png
    :width: 200
    :align: center

概要
---------------------------
タッチスイッチセンサ（タッチボタンまたはタッチスイッチとも呼ばれる）は、製品をスッキリと見せるために多くの新しいデバイスでボタンの代わりに使用されています（例：タッチ式のランプ）。

原理
---------------------------
このモジュールは、タッチセンサIC（TTP223B）に基づいた静電容量型タッチスイッチモジュールです。通常状態では、モジュールは低消費電力で低レベルを出力し、指が対応する位置に触れると高レベルを出力し、指が離れた後に再び低レベルになります。

静電容量型タッチスイッチの動作原理：

.. image:: img/17_touch_sensor_moudle_principle.jpeg
    :width: 400
    :align: center

実際には、静電容量型センサは、一方の面をタッチセンサとし、反対側の面をコンデンサの接地板として二層のPCB上に作成できます。電源がこれらのプレートに適用されると、2つのプレートは充電されます。平衡状態では、プレートは電源と同じ電圧を持ちます。

タッチ検出回路には、タッチパッドの容量に依存する振動子があります。指がタッチパッドに近づくと、追加の容量がこの内部振動子の周波数を変更します。検出回路は、タイムインターバルで振動子の周波数を追跡し、シフトがしきい値の変更を超えると、キープレスイベントをトリガーします。

使い方
---------------------------

**使用する電子部品**

- Arduino Uno R4 または R3 ボード * 1
- タッチセンサモジュール * 1
- ジャンパワイヤ

**回路の組み立て**

.. image:: img/17_touch_sensor_moudle_circuit.png
    :width: 400
    :align: center

.. raw:: html
    
    <br/><br/>   

コード
^^^^^^^^^^^^^^^^^^^^

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/3a0a411f-7bdc-43f0-82e9-5978e4167dd7/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/17-component_touch.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>
   <br/><br/>  

コードの説明
^^^^^^^^^^^^^^^^^^^^

#. タッチセンサが接続されているピン番号を定義して、必要な変数を設定します。

   .. code-block:: arduino

      const int sensorPin = 7;

#. ``setup()`` 関数内での初期設定。ここでは、センサピンが入力として使用され、内蔵LEDが出力として使用されるよう指定します。また、シリアルモニタにメッセージを送るためのシリアル通信を開始します。

   .. code-block:: arduino

      void setup() {
        pinMode(sensorPin, INPUT);
        pinMode(LED_BUILTIN, OUTPUT);
        Serial.begin(9600);
      }

#. Arduinoは継続的にタッチセンサが活性化されているかどうかを確認します。タッチが検出された場合、LEDを点灯させて「Touch detected!」というメッセージを送ります。タッチが検出されなかった場合は、LEDを消灯して「No touch detected...」というメッセージを送ります。センサが高速で読み取られないように、遅延が導入されます。

   .. code-block:: arduino

      void loop() {
        if (digitalRead(sensorPin) == 1) {
          digitalWrite(LED_BUILTIN, HIGH);
          Serial.println("Touch detected!");
        } else {
          digitalWrite(LED_BUILTIN, LOW);
          Serial.println("No touch detected...");
        }
        delay(100);
      }

追加のアイデア
^^^^^^^^^^^^^^^^^^^^

- タッチを示すために異なるLEDの色を使用する
- タッチセンサは、モーターやリレーなど、より複雑な要素を制御するために使用できる。

さらに多くのプロジェクト
---------------------------
* :ref:`fun_touch_toggle_light`
