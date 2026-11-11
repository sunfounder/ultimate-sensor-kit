.. note::

    こんにちは、SunFounderのRaspberry Pi & Arduino & ESP32愛好家コミュニティへようこそ！Facebook上でRaspberry Pi、Arduino、ESP32についてもっと深く掘り下げ、他の愛好家と交流しましょう。

    **参加する理由は？**

    - **エキスパートサポート**：コミュニティやチームの助けを借りて、販売後の問題や技術的な課題を解決します。
    - **学び＆共有**：ヒントやチュートリアルを交換してスキルを向上させましょう。
    - **独占的なプレビュー**：新製品の発表や先行プレビューに早期アクセスしましょう。
    - **特別割引**：最新製品の独占割引をお楽しみください。
    - **祭りのプロモーションとギフト**：ギフトや祝日のプロモーションに参加しましょう。

    👉 私たちと一緒に探索し、創造する準備はできていますか？[|link_sf_facebook|]をクリックして今すぐ参加しましょう！

.. _c201_iot_Auto_watering_system:

7. Blynk を使った自動給水システム
===================================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../../_static/video/iot/07-iot_Auto_watering_system.mp4"  type="video/mp4">
      お使いのブラウザは video タグに対応していません。
   </video>

植木鉢に土壌水分プローブを挿し、コップの水に小さなポンプを入れます。ボードは土の
湿り具合を報告し、あなたが許可すれば、植物が乾く前に自分でポンプを回します。

スマートフォンからは、水分を眺め、スライダーで「どこまで乾いたら給水するか」を決
め、自動で水をやってよいかどうかを切り替えられます。

1. 回路を組み立てる
-----------------------------

.. note::

   モジュールは起動時に大きな電流を引きます。9V 電池または外部電源を R4 Minima
   の DC ジャックに必ず接続してください。


.. image:: ../img/07-Wiring_Auto_watering_c201.png
   :width: 80%


* :ref:`cpn_uno`
* :ref:`cpn_espc201`
* :ref:`cpn_soil`
* :ref:`cpn_pump`


2. Blynk を設定する
-----------------------------

.. note::

    テンプレートとデバイスは :ref:`c201_iot_blynk_start` で一度作成済みです。どのプ
    ロジェクトも **同じ** テンプレートにデータストリームを追加するので、プロジェクト
    ごとに仮想ピンの範囲が分かれます。このプロジェクトは **V8** から **V10** を使いま
    す。

**このプロジェクトがクラウドに送るもの**

3 つの値があり、役割が異なります。

* ``moisture_percentage`` - ボードが書き込みます。土がどれだけ湿っているか分かりま
  す。
* ``water_threshold`` - スライダーからあなたが書き込みます。ポンプが動く下限値です。
* ``auto_mode`` - ボードが自分でポンプを始めてよいかを決めるスイッチです。

**データストリームを追加する**

#. **Developer Zone** -> **My Templates** を開き、**Ultimate Sensor Kit** をクリック
   します。

   .. image:: ../img/blynk_template.png
      :width: 80%

#. **Edit** をクリックしてテンプレートを開きます。

   .. image:: ../img/blynk_edit.png
      :width: 80%

#. **Datastreams** をクリックし、**Create New** を選びます。

#. 1 本目を **Virtual Pin** データストリームとして作ります。``V8`` には何も配線しま
   せん。仮想ピンはクラウドの中だけに存在し、ボードとアプリが共有する私書箱のような
   ものです。

   * **DATASTREAM NAME**: ``moisture_percentage``
   * **DISPLAY NAME**: ``Moisture Percentage``
   * **VIRTUAL PIN**: ``V8``
   * **DATA TYPE**: **Double**
   * **MIN** ``0``, **MAX** ``100``

   .. image:: ../img/blynk_water_data_mois.png
      :width: 80%

#. **UNITS** を ``Percentage`` にします。

   .. image:: ../img/blynk_water_data_unit.png
      :width: 80%

#. 残りの **2 本** も同じ要領で作ります。**Create New** をもう 2 回クリックします。

   .. list-table::
      :header-rows: 1
      :widths: 10 26 24 14 16 10

      * - ピン
        - データストリーム名
        - 表示名
        - 型
        - 最小 / 最大
        - 単位
      * - V9
        - ``water_threshold``
        - ``Water Threshold``
        - **Double**
        - 0 / 100
        - Percent
      * - V10
        - ``auto_mode``
        - ``Auto Mode``
        - **Integer**
        - 0 / 1
        - None

   .. image:: ../img/blynk_water_datastreams.png
      :width: 80%

**Web ダッシュボードを追加する**

#. **Dashboard** をクリックし、**Add Widget** を選びます。

   .. image:: ../img/blynk_dashboard.png
      :width: 80%

#. **Gauge** ウィジェットをダッシュボードにドラッグします。

   .. image:: ../img/blynk_dashboard_gauge.png
      :width: 80%

#. **Gauge** の右上の三点メニューから **Settings** を選びます。

   * **Datastream** を ``Moisture Percentage (V8)`` に設定します。

   .. image:: ../img/blynk_water_gauge_set.png
      :width: 80%

#. 同じ要領で **Slider** と **Switch** もドラッグし、次のように割り当てます。

   .. list-table::
      :header-rows: 1
      :widths: 26 40 34

      * - ウィジェット
        - データストリーム
        - 用途
      * - Slider
        - ``Water Threshold (V9)``
        - 給水を始めるしきい値を決める
      * - Switch
        - ``Auto Mode (V10)``
        - ボードが自分でポンプを動かすことを許可する

   .. image:: ../img/blynk_water_widgets.png
      :width: 80%

   .. note::

      **auto_mode** が OFF のときは、スライダーが何を言っていてもポンプは動きませ
      ん。これが安全な初期状態です。まずは値を眺めてから、キットに水やりを任せてくだ
      さい。

#. **Save** をクリックします。

   .. image:: ../img/blynk_save.png
      :width: 40%


3. コードを実行する
-----------------------------

#. ``07-Auto_watering_system.ino`` を ``ultimate-sensor-kit\code\iot_project_espc201\wifi\07-Auto_watering_system`` から開くか、コードを **Arduino IDE** にコピーします。

#. Blynk の 3 行は入門章でコピーしたものです - そのままにしてください。

   .. code-block:: arduino

      #define BLYNK_TEMPLATE_ID   "TMPLxxxxxx"
      #define BLYNK_TEMPLATE_NAME "Ultimate Sensor Kit"
      #define BLYNK_AUTH_TOKEN    "YourAuthToken"

#. 自分の Wi-Fi ネットワークの名前とパスワードを入力します。

   .. code-block:: arduino

      char ssid[] = "your_ssid";
      char pass[] = "your_password";

#. **Arduino UNO R4 Minima** と正しいポートを選び、**Upload** をクリックします。

#. シリアルモニターを **115200** で開きます。10 秒ごとに土壌水分を報告します。

   .. code-block:: text

      -----------------------------
      Update soil moisture data ...
      sensorValue:453  moisturePercentage:32.16

   ``sensorValue`` の後の数値がプローブの **生の値** です。パーセントはまだ校正して
   いないので、いまは無視してください。

#. プローブは個体差も土も違うので、校正します。

   #. プローブを **空気中**（乾燥）に置き、``sensorValue`` を記録します（例: ``535``）。
   #. プローブを **水の入ったコップ** に入れ、2 つ目の ``sensorValue`` を記録します
      （例: ``280``）。
   #. 両方の数値をスケッチに入れます。

      .. code-block:: arduino

         const float moistureInAir = 535;     // 乾燥した空気中の値
         const float moistureInWater = 280;   // 水中の値

   #. もう一度書き込みます。これでパーセントが意味を持ちます。0% が空気と同じ乾き、
      100% が水と同じ湿りです。

   .. note::

      プローブは **乾くと大きく、濡れると小さく** なります。だから式の中で 2 つの値
      がこの順番で現れます。校正を省いてもパーセントは表示されますが、湿った土で 0%
      になったり、乾いた土で 100% になったりします。

   .. image:: ../img/blynk_water_serial.png
      :width: 80%

#. ダッシュボードで **スライダー** を現在の水分より高い値（たとえば 40）にし、
   **Auto Mode** を ON にします。35 秒以内にポンプが動き出し、ゲージが上がり始めます。

   .. note::

      ポンプは **Auto Mode** が ON のときだけ動きます。スイッチを切っておけば、いく
      らでも値を眺められ、ポンプは静かなままです。

   .. image:: ../img/blynk_water_dashboard.png
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

#. **モジュールと通信するシリアルポート**

   ESPC2-01 はモデムとして動作し、スケッチが D0/D1（``Serial1``）で AT コマンドを送
   ります。ハードウェアポートなので 115200 でもビット化けしません。``espModuleInit()``
   は起動完了を待ってから ``ATE0`` を送り、応答にコマンドのコピーが混ざらないようにし
   ます。

   .. code-block:: arduino

      #define EspSerial Serial1
      #define ESP8266_BAUD 115200
      ESP8266 wifi(&EspSerial);

#. **ポンプ**

   .. code-block:: arduino

      const int pump1A = 9;
      const int pump1B = 10;
      bool pumpStatus = 0;

   ポンプは **L9110** ドライバー経由で動きます。``1A`` に HIGH を与えるとポンプが回
   り、``1B`` は LOW のままです。``1B`` はモーターを逆回転させるときだけ必要です。リ
   レーでも単純なトランジスタでも同じように動きます - ピン 1 本、オンかオフかです。

#. **プローブと 2 つの校正点**

   .. code-block:: arduino

      const float moistureInAir = 535;
      const float moistureInWater = 280;
      const int sensorPin = A0;

   プローブは生の数値を返し、しかも **土が濡れているほど数値は小さく** なります。ス
   ケッチはそれをパーセントに変換します。

   .. code-block:: arduino

      moisturePercentage = 1 - (sensorValue - moistureInWater) / (moistureInAir - moistureInWater);

   2 つの校正値により、「水中」が ``1.0``、「空気中」が ``0.0`` に対応し、その間は比例
   します。

#. **2 つのタイマー、2 つの役割**

   .. code-block:: arduino

      timer.setInterval(10000L, updateDataTimer);   // 10 秒ごとに報告
      timer.setInterval(35000L, autoWaterTimer);    // 35 秒ごとにポンプを確認

   測るのは安い処理なので頻繁に行います。ポンプを動かすのは安くないので、確認はゆっ
   くり行います。そして ``delay()`` は使いません。Blynk の接続を止めないためです。

#. **BLYNK_CONNECTED() と 2 つの書き込み**

   .. code-block:: arduino

      BLYNK_CONNECTED() {
        Blynk.syncVirtual(V9);
        Blynk.syncVirtual(V10);
      }

      BLYNK_WRITE(V9)  { waterThreshold = param.asInt(); }
      BLYNK_WRITE(V10) { autoMode       = param.asInt(); }

   ``BLYNK_CONNECTED()`` は停電後を含むすべての接続で実行され、スライダーとスイッチ
   の値をサーバーに問い合わせます。これがないと、再起動したボードはしきい値 ``0`` で
   水をやることになり、つまり一度もやりません。

#. **sendData() は報告、autoWater() は行動**

   .. code-block:: arduino

      void sendData() {
        sensorValue = analogRead(sensorPin);
        moisturePercentage = 1 - (sensorValue - moistureInWater) / (moistureInAir - moistureInWater);
        Blynk.virtualWrite(V8, moisturePercentage * 100);
      }

      void autoWater() {
        if (autoMode == 1 && moisturePercentage * 100 < waterThreshold) {
          // しばらくポンプを回す
        }
      }

   ``sendData()`` は読んで報告するだけで、ポンプには触れません。ポンプを動かすのは
   ``autoWater()`` だけで、**両方** の条件が必要です。自動モードが ON で、土がスライ
   ダーの値より乾いていること。
