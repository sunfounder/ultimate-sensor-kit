.. note::

    こんにちは、SunFounderのRaspberry Pi & Arduino & ESP32愛好家コミュニティへようこそ！Facebook上でRaspberry Pi、Arduino、ESP32についてもっと深く掘り下げ、他の愛好家と交流しましょう。

    **参加する理由は？**

    - **エキスパートサポート**：コミュニティやチームの助けを借りて、販売後の問題や技術的な課題を解決します。
    - **学び＆共有**：ヒントやチュートリアルを交換してスキルを向上させましょう。
    - **独占的なプレビュー**：新製品の発表や先行プレビューに早期アクセスしましょう。
    - **特別割引**：最新製品の独占割引をお楽しみください。
    - **祭りのプロモーションとギフト**：ギフトや祝日のプロモーションに参加しましょう。

    👉 私たちと一緒に探索し、創造する準備はできていますか？[|link_sf_facebook|]をクリックして今すぐ参加しましょう！

.. _c201_iot_Bluetooth_lcd:

8. Bluetooth LCD
================

スマートフォンで単語を入力すると、LCD に表示されます。ケーブルも Wi-Fi もインター
ネットも不要です。

ボードは前の章と同じ **SunFounder-C2** モジュールで、使い方も同じです。スマート
フォンが Characteristic **C304** にテキストを書き、スケッチがそれを読みます。


1. 回路を組み立てる
-----------------------------

.. note::

   モジュールは起動時に大きな電流を引きます。9V 電池または外部電源を R4 Minima
   の DC ジャックに必ず接続してください。


.. image:: ../img/15-Wiring_Bluetooth_LCD.png
   :width: 100%

* :ref:`cpn_uno`
* :ref:`cpn_espc201`
* :ref:`cpn_i2c_lcd1602`


2. コードを書き込む
-----------------------------

#. ``08-Bluetooth_lcd.ino`` を ``ultimate-sensor-kit\code\iot_project_espc201\bluetooth\08-Bluetooth_lcd`` から開くか、コードを **Arduino IDE** にコピーします。

   .. note::

      スケッチには **LiquidCrystal I2C** ライブラリが必要です。ライブラリマネー
      ジャーで ``LiquidCrystal I2C`` を検索してインストールしてください。

#. **Arduino UNO R4 Minima** と正しいポートを選び、**Upload** をクリックします。

#. シリアルモニターを **115200** で開きます。次のように表示されます。

   .. code-block:: text

      === ESPC2-01 Bluetooth (BLE) ===
      [OK] BLE is ready - scan for "SunFounder-C2" on your phone
      --------------------------------

   ``[!] no reply from the module`` と出たら、モジュールが D0/D1 で応答していませ
   ん。4 本の配線と電源を確認してください。


3. LightBlue でテキストを送る
------------------------------

入門章と同じ **LightBlue** アプリを使います。

#. LightBlue を開き **Scan** をタップして **SunFounder-C2** に接続します。

#. サービス **0xA002** を展開し、Characteristic **C304** を開きます。そして
   **Write new value** をタップします。

   .. image:: ../img/ble_lightblue_write.png
      :width: 80%

#. 右上の形式を **UTF-8 String** にし、短い単語（例: ``hello``）を入力します。図は
   送信直前の入力欄です。

   .. image:: ../img/ble_lightblue_hello.png
      :width: 80%

#. 送信すると、単語が **LCD** とシリアルモニターに表示されます。

   .. note::

      テキストは短くしてください。LCD は 16 桁 2 行で、17 文字目以降は 2 行目に送ら
      れます。長すぎる単語は切り捨てられます。

#. 逆方向（ボードからスマートフォン）は、**C305** を Subscribe してからシリアルモニ
   ターで入力します。入門章で使ったのと同じ 2 つの Characteristic で、片側が LCD を
   動かしているだけです。


4. コードの説明
-----------------------------

#. **I2C バス上の LCD**

   .. code-block:: arduino

      #include <LiquidCrystal_I2C.h>
      LiquidCrystal_I2C lcd(0x27, 16, 2);

   ``0x27`` はディスプレイの I2C アドレス、``16`` が桁数、``2`` が行数です。この種の
   モジュールは ``0x27`` で応答するものがほとんどですが、``0x3F`` のものも少しありま
   す。

#. **Bluetooth は 1 行で**

   .. code-block:: arduino

      #include "SunFounder_BLE.h"
      BLEStream bleSerial;

   ``BLEStream`` が AT コマンドをすべて隠してくれます。``bleSerial.begin()`` が
   Bluetooth を有効にし、名前を **SunFounder-C2** に設定してアドバタイズを始めます。
   その後は普通のシリアルポートのように ``available()``、``read()``、``write()`` が使
   えます。

   .. note::

      モジュールとは D0/D1（``Serial1``）を **115200** で通信します。ハードウェア
      ポートなので、LCD を更新している間もビットが失われません。

#. **setup()**

   .. code-block:: arduino

      void setup() {
        lcd.init();
        lcd.clear();
        lcd.backlight();

        Serial.begin(115200);
        bleSerial.begin();
        bleSerial.setTimeout(50);
      }

   ``lcd.backlight()`` が重要です。これがないと表示はされますが暗いままです。短い
   ``setTimeout(50)`` は、``readString()`` が来ない文字を丸 1 秒待つのを防ぎます。

#. **loop() - スマートフォンから LCD へ**

   .. code-block:: arduino

      if (bleSerial.available()) {
        data += bleSerial.readString();
        while (data.endsWith("\r") || data.endsWith("\n")) {
          data.remove(data.length() - 1);
        }
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(data);
      }

   スマートフォンは入力したテキストに改行を付けることがよくあります。取り除くのはそ
   の文字だけで、実際の文字は消しません。そのうえでテキストを表示します。

#. **loop() - ボードからスマートフォンへ**

   .. code-block:: arduino

      if (Serial.available()) {
        bleSerial.write(Serial.read());
      }

   シリアルモニターで入力したものはすべて **C305** に転送されます。LightBlue でそれを
   Subscribe しておけば、1 バイトずつ表示されます。
