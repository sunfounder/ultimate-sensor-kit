.. note::

    こんにちは、SunFounderのRaspberry Pi & Arduino & ESP32愛好家コミュニティへようこそ！Facebook上でRaspberry Pi、Arduino、ESP32についてもっと深く掘り下げ、他の愛好家と交流しましょう。

    **参加する理由は？**

    - **エキスパートサポート**：コミュニティやチームの助けを借りて、販売後の問題や技術的な課題を解決します。
    - **学び＆共有**：ヒントやチュートリアルを交換してスキルを向上させましょう。
    - **独占的なプレビュー**：新製品の発表や先行プレビューに早期アクセスしましょう。
    - **特別割引**：最新製品の独占割引をお楽しみください。
    - **祭りのプロモーションとギフト**：ギフトや祝日のプロモーションに参加しましょう。

    👉 私たちと一緒に探索し、創造する準備はできていますか？[|link_sf_facebook|]をクリックして今すぐ参加しましょう！

.. _c201_iot_Plant_monitor:

3. Blynk を使った植物モニター
========================================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../../_static/video/iot/03-iot_Plant_monitor.mp4"  type="video/mp4">
      お使いのブラウザは video タグに対応していません。
   </video>

このプロジェクトは植物を監視します。現在の温度、湿度、明るさ、土壌水分を測り、
Blynk に表示します。土壌水分に応じたコメントも表示します。

1. 回路を組み立てる
-----------------------------

.. note::

   モジュールは起動時に大きな電流を引きます。9V 電池または外部電源を R4 Minima
   の DC ジャックに必ず接続してください。

   **キットには複数のバージョンの DHT11 モジュールが入っている場合があります。お手
   元のモジュールに合わせて配線を確認してください。**


.. image:: ../img/03-Wiring_Plant_monitor_c201.png
   :width: 80%

.. image:: ../img/03-Wiring_Plant_monitor_new_c201.png
   :width: 80%


* :ref:`cpn_uno`
* :ref:`cpn_espc201`
* :ref:`cpn_dht11`
* :ref:`cpn_soil`


2. Blynk を設定する
-----------------------------

.. note::

    テンプレートとデバイスは :ref:`c201_iot_blynk_start` で一度作成済みです。どのプ
    ロジェクトも **同じ** テンプレートにデータストリームを追加するので、プロジェクト
    ごとに仮想ピンの範囲が分かれます。このプロジェクトは **V3** から **V6** を使いま
    す。

**このプロジェクトがクラウドに送るもの**

4 つの値があり、それぞれ型が重要です - 型が Blynk の表示方法を決めます。

* ``temperature`` - 小数なので **Double**。
* ``humidity`` - 小数なので **Double**。
* ``soil_moisture`` - ``dry`` / ``wet`` のような語なので **String**。
* ``led_status`` - ダッシュボードのランプの明るさ 0〜255 なので **Integer**。スケッ
  チは常に 255 を送り、変わるのは色だけです。

**データストリームを追加する**

#. **Developer Zone** -> **My Templates** を開き、**Ultimate Sensor Kit** をクリック
   します。

   .. image:: ../img/blynk_template.png
      :width: 80%

#. **Edit** をクリックしてテンプレートを開きます。

   .. image:: ../img/blynk_edit.png
      :width: 80%

#. **Datastreams** をクリックし、**Create New** を選びます。

   .. image:: ../img/blynk_new_data.png
      :width: 80%

#. 1 本目のデータストリームを作ります。

   * **DATASTREAM NAME**: ``temperature``
   * **DISPLAY NAME**: ``Temperature``
   * **VIRTUAL PIN**: ``V3``
   * **DATA TYPE**: **Integer**
   * **MIN** ``-100``, **MAX** ``100``

   .. image:: ../img/blynk_plant_data_tem.png
      :width: 80%

#. **UNITS** を ``Celsius`` にします。

   .. image:: ../img/blynk_plant_data_unit.png
      :width: 80%

#. 残り 3 本も同じ要領で作ります。

   .. list-table::
      :header-rows: 1
      :widths: 12 26 14 20 28

      * - ピン
        - 名前
        - 型
        - 最小 / 最大
        - 単位
      * - V4
        - ``humidity``
        - Double
        - 0 / 100
        - Percent
      * - V5
        - ``soil_moisture``
        - String
        - -
        - -
      * - V6
        - ``led_status``
        - Integer
        - 0 / 255
        - -

   .. image:: ../img/blynk_plant_datastreams.png
      :width: 80%

**Web ダッシュボードを追加する**

#. **Dashboard** をクリックし、**Add Widget** を選びます。

   .. image:: ../img/blynk_dashboard.png
      :width: 80%

#. **Gauge** ウィジェットをダッシュボードにドラッグします。

   .. image:: ../img/blynk_dashboard_gauge.png
      :width: 80%

#. **Gauge** の右上の三点メニューから **Settings** を選びます。

   * **Datastream** を ``Temperature (V3)`` に設定します。

   .. image:: ../img/blynk_plant_gauge_set.png
      :width: 80%

#. 同じ要領で **Gauge** をもう 1 つ、**Label** を 1 つ、**LED** を 1 つドラッグし、
   次のように割り当てます。

   .. list-table::
      :header-rows: 1
      :widths: 26 40 34

      * - ウィジェット
        - データストリーム
        - 表示内容
      * - Gauge
        - ``Humidity (V4)``
        - 空気の湿り具合
      * - Label
        - ``Soil Moisture (V5)``
        - ``dry`` または ``wet``
      * - LED
        - ``Led Status (V6)``
        - ダッシュボード上の状態ランプ。土壌水分が適正なら緑、そうでなければ赤

   .. image:: ../img/blynk_plant_widgets.png
      :width: 80%

   .. note::

      **LED** ウィジェットは **ダッシュボード上のランプ** です。スケッチは常に最大
      輝度の ``255`` を書き、色だけを変えます。土壌水分が適正なら緑、濡れすぎ・乾きす
      ぎなら赤です。部屋の反対側からでも植物の状態が分かります。

#. **Save** をクリックします。

   .. image:: ../img/blynk_save.png
      :width: 40%


3. コードを実行する
-----------------------------

#. ``03-Plant_monitor.ino`` を ``ultimate-sensor-kit\code\iot_project_espc201\wifi\03-Plant_monitor`` から開くか、コードを **Arduino IDE** にコピーします。

#. Blynk の 3 行は :ref:`c201_iot_blynk_start` でコピー済みです。このキットのどの
   プロジェクトも同じデバイスを使うので、変更は不要です - プロジェクト固有なのは下
   の Wi-Fi 設定だけです。

   .. code-block:: arduino

      #define BLYNK_TEMPLATE_ID   "TMPLxxxxxx"
      #define BLYNK_TEMPLATE_NAME "Ultimate Sensor Kit"
      #define BLYNK_AUTH_TOKEN    "YourAuthToken"

#. 使用する Wi-Fi の ``ssid`` と ``password`` も入力します。

   .. code-block:: arduino

    char ssid[] = "your_ssid";
    char pass[] = "your_password";

#. 正しいボードとポートを選んで **Upload** をクリックします。

#. シリアルモニターを **115200** で開き、接続成功のようなメッセージが出るまで待ちま
   す。

   .. image:: ../img/blynk_plant_serial.png
      :width: 80%

#. 同じ値が Blynk のダッシュボードにも表示されます。

   .. image:: ../img/blynk_plant_dashboard.png
      :width: 80%


4. コードの説明
-----------------------------

#. **Blynk アカウントとライブラリ**

   最初の 3 行は、このボードがどの Blynk デバイスに属するかを示します。デバイス
   ページの内容で、このキットのどのプロジェクトでも同じです。

   .. code-block:: arduino

      #define BLYNK_TEMPLATE_ID   "TMPL2Ms3WVki8"
      #define BLYNK_TEMPLATE_NAME "Ultimate Sensor Kit"
      #define BLYNK_AUTH_TOKEN    "lHSd4Q5pXP7YKUovVfPZYZqC0UHVORY6"

      #define BLYNK_PRINT Serial   // Blynk のログをシリアルモニターに出す

      #include <ESP8266_Lib.h>               // AT コマンドを送る
      #include <BlynkSimpleShieldEsp8266.h>  // その上で動く Blynk

#. **モジュールと通信するシリアルポート**

   ESPC2-01 はモデムとして動作します。スケッチが AT コマンドを送ります。R4 では
   D0/D1、つまり ``Serial1`` につながっており、ハードウェアポートなので 115200 で
   もビット化けしません。

   .. code-block:: arduino

      #define EspSerial Serial1
      #define ESP8266_BAUD 115200
      ESP8266 wifi(&EspSerial);

   ``espModuleInit()`` はモジュールの起動完了を待ち、``ATE0`` でエコーを切ります。
   これがないと起動ログとエコーされたコマンドが応答に混ざり、Blynk が読めません。

#. **DHT11 センサー**

   .. code-block:: arduino

      #include <DHT.h>
      #define DHTPIN 8
      #define DHTTYPE DHT11
      DHT dht(DHTPIN, DHTTYPE);

      float temperature;
      float humidity;

   DHT11 は整数の度と整数の % しか返さないので、``float`` はセンサー以上の精度です
   が、コードが簡単になり、後で DHT22 に替えても同じ書き方で済みます。

#. **土壌水分センサーと 2 つのしきい値**

   .. code-block:: arduino

      #define wetSoil 320
      #define drySoil 400

      const int moistureSensorPin = A0;
      int moisture;
      String soilStatus;

   プローブは 0〜1023 のアナログ値を返し、**土が濡れているほど数値は小さくなりま
   す**。だから「``wetSoil`` 未満 = 濡れすぎ」と判定しています。

   .. note::

      この 2 つの数値はご自分で測ってください。プローブを水の入ったグラスに挿して値
      を読み、それがおおよその ``wetSoil`` です。次に乾いた土で読み、それが
      ``drySoil`` です。初期値 320 / 400 は開発者の土に合わせた値でしかありません。

#. **setup()**

   .. code-block:: arduino

      void setup() {
        Serial.begin(115200);
        EspSerial.begin(ESP8266_BAUD);
        delay(10);

        espModuleInit();
        Blynk.config(wifi, BLYNK_AUTH_TOKEN);
        Blynk.connectWiFi(ssid, pass);

        timer.setInterval(5000L, myTimerEvent);

        dht.begin();
      }

   ``timer.setInterval(5000L, myTimerEvent)`` は 5 秒に 1 回測ります。DHT11 はもとも
   と 1 秒に 1 回以上は測れませんし、植物はそれ以上速く変化しません。

#. **loop()**

   .. code-block:: arduino

      void loop() {
        Blynk.run();
        timer.run();
      }

   ``Blynk.run()`` が接続を保ち、``timer.run()`` が測定を実行します。ここでブロッ
   クしてはいけません。クラウドがデバイスを切断します。

#. **sendData() - 測って、判断して、報告する**

   .. code-block:: arduino

      void sendData() {
        humidity = dht.readHumidity();
        temperature = dht.readTemperature();

        if (isnan(humidity) || isnan(temperature)) {
          Serial.println(F("Failed to read from DHT sensor!"));
          return;                                  // この回は飛ばす
        }

        moisture = analogRead(moistureSensorPin);

        String color;
        if (moisture < wetSoil) {
          soilStatus = "Soil is too wet";
          color = "#D3435C";
        } else if (moisture >= wetSoil && moisture < drySoil) {
          soilStatus = "Soil moisture is perfect";
          color = "#00FF00";
        } else {
          soilStatus = "Soil is too dry - time to water!";
          color = "#D3435C";
        }

        Blynk.virtualWrite(V3, temperature);
        Blynk.virtualWrite(V4, humidity);
        Blynk.virtualWrite(V5, soilStatus);
        Blynk.virtualWrite(V6, 255);
        Blynk.setProperty(V6, "color", color);
      }

   * DHT の読み取りに失敗したときの ``return`` は、ダッシュボードの値を ``nan`` で
     上書きせず、直前の正常値のまま残します。
   * ``Blynk.virtualWrite(V3, ...)`` などが 4 つの値をデータストリームに送ります。
   * ``Blynk.virtualWrite(V6, 255)`` は **ダッシュボードの LED** を最大に点け、
     ``Blynk.setProperty(V6, "color", color)`` が緑か赤に塗ります。ボード上の **L**
     と書かれた実物の LED はこのプロジェクトでは使いません。

#. **printData()**

   .. code-block:: arduino

      void printData() {
        Serial.print(F("Humidity: "));
        Serial.print(humidity);
        Serial.print(F("%  Temperature: "));
        Serial.print(temperature);
        Serial.println(F("°C "));
        Serial.print("(");
        Serial.print(moisture);
        Serial.print(") ");
        Serial.println(soilStatus);
      }

   同じ数値をシリアルモニターに出します。スマートフォンの表示がおかしいとき、セン
   サーが悪いのかクラウドが悪いのかをここで切り分けられます。
