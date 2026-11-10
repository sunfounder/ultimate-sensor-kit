.. note::

    こんにちは、SunFounderのRaspberry Pi & Arduino & ESP32愛好家コミュニティへようこそ！Facebook上でRaspberry Pi、Arduino、ESP32についてもっと深く掘り下げ、他の愛好家と交流しましょう。

    **参加する理由は？**

    - **エキスパートサポート**：コミュニティやチームの助けを借りて、販売後の問題や技術的な課題を解決します。
    - **学び＆共有**：ヒントやチュートリアルを交換してスキルを向上させましょう。
    - **独占的なプレビュー**：新製品の発表や先行プレビューに早期アクセスしましょう。
    - **特別割引**：最新製品の独占割引をお楽しみください。
    - **祭りのプロモーションとギフト**：ギフトや祝日のプロモーションに参加しましょう。

    👉 私たちと一緒に探索し、創造する準備はできていますか？[|link_sf_facebook|]をクリックして今すぐ参加しましょう！

.. _cpn_relay:

5V リレーモジュール
==========================

.. image:: img/25_relay_module.png
    :width: 400
    :align: center

概要
---------------------------
5Vリレーモジュールは、Arduinoからの5V信号を使って高電圧または高電流デバイスを制御することができる装置です。照明、扇風機、モーター、ソレノイドなど、多様なデバイスの制御に使用可能です。5Vリレーには、制御したいデバイスに接続する高電圧端子（NC、C、NO）と、Arduinoに接続する低電圧ピン（GND、Vcc、Signal）がそれぞれ3つずつあります。

原理
---------------------------
リレーは、入力信号に応じて二つ以上のポイントやデバイスを接続するための装置です。言い換えれば、リレーは、コントローラとACまたはDCで動作するデバイスとの間で隔離を提供します。リレーは、DCで動作するマイクロコントローラから信号を受け取るため、そのギャップを埋める必要があります。

リレーには以下の5つの部分があります：

.. image:: img/25_relay_2.jpeg
    :width: 500
    :align: center

電磁石 - 鉄の芯にコイル線が巻かれています。電気が流れると磁力が発生するため、電磁石と呼ばれます。

アーマチュア - 可動する磁気ストリップです。電流が流れると、コイルが励起され、磁場が発生し、通常開（N/O）または通常閉（N/C）の点を開閉します。

バネ - コイルに電流が流れていないとき、バネはアーマチュアを引っ張り、回路を開きます。

接点セット - 二つの接点があります：

* NO - リレーが動作しているときに接続し、動作していないときに切断します。
* NC - リレーが動作しているときに切断し、動作していないときに接続します。

成型フレーム - 通常はプラスチック製で、リレーの構造的なサポートと保護を提供します。

使い方
---------------------------

**使用する電子部品**

- Arduino Uno R4またはR3ボード * 1
- 5Vリレーモジュール * 1
- ジャンパーワイヤー

**回路の組み立て**

.. image:: img/25_relay_module_circuit.png
    :width: 100%
    :align: center

.. raw:: html
    
    <br/><br/>   

.. warning ::

以下の例はLEDモジュールを制御するためにリレーを使用する方法を示しています。
**実際の用途で他の機器にリレーを接続する場合、高電圧ACに取り扱う際は極度の注意が必要です。不適切または誤った使用は重傷や死につながる可能性があります。したがって、高電圧ACに精通しているか、それについて十分な知識がある人向けです。常に安全を最優先してください。**

コード
^^^^^^^^^^^^^^^^^^^^

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/d3f6723d-bd49-4461-96de-84293f2e6d10/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/25-component_relay.mp4"  type="video/mp4">
      ご使用のブラウザはこのビデオタグをサポートしていません。
   </video>
   <br/><br/>  

コードの説明
^^^^^^^^^^^^^^^^^^^^

1. リレーピンの設定:
   - リレーモジュールはArduinoのピン6に接続されています。このピンはコード内で ``relayPin`` として定義されています。

   .. code-block:: arduino
    
      const int relayPin = 6;

2. リレーピンを出力として設定:
   - ``setup()`` 関数内で、リレーピンは ``pinMode()`` 関数を使用してOUTPUTとして設定されています。

   .. code-block:: arduino

      void setup() {
        pinMode(relayPin, OUTPUT);
      }

3. リレーをON/OFFで切り替え:
   - ``loop()`` 関数内で、最初にリレーは ``digitalWrite(relayPin, LOW)`` を使用してOFF状態にされます。この状態は3秒間続きます（ ``delay(3000)`` ）。
   - 次に、リレーは ``digitalWrite(relayPin, HIGH)`` を使用してON状態にされます。これも3秒間続きます。
   - このサイクルは無限に繰り返されます。

   .. code-block:: arduino

      void loop() {
        digitalWrite(relayPin, LOW);
        delay(3000);

        digitalWrite(relayPin, HIGH);
        delay(3000);
      }

追加のアイデア
^^^^^^^^^^^^^^^^^^^^

- 物理的なボタンを導入して、リレーの状態を手動で制御します。
  
- 温度センサーや光センサーなどのセンサーを組み込み、環境条件に基づいてリレーをトリガーします。

さらに多くのプロジェクト
---------------------------
* :ref:`fun_light_control_switch`
* :ref:`fun_motion_triggered_relay`
* :ref:`iot_Remote_relay_controller`
* :ref:`iot_Bluetooth_remote_relay`
* :ref:`iot_Bluetooth_voice_control_relay`

