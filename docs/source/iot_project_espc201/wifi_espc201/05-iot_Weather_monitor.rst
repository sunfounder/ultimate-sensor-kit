.. note::

    こんにちは、SunFounderのRaspberry Pi & Arduino & ESP32愛好家コミュニティへようこそ！Facebook上でRaspberry Pi、Arduino、ESP32についてもっと深く掘り下げ、他の愛好家と交流しましょう。

    **参加する理由は？**

    - **エキスパートサポート**：コミュニティやチームの助けを借りて、販売後の問題や技術的な課題を解決します。
    - **学び＆共有**：ヒントやチュートリアルを交換してスキルを向上させましょう。
    - **独占的なプレビュー**：新製品の発表や先行プレビューに早期アクセスしましょう。
    - **特別割引**：最新製品の独占割引をお楽しみください。
    - **祭りのプロモーションとギフト**：ギフトや祝日のプロモーションに参加しましょう。

    👉 私たちと一緒に探索し、創造する準備はできていますか？[|link_sf_facebook|]をクリックして今すぐ参加しましょう！

.. _c201_iot_Weather_monitor:

5. ThingSpeak を使った気象モニター
====================================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../../_static/video/iot/05-iot_Weather_monitor.mp4"  type="video/mp4">
      お使いのブラウザは video タグに対応していません。
   </video>

このプロジェクトは気圧センサーで温度と気圧を測り、一定間隔で ESPC2-01 モジュールと
Wi-Fi 経由で ThingSpeak クラウドに送ります。


1. 回路を組み立てる
-----------------------------

.. note::

   モジュールは起動時に大きな電流を引きます。9V 電池または外部電源を R4 Minima
   の DC ジャックに必ず接続してください。


.. image:: ../img/05-Wiring_Weather_monitor_c201.png
   :width: 80%


* :ref:`cpn_uno`
* :ref:`cpn_espc201`
* :ref:`cpn_bmp280`


2. ThingSpeak を設定する
-----------------------------

|link_thingspeak| ™ は、クラウド上のライブデータストリームを集約・可視化・分析でき
る IoT 分析プラットフォームです。デバイスが送ったデータを即座にグラフ化します。
ThingSpeak 内で MATLAB® のコードが動くため、入ってくるデータをオンラインで分析・処
理することもできます。解析が必要な IoT システムの試作や実証によく使われます。

.. image:: https://thingspeak.com/assets/Signup_TSP_ML_image-3d581d644f5eb1ff9f4999fc55ad04e2530ee7f54be98323d7bb453032353750.svg
   :width: 80%

.. raw:: html
    
    <br/>  

**2.1 ThingSpeak アカウントを作る**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

まず ThingSpeak のアカウントが必要です。MATLAB との連携以降、MathWorks のアカウント
で |link_thingspeak| にログインできます。

お持ちでない場合は MathWorks でアカウントを作成し、ThingSpeak にログインしてください。

.. image:: ../img/new/05-thingspeak_signup_shadow.png
   :width: 70%


**2.2 チャネルを作る**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

ログイン後、**Channels** > **My Channels** と進み、**New Channel** をクリックして
データを保存するチャネルを作ります。

.. image:: ../img/new/05-thingspeak_channel_1_shadow.png
   :width: 80%

このプロジェクトでは "**Weather Monitor**" というチャネルを作り、フィールドを 2 つ用
意します。**Field 1** が "**Temperature**"、**Field 2** が "**Atmospheric Pressure**"
です。

.. image:: ../img/new/05-thingspeak_channel_2_shadow.png
   :width: 80%

.. raw:: html
    
    <br/>  


3. コードを実行する
-----------------------------

#. ``05-Weather_monitor.ino`` を ``ultimate-sensor-kit\code\iot_project_espc201\wifi\05-Weather_monitor`` から開くか、コードを **Arduino IDE** にコピーします。

   .. note::

      スケッチには **Adafruit BMP280** ライブラリが必要です。ライブラリマネー
      ジャーで ``Adafruit BMP280`` を検索してインストールしてください。

#. 自分の Wi-Fi ネットワークの名前とパスワードを入力します。

   .. code-block:: arduino

      String mySSID = "your_ssid";
      String myPWD  = "your_password";

#. ThingSpeak チャネルの **Write API Key** を ``myAPI`` に貼り付けます。

   .. code-block:: arduino

      String myAPI = "xxxxxxxxxxxxxxx";

   .. image:: ../img/new/05-thingspeak_api_shadow.png
      :width: 80%

   .. note::

      チャネルの **Write** キーを使ってください。Read キーでも User キーでもありませ
      ん。このキーは公開しないでください。持っていれば誰でもあなたのチャネルにデータ
      を送れます。

#. **Arduino UNO R4 Minima** と正しいポートを選び、**Upload** をクリックします。

#. シリアルモニターを **115200** で開きます。数秒後に次のように表示されます。

   .. code-block:: text

      === Weather Monitor (ThingSpeak) ===
      module is ready
      joining Wi-Fi ... connected
      BMP280 is ready

   その後 20 秒ごとに:

   .. code-block:: text

      > AT+CIPSTART="TCP","api.thingspeak.com",80
      > AT+CIPSEND=96
      update sent to ThingSpeak
      Temperature: 27.31 C.  Pressure: 100842.00 Pa

   .. note::

      ``Could not find a BMP280, check the wiring and the address`` と出たら、I2C ス
      キャナーを実行するか、もう一方のアドレスを試してください。``0x76`` ではなく
      ``0x77`` で応答するモジュールもあります。スケッチは両方試すので、このメッセージ
      はどちらも応答しなかったという意味です - SDA、SCL、VCC、GND を確認してくださ
      い。

   .. image:: ../img/new/05-ready_1_shadow.png
      :width: 80%

   .. image:: ../img/new/05-ready_2_shadow.png
      :width: 80%

#. ThingSpeak のチャネルを開きます。20 秒ごとにグラフへ新しい点が追加されます。

   .. note::

      無料の ThingSpeak チャネルは 15 秒に 1 回の更新を受け付けます。スケッチは 20 秒
      待つので、点を失うことはありません。


4. コードの説明
-----------------------------

このプロジェクトは Blynk を使いません。ボードは AT コマンド越しの平文 HTTP で
ThingSpeak と話します。ブラウザが Web ページを要求するのと同じ仕組みなので、後から
どのブラウザでも値を確認できます。

#. **入力する必要があるもの**

   .. code-block:: arduino

      String mySSID = "your_ssid";
      String myPWD  = "your_password";
      String myAPI  = "xxxxxxxxxxxxxxx";
      String myHOST = "api.thingspeak.com";
      String myPORT = "80";

   ホストとポートは変わりません。個別なのは API キーだけで、どのチャネルに値が属す
   るかを ThingSpeak に伝えます。

#. **モジュールと通信するシリアルポート**

   ESPC2-01 はモデムとして動作し、スケッチが D0/D1（``Serial1``）で AT コマンドを送
   ります。ハードウェアポートなので 115200 でもビット化けしません。

   .. code-block:: arduino

      #define EspSerial Serial1

   ``espModuleInit()`` はモジュールの起動完了を待ってから ``ATE0`` でエコーを切りま
   す。これがないと起動ログとエコーが応答に混ざります。

#. **at() - 時間制限付きの AT コマンド 1 本**

   .. code-block:: arduino

      String at(const String& cmd, unsigned long waitMs, const char* okMark, const char* errMark) {
        while (EspSerial.available()) EspSerial.read();
        EspSerial.print(cmd);
        EspSerial.print("\r\n");

        unsigned long t0 = millis();
        String r;
        while (millis() - t0 < waitMs) {
          while (EspSerial.available() && r.length() < 512) r += (char)EspSerial.read();
          if (okMark && r.indexOf(okMark) >= 0) break;
          if (errMark && r.indexOf(errMark) >= 0) break;
        }
        return r;
      }

   すべてのコマンドがこの関数を通ります。期待した応答が来た時点で止まり、**必ず戻
   る** ので、``OK`` がなくてもボードが固まることはありません。

#. **joinWiFi()**

   .. code-block:: arduino

      at("AT+CWMODE=1", 1500, "OK", "ERROR");
      String r = at("AT+CWJAP=\"" + mySSID + "\",\"" + myPWD + "\"", 20000,
                   "WIFI GOT IP", "FAIL");

   ``AT+CWJAP`` は数秒かかります。モジュールがアクセスポイントを見つけ、鍵を交換し、
   IP アドレスを取得する必要があるからです。だから 20 秒与え、他のコマンドは 1 秒で
   済ませています。

#. **BMP280**

   .. code-block:: arduino

      if (!bmp.begin(BMP280_ADDRESS)) {
        if (!bmp.begin(0x77)) {
          ...   // 諦める。測るものが無い
        }
      }

   このチップは SDO ピンの結線によって ``0x76`` か ``0x77`` で応答するので、スケッチ
   は諦める前に両方を試します。

#. **loop() - delay() を使わないタイマー**

   .. code-block:: arduino

      if (millis() - lastConnectionTime > postingInterval) {
        sendData();
      }

   ``millis()`` は電源投入からのミリ秒を数えます。最後の更新時刻と比べるのは、プログ
   ラムを **止めない** 遅延です。ボードは他のことに使えます。無料の ThingSpeak チャネ
   ルは 15 秒に 1 回の更新を受け付けるので、20 秒は安全な間隔です。

#. **sendData() - リクエストを組み立てて送る**

   .. code-block:: arduino

      String req = "GET /update?api_key=" + myAPI;
      req += "&field1=" + String(temperature);
      req += "&field2=" + String(pressure);
      req += " HTTP/1.1\r\nHost: api.thingspeak.com\r\nConnection: close\r\n\r\n";

      at("AT+CIPMUX=0", 1000, "OK", "ERROR");
      at("AT+CIPSTART=\"TCP\",\"" + myHOST + "\"," + myPORT, 5000, "OK", "ERROR");

      EspSerial.print("AT+CIPSEND=");
      EspSerial.print(req.length());
      ...
      EspSerial.print(req);

   AT コマンド 3 本で完了します。

   * ``AT+CIPMUX=0`` - 同時接続は 1 本。
   * ``AT+CIPSTART`` - ``api.thingspeak.com:80`` への TCP 接続を開く。
   * ``AT+CIPSEND=<長さ>`` - モジュールが ``>`` を返し、その後にリクエストを送りま
     す。長さは ``req`` の **正確な** 文字数でなければならず、だからスケッチは推測せ
     ず ``req.length()`` を測ります。

   ``field1`` と ``field2`` はチャネルの 2 つの列です。ThingSpeak でどんな名前を付け
   ていても、値はその順番で入ります。
