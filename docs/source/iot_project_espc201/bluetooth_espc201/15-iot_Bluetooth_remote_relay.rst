.. note::

    こんにちは、SunFounderのRaspberry Pi & Arduino & ESP32愛好家コミュニティへようこそ！Facebook上でRaspberry Pi、Arduino、ESP32についてもっと深く掘り下げ、他の愛好家と交流しましょう。

    **参加する理由は？**

    - **エキスパートサポート**：コミュニティやチームの助けを借りて、販売後の問題や技術的な課題を解決します。
    - **学び＆共有**：ヒントやチュートリアルを交換してスキルを向上させましょう。
    - **独占的なプレビュー**：新製品の発表や先行プレビューに早期アクセスしましょう。
    - **特別割引**：最新製品の独占割引をお楽しみください。
    - **祭りのプロモーションとギフト**：ギフトや祝日のプロモーションに参加しましょう。

    👉 私たちと一緒に探索し、創造する準備はできていますか？[|link_sf_facebook|]をクリックして今すぐ参加しましょう！

.. _c201_iot_Bluetooth_remote_relay:

15. Bluetooth リレー
====================

リレーは電磁石で動くスイッチなので、小さな信号でずっと大きな負荷を制御できます。
``1`` を送るとリレーが入り、``0`` で切れます。


1. 回路を組み立てる
-----------------------------

.. warning::

    このキットのリレーは小さな直流負荷だけを扱います。学習中は **絶対に商用電源を
    接続しないでください** - 220V は命に関わりますし、ここでは必要ありません。

.. note::

   モジュールは起動時に大きな電流を引きます。9V 電池または外部電源を R4 Minima
   の DC ジャックに必ず接続してください。


.. image:: ../img/13-Wiring_Bluetooth_remote_relay.png
   :width: 80%

* :ref:`cpn_uno`
* :ref:`cpn_espc201`
* :ref:`cpn_relay`


2. コードを書き込む
-----------------------------

#. ``15-Bluetooth_remote_relay.ino`` を ``ultimate-sensor-kit\code\iot_project_espc201\bluetooth\15-Bluetooth_remote_relay`` から開きます。

#. **Arduino UNO R4 Minima** と正しいポートを選び、**Upload** をクリックします。

#. シリアルモニターを **115200** で開きます。コマンドごとに ``On`` か ``Off`` で応答
   します。

   .. code-block:: text

      On
      Off


3. スマートフォンから切り替える
-------------------------------

#. LightBlue を開き **Scan** をタップして **SunFounder-C2** に接続し、サービス
   **0xA002**、Characteristic **C304** の順に開きます。赤い枠が押すボタンです。

   .. image:: ../img/ble_lightblue_write.png
      :width: 80%

#. **Write new value** をタップし、右上の形式を **UTF-8 String** にして ``1`` を入力
   します。図は送信直前の入力欄です。

   .. image:: ../img/ble_lightblue_1.png
      :width: 80%

#. 送信するとリレーがカチッと鳴り、表示 LED が点いて、モニターに ``On`` と出ます。

#. 同じ入力欄に ``0`` を入れて送ると、リレーが戻り ``Off`` と出ます。

   .. image:: ../img/ble_lightblue_0.png
      :width: 80%

   .. note::

      リレーモジュールの中には逆向きに動作するものがあり、ピンが **LOW** のときに
      入ります。アプリのスイッチと逆に鳴る場合は、スケッチの ``HIGH`` と ``LOW`` を入
      れ替えてください。


4. コードの説明
-----------------------------

#. **1 本のピン、1 つのスイッチ**

   .. code-block:: arduino

      const int relayPin = 8;

      pinMode(relayPin, OUTPUT);
      digitalWrite(relayPin, LOW);

   ``setup()`` の ``LOW`` が重要です。出力になったばかりのピンは一瞬 HIGH になること
   があり、再起動のたびにリレーがカチッと鳴ってしまいます。

#. **コマンドの判定**

   .. code-block:: arduino

      if (message == '1') {
        digitalWrite(relayPin, HIGH);
        Serial.println("On");
      } else if (message == '0') {
        digitalWrite(relayPin, LOW);
        Serial.println("Off");
      }

   ロックのプロジェクトと同じ形です。状態はスマートフォンから来て、``1`` と ``0`` 以
   外は無視されます。

#. **なぜリレーをスマートフォンから直接動かさないのか**

   スマートフォンはモジュールと話し、モジュールは 2 本の配線でボードと話し、ボードが
   リレーを動かします。各段階は短いコマンドを渡すだけなので、3 つの機器が関わってい
   ても 1 文字で足ります。
