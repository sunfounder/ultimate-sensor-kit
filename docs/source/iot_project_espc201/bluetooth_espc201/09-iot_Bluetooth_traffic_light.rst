.. note::

    こんにちは、SunFounderのRaspberry Pi & Arduino & ESP32愛好家コミュニティへようこそ！Facebook上でRaspberry Pi、Arduino、ESP32についてもっと深く掘り下げ、他の愛好家と交流しましょう。

    **参加する理由は？**

    - **エキスパートサポート**：コミュニティやチームの助けを借りて、販売後の問題や技術的な課題を解決します。
    - **学び＆共有**：ヒントやチュートリアルを交換してスキルを向上させましょう。
    - **独占的なプレビュー**：新製品の発表や先行プレビューに早期アクセスしましょう。
    - **特別割引**：最新製品の独占割引をお楽しみください。
    - **祭りのプロモーションとギフト**：ギフトや祝日のプロモーションに参加しましょう。

    👉 私たちと一緒に探索し、創造する準備はできていますか？[|link_sf_facebook|]をクリックして今すぐ参加しましょう！

.. _c201_iot_Bluetooth_traffic_light:

9. Bluetooth 信号機
===================

3 つの LED が信号機の代わりです。スマートフォンから 1 文字送ると切り替わります。
**R** が赤、**Y** が黄、**G** が緑です。

これはスマートフォンがテキストではなく **コマンド** を送る最初のプロジェクトです。
しかも、思ったよりずっと短いものです。スケッチは 1 文字ずつ見るので、1 文字で完全な
メッセージになります。


1. 回路を組み立てる
-----------------------------

.. note::

   モジュールは起動時に大きな電流を引きます。9V 電池または外部電源を R4 Minima
   の DC ジャックに必ず接続してください。


.. image:: ../img/16-Wiring_Bluetooth_traffic_light.png
   :width: 80%

* :ref:`cpn_uno`
* :ref:`cpn_espc201`
* :ref:`cpn_traffic`


2. コードを書き込む
-----------------------------

#. ``09-Bluetooth_traffic_light.ino`` を ``ultimate-sensor-kit\code\iot_project_espc201\bluetooth\09-Bluetooth_traffic_light`` から開きます。

#. **Arduino UNO R4 Minima** と正しいポートを選び、**Upload** をクリックします。

#. シリアルモニターを **115200** で開きます。Bluetooth の 2 行の後、スマートフォン
   から送った文字がここに表示されます - 何も起きないように見えるときの手がかりになり
   ます。


3. スマートフォンから信号を操作する
-----------------------------------

入門章と同じ **LightBlue** を使います。

#. LightBlue を開き **Scan** をタップして **SunFounder-C2** に接続し、サービス
   **0xA002** を展開して Characteristic **C304** を開きます。赤い枠が押すボタンです。

   .. image:: ../img/ble_lightblue_write.png
      :width: 80%

#. **Write new value** をタップし、右上の形式を **UTF-8 String** にして、大文字の
   ``R`` を 1 文字入力して送ります。

   .. image:: ../img/ble_lightblue_R.png
      :width: 80%

#. 赤い LED が点き、残りの 2 つが消えます。

   * ``Y`` を送ると黄、``G`` を送ると緑になります。
   * 1 文字で十分ですが、長い単語でも問題ありません。スケッチは知っている文字にだけ
     反応し、残りは無視します。``RED`` と入力しても ``R`` は効きます。
   * 小文字の ``r`` は **効きません**。スケッチは大文字とだけ比較します。

#. 送りながらシリアルモニターを見てください。受け取った文字が 1 行ずつ表示されるの
   で、スマートフォンがボードに届いたかどうかがいつでも分かります。


4. コードの説明
-----------------------------

#. **3 つの LED**

   .. code-block:: arduino

      const int rledPin = 10;   // 赤
      const int yledPin = 11;   // 黄
      const int gledPin = 12;   // 緑

#. **Bluetooth も 1 行**

   .. code-block:: arduino

      #include "SunFounder_BLE.h"
      BLEStream bleSerial;

   前の章と同じオブジェクトです。``bleSerial.begin()`` がモジュールを **SunFounder-C2**
   としてアドバタイズさせ、スマートフォンが **C304** に書き込み、届いたものは
   ``bleSerial.read()`` で読めます。

#. **setup()**

   .. code-block:: arduino

      void setup() {
        pinMode(rledPin, OUTPUT);
        pinMode(yledPin, OUTPUT);
        pinMode(gledPin, OUTPUT);

        Serial.begin(115200);
        bleSerial.begin();
      }

#. **loop() - 1 文字ずつ**

   .. code-block:: arduino

      while (bleSerial.available() > 0) {
        character = bleSerial.read();
        Serial.println(character);

        if (character == 'R') {
          toggleLights(rledPin);
        } else if (character == 'Y') {
          toggleLights(yledPin);
        } else if (character == 'G') {
          toggleLights(gledPin);
        }
      }

   ``if`` ではなく ``while`` にしているのは意図的です。ループの 2 回の実行の間に複
   数の文字が届くことがあり、こうすればバッファに残りません。

   引用符が重要です。``'R'`` は文字 R で、``"R"`` は 1 文字のテキストになります。

#. **toggleLights()**

   .. code-block:: arduino

      void toggleLights(int targetLight) {
        digitalWrite(rledPin, LOW);
        digitalWrite(yledPin, LOW);
        digitalWrite(gledPin, LOW);

        digitalWrite(targetLight, HIGH);
      }

   まず 3 つとも消してから、必要なものだけを点けます。これが信号機らしさを作ります。
   点いているのは常に 1 つだけです。
