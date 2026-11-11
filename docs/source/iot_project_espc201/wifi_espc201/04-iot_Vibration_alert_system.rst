.. note::

    こんにちは、SunFounderのRaspberry Pi & Arduino & ESP32愛好家コミュニティへようこそ！Facebook上でRaspberry Pi、Arduino、ESP32についてもっと深く掘り下げ、他の愛好家と交流しましょう。

    **参加する理由は？**

    - **エキスパートサポート**：コミュニティやチームの助けを借りて、販売後の問題や技術的な課題を解決します。
    - **学び＆共有**：ヒントやチュートリアルを交換してスキルを向上させましょう。
    - **独占的なプレビュー**：新製品の発表や先行プレビューに早期アクセスしましょう。
    - **特別割引**：最新製品の独占割引をお楽しみください。
    - **祭りのプロモーションとギフト**：ギフトや祝日のプロモーションに参加しましょう。

    👉 私たちと一緒に探索し、創造する準備はできていますか？[|link_sf_facebook|]をクリックして今すぐ参加しましょう！

.. _c201_iot_Vibration_alert_system:

4. IFTTT を使った振動警報システム
========================================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../../_static/video/iot/04-iot_Vibration_alert_system.mp4"  type="video/mp4">
      お使いのブラウザは video タグに対応していません。
   </video>

机の上に振動スイッチ（SW-420）を置きます。机を叩くと、ボードが IFTTT に知らせ、
IFTTT があなたにメールを送ります。

このプロジェクトは **Blynk を使いません**。HTTP リクエストを IFTTT に直接送るので、
モジュールが ``AT+CIPSEND`` のような AT コマンドで実際に何をしているかが見えます。
ブラウザが Web ページを開くときと同じことです。

受信箱が溢れないよう、2 つの警報は常に最低 **2 分** 離れています。


1. 回路を組み立てる
-----------------------------

.. note::

   モジュールは起動時に大きな電流を引きます。9V 電池または外部電源を R4 Minima
   の DC ジャックに必ず接続してください。


   .. image:: ../img/04-Wiring_Vibration_alert_system_c201.png
      :width: 80%


* :ref:`cpn_uno`
* :ref:`cpn_espc201`
* :ref:`cpn_vibration`


2. IFTTT を設定する
-----------------------------

|link_ifttt| は、アプリ同士をシンプルなルールでつなぐ無料サービスです。

> **If This が起きたら、Then That が起きる。**

ここでは 2 つの部分が必要です。

* **If This** - 誰かがセンサーを揺らす。IFTTT がボードから呼び出せる専用の Web アド
  レスを発行します。
* **Then That** - メールを送る。これがアクションです。


   .. image:: ../img/04-ifttt_intro.png
      :width: 80%


**2.1 IFTTT に登録する**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#. ブラウザで https://ifttt.com を開き、**Start building** をクリックします。
   フォームを入力してアカウントを作ります。

   .. image:: ../img/04-ifttt_signup.png
      :width: 80%

#. **start building** をクリックします。

   .. image:: ../img/ifttt_start_building.png
      :width: 80%

#. **Classic** モードを選びます。

   .. image:: ../img/ifttt_choose_classic.png
      :width: 80%


**2.2 If This - トリガー**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#. **If This** の横の **Add** をクリックします。

   .. image:: ../img/04-ifttt_create_applet_2_shadow.png
      :width: 80%

#. **webhook** を検索し、**Webhooks** をクリックします。

   .. image:: ../img/04-ifttt_create_applet_3_shadow.png
      :width: 80%

#. **Receive a web request** をクリックします。これがボードの呼び出すサービスです。

   .. image:: ../img/04-ifttt_create_applet_4_shadow.png
      :width: 80%

#. **Event Name** を **vibration_detected** にし、**Create trigger** をクリックします。

   .. note::

      この名前はアドレスの一部になるので、スケッチの ``URL`` と一致していなければな
      りません。ここで別の名前にしたら、スケッチ側も変えてください。

   .. image:: ../img/04-ifttt_create_applet_5_shadow.png
      :width: 80%


**2.3 Then That - アクション**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#. **Then That** の横の **Add** をクリックしてアクションを追加します。

   .. image:: ../img/04-ifttt_create_applet_6_shadow.png
      :width: 80%

#. **email** を検索し、**Email** をクリックします。

   .. image:: ../img/04-ifttt_create_applet_7_shadow.png
      :width: 80%

#. **Send me an email** をクリックします。

   .. image:: ../img/04-ifttt_create_applet_8_shadow.png
      :width: 80%

#. メールの件名と本文を書きます。

   例:

   * **Subject**: ``Detected vibration!!!``
   * **Body**: ``Detected vibration, please confirm the situation promptly! {{OccurredAt}}``

   ``{{OccurredAt}}`` は IFTTT がイベント発生時刻に置き換えます。翌朝メールを見ると
   きに便利です。

   .. image:: ../img/04-ifttt_create_applet_9_shadow.png
      :width: 80%

#. 以下の画面に従ってウィザードを完了します。

   .. image:: ../img/04-ifttt_create_applet_10_shadow.png
      :width: 80%

   .. image:: ../img/04-ifttt_create_applet_11_shadow.png
      :width: 80%


3. コードを実行する
-----------------------------

#. ``04-Vibration_alert_system.ino`` を ``ultimate-sensor-kit\code\iot_project_espc201\wifi\04-Vibration_alert_system`` から開くか、コードを **Arduino IDE** にコピーします。

#. 自分の Wi-Fi ネットワークの名前とパスワードを入力します。

   .. code-block:: arduino

      String mySSID = "your_ssid";
      String myPWD  = "your_password";

#. IFTTT の **My Applets** ページを開き、作成したアプレットをクリックします。

   .. image:: ../img/04_ifttt_my_applets.png
      :width: 80%

#. Webhook の URL をコピーします。

   .. image:: ../img/04_ifttt_webhook_url.png
      :width: 60%

#. IFTTT が表示したアドレスを **https:// も含めて丸ごと** ``URL`` に貼り付けます。

   .. code-block:: arduino

      String URL = "https://maker.ifttt.com/trigger/vibration_detected/with/key/xxxxxxxxxxxxxxxxxx";

   何も切り取る必要はありません。モジュールはポート 80 への平文 TCP で通信するため、
   スケッチは送信前にホスト名より後ろの部分だけを使います。

#. **Arduino UNO R4 Minima** と正しいポートを選び、**Upload** をクリックします。

#. シリアルモニターを **115200** で開きます。数秒後に次のように表示されます。

   .. code-block:: text

      === Vibration Alert System (IFTTT) ===
      module is ready
      joining Wi-Fi ... connected
      Detecting...

   ``FAILED (check ssid and password)`` と出たら、ボードがネットワークに入れていませ
   ん。Wi-Fi 名とパスワードを確認し、ESPC2-01 は **2.4GHz** のみ対応であることを思
   い出してください。

   .. image:: ../img/04-ready_shadow.png
      :width: 80%

#. センサーを叩きます。モニターには次のように出ます。

   .. code-block:: text

      Detected vibration!!!
        > AT+CIPMUX=0
        > AT+CIPSTART="TCP","maker.ifttt.com",80
        > AT+CIPSEND=118
        request sent to IFTTT

   数秒以内にメールが届きます。

   .. note::

      2 回続けて叩いてみてください。2 回目は ``An alert was sent recently, so this one
      is skipped.`` とだけ表示されます。2 分ルールが働いているだけで、故障ではありませ
      ん。


4. コードの説明
-----------------------------

#. **モジュールと通信するシリアルポート**

   ESPC2-01 はこのスケッチを実行しておらず、モデムとして動作します。ボードは D0/D1、
   つまり ``Serial1`` で AT コマンドを送ります。ハードウェアポートなので 115200 でも
   ビット化けしません。

   .. code-block:: arduino

      #define EspSerial Serial1

#. **入力する必要があるもの**

   .. code-block:: arduino

      String mySSID = "your_ssid";
      String myPWD  = "your_password";
      String myHOST = "maker.ifttt.com";
      String myPORT = "80";

      String URL = "https://maker.ifttt.com/trigger/vibration_detected/with/key/xxxxxxxxxx";

   IFTTT が表示するとおりに **https:// ごと** コピーし、スケッチが変換します。

   .. code-block:: arduino

      String urlPath() {
        String u = URL;
        u.replace("https://", "");
        u.replace("http://", "");
        int slash = u.indexOf('/');
        return (slash >= 0) ? u.substring(slash) : "/";
      }

   ``myHOST`` と ``myPORT`` は変わりません。IFTTT は常に ``maker.ifttt.com`` のポート
   80 で応答します。個別なのはパスだけで、そこにあなたのキーが入ります。

   .. note::

      ``https://`` をそのままモジュールに送らないのはなぜか。HTTPS は TLS を意味し、
      モジュールは証明書を使って安全な接続を張る必要があり、AT の手順がずっと長くなり
      ます。IFTTT は同じリクエストを平文の **ポート 80** でも受け付けるので、ここでは
      短い方法で十分です。

#. **振動ピンと 2 分ルール**

   .. code-block:: arduino

      unsigned long lastAlertTime = 0;
      const unsigned long postingInterval = 120000L;   // 2 分

      const int sensorPin = 7;

   SW-420 は単純なレベルを返し、**揺れている間は HIGH** になります。2 分ルールがない
   と、1 回の衝撃で何十通ものメールが飛びます。

#. **espModuleInit() - まずモジュールを起こす**

   モジュールは起動に約 1 秒かかり、その起動ログを同じ回線に出力します。この関数は
   ``ready`` を待ってから ``ATE0`` を送り、応答にコマンドのコピーが混ざらないようにし
   ます。

   .. code-block:: arduino

      void espModuleInit() {
        unsigned long t0 = millis();
        String buf;
        while (millis() - t0 < 5000) {
          while (EspSerial.available() && buf.length() < 512) {
            buf += (char)EspSerial.read();
            if (buf.indexOf("ready") >= 0) t0 = millis() - 5000;
          }
          if (buf.indexOf("ready") >= 0) break;
        }
        while (EspSerial.available()) EspSerial.read();
        EspSerial.print("ATE0\r\n");
        delay(300);
        while (EspSerial.available()) EspSerial.read();
      }

   ``buf.length() < 512`` のガードが重要です。これがないと、話し続けるモジュールが
   内側のループを永久に占有し、スケッチは ``setup()`` に到達できません。

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

   すべてのコマンドがこの 1 つの関数を通ります。送信し、応答を集め、期待した答え（ま
   たはエラー）が現れた時点で止まります。**必ず戻る** ので、``OK`` が来なくても
   ボードが固まることはありません。

#. **setup() と loop()**

   .. code-block:: arduino

      void setup() {
        Serial.begin(115200);
        EspSerial.begin(115200);
        espModuleInit();
        Serial.println("module is ready");
        wifiOK = joinWiFi();
      }

      void loop() {
        if (!wifiOK && millis() - lastRetry > 30000) {
          lastRetry = millis();
          wifiOK = joinWiFi();
        }
        ...
        delay(500);
      }

   起動時に Wi-Fi がなくても、スケッチは諦めません。30 秒ごとに再試行します。だから
   ルーターの準備前にボードを起動しても大丈夫です。

#. **sendAlert() - HTTP リクエスト 1 本**

   .. code-block:: arduino

      String req = "GET " + URL + " HTTP/1.1\r\n";
      req += "Host: maker.ifttt.com\r\n";
      req += "Connection: close\r\n\r\n";

      at("AT+CIPMUX=0", 1000, "OK", "ERROR");
      at("AT+CIPSTART=\"TCP\",\"" + myHOST + "\"," + myPORT, 5000, "OK", "ERROR");
      ...
      EspSerial.print("AT+CIPSEND=");
      EspSerial.print(req.length());
      ...
      EspSerial.print(req);

   AT コマンド 3 本で完了します。

   * ``AT+CIPMUX=0`` - 同時接続は 1 本。
   * ``AT+CIPSTART`` - ``maker.ifttt.com:80`` への TCP 接続を開く。
   * ``AT+CIPSEND=<長さ>`` - モジュールが ``>`` を返し、その後にリクエスト本文を送り
     ます。長さは文字数と正確に一致する必要があるので、スケッチは推測せず
     ``req.length()`` を測ります。

   リクエスト自体はブラウザが送るものと同じです。メソッドとパスの行、ヘッダー 1
   行、空行、それだけです。IFTTT はパスを読んだ時点でアプレットを起動します。
