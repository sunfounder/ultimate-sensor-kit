.. note::

    こんにちは、SunFounderのRaspberry Pi & Arduino & ESP32愛好家コミュニティへようこそ！Facebook上でRaspberry Pi、Arduino、ESP32についてもっと深く掘り下げ、他の愛好家と交流しましょう。

    **参加する理由は？**

    - **エキスパートサポート**：コミュニティやチームの助けを借りて、販売後の問題や技術的な課題を解決します。
    - **学び＆共有**：ヒントやチュートリアルを交換してスキルを向上させましょう。
    - **独占的なプレビュー**：新製品の発表や先行プレビューに早期アクセスしましょう。
    - **特別割引**：最新製品の独占割引をお楽しみください。
    - **祭りのプロモーションとギフト**：ギフトや祝日のプロモーションに参加しましょう。

    👉 私たちと一緒に探索し、創造する準備はできていますか？[|link_sf_facebook|]をクリックして今すぐ参加しましょう！

.. _c201_iot_Bluetooth_environmental_monitor:

10. Bluetooth 環境モニター
==================================

DHT11 が空気を測り、ボードが 2 秒ごとに 2 つの値をスマートフォンへ送ります。これは
**データを逆方向に送る最初のプロジェクト** です。これまではスマートフォンが話し、
ボードが聞いていました。ここではボードが話します。


1. 回路を組み立てる
-----------------------------

.. note::

   モジュールは起動時に大きな電流を引きます。9V 電池または外部電源を R4 Minima
   の DC ジャックに必ず接続してください。


.. image:: ../img/10-Wiring_Bluetooth_environmental_monitor.png
   :width: 80%

* :ref:`cpn_uno`
* :ref:`cpn_espc201`
* :ref:`cpn_dht11`


2. コードを書き込む
-----------------------------

#. ``10-Bluetooth_environmental_monitor.ino`` を ``ultimate-sensor-kit\code\iot_project_espc201\bluetooth\10-Bluetooth_environmental_monitor`` から開きます。

   .. note::

      ライブラリマネージャーから **DHT sensor library**（Adafruit）と、その依存で
      ある **Adafruit Unified Sensor** をインストールしてください。

#. **Arduino UNO R4 Minima** と正しいポートを選び、**Upload** をクリックします。

#. シリアルモニターを **115200** で開きます。2 秒ごとに次のような行が出ます。

   .. code-block:: text

      Humidity: 45.00%  Temperature: 27.00 C
      Data to send: 27.00,45.00

   この行はスマートフォンがなくても出ます。Bluetooth の問題を探す前に、センサーが
   動いていることを確かめられるので便利です。


3. LightBlue でデータを見る
------------------------------

今回は何も書き込みません - **Subscribe** します。Subscribe は、スマートフォンが
その Characteristic を開いたまま、届くものを表示し続けるという意味です。

#. LightBlue を開き **Scan** をタップして **SunFounder-C2** に接続します。

#. サービス **0xA002** を展開し、Characteristic **C305** を開きます。

#. **Subscribe** をタップします。1 秒に 2 回、数値が自動で現れます。

   .. image:: ../img/ble_lightblue_subs.png
      :width: 80%

   .. note::

      形式は ``温度,湿度`` です。``27.00,45.00`` は 27 度、湿度 45% を意味します。
      カンマで区切っているので、受け取る側は 1 行を 2 つの数値に分けられます。

#. センサーに手をかざすと、数秒で湿度の値が上がります。

   .. note::

      何も届かないときは 2 点を確認してください。**C305**（C304 ではなく）を開いた
      か、シリアルモニターに ``Data to send:`` が出続けているか。シリアルモニターが
      静かなら、問題は Bluetooth ではなくセンサーか配線です。


4. コードの説明
-----------------------------

#. **センサーを読む**

   .. code-block:: arduino

      float humidity = dht.readHumidity();
      float temperature = dht.readTemperature();

      if (isnan(humidity) || isnan(temperature)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
      }

   ``isnan`` は「数値ではない（is not a number）」という意味です。正しく配線されて
   いない DHT11 はまさにこれを返すので、空の行をスマートフォンに送る前に処理を止め
   ます。

#. **1 行に 2 つの値**

   .. code-block:: arduino

      sensorData = String(temperature) + "," + String(humidity);
      bleSerial.println(sensorData);

   ``bleSerial.println`` はテキストと改行を書きます。``Serial.println`` と同じです。
   ``BLEStream`` はそれを 20 バイトずつに分け、それぞれを **C305 の Notification** と
   して送ります。だからスマートフォンは Subscribe する必要があります。

#. **2 秒のリズム**

   .. code-block:: arduino

      void loop() {
        delay(2000);
        ...
      }

   このスケッチは他にすることがないので、ここでは ``delay`` を使ってかまいません。
   Wi-Fi のプロジェクトでは、Blynk を常に動かす必要があるため避けました。Bluetooth に
   はそういう裏方の仕事がありません。

#. **なぜボードは頼まれずに送れるのか**

   BLE の Notification は、スマートフォンがその Characteristic を Subscribe している
   ときだけ流れます。スケッチのどこにも「誰か聞いているか」の判定はありません - 購読
   がなければデータは消えるだけです。だから LightBlue で **Subscribe** を押すまで何も
   見えないのです。
